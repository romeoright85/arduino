//Used for MAIN - 3

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

	//Take any data received from COMM and send it to AUXI and NAVI
	if (Serial1.available() > 1)
	{
		while (Serial1.available() > 0)
		{
			//Read from COMM
			rxdChar = (char)Serial1.read();			
			//Transmit out to AUXI
			Serial3.print(rxdChar);
			//Transmit out to NAVI
			Serial2.print(rxdChar);
			delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
		}//end while		
	}//end if
	//Take any data received from AUXI and send it back to COMM
	if (Serial3.available() > 1)
	{
		while (Serial3.available() > 0)
		{
			//Read from AUXI
			rxdChar = (char)Serial3.read();
			//Transmit out to COMM
			Serial1.print(rxdChar);
			delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
		}//end while		
	}//end if	
	 //Take any data received from NAVI and send it back to COMM
	if (Serial2.available() > 1)
	{
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

