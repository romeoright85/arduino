//BeaconLightAssembly.h
#ifndef _BEACONLIGHTASSEMBLY_H
#define _BEACONLIGHTASSEMBLY_H


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

class BeaconLightAssembly : public virtual RoverReset {
public:
	BeaconLightAssembly(byte, byte, byte, byte, byte, byte, byte, byte);//constructor (led pins: front left ir beacon, back left ir beacon, back right ir beacon, front right ir beacon, left blue beacon, back blue beacon, right blue beacon, front blue beacon)
	~BeaconLightAssembly();//destructor
	
	//Note: For any LED assemblies, don't add blink options/patterns as it may hold up the main program flow as you're using delays. Instead only have parallel or singular off/on patterns.
	//overloaded on functions
	void turnOn(byte);
	void turnOn(byte, byte);
	void turnOn(byte, byte, byte);
	void turnOn(byte, byte, byte, byte);
	void turnOn(byte, byte, byte, byte, byte);
	void turnOn(byte, byte, byte, byte, byte, byte);
	void turnOn(byte, byte, byte, byte, byte, byte, byte);
	void turnOn(byte, byte, byte, byte, byte, byte, byte, byte);
	//overloaded off functions
	void turnOff(byte);
	void turnOff(byte, byte);
	void turnOff(byte, byte, byte);
	void turnOff(byte, byte, byte, byte);
	void turnOff(byte, byte, byte, byte, byte);
	void turnOff(byte, byte, byte, byte, byte, byte);
	void turnOff(byte, byte, byte, byte, byte, byte, byte);
	void turnOff(byte, byte, byte, byte, byte, byte, byte, byte);
	//returns status of that led
	boolean isOn(byte);
			
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)		
	
	
private:
	//Non-SW Resettable
	
	//have to declare them here in order to have "access of"/"scope to" these objects in all the methods of the class
	//use a pointer since they will not be created yet until the constructor of this class is called
	
	//IR Beacon LEDs
	DigitalLed* _frontLeftBeaconIR;
	DigitalLed* _backLeftBeaconIR;
	DigitalLed* _backRightBeaconIR;
	DigitalLed* _frontRightBeaconIR;
	
	//Blue Beacon LEDs
	DigitalLed* _leftBeaconBlue;
	DigitalLed* _backBeaconBlue;
	DigitalLed* _rightBeaconBlue;
	DigitalLed* _frontBeaconBlue;
	
	//SW Resettable
};

#endif 