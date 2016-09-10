//DistanceSensor.h
#ifndef _DISTANCESENSOR_H
#define _DISTANCESENSOR_H

	#include <Arduino.h>
	#include <RoverDebug.h>	
	#include <RoverReset.h>
	
	/*******************************************************************
	Configure (define) flags before calling #include <RoverConfig.h>
	/********************************************************************/
	//define modes for distance
	#ifndef _DISTANCE_UNITS_MODES
		#define _DISTANCE_UNITS_MODES
	#endif
	/********************************************************************/

	#include <RoverConfig.h>


	//this is an abstract class. It contains pure virtual function(s)
	class DistanceSensor : public virtual RoverReset {
	public:
		DistanceSensor();//constructor
		~DistanceSensor();//destructor
		virtual int getDistance(byte) = 0;//pure virtual function, returns distance (mode: UNIT_CM, UNIT_M, UNIT_FT, UNIT_IN). Also see RoverConfig.h
		virtual void reset() = 0;//pure virtual function, software resets everything
	protected:
		int _distance;
	};







#endif 