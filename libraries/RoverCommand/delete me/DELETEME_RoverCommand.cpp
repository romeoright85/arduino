#include <RoverCommand.h>



RoverCommand::RoverCommand()
{
	//do nothing
}
RoverCommand::~RoverCommand()
{
	//do nothing
}
void RoverCommand::reset()
{
	this->clearCommand();
	this->clearMsgOrigin();
	this->clearMsgDestination();
}//end of reset()
void RoverCommand::parseRxdMessage(char * dataString, byte arraySize)
{
	//take the dataString and parse it to grab the message origin, message destination, and the rover command (which contains the command tag and command data)
	//The format is /OcDLL*tttdddd... (Note: The d's can range from none to up to _MAX_ROVER_COMMAND_DATA_LEN_ - 1, i.e. 15-1=14. Minus 1 due to null character. So hence dddd....)
	//The command is everything after the * in /-c---*----..., where - are don't cares and ... means the length may vary
	//no need to check for validity as it's different for every Arduino. So instead check it at the Ardunio's .ino
	
	//Extract the Message Origin
	this->_roverMessageOrigin = DataType::charToByte(dataString[1]);
	//Extract the Message Destination
	this->_roverMessageDestination = DataType::charToByte(dataString[3]);
	//Extract the Rover Command
	CharArray::substring(dataString, arraySize, 7, this->_roverCommand);//grab everything starting with the 7th character	
}//end of parseRxdMessage()
char * RoverCommand::getCommand()
{
	return this->_roverCommand;
}//end of getCommand()
byte RoverCommand::getCommandLength()
{
	return CharArray::stringSize(this->_roverCommand,sizeof(this->_roverCommand));
}//end of getCommandLength()
byte RoverCommand::getMsgOrigin()
{
	return this->_roverMessageOrigin;
}//end of getMsgOrigin()
byte RoverCommand::getMsgDestination()
{
	return this->_roverMessageDestination;
}//end of getMsgDestination()
void RoverCommand::clearCommand()
{
	memset(this->_roverCommand,0,sizeof(this->_roverCommand));	
}
void RoverCommand::clearMsgOrigin()
{
	this->_roverMessageOrigin = ROVERCOMM_NONE;//set it to default 0
}//end of clearMsgOrigin()
void RoverCommand::clearMsgDestination()
{
	this->_roverMessageOrigin = ROVERCOMM_NONE;//set it to default 0
}//end of clearMsgDestination()		