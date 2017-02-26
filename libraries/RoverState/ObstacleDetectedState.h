//ObstacleDetectedState.h
#ifndef _OBSTACLEDETECTEDSTATE_H
#define _OBSTACLEDETECTEDSTATE_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <RoverState.h>
#include <DoSomething.h>

#include <RoverConfig.h>

class ObstacleDetectedState : public virtual RoverReset, public virtual RoverState {
public:
	ObstacleDetectedState(DoSomething *);//constructor
	~ObstacleDetectedState();//destructor
	void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	void process();
	RoverState * nextState(RoverState *[]);
private:
	//Non-SW Resettable
	//SW Resettable		
	byte _theNextState = OBSTACLE_DETECTED_STATE;		
	byte _count = 0;
	DoSomething * doSomething;
};

#endif 