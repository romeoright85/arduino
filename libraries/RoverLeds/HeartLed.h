/*
The heart led runs through a table of values to create a breathing effect on the led.
//It uses  a 1-sin(x) modified pattern (has extra 0's and 255's)
Run HeartLed::breathing() to activate the analog led with the breathing pattern.
Run HeartLed::resetHeartLed() to reset the pattern to the beginning of the array.
*/


//HeartLed.h
#ifndef _HEART_LED_H
#define _HEART_LED_H

#include <AnalogLed.h>
#include <DelayCounter.h>

//Created this class so can configure RoverConfig.h

/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/

//define Arduino 1: NAVI in order to use it's config pins
#ifndef _ARD_4_COMM_H
#define _ARD_4_COMM_H
#endif

/********************************************************************/
#include <RoverConfig.h>




class HeartLed : public AnalogLed {
public:
	HeartLed(byte, DelayCounter *, unsigned int, unsigned int);//constructor. (LED pin, DelayCounter pointer, periods for short delay, periods for long delay)
	~HeartLed();//destructor
	void breathing();//have the led step through the breathing effect
	void resetHeartLed();//reset the delay pattern index
private:
	byte baseClassPin;//this parameter is passed to the base class's constructor
	byte ledPatternIndex = 0;//index of the pattern array
	byte ledPatternArray_Breathe[38] = { 0, 0, 1, 6, 12, 22, 34, 49, 65, 84, 105, 128, 151, 176, 202, 228, 255, 255, 255, 255, 228, 202, 176, 151, 128, 105, 84, 65, 49, 34, 22, 12, 6, 1, 0, 0 };//1-sin(x) modified pattern (has extra 0's and 255's)
	DelayCounter * counterPtr;//delay counter pointer
	unsigned int periodsForShortDelay;//holds the number of periods for the short delay
	unsigned int periodsForLongDelay;//holds the number of periods for the long delay
};


#endif 