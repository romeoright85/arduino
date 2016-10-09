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
#include <RoverDebug.h>
#include <RoverReset.h>

#define _DELAYCOUNTERPERIODS
#include <RoverConfig.h>





	class DelayCounter : public virtual RoverReset {
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
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		
	private:
		unsigned int _count;//counter
		unsigned int _stopValue;//the value to stop counting at	
		unsigned int _startValue;//will store the start value and be used when it's reset
		boolean _counterDone;//is true when the stopValue is reached
		void initializeCounter(unsigned int, unsigned int);//helper function used by the overloaded constructors to create the initial object (start value, and stop value)
	};


#endif 
