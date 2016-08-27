#include <AnalogLed.h>

#include <Arduino.h>



AnalogLed::AnalogLed(byte ledPin)
{
	this->_ledPin = ledPin;
	pinMode(this->_ledPin, OUTPUT);
	analogWrite(this->_ledPin, 0);//initialize off
}

AnalogLed::~AnalogLed()
{
	//do nothing
}

void AnalogLed::ledOn()
{
	this->_ledIsOn = true;
	analogWrite(this->_ledPin, 255);
	
}

void AnalogLed::ledSetLevel(byte level)
{
	if (level > 0)
	{
		this->_ledIsOn = true;
		analogWrite(this->_ledPin, level);
	}
	else
	{
		this->_ledIsOn = false;
		analogWrite(this->_ledPin, level);//byte is already a range from 0 to 255 so no need to check for negatives
	}
	
}
void AnalogLed::ledOff()
{
	this->_ledIsOn = false;
	analogWrite(this->_ledPin, 0);
}
boolean AnalogLed::isLedOn()
{
	return this->_ledIsOn;
}

void AnalogLed::reset()
{
	ledOff();
}
