#include <AnalogLed.h>

#include <Arduino.h>



AnalogLed::AnalogLed(byte ledPin)
{
	this->ledPin = ledPin;
	pinMode(ledPin, OUTPUT);
	analogWrite(ledPin, 0);//initialize off
}

AnalogLed::~AnalogLed()
{
	//do nothing
}

void AnalogLed::ledOn()
{
	ledIsOn = true;
	analogWrite(ledPin, 255);
	
}

void AnalogLed::ledSetLevel(byte level)
{
	if (level > 0)
	{
		ledIsOn = true;
		analogWrite(ledPin, level);
	}
	else
	{
		ledIsOn = false;
		analogWrite(ledPin, level);//byte is already a range from 0 to 255 so no need to check for negatives
	}
	
}
void AnalogLed::ledOff()
{
	ledIsOn = false;
	analogWrite(ledPin, 0);
}
boolean AnalogLed::isLedOn()
{
	return ledIsOn;
}

void AnalogLed::reset()
{
	ledOff();
}
