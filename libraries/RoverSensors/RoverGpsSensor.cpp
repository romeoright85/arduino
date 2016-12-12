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
	//Persistent GPS Data Array (GPGGA and GPRMC merged data)
	this->clearProcessedGpsDataArray();	
	//GPS Helper Variables	
	this->clearGpsHelperVariables();
	//GPS Received Data	
	this->clearRxGpsDataString();
	
}
void RoverGpsSensor::clearGpsHelperVariables()
{	
	this->_startIndex = 0;
	this->_endIndex = 0;		
	memset(this->_gpsPreProcessedDataArray,0,sizeof(this->_gpsPreProcessedDataArray));	
}
void RoverGpsSensor::clearRxGpsDataString()
{
	this->_rxData = "";
}
void RoverGpsSensor::clearProcessedGpsDataArray()
{
	//Note: This data should be presistent since it's shared between GPGGA and GPRMC. Try only to clear it when needed (i.e. during reset)
	memset(this->_gpsPostProcessedDataArray,0,sizeof(this->_gpsPostProcessedDataArray));	
}
void RoverGpsSensor::appendToRxGPSData(char dataIn)
{
	this->_rxData.concat(dataIn);		
}
boolean RoverGpsSensor::processRxGPSData()
{

	//Note: The data starts after the $ since the function in the .ino (rxGPSData) that runs before this code will strip out the $	
	
	
	//Example Raw Data: $GPGGA,142103.400,3916.2242,N,07636.6542,W,1,3,3.90,183.6,M,-33.6,M,,*6B
	//Example Data Received by this function: GPGGA,142103.400,3916.2242,N,07636.6542,W,1,3,3.90,183.6,M,-33.6,M,,*6B	
	//Reference:
	//https://www.arduino.cc/en/Reference/StringObject
	//http://stackoverflow.com/questions/11068450/arduino-c-language-parsing-string-with-delimiter-input-through-serial-interfa
	
	
	//Initialize variable(s)		
	this->clearGpsHelperVariables();
	
	
	//==Data Filtering==
	//Note: Only keep and process GPGGA or GPRMC data. Ignore everything else.
	if (!dataPassedFiltering(this->_rxData, this->_gpsPreProcessedDataArray[GPS_GENERIC_INDEX_OF_HEADER]))//Save the GPS Header (gpsHeader) into gpsPreProcessedData[GPS_GENERIC_INDEX_OF_HEADER] where GPS_GENERIC_INDEX_OF_HEADER = 0;
	{
		Serial.println(F("Filtered Out"));	
		this->clearRxGpsDataString();//clear the gps data
		return false;//do nothing if the data isn't desired
	}//end if
	//else continue

	
	
	//Make a copy of the data string. This copy will be manipulated.
	String dataStringToParse = _rxData;
		
	//==Validating the Checksum==
	if (!this->validateChecksum(this->_rxData, dataStringToParse, this->_gpsPreProcessedDataArray[GPS_GENERIC_INDEX_OF_CHECKSUM]))//if checksum failed
	{
		Serial.println(F("Checksum Failed"));
		this->clearRxGpsDataString();//clear the gps data
		this->_validChecksum = false;
		return false;//do nothing if the data isn't desired
	}//end if
	else
	{
		this->_validChecksum = true;
		//then continue below
	}//end else
	
	
	//==Parsing and extracting the data based on GPS header type (GPGGA or GPRMC)==
	
	//Notes:
	//dataStringToParse is the GPS data without the $ at the beginning or the ending part (i.e. without the * or anything after, like the checksum)
	//Since GPGGA has a comma before the * but GPRMC doesn't, will have to have different algorithms string parsing for the two types
	if (this->_gpsPreProcessedDataArray[GPS_GPGGA_INDEX_OF_HEADER] == GPS_GPGGA_FIXED_DATA)//for GPGGA data
	{

		//Parse and extract the GPS data string for GPGGA
		for (byte i = 0; i < GPS_GPGGA_FIELDS; i++)
		{
			this->_endIndex = dataStringToParse.indexOf(',', this->_startIndex);//search for the first/next comma			

		   //Serial.println(dataStringToParse);//DEBUG
		   //Serial.println(this->_startIndex);//DEBUG
		   //Serial.println(this->_endIndex);//DEBUG

			this->_gpsPreProcessedDataArray[i] = dataStringToParse.substring(this->_startIndex, this->_endIndex);//grab the substring the start and the first commas (for the first field) or the substring between two commas

			#ifdef _DEBUG_
						Serial.println(this->_gpsPreProcessedDataArray[i]);//DEBUG
			#endif

			dataStringToParse = dataStringToParse.substring(this->_endIndex + 1);//skip over the current comma to process the data the next loop					
		}//end for

		//Store the GPGGA data into the Persistent GPS Data array (Shared between GPGGA and GPRMC, the common data fields are overwritten as they get updates).				
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_DATA_FIX_TIME] = this->_gpsPreProcessedDataArray[GPS_GPGGA_INDEX_OF_DATA_FIX_TIME];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_LATITUDE] = this->_gpsPreProcessedDataArray[GPS_GPGGA_INDEX_OF_LATITUDE];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_LATITUDE_DIRECTION] = this->_gpsPreProcessedDataArray[GPS_GPGGA_INDEX_OF_LATITUDE_DIRECTION];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_LONGITUDE] = this->_gpsPreProcessedDataArray[GPS_GPGGA_INDEX_OF_LONGITUDE];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_LONGITUDE_DIRECTION] = this->_gpsPreProcessedDataArray[GPS_GPGGA_INDEX_OF_LONGITUDE_DIRECTION];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_FIX_QUALITY] = this->_gpsPreProcessedDataArray[GPS_GPGGA_INDEX_OF_FIX_QUALITY];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_SATELLITES_TRACKED] = this->_gpsPreProcessedDataArray[GPS_GPGGA_INDEX_OF_SATELLITES_TRACKED];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_HORIZONTAL_DILUTION_OF_POSITION] = this->_gpsPreProcessedDataArray[GPS_GPGGA_INDEX_OF_HORIZONTAL_DILUTION_OF_POSITION];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_ALTITUDE_ABOVE_MEAN_SEA_LEVEL] = this->_gpsPreProcessedDataArray[GPS_GPGGA_INDEX_OF_ALTITUDE_ABOVE_MEAN_SEA_LEVEL];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_ALTITUDE_UNIT] = this->_gpsPreProcessedDataArray[GPS_GPGGA_INDEX_OF_ALTITUDE_UNIT];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_HEIGHT_OF_GEOID] = this->_gpsPreProcessedDataArray[GPS_GPGGA_INDEX_OF_HEIGHT_OF_GEOID];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_GEOID_UNIT] = this->_gpsPreProcessedDataArray[GPS_GPGGA_INDEX_OF_GEOID_UNIT];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_GPGGA_CHECKSUM] = this->_gpsPreProcessedDataArray[GPS_GENERIC_INDEX_OF_CHECKSUM];

	}//end if
	else if (this->_gpsPreProcessedDataArray[GPS_GPRMC_INDEX_OF_HEADER] == GPS_GPRMC_MIN_RECOMMENDED_DATA)//For GPRMC data
	{
		//Parse and extract the GPS data string for GPRMC
		for (byte i = 0; i < GPS_GPRMC_FIELDS; i++)
		{
			this->_endIndex = dataStringToParse.indexOf(',', this->_startIndex);//search for the first/next comma			
														   //Serial.println(dataStringToParse);//DEBUG
														   //Serial.println(this->_startIndex);//DEBUG
														   //Serial.println(this->_endIndex);//DEBUG
			this->_gpsPreProcessedDataArray[i] = dataStringToParse.substring(this->_startIndex, this->_endIndex);//grab the substring the start and the first commas (for the first field) or the substring between two commas

			#ifdef _DEBUG_
						Serial.println(this->_gpsPreProcessedDataArray[i]);//DEBUG
			#endif

			dataStringToParse = dataStringToParse.substring(this->_endIndex + 1);//skip over the current comma to process the data the next loop					
		}//end for

		//Store the GPRMC data into the Persistent GPS Data array (Shared between GPGGA and GPRMC, the common data fields are overwritten as they get updates).
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_DATA_FIX_TIME] = this->_gpsPreProcessedDataArray[GPS_GPRMC_INDEX_OF_DATA_FIX_TIME];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_STATUS] = this->_gpsPreProcessedDataArray[GPS_GPRMC_INDEX_OF_STATUS];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_LATITUDE] = this->_gpsPreProcessedDataArray[GPS_GPRMC_INDEX_OF_LATITUDE];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_LATITUDE_DIRECTION] = this->_gpsPreProcessedDataArray[GPS_GPRMC_INDEX_OF_LATITUDE_DIRECTION];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_LONGITUDE] = this->_gpsPreProcessedDataArray[GPS_GPRMC_INDEX_OF_LONGITUDE];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_LONGITUDE_DIRECTION] = this->_gpsPreProcessedDataArray[GPS_GPRMC_INDEX_OF_LONGITUDE_DIRECTION];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_SPEED] = this->_gpsPreProcessedDataArray[GPS_GPRMC_INDEX_OF_SPEED];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_TRACK_ANGLE] = this->_gpsPreProcessedDataArray[GPS_GPRMC_INDEX_OF_TRACK_ANGLE];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_DATE] = this->_gpsPreProcessedDataArray[GPS_GPRMC_INDEX_OF_DATE];
		this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_GPRMC_CHECKSUM] = this->_gpsPreProcessedDataArray[GPS_GENERIC_INDEX_OF_CHECKSUM];

	}//end else if
	else
	{
		//do nothing as this is an error
	}//end else

	#ifdef _DEBUG2_

		Serial.println("==BEGIN==");
		for (byte i = 0; i < GPS_POST_PROCESSED_FIELDS; i++)
		{
			Serial.println(this->_gpsPostProcessedDataArray[i]);
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
			
	if(this->getGpsStatus() == 'A' && this->getGpsFixQuality() > 0)//if the status if Active and the Fix Quality has a valid value (1-8)
	{
		return true;
	}//end if
	else //the status is either 'V' for void or something other than 'A', so it is invalid and/or the Fix Quality is not between 1-8, so it is invalid
	{
		return false;
	}//end else	
}
unsigned int RoverGpsSensor::getGpsTimeWhenDataWasFixed()
{	
	return (this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_DATA_FIX_TIME]).toInt();
}
char RoverGpsSensor::getGpsStatus()
{	
	byte charBufferSize = (this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_STATUS]).length() + 1;
	char charArray[charBufferSize];
	(this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_STATUS]).toCharArray(charArray,charBufferSize);
	return charArray[0];
}
double RoverGpsSensor::getGpsLatitude()
{	
	return (this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_LATITUDE]).toFloat();
}
char RoverGpsSensor::getGpsLatitudeDirection()
{	
	byte charBufferSize = (this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_LATITUDE_DIRECTION]).length() + 1;
	char charArray[charBufferSize];
	(this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_LATITUDE_DIRECTION]).toCharArray(charArray,charBufferSize);
	return charArray[0];
}
double RoverGpsSensor::getGpsLongitude()
{	
	return (this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_LONGITUDE]).toFloat();
}
char RoverGpsSensor::getGpsLongitudeDirection()
{	
	byte charBufferSize = (this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_LONGITUDE_DIRECTION]).length() + 1;
	char charArray[charBufferSize];
	(this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_LONGITUDE_DIRECTION]).toCharArray(charArray,charBufferSize);
	return charArray[0];
}
byte RoverGpsSensor::getGpsFixQuality()
{		
	return (this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_FIX_QUALITY]).toInt();		
}
byte RoverGpsSensor::getGpsSatellitesTracked()
{
	return (this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_SATELLITES_TRACKED]).toInt();		
}
double RoverGpsSensor::getGpsHorizontalDilution()
{
	return (this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_HORIZONTAL_DILUTION_OF_POSITION]).toFloat();
}
double RoverGpsSensor::getGpsAltitude()
{
	return (this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_ALTITUDE_ABOVE_MEAN_SEA_LEVEL]).toFloat();
}
char RoverGpsSensor::getGpsAltitudeUnit()
{
	byte charBufferSize = (this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_ALTITUDE_UNIT]).length() + 1;
	char charArray[charBufferSize];
	(this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_ALTITUDE_UNIT]).toCharArray(charArray,charBufferSize);
	return charArray[0];
}
double RoverGpsSensor::getGpsSpeed()
{
	return (this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_SPEED]).toFloat();
}
double RoverGpsSensor::getGpsGeoidHeight()
{
	return (this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_HEIGHT_OF_GEOID]).toFloat();	
}
char RoverGpsSensor::getGpsGeoidHeightUnit()
{
	byte charBufferSize = (this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_GEOID_UNIT]).length() + 1;
	char charArray[charBufferSize];
	(this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_GEOID_UNIT]).toCharArray(charArray,charBufferSize);
	return charArray[0];
}
double RoverGpsSensor::getGpsTrackAngle()
{
	return (this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_TRACK_ANGLE]).toFloat();	
}
unsigned int RoverGpsSensor::getGpsDate()
{
	return (this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_DATE]).toInt();
}
String RoverGpsSensor::getGpsGPGGAChecksum()
{
	return this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_GPGGA_CHECKSUM];
}
String RoverGpsSensor::getGpsGPRMCChecksum()
{
	return this->_gpsPostProcessedDataArray[GPS_POST_PROCESSED_INDEX_OF_GPRMC_CHECKSUM];
}
boolean RoverGpsSensor::dataPassedFiltering(String gpsRxdData, String & gpsHeader)
{

//This function will return true if the GPS data passes the filtering and false if it doesn't.
	//This function will pass by reference the outputString:
	//For Filter-Passed GPS data: the GPS header (i.e. GPGGA or GPRMC)
	//For Filter-Blocked GPS data: a blank string


	//Declare and initialize variable(s)
	byte startIndex = 0;
	byte endIndex;
	String tempString;

	//GPS header (data type) i.e. GPGGA or GPRMC
	//Search for the first comma
	endIndex = gpsRxdData.indexOf(',', startIndex);
	//Grab the GPS Header
	tempString = gpsRxdData.substring(startIndex, endIndex);//grab the substring from the start to the first comma

	if (tempString.equals(GPS_GPGGA_FIXED_DATA) || tempString.equals(GPS_GPRMC_MIN_RECOMMENDED_DATA))
	{
		gpsHeader = tempString;
		return true;
	}//end if
	else
	{
		gpsHeader = "";
		return false;
	}//end else
}
boolean RoverGpsSensor::validateChecksum(String inputString, String & outputString, String & receivedChecksumInHex)
{
	//This function will return true if the checksum is valid and false if it isn't.
	//This function will pass by reference the variable outputString:
		//For Valid Checksums: as the GPS data without the $ at the beginning or the ending part (i.e. without the * or anything after, like the checksum)
		//For Invalid Checksums: as a blank string

	//Note: This checksum calculation algorithm works for both GPRMC and GPGGA
	//Note: The checksum doesn't include the $ at the beginning or the * or anything after that

	//Declare and initialize variables
	byte startIndex = 0;
	byte endIndex = 0;
	byte calculatedChecksumInDecimal = 0;
	String calculatedChecksumInHex = "";	

	//Make a copy of the original string in order to calculate the checksum
	String tempString = inputString;

	//Search for the *
	endIndex = tempString.indexOf('*');

	//Grab the substring to use in the checksum calculation
	tempString = tempString.substring(startIndex, endIndex);//grab the substring of GPS data without the ending part (i.e. without the * or anything after, like the checksum)

	//Calculate the Checksum In Decimal
	for (byte i = 0; i < tempString.length(); i++)
	{
		calculatedChecksumInDecimal ^= tempString.charAt(i);
	}//end for

	//Convert the Checksum into Hex
	calculatedChecksumInHex = twoDigitDecimalToHexConverter(calculatedChecksumInDecimal);

	//Serial.println(calculatedCheckSumInHex);//DEBUG

	//Grab the received checksum
	receivedChecksumInHex = inputString.substring(endIndex + 1, endIndex + 3);//It is the two characters after the *

	
	//Set the outputString as the tempString
	outputString = tempString;
	
	if (receivedChecksumInHex.equals(calculatedChecksumInHex))
	{	
		return true;
	}//end if
	else
	{		
		return false;
	}//end else
}
String RoverGpsSensor::twoDigitDecimalToHexConverter(byte decimalValue)
{
	char upperDigit;
	char lowerDigit;
	String output = "";
	if (decimalValue > 255 || decimalValue < 0)//the range is o to FF aka 0 to 255
	{
		return "ZZ";//error value
	}//end if
	else
	{

		//Convert the decimal values into hex (upper and lower digits)
		upperDigit = decimalToHex(decimalValue / 16);
		lowerDigit = decimalToHex(decimalValue % 16);

		//Construct and return the 2 digit hex string		
		return (String)upperDigit + (String)lowerDigit;
	}//end else
}
char RoverGpsSensor::decimalToHex(byte decimalValue)
{
	switch (decimalValue)
	{
	case 0:
		return '0';
		break;
	case 1:
		return '1';
		break;
	case 2:
		return '2';
		break;
	case 3:
		return '3';
		break;
	case 4:
		return '4';
		break;
	case 5:
		return '5';
		break;
	case 6:
		return '6';
		break;
	case 7:
		return '7';
		break;
	case 8:
		return '8';
		break;
	case 9:
		return '9';
		break;
	case 10:
		return 'A';
		break;
	case 11:
		return 'B';
		break;
	case 12:
		return 'C';
		break;
	case 13:
		return 'D';
		break;
	case 14:
		return 'E';
		break;
	case 15:
		return 'F';
		break;
	default:
		return 'Z';//error, for numbers out of the range of hex, 0 to 16
		break;
	}//end switch
}
