//Used for AUXI - 2

/*
Outputs Compass Gauss Values for X, Y, and Z
*/

//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast

#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ Serial2
#else
	#define _SERIAL_DEBUG_CHANNEL_ Serial
#endif

#include <RoverConfig.h>


#include <Wire.h>
#include <LSM303.h>

LSM303 compass;

char report[80];

void setup()
{
	Serial.begin(PC_USB_BAUD_RATE);
	Serial2.begin(MAIN_BAUD_RATE);
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
