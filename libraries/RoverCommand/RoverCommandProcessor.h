//RoverCommandProcessor.h
#ifndef _ROVERCOMMANDPROCESSOR_H
#define _ROVERCOMMANDPROCESSOR_H

#define _ROVERCOMM_DEFINITIONS
#include <RoverCommandDefs.h>
#include <RoverConfig.h>
#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <DataType.h>
#include <CharArray.h>

#define _COMMAND_CREATION_DEFINITIONS
#include <RoverCommandDefs.h>

/*


Reference: Also see the spreadsheet "Command Creator..." at K:\Working Directory\DESIGN_PROJ\Design Projects\Robot\My Notes


		==Rover Data Format==
		The format is /OcDLL*tttdddd... (Note: The d's can range from none to up to _MAX_ROVER_COMMAND_DATA_LEN_ - 1, i.e. 15-1=14. Minus 1 due to null character. So hence dddd....)
		The /, c, and * are format identifiers. For commands the headers are as such: /-c---*----
		The O shows the origin where the message came from (Origin ID): See definitions below.
		The D shows the destination Arduino it's going to (Destination ID): See definitions below.
		Definitions:
			0=NONE, 1=CMNC (external), 2=NAVI (internal), 3=AUXI (internal), 4=MAIN (internal), 5=COMM (internal)
		The LL shows command priority level it should be in the lookup table
		The ttt are the rover command tag to represent which command it is.
		The d's (none to _MAX_ROVER_COMMAND_DATA_LEN_ - 1, i.e. 15-1 = 14. Minus 1 due to null character.) are the letters that designate the command data, if any.
		
		
		(where - are don't cares and ... means it can vary in length)
		Any messages for
			CMNC: 
				/-c1--*----.... 
			NAVI:
				/-c2--*----.... 
			AUXI:
				/-c3--*----.... 
			MAIN:
				/-c4--*----.... 				
			COMM:
				/-c5--*----.... 
				
				
	Example:
		/3c101*002HelloMAINtoCMNC
		
*/	

class RoverCommandProcessor : public virtual RoverReset {
public:
	RoverCommandProcessor();//constructor
	~RoverCommandProcessor();//destructor
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	
	//Note: origin and destination variables are defined in _ROVERCOMM_DEFINITIONS, see RoverConfig.h
	
	
	static char * createCmd(byte, byte, byte, char *);//(origin, destination, priority level, command - if a tag used then it must be appended manually)	
	static char * createCmd(byte, byte, byte, byte, char *);//(origin, destination, priority level, command tag, command)
	static char * byteToCharArrayWithLeadingZeros(byte);//(input byte) returns char array, with a range of 0 to 255 (with leading zeros)
	
	
	
	static byte parseCmd(char *, byte, char *);//(input RoverCommand, array size, output-command data char array) Returns the commandTag.
	
	
private:
	//Non-SW Resettable
	//SW Resettable
};

#endif 