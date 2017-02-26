//Used for AUXI - 2

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
#define _ARD_2_AUXI_H //define this flag to turn on AUXI definitions

#include <RoverConfig.h>



void setup() {

	//Setup the HW_UART for communications between AUXI and MAIN, and AUXI and PC USB
	Serial.begin(PC_USB_BAUD_RATE);
	Serial2.begin(MAIN_BAUD_RATE);

}


void loop() {

	char rxdChar;

	//Take any data received from MAIN and send it back out to MAIN
	if (Serial2.available() > 1)
	{
		//Send tag to PC USB
		Serial.println(">AUXI<");
		while (Serial2.available() > 0)
		{
			//Read from MAIN
			rxdChar = (char)Serial2.read();
			//Transmit back out to MAIN
			Serial2.print(rxdChar);			
			delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
		}//end while		
	}//end if



}//end loop
