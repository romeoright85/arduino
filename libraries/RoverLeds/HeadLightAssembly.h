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
	//overloaded on functions
	void turnOn(byte);
	void turnOn(byte, byte);
	void turnOn(byte, byte, byte);

	//overloaded off functions
	void turnOff(byte);
	void turnOff(byte, byte);
	void turnOff(byte, byte, byte);

	//returns status of that led
	boolean isOn(byte);
		
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:
	//Non-SW Resettable
	//have to declare them here in order to have "access of"/"scope to" these objects in all the methods of the class
	//use a pointer since they will not be created yet until the constructor of this class is called
	DigitalLed* _highBeam;
	DigitalLed* _signal;
	DigitalLed* _fog;
		
	//SW Resettable
};

#endif 











