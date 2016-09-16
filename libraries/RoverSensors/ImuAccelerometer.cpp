#include <ImuAccelerometer.h>


ImuAccelerometer::ImuAccelerometer()
{
}
ImuAccelerometer::~ImuAccelerometer()
{
	//do nothing
}
void ImuAccelerometer::reset()
{
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
	return 111;//DEBUG//WRITE ME LATER
}
int ImuAccelerometer::getRawYValue()
{
	return 222;//DEBUG//WRITE ME LATER
}
int ImuAccelerometer::getRawZValue()
{
	return 333;//DEBUG//WRITE ME LATER
}