//Test code to be used on any Arduino.

#include <RoverCommandCreator.h>

//See Command Creator Spreadsheet for commands:
//K:\Working Directory\DESIGN_PROJ\Design Projects\Robot\My Notes\Command Creator

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
	
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	
}


void loop() {
	
	
	//Test with the command tag
	
	//Two leading zeros test
	_PC_USB_SERIAL_.println(roverCommandCreator->createCmd(ROVERCOMM_CMNC, ROVERCOMM_MAIN, CMD_PRI_LVL_0, CMD_TAG_NO_MSG, "NoData"));// Result: /1c400000NoData
	_PC_USB_SERIAL_.println(roverCommandCreator->createCmd(ROVERCOMM_CMNC, ROVERCOMM_MAIN, CMD_PRI_LVL_0, CMD_TAG_DEBUG_OUTPUT_RXD_CMD
		, "NoData"));// Result: 


	//One leading zero test
	_PC_USB_SERIAL_.println(roverCommandCreator->createCmd(ROVERCOMM_CMNC, ROVERCOMM_MAIN, CMD_PRI_LVL_0, CMD_TAG_NAVI_SLEEP_REQUEST
		, "NoData"));// Result: 

	//No leading zeros test
	_PC_USB_SERIAL_.println(roverCommandCreator->createCmd(ROVERCOMM_CMNC, ROVERCOMM_MAIN, CMD_PRI_LVL_0, CMD_TAG_LATITUDE_REQUEST
		, "12.3456N"));// Result: /1c40016912.3456N
	
	//Test without the command tag
	_PC_USB_SERIAL_.println(roverCommandCreator->createCmd(ROVERCOMM_CMNC, ROVERCOMM_MAIN, CMD_PRI_LVL_1, "987601.2545E"));// Result: /1c401987601.2545E
	


	while (1);
}
