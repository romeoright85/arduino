#include <RoverSandbox.h>
#include <RoverConfig.h>

//Global Variables



RoverSandbox * roverSandbox = new RoverSandbox();

RoverReset * resetArray[] = { roverSandbox };
boolean test = false;

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
}


void loop() {
	_PC_USB_SERIAL_.println("1");
	delay(1000);

}
