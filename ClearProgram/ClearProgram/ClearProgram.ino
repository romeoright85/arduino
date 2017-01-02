/*
Used for any Arduino:
AUXI - 2
NAVI - 1
COMM - 4
MAIN - 3


To be used to delete/overwrite/clear out any current program on the Arduino.
Helps with debugging so one Arduino doesn't do anything strange in the background while you're testing other code.
*/



#include <RoverConfig.h>

void setup() {
	Serial.begin(PC_USB_BAUD_RATE);
	delay(1000);
	Serial.println("Cleared Program");
	//Do Nothing Else
}

void loop() {
	//Do Nothing
}
