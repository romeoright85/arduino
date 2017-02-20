//Used for AUXI - 2

/*
Outputs Compass Gauss Values for X, Y, and Z
*/

//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast

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

#ifdef _DEBUG_COMM_BROADCAST
	Serial2.println("X:\tY:\tZ:");
#else
	Serial.println("X:\tY:\tZ:");
#endif
	

	while (1)
	{

		compass.read();
		snprintf(report, sizeof(report), "%6d\t%6d\t%6d",
		compass.m.x, compass.m.y, compass.m.z);
#ifdef _DEBUG_COMM_BROADCAST
		Serial2.println(report);
#else
		Serial.println(report);
#endif		
		delay(100);
	}
}
