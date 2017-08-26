//Used for MAIN - 3

/*
Takes AUXI data forwards the data to NAVI
*/

//Must define this before calling RoverConfig.h (either directly or through another header file)
#define _ARD_3_MAIN_H //define this flag to turn on MAIN definitions

#include <RoverConfig.h>

void setup() {

	//Setup the HW_UART for communications between MAIN and COMM, MAIN and AUXI, MAIN and NAVI, and MAIN and PC USB
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);	
	_NAVI_SERIAL_.begin(NAVI_BAUD_RATE);
	_AUXI_SERIAL_.begin(AUXI_BAUD_RATE);

}


void loop() {

	char rxdChar;

	 //Take any data received from AUXI and send it to NAVI
	if (_AUXI_SERIAL_.available() > 1)
	{		
		while (_AUXI_SERIAL_.available() > 0)
		{
			//Read from AUXI
			rxdChar = (char)_AUXI_SERIAL_.read();
			//Transmit out to NAVI
			_NAVI_SERIAL_.print(rxdChar);
			//Also output to PC USB as well for debug
			_PC_USB_SERIAL_.print(rxdChar);
			delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
		}//end while	
		//Note: Don't send a newline. The AUXI should already do this with _PC_USB_SERIAL_.println().
	}//end if	

}//end loop

