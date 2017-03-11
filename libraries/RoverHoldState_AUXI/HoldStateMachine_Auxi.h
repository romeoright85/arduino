//HoldStateMachine_Auxi.h
#ifndef _HOLDSTATEMACHINE_AUXI_H
#define _HOLDSTATEMACHINE_AUXI_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>


#include <RoverState.h>


#include <NoHoldsState_Auxi.h>


#include <RoverConfig.h>

class HoldStateMachine_Auxi : public virtual RoverReset {
public:
	HoldStateMachine_Auxi();//constructor
	~HoldStateMachine_Auxi();//destructor
	void run();	
	void setNextState(RoverState *);//(the RoverState to set the next state with)
	void setExitHold(boolean);//(true to exit the HOLD state, else false to stay in the HOLD state). Sets the status to exit the hold.
	boolean exitHoldStatus();//returns the exit status
	RoverState * getNoHoldsStateAuxi();//returns the desired state
	//RoverState * getCurrentFaultHoldStateAuxi();//returns the desired state
	
	
	void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)	
private:
	//Non-SW Resettable
	RoverState * _noHoldsState_Auxi;
	
	
	//SW Resettable	
	RoverState * _state;
	
	boolean _exitHold;//true if it's time to exit the HOLD state of the finite state machine, else false
	
};

#endif 