//SignalLightAssembly.h
#ifndef _SIGNALLIGHT_ASSEMBLY_H
#define _SIGNALLIGHT_ASSEMBLY_H

#include <DigitalLed.h>

//Signal light types
#define FRONT_RIGHT_SIGNAL_PIN 0
#define FRONT_LEFT_SIGNAL_PIN 1
#define SIDE_RIGHT_SIGNAL_PIN 2
#define SIDE_LEFT_SIGNAL_PIN 3


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
		SignalLightAssembly(byte, byte, byte, byte);//constructor. (signal light pins: front right, front left, side right, side left)
		~SignalLightAssembly();//destructor
		//Note: For any LED assemblies, don't add blink options/patterns as it may hold up the main program flow as you're using delays. Instead only have parallel or singular off/on patterns.
		//overloaded on functions
		void turnOn(byte);
		void turnOn(byte, byte);
		void turnOn(byte, byte, byte);
		void turnOn(byte, byte, byte, byte);
		//overloaded off functions
		void turnOff(byte);
		void turnOff(byte, byte);
		void turnOff(byte, byte, byte);
		void turnOff(byte, byte, byte, byte);
		//returns status of that led
		boolean isOn(byte);
	private:
		//have to declare them here in order to have "access of"/"scope to" these objects in all the methods of the class
		//use a pointer since they will not be created yet until the constructor of this class is called
		DigitalLed* frontRightSignal;
		DigitalLed* frontLeftSignal;
		DigitalLed* sideRightSignal;
		DigitalLed* sideLeftSignal;
};


#endif 

