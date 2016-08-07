/*
 Name:		RoverGen2.ino
 Created:	8/6/2016 8:49:24 PM
 Author:	Richard
*/


#include <RoverSensor.h>

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
		
}

// the loop function runs over and over again until power down or reset
void loop() {
	String test;
	RoverSensor sensor1;
	RoverSensor sensor2;
	delay(1000);//allow enough delay so after it finishes uploading, the terminal window can be opened

	test = sensor1.getName();
	Serial.println(test);
	delay(10);

	test = sensor2.getName();
	Serial.println(test);
	delay(10);
	
	while (1);
}
