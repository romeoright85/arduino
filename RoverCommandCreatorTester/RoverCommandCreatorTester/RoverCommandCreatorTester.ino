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
	
	//Test with the command tag
	Serial.println(roverCommandCreator->createCmd(ROVERCOMM_CMNC, ROVERCOMM_MAIN, CMD_PRI_LVL_0, CMD_TAG_LATITUDE, "12.3456N"));

	//Test without the command tag
	Serial.println(roverCommandCreator->createCmd(ROVERCOMM_CMNC, ROVERCOMM_MAIN, CMD_PRI_LVL_1, "987601.2545E"));
		
	while (1);
}
