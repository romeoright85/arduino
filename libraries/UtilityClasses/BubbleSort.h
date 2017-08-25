//BubbleSort.h
#ifndef _BUBBLESORT_H
#define _BUBBLESORT_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>



/*
	Reference:
	https://en.wikipedia.org/wiki/Bubble_sort
*/


//Uncomment to debug
//#define _DEBUG_PRINT_BUBBLESORT_ARRAY_HORIZONTAL
//#define _DEBUG_PRINT_BUBBLESORT_ARRAY_VERTICAL

#include <RoverConfig.h>


class BubbleSort : public virtual RoverReset {
public:
	BubbleSort();//constructor
	~BubbleSort();//destructor
	static double getMedian(double, double, double, double, double, double, double);
	
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:
	//Non-SW Resettable
	//SW Resettable
};

#endif 