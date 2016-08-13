#include <FoglightAssembly.h>

#include <Arduino.h>



FoglightAssembly::FoglightAssembly(byte rightLedPin, byte leftLedPin)
{
	this->rightFogLight = new DigitalLed(rightLedPin);
	this->leftFogLight = new DigitalLed(leftLedPin);
	//initialize them as off
	rightFogLight->ledOff();
	leftFogLight->ledOff();
}
FoglightAssembly::~FoglightAssembly()
{
	//do nothing
}
void FoglightAssembly::allOn()
{
	rightFogLight->ledOn();
	leftFogLight->ledOn();
}
void FoglightAssembly::allOff()
{
	rightFogLight->ledOff();
	leftFogLight->ledOff();
}
void FoglightAssembly::leftOn()
{
	leftFogLight->ledOn();
}
void FoglightAssembly::leftOff()
{
	leftFogLight->ledOff();
}
void FoglightAssembly::rightOn()
{
	rightFogLight->ledOn();
}
void FoglightAssembly::rightOff()
{
	rightFogLight->ledOff();
}
boolean FoglightAssembly::isRightFogOn()
{
	return rightFogLight->isLedOn();
}
boolean FoglightAssembly::isLeftFogOn()
{
	return leftFogLight->isLedOn();
}



void FoglightAssembly::turnOn(byte foglightType)
{	
	if (RIGHT_FOG)
	{
		rightFogLight->ledOn();
	}
	else if(LEFT_FOG)
	{
		leftFogLight->ledOn();
	}
	else
	{
		//do nothing. invalid value.
	}
}
void FoglightAssembly::turnOn(byte foglightType1, byte foglightType2)
{
	
	byte fogLightTypes[2] = { foglightType1, foglightType2 };
	for (byte i = 0; i <= 1; i++)
	{
		this->turnOn(fogLightTypes[i]);//using delegation. Passing the fog light type (i.e. LEFT_FOG or RIGHT_FOG)
	}
	
}
void FoglightAssembly::turnOff(byte foglightType)
{
	if (RIGHT_FOG)
	{
		rightFogLight->ledOff();
	}
	else if (LEFT_FOG)
	{
		leftFogLight->ledOff();
	}
	else
	{
		//do nothing. invalid value.
	}
}
void FoglightAssembly::turnOff(byte foglightType1, byte foglightType2)
{
	byte fogLightTypes[2] = { foglightType1, foglightType2 };
	for (byte i = 0; i <= 1; i++)
	{
		this->turnOff(fogLightTypes[i]);//using delegation. Passing the foglight type (i.e. LEFT_FOG or RIGHT_FOG)
	}

}