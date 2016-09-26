#include <WheelEncoderSensor.h>


//Global Variables

void InterruptDispatch_wheelEncoder_FrontLeft();
void InterruptDispatch_wheelEncoder_FrontRight();
void InterruptDispatch_wheelEncoder_RearLeft();
void InterruptDispatch_wheelEncoder_RearRight();

WheelEncoderSensor * wheelEncoder_FrontLeft = new WheelEncoderSensor(ENCODER_A_FRONT_LEFT, ENCODER_B_FRONT_LEFT, LEFT_MOUNTED_MOTOR, &InterruptDispatch_wheelEncoder_FrontLeft);
//WheelEncoderSensor * wheelEncoder_FrontRight = new WheelEncoderSensor();
//WheelEncoderSensor * wheelEncoder_RearLeft = new WheelEncoderSensor();
//WheelEncoderSensor * wheelEncoder_RearRight = newWheelEncoderSensor();

//RoverReset * resetArray[] = { wheelEncoder_FrontLeft, wheelEncoder_FrontRight,  wheelEncoder_RearLeft, wheelEncoder_RearRight };
RoverReset * resetArray[] = { wheelEncoder_FrontLeft };//DEBUG


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}

}


void loop() {
	wheelEncoder_FrontLeft->getDirection();
	wheelEncoder_FrontLeft->getSpeed();
	wheelEncoder_FrontLeft->getFootage();
}





void InterruptDispatch_wheelEncoder_FrontLeft() {
	wheelEncoder_FrontLeft->isrUpdate();
}
/*
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