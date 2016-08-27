#include <UnoLoopback.h>


//Data Rates
#define BAUD_RATE 9600//baud rate
UnoLoopback unoLoopback(BAUD_RATE);

RoverReset * resetArray[] = { &unoLoopback };


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
    unoLoopback.startComms();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  unoLoopback.startLoopback();
  
}
