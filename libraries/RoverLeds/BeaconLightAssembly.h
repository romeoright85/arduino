//BeaconLightAssembly.h
#ifndef _BEACONLIGHTASSEMBLY_H
#define _BEACONLIGHTASSEMBLY_H


#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <DigitalLed.h>

#define _BEACON_LIGHT_TYPES
	
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
	//Note: Beacon light types are defined by _BEACON_LIGHT_TYPES in RoverConfig.h
	//overloaded on functions 	
	void turnOn(byte);//(beacon light type x1)
	void turnOn(byte, byte);//(beacon light type x2)
	void turnOn(byte, byte, byte);//(beacon light type x3)
	void turnOn(byte, byte, byte, byte);//(beacon light type x4)
	void turnOn(byte, byte, byte, byte, byte);//(beacon light type x5)
	void turnOn(byte, byte, byte, byte, byte, byte);//(beacon light type x6)
	void turnOn(byte, byte, byte, byte, byte, byte, byte);//(beacon light type x7)
	void turnOn(byte, byte, byte, byte, byte, byte, byte, byte);//(beacon light type x8)
	//overloaded off functions
	void turnOff(byte);//(beacon light type x1)
	void turnOff(byte, byte);//(beacon light type x2)
	void turnOff(byte, byte, byte);//(beacon light type x3)
	void turnOff(byte, byte, byte, byte);//(beacon light type x4)
	void turnOff(byte, byte, byte, byte, byte);//(beacon light type x5)
	void turnOff(byte, byte, byte, byte, byte, byte);//(beacon light type x6)
	void turnOff(byte, byte, byte, byte, byte, byte, byte);//(beacon light type x7)
	void turnOff(byte, byte, byte, byte, byte, byte, byte, byte);//(beacon light type x8)
	//returns status of that led
	boolean isOn(byte);
			
	virtual void reset();//turns off all leds, software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	
	
private:
	//Non-SW Resettable
		
	//SW Resettable
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

};

#endif 