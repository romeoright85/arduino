#include <RoverConfig.h>
#include <WheelEncoderSensor.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>

//Global Variables


unsigned int outputMessageDelay = 0;//using a counter to delay the output messages without the delaying the return time of the loop(). Timing doesn't have to be exact. Just picked an approximate number that outputted the messages around once a second.



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
	wheelEncoder_MidRight	
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
	





	if (outputMessageDelay >= 40000)
	{


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
	outputMessageDelay++;//increment the counter




}





void InterruptDispatch_wheelEncoder_MidLeft() {
	wheelEncoder_MidLeft->isrUpdate();
}
void InterruptDispatch_wheelEncoder_MidRight() {
	wheelEncoder_MidRight->isrUpdate();
}
