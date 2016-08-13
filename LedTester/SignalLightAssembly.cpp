#include <SignalLightAssembly.h>

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
