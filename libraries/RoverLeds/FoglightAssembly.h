//FoglightAssembly.h
#ifndef _FOGLIGHT_ASSEMBLY_H
#define _FOGLIGHT_ASSEMBLY_H

#include <DigitalLed.h>
#include <RoverReset.h>

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

class FoglightAssembly : public virtual RoverReset {
	public:
		FoglightAssembly(byte, byte);//constructor. (right fog led pin, left fog led pin)
		~FoglightAssembly();//destructor
		//Note: For any LED assemblies, don't add blink options/patterns as it may hold up the main program flow as you're using delays. Instead only have parallel or singular off/on patterns.
		//overloaded on functions
		void turnOn(byte);
		void turnOn(byte, byte);
		//overloaded off functions
		void turnOff(byte);
		void turnOff(byte, byte);
		//returns status of that led
		boolean isOn(byte);
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	private:
		//have to declare them here in order to have "access of"/"scope to" these objects in all the methods of the class
		//use a pointer since they will not be created yet until the constructor of this class is called
		DigitalLed* _rightFogLight;
		DigitalLed* _leftFogLight;
};


#endif 