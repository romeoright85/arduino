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
	PowerOnResetState();//constructor
	~PowerOnResetState();//destructor
	void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	void process();
	RoverState * nextState(RoverState *[]);
private:
	//Non-SW Resettable
	//SW Resettable
	byte _theNextState = OBSTACLE_DETECTED_STATE;
};

#endif 