//BooleanBitFlags.h

//Flag set is a byte that contains 8 flags (bits)
//This class uses one 8-bit byte to hold 8 boolean states to save memory (instead of using eight 8-bit booleans)


#ifndef _BOOLEANBITFLAGS_H
#define _BOOLEANBITFLAGS_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>



class BooleanBitFlags : public virtual RoverReset {
public:
	BooleanBitFlags();//constructor
	~BooleanBitFlags();//destructor
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	static void resetFlag(byte &);//(flag set) resets the flag set
	static void setFlagBit(byte &, byte);//(flag set, bit to set) sets the desired bit in the flag set
	static void clearFlagBit(byte &, byte);//(flag set, bit to clear) clears the desired bit in the flag set
	static boolean flagIsSet(byte &, byte);//(flag set, bit to check if set) returns true is set and false if not.



private:
	//Non-SW Resettable
	//SW Resettable
};

#endif 