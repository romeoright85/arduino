/*
 Name:		SandBoxClassTesterv3.ino
 Created:	1/28/2017 9:54:42 AM
 Author:	Richard
*/
#include <CharArray.h>

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
}

// the loop function runs over and over again until power down or reset
void loop() {
	char OriginalTemp[] = "  #Hello World! ! ";
	char LTrimTemp[] = "  #Hello World! ! ";
	char RTrimTemp[] = "  #Hello World! ! ";
	char TrimTemp[] = "  #Hello World! ! ";
	
	delay(1);
	Serial.println(F("Original"));
	Serial.print(OriginalTemp);
	Serial.println(F("."));

	Serial.println(F("LTrim"));
	CharArray::LTrim(LTrimTemp);
	Serial.print(LTrimTemp);
	Serial.println(F("."));



	Serial.println(F("RTrim"));
	CharArray::RTrim(RTrimTemp);
	Serial.print(RTrimTemp);
	Serial.println(F("."));


	Serial.println(F("Trim"));
	CharArray::Trim(TrimTemp);
	Serial.print(TrimTemp);
	Serial.println(F("."));




	while (1);
}

