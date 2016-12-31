//Used for AUXI - 2
//Used for the Gas Sensor, etc.

#include <UpTime.h>


//Global Variables

UpTime * roverUptime = new UpTime();

RoverReset * resetArray[] = {
	roverUptime
};


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}

	Serial.begin(PC_USB_BAUD_RATE);

}


void loop() {
	roverUptime->run();

	roverUptime->printUptime();

	delay(random(500, 5000));//delay a randon number between 0.5 a second to 5 seconds in order to test the code by seeing time variability
}



