//Used for COMM - 4

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
*/


//Must define this before calling RoverConfig.h (either directly or through another header file)
#define _ARD_4_COMM_H //define this flag to turn on COMM definitions

#include <SoftwareSerial.h>
#include <RoverConfig.h>



SoftwareSerial swSerialMAIN(COMM_SW_UART_RX_PIN, COMM_SW_UART_TX_PIN);


void setup() {

	//Setup the HW_UART for communications between COMM and CMNC/PC USB
	Serial.begin(CMNC_BAUD_RATE);

	//Setup the SW_UART for communications between COMM and MAIN
	swSerialMAIN.begin(MAIN_BAUD_RATE);
}


void loop() {

	char rxdChar;

	//Take any data received from CMNC/PC USB and send it to MAIN
	if (Serial.available() > 1)
	{
		//Adding the COMM tag to the data chain
		swSerialMAIN.print(F("-COMM-"));

		while (Serial.available() > 0)
		{
			//Read from CMNC/PC USB
			rxdChar = (char)Serial.read();
			//Transmit out to MAIN
			swSerialMAIN.print(rxdChar);
			delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
		}//end while		
	}//end if
	 //Take any data received from MAIN and send it to CMNC/PC USB
	if (swSerialMAIN.available() > 1)
	{
		//Adding the COMM tag to the data chain
		swSerialMAIN.print(F("-COMM-"));

		while (swSerialMAIN.available() > 0)
		{
			//Read from CMNC/PC USB
			rxdChar = (char)swSerialMAIN.read();
			//Transmit out to MAIN
			Serial.print(rxdChar);
			delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
		}//end while		
	}//end if	
}//end loop

