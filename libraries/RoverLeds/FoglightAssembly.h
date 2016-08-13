//FoglightAssembly.h
#ifndef _FOGLIGHT_ASSEMBLY_H
#define _FOGLIGHT_ASSEMBLY_H

#include <DigitalLed.h>

//Foglight types
#define LEFT_FOG 0
#define RIGHT_FOG 1

/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/

//define Arduino 1: NAVI in order to use it's config pins
#ifndef _ARD_1_NAVI_H
#define _ARD_1_NAVI_H
#endif

/********************************************************************/
#include <RoverConfig.h>

class FoglightAssembly {
public:
	FoglightAssembly(byte, byte);//constructor. (right fog led pin, left fog led pin)
	~FoglightAssembly();//destructor
	//Note: For any LED assemblies, don't add blink options/patterns as it may hold up the main program flow as you're using delays. Instead only have parallel or singular off/on patterns.
	void allOn();//turns on both fog lights
	void allOff();//turns off both fog lights
	void rightOn();//turns on right fog light
	void rightOff();//turns off right fog light
	void leftOn();//turns on left fog light
	void leftOff();//turns off left fog light

	//overloaded functions
	void turnOn(byte);
	void turnOn(byte, byte);
	void turnOff(byte);
	void turnOff(byte, byte);


	boolean isRightFogOn();//returns status of the right fog led
	boolean isLeftFogOn();//returns status of the left fog led	
private:
	//have to declare them here in order to have "access of"/"scope to" these objects in all the methods of the class
	//use a pointer since they will not be created yet until the constructor of this class is called
	DigitalLed* rightFogLight;
	DigitalLed* leftFogLight;
};


#endif 