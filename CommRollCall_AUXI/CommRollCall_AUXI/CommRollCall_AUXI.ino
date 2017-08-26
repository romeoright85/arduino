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
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	_MAIN_SERIAL_.begin(MAIN_BAUD_RATE);

}


void loop() {

	char rxdChar;

	//Take any data received from MAIN and send it back out to MAIN
	if (_MAIN_SERIAL_.available() > 1)
	{
		//Send tag to PC USB
		_PC_USB_SERIAL_.println(">AUXI<");
		while (_MAIN_SERIAL_.available() > 0)
		{
			//Read from MAIN
			rxdChar = (char)_MAIN_SERIAL_.read();
			//Transmit back out to MAIN
			_MAIN_SERIAL_.print(rxdChar);			
			delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
		}//end while		
	}//end if



}//end loop

