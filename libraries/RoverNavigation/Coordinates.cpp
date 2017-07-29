#include <Coordinates.h>


Coordinates::Coordinates()
{
	this->_latitude = 0.0;
	this->_longitude = 0.0;
}
Coordinates::Coordinates(double latitude, double longitude)
{
	this->setLatitude(latitude);
	this->setLongitude(longitude);
}
Coordinates::~Coordinates()
{
	//do nothing
}
void Coordinates::setLatitude(double latitude)
{
	if( latitude  >= -90 && latitude <= 90 )
	{
		this->_latitude = latitude;
	}
	else
	{
		this->_latitude = 0.0;
	}
	
}
void Coordinates::setLongitude(double longitude)
{
	if( longitude  >= -180 && longitude <= 180 )
	{
		this->_longitude = longitude;
	}
	else
	{
		this->_longitude = 0.0;
	}	
}
void Coordinates::setPosition(double latitude, double longitude)
{
	this->setLatitude(latitude);
	this->setLongitude(longitude);
}
double Coordinates::getLatitude()
{
	return this->_latitude;
}
double Coordinates::getLongitude()
{
	return this->_longitude;
}

void Coordinates::reset()
{
	this->_latitude = 0.0;
	this->_longitude = 0.0;
}

		