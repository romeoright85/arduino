#include <string.h>
#include <RoverConfig.h>


void setup() {

	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);

}


void loop() {


	//debug
	String tempString = "10";
	int tempInt = (tempString).toInt();
	_PC_USB_SERIAL_.println(tempInt);

	tempString = "A";
	byte charBufferSize = (tempString).length() + 1;
	char charArray[charBufferSize];
	(tempString).toCharArray(charArray, charBufferSize);
	_PC_USB_SERIAL_.println(charArray[0]);

	tempString = "3.14";
	double tempDouble = (tempString).toFloat();
	_PC_USB_SERIAL_.println(tempDouble);

	tempString = "255";
	byte tempByte = (tempString).toInt();
	_PC_USB_SERIAL_.println(tempByte);

	tempString = "256";//test a byte overflow case
	tempByte = (tempString).toInt();
	_PC_USB_SERIAL_.println(tempByte);

	_PC_USB_SERIAL_.println();//Blank line separator
	delay(1000);

}
