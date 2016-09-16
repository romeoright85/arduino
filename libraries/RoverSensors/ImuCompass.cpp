#include <ImuCompass.h>


ImuCompass::ImuCompass()
{
}
ImuCompass::~ImuCompass()
{
	//do nothing
}
void ImuCompass::reset()
{
}
int ImuCompass::getXValue()
{
	//Converting Raw Data to Usable Data
	//WRITE ME LATER//DEBUG
	
	return this->getRawXValue();//DEBUG, write conversion later
}
int ImuCompass::getYValue()
{
	//Converting Raw Data to Usable Data
	//WRITE ME LATER//DEBUG
	
	return this->getRawYValue();
}
int ImuCompass::getZValue()
{
	//Converting Raw Data to Usable Data
	//WRITE ME LATER//DEBUG
	
	return this->getRawZValue();
}


int ImuCompass::getRawXValue()
{
	return 11;//DEBUG//WRITE ME LATER
}
int ImuCompass::getRawYValue()
{
	return 11;//DEBUG//WRITE ME LATER
}
int ImuCompass::getRawZValue()
{
	return 11;//DEBUG//WRITE ME LATER
}