//ImuSensor.h



#ifndef _IMUSENSOR_H
#define _IMUSENSOR_H

	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>		
	

	
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

	#define _IMU_DEFINITIONS
	#define _IMU_CALIBRATIONS
	
	#include <RoverCalibration.h>
	#include <RoverConfig.h>
	
	class ImuSensor : public virtual RoverReset {
	public:
		ImuSensor();//constructor
		~ImuSensor();//destructor
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)		
		void init();//initialize the IMU Sensor, must not be done in the global, but either in the setup() or the loop().		
		void readSensor();//reads the IMU Sensor Data. You will still need to get the data.
		float getRoll();	
		float getPitch();
		float getYaw();
		float getHeading();	
		void printForAHRS();//serially prints the output in the format for the AHRS (i.e. "!ANG:0.00,0.00,0.00")
		
		
		
	private:		
	
		
		//SW Resetable			
		float _roll;
		float _pitch;
		float _yaw;
	
			
	};
	
#endif 














