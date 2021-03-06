//ImuGyro.h
#ifndef _IMUGYRO_H
#define _IMUGYRO_H

	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>
	#include <Wire.h>
	//Gyro Sensor Libraries
	//https://github.com/pololu/l3g-arduino/
	#include <L3G.h>
	#define _IMUDATATYPES //used with RoverConfig.h

	/*******************************************************************
	Configure (define) flags before calling #include <RoverConfig.h>
	/********************************************************************/

	//define Arduino 2: AUXI in order to use it's config pins
	#ifndef _ARD_2_AUXI_H
		#define _ARD_2_AUXI_H
	#endif


	/********************************************************************/

	#include <RoverConfig.h>
	
	class ImuGyro : public virtual RoverReset {
	public:
	
		ImuGyro();//constructor
		~ImuGyro();//destructor
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		void readSensor();//read Gyro sensor
		int getXValue();
		int getYValue();
		int getZValue();
		bool init();//initialize the Gyro Sensor, must not be done in the global, but either in the setup() or the loop(). returns true when successful, else returns false.
	private:
	
		L3G * _gyro;
		int getRawXValue();
		int getRawYValue();
		int getRawZValue();	
		
	};

	#endif 