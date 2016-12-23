#include <GlobalDelayTimer.h>

#include <Arduino.h>



GlobalDelayTimer::GlobalDelayTimer(byte delayInterval, DelayCounter * counterPtr)
{
	this->_delayInterval = delayInterval;
	this->_counterPtr = counterPtr;//take the passed counter pointer in the constructor argument and save it to the object member counter pointer
}
GlobalDelayTimer::~GlobalDelayTimer()
{
	//do nothing
}

void GlobalDelayTimer::Running()
{
		
	if (millis() - this->_prevMillis >= this->_delayInterval)
	{
		this->_prevMillis = millis();//reset the start time once the delay interval has reached (since the clock is relative and not absolute time)
		this->_counterPtr->incCounter();//increment the counter for each delay interval reached. So the counter will count the number of delays (delay intervals). Only once the number of delays have been achieved, will the counter reset itself after doing something.
	}//end if
}
void GlobalDelayTimer::reset()
{
		//software reset
		//nothing needed to be done. The counter class will reset the counter object. This class just acts on the counter object.
}