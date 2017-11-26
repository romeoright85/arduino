//Used for MAIN - 3

/*
When you enable and disable the motor, you're enabling and disabling the MOSFET through an OR gate that is also controled by the toggle switch on the rover.
Once you disable the motor and then reenable it, you'll probably have to re-run the motor calibration because it lost power.
It's actually best just to switch buffers to manual mode or auto mode when you want to stop the rover. It's best to only disable the motor controller mosfet for emergency stops only, as it might not come up or work properly again until you physically reboot the rover.
*/

#include <RoverConfig.h>
#include <WheelEncoderSensor.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>
#include <MotorPowerControl.h>

//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast

#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ _COMM_SERIAL_ //When using COMM Broadcast, reroute the PC USB output to the channel to COMM instead
#else
	#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_
#endif


//Global Variables

MotorPowerControl * mtrPowerCtrlr = new MotorPowerControl(MTR_FET_CTRL_PIN, MTR_ENABLE_STATUS);

//The WheelEncoder will wait for 1sec (1000 periods * 1mS) between each wheel encoder calculation
DelayCounter * midLeftSyncCounter = new DelayCounter(DELAY_200_PERIODS);//initialize it to count to 1 periods x 1ms delay timer resolution = 1ms before the count has reached flag goes true
GlobalDelayTimer * midLeftSyncTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, midLeftSyncCounter);//everytime the delay interval (resolution) is reached, it will increment the delay counter. The standard resolution used for the Rover has been 5mS so it's not too small where it has to increment the counter often, but not to big where it won't work for many different classes without being too slow or fast

DelayCounter * midRightSyncCounter = new DelayCounter(DELAY_200_PERIODS);//initialize it to count to 1 periods x 1ms delay timer resolution = 1ms before the count has reached flag goes true
GlobalDelayTimer * midRightSyncTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, midRightSyncCounter);//everytime the delay interval (resolution) is reached, it will increment the delay counter. The standard resolution used for the Rover has been 5mS so it's not too small where it has to increment the counter often, but not to big where it won't work for many different classes without being too slow or fast

void InterruptDispatch_wheelEncoder_MidLeft();
void InterruptDispatch_wheelEncoder_MidRight();


//Note: Remember to update all fields of the constructor. All the fields are unique to/distinct for each motor. You can't share the counter, because it gets reset for each one. And each timer get's only one counter, so you need a timer for each one as well.
WheelEncoderSensor * wheelEncoder_MidLeft = new WheelEncoderSensor(ENCODER_A_MID_LEFT, ENCODER_B_MID_LEFT, LEFT_MOUNTED, &InterruptDispatch_wheelEncoder_MidLeft, midLeftSyncCounter);
WheelEncoderSensor * wheelEncoder_MidRight = new WheelEncoderSensor(ENCODER_A_MID_RIGHT, ENCODER_B_MID_RIGHT, RIGHT_MOUNTED, &InterruptDispatch_wheelEncoder_MidRight, midRightSyncCounter);



RoverReset * resetArray[] = {
	mtrPowerCtrlr,
	midLeftSyncCounter,
	midLeftSyncTimer,
	midRightSyncCounter,
	midRightSyncTimer,
	wheelEncoder_MidLeft,
	wheelEncoder_MidRight	
};


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	_COMM_SERIAL_.begin(COMM_BAUD_RATE);
	delay(100);
	mtrPowerCtrlr->setMotorPower(MTR_ENABLED);
	_SERIAL_DEBUG_CHANNEL_.println(F("ENABLING MTR"));
	getMotorStatus();
	delay(1000);

	
	//Setting Up Timer Interrupt
	OCR0A = 0x7F;//Set the timer to interrupt somewhere in the middle of it's count, say 127 aka 7F in hex (since Timer0 is 8 bit and counts from 0 to 255)
	TIMSK0 |= _BV(OCIE0A);//Activating the Timer Interrupt by setting the Mask Register
	/*	
		Reference:
		https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers
		http://forum.arduino.cc/index.php?topic=3240.0
		https://protostack.com.au/2010/09/timer-interrupts-on-an-atmega168/
	*/
}



SIGNAL(TIMER0_COMPA_vect)//Interrupt Service Routine
{
	//Tasks always running in the background, called by the timer about every 1 ms
	//This will allow the millis value to be checked every millisecond and not get missed.
	//Timer(s)
	midLeftSyncTimer->Running();
	midRightSyncTimer->Running();	
}

