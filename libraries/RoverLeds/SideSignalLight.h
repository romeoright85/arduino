//SideSignalLight.h
#ifndef _SIDESIGNALLIGHT_H
#define _SIDESIGNALLIGHT_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <DigitalLed.h>

/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/

//define Arduino 1: NAVI in order to use it's config pins
#ifndef _ARD_1_NAVI_H
#define _ARD_1_NAVI_H
#endif

/********************************************************************/
#include <RoverConfig.h>




class SideSignalLight: public virtual RoverReset {
	public:
		SideSignalLight(byte);//constructor. (signal light pin)
		~SideSignalLight();//destructor
		//Note: For any LED assemblies, don't add blink options/patterns as it may hold up the main program flow as you're using delays. Instead only have parallel or singular off/on patterns.
		void turnOn();
		void turnOff();
		//returns status of that led
		boolean isOn();
		virtual void reset();//turns off all leds, software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	private:
		//have to declare them here in order to have "access of"/"scope to" these objects in all the methods of the class
		//use a pointer since they will not be created yet until the constructor of this class is called
		DigitalLed* _sideSignalLight;		
};


#endif 

