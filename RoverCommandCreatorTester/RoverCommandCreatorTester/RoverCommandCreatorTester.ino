#include <RoverCommandCreator.h>


//Global Variables

RoverCommandCreator * roverCommandCreator = new RoverCommandCreator();

RoverReset * resetArray[] = {
	roverCommandCreator
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
	//need to emulate the conversion of doubles, bytes, char, char *, etc. like in the GPS class, then pass it to createCmd to see if it works




	Serial.println(roverCommandCreator->createCmd(ROVERCOMM_CMNC, ROVERCOMM_MAIN, CMD_PRI_LVL_0, CMD_TAG_LATITUDE, "12.3456N"));
	
	Serial.println("Hi!");

	while (1);
}
