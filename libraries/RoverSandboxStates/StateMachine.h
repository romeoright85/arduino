//StateMachine.h
#ifndef _STATEMACHINE_H
#define _STATEMACHINE_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>


#include <RoverState.h>
#include <DoSomething.h>


#include <PowerOnResetState.h>
#include <ShutdownState.h>
#include <ObstacleDetectedState.h>



#include <RoverConfig.h>

class StateMachine : public virtual RoverReset {
public:
	StateMachine();//constructor
	~StateMachine();//destructor
	void run();	
	void setNextState(RoverState *);//(the RoverState to set the next state with)
	RoverState * getPowerOnResetState();//returns the desired state
	RoverState * getObstacleDetectedState();//returns the desired state
	RoverState * getShutdownState();//returns the desired state
	
	void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)	
private:
	//Non-SW Resettable
	RoverState * _powerOnResetState;	
	RoverState * _obstacleDetectedState;
	RoverState * _shutdownState;
	
	DoSomething * _doSomething;
	//SW Resettable	
	RoverState * _state;
	
};

#endif 