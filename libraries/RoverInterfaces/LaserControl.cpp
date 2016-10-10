#include <LaserControl.h>


LaserControl::LaserControl(byte laserControlPin)
{
	//Assign pins
	this->_laserControlPin = laserControlPin;
	
	
	//Setup pins
	pinMode(this->_laserControlPin, OUTPUT);

	//Initialize
	this->reset();
	
	
}
LaserControl::~LaserControl()
{
	//do nothing
}
void LaserControl::reset()
{
	this->laserEnable(LASER_OFF);
}

void LaserControl::laserEnable(byte selection)
{
	
	if(selection==LASER_ON)
	{
		digitalWrite(this->_laserControlPin, HIGH);
		this->_isLaserOn = true;
	}
	else//selection==LASER_OFF
	{
		digitalWrite(this->_laserControlPin, LOW);
		this->_isLaserOn = false;
	}
}
boolean LaserControl::isLaserOn()
{
	return this->_isLaserOn;
}

