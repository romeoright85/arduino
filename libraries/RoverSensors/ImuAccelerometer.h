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
	
		
	/*
	The sensor outputs provided by the library are the raw 16-bit values
	obtained by concatenating the 8-bit high and low accelerometer and
	magnetometer data registers. They can be converted to units of g and
	gauss using the conversion factors specified in the datasheet for your
	particular device and full scale setting (gain).

	Example: An LSM303D gives a magnetometer X axis reading of 1982 with
	its default full scale setting of +/- 4 gauss. The M_GN specification
	in the LSM303D datasheet (page 10) states a conversion factor of 0.160
	mgauss/LSB (least significant bit) at this FS setting, so the raw
	reading of -1982 corresponds to 1982 * 0.160 = 317.1 mgauss =
	0.3171 gauss.

	In the LSM303DLHC, LSM303DLM, and LSM303DLH, the acceleration data
	registers actually contain a left-aligned 12-bit number, so the lowest
	4 bits are always 0, and the values should be shifted right by 4 bits
	(divided by 16) to be consistent with the conversion factors specified
	in the datasheets.

	Example: An LSM303DLH gives an accelerometer Z axis reading of -16144
	with its default full scale setting of +/- 2 g. Dropping the lowest 4
	bits gives a 12-bit raw value of -1009. The LA_So specification in the
	LSM303DLH datasheet (page 11) states a conversion factor of 1 mg/digit
	at this FS setting, so the value of -1009 corresponds to -1009 * 1 =
	1009 mg = 1.009 g.
	*/


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
		void readSensor();//read Accelerometer sensor
		int getXValue();
		int getYValue();
		int getZValue();
		bool init();//initialize the Accelerometer Sensor, must not be done in the global, but either in the setup() or the loop(). returns true when successful, else returns false.
	private:
		LSM303 * _accelerometer;	
		int getRawXValue();
		int getRawYValue();
		int getRawZValue();		
		
	};

	#endif 