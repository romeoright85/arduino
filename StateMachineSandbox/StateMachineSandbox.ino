#include <StateMachine.h>


//Global Variables



StateMachine * stateMachine = new StateMachine();



RoverReset * resetArray[] = {
	stateMachine
};





void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}

	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	
}


void loop() {
	_PC_USB_SERIAL_.println(F("Loop"));
	stateMachine->run();
	delay(100);
}
