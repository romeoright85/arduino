#include <RoverData.h>


RoverData::RoverData()
{	
	//do nothing
}
RoverData::~RoverData()
{
	//do nothing
}
void RoverData::setData(char * dataString, byte arraySize)
{		 
	strncpy(this->_dataString, dataString, arraySize);
}
char * RoverData::getData()
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
	this->clearData();
}
void RoverData::clearData()
{		 
	memset(this->_dataString,0,sizeof(this->_dataString));	
}
byte RoverData::getDataLength()
{		 
	return CharArray::stringSize(this->_dataString,sizeof(this->_dataString));	
}