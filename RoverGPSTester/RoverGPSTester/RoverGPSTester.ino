//Used for NAVI - 1

#include <RoverGpsSensor.h>


//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast


//Note: To hook up the GPS for testing, look up GPS_DATA_TX_PIN, i.e. #define GPS_DATA_TX_PIN						15
//Uncomment to used fixed GPS example data to test parsing algorithm
//#define _DEBUG_PARSING_WITH_FIXED_DATA
//Uncomment to customize output data
#define _OUTPUT_STARTING_BLANK_LINE
#define _OUTPUT_SENTENCE_ID
#define _OUTPUT_DATA_FIX_TIME
#define _OUTPUT_LATITUDE
#define _OUTPUT_LONGITUDE
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

	Serial.begin(PC_USB_BAUD_RATE);
	Serial2.begin(MAIN_BAUD_RATE);
	Serial3.begin(GPS_BAUD_RATE);


	delay(1000);
#ifdef _DEBUG_COMM_BROADCAST
	Serial2.println(F("GPS Test Started"));
	Serial2.println();
	Serial2.println();
#else
	Serial.println(F("GPS Test Started"));
	Serial.println();
	Serial.println();
#endif
	
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
			#ifdef _DEBUG_COMM_BROADCAST
				Serial2.println();
			#else
				Serial.println();
			#endif			
		#endif

		//Print Valid GPS Data
		#ifdef _OUTPUT_SENTENCE_ID
			#ifdef _DEBUG_COMM_BROADCAST
				Serial2.print(F("Sentence ID: "));
				Serial2.println(roverGps->getGpsSentenceId());
			#else
				Serial.print(F("Sentence ID: "));
				Serial.println(roverGps->getGpsSentenceId());
			#endif			
		#endif

			
				
		#ifdef _OUTPUT_DATA_FIX_TIME
			#ifdef _DEBUG_COMM_BROADCAST
				Serial2.print(F("Time Of Data Fix: "));
			#else
				Serial.print(F("Time Of Data Fix: "));
			#endif
				dtostrf(roverGps->getGpsTimeWhenDataWasFixed(), 4, 3, numCharArray);//convert double to char array			
			#ifdef _DEBUG_COMM_BROADCAST
				Serial2.println(numCharArray);//print char array
			#else
				Serial.println(numCharArray);//print char array
			#endif
		#endif


		#ifdef _OUTPUT_LATITUDE
			#ifdef _DEBUG_COMM_BROADCAST
				Serial2.print(F("Latitude: "));
			#else
				Serial.print(F("Latitude: "));
			#endif

			dtostrf(roverGps->getGpsLatitude(), 5, 4, numCharArray);//convert double to char array
			//IT SHOULD WORK WITHOUT THE * before roverGps, TEST IT. sprintf(charBuffer, "%s %c", numCharArray, *roverGps->getGpsLatitudeDirection());//for getGpsLatitudeDirection(), remember to dereference the pointer to get it's value
			sprintf(charBuffer, "%s %c", numCharArray, roverGps->getGpsLatitudeDirection());//for getGpsLatitudeDirection(), remember to dereference the pointer to get it's value
			#ifdef _DEBUG_COMM_BROADCAST
				Serial2.println(charBuffer);
			#else
				Serial.println(charBuffer);
			#endif
		#endif

		#ifdef _OUTPUT_LONGITUDE
			#ifdef _DEBUG_COMM_BROADCAST
				Serial2.print(F("Longitude: "));
			#else
				Serial.print(F("Longitude: "));
			#endif
			dtostrf(roverGps->getGpsLongitude(), 5, 4, numCharArray);//convert double to char array
			//IT SHOULD WORK WITHOUT THE * before roverGps, TEST IT. sprintf(charBuffer, "%s %c", numCharArray, *roverGps->getGpsLongitudeDirection());//for getGpsLongitudeDirection(), remember to dereference the pointer to get it's value
			sprintf(charBuffer, "%s %c", numCharArray, roverGps->getGpsLongitudeDirection());//for getGpsLongitudeDirection(), remember to dereference the pointer to get it's value
			#ifdef _DEBUG_COMM_BROADCAST
				Serial2.println(charBuffer);
			#else
				Serial.println(charBuffer);
			#endif
			
		#endif

		#ifdef _OUTPUT_FIX_QUALITY
			#ifdef _DEBUG_COMM_BROADCAST
				Serial2.print(F("Fix Quality: "));
			#else
				Serial.print(F("Fix Quality: "));
			#endif			
			sprintf(charBuffer, "%u", roverGps->getGpsFixQuality());
			#ifdef _DEBUG_COMM_BROADCAST
				Serial2.println(charBuffer);
			#else
				Serial.println(charBuffer);
			#endif
		#endif

		#ifdef _OUTPUT_SATELLITES_TRACKED
			#ifdef _DEBUG_COMM_BROADCAST
				Serial2.print(F("Satellites Tracked: "));
			#else
				Serial.print(F("Satellites Tracked: "));
			#endif			
			sprintf(charBuffer, "%u", roverGps->getGpsSatellitesTracked());
			#ifdef _DEBUG_COMM_BROADCAST
				Serial2.println(charBuffer);
			#else
				Serial.println(charBuffer);
			#endif			
		#endif

		#ifdef _OUTPUT_GOOGLE_MAPS
			#ifdef _DEBUG_COMM_BROADCAST
				Serial2.print(F("For Google Maps: "));
				Serial2.println(roverGps->getGoogleMapsCoordinates());
			#else
				Serial.print(F("For Google Maps: "));
				Serial.println(roverGps->getGoogleMapsCoordinates());
			#endif			
		#endif

		#ifdef _OUTPUT_ENDING_BLANK_LINE
			//Add some white space/ new lines for clarity
			#ifdef _DEBUG_COMM_BROADCAST
				Serial2.println();
			#else
				Serial.println();
			#endif			
		#endif		
	}

