#include <RoverSandbox.h>


//Global Variables

RoverSandbox roverSandbox = RoverSandbox();

RoverReset * resetArray[] = { &roverSandbox };
#include <String.h>
String string1 = "hello";
String string2 = "";

void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	Serial.begin(9600);
}


void loop() {
	string2 = string1;
	Serial.println("String1");
	Serial.println(string1);
	Serial.println("String2");
	Serial.println(string2);
	delay(1000);
}
