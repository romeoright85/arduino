//Used for NAVI - 1

#include <RoverGpsSensor.h>

//Debug code used to review what the GPS module is outputting and how it's received by the Serial read.


//Uncomment debug flags to view the data in different ways
#define _DEBUG_OUTPUT_GPS_AS_RX
//#define _DEBUG_OUTPUT_GPS_NEWLINES
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast

#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ _MAIN_SERIAL_
#else
	#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_
#endif

void setup()
{
	Serial.begin(PC_USB_BAUD_RATE);
	Serial2.begin(MAIN_BAUD_RATE);
	Serial3.begin(GPS_BAUD_RATE);	
}

void loop()
{
	char temp;
	#ifdef _DEBUG_OUTPUT_GPS_AS_RX
	//Check availabiltiy of serial data
	if (Serial3.available() > 0)
	{
		temp = (char)Serial3.read();
		_SERIAL_DEBUG_CHANNEL_.print(temp);
	}
	#endif


	#ifdef _DEBUG_OUTPUT_GPS_NEWLINES

		//Check availabiltiy of serial data
		if (Serial3.available() > 0)
		{
			temp = (char)Serial3.read();
			if (temp == '\n')
			{
				_SERIAL_DEBUG_CHANNEL_.println();
				_SERIAL_DEBUG_CHANNEL_.println(F("n"));
			}//end if
			else if (temp == '\r')
			{
				_SERIAL_DEBUG_CHANNEL_.println();
				_SERIAL_DEBUG_CHANNEL_.println(F("r"));
			}//end else if
			else
			{
				_SERIAL_DEBUG_CHANNEL_.print(temp);
			}//end else
		}
	#endif
	


}
