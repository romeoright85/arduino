//PirSensor.h
#ifndef _PIRSENSOR_H
#define _PIRSENSOR_H


	#include <Arduino.h>

	/*******************************************************************
	Configure (define) flags before calling #include <RoverConfig.h>
	/********************************************************************/
		//define Arduino 4: COMM in order to use it's config pins
		#ifndef _ARD_4_COMM_H
			#define _ARD_4_COMM_H		
		#endif

	/********************************************************************/	

	#include <RoverConfig.h>	

	
	
	typedef void (*voidFuncPtr)(void);//defining the type voidFuncPtr
	
	class PirSensor {
		public:
			PirSensor(byte, voidFuncPtr );//constructor. (pin, interrupt_service_routine)
			~PirSensor();//destructor
			boolean readSensor();//returns true is motion detected, else returns false
			void isrUpdate();//updates the motionDetected variable when the interrupt service routine (ISR) is called
		private:
			volatile boolean motionDetected = false;//initialize to no motion detected
	};


#endif 