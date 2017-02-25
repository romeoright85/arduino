//RoverState.h
#ifndef _ROVERSTATE_H
#define _ROVERSTATE_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>


#define POWER_ON_RESET_STATE				0
#define SHUTDOWN_STATE							1
#define OBSTACLE_DETECTED_STATE			2


#include <RoverConfig.h>

class RoverState : public virtual RoverReset {
public:
	//Don't make a constructor since treating this like a Java Interface (which means it can't be instantiated, only derived)
	// virtual destructor is required if the object may be deleted through a pointer to RoverReset
	virtual ~RoverState();//destructor
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	virtual void process();
	virtual RoverState * nextState(RoverState * []);
private:
	//Non-SW Resettable
	//SW Resettable
};

#endif