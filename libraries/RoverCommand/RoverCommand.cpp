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
		_roverCommand = "";
}

void RoverCommand::parseCommand(String dataString)
{
		//take the dataString and parse it to grab only the rover command
		//The command is everything after the * in /-c---*----..., where - are don't cares and ... means the length may vary
		//no need to check for validity as it's different for every Arduino. So instead check it at the Ardunio's .ino
		this->_roverCommand = dataString.substring(7);//grab everything after yhe 7th character	
}
String RoverCommand::getCommand()
{
	return this->_roverCommand;
}