#include <Sandbox.h>


Sandbox::Sandbox()
{
	//Latitude: 3916.10N
	//Longitude : 7636.66W
	strncpy(this->_lat, "3916.10", strlen("3916.10")+1);	
	strncpy(this->_latUnit, "N", strlen("N")+1);	
	strncpy(this->_lon, "7636.66", strlen("7636.66")+1);	
	strncpy(this->_lonUnit, "W", strlen("W")+1);
	
	
	this->_gpsFields[0] = this->_lat;
	this->_gpsFields[1] = this->_latUnit;
	this->_gpsFields[2] = this->_lon;
	this->_gpsFields[3] = this->_lonUnit;
	
}
Sandbox::~Sandbox()
{
	//do nothing
}
void Sandbox::reset()
{
}
void Sandbox::write(char * charArray, byte charArraySize)
{
	
	strncpy(this->_data, charArray,  charArraySize);
	//Serial.println(this->_data);//DEBUG
}
char * Sandbox::read()
{
	
	return this->_data;
}
char * Sandbox::getLat()
{
	return this->_gpsFields[0];
}
char * Sandbox::getLatUnit()
{
	return this->_gpsFields[1];
}
char * Sandbox::getLon()
{
	return this->_gpsFields[2];
}
char * Sandbox::getLonUnit()
{
	return this->_gpsFields[3];
}