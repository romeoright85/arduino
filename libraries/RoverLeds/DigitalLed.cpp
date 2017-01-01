#include <DigitalLed.h>

#include <Arduino.h>



DigitalLed::DigitalLed(byte ledPin)
{
	this->_ledPin = ledPin;
	pinMode(this->_ledPin, OUTPUT);
	digitalWrite(this->_ledPin, LOW);//initialize off
}

DigitalLed::~DigitalLed()
{
	//do nothing
}


void DigitalLed::ledOn()
{
	this->_ledIsOn = true;
	digitalWrite(this->_ledPin, HIGH);
}
void DigitalLed::ledOff()
{
	this->_ledIsOn = false;
	digitalWrite(this->_ledPin, LOW);
}
boolean DigitalLed::isLedOn()
{
	return this->_ledIsOn;
}
void DigitalLed::reset()
{
	//software reset
	this->ledOff();//turn led off	
}


