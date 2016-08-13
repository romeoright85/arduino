//UltrasonicSensor.h
#ifndef _ULTRASONICSENSOR_H
#define _ULTRASONICSENSOR_H
	
	#include <Arduino.h>
	#include <DistanceSensor.h>

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




	class UltrasonicSensor : public DistanceSensor {
		public:
			UltrasonicSensor(byte, byte);//constructor. (trigger pin, echo pin)
			~UltrasonicSensor();//destructor
			int getDistance(byte);//returns distance (mode: UNIT_CM, UNIT_M, UNIT_FT, UNIT_IN). Also see RoverConfig.h
		private:
			byte triggerPin;
			byte echoPin;
	};




#endif 