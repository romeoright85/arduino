//Coordinates.h
#ifndef _COORDINATES_H
#define _COORDINATES_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>

/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/
//define Arduino 1: NAVI in order to use it's config pins
#ifndef _ARD_1_NAVI_H
	#define _ARD_1_NAVI_H
#endif

/********************************************************************/

#include <RoverConfig.h>

class Coordinates : public virtual RoverReset {
public:
	Coordinates();//constructor
	Coordinates(double, double);//constructor: (latitude, longitude)
	~Coordinates();//destructor	
	void setLatitude(double);
	void setLongitude(double);
	void setPosition(double,double);//(latitude, longitude)
	double getLatitude();
	double getLongitude();
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:
	//Non-SW Resettable
	//SW Resettable
	double _latitude;
	double _longitude;
};

#endif 