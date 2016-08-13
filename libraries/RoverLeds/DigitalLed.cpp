#include <DigitalLed.h>

#include <Arduino.h>



DigitalLed::DigitalLed(byte ledPin)
{
	this->ledPin = ledPin;
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);//initialize off
}

DigitalLed::~DigitalLed()
{
	//do nothing
}


void DigitalLed::ledOn()
{
	this->ledIsOn = true;
	digitalWrite(ledPin, HIGH);
}
void DigitalLed::ledOff()
{
	this->ledIsOn = false;
	digitalWrite(ledPin, LOW);
}
boolean DigitalLed::isLedOn()
{
	return this->ledIsOn;
}

