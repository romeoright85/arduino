#include <PirSensor.h>

PirSensor::PirSensor(byte pin, voidFuncPtr interruptDispatch )
{
	pinMode(pin, INPUT);
	byte interruptChannel = digitalPinToInterrupt(pin); //calling an arduino function
	attachInterrupt(interruptChannel, interruptDispatch, RISING); //calling an arduino function, attachInterrupt()
}

PirSensor::~PirSensor()
{
	//do nothing
}

boolean PirSensor::monitorMotion()
{
	return this->_motionDetected;
}

void PirSensor::isrUpdate()//this will be called by an interruptDispatch
{
	this->_motionDetected = true;
}
void PirSensor::reset()
{
	//software reset
	this->_motionDetected = false;//initialize to no motion detected
}


