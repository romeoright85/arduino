#include <RoverSandbox.h>


//Global Variables


//RoverSandbox * roverSandbox = new RoverSandbox();
RoverSandbox * roverSandbox = NULL;

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

	delay(100);
	Serial.println("Create object");
	roverSandbox = new RoverSandbox();
	//Serial.println("Reset Object");
	//roverSandbox->reset();
	//Serial.println("Reset Counter");
	//RoverSandbox::resetObjectInstances();
	Serial.println("Destroy object");
	delete roverSandbox;
	//Serial.println("NULL ptr");
	//roverSandbox = NULL;
	//Serial.println("Destroy object");
	//roverSandbox->~RoverSandbox();

	delay(5000);
}
