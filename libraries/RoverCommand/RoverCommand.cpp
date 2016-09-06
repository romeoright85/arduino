#include <RoverCommand.h>

/*
		==Data Format==
		The format is /OcDLL*CCCC... (Note: There could be more than four C's so hence CCCC...)
		The /, c, and * are format identifiers. For commands the headers are as such: /-c---*----
		The O shows the origin where the message came from (Origin ID): 0=CMNC (external), 1=NAVI (internal), 2=AUXI (internal), 3=MAIN (internal), 4=COMM (internal)
		The D shows the destination Arduino it's going to (Destination ID): 0=CMNC (external), 1=NAVI (internal), 2=AUXI (internal), 3=MAIN (internal), 4=COMM (internal)
		The LL shows command priority level it should be in the lookup table
		The C's (four or more) are the letters that designate the command. The length of the letters will be determined by the lookup's priority and destination
		
		
		(where - are don't cares and ... means it can vary in length)
		Any messages for
			CMNC: 
				/-c0--*----.... 
			NAVI:
				/-c1--*----.... 
			AUXI:
				/-c2--*----.... 
			MAIN:
				/-c3--*----.... 				
			COMM:
				/-c4--*----.... 
*/	

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
		dataString.
		//take the dataString and parse it to grab only the rover command
		//no need to check for validity as it's different for every Arduino. So instead check it at the Ardunio's ino
		//this->_roverCommand = "cmd0";//DEBUG
		this->_roverCommand = "invalid";//DEBUG
}
String RoverCommand::getCommand()
{
	return this->_roverCommand;
}