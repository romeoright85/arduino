//Used for NAVI - 1


#include <LedController_NAVI.h>
#include <RoverConfig.h>

//Global Variables

LedController_NAVI * ledController_NAVI = new LedController_NAVI();

RoverReset * resetArray[] = {
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
