//Used for MAIN - 3

#include <RoverHwReset.h>


//Global Variables

RoverHwReset * commHwResetter = new RoverHwReset(COMM_HW_RESET_CTRL_PIN);

RoverReset * resetArray[] = {
	commHwResetter
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

	delay(1000);
	Serial.println(F("Running..."));
	delay(4000);
	Serial.println(F("Resetting COMM..."));
	commHwResetter->performHwReset();	
	delay(1000);
	Serial.println(F("Reset Complete!"));
}
