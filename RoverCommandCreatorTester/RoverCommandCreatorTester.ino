//Test code to be used on any Arduino.

#include <RoverCommandCreator.h>
#define _ROVERDATA
#include <RoverConfig.h>

//See Command Creator Spreadsheet for commands:
//K:\Working Directory\DESIGN_PROJ\Design Projects\Robot\My Notes\Command Creator

//Global Variables


char outputCharBuffer[ROVER_COMM_SENTENCE_LENGTH];

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
	RoverCommandCreator::createCmd(ROVERCOMM_CMNC, ROVERCOMM_MAIN, CMD_PRI_LVL_0, CMD_TAG_NO_MSG, "NoData", outputCharBuffer);
	_PC_USB_SERIAL_.println(outputCharBuffer);
	

	//One leading zero test in the CMD_TAG, Priority level 0
	RoverCommandCreator::createCmd(ROVERCOMM_CMNC, ROVERCOMM_MAIN, CMD_PRI_LVL_0, CMD_TAG_NAVI_SLEEP_REQUEST
		, "NoData", outputCharBuffer);
	_PC_USB_SERIAL_.println(outputCharBuffer);

	//No leading zeros test, Priority level 0
	RoverCommandCreator::createCmd(ROVERCOMM_CMNC, ROVERCOMM_MAIN, CMD_PRI_LVL_0, CMD_TAG_LATITUDE_REQUEST
		, "12.3456N", outputCharBuffer);
	_PC_USB_SERIAL_.println(outputCharBuffer);

	//Test without the command tag, Priority level 1, where 123 is the manual command tag
	RoverCommandCreator::createCmd(ROVERCOMM_CMNC, ROVERCOMM_MAIN, CMD_PRI_LVL_1, "123987601.2545E", outputCharBuffer);
	_PC_USB_SERIAL_.println(outputCharBuffer);
		
	RoverCommandCreator::byteToCharArrayWithLeadingZeros(28, outputCharBuffer);//should get 028
	_PC_USB_SERIAL_.println(outputCharBuffer);

	while (1);
}
