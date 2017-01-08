#include <RoverGpsSensor.h>

//Debug code used to review what the GPS module is outputting and how it's received by the Serial read.


//Uncomment debug flags to view the data in different ways
#define _DEBUG_OUTPUT_GPS_AS_RX
//#define _DEBUG_OUTPUT_GPS_NEWLINES


void setup()
{
	Serial.begin(PC_USB_BAUD_RATE);
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
		Serial.print(temp);	
	}
	#endif


	#ifdef _DEBUG_OUTPUT_GPS_NEWLINES

		//Check availabiltiy of serial data
		if (Serial3.available() > 0)
		{
			temp = (char)Serial3.read();
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
		
		}
	#endif
	


}