#ifdef _OUTPUT_DATA_NOT_READY_STATUS
	else
	{
	#ifdef _DEBUG_COMM_BROADCAST
		Serial2.println(F("GPS Data Not Ready"));
	#else
		Serial.println(F("GPS Data Not Ready"));
	#endif
	}
#endif	

	delay(10);//need some delay between reads else the data gets noisy

}

boolean rxGPSData(RoverGpsSensor * roverGps) {

	//Note: Make sure processRxGPSData() is called between (before, after, or in) successive rxGPSData() function calls, as it will clear the string and reset the index (required for the code to work properly)


	byte numberOfAttempts = 0;//counts the number of times attempting to wait for a valid gps data string
	byte gpsCharactersToReceiveBeforeTimeout;//counts the number of characters received while waiting for the start of the gps data (i.e. $) before timing out
	boolean foundStart = false;
	boolean validGpsData = false;
	byte counter;


#ifndef _DEBUG_PARSING_WITH_FIXED_DATA
	while (numberOfAttempts <= GPS_RX_DATA_ATTEMPTS)
	{
	
		//Check availabiltiy of serial data
		if (Serial3.available() )
		{	
			//initialize the counter
			gpsCharactersToReceiveBeforeTimeout = 0;
			//Wait for the GPS start of data (i.e. $) else for a time out
			do			
			{				
				if ((char)Serial3.read() == '$')//look for the start of the GPS data (do NOT include it in the gps data string if found)
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
				counter = 0;

				//Gather the rest of the GPS String (AFTER the $, so $ is not included)
				while ( Serial3.available() && Serial3.peek() != '$' && counter <= GPS_SENTENCE_LENGTH)//while there is still data on the Serial RX Buffer, another sentence has not started, and the length is not over the max GPS sentence length
				{
	
			
						//Read one character of serial data at a time
						//Note: Must type cast the Serial.Read to a char since not saving it to a char type first					
						
						roverGps->appendToRxGPSData((char)Serial3.read());//construct the string one char at a time
															 //DEBUG: Add as needed
						counter++;
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

#else

	char debugFixedData[] = "GPGGA,142103.400,3916.2242,N,07636.6542,W,1,3,3.90,183.6,M,-33.6,M,,*6B";
	roverGps->setRxGPSData(debugFixedData, sizeof(debugFixedData) / sizeof(debugFixedData[0]));

	#ifdef _DEBUG_COMM_BROADCAST
		Serial2.print(F("Set to: "));//DEBUG
		Serial2.println(roverGps->getRxGPSData());//DEBUG			
	#else
		Serial.print(F("Set to: "));//DEBUG
		Serial.println(roverGps->getRxGPSData());//DEBUG			
	#endif
		
	//Process and validate GPS Data
	validGpsData = roverGps->processRxGPSData();

	

	//If the received gps data is valid, return validGpsData and exit out of this function (no more trial attempts needed)
	if (validGpsData)
	{
		return validGpsData;
	}
	//else the GPS data was invalid, so make another attempt to find valid GPS data				

#endif	

	
}