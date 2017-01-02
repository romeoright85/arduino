//Used for MAIN - 3


//Note: Since all the Arduinos use this class, you have to define them in each of its .ino as there are shared naming conventions and will cause a conflict otherwise.


/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/

//define Arduino 3: MAIN in order to use it's config pins
#ifndef _ARD_3_MAIN_H
#define _ARD_3_MAIN_H		
#endif

/********************************************************************/


#include <RoverConfig.h>


#include <RoverHwReset.h>


//Global Variables

RoverHwReset * commHwResetter = new RoverHwReset(COMM_HW_RESET_CTRL_PIN);

RoverReset * resetArray[] = {
	commHwResetter
};


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	Serial.begin(9600);
}


void loop() {

	delay(1000);
	Serial.println(F("Running..."));
	delay(4000);
	Serial.println(F("Resetting COMM..."));
	commHwResetter->performHwReset();	
	delay(1000);
	Serial.println(F("Reset Complete!"));
}
