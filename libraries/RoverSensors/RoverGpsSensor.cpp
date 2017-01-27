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
		Serial.println(F("BuffOvrFlw"));
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
	
	//Return from the function if the GPS data is invalid (status is extracted from the parsed GPS data) or the GPS checksum is invalid
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
double RoverGpsSensor::getGpsTimeWhenDataWasFixed()
{	
	return atof(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_DATA_FIX_TIME]);
}

double RoverGpsSensor::getGpsLatitude()
{	

	return atof(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LATITUDE]);	
}
char * RoverGpsSensor::getGpsLatitudeDirection()
{	
	return this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LATITUDE_DIRECTION];
}
double RoverGpsSensor::getGpsLongitude()
{	
	return atof(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LONGITUDE]);		
}
char * RoverGpsSensor::getGpsLongitudeDirection()
{	
	return this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LONGITUDE_DIRECTION];
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
	
	//Create temp/placeholder and output char arrays
	char tempCharArray[GPS_DATA_CHAR_BUFFER_SIZE]; 
	char outputCharArray[GPS_DATA_CHAR_BUFFER_SIZE];
			
		
	//Constructing the output array
		
	//Remember: Latitude is 0 to 90 and Longitude is 0 to 180. So Grab the first two characters for longitude and the first three characters for longitude.
			
	//Grab the first two characters of latitude, into the outputCharArray
	CharArray::substring(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LATITUDE], stringSizeLatitude, 0, 2, outputCharArray);
	//Add a space to the outputCharArray
	strcat (outputCharArray, " ");
	//Grab the remainining characters of latitude, into the tempCharArray
	CharArray::substring(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LATITUDE], stringSizeLatitude, 2, tempCharArray);
	//Concatenate the tempCharArray into the outputCharArray
	strcat (outputCharArray, tempCharArray);
	//Add a space to the outputCharArray
	strcat (outputCharArray, " ");	
	//Concatenate the Latitude Direction into the outputCharArray
	strcat (outputCharArray, this->getGpsLatitudeDirection());
	//Add a space and comma to the outputCharArray
	strcat (outputCharArray, ", ");
	//Grab the first three characters of longitude, into the tempCharArray
	CharArray::substring(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LONGITUDE], stringSizeLongitude, 0, 3, tempCharArray);
	//Concatenate the tempCharArray into the outputCharArray
	strcat (outputCharArray, tempCharArray);
	//Add a space to the outputCharArray
	strcat (outputCharArray, " ");	
	//Grab the remainining characters of longitude, into the tempCharArray
	CharArray::substring(this->_gpsDataArray[GPS_GPGGA_INDEX_OF_LONGITUDE], stringSizeLatitude, 3, tempCharArray);
	//Concatenate the tempCharArray into the outputCharArray
	strcat (outputCharArray, tempCharArray);	
	//Add a space to the outputCharArray
	strcat (outputCharArray, " ");	
	//Concatenate the Latitude Direction into the outputCharArray
	strcat (outputCharArray, this->getGpsLongitudeDirection());	

	return outputCharArray;

	
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
