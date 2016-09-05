//This is for an Arduino MEGA

#include <UnderglowLeds.h>
#include <FoglightAssembly.h>
#include <SignalLightAssembly.h>
#include <DelayCounter.h>
#include <GlobalDelayTimer.h>


UnderglowLeds underglowLight = UnderglowLeds(UNDERGLOW_PIN);
FoglightAssembly fogLights = FoglightAssembly(FRONT_RIGHT_FOG_PIN, FRONT_LEFT_FOG_PIN);
SignalLightAssembly signalLightAssy = SignalLightAssembly(FRONT_RIGHT_SIGNAL_PIN, FRONT_LEFT_SIGNAL_PIN, SIDE_RIGHT_SIGNAL_PIN, SIDE_LEFT_SIGNAL_PIN);
DelayCounter delayCounter = DelayCounter(DELAY_200_PERIODS);//initialize it to count to 200 periods.
GlobalDelayTimer mainTimer = GlobalDelayTimer(DELAY_TIMER_RES_5ms, &delayCounter);//200 periods x 5ms = 1s

void wait1Sec();

//Holds all objects created by this sketch
RoverReset * resetArray[] = { &underglowLight , &fogLights, &signalLightAssy, &delayCounter, &mainTimer };





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
	Serial.println("Test running");
}


void loop() {




	Serial.println("tick");
	//blink all the lights
	underglowLight.ledOn();
	fogLights.turnOn(LEFT_FOG, RIGHT_FOG);
	signalLightAssy.turnOn(FRONT_RIGHT_SIGNAL_PIN, FRONT_LEFT_SIGNAL_PIN, SIDE_RIGHT_SIGNAL_PIN, SIDE_LEFT_SIGNAL_PIN);
	wait1Sec();//this will stop the program for 1 sec and do nothing else until 1 sec has passed
	Serial.println("tock");
	underglowLight.ledOff();
	fogLights.turnOff(LEFT_FOG, RIGHT_FOG);
	signalLightAssy.turnOff(FRONT_RIGHT_SIGNAL_PIN, FRONT_LEFT_SIGNAL_PIN, SIDE_RIGHT_SIGNAL_PIN, SIDE_LEFT_SIGNAL_PIN);
	wait1Sec();//this will stop the program for 1 sec and do nothing else until 1 sec has passed



}



void wait1Sec()
{
	//wait for 1 sec
	while (!delayCounter.countReached())//if the counter stop value has not been reach, keep running the timer
	{
		mainTimer.Running();//run the timer, once the desired interval has passed, increment the period counter
	};
	delayCounter.counterReset();//once the counter stop value has been reached, reset the counter

}