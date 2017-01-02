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
	Serial.begin(PC_USB_BAUD_RATE);
}


void loop() {
	Serial.println("Alive");
	delay(1000);
}
