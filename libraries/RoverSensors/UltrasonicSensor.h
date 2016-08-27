//UltrasonicSensor.h
#ifndef _ULTRASONICSENSOR_H
#define _ULTRASONICSENSOR_H
	
	#include <Arduino.h>
	#include <DistanceSensor.h>
	#include <RoverReset.h>
	
	/*******************************************************************
	Configure (define) flags before calling #include <RoverConfig.h>
	/********************************************************************/

	//define Arduino 1: NAVI in order to use it's config pins
	#ifndef _ARD_1_NAVI_H
		#define _ARD_1_NAVI_H
	#endif

	/********************************************************************/
	#include <RoverConfig.h>




	//Used to set ultrasonic timeout
	#define USON_TIMEOUT 30000		




	class UltrasonicSensor : public DistanceSensor, public virtual RoverReset {
		public:
			UltrasonicSensor(byte, byte);//constructor. (trigger pin, echo pin)
			~UltrasonicSensor();//destructor
			int getDistance(byte);//returns distance (mode: UNIT_CM, UNIT_M, UNIT_FT, UNIT_IN). Also see RoverConfig.h
			virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		private:
			byte triggerPin;
			byte echoPin;
	};




#endif 