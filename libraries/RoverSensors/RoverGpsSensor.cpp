#include <RoverGpsSensor.h>


RoverGpsSensor::RoverGpsSensor()
{
	this->reset();
}
RoverGpsSensor::~RoverGpsSensor()
{
	//do nothing
}
void RoverGpsSensor::reset()
{
	
	//Flags	
	//GPS Helper Variables	
	this->clearGpsDataArray();
	//GPS Received Data	
	this->clearRxGpsVariables();
	
}
void RoverGpsSensor::clearGpsDataArray()
{	
	memset(this->_gpsDataArray,0,sizeof(this->_gpsDataArray));	
}
void RoverGpsSensor::clearRxGpsVariables()
{
	
	this->_rxdCharacterIndex = 0;
	
	memset(this->_rxData,0,sizeof(this->_rxData));		
}
void RoverGpsSensor::appendToRxGPSData(char dataIn)
{	
		
	if(this->_rxdCharacterIndex <= GPS_DATA_CHAR_BUFFER_SIZE)//make sure there is no buffer overflow
	{
		this->_rxData[this->_rxdCharacterIndex] = dataIn;
		this->_rxdCharacterIndex++;//move the cursor to the next position in the array		
	}
	else
	{
		Serial.println(F("GpsBuffOvrFlw"));
	}
	
	
}
void RoverGpsSensor::setRxGPSData(char * dataString, byte arraySize)
{			
	strncpy(this->_rxData, dataString, arraySize);
}

