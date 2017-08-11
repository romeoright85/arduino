//Used for MAIN - 3

/*
Takes AUXI data forwards the data to NAVI
*/

//Must define this before calling RoverConfig.h (either directly or through another header file)
#define _ARD_3_MAIN_H //define this flag to turn on MAIN definitions

#include <RoverConfig.h>

void setup() {

	//Setup the HW_UART for communications between MAIN and COMM, MAIN and AUXI, MAIN and NAVI, and MAIN and PC USB
	Serial.begin(PC_USB_BAUD_RATE);	
	Serial2.begin(NAVI_BAUD_RATE);
	Serial3.begin(AUXI_BAUD_RATE);

}


void loop() {

	char rxdChar;

	 //Take any data received from AUXI and send it to NAVI
	if (Serial3.available() > 1)
	{		
		while (Serial3.available() > 0)
		{
			//Read from AUXI
			rxdChar = (char)Serial3.read();
			//Transmit out to NAVI
			Serial2.print(rxdChar);
			//Also output to PC USB as well for debug
			Serial.print(rxdChar);
			delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
		}//end while	
		Serial.println();//Add a new line at the end
	}//end if	

}//end loop

