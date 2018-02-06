//Used for NAVI - 1


#ifndef _LED_STATE_BIT_FLAGS_
#define _LED_STATE_BIT_FLAGS_ //For RoverBitFlags.h
#endif

#include <LedController_NAVI.h>
#include <RoverConfig.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>
#include <BooleanBitFlags.h>	
#include <RoverBitFlags.h>	


//Global Variables


DelayCounter * ledControllerDelayCounter = new DelayCounter(DELAY_100_PERIODS);//initialize it to count to 100 periods (so 100 periods x 5ms = 500ms). This is only the initial/default delay. It may change in the code dynamically as needed.
GlobalDelayTimer * ledControllerTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, ledControllerDelayCounter);//arbitrarily chose 5ms resolution for the timer. Can change this later to something else if I want
LedController_NAVI * ledController_NAVI = new LedController_NAVI(ledControllerDelayCounter, DELAY_50_PERIODS, DELAY_100_PERIODS);//the short delay is 50 periods (50x5ms=250ms) and the long delay is 100 periods (100x5ms=500ms)



RoverReset * resetArray[] = {
	ledControllerDelayCounter,
	ledControllerTimer,
	ledController_NAVI
};


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	_PC_USB_SERIAL_.flush();//waits for any outgoing serial data to complete
	delay(50);
	
}


void loop() {
	ledController_NAVI->setErrorType(LED_ERROR_TYPE_GENERIC_HEALTH);
	ledController_NAVI->setUniversalLEDMode(LED_ERROR_MODE);

	while (1)
	{
		ledController_NAVI->runLedController();
	}
	
}
