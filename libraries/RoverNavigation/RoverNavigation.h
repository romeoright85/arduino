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
https://sites.google.com/site/wayneholder/self-driving-rc-car/getting-from-point-a-to-point-b
http://www.movable-type.co.uk/scripts/latlong.html
http://diydrones.com/profiles/blogs/the-difference-between-heading
https://aviation.stackexchange.com/questions/8000/what-are-the-differences-between-bearing-vs-course-vs-direction-vs-heading-vs-tr
https://www.sunearthtools.com/tools/distance.php
https://www.youtube.com/watch?v=9nDkR-X9dqo
*/


/*
	Haversine Sample Coordinates
	Example:
	Actual Lat/Long in Degrees
	39.268761, -76.606402 (lower right corner of Riverside Park in South Baltimore)
	Desired Lat/Long in Degrees (Hersh's Pizza in South Baltimore)
	39.268603, -76.611702

	
	Distance
	RoverNavigation Calculated Result:
	456.6073 m
	
	Google Maps Calculated Result:
	about 462.27 m
	
	
	Bearing
	RoverNavigation Calculated Result:
	267.8314 degrees
	
	SunEarthTools Calculated:
	https://www.sunearthtools.com/tools/distance.php
	267.79 degrees
	
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
	void setHeadingDeg(float);
	
	
	
	
	
	
	double getDesiredLatitudeDeg();
	double getDesiredLongitudeDeg();
	double getActualLatitudeDeg();
	double getActualLongitudeDeg();
	
	double getDesiredLatitudeRad();
	double getDesiredLongitudeRad();
	double getActualLatitudeRad();
	double getActualLongitudeRad();	
	
	
	
	double getDistance(byte);//(unit type) takes the object's currently set coordinates and returns distance in km or m based on unit type (i.e. UNIT_M or UNIT_KM). See RoverConfig for more details.
	double calculateDistance(float, float, float, float, byte);///(actual latitude in radians, actual Longitude in radians, desired Latitude in radians, desired Longitude in radians, unit type) returns distance in km or m based on unit type (i.e. UNIT_M or UNIT_KM). See RoverConfig for more details.
	float calculateTrueBearing(float, float, float, float);//(actual latitude in radians, actual Longitude in radians, desired Latitude in radians, desired Longitude in radians) returns the true (magnetic) bearing (destination angle) in degrees based on actual and desired latitude/longitude coordinates
	float getTrueBearing();//takes the object's currently set coordinates and returns the true (magnetic) bearing (destination angle) in degrees based on actual and desired latitude/longitude coordinates
	float calculateRelativeBearing(float, float);//(heading of Rover in degrees: current angle i.e. from IMU, true bearing: destination angle) returns relative bearing in degrees
	
	
	
	
	
	
	
	//WRITE ME
	float getRelativeBearing();//takes the object's currently set heading and true bearing and returns relative bearing in degrees
	int getCalculatedMotorThrottle();//returns the ideal rover throttle (since the MotorController will handle the calibrated offset behind the scenes) based on the calculated distance and bearing
		//Throttle: 180 max reverse, 90 stop, 0 max forward
	int getCalculatedMotorSteering();//takes the object's current relative bearing and returns the ideal rover steering (since the MotorController will handle the calibrated offset behind the scenes) based on the calculated distance and bearing
		//Steering: 180 max right, 90 center,  0 max left
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	
	
	
	
	
	
	
private:
	//Non-SW Resettable
	float normalizeAngleDeg(float);//keeps the degrees angle from 0-359 degrees
	double degToRad(double);//(degrees) returns results in radians
	double radToDeg(double);//(radians) returns results in degrees
	
	
	
	//SW Resettable
	double _desiredLatitudeDeg = 0.0;
	double _desiredLongitudeDeg = 0.0;
	double _actualLatitudeDeg = 0.0;
	double _actualLongitudeDeg = 0.0;	
	
	
	double _desiredLatitudeRad = 0.0;
	double _desiredLongitudeRad = 0.0;
	double _actualLatitudeRad = 0.0;
	double _actualLongitudeRad = 0.0;	
	
	
	float _measuredIMUHeading = 0.0;	
};

#endif 