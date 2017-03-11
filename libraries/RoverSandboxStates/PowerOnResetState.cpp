#include <PowerOnResetState.h>
#include <StateMachine.h>


PowerOnResetState::PowerOnResetState(StateMachine * stateMachine)
{
	this->_stateMachine = stateMachine;
}
PowerOnResetState::~PowerOnResetState()
{
	//do nothing	
}
void PowerOnResetState::reset()
{
	//do nothing	
}
void PowerOnResetState::process()
{
	Serial.println(F("1: PowerOnResetState"));//DEBUG
	this->_stateMachine->setNextState(this->_stateMachine->getObstacleDetectedState());//Set the next state
	
}