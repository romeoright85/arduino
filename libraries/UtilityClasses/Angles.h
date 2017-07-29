//Angles.h
#ifndef _ANGLES_H
#define _ANGLES_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#define _ANGLEDEFINITIONS

class Angles : public virtual RoverReset {
public:
	Angles();//constructor
	~Angles();//destructor
	static float normalizeAngleDeg(float);//keeps the degrees angle from 0-359 degrees
	static double degToRad(double);//(degrees) returns results in radians
	static double radToDeg(double);//(radians) returns results in degrees
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:
	//Non-SW Resettable
	//SW Resettable
};

#endif 