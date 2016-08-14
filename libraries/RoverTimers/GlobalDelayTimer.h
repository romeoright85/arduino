//GlobalDelayTimer.h
#ifndef _GLOBALDELAYTIMER_H
#define _GLOBALDELAYTIMER_H

#include <Arduino.h>
#include <DelayCounter.h>

#define DELAY_TIMER_RES_5ms 5

class GlobalDelayTimer {
public:
	GlobalDelayTimer(byte, DelayCounter * );//constructor, (delayInterval value, DelayCounter pointer)
	~GlobalDelayTimer();//destructor
	void Running();//activates the clock
private:
	unsigned long prevMillis;//holds the previous counter value
	byte delayInterval;//holds the delay interval size
	DelayCounter * counterPtr;//delay counter pointer
};


#endif 
