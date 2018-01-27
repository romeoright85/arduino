//HeadLightAssembly.h
#ifndef _HEADLIGHTASSEMBLY_H
#define _HEADLIGHTASSEMBLY_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <DigitalLed.h>

#define _HEADLIGHT_TYPES

/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/
//define Arduino 1: NAVI in order to use it's config pins
#ifndef _ARD_1_NAVI_H
	#define _ARD_1_NAVI_H
#endif

/********************************************************************/

#include <RoverConfig.h>

class HeadLightAssembly : public virtual RoverReset {
public:
	HeadLightAssembly(byte, byte, byte);//constructor. (headlight pins: high beam, signal, fog)
	~HeadLightAssembly();//destructor
	
	//Note: For any LED assemblies, don't add blink options/patterns as it may hold up the main program flow as you're using delays. Instead only have parallel or singular off/on patterns.
	//Note: Headlight types are defined by _HEADLIGHT_TYPES in RoverConfig.h
	//overloaded on functions
	void turnOn(byte);//(headlight type x1)
	void turnOn(byte, byte);//(headlight type x2)
	void turnOn(byte, byte, byte);//(headlight type x3)

	//overloaded off functions
	void turnOff(byte);//(headlight type x1)
	void turnOff(byte, byte);//(headlight type x2)
	void turnOff(byte, byte, byte);//(headlight type x3)

	//returns status of that led
	boolean isOn(byte);
		
	virtual void reset();//turns off all leds, software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:
	//Non-SW Resettable

		
	//SW Resettable
	//have to declare them here in order to have "access of"/"scope to" these objects in all the methods of the class
	//use a pointer since they will not be created yet until the constructor of this class is called
	DigitalLed* _highBeam;
	DigitalLed* _signal;
	DigitalLed* _fog;
};

#endif 











