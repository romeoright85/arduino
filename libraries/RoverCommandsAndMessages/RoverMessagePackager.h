//RoverMessagePackager.h
#ifndef _ROVERMESSAGEPACKAGER_H
#define _ROVERMESSAGEPACKAGER_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>

#include <RoverConfig.h>

class RoverMessagePackager : public virtual RoverReset {
public:
	RoverMessagePackager();//constructor
	~RoverMessagePackager();//destructor
	static void packEncoderStatus(byte, int, int, char *, &byte);//(direction, speed, footage/distance, output char array, output char array size) Note: The output char array should be of size _MAX_ROVER_COMMAND_DATA_LEN_. The data per this design will be fixed predetermined lengths, i.e. xyy.yyyzzz.zzz (where x is the direction, y is the speed, and z is the footage/distance in feet.
	//Note: Speed is in inches per second.
	static void unpackEncoderStatus(char *, byte, &byte, &int, &int);//(input char array, input char array size, direction, speed, footage/distance in feet) Note: The input char array should be of size _MAX_ROVER_COMMAND_DATA_LEN_. The data per this design will be fixed predetermined lengths, i.e. xyy.yyyzzz.zzz (where x is the direction, y is the speed, and z is the footage/distance in feet
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:
	//Non-SW Resettable
	//SW Resettable
};

#endif 