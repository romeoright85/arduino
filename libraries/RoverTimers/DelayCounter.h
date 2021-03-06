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


//Note: Careful not using delay() in the loop when using timers as it will slow everything down in proportion
//Note: The timer/delay won't be accurate because things like Serial.println() will also slow it down. But good enough if you want parallel processing (using the poll method).



Reference:
https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers
http://forum.arduino.cc/index.php?topic=3240.0
https://protostack.com.au/2010/09/timer-interrupts-on-an-atmega168/






--------------------
Example Use:
--------------------
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>

DelayCounter * counter = new DelayCounter(DELAY_10_PERIODS);//initialize it to count to 10 periods
GlobalDelayTimer * timer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, counter);//set each period to be 5ms long (delay interval)



Place the output compare interrupt setup code in the setup function:
	setup(){
		//Setting Up Timer Interrupt
		OCR0A = 0x7F;//Set the timer to interrupt somewhere in the middle of it's count, say 127 aka 7F in hex (since Timer0 is 8 bit and counts from 0 to 255)
		TIMSK0 |= _BV(OCIE0A);//Activating the Timer Interrupt by setting the Mask Register	
	}


Then create a interrupt service routine:
	SIGNAL(TIMER0_COMPA_vect)//Interrupt Service Routine
	{
		//Tasks always running in the background, called by the timer about every 1 ms
		//This will allow the millis value to be checked every millisecond and not get missed.
		//Timer(s)
		timer->Running();
		
	}
	
	
Then in the loop (either directly or by some other function, class method, etc.)

Example for loop() use:
if (counter->countReached())
{
	//do something
	counter->counterReset();//reset the counter
}//end if
--------------------

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
		DelayCounter(unsigned int);//constructor. (initial stop value. The default start value when not provided is 0.)
		//Note: The initial stop value can be assigned to a different stop value by calling setStopValue()
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
