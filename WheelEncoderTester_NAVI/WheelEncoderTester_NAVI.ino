#include <WheelEncoderSensor.h>


//Global Variables

void InterruptDispatch_wheelEncoder_FrontLeft();
void InterruptDispatch_wheelEncoder_FrontRight();
void InterruptDispatch_wheelEncoder_RearLeft();
void InterruptDispatch_wheelEncoder_RearRight();

WheelEncoderSensor * wheelEncoder_FrontLeft = new WheelEncoderSensor(ENCODER_A_FRONT_LEFT, ENCODER_B_FRONT_LEFT, LEFT_MOUNTED, &InterruptDispatch_wheelEncoder_FrontLeft);

/*
WRITE ME LATER
WheelEncoderSensor * wheelEncoder_FrontRight = new WheelEncoderSensor();
WheelEncoderSensor * wheelEncoder_RearLeft = new WheelEncoderSensor();
WheelEncoderSensor * wheelEncoder_RearRight = newWheelEncoderSensor();

RoverReset * resetArray[] = { wheelEncoder_FrontLeft, wheelEncoder_FrontRight,  wheelEncoder_RearLeft, wheelEncoder_RearRight };
*/

RoverReset * resetArray[] = { wheelEncoder_FrontLeft };//DEBUG


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	Serial.begin(9600);
}


void loop() {


	byte direction = wheelEncoder_FrontLeft->getDirection();

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
	
	delay(1000);



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