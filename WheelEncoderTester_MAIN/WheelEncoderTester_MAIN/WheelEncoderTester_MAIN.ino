#include <WheelEncoderSensor.h>


//Global Variables


WheelEncoderSensor * wheelEncoder_MidLeft = new WheelEncoderSensor();
WheelEncoderSensor * wheelEncoder_MidRight = new WheelEncoderSensor();

RoverReset * resetArray[] = { wheelEncoder_MidLeft, wheelEncoder_MidRight };



void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}

}


void loop() {
	
}


