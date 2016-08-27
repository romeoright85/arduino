#include <HeartLed.h>

#include <Arduino.h>


HeartLed::HeartLed(byte ledPin, DelayCounter * counterPtr, unsigned int periodsForShortDelay, unsigned int periodsForLongDelay) : AnalogLed(baseClassPin)
{
	this->baseClassPin = ledPin;
	this->counterPtr = counterPtr;//take the passed counter pointer in the constructor argument and save it to the object member counter pointer
	this->periodsForShortDelay = periodsForShortDelay;//store the number of periods for short delay
	this->periodsForLongDelay = periodsForLongDelay;//story the number of periods for long delay
	this->counterPtr->setStopValue(this->periodsForShortDelay);//start by counting to the number of short delays
}

HeartLed::~HeartLed()
{
	//do nothing
}

void HeartLed::breathing()
{
	
	//LED Code
	if (ledPatternIndex < 37)
	{

		//waits for the short delay (determined the by periodsForShortDelay * delayInterval)
		//The periodsForShortDelay is set by the heart led from the else statement below or by the constructor. The delayInterval is set when the GlobalDelayTimer object is created. And the GlobalDelayTimer is what increments the counter.
		if (counterPtr->countReached())
		{
			ledPatternIndex++;//change the LED index every (periodsForShortDelay * delayInterval)
			analogWrite(HEART_LED_PIN, this->ledPatternArray_Breathe[ledPatternIndex]);//write the new voltage value to the LED
			counterPtr->counterReset();//reset the counter
			if (ledPatternIndex >= 37)//once all the values of the array has been displayed (0 to 37 aka 38 elements)
			{
				counterPtr->setStopValue(this->periodsForLongDelay);//set the counter for the next interation to wait for (periodsForLongDelay * delayInterval)
				counterPtr->counterReset();
			}			
		}//end if
	}//end if	
	else//once ledPatternIndex reaches 37, it will remain at 37 and wait for 400 mS, then it resets ledPatternIndex = 0
	{
		//waits for the long delay (determined the by periodsForLongDelay * delayInterval)
		//The periodsForLongDelay is set by the heart led in the if statement above. The delayInterval is set when the GlobalDelayTimer object is created. And the GlobalDelayTimer is what increments the counter.
		if (counterPtr->countReached())
		{
			this->resetHeartLed();//reset ledPatternIndex
			counterPtr->setStopValue(this->periodsForShortDelay);//set the counter for the next interation to wait for (periodsForShortDelay * delayInterval)
			counterPtr->counterReset();
		}//end if
	}//end else

}
void HeartLed::resetHeartLed()
{
	AnalogLed::reset();
	this->ledPatternIndex = 0;
}
void HeartLed::reset()
{
	//software reset
	this->resetHeartLed();
	
}
