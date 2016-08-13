//SignalLightAssembly.h
#ifndef _SIGNALLIGHT_ASSEMBLY_H
#define _SIGNALLIGHT_ASSEMBLY_H

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

class SignalLightAssembly {
public:
	SignalLightAssembly(byte, byte, byte, byte);//constructor. (signal led pins: front right, front left, side right, and side left)
	~SignalLightAssembly();//destructor
	//Note: For any LED assemblies, don't add blink options/patterns as it may hold up the main program flow as you're using delays. Instead only have parallel or singular off/on patterns.
	void allOn();//turns on all signal lights
	void allOff();//turns off all signal lights
	void rightOn();//turns on front and side right signal lights
	void rightOff();//turns off front and side right signal lights
	void leftOn();//turns on front and side left signal lights
	void leftOff();//turns off front and side left signal lights
	void frontRightOn();//turns on front right signal light
	void frontLeftOn();//turns on front left signal light
	void sideRightOn();//turns on side right signal light
	void sideLeftOn();//turns on side left signal light
	void frontRightOff();//turns off front right signal light
	void frontLeftOff();//turns off front left signal light
	void sideRightOff();//turns off side right signal light
	void sideLeftOff();//turns off side left signal light



	boolean isRightFogOn();//returns status of the right fog led
	boolean isLeftFogOn();//returns status of the left fog led	
private:
	//have to declare them here in order to have "access of"/"scope to" these objects in all the methods of the class
	//use a pointer since they will not be created yet until the constructor of this class is called
	DigitalLed* rightFogLight;
	DigitalLed* leftFogLight;
};


#endif 