#include <HeartLed.h>

#include <Arduino.h>


HeartLed::HeartLed(byte ledPin, DelayCounter * counterPtr) : AnalogLed(baseClassPin)
{
	this->baseClassPin = ledPin;
	this->counterPtr = counterPtr;//take the passed counter pointer in the constructor argument and save it to the object member counter pointer
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


		if (counterPtr->countReached())//waits for 50mS, 10*5mS delay counter resolution = 50mS, use >= just in case there's a glitch and it goes over the == value
		{
			ledPatternIndex++;//change the LED index every 50ms
			analogWrite(HEART_LED_PIN, this->ledPatternArray_Breathe[ledPatternIndex]);//write the new voltage value to the LED
			counterPtr->counterReset();//reset the counter
			if (ledPatternIndex >= 37)//once all the values of the array has been displayed (0 to 37 aka 38 elements)
			{
				counterPtr->setStopValue(DELAY_80_PERIODS);//set the counter for the next interation to wait for 400mS, 80*5mS = 400mS	
				counterPtr->counterReset();
			}			
		}//end if
	}//end if	
	else//once ledPatternIndex reaches 37, it will remain at 37 and wait for 400 mS, then it resets ledPatternIndex = 0
	{
		if (counterPtr->countReached())//from the if statement above, it will now waiy for 80 periods
		{
			this->resetHeartLed();//reset ledPatternIndex
			counterPtr->setStopValue(DELAY_10_PERIODS);//set the counter for the next interation to wait for 400mS, 80*5mS = 400mS
			counterPtr->counterReset();
		}//end if
	}//end else

}
void HeartLed::resetHeartLed()
{
	this->ledPatternIndex = 0;
}

