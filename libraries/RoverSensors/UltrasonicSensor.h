//UltrasonicSensor.h
#ifndef _ULTRASONICSENSOR_H
#define _ULTRASONICSENSOR_H
	
	#include <Arduino.h>
	#include <RoverDebug.h>		
	#include <DistanceSensor.h>
	#include <RoverReset.h>
	
	
	//uncomment of one the test cases below to simulate the ultrasonic read values
	//#define _DEBUG_TEST_CASE_1
	//#define _DEBUG_TEST_CASE_2
	//#define _DEBUG_TEST_CASE_3
	//#define _DEBUG_TEST_CASE_4
	
	
	/*******************************************************************
	Configure (define) flags before calling #include <RoverConfig.h>
	/********************************************************************/

	//define Arduino 1: NAVI in order to use it's config pins
	#ifndef _ARD_1_NAVI_H
		#define _ARD_1_NAVI_H
	#endif

	/********************************************************************/
	
	#define _ULTRASONIC_SENSOR_DEFINITIONS
	
	#include <RoverConfig.h>








	class UltrasonicSensor : public DistanceSensor, public virtual RoverReset {
		public:
			UltrasonicSensor(byte, byte);//constructor. (trigger pin, echo pin)
			~UltrasonicSensor();//destructor
			int getDistance(byte);//reads the sensor a designated amount of times and returns the average distance (mode: UNIT_CM, UNIT_M, UNIT_FT, UNIT_IN). Also see RoverConfig.h
			virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		private:
			int readSensor();//reads the pulse width of the sensor returns the raw value used for averaging
			byte _triggerPin;
			byte _echoPin;
	};




#endif 