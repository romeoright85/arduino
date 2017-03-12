//Used for AUXI - 2
//Used for NAVI - 1
//Used for COMM - 4
//Used for MAIN - 3


#include <Template.h>


//Global Variables

Template * template = new Template();

RoverReset * resetArray[] = {
	template
};


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	
	Serial.begin(PC_USB_BAUD_RATE);
	
}


void loop() {

}
