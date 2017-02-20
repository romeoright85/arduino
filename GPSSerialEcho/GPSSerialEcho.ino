//Used for NAVI - 1

#include <RoverGpsSensor.h>

//Debug code used to review what the GPS module is outputting and how it's received by the Serial read.


//Uncomment debug flags to view the data in different ways
#define _DEBUG_OUTPUT_GPS_AS_RX
//#define _DEBUG_OUTPUT_GPS_NEWLINES
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast


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
	#ifdef _DEBUG_COMM_BROADCAST
		Serial2.print(temp);
	#else
		Serial.print(temp);
	#endif		
	}
	#endif


	#ifdef _DEBUG_OUTPUT_GPS_NEWLINES

		//Check availabiltiy of serial data
		if (Serial3.available() > 0)
		{
			temp = (char)Serial3.read();
		#ifdef _DEBUG_COMM_BROADCAST
			if (temp == '\n')
			{
				Serial2.println();
				Serial2.println(F("n"));
			}
			if (temp == '\r')
			{
				Serial2.println();
				Serial2.println(F("r"));
			}
			else
			{
				Serial2.print(temp);
			}
		#else
			if (temp == '\n')
			{
				Serial.println();
				Serial.println(F("n"));
			}
			if (temp == '\r')
			{
				Serial.println();
				Serial.println(F("r"));
			}
			else
			{
				Serial.print(temp);
			}
		#endif		
		}
	#endif
	


}
