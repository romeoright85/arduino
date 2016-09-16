#include <ImuGyro.h>


ImuGyro::ImuGyro()
{
	this->_gyro = new L3G();
}
ImuGyro::~ImuGyro()
{
	//do nothing
}
void ImuGyro::reset()
{
	//do nothing
}

int ImuGyro::getXValue()
{
	//Converting Raw Data to Usable Data
	//WRITE ME LATER//DEBUG
	
	return this->getRawXValue();//DEBUG, write conversion later
}
int ImuGyro::getYValue()
{
	//Converting Raw Data to Usable Data
	//WRITE ME LATER//DEBUG
	
	return this->getRawYValue();
}
int ImuGyro::getZValue()
{
	//Converting Raw Data to Usable Data
	//WRITE ME LATER//DEBUG
	
	return this->getRawZValue();
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