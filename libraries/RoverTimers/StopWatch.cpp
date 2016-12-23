#include <StopWatch.h>

#include <Arduino.h>



StopWatch::StopWatch()
{
	//do nothing
}
StopWatch::~StopWatch()
{
	//do nothing
}
void StopWatch::reset()
{
	//software reset
	this->_startedTime = 0;
	this->_recordedStartTime = 0;
}
void StopWatch::startStopWatch()
{
	this->_startedTime = millis();
}
unsigned long StopWatch::getElapsedTime()
{
	return this->_startedTime - this->_recordedStartTime;
}
void StopWatch::recordStartTime()
{
	this->_recordedStartTime = this->_startedTime;
}
bool StopWatch::timeElapsedAfterRecordedTime()
{
	if(this->_startedTime > this->_recordedStartTime)
	{
		return true;
	}
	else
	{
		return false;
	}
}

