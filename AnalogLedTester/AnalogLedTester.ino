//Used for COMM - 4

//This is for an Arduino UNO

#include <HeartLed.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>

#include <RoverConfig.h>

//The heartled will wait for 50ms (10 periods * 5mS) between each breath level, then wait for 400mS (80 periods * 5mS) before starting over again.
DelayCounter * heartLedCounter = new DelayCounter(DELAY_10_PERIODS);//initialize it to count to 10 periods, though can pass anything here as the heart led will automatically set it to the number of short delay periods (that is also passed to it as DELAY_10_PERIODS) anyways.
HeartLed * heartLed = new HeartLed(HEART_LED_PIN, heartLedCounter, DELAY_10_PERIODS, DELAY_80_PERIODS);
GlobalDelayTimer * mainTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, heartLedCounter);


//Holds all custom objects created by this sketch
RoverReset * resetArray[] = {
	heartLedCounter,
	heartLed,
	mainTimer
};


void setup() {
	//resetting all objects in this sketch
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		if (!resetArray[i] == NULL)//if the object isn't null
		{
			resetArray[i]->reset();//reset the object	
		}

	}

	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	delay(100);//add a little delay so the serial port has time to start up
	_PC_USB_SERIAL_.println(F("Heart LED Test Running"));	


	//Setting Up Timer Interrupt
	OCR0A = 0x7F;//Set the timer to interrupt somewhere in the middle of it's count, say 127 aka 7F in hex (since Timer0 is 8 bit and counts from 0 to 255)
	TIMSK0 |= _BV(OCIE0A);//Activating the Timer Interrupt by setting the Mask Register
	/*
	Reference:
	https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers
	http://forum.arduino.cc/index.php?topic=3240.0
	https://protostack.com.au/2010/09/timer-interrupts-on-an-atmega168/
	*/

}


SIGNAL(TIMER0_COMPA_vect)//Interrupt Service Routine
{
	//Tasks always running in the background, called by the timer about every 1 ms
	//This will allow the millis value to be checked every millisecond and not get missed.
	//Timer(s)
	mainTimer->Running();//activate the timer
}


void loop() {
		
	heartLed->breathing();//activate the heart led


}

