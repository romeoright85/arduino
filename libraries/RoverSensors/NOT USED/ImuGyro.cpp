#include <ImuGyro.h>

ImuGyro::ImuGyro()
{
	this->_gyro = new L3G();	
}
ImuGyro::~ImuGyro()
{
	//do nothing
}
bool ImuGyro::init()
{
	Wire.begin();//Begin the Wire (just in case it has not started yet)
	if (this->_gyro->init())
	{
		this->_gyro->enableDefault();		
		return true;
	}
	else
	{
		return false;
	}	
}
void ImuGyro::reset()
{
	//do nothing
}
void ImuGyro::readSensor()
{
	this->_gyro->read();
}
int ImuGyro::getXValue()
{
	//Converting Raw Data to Usable Data
	//WRITE ME LATER//DEBUG
	
	return this->getRawXValue();//DEBUG
}
int ImuGyro::getYValue()
{
	//Converting Raw Data to Usable Data
	//WRITE ME LATER//DEBUG
	
	return this->getRawYValue();//DEBUG
}
int ImuGyro::getZValue()
{
	//Converting Raw Data to Usable Data
	//WRITE ME LATER//DEBUG
	
	return this->getRawZValue();//DEBUG
}


int ImuGyro::getRawXValue()
{
	return (int)this->_gyro->g.x;
}
int ImuGyro::getRawYValue()
{
	return (int)this->_gyro->g.y;
}
int ImuGyro::getRawZValue()
{
	return (int)this->_gyro->g.z;
}