char * RoverGpsSensor::getRxGPSData()
{
	return this->_rxData;
}
byte RoverGpsSensor::getRxGPSDataLength()
{
	return CharArray::stringSize(this->_rxData,sizeof(this->_rxData));
}
boolean RoverGpsSensor::processRxGPSData()
{

	//Note: The data starts after the $ since the function in the .ino (rxGPSData) that runs before this code will strip out the $	

	//Example Raw Data: $GPGGA,142103.400,3916.2242,N,07636.6542,W,1,3,3.90,183.6,M,-33.6,M,,*6B
	//Example Data Received by this function: GPGGA,142103.400,3916.2242,N,07636.6542,W,1,3,3.90,183.6,M,-33.6,M,,*6B	
		

	
	#ifdef _DEBUG_OUTPUT_PRE_FILTERED_RAW_RX_DATA
		Serial.println(this->_rxData);//DEBUG	
	#endif


	//Initialize variable(s)		
	this->clearGpsDataArray();
	byte startIndex = 0;
	byte endIndex = 0;
	int stringSize = 0;	
	char dataStringToParse[GPS_DATA_CHAR_BUFFER_SIZE];
	
	

	stringSize = CharArray::stringSize(this->_rxData, sizeof(this->_rxData)/sizeof(this->_rxData[0]));


	
	//if no null terminated character found, it's a bad string so end the function
	if( stringSize < 0)
	{
		
		this->clearRxGpsVariables();//clear the gps data
		return false;//do nothing if the data isn't desired
	}
	


	//Make a copy of the data char array. This copy will be manipulated.	
	strncpy(dataStringToParse, this->_rxData, stringSize);	//copy rxData to the temp buffer char array dataStringToParse
	



	//==Data Filtering==
	//Note: Only keep and process GPGGA data. Ignore everything else.
	if ( !dataPassedFiltering(dataStringToParse, stringSize) )
	{		
		
		#ifdef _DEBUG_OUTPUT_FILTERED_DATA_STATUS
			Serial.println(F("Filtered Out"));
		#endif
		
		this->clearRxGpsVariables();//clear the gps data
		return false;//do nothing if the data isn't desired
	}//end if
	//else continue

	#ifdef _DEBUG_OUTPUT_POST_FILTERED_RAW_RX_DATA
		Serial.println(dataStringToParse);//DEBUG	
	#endif



					
	//==Parsing and extracting the GPS GPGGA data==
	
	//Note: The dataStringToParse starts after the $ since the function in the .ino (rxGPSData) that runs before this code will strip out the $	

		
	//Example Data Received by this function: GPGGA,142103.400,3916.2242,N,07636.6542,W,1,3,3.90,183.6,M,-33.6,M,,*6B	
	
	
	//Parse and extract the GPS data string for GPGGA
	for (byte i = 0; i < GPS_GPGGA_FIELDS; i++) 
	{
	


		//Get the position of the next comma
		endIndex = CharArray::indexOf(dataStringToParse, stringSize, ',', startIndex);
		
		//if no comma found, the function would have returned a -1, so break out of the for loop early when a -1 was found
		if( endIndex < 0)
		{
			break;
		}
		
		//Grab the substring the start and the first commas (for the first field) or the substring between two commas
		CharArray::substring(dataStringToParse, stringSize, startIndex, endIndex, this->_gpsDataArray[i]);
				
		#ifdef _DEBUG_OUTPUT_PARSING_PROCESS
			Serial.print(F("Data Being Parsed: "));//DEBUG
			Serial.println(dataStringToParse);//DEBUG
			Serial.print(F("Start Index: "));//DEBUG
			Serial.println(startIndex);//DEBUG
			Serial.print(F("End Index: "));//DEBUG
			Serial.println(endIndex);//DEBUG
			Serial.print(F("Parsed Data: "));//DEBUG
			Serial.println(this->_gpsDataArray[i]);//DEBUG
		#endif			


		//Prepare the data for the next interation of the loop by skipping over the current comma
		CharArray::substring(dataStringToParse, stringSize, endIndex+1, dataStringToParse);
				

		
	}//end for


	#ifdef _DEBUG_OUTPUT_PARSED_GPS_DATA_ARRAY

		Serial.println("==BEGIN==");
		for (byte i = 0; i < GPS_GPGGA_FIELDS; i++)
		{
			Serial.println(this->_gpsDataArray[i]);
		}
		Serial.println("==END==");
		Serial.println();

	#endif

	//Clear the GPS data string for future use
	this->clearRxGpsVariables();
	
	//Return from the function if the GPS data is invalid (status is extracted from the parsed GPS data)
	if(!this->isGpsDataValid())
	{
		return false;
	}//end if
	else
	{	
		return true;
	}//end else					
	

	
}
boolean RoverGpsSensor::isGpsDataValid()
{	
	//Checks the GPS Status and the Fix Quality to see if the data is valid
			
	if(this->getGpsFixQuality() > 0)//if the Fix Quality has a valid value (non zero)
	{
		return true;
	}//end if
	else //the Fix Quality is 0, so it is invalid
	{
		return false;
	}//end else	
}
char * RoverGpsSensor::getGpsSentenceId()
{
	return this->_gpsDataArray[GPS_GPGGA_INDEX_OF_SENTENCE_ID];
}
byte RoverGpsSensor::getGpsSentenceIdLength()
{
	return CharArray::stringSize(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_SENTENCE_ID],sizeof(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_SENTENCE_ID]));
}
double RoverGpsSensor::getGpsTimeWhenDataWasFixed()
{	
	return atof(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_DATA_FIX_TIME]);
}

