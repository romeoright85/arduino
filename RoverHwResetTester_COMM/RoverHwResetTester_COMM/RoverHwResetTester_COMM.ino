//Used for COMM - 4

#include <RoverHwReset.h>



//Note: Since all the Arduinos use this class, you have to define them in each of its .ino as there are shared naming conventions and will cause a conflict otherwise.


/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/

//define Arduino 4: COMM in order to use it's config pins
#ifndef _ARD_4_COMM_H
#define _ARD_4_COMM_H		
#endif



/********************************************************************/


#include <RoverConfig.h>


//Global Variables

RoverHwReset * naviHwResetter = new RoverHwReset(NAVI_HW_RESET_CTRL_PIN);
RoverHwReset * auxiHwResetter = new RoverHwReset(AUXI_HW_RESET_CTRL_PIN);
RoverHwReset * mainHwResetter = new RoverHwReset(MAIN_HW_RESET_CTRL_PIN);


RoverReset * resetArray[] = {
	naviHwResetter,
	auxiHwResetter,
	mainHwResetter
};


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
}


void loop() {

	delay(1000);
	_PC_USB_SERIAL_.println(F("Running..."));
	delay(7000);
	_PC_USB_SERIAL_.println(F("Resetting NAVI..."));
	naviHwResetter->performHwReset();
	_PC_USB_SERIAL_.println(F("Resetting AUXI..."));
	auxiHwResetter->performHwReset();
	_PC_USB_SERIAL_.println(F("Resetting MAIN..."));
	mainHwResetter->performHwReset();
	delay(1000);
	_PC_USB_SERIAL_.println(F("Reset Complete!"));
}
