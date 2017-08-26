#include <Sandbox.h>
#include <DataType.h>
#include <RoverConfig.h>


Sandbox * sandboxObject = new Sandbox();

char charArray[10];
//Latitude: 3916.10N
//	Longitude : 7636.66W


void setup()
{

	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);

}

void loop()
{	
	byte num = 10;
	byte success;
	char tempCharArray[4] = "";//it needs to be at least 4 chars long for the null character
	success = DataType::byteToChars(num, tempCharArray, sizeof(tempCharArray));
	if (success)
	{
		_PC_USB_SERIAL_.println(tempCharArray);
	}
	while (1);
}
