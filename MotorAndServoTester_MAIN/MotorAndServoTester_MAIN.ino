#include <RoverConfig.h>
#include <WheelEncoderSensor.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>
#include <MotorPowerControl.h>



//Global Variables

//counter delays
//using a counter to create delays while still allowing the loop() to run (i.e. for messages, etc.)
unsigned int outputMessageDelay = 0;
unsigned int mtrPowerToggleDelay = 0;

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
	Serial.begin(9600);
}


void loop() {

	//Tasks always running in the background with every loop() cycle
	//Timers
	midLeftSyncTimer->Running();
	midRightSyncTimer->Running();	
	//Wheel Encoders
	wheelEncoder_MidLeft->sensorOnline();
	wheelEncoder_MidRight->sensorOnline();
	//Counter Delays
	//increment the counters
	outputMessageDelay++;
	mtrPowerToggleDelay++;



	//Motor Power Control
	if (mtrPowerToggleDelay >= 40000)//about once a 1 seconds
	{
		//toggle motor power on and off
		Serial.print(F("SWITCHING MTR "));
		if (mtrPowerCtrlr->motorIsOn())//motor is currently on, so turn it off
		{
			mtrPowerCtrlr->setMotorPower(MTR_OFF);
			Serial.println(F("OFF"));
		}
		else//motor is currently off, so turn it on
		{
			mtrPowerCtrlr->setMotorPower(MTR_ON);
			Serial.println(F("ON"));
		}
		Serial.println();
		mtrPowerToggleDelay = 0;//reset the counter
	}



	if (outputMessageDelay >= 40000)//about once a second
	{




		//Print Motor Power Status
		Serial.println(F("=MTR STATUS="));
		if (mtrPowerCtrlr->motorIsOn())//motor is currently on
		{
			Serial.println(F("MTR ON"));
		}
		else//motor is currently off
		{
			
			Serial.println(F("MTR OFF"));
		}
		Serial.println();

		

		//Wheel Encoder Control and Status
		//========Mid Left Motor===========
		byte direction_MidLeft = wheelEncoder_MidLeft->getDirection();
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




		outputMessageDelay = 0;//reset the counter
	}
	




}





void InterruptDispatch_wheelEncoder_MidLeft() {
	wheelEncoder_MidLeft->isrUpdate();
}
void InterruptDispatch_wheelEncoder_MidRight() {
	wheelEncoder_MidRight->isrUpdate();
}