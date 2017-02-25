#include <ObstacleDetectedState.h>


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
	Serial.println(F("DEBUG2"));//DEBUG
}
RoverState * ObstacleDetectedState::nextState(RoverState * statesArray[])
{
	return statesArray[SHUTDOWN_STATE];
}
