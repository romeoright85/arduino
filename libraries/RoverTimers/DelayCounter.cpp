#include <DelayCounter.h>

#include <Arduino.h>



DelayCounter::DelayCounter(unsigned int stopValue)
{		

	this->stopValue = stopValue;//no need to check for negative values since using unsigned int
	this->count = 0;//initialize counter
}
DelayCounter::~DelayCounter()
{
	//do nothing
}
void DelayCounter::incCounter()
{
	if (this->count < 4294967295)//4294967295 is the max value of unsigned in
	{
		this->count++;//increment the counter		
	}
	else
	{
		this->count = 0;//reset the count since there is overflow
	}
	
}
void DelayCounter::decCounter()
{
	if (this->count > 0)//0 is the min value of unsigned in
	{
		this->count--;//decrement the counter		
	}
	else
	{
		this->count = 0;//reset the count since there is overflow
	}
}

unsigned int DelayCounter::getCnt()
{
	return this->count;
}

boolean DelayCounter::countReached()
{
	if (this->count >= stopValue)//use >= just in case there is a glitch and it goes over the stopValue
	{
		return true;
	}
	else
	{
		return false;
	}
}
void DelayCounter::counterReset()
{
	this->count = 0;//reset the count
}
void DelayCounter::setStopValue(unsigned int stopValue)
{
	this->stopValue = stopValue;//no need to check for negative values since using unsigned int
}
