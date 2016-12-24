#include <RoverData.h>


RoverData::RoverData()
{	
	//do nothing
}
RoverData::~RoverData()
{
	//do nothing
}
void RoverData::setData(String dataString)
{	
	this->_dataString = dataString;
}
String RoverData::getData()
{	
	return this->_dataString;
}
byte RoverData::getCommType()
{	
	return this->_roverCommType;
}

void RoverData::setCommType(byte roverCommType)
{	
	this->_roverCommType = roverCommType;
}
void RoverData::reset()
{	
	this->_roverCommType = ROVERCOMM_NONE;
	this->_dataString = "";
}
void RoverData::clearData()
{	
	this->_dataString = "";	
}