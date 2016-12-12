#include <string.h>

void setup() {

	Serial.begin(9600);

}


void loop() {


	//debug
	String tempString = "10";
	int tempInt = (tempString).toInt();
	Serial.println(tempInt);

	tempString = "A";
	byte charBufferSize = (tempString).length() + 1;
	char charArray[charBufferSize];
	(tempString).toCharArray(charArray, charBufferSize);
	Serial.println(charArray[0]);

	tempString = "3.14";
	double tempDouble = (tempString).toFloat();
	Serial.println(tempDouble);

	tempString = "255";
	byte tempByte = (tempString).toInt();
	Serial.println(tempByte);

	tempString = "256";//test a byte overflow case
	tempByte = (tempString).toInt();
	Serial.println(tempByte);

	Serial.println();//Blank line separator
	delay(1000);

}
