//Used for AUXI - 2
//Used for NAVI - 1
//Used for COMM - 4
//Used for MAIN - 3


//Checks to see order of else if statement and also if multiple statements will execute.


//Results: Only the first true statement in the else if block executes (as predicted)

#include <RoverConfig.h>

void setup()
{

	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	_PC_USB_SERIAL_.flush();//waits for any outgoing serial data to complete
	delay(50);

}

void loop()
{

	if (false)
	{
		//do nothing
	}
	else if (false)
	{
		_PC_USB_SERIAL_.println(F("1"));
	}
	else if (true)
	{
		_PC_USB_SERIAL_.println(F("2"));
	}
	else if (true)
	{
		_PC_USB_SERIAL_.println(F("3"));
	}
}



