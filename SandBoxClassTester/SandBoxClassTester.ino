#include <Sandbox.h>
#include <DataType.h>

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
	byte num = 123;
	byte success;
	char tempCharArray[4] = "";//it needs to be at least 4 chars long for the null character
	success = DataType::byteToChars(num, tempCharArray, sizeof(tempCharArray));
	if (success)
	{
		Serial.println(tempCharArray);
	}
	while (1);
}
