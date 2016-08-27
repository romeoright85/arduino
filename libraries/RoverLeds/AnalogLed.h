//AnalogLed.h
#ifndef _ANALOGLED_H
#define _ANALOGLED_H

#include <Arduino.h>
#include <RoverReset.h>

//You will need to create a class to configure RoverConfig.h to use the defined constant for the pin

class AnalogLed : public virtual RoverReset {
public:
	AnalogLed(byte);//constructor. (LED pin)
	~AnalogLed();//destructor
	void ledOn();//turn led full on
	void ledSetLevel(byte);//turn on (or off) led to the level passed (0-255)
	void ledOff();//turn led off
	boolean isLedOn();//returns status of the led (true for any level on and false of off)
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:
	boolean ledIsOn;//if it's on, returns true, else off, returns false
	byte ledPin;
};




#endif 