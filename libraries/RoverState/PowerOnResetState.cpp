#include <PowerOnResetState.h>

PowerOnResetState::PowerOnResetState()
{
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
	Serial.println(F("DEBUG1"));//DEBUG
}
RoverState *  PowerOnResetState::nextState(RoverState * statesArray[])
{
	return statesArray[this->_theNextState];
}
