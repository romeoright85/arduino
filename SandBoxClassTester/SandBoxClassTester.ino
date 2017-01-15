#include <Sandbox.h>

Sandbox * sandboxObject = new Sandbox();

char charArray[10];
//Latitude: 3916.10N
//	Longitude : 7636.66W


void setup()
{

	Serial.begin(9600);

}

void loop()
{	



	strncpy(charArray, "hello", strlen("hello")+1);
	sandboxObject->write(charArray, sizeof(charArray)/sizeof(charArray[0]));
	Serial.println(sandboxObject->read());
		



	Serial.print(sandboxObject->getLat());
	Serial.println(sandboxObject->getLatUnit());
	
	Serial.println();

	Serial.print(sandboxObject->getLon());
	Serial.println(sandboxObject->getLonUnit());

	while (1);
}
