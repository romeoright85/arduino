//RoverCommand.h


/*
		
		Note: RoverComm, RoverData, and RoverCommand classes are used together.
		
		==IMU AHRS Data Format==
		!ANG:Y.XX,Y.XX,Y.XX
			Where Y can be 1 or more digits.
		i.e.
		
		!ANG:0.27,1.56,16.47
		!ANG:0.24,1.57,16.46
		!ANG:0.26,1.56,16.46
		!ANG:0.38,1.61,16.47
		!ANG:0.38,1.63,16.46
		!ANG:0.42,1.63,16.47
		!ANG:0.45,1.61,16.47
		!ANG:0.41,1.61,16.47



		==Rover Data Format==
		The format is /OcDLL*CCCC... (Note: There could be more than four C's so hence CCCC...)
		The /, c, and * are format identifiers. For commands the headers are as such: /-c---*----
		The O shows the origin where the message came from (Origin ID): See definitions below.
		The D shows the destination Arduino it's going to (Destination ID): See definitions below.
		Definitions:
			0=NONE, 1=CMNC (external), 2=NAVI (internal), 3=AUXI (internal), 4=MAIN (internal), 5=COMM (internal)
		The LL shows command priority level it should be in the lookup table
		The C's (four or more) are the letters that designate the command. The length of the letters will be determined by the lookup's priority and destination
		
		
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
		/3c101*HelloMAINtoCMNC
		
*/	



#ifndef _ROVERCOMMAND_H
#define _ROVERCOMMAND_H
#define _ROVERDATA

	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>
	#include <CharArray.h>
	#include <RoverConfig.h>
	
	
	
	class RoverCommand : public virtual RoverReset {
	public:
		RoverCommand();//constructor
		~RoverCommand();//destructor
		void parseCommand(char * dataString, byte);//(charArray, array size) parse the rover command and store it interally to this object in _roverCommand
		char * getCommand();//retrieved the parsed rover command, _roverCommand
		byte getCommandLength();//returns the length of the corresponding string
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		void clearCommand();//clear the string in _roverCommand
	private:
		char _roverCommand[ROVER_DATA_BUFFER_SIZE];
	};

#endif 