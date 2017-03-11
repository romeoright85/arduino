#include <NoHoldsState_Auxi.h>
#include <HoldStateMachine_Auxi.h>


NoHoldsState_Auxi::NoHoldsState_Auxi(HoldStateMachine_Auxi * holdStateMachine_Auxi)
{
	this->_holdStateMachine_Auxi = holdStateMachine_Auxi;
}
NoHoldsState_Auxi::~NoHoldsState_Auxi()
{
	//do nothing	
}
void NoHoldsState_Auxi::reset()
{
	//do nothing	
}
void NoHoldsState_Auxi::process()
{
	#ifdef _DEBUG_OUTPUT
		_SERIAL_DEBUG_CHANNEL_.println(F("NoHoldsState_Auxi"));//DEBUG
	#endif
	
	//Do nothing in the NoHoldsState_Auxi
		
	//Set Next State
	//Note: Though next state not used since it will exit the HOLDS state in the Finite State Machine. This just reinitializes it to a known state.
	this->_holdStateMachine_Auxi->setNextState(this->_holdStateMachine_Auxi->getNoHoldsStateAuxi());//Set the next state
	this->_holdStateMachine_Auxi->setExitHold(true);//Exit the HOLD state of the finite state machine
}