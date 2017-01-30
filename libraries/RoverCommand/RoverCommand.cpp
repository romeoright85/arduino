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
}
void RoverCommand::parseCommand(char * dataString, byte arraySize)
{
	//take the dataString and parse it to grab only the rover command
	//The command is everything after the * in /-c---*----..., where - are don't cares and ... means the length may vary
	//no need to check for validity as it's different for every Arduino. So instead check it at the Ardunio's .ino
	CharArray::substring(dataString, arraySize, 7, this->_roverCommand);//grab everything after the 7th character	
}
char * RoverCommand::getCommand()
{
	return this->_roverCommand;
}
byte RoverCommand::getCommandLength()
{
	return CharArray::stringSize(this->_roverCommand,sizeof(this->_roverCommand));
}
void RoverCommand::clearCommand()
{
	memset(this->_roverCommand,0,sizeof(this->_roverCommand));	
}
