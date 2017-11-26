//Used for AUXI - 2

/*
Outputs Compass Gauss Values for X, Y, and Z
*/

//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast

#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ _MAIN_SERIAL_ //When using COMM Broadcast, reroute the PC USB output to the channel to MAIN instead
#else
	#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_
#endif

#include <RoverConfig.h>


#include <Wire.h>
#include <LSM303.h>

LSM303 compass;

char report[80];

void setup()
{
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	_MAIN_SERIAL_.begin(MAIN_BAUD_RATE);
	Wire.begin();
	compass.init();
	compass.enableDefault();
}

void loop()
{
	_SERIAL_DEBUG_CHANNEL_.println("X:\tY:\tZ:");

	while (1)
	{

		compass.read();
		snprintf(report, sizeof(report), "%6d\t%6d\t%6d",
		compass.m.x, compass.m.y, compass.m.z);
		_SERIAL_DEBUG_CHANNEL_.println(report);
		delay(100);
	}
}
