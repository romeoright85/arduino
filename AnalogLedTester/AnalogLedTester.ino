//Used for COMM - 4

//This is for an Arduino UNO

#include <HeartLed.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>



//The heartled will wait for 50ms (10 periods * 5mS) between each breath level, then wait for 400mS (80 periods * 5mS) before starting over again.
DelayCounter heartLedCounter = DelayCounter(DELAY_10_PERIODS);//initialize it to count to 10 periods, though can pass anything here as the heart led will automatically set it to the number of short delay periods (that is also passed to it as DELAY_10_PERIODS) anyways.
HeartLed heartLed = HeartLed(HEART_LED_PIN, &heartLedCounter, DELAY_10_PERIODS, DELAY_80_PERIODS);
GlobalDelayTimer mainTimer = GlobalDelayTimer(DELAY_TIMER_RES_5ms, &heartLedCounter);


//Holds all custom objects created by this sketch
RoverReset * resetArray[] = { &heartLedCounter , &heartLed, &mainTimer };


void setup() {
	//resetting all objects in this sketch
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		if (!resetArray[i] == NULL)//if the object isn't null
		{
			resetArray[i]->reset();//reset the object	
		}

	}

	Serial.begin(9600);
	delay(15);//add a little delay so the serial port has time to start up
	Serial.println(F("Test Running"));	
}


void loop() {

	//Tasks always running in the background with every loop() cycle
	mainTimer.Running();//activate the timer
	heartLed.breathing();//activate the heart led


}

