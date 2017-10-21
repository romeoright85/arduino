#include <RoverData.h>


RoverData::RoverData()
{	
	//do nothing
}
RoverData::~RoverData()
{
	//do nothing
}
void RoverData::reset()
{
	this->clearOriginCommType();
	this->clearDestinationCommType();
	this->clearCommandData();
	this->clearCommandTag();		
}//end of reset()
void RoverData::setOriginCommType(byte roverCommType)
{
	this->_roverOriginCommType = roverCommType;
}//end of setOriginCommType()
byte RoverData::getOriginCommType()
{
	return this->_roverOriginCommType;
}//end of getOriginCommType()
void RoverData::clearOriginCommType()
{
	this->setOriginCommType(ROVERCOMM_NONE);
}//end of clearOriginCommType()
void RoverData::setDestinationCommType(byte roverCommType)
{
	this->_roverDestinationCommType = roverCommType;	
}//end of setDestinationCommType()
byte RoverData::getDestinationCommType()
{
	return this->_roverDestinationCommType;
}//end of getDestinationCommType()
void RoverData::clearDestinationCommType()
{
	this->setDestinationCommType(ROVERCOMM_NONE);
}//end of clearDestinationCommType()
void RoverData::setCommandData(char * commandData, byte arraySize)
{
	strncpy(this->_commandData, commandData, arraySize);
}//end of setCommandData()
char * RoverData::getCommandData()
{
	return this->_commandData;
}//end of getCommandData()
byte RoverData::getCommandDataLength()
{
	return CharArray::stringSize(this->_commandData,sizeof(this->_commandData));	
}//end of getCommandDataLength()
void RoverData::clearCommandData()
{
	memset(this->_commandData,0,sizeof(this->_commandData));	
}//end of clearCommandData()
void RoverData::setCommandTag(byte commandTag)
{
	this->_commandTag = commandTag;
}//end of setCommandTag()
byte RoverData::getCommandTag()
{
	return this->_commandTag;
}//end of getCommandTag()
void RoverData::clearCommandTag()
{
	this->setCommandTag(CMD_TAG_NO_MSG);
}//end of clearCommandTag()
void RoverData::setIMUData(char * imuDataString, byte arraySize)
{
	strncpy(this->_imuDataString, imuDataString, arraySize);
}//end of setIMUData()
void RoverData::clearIMUData()
{
	memset(this->_imuDataString,0,sizeof(this->_imuDataString));	
}//end of clearIMUData()
char * RoverData::getIMUData()
{
	return this->_imuDataString;
}//end of getIMUData()
byte RoverData::getIMUDataLength()
{
	return CharArray::stringSize(this->_imuDataString,sizeof(this->_imuDataString));	
}//end of getIMUDataLength()