//Used for MAIN - 3

#include <RoverConfig.h>
#include <WheelEncoderSensor.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>
#include <MotorPowerControl.h>

//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast


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
#ifdef _DEBUG_COMM_BROADCAST
	Serial1.println(F("ENABLING MTR"));
#else
	Serial.println(F("ENABLING MTR"));
#endif
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
	
#ifdef _DEBUG_COMM_BROADCAST
	if (Serial1.available() > 0)
	{
		rxData = Serial1.read();//Get data from COMM
#else
	if (Serial.available() > 0)
	{
		rxData = Serial.read();//Get data from the computer
#endif

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
#ifdef _DEBUG_COMM_BROADCAST
	Serial1.println(F("=MID LEFT MTR="));
	Serial1.print(F("Dir: "));
	if (direction_MidLeft == MOTOR_FORWARD)//forward, reverse, stopped
	{
		Serial1.println(F("Fwd"));
	}
	else if (direction_MidLeft == MOTOR_REVERSE)
	{
		Serial1.println(F("Rev"));
	}
	else//MOTOR_STOPPED
	{
		Serial1.println(F("Stopped"));
	}
	Serial1.print(F("Dist: "));//in inches
	Serial1.println(wheelEncoder_MidLeft->getFootage());//distance traveled in feet
	Serial1.print(F("Spd: "));//in inches per second
	Serial1.println(wheelEncoder_MidLeft->getSpeed());//in inches per second


													 //========Mid Right Motor===========
	byte direction_MidRight = wheelEncoder_MidRight->getDirection();
	Serial1.println(F("=MID RIGHT MTR="));
	Serial1.print(F("Dir: "));
	if (direction_MidRight == MOTOR_FORWARD)//forward, reverse, stopped
	{
		Serial1.println(F("Fwd"));
	}
	else if (direction_MidRight == MOTOR_REVERSE)
	{
		Serial1.println(F("Rev"));
	}
	else//MOTOR_STOPPED
	{
		Serial1.println(F("Stopped"));
	}
	Serial1.print(F("Dist: "));//in inches
	Serial1.println(wheelEncoder_MidRight->getFootage());//distance traveled in feet
	Serial1.print(F("Spd: "));//in inches per second
	Serial1.println(wheelEncoder_MidRight->getSpeed());//in inches per second
	Serial1.println();
#else
	Serial.println(F("=MID LEFT MTR="));
	Serial.print(F("Dir: "));
	if (direction_MidLeft == MOTOR_FORWARD)//forward, reverse, stopped
	{
		Serial.println(F("Fwd"));
	}
	else if (direction_MidLeft == MOTOR_REVERSE)
	{
		Serial.println(F("Rev"));
	}
	else//MOTOR_STOPPED
	{
		Serial.println(F("Stopped"));
	}
	Serial.print(F("Dist: "));//in inches
	Serial.println(wheelEncoder_MidLeft->getFootage());//distance traveled in feet
	Serial.print(F("Spd: "));//in inches per second
	Serial.println(wheelEncoder_MidLeft->getSpeed());//in inches per second


													 //========Mid Right Motor===========
	byte direction_MidRight = wheelEncoder_MidRight->getDirection();
	Serial.println(F("=MID RIGHT MTR="));
	Serial.print(F("Dir: "));
	if (direction_MidRight == MOTOR_FORWARD)//forward, reverse, stopped
	{
		Serial.println(F("Fwd"));
	}
	else if (direction_MidRight == MOTOR_REVERSE)
	{
		Serial.println(F("Rev"));
	}
	else//MOTOR_STOPPED
	{
		Serial.println(F("Stopped"));
	}
	Serial.print(F("Dist: "));//in inches
	Serial.println(wheelEncoder_MidRight->getFootage());//distance traveled in feet
	Serial.print(F("Spd: "));//in inches per second
	Serial.println(wheelEncoder_MidRight->getSpeed());//in inches per second
	Serial.println();
#endif
	


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
#ifdef _DEBUG_COMM_BROADCAST
	//Print Motor Power Status
	Serial1.println(F("=MTR STATUS="));
	if (mtrPowerCtrlr->motorIsOn())//motor is currently on
	{
		Serial1.println(F("ENABLED"));
	}//end if
	else//motor is currently off
	{

		Serial1.println(F("DISABLED"));
	}//end else
	Serial1.println();
#else
	//Print Motor Power Status
	Serial.println(F("=MTR STATUS="));
	if (mtrPowerCtrlr->motorIsOn())//motor is currently on
	{
		Serial.println(F("ENABLED"));
	}//end if
	else//motor is currently off
	{

		Serial.println(F("DISABLED"));
	}//end else
	Serial.println();
#endif

}
