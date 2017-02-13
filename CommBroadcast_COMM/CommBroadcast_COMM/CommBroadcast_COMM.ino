//Used for COMM - 4

/*
Takes CMNC data and broadcasts the exact same message to all Ardunio.
Good for a quick debug when you need to receive unformatted data back to CMNC and want to send data to from CMNC without having to worry about data filtering and re-routing. (all data from CMNC will be broadcasted to all other Arduinos the same)
Load this on all Arduinos except the UUT. The UUT should have it's own code running. The input to the UUT will take in data sent from this CommBroadcast and the output will be received by CommBroadcast and sent back out to CMNC.


If COMM is the UUT, that code should be loaded instead. And if it's not the UUT, then it should send the command to MAIN.
If MAIN is the UUT, that code should be loaded instead. And if it's not the UUT, then it should send the command to NAVI and AUXI.
If AUXI or NAVI is the UUT, that code should be loaded instead. And if it's not the UUT, then it should not send anything back. Only the UUT should respond.
Still load this code, to make sure AUXI or NAVI isn't loaded with any "old" or "residual" code that might interfere with this test.
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
		//Output data title/label
		Serial.println(F("CMNC->COMM:"));

		while (Serial.available() > 0 )
		{
			//Read from CMNC/PC USB
			rxdChar = (char)Serial.read();
			//Transmit out to MAIN
			swSerialMAIN.print(rxdChar);
			//Also output to PC USB as well for debug
			Serial.print(rxdChar);
			delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
		}//end while
		Serial.println();//Add a new line at the end
	}//end if
	//Take any data received from MAIN and send it to CMNC/PC USB
	if (swSerialMAIN.available() > 1)
	{
		//Output data title/label
		Serial.println(F("COMM->CMNC:"));

		while (swSerialMAIN.available() > 0)
		{
			//Read from MAIN
			rxdChar = (char)swSerialMAIN.read();			
			//Transmit out to CMNC/PC USB
			Serial.print(rxdChar);
			delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
		}//end while
		Serial.println();//Add a new line at the end
	}//end if	
}//end loop

