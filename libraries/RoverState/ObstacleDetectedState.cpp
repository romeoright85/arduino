#include <ObstacleDetectedState.h>

ObstacleDetectedState::ObstacleDetectedState(DoSomething * doSomething)
{
	this->doSomething = doSomething;
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
		Serial.println(F("AH HA!"));//DEBUG
		doSomething->helloWorld();
		this->_theNextState = SHUTDOWN_STATE;			
		this->_count = 0;
	}		
	else
	{
		Serial.println(F("DEBUG2"));//DEBUG
		doSomething->goodbyeWorld();
		_theNextState = OBSTACLE_DETECTED_STATE;	
		this->_count++;		
	}
	
	
	
}
RoverState * ObstacleDetectedState::nextState(RoverState * statesArray[])
{
	return statesArray[this->_theNextState];
}
