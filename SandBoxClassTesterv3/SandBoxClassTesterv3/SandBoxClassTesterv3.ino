/*
 Name:		SandBoxClassTesterv3.ino
 Created:	1/28/2017 9:54:42 AM
 Author:	Richard
*/
#include <CharArray.h>
#include <RoverConfig.h>



// the setup function runs once when you press reset or power the board
void setup() {
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
}

// the loop function runs over and over again until power down or reset
void loop() {
	char OriginalTemp[] = "  #Hello World! ! ";
	char LTrimTemp[] = "  #Hello World! ! ";
	char RTrimTemp[] = "  #Hello World! ! ";
	char TrimTemp[] = "  #Hello World! ! ";
	
	delay(1);
	_PC_USB_SERIAL_.println(F("Original"));
	_PC_USB_SERIAL_.print(OriginalTemp);
	_PC_USB_SERIAL_.println(F("."));

	_PC_USB_SERIAL_.println(F("LTrim"));
	CharArray::LTrim(LTrimTemp);
	_PC_USB_SERIAL_.print(LTrimTemp);
	_PC_USB_SERIAL_.println(F("."));



	_PC_USB_SERIAL_.println(F("RTrim"));
	CharArray::RTrim(RTrimTemp);
	_PC_USB_SERIAL_.print(RTrimTemp);
	_PC_USB_SERIAL_.println(F("."));


	_PC_USB_SERIAL_.println(F("Trim"));
	CharArray::Trim(TrimTemp);
	_PC_USB_SERIAL_.print(TrimTemp);
	_PC_USB_SERIAL_.println(F("."));




	while (1);
}

