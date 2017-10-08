//Test code to be used on any Arduino.

#include <RoverCommandProcessor.h>

//See Command Creator Spreadsheet for commands:
//K:\Working Directory\DESIGN_PROJ\Design Projects\Robot\My Notes\Command Creator

//Global Variables


RoverReset * resetArray[] = {

};



void setup() {


	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}

	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	delay(100);
}


void loop() {


	//Test with the command tag

	//Two leading zeros test in the CMD_TAG, Priority level 0
	_PC_USB_SERIAL_.println(RoverCommandProcessor::createCmd(ROVERCOMM_CMNC, ROVERCOMM_MAIN, CMD_PRI_LVL_0, CMD_TAG_NO_MSG, "NoData"));
	_PC_USB_SERIAL_.println(RoverCommandProcessor::createCmd(ROVERCOMM_CMNC, ROVERCOMM_MAIN, CMD_PRI_LVL_0, CMD_TAG_DEBUG_OUTPUT_RXD_CMD
		, "NoData"));


	//One leading zero test in the CMD_TAG, Priority level 0
	_PC_USB_SERIAL_.println(RoverCommandProcessor::createCmd(ROVERCOMM_CMNC, ROVERCOMM_MAIN, CMD_PRI_LVL_0, CMD_TAG_NAVI_SLEEP_REQUEST
		, "NoData"));

	//No leading zeros test, Priority level 0
	_PC_USB_SERIAL_.println(RoverCommandProcessor::createCmd(ROVERCOMM_CMNC, ROVERCOMM_MAIN, CMD_PRI_LVL_0, CMD_TAG_LATITUDE_REQUEST
		, "12.3456N"));

	//Test without the command tag, Priority level 1, where 123 is the manual command tag
	_PC_USB_SERIAL_.println(RoverCommandProcessor::createCmd(ROVERCOMM_CMNC, ROVERCOMM_MAIN, CMD_PRI_LVL_1, "123987601.2545E"));


	while (1);
}
