#include <UnderglowLeds.h>

#include <Arduino.h>


UnderglowLeds::UnderglowLeds(byte ledPin) : DigitalLed(_baseClassPin)
{
	_baseClassPin = ledPin;
}

UnderglowLeds::~UnderglowLeds()
{
	//do nothing
}

void UnderglowLeds::reset()
{
	//software reset
	DigitalLed::reset();
}

