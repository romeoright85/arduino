//Used for NAVI - 1

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
#define _ARD_1_NAVI_H //define this flag to turn on NAVI definitions

#include <RoverConfig.h>




void setup() {

	//Setup the HW_UART for communications between AUXI and MAIN, and AUXI and PC USB
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	_MAIN_SERIAL_.begin(MAIN_BAUD_RATE);

}


void loop() {
	
	char rxdChar;

	if (_MAIN_SERIAL_.available() > 1)
	{
		//Output data title/label
		_PC_USB_SERIAL_.println(F("CMNC->COMM:"));

		while (_MAIN_SERIAL_.available() > 0)
		{
			//Read from CMNC/PC USB
			rxdChar = (char)_MAIN_SERIAL_.read();
			//Output to PC USB as well for debug
			_PC_USB_SERIAL_.print(rxdChar);
			delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
		}//end while		
		_PC_USB_SERIAL_.println();//Add a new line at the end
	}
}//end loop

