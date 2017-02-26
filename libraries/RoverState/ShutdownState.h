//ShutdownState.h
#ifndef _SHUTDOWNSTATE_H
#define _SHUTDOWNSTATE_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <RoverState.h>


#include <RoverConfig.h>

class ShutdownState : public virtual RoverReset, public virtual RoverState {
public:
	ShutdownState();//constructor
	~ShutdownState();//destructor
	void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	void process();
	RoverState * nextState(RoverState *[]);
private:
	//Non-SW Resettable
	//SW Resettable
	byte _theNextState = POWER_ON_RESET_STATE;
};

#endif 