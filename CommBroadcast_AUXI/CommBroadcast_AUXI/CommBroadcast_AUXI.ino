//Used for AUXI - 2

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
#define _ARD_2_AUXI_H //define this flag to turn on AUXI definitions

#include <RoverConfig.h>




void setup() {

	//Setup the HW_UART for communications between AUXI and MAIN, and AUXI and PC USB
	Serial.begin(PC_USB_BAUD_RATE);
	Serial2.begin(MAIN_BAUD_RATE);

}


void loop() {
	//Do Nothing
	
	
}//end loop

