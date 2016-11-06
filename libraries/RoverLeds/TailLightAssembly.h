//TailLightAssembly.h
#ifndef _TAILIGHTASSEMBLY_H
#define _TAILIGHTASSEMBLY_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <DigitalLed.h>

#define _TAILLIGHT_TYPES

/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/
//define Arduino 1: NAVI in order to use it's config pins
#ifndef _ARD_1_NAVI_H
	#define _ARD_1_NAVI_H
#endif	

/********************************************************************/

#include <RoverConfig.h>

class TailLightAssembly : public virtual RoverReset {
public:
	TailLightAssembly(byte, byte, byte, byte, byte, byte);//constructor (redLed1Pin, redLed2Pin, redLed3Pin, redLed4Pin, redLed5Pin, whiteLedPin)
	~TailLightAssembly();//destructor
	
	//Note: For any LED assemblies, don't add blink options/patterns as it may hold up the main program flow as you're using delays. Instead only have parallel or singular off/on patterns.
	//overloaded on functions
	void turnOn(byte);
	void turnOn(byte, byte);
	void turnOn(byte, byte, byte);
	void turnOn(byte, byte, byte, byte);
	void turnOn(byte, byte, byte, byte, byte);
	void turnOn(byte, byte, byte, byte, byte, byte);

	//overloaded off functions
	void turnOff(byte);
	void turnOff(byte, byte);
	void turnOff(byte, byte, byte);
	void turnOff(byte, byte, byte, byte);
	void turnOff(byte, byte, byte, byte, byte);
	void turnOff(byte, byte, byte, byte, byte, byte);
	//returns status of that led
	boolean isOn(byte);
	
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:
	//Non-SW Resettable
	DigitalLed* _redLed1;
	DigitalLed* _redLed2;
	DigitalLed* _redLed3;
	DigitalLed* _redLed4;
	DigitalLed* _redLed5;
	DigitalLed* _whiteLed;

	//SW Resettable


};

#endif 