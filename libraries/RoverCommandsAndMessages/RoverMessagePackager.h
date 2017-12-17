//RoverMessagePackager.h
#ifndef _ROVERMESSAGEPACKAGER_H
#define _ROVERMESSAGEPACKAGER_H


#define _CHAR_BUFFER_ARRAY_SIZES

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <DataType.h>
#include <CharArray.h>


#define _ROVERDATA

#include <RoverConfig.h>

class RoverMessagePackager {
public:
	RoverMessagePackager();//constructor
	~RoverMessagePackager();//destructor
	static void packEncoderStatus(byte, int, int, char *, byte &);//(direction, speed, footage/distance, output char array, output char array size) Note: The output char array should be of size _MAX_ROVER_COMMAND_DATA_LEN_. The data per this design will be fixed predetermined lengths, i.e. xyyyzzzz (where x is the direction, y is the speed, and z is the footage/distance in feet.
	//Note: Speed is in inches per second.
	static void unpackEncoderStatus(char *, byte, byte &, int &, int &);//(input char array, input char array size, direction, speed, footage/distance in feet) Note: The input char array should be of size _MAX_ROVER_COMMAND_DATA_LEN_. The data per this design will be fixed predetermined lengths, i.e. xyyyzzzz (where x is the direction, y is the speed, and z is the footage/distance in feet	
private:
	//None
};

#endif 