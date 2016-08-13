#include <UnderglowLeds.h>

#include <Arduino.h>


UnderglowLeds::UnderglowLeds(byte ledPin) : DigitalLed(baseClassPin)
{
	baseClassPin = ledPin;
}

UnderglowLeds::~UnderglowLeds()
{
	//do nothing
}

