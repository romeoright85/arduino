//Used for NAVI - 1

#include <RoverGpsSensor.h>

//Debug code used to review what the GPS module is outputting and how it's received by the Serial read.


//Uncomment debug flags to view the data in different ways
#define _DEBUG_OUTPUT_GPS_AS_RX
//#define _DEBUG_OUTPUT_GPS_NEWLINES
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast

#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ _MAIN_SERIAL_ //When using COMM Broadcast, reroute the PC USB output to the channel to MAIN instead
#else
	#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_
#endif

#include <RoverConfig.h>


void setup()
{
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	_MAIN_SERIAL_.begin(MAIN_BAUD_RATE);
	_GPS_SERIAL_.begin(GPS_BAUD_RATE);
}

void loop()
{
	char temp;
	#ifdef _DEBUG_OUTPUT_GPS_AS_RX
	//Check availabiltiy of serial data
	if (_GPS_SERIAL_.available() > 0)
	{
		temp = (char)_GPS_SERIAL_.read();
		_SERIAL_DEBUG_CHANNEL_.print(temp);
	}
	#endif


	#ifdef _DEBUG_OUTPUT_GPS_NEWLINES

		//Check availabiltiy of serial data
		if (_GPS_SERIAL_.available() > 0)
		{
			temp = (char)_GPS_SERIAL_.read();
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
