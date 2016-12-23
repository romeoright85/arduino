//StopWatch.h
#ifndef _STOPWATCH_H
#define _STOPWATCH_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>




class StopWatch : public virtual RoverReset {
public:
	StopWatch();//constructor
	~StopWatch();//destructor	
	void startStopWatch();//starts/resets the stop watch
	void recordStartTime();//stores the start time of the stop watch into memory into _recordedStartTime
	unsigned long getElapsedTime();//returns the delta time between the start time and the recorded time
	bool timeElapsedAfterRecordedTime();//returns true if time has elapsed between the recorded time and the last start time
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:	
	unsigned long _startedTime;//holds the last time the stop watch was started
	unsigned long _recordedStartTime;//holds the recorded time the stop watch was started
};


#endif 
