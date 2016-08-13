//UnderglowLed.h
#ifndef _UNDERGLOW_LEDS_H
#define _UNDERGLOW_LEDS_H

#include <DigitalLed.h>

//Created this class so can configure RoverConfig.h

/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/

//define Arduino 1: NAVI in order to use it's config pins
#ifndef _ARD_1_NAVI_H
#define _ARD_1_NAVI_H
#endif

/********************************************************************/
#include <RoverConfig.h>




class UnderglowLeds : public DigitalLed {
	public:
		UnderglowLeds(byte);//constructor. (LED pin)
		~UnderglowLeds();//destructor
	private:
		byte baseClassPin;//this parameter is passed to the base class's constructor
};


#endif 