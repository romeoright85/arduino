#include <UnoLoopback.h>


//Data Rates
#define BAUD_RATE 9600//baud rate
UnoLoopback unoLoopback(BAUD_RATE);

RoverReset * resetArray[] = { &unoLoopback };


void setup() {
	//resetting all objects in this sketch
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		if (!resetArray[i] == NULL)//if the object isn't null
		{
			resetArray[i]->reset();//reset the object	
		}

	}
    unoLoopback.startComms();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  unoLoopback.startLoopback();
  
}
