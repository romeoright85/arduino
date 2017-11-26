//NoHoldsState_Auxi.h
#ifndef _NOHOLDS_AUXI_H
#define _NOHOLDS_AUXI_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <RoverState.h>
#include <RoverConfig.h>


//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast
#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ _MAIN_SERIAL_ //When using COMM Broadcast, reroute the PC USB output to the channel to MAIN instead
#else
	#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_
#endif



//uncomment to debug
#define _DEBUG_OUTPUT

class HoldStateMachine_Auxi;

class NoHoldsState_Auxi : public virtual RoverReset, public virtual RoverState {
public:
	NoHoldsState_Auxi(HoldStateMachine_Auxi *);//constructor
	~NoHoldsState_Auxi();//destructor
	void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	void process();	
private:
	//Non-SW Resettable
	HoldStateMachine_Auxi * _holdStateMachine_Auxi;
	//SW Resettable	
};

#endif 


