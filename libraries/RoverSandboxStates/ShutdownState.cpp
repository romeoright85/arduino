#include <ShutdownState.h>
#include <StateMachine.h>

ShutdownState::ShutdownState(StateMachine * stateMachine)
{
	this->_stateMachine = stateMachine;
}
ShutdownState::~ShutdownState()
{
	//do nothing	
}
void ShutdownState::reset()
{
	//do nothing	
}
void ShutdownState::process()
{
	Serial.println(F("3: ShutdownState"));//DEBUG
	this->_stateMachine->setNextState(this->_stateMachine->getPowerOnResetState());//Set the next state
}










