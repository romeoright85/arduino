/*
Used for any Arduino:
AUXI - 2
NAVI - 1
COMM - 4
MAIN - 3


To be used to help test other code like:
WakeUpTesters
HwResetTesters
etc.
*/



#include <RoverConfig.h>




void setup() {
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	delay(1000);
	_PC_USB_SERIAL_.println("Arduino Starting Up");
}


void loop() {
	_PC_USB_SERIAL_.println("Alive");
	delay(1000);
}
