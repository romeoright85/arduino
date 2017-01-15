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
	this->_validChecksum = false;		
	//GPS Helper Variables	
	this->clearGpsHelperVariables();
	//GPS Received Data	
	this->clearRxGpsDataString();
	
}
void RoverGpsSensor::clearGpsHelperVariables()
{	
	this->_startIndex = 0;
	this->_endIndex = 0;		
	memset(this->_gpsDataArray,0,sizeof(this->_gpsDataArray));	
}
void RoverGpsSensor::clearRxGpsDataString()
{
	this->_rxData = "";
}
void RoverGpsSensor::appendToRxGPSData(char dataIn)
{
	this->_rxData.concat(dataIn);		
}
char * RoverGpsSensor::getRxGPSData()
{
	return this->_rxData;
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
	this->clearGpsHelperVariables();
	
	
	//==Data Filtering==
	//Note: Only keep and process GPGGA data. Ignore everything else.
	if (!dataPassedFiltering(this->_rxData))
	{
		#ifdef _DEBUG_OUTPUT_FILTERED_DATA_STATUS
			Serial.println(F("Filtered Out"));
		#endif
		
		this->clearRxGpsDataString();//clear the gps data
		return false;//do nothing if the data isn't desired
	}//end if
	//else continue

	#ifdef _DEBUG_OUTPUT_POST_FILTERED_RAW_RX_DATA
		Serial.println(this->_rxData);//DEBUG	
	#endif
	
		
	//Make a copy of the data char array. This copy will be manipulated.
	
	
	char dataStringToParse[GPS_DATA_CHAR_BUFFER_SIZE];
	
	strncpy(dataStringToParse, this->_rxData, sizeof(this->_rxData)/sizeof(this->_rxData[0]));	
	
		
					
	//==Parsing and extracting the GPS GPGGA data==
	
	//Note: The dataStringToParse starts after the $ since the function in the .ino (rxGPSData) that runs before this code will strip out the $	

	
	
	//Example Data Received by this function: GPGGA,142103.400,3916.2242,N,07636.6542,W,1,3,3.90,183.6,M,-33.6,M,,*6B	
	
	
	
	//Parse and extract the GPS data string for GPGGA
	for (byte i = 0; i < GPS_GPGGA_FIELDS; i++) 
	{
//REWRITE ME//		this->_endIndex = dataStringToParse.indexOf(',', this->_startIndex);//search for the first/next comma			
		
//REWRITE ME//		this->_gpsDataArray[i] = dataStringToParse.substring(this->_startIndex, this->_endIndex);//grab the substring the start and the first commas (for the first field) or the substring between two commas

		
		#ifdef _DEBUG_OUTPUT_PARSING_PROCESS
			Serial.print(F("Data Being Parsed: "));//DEBUG
			Serial.println(dataStringToParse);//DEBUG
			Serial.print(F("Start Index: "));//DEBUG
			Serial.println(this->_startIndex);//DEBUG
			Serial.print(F("End Index: "));//DEBUG
			Serial.println(this->_endIndex);//DEBUG
			Serial.print(F("Parsed Data: "));//DEBUG
			Serial.println(this->_gpsDataArray[i]);//DEBUG
		#endif			
		
//REWRITE ME//		dataStringToParse = dataStringToParse.substring(this->_endIndex + 1);//prepare the data for the next interation of the loop by skipping over the current comma
		
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

	
	//Return from the function if the GPS data is invalid (status is extracted from the parsed GPS data) or the GPS checksum is invalid
	if(!this->isGpsDataValid())
	{
		//End the function if the GPS data in not valid
		this->clearRxGpsDataString();//clear the gps data
		return false;
	}//end if
	else
	{
		//Clear the GPS data string for future use
		this->clearRxGpsDataString();
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
double RoverGpsSensor::getGpsTimeWhenDataWasFixed()
{	
	return (this->_gpsDataArray[GPS_GPGGA_INDEX_OF_DATA_FIX_TIME]).toFloat();
}

double RoverGpsSensor::getGpsLatitude()
{	
	return (this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LATITUDE]).toFloat();
}
char RoverGpsSensor::getGpsLatitudeDirection()
{	
	byte charBufferSize = (this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LATITUDE_DIRECTION]).length() + 1;
	char charArray[charBufferSize];
	(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LATITUDE_DIRECTION]).toCharArray(charArray,charBufferSize);
	return charArray[0];
}
double RoverGpsSensor::getGpsLongitude()
{	
	return (this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LONGITUDE]).toFloat();
}
char RoverGpsSensor::getGpsLongitudeDirection()
{	
	byte charBufferSize = (this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LONGITUDE_DIRECTION]).length() + 1;
	char charArray[charBufferSize];
	(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LONGITUDE_DIRECTION]).toCharArray(charArray,charBufferSize);
	return charArray[0];
}
byte RoverGpsSensor::getGpsFixQuality()
{		
	return (this->_gpsDataArray[GPS_GPGGA_INDEX_OF_FIX_QUALITY]).toInt();		
}
byte RoverGpsSensor::getGpsSatellitesTracked()
{
	return (this->_gpsDataArray[GPS_GPGGA_INDEX_OF_SATELLITES_TRACKED]).toInt();		
}
char * RoverGpsSensor::getGoogleMapsCoordinates()
{
	
	//Example Google Maps Format: 39 16.10 N, 76 36.66 W
	
	//Use the original string before it's converted to a double for latitude and longitude to prevent round off or conversion errors
//REWRITE ME//	String latitude = this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LATITUDE];
//REWRITE ME//	String longitude = this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LONGITUDE];
	
	//Remember: Latitude is 0 to 90 and Longitude is 0 to 180. So Grab the first two characters for longitude and the first three characters for longitude.
//REWRITE ME//	return latitude.substring(0,2) + " " + latitude.substring(2) + " " + this->getGpsLatitudeDirection() + ", " +  longitude.substring(0,3) + " " + longitude.substring(3) + " " + this->getGpsLongitudeDirection();
	
	
}
boolean RoverGpsSensor::dataPassedFiltering(char * gpsRxdData)
{

//This function will return true if the GPS data passes the filtering and false if it doesn't.
	//This function will pass by reference the outputString:
	//For Filter-Passed GPS data: the GPS Sentence ID (i.e. GPGGA)
	//For Filter-Blocked GPS data: a blank string


	//Declare and initialize variable(s)
	byte startIndex = 0;
	byte endIndex;
//REWRITE ME//	String tempString;

	//GPS Sentence ID (i.e. GPGGA )
	//Search for the first comma
//REWRITE ME//	endIndex = gpsRxdData.indexOf(',', startIndex);
	//Grab the GPS Sentence ID
//REWRITE ME//	tempString = gpsRxdData.substring(startIndex, endIndex);//grab the substring from the start to the first comma

	
	#ifdef _DEBUG_OUTPUT_PARSED_HEADER
			Serial.print(F("Start Index: "));//DEBUG
			Serial.println(startIndex);//DEBUG
			Serial.print(F("End Index: "));//DEBUG
			Serial.println(endIndex);//DEBUG
			Serial.print(F("Parsed Header: "));//DEBUG
			Serial.println(tempString);//DEBUG			
	#endif			
		
	
	
//REWRITE ME//	if (tempString.equals(GPS_GPGGA_SENTENCE_ID) )
	{
		return true;
	}//end if
	else
	{
		return false;
	}//end else
}
