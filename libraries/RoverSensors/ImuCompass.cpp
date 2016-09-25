#include <ImuCompass.h>


ImuCompass::ImuCompass()
{
	this->_compass = new LSM303();
}
ImuCompass::~ImuCompass()
{
	//do nothing
}
bool ImuCompass::init()
{
	Wire.begin();//Begin the Wire (just in case it has not started yet)
	if (this->_compass->init())
	{
		this->_compass->enableDefault();	
		this->_compass->m_min = (LSM303::vector<int16_t>){-32767, -32767, -32767};
		this->_compass->m_max = (LSM303::vector<int16_t>){+32767, +32767, +32767};		
		return true;
	}
	else
	{
		return false;
	}
}
void ImuCompass::reset()
{
		//do nothing
}
void ImuCompass::readSensor()
{
	this->_compass->read();
}
float ImuCompass::getCompassHeading()
{
	return this->_compass->heading();
}

