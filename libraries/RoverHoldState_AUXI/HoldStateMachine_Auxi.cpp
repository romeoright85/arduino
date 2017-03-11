#include <HoldStateMachine_Auxi.h>

HoldStateMachine_Auxi::HoldStateMachine_Auxi()
{
			
	//Create the state objects (for processing the state machine)
	this->_noHoldsState_Auxi = new NoHoldsState_Auxi(this);
		
	//Reset/Initialize the state machine
	this->reset();
	
}
HoldStateMachine_Auxi::~HoldStateMachine_Auxi()
{
	//do nothing	
}
void HoldStateMachine_Auxi::reset()
{
	//(Re)Initialize the state machine
	this->_state = this->_noHoldsState_Auxi;
	
	//Initialize the exit hold flag
	this->_exitHold = true;//exit the HOLD state on default
}
void HoldStateMachine_Auxi::run()
{
	//Run the state machine
	this->_state->process();	//process the current state of the state machine
}
void HoldStateMachine_Auxi::setNextState(RoverState * state)
{
	this->_state = state;
}
RoverState * HoldStateMachine_Auxi::getNoHoldsStateAuxi()
{			
	return this->_noHoldsState_Auxi;
}
void HoldStateMachine_Auxi::setExitHold(boolean status)
{
	this->_exitHold = status;
}
boolean HoldStateMachine_Auxi::exitHoldStatus()
{
	return this->_exitHold;
}



