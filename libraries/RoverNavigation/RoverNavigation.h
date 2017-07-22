//RoverNavigation.h
#ifndef _ROVERNAVIGATION_H
#define _ROVERNAVIGATION_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <math.h>

/*

This class takes in a desired waypoint and an actual waypoint from the GPS sensor in the decimal degrees format,
then it calculates the relative bearing and distance
then in generates the motor control signals accordingly


Bearing vs. Heading
Heading is not always the direction an aircraft is moving. That is called 'course'. Heading is the direction the aircraft is pointing. The aircraft may be drifting a little or a lot due to a crosswind. 
Bearing is the angle in degrees (clockwise) between North and the direction to the destination or nav aid. 
Relative bearing is the angle in degrees (clockwise) between the heading of the aircraft and the destination or nav aid.
https://www.google.com/search?q=heading+vs+bearing&oq=heading+vs&aqs=chrome.2.69i57j0l5.3168j0j7&sourceid=chrome&ie=UTF-8
*/


/*
	Haversine Sample Coordinates
	Example:
	Actual Lat/Long in Degrees
	39.268761, -76.606402 (lower right corner of Riverside Park in South Baltimore)
	Desired Lat/Long in Degrees (Hersh's Pizza in South Baltimore)
	39.268603, -76.611702

	RoverNavigation Calculated Result:
	456.7968 m
	Google Maps Calculated Result:
	about 462.27 m

*/



#define _ROVERNAVIGATIONDEFINITIONS
#define _DISTANCE_UNITS_MODES
#define _MOTORCONTROLLER_DEFINITIONS

#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ Serial2
#else
	#define _SERIAL_DEBUG_CHANNEL_ Serial
#endif



/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/
//define Arduino 1: NAVI in order to use it's config pins
#ifndef _ARD_1_NAVI_H
	#define _ARD_1_NAVI_H
#endif

/********************************************************************/

#include <RoverConfig.h>

class RoverNavigation : public virtual RoverReset {
public:
	RoverNavigation();//constructor
	~RoverNavigation();//destructor
	
	void setDesiredLatitudeDeg(double);
	void setDesiredLongitudeDeg(double);
	void setActualLatitudeDeg(double);
	void setActualLongitudeDeg(double);
	
	double getDesiredLatitudeDeg();
	double getDesiredLongitudeDeg();
	double getActualLatitudeDeg();
	double getActualLongitudeDeg();
	
	double calculateDistance( double , double , double , double , byte );//(desired degrees latitude, desired degrees longitude, actual degrees latitude, actual degrees longitude, unit type) returns distance in km or m based on unit type (i.e. UNIT_M or UNIT_KM). See RoverConfig for more details.
	
	
	
	//WRITE ME
	float getRelativeBearing(float, double , double , double , double);//(heading of Rover in degrees i.e. from the IMU, desired degrees latitude, desired degrees longitude, actual degrees latitude, actual degrees longitude), returns relative bearing in degrees
	int getCalculatedMotorThrottle();//returns the ideal rover throttle (since the MotorController will handle the calibrated offset behind the scenes) based on the calculated distance and bearing
		//Throttle: 180 max reverse, 90 stop, 0 max forward
	int getCalculatedMotorSteering();//returns the ideal rover steering (since the MotorController will handle the calibrated offset behind the scenes) based on the calculated distance and bearing
		//Steering: 180 max right, 90 center,  0 max left
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	
	
	
	
	
	
	
private:
	//Non-SW Resettable
	//SW Resettable
	double _desiredLatitudeDeg = 0.0;
	double _desiredLongitudeDeg = 0.0;
	double _actualLatitudeDeg = 0.0;
	double _actualLongitudeDeg = 0.0;	
	
};

#endif 