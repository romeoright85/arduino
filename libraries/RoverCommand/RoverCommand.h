//RoverCommand.h
#ifndef _ROVERCOMMAND_H
#define _ROVERCOMMAND_H

	#include <Arduino.h>
	#include <RoverReset.h>
	#include <String.h>
	
	class RoverCommand : public virtual RoverReset {
	public:
		RoverCommand();//constructor
		~RoverCommand();//destructor
		void parseCommand(String);//parse the rover command and store it interally to this object in _roverCommand
		String getCommand();//retrieved the parsed rover command, _roverCommand
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	private:
		String _roverCommand = "";
	};

#endif 