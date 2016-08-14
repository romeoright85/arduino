#include <GlobalDelayTimer.h>

#include <Arduino.h>



GlobalDelayTimer::GlobalDelayTimer(byte delayInterval, DelayCounter * counterPtr)
{
	this->delayInterval = delayInterval;
	this->counterPtr = counterPtr;//take the passed counter pointer in the constructor argument and save it to the object member counter pointer
}

GlobalDelayTimer::~GlobalDelayTimer()
{
	//do nothing
}

void GlobalDelayTimer::Running()
{
		
	if (millis() - prevMillis >= this->delayInterval)
	{

		prevMillis = millis();//reset the start time once the delay interval has reached (since the clock is relative and not absolute time)
		counterPtr->incCounter();//increment the counter for each delay interval reached
	}//end if
}


