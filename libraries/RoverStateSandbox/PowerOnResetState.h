//PowerOnResetState.h
#ifndef _POWERONRESETSTATE_H
#define _POWERONRESETSTATE_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <RoverState.h>
#include <RoverConfig.h>

class StateMachine;

class PowerOnResetState : public virtual RoverReset, public virtual RoverState {
public:
	PowerOnResetState(StateMachine *);//constructor
	~PowerOnResetState();//destructor
	void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	void process();	
private:
	//Non-SW Resettable
	StateMachine * _stateMachine;
	//SW Resettable	
};

#endif 


