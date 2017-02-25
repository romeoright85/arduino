//PowerOnResetState.h
#ifndef _POWERONRESETSTATE_H
#define _POWERONRESETSTATE_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <RoverState.h>


#include <RoverConfig.h>

class PowerOnResetState : public virtual RoverReset, public virtual RoverState {
public:
	//Don't make a constructor since treating this like a Java Interface (which means it can't be instantiated, only derived)
	// virtual destructor is required if the object may be deleted through a pointer to RoverReset
	virtual ~PowerOnResetState();//destructor
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	virtual void process();
	virtual RoverState * nextState(RoverState *[]);
private:
	//Non-SW Resettable
	//SW Resettable
};

#endif 