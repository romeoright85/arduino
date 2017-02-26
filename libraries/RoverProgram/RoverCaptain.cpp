#include <RoverCaptain.h>


RoverCaptain::RoverCaptain()
{

	this->_state = State::INITIALIZE;
	
}
RoverCaptain::~RoverCaptain()
{
	//do nothing
}
void RoverCaptain::reset()
{


	
	//resetting all objects
	for (byte i = 0; i < sizeof(this->resetArray) / sizeof(this->resetArray[0]); i++)
	{
		this->resetArray[i]->reset();
	}

}
void RoverCaptain::run()
{

	switch(this->_state)
	{
		case State::POWER_ON_RESET:
			Serial.println(F("1"));//DEBUG
			this->_state = State::INITIALIZE;
			break;
		case State::INITIALIZE:
			Serial.println(F("2"));//DEBUG
			this->_state = State::ROUTINE;
			break;			
		case State::ROUTINE:
			Serial.println(F("3"));//DEBUG
			this->_state = State::SHUTDOWN;
			break;			
		case State::SHUTDOWN:
			Serial.println(F("4"));//DEBUG
			this->_state = State::INITIALIZE;
			break;		
		default:
			Serial.println(F("ERROR"));//DEBUG
			break;		
	}
}