void loop() {
	

	//Wheel Encoders
	wheelEncoder_MidLeft->sensorOnline();
	wheelEncoder_MidRight->sensorOnline();


	char rxData;
	

	if (_SERIAL_DEBUG_CHANNEL_.available() > 0)
	{
		rxData = (char)_SERIAL_DEBUG_CHANNEL_.read();//Get data from COMM or PC USB

		delay(1);

		switch (rxData)
		{
			case '1'://turn motors on
				mtrPowerCtrlr->setMotorPower(MTR_ENABLED);
				_SERIAL_DEBUG_CHANNEL_.println(F("ENABLING MTR"));
				getMotorStatus();
				delay(500);
				break;
			case '0'://turn motors off
				mtrPowerCtrlr->setMotorPower(MTR_DISABLED);
				_SERIAL_DEBUG_CHANNEL_.println(F("DISABLING MTR"));
				getMotorStatus();
				delay(500);
				break;
			default:
				_SERIAL_DEBUG_CHANNEL_.println(F("INVALID OPTION"));
				break;
		}//end switch
	}//end if
	
	

	//Wheel Encoder Control and Status
	//========Mid Left Motor===========
	byte direction_MidLeft = wheelEncoder_MidLeft->getDirection();
	_SERIAL_DEBUG_CHANNEL_.println(F("=MID LEFT MTR="));
	_SERIAL_DEBUG_CHANNEL_.print(F("Dir: "));
	if (direction_MidLeft == MOTOR_FORWARD)//forward, reverse, stopped
	{
		_SERIAL_DEBUG_CHANNEL_.println(F("Fwd"));
	}
	else if (direction_MidLeft == MOTOR_REVERSE)
	{
		_SERIAL_DEBUG_CHANNEL_.println(F("Rev"));
	}
	else//MOTOR_STOPPED
	{
		_SERIAL_DEBUG_CHANNEL_.println(F("Stopped"));
	}
	_SERIAL_DEBUG_CHANNEL_.print(F("Dist: "));//in inches
	_SERIAL_DEBUG_CHANNEL_.println(wheelEncoder_MidLeft->getFootage());//distance traveled in feet
	_SERIAL_DEBUG_CHANNEL_.print(F("Spd: "));//in inches per second
	_SERIAL_DEBUG_CHANNEL_.println(wheelEncoder_MidLeft->getSpeed());//in inches per second


													 //========Mid Right Motor===========
	byte direction_MidRight = wheelEncoder_MidRight->getDirection();



	_SERIAL_DEBUG_CHANNEL_.println(F("=MID RIGHT MTR="));



	_SERIAL_DEBUG_CHANNEL_.print(F("Dir: "));
	if (direction_MidRight == MOTOR_FORWARD)//forward, reverse, stopped
	{
		_SERIAL_DEBUG_CHANNEL_.println(F("Fwd"));
	}
	else if (direction_MidRight == MOTOR_REVERSE)
	{
		_SERIAL_DEBUG_CHANNEL_.println(F("Rev"));
	}
	else//MOTOR_STOPPED
	{
		_SERIAL_DEBUG_CHANNEL_.println(F("Stopped"));
	}
	_SERIAL_DEBUG_CHANNEL_.print(F("Dist: "));//in inches
	_SERIAL_DEBUG_CHANNEL_.println(wheelEncoder_MidRight->getFootage());//distance traveled in feet
	_SERIAL_DEBUG_CHANNEL_.print(F("Spd: "));//in inches per second
	_SERIAL_DEBUG_CHANNEL_.println(wheelEncoder_MidRight->getSpeed());//in inches per second
	_SERIAL_DEBUG_CHANNEL_.println();

	
	delay(500);
	

}//end loop()


void InterruptDispatch_wheelEncoder_MidLeft() {
	wheelEncoder_MidLeft->isrUpdate();
}
void InterruptDispatch_wheelEncoder_MidRight() {
	wheelEncoder_MidRight->isrUpdate();
}

void getMotorStatus()
{
	//Print Motor Power Status
	_SERIAL_DEBUG_CHANNEL_.println(F("=MTR STATUS="));
	if (mtrPowerCtrlr->motorIsOn())//motor is currently on
	{
		_SERIAL_DEBUG_CHANNEL_.println(F("ENABLED"));
	}//end if
	else//motor is currently off
	{

		_SERIAL_DEBUG_CHANNEL_.println(F("DISABLED"));
	}//end else
	_SERIAL_DEBUG_CHANNEL_.println();
}
