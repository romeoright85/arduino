//ShutdownState.h
#ifndef _SHUTDOWNSTATE_H
#define _SHUTDOWNSTATE_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <RoverState.h>
#include <RoverConfig.h>

class StateMachine;

class ShutdownState : public virtual RoverReset, public virtual RoverState {
public:
	ShutdownState(StateMachine *);//constructor
	~ShutdownState();//destructor
	void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	void process();	
private:
	//Non-SW Resettable
	StateMachine * _stateMachine;
	
	//SW Resettable	
};

#endif