double RoverGpsSensor::getGpsLatitude(byte format)
{	
	if(format == DEC_DEC_NMEA)
	{
		return atof(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LATITUDE]);	
	}//end if
	else if(format == DEC_DEG)
	{
		double value = atof(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LATITUDE]);					
			
		byte degrees;
		double degreesDecimal;
	
		/*
			The latitude data NMEA format is ddmm.mmmm, n/s "
			decimal degrees = dd + mm.mmmm/60
			Then use the direction to determine if the number is positive or negative.
			https://community.oracle.com/thread/3619431
		*/
				
		degrees = value / 100;//the fractional part is truncated off since it's a byte
		degreesDecimal = (value - (degrees * 100))/60;
		
		degrees = value / 100;//the fractional part is truncated off since it's a byte
		degreesDecimal = (value - (degrees * 100))/60;
		
		if(strcmp(this->getGpsLatitudeDirection(),"N") == 0)			
		{
			return degrees + degreesDecimal;
		}//end if
		else // the direction is South
		{
			return -1 * (degrees + degreesDecimal);
		}//end else	
				
	}//end else if
	else
	{
		return -1.2345;//invalid error value
	}//end else
	
}
char * RoverGpsSensor::getGpsLatitudeDirection()
{	
	return this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LATITUDE_DIRECTION];
}
byte RoverGpsSensor::getGpsLatitudeDirectionLength()
{	
	return CharArray::stringSize(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LATITUDE_DIRECTION],sizeof(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LATITUDE_DIRECTION]));
}
double RoverGpsSensor::getGpsLongitude(byte format)
{	
	if(format == DEC_DEC_NMEA)
	{
		return atof(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LONGITUDE]);		
	}//end if
	else if(format == DEC_DEG)
	{
		double value = atof(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LONGITUDE]);					
		byte degrees;
		double degreesDecimal;

		/*
			The longitude data NMEA format is (d)ddmm.mmmm, e/w"
			decimal degrees = (d)dd + mm.mmmm/60
			Then use the direction to determine if the number is positive or negative.			
			https://community.oracle.com/thread/3619431
		*/
		
		degrees = value / 100;//the fractional part is truncated off since it's a byte
		degreesDecimal = (value - (degrees * 100))/60;
		if(strcmp(this->getGpsLongitudeDirection(),"E") == 0)			
		{
			return degrees + degreesDecimal;
		}//end if
		else // the direction is West
		{
			return -1 * (degrees + degreesDecimal);
		}//end else	
				
	}//end else if
	else
	{
		return -1.2345;//invalid error value
	}//end else

	
}
char * RoverGpsSensor::getGpsLongitudeDirection()
{	
	return this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LONGITUDE_DIRECTION];
}
byte RoverGpsSensor::getGpsLongitudeDirectionLength()
{	
	return CharArray::stringSize(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LONGITUDE_DIRECTION],sizeof(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LONGITUDE_DIRECTION]));
}
byte RoverGpsSensor::getGpsFixQuality()
{		
	return atoi(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_FIX_QUALITY]);
}
byte RoverGpsSensor::getGpsSatellitesTracked()
{
	return atoi(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_SATELLITES_TRACKED]);	
}
char * RoverGpsSensor::getGoogleMapsCoordinates()
{
	
	//Example Google Maps Format: 39 16.10 N, 76 36.66 W
		
	//Use the original string (i.e.  this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LATITUDE] and not getGpsLatitude()) before it's converted to a double for latitude and longitude to prevent round off or conversion errors
	
	//Get the string sizes
	int stringSizeLatitude = CharArray::stringSize(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LATITUDE], sizeof(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LATITUDE])/sizeof(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LATITUDE][0]));
	int stringSizeLongitude = CharArray::stringSize(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LONGITUDE], sizeof(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LONGITUDE])/sizeof(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LONGITUDE][0]));
	
	//Create temp/placeholder char array
	char tempCharArray[GPS_DATA_CHAR_BUFFER_SIZE]; 
	
			
	//Constructing the _googleMapsCoordinates char array
		
	//Remember: Latitude is 0 to 90 and Longitude is 0 to 180. So Grab the first two characters for longitude and the first three characters for longitude.
			
	//Grab the first two characters of latitude, into the this->_googleMapsCoordinates
	CharArray::substring(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LATITUDE], stringSizeLatitude, 0, 2, this->_googleMapsCoordinates);
	//Add a space to the this->_googleMapsCoordinates
	strcat(this->_googleMapsCoordinates, " ");
	//Grab the remaining characters of latitude, into the tempCharArray
	CharArray::substring(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LATITUDE], stringSizeLatitude, 2, tempCharArray);
	//Concatenate the tempCharArray into the this->_googleMapsCoordinates
	strcat(this->_googleMapsCoordinates, tempCharArray);
	//Add a space to the this->_googleMapsCoordinates
	strcat(this->_googleMapsCoordinates, " ");	
	//Concatenate the Latitude Direction into the this->_googleMapsCoordinates
	strcat(this->_googleMapsCoordinates, this->getGpsLatitudeDirection());
	//Add a space and comma to the this->_googleMapsCoordinates
	strcat(this->_googleMapsCoordinates, ", ");
	//Grab the first three characters of longitude, into the tempCharArray
	CharArray::substring(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LONGITUDE], stringSizeLongitude, 0, 3, tempCharArray);
	//Concatenate the tempCharArray into the this->_googleMapsCoordinates
	strcat(this->_googleMapsCoordinates, tempCharArray);
	//Add a space to the this->_googleMapsCoordinates
	strcat(this->_googleMapsCoordinates, " ");	
	//Grab the remainining characters of longitude, into the tempCharArray
	CharArray::substring(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LONGITUDE], stringSizeLatitude, 3, tempCharArray);
	//Concatenate the tempCharArray into the this->_googleMapsCoordinates
	strcat(this->_googleMapsCoordinates, tempCharArray);	
	//Add a space to the this->_googleMapsCoordinates
	strcat(this->_googleMapsCoordinates, " ");	
	//Concatenate the Latitude Direction into the this->_googleMapsCoordinates
	strcat(this->_googleMapsCoordinates, this->getGpsLongitudeDirection());	

	return this->_googleMapsCoordinates;

}
byte RoverGpsSensor::getGoogleMapsCoordinatesLength()
{
	return CharArray::stringSize(this->_googleMapsCoordinates,sizeof(this->_googleMapsCoordinates));	
}
void RoverGpsSensor::clearGoogleMapsCoordinates()
{
	memset(this->_googleMapsCoordinates,0,sizeof(this->_googleMapsCoordinates));	
}
double RoverGpsSensor::convertNMEALatitudeToDecimalDegrees(double nmea_latitude, char * direction)
{	
	//(latitude in NMEA format ddmm.mmmm)
	double lattitude_whole;
	double lattitude_fraction;		
	lattitude_whole = floor(nmea_latitude/100);
	lattitude_fraction = fmod(nmea_latitude, 100) / 60;
	if(strcmp(direction,"N") == 0)
	{
		return lattitude_whole + lattitude_fraction;
	}
	else if(strcmp(direction,"S") == 0)
	{
		return -1 * (lattitude_whole + lattitude_fraction);
	}
	else
	{
		return -999.99;//defaulting error value
	}
}
double RoverGpsSensor::convertNMEALongitudeToDecimalDegrees(double nmea_longitude, char * direction)
{	
	//(longitude in NMEA format (d)ddmm.mmmm)
	double longitude_whole;
	double longitude_fraction;
	longitude_whole = floor(nmea_longitude/100);
	longitude_fraction = fmod(nmea_longitude, 100) / 60;	
	if(strcmp(direction,"E") == 0)
	{
		return longitude_whole + longitude_fraction;//in decimal degrees
	}
	else if(strcmp(direction,"W") == 0)
	{
		return -1 * (longitude_whole + longitude_fraction);//in decimal degrees
	}
	else
	{
		return -999.99;//defaulting error value
	}
	
}
boolean RoverGpsSensor::dataPassedFiltering(char * gpsRxdData, byte arraySize)
{

//This function will return true if the GPS data passes the filtering and false if it doesn't.
	//This function will pass by reference the outputString:
	//For Filter-Passed GPS data: the GPS Sentence ID (i.e. GPGGA)
	//For Filter-Blocked GPS data: a blank string


	//Declare and initialize variable(s)
	byte startIndex = 0;
	byte endIndex = 0;
	char tempString[GPS_DATA_CHAR_BUFFER_SIZE];
	

	//GPS Sentence ID (i.e. GPGGA )
	//Search for the first comma
	endIndex = CharArray::indexOf(gpsRxdData, arraySize, ',');


	//Grab the GPS Sentence ID
	CharArray::substring(gpsRxdData, arraySize, startIndex, endIndex, tempString);
	
	#ifdef _DEBUG_OUTPUT_PARSED_HEADER
			Serial.print(F("Start Index: "));//DEBUG
			Serial.println(startIndex);//DEBUG
			Serial.print(F("End Index: "));//DEBUG
			Serial.println(endIndex);//DEBUG
			Serial.print(F("Parsed Header: "));//DEBUG
			Serial.println(tempString);//DEBUG			
	#endif			
		
	if (strcmp(tempString, GPS_GPGGA_SENTENCE_ID) == 0)	
	{	
		return true;
	}//end if
	else
	{
		return false;
	}//end else
}
