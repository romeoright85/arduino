//RoverVcc.h
#ifndef _ROVERVCC_H
#define _ROVERVCC_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>


//Reference:
//For Megas And Unos (per my own tests):
//http://provideyourown.com/2012/secret-arduino-voltmeter-measure-battery-voltage/
//Also reference the code below, but it only works for Unos. (Per my own tests)
//https://hackingmajenkoblog.wordpress.com/2016/02/01/making-accurate-adc-readings-on-the-arduino/
//https://web.archive.org/web/20150218055034/http://code.google.com/p/tinkerit/wiki/SecretVoltmeter


class RoverVcc : public virtual RoverReset {
public:
	RoverVcc();//constructor
	~RoverVcc();//destructor
	virtual void reset();//do nothing	
	long readVcc();//reads the value of Vcc for Megas in millivolts
private:
	//Non-SW Resettable
	//SW Resettable
};

#endif 