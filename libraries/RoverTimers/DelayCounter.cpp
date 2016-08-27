#include <DelayCounter.h>

#include <Arduino.h>


DelayCounter::DelayCounter(unsigned int stopValue)
{
	this->initializeCounter(0, stopValue);//set the default start value as 0 and pass the stopValue		
}
DelayCounter::DelayCounter(unsigned int startValue, unsigned int stopValue)
{		
	this->initializeCounter(startValue, stopValue);//pass the start and stop values
}
DelayCounter::~DelayCounter()
{
	//do nothing
}
void DelayCounter::incCounter()
{
	if (this->_count < 4294967295)//4294967295 is the max value of unsigned in
	{
		if (this->_count == this->_stopValue)
		{
			//stop counting as the stop value has been reached. It will only increment again after a reset
			this->_counterDone = true;
		}
		else
		{
			this->_count++;//increment the counter
			this->_counterDone = false;
		}
	}
	else
	{
		this->_count = 0;//reset the count since there is overflow
	}	
}
void DelayCounter::decCounter()
{
	if (this->_count >= 0)//0 is the min value of unsigned in
	{
		if (this->_count == this->_stopValue)
		{
			//stop counting as the stop value has been reached. It will only decrement again after a reset
			this->_counterDone = true;
		}
		else
		{
			this->_count--;//decrement the counter		
			this->_counterDone = false;
		}
	}
	else
	{
		this->_count = 0;//reset the count since it's at the min value and you don't want wrap around.
	}
}
unsigned int DelayCounter::getCnt()
{
	return this->_count;
}

boolean DelayCounter::countReached()
{
	return this->_counterDone;
}
void DelayCounter::counterReset()
{
	this->_count = this->_startValue;//reset the count
	this->_counterDone = false;//reset counter done flag
}
void DelayCounter::setStopValue(unsigned int stopValue)
{
	this->_stopValue = stopValue;
}
void DelayCounter::setStartValue(unsigned int startValue)
{
	this->_startValue = startValue;
}
void DelayCounter::initializeCounter(unsigned int startValue, unsigned int stopValue)
{

	//shouldn't have to check for negative values since it's an unsigned int. But just in case this gets changed later, add this if statement as a guard
	if (startValue < 0)
	{
		this->_startValue = 0;
		this->counterReset();//reset the counter with the startValue to initialize it
	}
	else
	{
		//the value is positive or 0 so it's okay.		
		this->counterReset();//reset the counter with the startValue to initialize it
	}

	//either increment or decrement can be used
	//shouldn't have to check for negative values since it's an unsigned int. But just in case this gets changed later, add this if statement as a guard
	if (stopValue < 0)
	{
		this->_stopValue = 0;
	}
	else
	{
		//the value is positive or 0 so it's okay.		
		this->_stopValue = stopValue;
	}
}
void DelayCounter::reset()
{
		//software reset
		this->counterReset();		
}

