#include <ImuAccelerometer.h>


ImuAccelerometer::ImuAccelerometer()
{
		this->_accelerometer = new LSM303();
}
ImuAccelerometer::~ImuAccelerometer()
{
	//do nothing
}
void ImuAccelerometer::reset()
{
	//do nothing
}
bool ImuAccelerometer::init()
{
	Wire.begin();//Begin the Wire (just in case it has not started yet)
	if (this->_accelerometer->init())
	{
		this->_accelerometer->enableDefault();		
		return true;
	}
	else
	{
		return false;
	}	
}
void ImuAccelerometer::readSensor()
{
	this->_accelerometer->read();
}
int ImuAccelerometer::getXValue()
{
	//Converting Raw Data to Usable Data
	//WRITE ME LATER//DEBUG
	
	return this->getRawXValue();//DEBUG, write conversion later
}
int ImuAccelerometer::getYValue()
{
	//Converting Raw Data to Usable Data
	//WRITE ME LATER//DEBUG
	
	return this->getRawYValue();
}
int ImuAccelerometer::getZValue()
{
	//Converting Raw Data to Usable Data
	//WRITE ME LATER//DEBUG
	
	return this->getRawZValue();
}

int ImuAccelerometer::getRawXValue()
{
	return this->_accelerometer->a.x;
}
int ImuAccelerometer::getRawYValue()
{
	return this->_accelerometer->a.y;
}
int ImuAccelerometer::getRawZValue()
{
	return this->_accelerometer->a.z;
}