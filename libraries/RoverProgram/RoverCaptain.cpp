#include <RoverCaptain.h>


RoverCaptain::RoverCaptain()
{

	this->_state = INITIALIZE;
	
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
		case POWER_ON_RESET:
			Serial.println(F("1"));//DEBUG
			this->_state = INITIALIZE;
			break;
		case INITIALIZE:
			Serial.println(F("2"));//DEBUG
			this->_state = ROUTINE;
			break;			
		case ROUTINE:
			Serial.println(F("3"));//DEBUG
			this->_state = SHUTDOWN;
			break;			
		case SHUTDOWN:
			Serial.println(F("4"));//DEBUG
			this->_state = INITIALIZE;
			break;		
		default:
			Serial.println(F("ERROR"));//DEBUG
			break;		
	}
}
