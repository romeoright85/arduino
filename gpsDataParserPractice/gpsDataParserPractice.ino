//NOTES:
//Used to test filtering, checksum, parsing, and validating algorithms. Though not kept up to date.
//After the migration of this practice code to the actual rover code, improvements have been made to the actual rover code (i..e got ride of unnecessary variables, renamed things to make it more clear, etc.)
//Not for long term use since it uses the string classes


#include <string.h>

#define _GPS_SENSOR
#include <RoverConfig.h>


//#define _DEBUG_ //Uncomment this flag to turn on debug outputs
#define _DEBUG2_ //Uncomment this flag to turn on more debug outputs


//Declare variables (and initialize some)
String dataString = "";//string that holds the GPS data (GPGGA or GPRMC) with the $, the *, or the checksum (afther the *)
byte startIndex;
byte endIndex;
byte gpsPreProcessedDataIndex;//index for the gpsPreProcessedData array
String gpsPreProcessedData[13];//size 15, from 0 to 12.
							   //Notes:
							   //For GPGGA there are 13 fields, the rest won't be used.
							   //For GPRMC there are 10 fields, the rest won't be used.
byte gpsPostProcessedDataIndex;//index for the gpsPostProcessedData array. This array is the merger of GPGGA and GPRMC data.
String gpsPostProcessedData[16];//size 16, from 0 to 15.




void setup()
{

	
	Serial.begin(9600);
	Serial1.begin(57600);
}

void loop()
{



	
	//Test Case 1
	//DEBUG: Example of GPGGA data with a GOOD checksum to test this function. Uncomment to use.
	String original = "GPGGA,142103.400,3916.2242,N,07636.6542,W,1,3,3.90,183.6,M,-33.6,M,,*6B";//DEBUG

	//Test Case 2
	//DEBUG: Example of GPGGA data with a BAD checksum to test this function. Uncomment to use.
	//String original = "GPGGA,142103.400,3916.2242,N,07636.6542,W,1,3,3.90,183.6,M,-33.6,M,,*6C";//DEBUG
	
	//Test Case 3
	//DEBUG: Example of GPRMC data with a GOOD checksum to test this function. Uncomment to use.
	//String original = "GPRMC,142101.600,A,3916.2226,N,07636.6530,W,0.33,0.00,271116,,,A*72";//DEBUG

	//Test Case 4
	//DEBUG: Example of GPRMC data with a BAD checksum to test this function. Uncomment to use.
	//String original = "GPRMC,142101.600,A,3916.2226,N,07636.6530,W,0.33,0.00,271116,,,A*71";//DEBUG


	//Initialize variable(s)
	gpsPreProcessedDataIndex = GPS_GENERIC_INDEX_OF_HEADER;

	//Data Filtering
	//Note: Only keep and process GPGGA or GPRMC data. Ignore everything else.
	if (!dataPassedFiltering(original, gpsPreProcessedData[gpsPreProcessedDataIndex]))//Save the GPS Header (gpsHeader) into gpsPreProcessedData[gpsPreProcessedDataIndex] where gpsPreProcessedDataIndex = 0;
	{
		Serial.println(F("Filtered Out"));
		return;//do nothing if the data isn't desired
	}
	//else continue
	
	//Checksum
	if (!checkSumCalculation(original, dataString ))//if checksum failed
	{
		Serial.println(F("Checksum Failed"));
		return;
	}	
	//else continue
	
	#ifdef _DEBUG_
		Serial.println("====");//DEBUG
		Serial.println(dataString);//DEBUG
	#endif
	

	//Notes:
		//dataString is the GPS data without the $ at the beginning or the ending part (i.e. without the * or anything after, like the checksum)
		//Since GPGGA has a comma before the * but GPRMC doesn't, will have to have different algorithms string parsing for the two types


	if (gpsPreProcessedData[GPS_GPGGA_INDEX_OF_HEADER] == GPS_GPGGA_FIXED_DATA)//for GPGGA data
	{
		
		for (byte i = 0; i < GPS_GPGGA_FIELDS; i++)
		{
			endIndex = dataString.indexOf(',', startIndex);//search for the first/next comma			

			//Serial.println(dataString);//DEBUG
			//Serial.println(startIndex);//DEBUG
			//Serial.println(endIndex);//DEBUG

			gpsPreProcessedData[i] = dataString.substring(startIndex, endIndex);//grab the substring the start and the first commas (for the first field) or the substring between two commas

			#ifdef _DEBUG_
				Serial.println(gpsPreProcessedData[i]);//DEBUG
			#endif
			
			dataString = dataString.substring(endIndex + 1);//skip over the current comma to process the data the next loop					
		}
		
		//Merge GPGGA data (shared/overwritten array, gpsPreProcessedData) with the master data array, gpsPostProcessedData
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_DATA_FIX_TIME] = gpsPreProcessedData[GPS_GPGGA_INDEX_OF_DATA_FIX_TIME];
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_LATITUDE] = gpsPreProcessedData[GPS_GPGGA_INDEX_OF_LATITUDE];
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_LATITUDE_DIRECTION] = gpsPreProcessedData[GPS_GPGGA_INDEX_OF_LATITUDE_DIRECTION];
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_LONGITUDE] = gpsPreProcessedData[GPS_GPGGA_INDEX_OF_LONGITUDE];
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_LONGITUDE_DIRECTION] = gpsPreProcessedData[GPS_GPGGA_INDEX_OF_LONGITUDE_DIRECTION];
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_FIX_QUALITY] = gpsPreProcessedData[GPS_GPGGA_INDEX_OF_FIX_QUALITY];
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_SATELLITES_TRACKED] = gpsPreProcessedData[GPS_GPGGA_INDEX_OF_SATELLITES_TRACKED];
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_HORIZONTAL_DILUTION_OF_POSITION] = gpsPreProcessedData[GPS_GPGGA_INDEX_OF_HORIZONTAL_DILUTION_OF_POSITION];
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_ALTITUDE_ABOVE_MEAN_SEA_LEVEL] = gpsPreProcessedData[GPS_GPGGA_INDEX_OF_ALTITUDE_ABOVE_MEAN_SEA_LEVEL];
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_ALTITUDE_UNIT] = gpsPreProcessedData[GPS_GPGGA_INDEX_OF_ALTITUDE_UNIT];
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_HEIGHT_OF_GEOID] = gpsPreProcessedData[GPS_GPGGA_INDEX_OF_HEIGHT_OF_GEOID];
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_GEOID_UNIT] = gpsPreProcessedData[GPS_GPGGA_INDEX_OF_GEOID_UNIT];
		
	}
	else if (gpsPreProcessedData[GPS_GPRMC_INDEX_OF_HEADER] == GPS_GPRMC_MIN_RECOMMENDED_DATA)//For GPRMC data
	{
		for (byte i = 0; i < GPS_GPRMC_FIELDS; i++)
		{
			endIndex = dataString.indexOf(',', startIndex);//search for the first/next comma			
			//Serial.println(dataString);//DEBUG
			//Serial.println(startIndex);//DEBUG
			//Serial.println(endIndex);//DEBUG
			gpsPreProcessedData[i] = dataString.substring(startIndex, endIndex);//grab the substring the start and the first commas (for the first field) or the substring between two commas
			
			#ifdef _DEBUG_
						Serial.println(gpsPreProcessedData[i]);//DEBUG
			#endif

			dataString = dataString.substring(endIndex + 1);//skip over the current comma to process the data the next loop					
		}


		//Merge GPRMC data (shared/overwritten array, gpsPreProcessedData) with the master data array, gpsPostProcessedData
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_DATA_FIX_TIME] = gpsPreProcessedData[GPS_GPRMC_INDEX_OF_DATA_FIX_TIME];
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_STATUS] = gpsPreProcessedData[GPS_GPRMC_INDEX_OF_STATUS];
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_LATITUDE] = gpsPreProcessedData[GPS_GPRMC_INDEX_OF_LATITUDE];
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_LATITUDE_DIRECTION] = gpsPreProcessedData[GPS_GPRMC_INDEX_OF_LATITUDE_DIRECTION];
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_LONGITUDE] = gpsPreProcessedData[GPS_GPRMC_INDEX_OF_LONGITUDE];
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_LONGITUDE_DIRECTION] = gpsPreProcessedData[GPS_GPRMC_INDEX_OF_LONGITUDE_DIRECTION];
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_SPEED] = gpsPreProcessedData[GPS_GPRMC_INDEX_OF_SPEED];
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_TRACK_ANGLE] = gpsPreProcessedData[GPS_GPRMC_INDEX_OF_TRACK_ANGLE];
		gpsPostProcessedData[GPS_POST_PROCESSED_INDEX_OF_DATE] = gpsPreProcessedData[GPS_GPRMC_INDEX_OF_DATE];


	}
	else
	{
		//do nothing as this is an error
	}

		#ifdef _DEBUG2_

				Serial.println("==BEGIN==");
				for (byte i = 0; i < GPS_POST_PROCESSED_FIELDS; i++)
				{		
					Serial.println(gpsPostProcessedData[i]);
				}
				Serial.println("==END==");
				Serial.println();

		#endif

	return;

}





