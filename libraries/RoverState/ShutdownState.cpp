#include <ShutdownState.h>

ShutdownState::ShutdownState()
{
	//do nothing	
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
	Serial.println(F("DEBUG3"));//DEBUG
}
RoverState * ShutdownState::nextState(RoverState * statesArray[])
{
	return statesArray[this->_theNextState];
}
