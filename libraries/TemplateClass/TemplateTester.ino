#include <Template.h>


//Global Variables

Template template = Template();

RoverReset * resetArray[] = { &template };


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}

}


void loop() {

}
