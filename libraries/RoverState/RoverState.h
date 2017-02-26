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
	//virtual destructor is required if the object may be deleted through a pointer to RoverReset
	virtual ~RoverState();//destructor
	virtual void reset() = 0;//pure virtual function, must be overridden
	virtual void process() = 0;//pure virtual function, must be overridden
	virtual RoverState * nextState(RoverState * []) = 0;//pure virtual function, must be overridden
private:
	//Non-SW Resettable
	//SW Resettable	
};

#endif