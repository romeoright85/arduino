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


//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast



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
	Serial.begin(PC_USB_BAUD_RATE);
	Serial1.begin(COMM_BAUD_RATE);	
}


void loop() {

	delay(1000);
#ifdef _DEBUG_COMM_BROADCAST
	Serial1.println(F("Running..."));
#else
	Serial.println(F("Running..."));
#endif
	delay(4000);
#ifdef _DEBUG_COMM_BROADCAST
	Serial1.println(F("Resetting COMM..."));
#else
	Serial.println(F("Resetting COMM..."));
#endif	
	commHwResetter->performHwReset();	
	delay(1000);
#ifdef _DEBUG_COMM_BROADCAST
	Serial1.println(F("Reset Complete!"));
#else
	Serial.println(F("Reset Complete!"));
#endif

}
