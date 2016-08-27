/*
The timer will check for the time each time GlobalDelayTimer::Running() is executed.
So it need to be executed in a loop such as loop().
The design for this is instead of using delay() which holds up the program from doing anything else, you can check for GlobalDelayTimer::Running() then go do something else and check it again later in a polling style.
The timer will be running in the background then.

The class takes in a delayInterval and DelayCounter object (pointer). It will count in milliseconds until it reaches the delayInterval.
Then it will increment the DelayCounter's "period" counter.
The reason for this is just in case the main code has different periods it want to check, you can create a DelayCounter object for each desired increments of the delayInterval.
So for the total desired delay, you multiply delayInterval by the number of counted "periods".
i.e. for a 5ms delayInterval with a stop value to count up to of 10, you get 5ms x 10 = 50ms
*/

//GlobalDelayTimer.h
#ifndef _GLOBALDELAYTIMER_H
#define _GLOBALDELAYTIMER_H

#include <Arduino.h>
#include <DelayCounter.h>
#include <RoverReset.h>

#define DELAY_TIMER_RES_5ms 5

class GlobalDelayTimer : public virtual RoverReset {
public:
	GlobalDelayTimer(byte, DelayCounter * );//constructor, (delayInterval value, DelayCounter pointer)
	~GlobalDelayTimer();//destructor
	void Running();//activates the clock
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:
	unsigned long prevMillis;//holds the previous counter value
	byte delayInterval;//holds the delay interval size
	DelayCounter * counterPtr;//delay counter pointer
};


#endif 
