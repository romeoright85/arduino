//DigitalLed.h
#ifndef _DIGITALLED_H
#define _DIGITALLED_H

	#include <Arduino.h>



	class DigitalLed {
	public:
		DigitalLed(byte);//constructor. (LED pin)
		~DigitalLed();//destructor
		void ledOn();//turn led on
		void ledOff();//turn led off
		boolean isLedOn();//returns status of the led
	private:
		boolean ledIsOn;//if it's on, returns true, else off, returns false
		byte ledPin;
	};




#endif 