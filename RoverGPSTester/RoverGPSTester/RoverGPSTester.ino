//Used for NAVI - 1

#include <RoverGpsSensor.h>

//Uncomment to customize output data
#define _OUTPUT_STARTING_BLANK_LINE
//#define _OUTPUT_SENTENCE_ID
#define _OUTPUT_DATA_FIX_TIME
#define _OUTPUT_LATITUDE
#define _OUTPUT_LONGITUDE
#define _OUTPUT_FIX_QUALITY
#define _OUTPUT_SATELLITES_TRACKED
#define _OUTPUT_HORIZONTAL_DILUTION_OF_POSITION
#define _OUTPUT_ALTITUDE_ABOVE_MEAN_SEA_LEVEL
#define _OUTPUT_HEIGHT_OF_GEOID
#define _OUTPUT_RXD_CHECKSUM
#define _OUTPUT_GOOGLE_MAPS
#define _OUTPUT_ENDING_BLANK_LINE
#define _OUTPUT_DATA_NOT_READY_STATUS



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


	delay(1000);
	Serial.println(F("GPS Test Started"));
	Serial.println();
	Serial.println();
}


void loop() {
	

	//reset flags
	gpsDataReady = false;
		
	//Receive (via serial) and process gps data
	gpsDataReady = rxGPSData(roverGps);

	if (gpsDataReady)
	{
		#ifdef _OUTPUT_STARTING_BLANK_LINE
			//Add some white space/ new lines for clarity
			Serial.println();
		#endif

		//Print Valid GPS Data
		#ifdef _OUTPUT_SENTENCE_ID
			Serial.print(F("Sentence ID: "));
			Serial.println((String)roverGps->getGpsSentenceId());
		#endif

			
				
		#ifdef _OUTPUT_DATA_FIX_TIME
			Serial.print(F("Time Of Data Fix: "));
			Serial.println((String)roverGps->getGpsTimeWhenDataWasFixed());
		#endif


		#ifdef _OUTPUT_LATITUDE
			Serial.print(F("Latitude: "));
			Serial.print((String)roverGps->getGpsLatitude());
			Serial.println((String)roverGps->getGpsLatitudeDirection());
		#endif

		#ifdef _OUTPUT_LONGITUDE
			Serial.print(F("Longitude: "));
			Serial.print((String)roverGps->getGpsLongitude());		
			Serial.println((String)roverGps->getGpsLongitudeDirection());
		#endif

		#ifdef _OUTPUT_FIX_QUALITY
			Serial.print(F("Fix Quality: "));
			Serial.println((String)roverGps->getGpsFixQuality());
		#endif

		#ifdef _OUTPUT_SATELLITES_TRACKED
			Serial.print(F("Satellites Tracked: "));
			Serial.println((String)roverGps->getGpsSatellitesTracked());
		#endif

		#ifdef _OUTPUT_HORIZONTAL_DILUTION_OF_POSITION
			Serial.print(F("Horiontal Dilution Of Position: "));
			Serial.println((String)roverGps->getGpsHorizontalDilution());
		#endif

		#ifdef _OUTPUT_ALTITUDE_ABOVE_MEAN_SEA_LEVEL
			Serial.print(F("Altitude Above Mean Sea Level: "));
			Serial.print((String)roverGps->getGpsAltitude());
			Serial.println((String)roverGps->getGpsAltitudeUnit());
		#endif

		#ifdef _OUTPUT_HEIGHT_OF_GEOID
			Serial.print(F("Height OF Geoid: "));
			Serial.print((String)roverGps->getGpsGeoidHeight());
			Serial.println((String)roverGps->getGpsGeoidHeightUnit());
		#endif

		#ifdef _OUTPUT_RXD_CHECKSUM
			Serial.print(F("Received Checksum: "));
			Serial.println((String)roverGps->getGpsReceivedChecksum());
		#endif


		#ifdef _OUTPUT_GOOGLE_MAPS
			Serial.print(F("For Google Maps: "));		
			Serial.println((String)roverGps->getGoogleMapsCoordinates());
		#endif

		#ifdef _OUTPUT_ENDING_BLANK_LINE
			//Add some white space/ new lines for clarity
			Serial.println();
		#endif
		
	}

#ifdef _OUTPUT_DATA_NOT_READY_STATUS
	else
	{
		Serial.println(F("GPS Data Not Ready"));
	}
#endif	

	delay(10);//need some delay between reads else the data gets noisy

}

boolean rxGPSData(RoverGpsSensor * roverGps) {

	byte numberOfAttempts = 0;//counts the number of times attempting to wait for a valid gps data string
	byte gpsCharactersToReceiveBeforeTimeout = 0;//counts the number of characters received while waiting for the start of the gps data (i.e. $) before timing out
	boolean validGpsData = false;
	

	while (numberOfAttempts <= GPS_RX_DATA_ATTEMPTS)
	{
		//Check availabiltiy of serial data
		if (Serial3.available() >= 1)
		{	
			//Wait for the GPS start of data (i.e. $) else for a time out
			do			
			{				
				if ((char)Serial3.read() == '$')//look for the start of the GPS data (do NOT include it in the gps data string if found)
				{
					break;//break out of the loop since the header was found
				}
			} while (gpsCharactersToReceiveBeforeTimeout <= GPS_CHARACTERS_TO_RX_BEFORE_TIMEOUT);		
			


			//If timeout has NOT occured, keep processing the GPS data
			if (gpsCharactersToReceiveBeforeTimeout <= GPS_CHARACTERS_TO_RX_BEFORE_TIMEOUT)
			{


				//Gather the rest of the GPS String (AFTER the $, so $ is not included)
				while ( Serial3.available() )//while there is still data on the Serial RX Buffer				
				{
					//Read one character of serial data at a time
					//Note: Must type cast the Serial.Read to a char since not saving it to a char type first					
					roverGps->appendToRxGPSData((char)Serial3.read());//construct the string one char at a time
					//DEBUG: Add as needed
					delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
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


























