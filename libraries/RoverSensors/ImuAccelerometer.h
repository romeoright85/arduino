//ImuAccelerometer.h
#ifndef _IMUACCELEROMETER_H
#define _IMUACCELEROMETER_H

	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>
	
	//Accelerometer/Compass Sensor Libraries
	//https://www.pololu.com/product/1268/resources
	#include <Wire.h>
	#include <LSM303.h>
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
	
	class ImuAccelerometer : public virtual RoverReset {
	public:
		ImuAccelerometer();//constructor
		~ImuAccelerometer();//destructor
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		
		int getXValue();
		int getYValue();
		int getZValue();
		
	private:
	
		int getRawXValue();
		int getRawYValue();
		int getRawZValue();		
		
	};

	#endif 