//Used for NAVI - 1

#include <RoverGpsSensor.h>



//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast
#ifdef _DEBUG_COMM_BROADCAST
#define _SERIAL_DEBUG_CHANNEL_ _MAIN_SERIAL_
#else
#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_
#endif


//Note: To hook up the GPS for testing, look up GPS_DATA_TX_PIN, i.e. #define GPS_DATA_TX_PIN						15
//Uncomment to used fixed GPS example data to test parsing algorithm

//RECOMMENT ME LATER
//#define _DEBUG_PARSING_WITH_FIXED_DATA

/*
Example Output:

Sentence ID: GPGGA
Time Of Data Fix: 171446.410
Latitude (Dec-Dec NMEA): 3916.1023 N
Longitude (Dec-Dec NMEA): 7636.6616 W
Latitude (Dec-Deg): 39.2684
Longitude (Dec-Deg): -76.6110
Fix Quality: 1
Satellites Tracked: 6
For Google Maps: 39 16.1023 N, 076 36.6616 W

Sentence ID: GPGGA
Time Of Data Fix: 171446.800
Latitude (Dec-Dec NMEA): 3916.1023 N
Longitude (Dec-Dec NMEA): 7636.6621 W
Latitude (Dec-Deg): 39.2684
Longitude (Dec-Deg): -76.6110
Fix Quality: 1
Satellites Tracked: 6
For Google Maps: 39 16.1023 N, 076 36.6620 W
GPS Data Not Ready
GPS Data Not Ready
GPS Data Not Ready

Sentence ID: GPGGA
Time Of Data Fix: 171447.200
Latitude (Dec-Dec NMEA): 3916.1023 N
Longitude (Dec-Dec NMEA): 7636.6621 W
Latitude (Dec-Deg): 39.2684
Longitude (Dec-Deg): -76.6110
Fix Quality: 1
Satellites Tracked: 6
For Google Maps: 39 16.1022 N, 076 36.6623 W
GPS Data Not Ready
GPS Data Not Ready
GPS Data Not Ready


*/


//Uncomment to customize output data
#define _OUTPUT_STARTING_BLANK_LINE
#define _OUTPUT_SENTENCE_ID
#define _OUTPUT_DATA_FIX_TIME
#define _OUTPUT_LATITUDE_DEC_DEC_NMEA
#define _OUTPUT_LONGITUDE_DEC_DEC_NMEA
#define _OUTPUT_LATITUDE_DEC_DEG
#define _OUTPUT_LONGITUDE_DEC_DEG
#define _OUTPUT_FIX_QUALITY
#define _OUTPUT_SATELLITES_TRACKED
#define _OUTPUT_GOOGLE_MAPS
#define _OUTPUT_DATA_NOT_READY_STATUS


//Global Variables
RoverGpsSensor * roverGps = new RoverGpsSensor();

//flags for data ready
boolean gpsDataReady;
char numCharArray[10];
char charBuffer[100];

RoverReset * resetArray[] = {
	roverGps
};


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}

	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	_MAIN_SERIAL_.begin(MAIN_BAUD_RATE);
	_GPS_SERIAL_.begin(GPS_BAUD_RATE);


	delay(1000);
	_SERIAL_DEBUG_CHANNEL_.println(F("GPS Test Started"));
	_SERIAL_DEBUG_CHANNEL_.println();
	_SERIAL_DEBUG_CHANNEL_.println();
	
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
			_SERIAL_DEBUG_CHANNEL_.println();			
		#endif

		//Print Valid GPS Data
		#ifdef _OUTPUT_SENTENCE_ID
			_SERIAL_DEBUG_CHANNEL_.print(F("Sentence ID: "));
			_SERIAL_DEBUG_CHANNEL_.println(roverGps->getGpsSentenceId());
		#endif

			
				
		#ifdef _OUTPUT_DATA_FIX_TIME
				_SERIAL_DEBUG_CHANNEL_.print(F("Time Of Data Fix: "));
				dtostrf(roverGps->getGpsTimeWhenDataWasFixed(), 4, 3, numCharArray);//convert double to char array
				_SERIAL_DEBUG_CHANNEL_.println(numCharArray);//print char array
		#endif


		#ifdef _OUTPUT_LATITUDE_DEC_DEC_NMEA
			_SERIAL_DEBUG_CHANNEL_.print(F("Latitude (Dec-Dec NMEA): "));			
			dtostrf(roverGps->getGpsLatitude(DEC_DEC_NMEA), 5, 4, numCharArray);//convert double to char array
			//IT SHOULD WORK WITHOUT THE * before roverGps, TEST IT. sprintf(charBuffer, "%s %s", numCharArray, *roverGps->getGpsLatitudeDirection());//for getGpsLatitudeDirection(), remember to dereference the pointer to get it's value
			sprintf(charBuffer, "%s %s", numCharArray, roverGps->getGpsLatitudeDirection());//for getGpsLatitudeDirection(), remember to dereference the pointer to get it's value
			_SERIAL_DEBUG_CHANNEL_.println(charBuffer);
		#endif

		#ifdef _OUTPUT_LONGITUDE_DEC_DEC_NMEA
			_SERIAL_DEBUG_CHANNEL_.print(F("Longitude (Dec-Dec NMEA): "));			
			dtostrf(roverGps->getGpsLongitude(DEC_DEC_NMEA), 5, 4, numCharArray);//convert double to char array
			//IT SHOULD WORK WITHOUT THE * before roverGps, TEST IT. sprintf(charBuffer, "%s %s", numCharArray, *roverGps->getGpsLongitudeDirection());//for getGpsLongitudeDirection(), remember to dereference the pointer to get it's value
			sprintf(charBuffer, "%s %s", numCharArray, roverGps->getGpsLongitudeDirection());//for getGpsLongitudeDirection(), remember to dereference the pointer to get it's value
			_SERIAL_DEBUG_CHANNEL_.println(charBuffer);
		#endif

		#ifdef _OUTPUT_LATITUDE_DEC_DEG
		_SERIAL_DEBUG_CHANNEL_.print(F("Latitude (Dec-Deg): "));
		_SERIAL_DEBUG_CHANNEL_.println(roverGps->getGpsLatitude(DEC_DEG),4);//print with 4 decimal places
		#endif

		#ifdef _OUTPUT_LONGITUDE_DEC_DEG
		_SERIAL_DEBUG_CHANNEL_.print(F("Longitude (Dec-Deg): "));
		_SERIAL_DEBUG_CHANNEL_.println(roverGps->getGpsLongitude(DEC_DEG),4);//print with 4 decimal places
		#endif
		

		#ifdef _OUTPUT_FIX_QUALITY
			_SERIAL_DEBUG_CHANNEL_.print(F("Fix Quality: "));
			sprintf(charBuffer, "%u", roverGps->getGpsFixQuality());
			_SERIAL_DEBUG_CHANNEL_.println(charBuffer);
		#endif

		#ifdef _OUTPUT_SATELLITES_TRACKED
			_SERIAL_DEBUG_CHANNEL_.print(F("Satellites Tracked: "));
			sprintf(charBuffer, "%u", roverGps->getGpsSatellitesTracked());
			_SERIAL_DEBUG_CHANNEL_.println(charBuffer);
		#endif

		#ifdef _OUTPUT_GOOGLE_MAPS
			_SERIAL_DEBUG_CHANNEL_.print(F("For Google Maps: "));
			_SERIAL_DEBUG_CHANNEL_.println(roverGps->getGoogleMapsCoordinates());
		#endif

		#ifdef _OUTPUT_ENDING_BLANK_LINE
			//Add some white space/ new lines for clarity
			_SERIAL_DEBUG_CHANNEL_.println();
		#endif		
	}

