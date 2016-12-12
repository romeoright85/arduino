#include <RoverGpsSensor.h>

//#define _DEBUG_ //Uncomment this flag to turn on debug outputs
//#define _DEBUG2_ //Uncomment this flag to turn on more debug outputs


//Global Variables
RoverGpsSensor * roverGps = new RoverGpsSensor();

//flags for data ready
boolean gpsDataReady;

RoverReset * resetArray[] = {
	roverGps
};


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}

	Serial.begin(PC_USB_BAUD_RATE);
	Serial3.begin(GPS_BAUD_RATE);

}


void loop() {
	

	//reset flags
	gpsDataReady = false;
		
	//Receive (via serial) and process gps data
	gpsDataReady = rxGPSData(roverGps);

	if (gpsDataReady)
	{
		//Print Valid GPS Data
		Serial.print(F("Time Of Data Fix: "));
		Serial.println((String)roverGps->getGpsTimeWhenDataWasFixed());

		Serial.print(F("GPS Status: "));
		Serial.println((String)roverGps->getGpsStatus());


		Serial.print(F("Latitude: "));
		Serial.print((String)roverGps->getGpsLatitude());
		Serial.println((String)roverGps->getGpsLatitudeDirection());

		Serial.print(F("Longitude: "));
		Serial.print((String)roverGps->getGpsLongitude());		
		Serial.println((String)roverGps->getGpsLongitudeDirection());


		Serial.print(F("Fix Quality: "));
		Serial.println((String)roverGps->getGpsFixQuality());

		Serial.print(F("Satellites Tracked: "));
		Serial.println((String)roverGps->getGpsSatellitesTracked());


		Serial.print(F("Horiontal Dilution Of Position: "));
		Serial.println((String)roverGps->getGpsHorizontalDilution());


		Serial.print(F("Altitude Above Mean Sea Level: "));
		Serial.print((String)roverGps->getGpsAltitude());
		Serial.println((String)roverGps->getGpsAltitudeUnit());

		Serial.print(F("Speed"));
		Serial.println((String)roverGps->getGpsSpeed());
		

		Serial.print(F("Height OF Geoid"));
		Serial.print((String)roverGps->getGpsGeoidHeight());
		Serial.println((String)roverGps->getGpsGeoidHeightUnit());

		Serial.print(F("Track Angle in degrees True"));
		Serial.println((String)roverGps->getGpsTrackAngle());


		Serial.print(F("Date"));
		Serial.println((String)roverGps->getGpsDate());
		


	}


	else
	{
		Serial.println(F("GPS Data Not Ready"));
	}
	//Add some white space/ new lines for clarity
	Serial.println();
	Serial.println();
	
	delay(1000);

}

boolean rxGPSData(RoverGpsSensor * roverGps) {

	byte numberOfAttempts = 0;//counts the number of times attempting to wait for a valid gps data string
	byte gpsCharactersToReceiveBeforeTimeout = 0;//counts the number of characters received while waiting for the start of the gps data (i.e. $) before timing out
	boolean validGpsData = false;
	

	while (numberOfAttempts <= GPS_RX_DATA_ATTEMPTS)
	{
		//Check availabiltiy of serial data
		if (Serial3.available() > 1)
		{	
			//Wait for the GPS start of data (i.e. $) else for a time out
			do			
			{				
				if ((char)Serial.read() == '$')//look for the start of the GPS data (do NOT include it in the gps data string if found)
				{
					break;//break out of the loop since the header was found
				}
			} while (gpsCharactersToReceiveBeforeTimeout <= GPS_CHARACTERS_TO_RX_BEFORE_TIMEOUT);		


			//If timeout has NOT occured, keep processing the GPS data
			if (gpsCharactersToReceiveBeforeTimeout <= GPS_CHARACTERS_TO_RX_BEFORE_TIMEOUT)
			{


				//Gather the rest of the GPS String (AFTER the $, so $ is not included)
				while (Serial3.available() > 0)//while there is still data on the Serial RX Buffer
				{
					//Read one character of serial data at a time
					//Note: Must type cast the Serial.Read to a char since not saving it to a char type first					
					roverGps->appendToRxGPSData((char)Serial.read());//construct the string one char at a time
					//DEBUG: Add as needed//delay(1);//add a 1 us delay between each transmission
				}//end while

							

				//Process and validate GPS Data
				validGpsData = roverGps->processRxGPSData();
				

				//If the received gps data is valid, return validGpsData and exit out of this function (no more trial attempts needed)
				if (validGpsData)
				{
					return validGpsData;
				}
				//else the GPS data was invalid, so make another attempt to find valid GPS data

			}//end if
			//else if time out has occurred, go to the next trial		

		}//end if
		//else if there is no serial data available do nothing, go to the next trial

		//Increment trial counter
		numberOfAttempts++;

	}//end while
	//Reached the max attempts to receive valid GPS Data
	return validGpsData;//If the code has reached this point, this value will be false. No valid GPS data found, and max attempts to find it has been reached.
}


























