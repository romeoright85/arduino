#include <ObstacleDetectedState.h>
#include <StateMachine.h>

ObstacleDetectedState::ObstacleDetectedState(StateMachine * stateMachine, DoSomething * doSomething)
{
	this->_stateMachine = stateMachine;
	this->_doSomething = doSomething;
}
ObstacleDetectedState::~ObstacleDetectedState()
{
	//do nothing	
}
void ObstacleDetectedState::reset()
{
	//do nothing	
}
void ObstacleDetectedState::process()
{
	
	
	if(this->_count == 4)
	{
		Serial.println(F("2: ObstacleDetectedState: Count Reached"));//DEBUG
		this->_doSomething->goodbyeWorld();		
		this->_count = 0;
		this->_stateMachine->setNextState(this->_stateMachine->getShutdownState());//Set the next state
	}		
	else
	{
		Serial.println(F("2: ObstacleDetectedState"));//DEBUG
		this->_doSomething->helloWorld();		
		this->_count++;		
		this->_stateMachine->setNextState(this->_stateMachine->getObstacleDetectedState());//Set the next state
	}
	
	
	
}
