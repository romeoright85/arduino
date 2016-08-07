//PirSensor.h
#ifndef _PIRSENSOR_H
#define _PIRSENSOR_H

#include <Arduino.h>
#include <RoverSensor.h>


typedef void (*voidFuncPtr)(void);//defining the type voidFuncPtr


		class PirSensor : public RoverSensor {
		public:
			PirSensor(byte, byte, voidFuncPtr );//constructor. (pin, interrupt, interrupt_service_routine)
			~PirSensor();//destructor
			boolean readSensor();
			void isrUpdate();//updates the motionDetected variable when the interrupt service routine (ISR) is called
		private:
			volatile boolean motionDetected = false;//initialize to no motion detected
		};


#endif 