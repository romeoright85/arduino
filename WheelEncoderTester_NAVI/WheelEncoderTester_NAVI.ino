#include <RoverConfig.h>
#include <WheelEncoderSensor.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>

//Global Variables


//The WheelEncoder will wait for 1sec (1000 periods * 1mS) between each wheel encoder calculation
DelayCounter * wheelEncoderSyncCounter = new DelayCounter(DELAY_200_PERIODS);//initialize it to count to 1 periods x 1ms delay timer resolution = 1ms before the count has reached flag goes true


GlobalDelayTimer * wheelEncoderSyncTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, wheelEncoderSyncCounter);//everytime the delay interval (resolution) is reached, it will increment the delay counter. The standard resolution used for the Rover has been 5mS so it's not too small where it has to increment the counter often, but not to big where it won't work for many different classes without being too slow or fast



unsigned int counterDelay = 0;//using a counter to delay the output messages without the delaying the return time of the loop(). Timing doesn't have to be exact. Just picked an approximate number that outputted the messages around once a second.


void InterruptDispatch_wheelEncoder_FrontLeft();
void InterruptDispatch_wheelEncoder_FrontRight();
void InterruptDispatch_wheelEncoder_RearLeft();
void InterruptDispatch_wheelEncoder_RearRight();

WheelEncoderSensor * wheelEncoder_FrontLeft = new WheelEncoderSensor(ENCODER_A_FRONT_LEFT, ENCODER_B_FRONT_LEFT, LEFT_MOUNTED, &InterruptDispatch_wheelEncoder_FrontLeft, wheelEncoderSyncCounter);

/*
WRITE ME LATER
WheelEncoderSensor * wheelEncoder_FrontRight = new WheelEncoderSensor();
WheelEncoderSensor * wheelEncoder_RearLeft = new WheelEncoderSensor();
WheelEncoderSensor * wheelEncoder_RearRight = newWheelEncoderSensor();


*/



RoverReset * resetArray[] = { wheelEncoderSyncCounter, wheelEncoderSyncTimer, wheelEncoder_FrontLeft };//DEBUG, ADD OTHER OBJECTS LATER


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
	wheelEncoderSyncTimer->Running();
	wheelEncoder_FrontLeft->sensorOnline();
	
	
	//Serial.print("test1");//DEBUG
	//Serial.print(wheelEncoderSyncCounter->test1);//DEBUG
	//Serial.print("test1");//DEBUG
	//Serial.println(wheelEncoderSyncCounter->test2);//DEBUG
	
	
	byte direction = wheelEncoder_FrontLeft->getDirection();


	if (counterDelay >= 40000)
	{

		Serial.print(F("Dir: "));
		if (direction == MOTOR_FORWARD)//forward, reverse, stopped
		{
			Serial.println(F("Fwd"));
		}
		else if (direction == MOTOR_REVERSE)
		{
			Serial.println(F("Rev"));
		}
		else//MOTOR_STOPPED
		{
			Serial.println(F("Stopped"));
		}


		Serial.print(F("Dist: "));//in inches
		Serial.println(wheelEncoder_FrontLeft->getFootage());//distance traveled in feet


		Serial.print(F("Spd: "));//in inches per second
		Serial.println(wheelEncoder_FrontLeft->getSpeed());//in inches per second

		counterDelay = 0;//reset the counter
	}
	counterDelay++;//increment the counter
	
	


}





void InterruptDispatch_wheelEncoder_FrontLeft() {
	wheelEncoder_FrontLeft->isrUpdate();
}
/*
WRITE ME LATER
void InterruptDispatch_wheelEncoder_FrontLeft() {
	wheelEncoder_FrontRight->isrUpdate();
}
void InterruptDispatch_wheelEncoder_FrontLeft() {
	wheelEncoder_RearLeft->isrUpdate();
}
void InterruptDispatch_wheelEncoder_FrontLeft() {
	wheelEncoder_RearRight->isrUpdate();
}
*/