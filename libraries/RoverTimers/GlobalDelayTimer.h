/*
The timer will count to the provided delay interval.
Once that is reached, it will increment the counter that is passed to it.
So the counter, that is passed to this timer, will count the number of delays (delay intervals).
Only once the number of delay intervals have been achieved, the counter (that is passed to this timer) will produce a counter done flag and stay there until it is reset by the object that needs to use the counter.

	
	
	

The timer will check for the time each time GlobalDelayTimer::Running() is executed.
This code should be placed in an interrupt service handler of a timer output compare.


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
		yourTimer->Running();
		
	}



Reference:
https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers
http://forum.arduino.cc/index.php?topic=3240.0
https://protostack.com.au/2010/09/timer-interrupts-on-an-atmega168/



		
		
		

The design for this is instead of using delay() which holds up the program from doing anything else, you can check for GlobalDelayTimer::Running() then go do something else and check it again later in a polling style.
The timer will be running in the background then.

The class takes in a delayInterval and DelayCounter object (pointer). It will count in milliseconds until it reaches the delayInterval.
Then it will increment the DelayCounter's "period" counter.
The reason for this is just in case the main code has different periods it want to check, you can create a DelayCounter object for each desired increments of the delayInterval.
So for the total desired delay, you multiply delayInterval by the number of counted "periods".
i.e. for a 5ms delayInterval with a stop value to count up to of 10, you get 5ms x 10 = 50ms


//Note: Careful not using delay() in the loop when using timers as it will slow everything down in proportion
//Note: The timer/delay won't be accurate because things like Serial.println() will also slow it down. But good enough if you want parallel processing (using the poll method).

--------------------
Example Use:
--------------------
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>

DelayCounter * counter = new DelayCounter(DELAY_10_PERIODS);//initialize it to count to 10 periods
GlobalDelayTimer * timer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, counter);//set each period to be 5ms long (delay interval)


In the main loop() function put:
	timer->Running();//activate the timer
	
Then in the loop (either directly or by some other function, class method, etc.)

Example for loop() use:
if (counter->countReached())
{
	//do something
	counter->counterReset();//reset the counter
}//end if
--------------------

*/


//GlobalDelayTimer.h
#ifndef _GLOBALDELAYTIMER_H
#define _GLOBALDELAYTIMER_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <DelayCounter.h>
#include <RoverReset.h>

#define _DELAYTIMER_RESOLUTIONS
#include <RoverConfig.h>



class GlobalDelayTimer : public virtual RoverReset {
public:
	GlobalDelayTimer(byte, DelayCounter * );//constructor, (delayInterval value, DelayCounter pointer)
	~GlobalDelayTimer();//destructor
	void Running();//activates the clock	
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:
	unsigned long _prevMillis;//holds the previous counter value
	byte _delayInterval;//holds the delay interval size
	DelayCounter * _counterPtr;//delay counter pointer		
};


#endif 
