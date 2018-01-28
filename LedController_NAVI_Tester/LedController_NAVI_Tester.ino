//Used for NAVI - 1


#include <LedController_NAVI.h>
#include <RoverConfig.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>

//Global Variables


DelayCounter * ledControllerDelayCounter = new DelayCounter(DELAY_10_PERIODS);//initialize it to count to 10 periods (so 10 periods x 5ms = 50ms)
GlobalDelayTimer * ledControllerTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, ledControllerDelayCounter);//arbitrarily chose 5ms resolution for the timer. Can change this later to something else if I want
LedController_NAVI * ledController_NAVI = new LedController_NAVI(ledControllerDelayCounter);



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

}
