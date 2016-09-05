#include <RoverCommand.h>


RoverCommand::RoverCommand()
{
}
RoverCommand::~RoverCommand()
{
	//do nothing
}
void RoverCommand::reset()
{
		_roverCommand = "";
}

void RoverCommand::parseCommand(String dataString)
{
		//WRITE ME LATER
		//take the dataString and parse it to grab only the rover command
		//no need to check for validity as it's different for every Arduino. So instead check it at the Ardunio's ino
		this->_roverCommand = "cmd0";//DEBUG
}
String RoverCommand::getCommand()
{
	return this->_roverCommand;
}