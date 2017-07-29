//Coordinates.h
#ifndef _COORDINATES_H
#define _COORDINATES_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <Angles.h>


class Coordinates : public virtual RoverReset {
public:
	Coordinates();//constructor
	Coordinates(double, double);//constructor: (latitude, longitude)
	~Coordinates();//destructor	
	void setLatitudeDeg(double);//(latitude in degrees)
	void setLongitudeDeg(double);//(longitude in degrees)
	void setPositionDeg(double,double);//(latitude in degrees, longitude in degrees)
	double getLatitudeDeg();//returns latitude in degrees
	double getLongitudeDeg();//returns longitude in degrees
	double getLatitudeRad();//returns latitude in degrees
	double getLongitudeRad();//returns longitude in degrees
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:
	//Non-SW Resettable
	//SW Resettable
	double _latitudeDeg;//in degrees
	double _longitudeDeg;//in degrees
};

#endif 