#include <HeartLed.h>

#include <Arduino.h>


HeartLed::HeartLed(byte ledPin, DelayCounter * counterPtr, unsigned int periodsForShortDelay, unsigned int periodsForLongDelay) : AnalogLed(_baseClassPin)
{
	_baseClassPin = ledPin;
	this->_counterPtr = counterPtr;//take the passed counter pointer in the constructor argument and save it to the object member counter pointer
	this->_periodsForShortDelay = periodsForShortDelay;//store the number of periods for short delay
	this->_periodsForLongDelay = periodsForLongDelay;//story the number of periods for long delay
	this->_counterPtr->setStopValue(this->_periodsForShortDelay);//start by counting to the number of short delays
}

HeartLed::~HeartLed()
{
	//do nothing
}

void HeartLed::breathing()
{

//UNCOMMENT THE LINE BELOW FOR DEBUGGING
//Serial.println(this->_ledPatternIndex);//KEEP FOR DEBUGGING

	//LED Code
	if (this->_ledPatternIndex < 37)
	{
		//waits for the short delay (determined the by periodsForShortDelay * delayInterval)
		//The periodsForShortDelay is set by the heart led from the else statement below or by the constructor. The delayInterval is set when the GlobalDelayTimer object is created. And the GlobalDelayTimer is what increments the counter.
		if (this->_counterPtr->countReached())
		{
			this->_ledPatternIndex++;//change the LED index every (periodsForShortDelay * delayInterval)
			analogWrite(HEART_LED_PIN, this->_ledPatternArray_Breathe[this->_ledPatternIndex]);//write the new voltage value to the LED
			this->_counterPtr->counterReset();//reset the counter
			if (this->_ledPatternIndex >= 37)//once all the values of the array has been displayed (0 to 37 aka 38 elements)
			{
				this->_counterPtr->setStopValue(this->_periodsForLongDelay);//set the counter for the next iteration to wait for (periodsForLongDelay * delayInterval)
				this->_counterPtr->counterReset();
			}			
		}//end if
	}//end if	
	else//once ledPatternIndex reaches 37, it will remain at 37 and wait for 400 mS, then it resets ledPatternIndex = 0
	{
		//waits for the long delay (determined the by periodsForLongDelay * delayInterval)
		//The periodsForLongDelay is set by the heart led in the if statement above. The delayInterval is set when the GlobalDelayTimer object is created. And the GlobalDelayTimer is what increments the counter.
		if (this->_counterPtr->countReached())
		{
			this->resetHeartLed();//reset ledPatternIndex
			this->_counterPtr->setStopValue(this->_periodsForShortDelay);//set the counter for the next iteration to wait for (periodsForShortDelay * delayInterval)
			this->_counterPtr->counterReset();
		}//end if
	}//end else

}
void HeartLed::resetHeartLed()
{
	AnalogLed::reset();
	this->_ledPatternIndex = 0;
}
void HeartLed::reset()
{
	//software reset
	this->resetHeartLed();
	
}
