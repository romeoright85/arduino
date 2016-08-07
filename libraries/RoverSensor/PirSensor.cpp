#include <PirSensor.h>

PirSensor::PirSensor(byte pin, byte interruptChannel, voidFuncPtr interruptDispatch)
{
	pinMode(pin, INPUT);
	attachInterrupt(interruptChannel, interruptDispatch, RISING);
}

PirSensor::~PirSensor()
{
	//do nothing
}

boolean PirSensor::readSensor()
{
	return motionDetected;
}

void PirSensor::isrUpdate()//this will be called by interruptDispatch
{
  motionDetected = true;
}