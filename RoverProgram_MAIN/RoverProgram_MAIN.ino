//Used for MAIN - 3


#include <RoverCaptain.h>


//Global Variables

RoverCaptain * roverCaptain = new RoverCaptain();


void setup() {


	Serial.begin(PC_USB_BAUD_RATE);
	delayMicroseconds(1);//add some delay to give the serial time to startup
	roverCaptain->reset();
}


void loop() {
	roverCaptain->run();
}
