#include <PirSensor.h>

PirSensor::PirSensor(byte pin, voidFuncPtr interruptDispatch )
{
	pinMode(pin, INPUT);
	byte interruptChannel = digitalPinToInterrupt(pin); //calling an arduino function
	attachInterrupt(interruptChannel, interruptDispatch, RISING); //calling an arduino function
}

PirSensor::~PirSensor()
{
	//do nothing
}

boolean PirSensor::readSensor()
{
	return this->motionDetected;
}

void PirSensor::isrUpdate()//this will be called by interruptDispatch
{
	this->motionDetected = true;
}