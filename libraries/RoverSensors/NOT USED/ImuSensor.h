//ImuSensor.h
#ifndef _IMUSENSOR_H
#define _IMUSENSOR_H

	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>
	#include <Wire.h>
	#include <ImuGyro.h>
	#include <ImuCompass.h>
	#include <ImuAccelerometer.h>
	#define _IMUDATATYPES //used with RoverConfig.h
	
	//MinIMU-9 v2
	//Reference: https://www.pololu.com/product/1268/resources
	
	/*******************************************************************
	Configure (define) flags before calling #include <RoverConfig.h>
	/********************************************************************/

	//define Arduino 2: AUXI in order to use it's config pins
	#ifndef _ARD_2_AUXI_H
		#define _ARD_2_AUXI_H
	#endif

	/********************************************************************/

	#include <RoverConfig.h>
	
	class ImuSensor : public virtual RoverReset {
	public:
		ImuSensor();//constructor
		~ImuSensor();//destructor
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		
		void readSensor();//reads the IMU Sensor Data. You will still need to get the data.
		bool init();//initialize the IMU Sensor, must not be done in the global, but either in the setup() or the loop(). returns true when successful, else returns false.
		void getGyroXYZData(int []);//the 1x3 int array of gyro values (x,y,z) is passed by reference and the values are altered by the function
		void getAccelerometerXYZData(int []);//the 1x3 int array of accelerometer values (x,y,z) is passed by reference and the values are altered by the function
		float getCompassHeading();// returns the angular difference in the horizontal plane between a default vector and north, in degrees.
		
	private:
		ImuGyro * _imuGyro;
		ImuAccelerometer * _imuAccelerometer;
		ImuCompass * _imuCompass;
		
		//holds pointers to the IMU Sensors
		RoverReset * _resetArray[3];
		
		//SW Resetable
		//Holds the compass heading in degrees
		float _compassHeading;
		//Arrays to hold x,y,z values of corresponding data
		int _gyroXYZData[3];
		int _accelerometerXYZData[3];
			
	};
	
#endif 