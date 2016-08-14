//DelayCounter.h
#ifndef _DELAYCOUNTER_H
#define _DELAYCOUNTER_H

#include <Arduino.h>

#define DELAY_10_PERIODS 10
#define DELAY_80_PERIODS 80
#define DELAY_200_PERIODS 200

	class DelayCounter {
	public:
		DelayCounter(unsigned int);//constructor. (value to stop the count at)
		~DelayCounter();//destructor
		void setStopValue(unsigned int);//set the stop value
		void incCounter();//increment counter
		void decCounter();//decrement counter
		unsigned int getCnt();//get the current count. good for debugging.
		boolean countReached();//returns true when the count is reached
		void counterReset();//resets the counter
	private:
		unsigned int count = 0;//counter
		unsigned int stopValue = 0;//the value to stop counting at	
	};


#endif 