boolean checkSumCalculation(String inputString, String & outputString)
{
	//This function will return true if the checksum is valid and false if it isn't.
	//This function will pass by reference the outputString:
		//For Valid Checksums: the GPS data without the $ at the beginning or the ending part (i.e. without the * or anything after, like the checksum)
		//For Invalid Checksums: a blank string
	
	//Note: This checksum calculation algorithm works for both GPRMC and GPGGA
	//Note: The checksum doesn't include the $ at the beginning or the * or anything after that
	
	//Declare and initialize variables
	byte startIndex = 0;
	byte endIndex = 0;
	byte calculatedChecksumInDecimal = 0;
	String calculatedChecksumInHex = "";
	String receivedChecksumInHex = "";

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
	}
		
	//Convert the Checksum into Hex
	calculatedChecksumInHex = twoDigitDecimalToHexConverter(calculatedChecksumInDecimal);

	//Serial.println(calculatedCheckSumInHex);//DEBUG

	//Grab the received checksum
	receivedChecksumInHex = inputString.substring(endIndex+1, endIndex+3);//It is the two characters after the *

	if (receivedChecksumInHex.equals(calculatedChecksumInHex))
	{
		//Set the outputString as the tempString
		outputString = tempString;
		return true;
	}
	else
	{
		//Return a blank output string
		outputString = "";
		return false;
	}
}


String twoDigitDecimalToHexConverter(byte decimalValue)
{
	char upperDigit;
	char lowerDigit;
	String output = "";
	if (decimalValue > 255 || decimalValue < 0)//the range is o to FF aka 0 to 255
	{
		return "ZZ";//error value
	}
	else
	{

		//Convert the decimal values into hex (upper and lower digits)
		upperDigit = decimalToHex(decimalValue / 16);
		lowerDigit = decimalToHex(decimalValue % 16);

		//Construct and return the 2 digit hex string		
		return (String)upperDigit + (String)lowerDigit;
	}
}
char decimalToHex(byte decimalValue)
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



boolean dataPassedFiltering(String gpsRxdData, String & gpsHeader)
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
	}
	else
	{
		gpsHeader = "";
		return false;
	}
}