#include <UnderglowLeds.h>

UnderglowLeds::UnderglowLeds(byte underglowLedPin)
{
	this->_underGlowLight = new DigitalLed(underglowLedPin);	
	
	//initialize them as off
	this->reset();
}
UnderglowLeds::~UnderglowLeds()
{
	//do nothing
}
void UnderglowLeds::reset()
{
	//software reset
	this->turnOff();
	
}
//overloaded turn on functions
void UnderglowLeds::turnOn()
{

	this->_underGlowLight->ledOn();
}

//overloaded turn off functions
void UnderglowLeds::turnOff()
{
	this->_underGlowLight->ledOff();	
}

boolean UnderglowLeds::isOn()
{
	return this->_underGlowLight->isLedOn();		
}