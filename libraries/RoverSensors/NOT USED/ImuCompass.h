//ImuCompass.h
#ifndef _IMUCOMASS_H
#define _IMUCOMASS_H

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


	 /*
	  When given no arguments, the heading() function returns the angular
	  difference in the horizontal plane between a default vector and
	  north, in degrees.
	  
	  The default vector is chosen by the library to point along the
	  surface of the PCB, in the direction of the top of the text on the
	  silkscreen. This is the +X axis on the Pololu LSM303D carrier and
	  the -Y axis on the Pololu LSM303DLHC, LSM303DLM, and LSM303DLH
	  carriers.
	  
	  To use a different vector as a reference, use the version of heading()
	  that takes a vector argument; for example, use
	  
		compass.heading((LSM303::vector<int>){0, 0, 1});
	  
	  to use the +Z axis as a reference.
	*/
	

	/********************************************************************/

	#include <RoverConfig.h>
	
	class ImuCompass : public virtual RoverReset {
	public:
		ImuCompass();//constructor
		~ImuCompass();//destructor
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		void readSensor();//read Compass sensor
		bool init();
		float getCompassHeading();// returns the angular difference in the horizontal plane between a default vector and north, in degrees.
	private:
		LSM303 * _compass;	
	};

	#endif 