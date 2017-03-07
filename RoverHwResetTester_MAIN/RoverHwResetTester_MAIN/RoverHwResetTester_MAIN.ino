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
#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ Serial1
#else
	#define _SERIAL_DEBUG_CHANNEL_ Serial
#endif



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
	_SERIAL_DEBUG_CHANNEL_.println(F("Running..."));
	delay(4000);
	_SERIAL_DEBUG_CHANNEL_.println(F("Resetting COMM..."));
	commHwResetter->performHwReset();	
	delay(1000);
	_SERIAL_DEBUG_CHANNEL_.println(F("Reset Complete!"));

}
