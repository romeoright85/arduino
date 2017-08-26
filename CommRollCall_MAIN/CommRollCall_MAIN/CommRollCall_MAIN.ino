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
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	_COMM_SERIAL_.begin(COMM_BAUD_RATE);
	_NAVI_SERIAL_.begin(NAVI_BAUD_RATE);
	_AUXI_SERIAL_.begin(AUXI_BAUD_RATE);

}


void loop() {

	char rxdChar;

	//Take any data received from COMM and send it to AUXI
	if (_COMM_SERIAL_.available() > 1)
	{
		
		//Send tag to PC USB
		_PC_USB_SERIAL_.println(">MAIN>");

		while (_COMM_SERIAL_.available() > 0)
		{
			//Read from COMM
			rxdChar = (char)_COMM_SERIAL_.read();
			//Transmit out to AUXI
			_AUXI_SERIAL_.print(rxdChar);		
			delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
		}//end while		
	}//end if

	//Take any data received from AUXI and send it to NAVI
	if (_AUXI_SERIAL_.available() > 1)
	{
	
		//Send tag to PC USB
		_PC_USB_SERIAL_.println(">MAIN<");		

		while (_AUXI_SERIAL_.available() > 0)
		{
			//Read from AUXI
			rxdChar = (char)_AUXI_SERIAL_.read();
			//Transmit out to NAVI
			_NAVI_SERIAL_.print(rxdChar);			
			delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
		}//end while		
	}//end if

	 //Take any data received from NAVI and send it to CMNC
	if (_NAVI_SERIAL_.available() > 1)
	{
		
		//Send tag to PC USB
		_PC_USB_SERIAL_.println("<MAIN>");

		while (_NAVI_SERIAL_.available() > 0)
		{
			//Read from NAVI
			rxdChar = (char)_NAVI_SERIAL_.read();
			//Transmit out to COMM
			_COMM_SERIAL_.print(rxdChar);			
			delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
		}//end while		
	}//end if

}//end loop

