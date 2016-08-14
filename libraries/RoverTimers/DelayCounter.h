/*

This counter can up count or down count.
Typically used in conjunction with GlobalDelayTimer it counts up to the stopValue and then marks counterDone as true.
This private variable can be read with the public method DelayCounter::countReached().
The counter will stop counting once it hits the stop value (regardless of incrementing or decrementing)

You can either create a default DelayCounter(unsigned int) that takes only the stopValue and will be used to increment to a stopValue (since the count starts at the lowest value, 0).
Or you can create a DelayCounter(unsigned int, unsigned int) and pass a startValue and a stopValue. The count will be set to startValue and it will stop counting when it reaches stopValue.

Use DelayCounter::incCounter() or DelayCounter::decCounter() to increment or decrement the counter respectively.
You can use DelayCounter::setStopValue() or DelayCounter::setStartValue() to set the start and stop values respective. You may want to do a reset though as it won't do it automatically.

Use DelayCounter::getCnt() to get the current count the counter is at.
Use DelayCounter::counterReset() to reset the counter to the startValue and clear the counterDone flag.

*/

//DelayCounter.h
#ifndef _DELAYCOUNTER_H
#define _DELAYCOUNTER_H

#include <Arduino.h>

#define DELAY_10_PERIODS 10
#define DELAY_80_PERIODS 80
#define DELAY_200_PERIODS 200

	class DelayCounter {
	public:
		DelayCounter(unsigned int);//constructor. (stop value. The default start value when not provided is 0.)
		DelayCounter(unsigned int, unsigned int);//constructor. (start value, and stop value)
		~DelayCounter();//destructor
		void setStopValue(unsigned int);//set the stop value
		void setStartValue(unsigned int);//set the start value
		void incCounter();//increment counter
		void decCounter();//decrement counter
		unsigned int getCnt();//get the current count. good for debugging.
		boolean countReached();//returns true when the count is reached
		void counterReset();//resets the counter to the startValue and clears the counterDone flag
	private:
		unsigned int count;//counter
		unsigned int stopValue;//the value to stop counting at	
		unsigned int startValue;//will store the start value and be used when it's reset
		boolean counterDone;//is true when the stopValue is reached
		void initializeCounter(unsigned int, unsigned int);//helper function used by the overloaded constructors to create the initial object (start value, and stop value)
	};


#endif 
