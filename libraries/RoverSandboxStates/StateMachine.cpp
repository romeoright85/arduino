#include <StateMachine.h>




StateMachine::StateMachine()
{
	
	//Create Misc Objects controlled by the state machine (but not part of the state machine process itself)
	this->_doSomething = new DoSomething();
		
	//Create the state objects (for processing the state machine)
	this->_powerOnResetState = new PowerOnResetState(this);	
	this->_obstacleDetectedState = new ObstacleDetectedState(this, this->_doSomething);
	this->_shutdownState = new ShutdownState(this);
		
	//Reset/Initialize the state machine
	this->reset();
	
}
StateMachine::~StateMachine()
{
	//do nothing	
}
void StateMachine::reset()
{
	//(Re)Initialize the state machine
	this->_state = this->_powerOnResetState;
}
void StateMachine::run()
{
	//Run the state machine
	this->_state->process();	//process the current state of the state machine
}
void StateMachine::setNextState(RoverState * state)
{
	this->_state = state;
}
RoverState * StateMachine::getPowerOnResetState()
{	
	return this->_powerOnResetState;
}
RoverState * StateMachine::getObstacleDetectedState()
{	
	return this->_obstacleDetectedState;
}
RoverState * StateMachine::getShutdownState()
{	
	return this->_shutdownState;
}