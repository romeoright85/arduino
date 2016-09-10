//DigitalLed.h
#ifndef _DIGITALLED_H
#define _DIGITALLED_H

	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>

//You will need to create a class to configure RoverConfig.h to use the defined constant for the pin

	class DigitalLed : public virtual RoverReset {
	public:
		DigitalLed(byte);//constructor. (LED pin)
		~DigitalLed();//destructor
		void ledOn();//turn led on
		void ledOff();//turn led off
		boolean isLedOn();//returns status of the led
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	private:
		boolean _ledIsOn;//if it's on, returns true, else off, returns false
		byte _ledPin;
	};




#endif 