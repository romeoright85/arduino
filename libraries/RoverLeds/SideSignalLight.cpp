#include <SideSignalLight.h>

SideSignalLight::SideSignalLight(byte sideSignalLightPin)
{
	this->_sideSignalLight = new DigitalLed(sideSignalLightPin);	
	
	//initialize them as off
	this->reset();
}
SideSignalLight::~SideSignalLight()
{
	//do nothing
}
void SideSignalLight::reset()
{
	//software reset
	this->turnOff();
	
}
//overloaded turn on functions
void SideSignalLight::turnOn()
{

	this->_sideSignalLight->ledOn();
}

//overloaded turn off functions
void SideSignalLight::turnOff()
{
	this->_sideSignalLight->ledOff();	
}

boolean SideSignalLight::isOn()
{
	return this->_sideSignalLight->isLedOn();		
}