//PirSensor.h
#ifndef _PIRSENSOR_H
#define _PIRSENSOR_H

	//define Arduino 4: COMM in order to use it's config pins
	#ifndef _ARD_4_COMM_H
		#define _ARD_4_COMM_H
	#endif


	#include <Arduino.h>

	typedef void (*voidFuncPtr)(void);//defining the type voidFuncPtr
	
	class PirSensor {
		public:
			PirSensor(byte, voidFuncPtr );//constructor. (pin, interrupt_service_routine)
			~PirSensor();//destructor
			boolean readSensor();
			void isrUpdate();//updates the motionDetected variable when the interrupt service routine (ISR) is called
		private:
			volatile boolean motionDetected = false;//initialize to no motion detected
	};


#endif 