#ifdef _OUTPUT_DATA_NOT_READY_STATUS
	else
	{
		_SERIAL_DEBUG_CHANNEL_.println(F("GPS Data Not Ready"));
	}
#endif	

	delay(10);//need some delay between reads else the data gets noisy

}//end loop

boolean rxGPSData(RoverGpsSensor * roverGps) {

	//Important Note: Make sure processRxGPSData() is called between (before, after, or in) successive rxGPSData() function calls, as it will clear the string and reset the index (required for the code to work properly)


	byte numberOfAttempts = 0;//counts the number of times attempting to wait for a valid gps data string
	byte gpsCharactersToReceiveBeforeTimeout;//counts the number of characters received while waiting for the start of the gps data (i.e. $) before timing out
	boolean foundStart = false;
	boolean validGpsData = false;
	byte gpsLengthCounter;


#ifndef _DEBUG_PARSING_WITH_FIXED_DATA
	while (numberOfAttempts <= GPS_RX_DATA_ATTEMPTS)
	{
	
		//Check availabiltiy of serial data
		if (_GPS_SERIAL_.available() )
		{	
			//initialize the counter
			gpsCharactersToReceiveBeforeTimeout = 0;
			//Wait for the GPS start of data (i.e. $) else for a time out
			do			
			{				
				if ((char)_GPS_SERIAL_.read() == '$')//look for the start of the GPS data (do NOT include it in the gps data string if found)
				{
					foundStart = true;
					delay(1);
					break;//break out of the loop since the header was found
				}
				delay(1);
			} while (gpsCharactersToReceiveBeforeTimeout <= GPS_SENTENCE_LENGTH);
			



			//If timeout has NOT occured, keep processing the GPS data
			if (foundStart)
			{
				//initialize the counter
				gpsLengthCounter = 0;

				//Gather the rest of the GPS String (AFTER the $, so $ is not included)
				while ( _GPS_SERIAL_.available() && _GPS_SERIAL_.peek() != '$' && gpsLengthCounter <= GPS_SENTENCE_LENGTH)//while there is still data on the Serial RX Buffer, another sentence has not started, and the length is not over the max GPS sentence length
				{
	
			
						//Read one character of serial data at a time
						//Note: Must type cast the _PC_USB_SERIAL_.Read to a char since not saving it to a char type first					
						
						roverGps->appendToRxGPSData((char)_GPS_SERIAL_.read());//construct the string one char at a time
															 //DEBUG: Add as needed
						gpsLengthCounter++;
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
			//else if no start character was foind and time out has occurred, go to the next trial		

		}//end if
		//else if there is no serial data available do nothing, go to the next trial

		//Increment trial counter
		numberOfAttempts++;

	}//end while

	 //Reached the max attempts to receive valid GPS Data
	return validGpsData;//If the code has reached this point, this value will be false. No valid GPS data found, and max attempts to find it has been reached.

#else

	char debugFixedData[] = "GPGGA,142103.400,3916.2242,N,07636.6542,W,1,3,3.90,183.6,M,-33.6,M,,*6B";
	roverGps->setRxGPSData(debugFixedData, sizeof(debugFixedData));

	_SERIAL_DEBUG_CHANNEL_.print(F("Set to: "));//DEBUG
	_SERIAL_DEBUG_CHANNEL_.println(roverGps->getRxGPSData());//DEBUG			
		
	//Process and validate GPS Data
	validGpsData = roverGps->processRxGPSData();

	

	//If the received gps data is valid, return validGpsData and exit out of this function (no more trial attempts needed)
	if (validGpsData)
	{
		return validGpsData;
	}
	//else the GPS data was invalid, so make another attempt to find valid GPS data				

#endif	

	
}//end rxGPSData