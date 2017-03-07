//Used for MAIN - 3

#include <RoverConfig.h>
#include <WheelEncoderSensor.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>
#include <MotorPowerControl.h>

//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast

#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ Serial1
#else
	#define _SERIAL_DEBUG_CHANNEL_ Serial
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
	midLeftSyncCounter,
	midLeftSyncTimer,
	midRightSyncCounter,
	midRightSyncTimer,
	wheelEncoder_MidLeft,
	wheelEncoder_MidRight,
	mtrPowerCtrlr
};


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	Serial.begin(PC_USB_BAUD_RATE);
	Serial1.begin(COMM_BAUD_RATE);
	delay(100);
	mtrPowerCtrlr->setMotorPower(MTR_ENABLED);
	_SERIAL_DEBUG_CHANNEL_.println(F("ENABLING MTR"));
	getMotorStatus();
	delay(1000);
}


void loop() {

	//Tasks always running in the background with every loop() cycle
	//Timers
	midLeftSyncTimer->Running();
	midRightSyncTimer->Running();	
	//Wheel Encoders
	wheelEncoder_MidLeft->sensorOnline();
	wheelEncoder_MidRight->sensorOnline();


	char rxData;
	

	if (_SERIAL_DEBUG_CHANNEL_.available() > 0)
	{
		rxData = Serial1.read();//Get data from COMM

		delay(1);

		switch (rxData)
		{
			case '1'://turn motors on
				mtrPowerCtrlr->setMotorPower(MTR_ENABLED);
			#ifdef _DEBUG_COMM_BROADCAST
				Serial1.println(F("ENABLING MTR"));
			#else
				Serial.println(F("ENABLING MTR"));
			#endif
				getMotorStatus();
				delay(500);
				break;
			case '0'://turn motors off
				mtrPowerCtrlr->setMotorPower(MTR_DISABLED);
			#ifdef _DEBUG_COMM_BROADCAST
				Serial1.println(F("DISABLING MTR"));
			#else
				Serial.println(F("DISABLING MTR"));
			#endif				
				getMotorStatus();
				delay(500);
				break;
			default:
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
