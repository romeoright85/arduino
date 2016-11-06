//RoverVcc.h
#ifndef _ROVERVCC_H
#define _ROVERVCC_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>


//Reference:
//https://hackingmajenkoblog.wordpress.com/2016/02/01/making-accurate-adc-readings-on-the-arduino/

class RoverVcc : public virtual RoverReset {
public:
	RoverVcc();//constructor
	~RoverVcc();//destructor
	virtual void reset();//do nothing
	long readVcc();//reads the value of Vcc against the 1.1V reference and outputs the corrected Vcc value
private:
	//Non-SW Resettable
	//SW Resettable
};

#endif 