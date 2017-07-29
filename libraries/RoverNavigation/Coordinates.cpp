#include <Coordinates.h>


Coordinates::Coordinates()
{
	this->_latitudeDeg = 0.0;
	this->_longitudeDeg = 0.0;
}
Coordinates::Coordinates(double latitudeDeg, double longitudeDeg)
{
	this->setLatitudeDeg(latitudeDeg);
	this->setLongitudeDeg(longitudeDeg);
}
Coordinates::~Coordinates()
{
	//do nothing
}
void Coordinates::setLatitudeDeg(double latitudeDeg)
{
	if( latitudeDeg  >= -90 && latitudeDeg <= 90 )
	{
		this->_latitudeDeg = latitudeDeg;
	}
	else
	{
		this->_latitudeDeg = 0.0;
	}
	
}
void Coordinates::setLongitudeDeg(double longitudeDeg)
{
	if( longitudeDeg  >= -180 && longitudeDeg <= 180 )
	{
		this->_longitudeDeg = longitudeDeg;
	}
	else
	{
		this->_longitudeDeg = 0.0;
	}	
}
void Coordinates::setPositionDeg(double latitudeDeg, double longitudeDeg)
{
	this->setLatitudeDeg(latitudeDeg);
	this->setLongitudeDeg(longitudeDeg);
}
double Coordinates::getLatitudeDeg()
{
	return this->_latitudeDeg;
}
double Coordinates::getLongitudeDeg()
{
	return this->_longitudeDeg;
}
double Coordinates::getLatitudeRad()
{
	return Angles::degToRad(this->_latitudeDeg);	
}
double Coordinates::getLongitudeRad()
{
	return Angles::degToRad(this->_longitudeDeg);
}	
void Coordinates::reset()
{
	this->_latitudeDeg = 0.0;
	this->_longitudeDeg = 0.0;
}

		