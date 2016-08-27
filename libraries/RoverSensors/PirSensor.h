//PirSensor.h
#ifndef _PIRSENSOR_H
#define _PIRSENSOR_H


	#include <Arduino.h>
	#include <RoverReset.h>
	
	/*******************************************************************
	Configure (define) flags before calling #include <RoverConfig.h>
	/********************************************************************/
	//define Arduino 4: COMM in order to use it's config pins
	#ifndef _ARD_4_COMM_H
		#define _ARD_4_COMM_H		
	#endif
	
	/********************************************************************/

	#include <RoverConfig.h>
	
	
	typedef void (*voidFuncPtr)(void);//defining the type voidFuncPtr that is a function pointer that takes no arguments and returns void. It is used later on for the interrupt service routine.
	
	class PirSensor: public virtual RoverReset {
		public:
			PirSensor(byte, voidFuncPtr );//constructor. (pin, interrupt_service_routine)
			~PirSensor();//destructor
			boolean monitorMotion();//returns true is motion detected, else returns false
			void isrUpdate();//updates the motionDetected variable when the interrupt service routine (ISR) is called
			virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		private:
			volatile boolean _motionDetected = false;//initialize to no motion detected
	};


#endif 