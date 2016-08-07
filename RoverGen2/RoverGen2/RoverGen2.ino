/*
 Name:		RoverGen2.ino
 Created:	8/6/2016 8:49:24 PM
 Author:	Richard
*/


#include <RoverSensor.h>
#include <PirSensor.h>
#include <RoverPinConfig.h>





void InterruptDispatch1();

//Global Variables
RoverSensor sensor1 = RoverSensor();
PirSensor sensor2 = PirSensor(PIR_PIN, INTRPT_1, &InterruptDispatch1);


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
		
}

// the loop function runs over and over again until power down or reset
void loop() {
	String test;
	
	volatile boolean motionDetected;
	
	delay(1000);//allow enough delay so after it finishes uploading, the terminal window can be opened

	//testing superclass Rover Sensor
	test = sensor1.getName();
	Serial.println(test);
	delay(10);


	//testing specific PIR Sensor with interrupt
	test = sensor2.getName();
	Serial.println(test);
	delay(10);


	//test interrupt
	while (1)
	{
		motionDetected = sensor2.readSensor();
		if (motionDetected)
		{
			Serial.println(motionDetected);
		}
		else
		{
			Serial.println("no motion");
			delay(900);
		}
		delay(100);
	}
}



void InterruptDispatch1() {
	sensor2.isrUpdate();
}