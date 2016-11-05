//RoverAdc.h
#ifndef _ROVERADC_H
#define _ROVERADC_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <RoverConfig.h>

//Reference:
//https://hackingmajenkoblog.wordpress.com/2016/02/01/making-accurate-adc-readings-on-the-arduino/

class RoverAdc : public virtual RoverReset {
public:
	RoverAdc();//constructor
	~RoverAdc();//destructor
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	unsigned int rawADCRead(byte);//reads raw analog to digital voltage only (analog channel pin)
	long readVcc();//reads the value of Vcc against the 1.1V reference and outputs the corrected Vcc value
	double voltageRead(byte);//does an accurate reading of the analog to digital converter by first measuring Vcc then using it in the calucations with the standard analog read (instead of assuming Vcc is 5V)
private:
	//Non-SW Resettable
	//SW Resettable
};

#endif 