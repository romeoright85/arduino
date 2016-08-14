//This is for an Arduino UNO

#include <HeartLed.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>


DelayCounter heartLedCounter = DelayCounter(DELAY_10_PERIODS);//initialize it to count to 10 periods, but this will be changed over time by the heart led object
HeartLed heartLed = HeartLed(HEART_LED_PIN, &heartLedCounter);
GlobalDelayTimer mainTimer = GlobalDelayTimer(DELAY_TIMER_RES_5ms, &heartLedCounter);



void setup() {
	Serial.begin(9600);
	delay(15);//add a little delay so the serial port has time to start up
	Serial.println(F("Test Running"));
}


void loop() {

	mainTimer.Running();
	heartLed.breathing();


}

