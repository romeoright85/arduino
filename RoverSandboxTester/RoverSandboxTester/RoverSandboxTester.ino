#include <RoverSandbox.h>


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
	Serial.begin(9600);
}


void loop() {
	Serial.println("1");
	delay(1000);

}
