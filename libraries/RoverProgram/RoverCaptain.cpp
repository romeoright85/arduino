#include <RoverCaptain.h>


RoverCaptain::RoverCaptain()
{
	//this->_state = State::INITIALIZE;	
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


}
