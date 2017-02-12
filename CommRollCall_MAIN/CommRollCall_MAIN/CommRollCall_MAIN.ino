//Used for MAIN - 3

/*
Once a command is sent from CMNC:
it goes to COMM where COMM appends its tag
then goes to MAIN, where MAIN appends it's tag
then goes to AUXI, where AUXI appends it's tag
then goes to MAIN, where MAIN appends it's tag again (to show it's doing through the right channels)
then goes to NAVI, where NAVI appends it's tag
then goes to MAIN, where MAIN appends it's tag again (to show it's doing through the right channels)
it goes to COMM where COMM appends its tag again (to show it's doing through the right channels)
then goes back to CMNC

CMNC->COMM->MAIN->AUXI->MAIN->NAVI->MAIN-COMM->CMNC
*/


//Must define this before calling RoverConfig.h (either directly or through another header file)
#define _ARD_3_MAIN_H //define this flag to turn on MAIN definitions

#include <RoverConfig.h>



void setup() {

	//Setup the HW_UART for communications between MAIN and COMM, MAIN and AUXI, MAIN and NAVI, and MAIN and PC USB
	Serial.begin(PC_USB_BAUD_RATE);
	Serial1.begin(COMM_BAUD_RATE);
	Serial2.begin(NAVI_BAUD_RATE);
	Serial3.begin(AUXI_BAUD_RATE);

}


void loop() {

	char rxdChar;

	//Take any data received from COMM and send it to AUXI
	if (Serial1.available() > 1)
	{
		//Adding the MAIN tag to the data chain
		Serial3.print(F("-MAIN-"));

		while (Serial1.available() > 0)
		{
			//Read from COMM
			rxdChar = (char)Serial1.read();
			//Transmit out to AUXI
			Serial3.print(rxdChar);
			delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
		}//end while		
	}//end if

	 //Take any data received from AUXI and send it to NAVI
	if (Serial3.available() > 1)
	{
		//Adding the MAIN tag to the data chain
		Serial2.print(F("-MAIN-"));

		while (Serial3.available() > 0)
		{
			//Read from AUXI
			rxdChar = (char)Serial3.read();
			//Transmit out to NAVI
			Serial2.print(rxdChar);
			delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
		}//end while		
	}//end if

	 //Take any data received from NAVI and send it to CMNC
	if (Serial2.available() > 1)
	{
		//Adding the MAIN tag to the data chain
		Serial1.print(F("-MAIN-"));

		while (Serial2.available() > 0)
		{
			//Read from NAVI
			rxdChar = (char)Serial2.read();
			//Transmit out to COMM
			Serial1.print(rxdChar);
			delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
		}//end while		
	}//end if

}//end loop

