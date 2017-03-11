//ObstacleDetectedState.h
#ifndef _OBSTACLEDETECTEDSTATE_H
#define _OBSTACLEDETECTEDSTATE_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <RoverState.h>
#include <DoSomething.h>
#include <RoverConfig.h>

class StateMachine;

class ObstacleDetectedState : public virtual RoverReset, public virtual RoverState {
public:
	ObstacleDetectedState(StateMachine *, DoSomething *);//constructor (the parent StateMachine, an object controlled by this state)
	~ObstacleDetectedState();//destructor
	void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	void process();	
private:
	//Non-SW Resettable
	//SW Resettable			
	byte _count = 0;
	StateMachine * _stateMachine;
	DoSomething * _doSomething;
};

#endif 