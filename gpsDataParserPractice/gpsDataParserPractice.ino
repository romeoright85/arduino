//See: //FINISH WRITING ME

#include <string.h>

#define GPS_HD_FIXED_DATA			"GPGGA"
#define GPS_HD_MIN_RECOMMENDED_DATA	"GPRMC"
#define GPS_HEADER_FIELD	0



void setup()
{

	/* add setup code here */
	Serial.begin(9600);
	Serial1.begin(57600);
}

void loop()
{

	

	//Declare variables (and initialize some)
	String dataString = "";//string that holds the GPS data (GPGGA or GPRMC) with the $, the *, or the checksum (afther the *)
	byte startIndex;
	byte endIndex;
	byte gpsDataIndex;//index for the gpsData array
	String gpsData[15];//size 15, from 0 to 14.
					   //Notes:
					   //For GPGGA there are 15 fields
					   //For GPRMC there are 13 fields, the rest won't be used.


	//Test Case 1
	//DEBUG: Example of GPGGA data with a GOOD checksum to test this function. Uncomment to use.
	//String original = "GPGGA,142103.400,3916.2242,N,07636.6542,W,1,3,3.90,183.6,M,-33.6,M,,*6B";//DEBUG

	//Test Case 2
	//DEBUG: Example of GPGGA data with a BAD checksum to test this function. Uncomment to use.
	//String original = "GPGGA,142103.400,3916.2242,N,07636.6542,W,1,3,3.90,183.6,M,-33.6,M,,*6C";//DEBUG
	
	//Test Case 3
	//DEBUG: Example of GPRMC data with a GOOD checksum to test this function. Uncomment to use.
	String original = "GPRMC,142101.600,A,3916.2226,N,07636.6530,W,0.33,0.00,271116,,,A*72";//DEBUG

	//Test Case 4
	//DEBUG: Example of GPRMC data with a BAD checksum to test this function. Uncomment to use.
	//String original = "GPRMC,142101.600,A,3916.2226,N,07636.6530,W,0.33,0.00,271116,,,A*71";//DEBUG


	//Initialize variable(s)
	gpsDataIndex = GPS_HEADER_FIELD;

	//Data Filtering
	//Note: Only keep and process GPGGA or GPRMC data. Ignore everything else.
	if (!dataPassedFiltering(original, gpsData[gpsDataIndex]))//Save the GPS Header (outputString) into gpsData[gpsDataIndex] where gpsDataIndex = 0;
	{
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
	
	//Serial.println(dataString);//DEBUG

	//Note: dataString is the GPS data without the $ at the beginning or the ending part (i.e. without the * or anything after, like the checksum)
	
	//Note: Since GPGGA has a comma before the * but GPRMC doesn't, will have to have different algorithms string parsing for the two types

	if (gpsData[GPS_HEADER_FIELD] == GPS_HD_FIXED_DATA)//for GPGGA data
	{
		//FINISH WRITING ME

		/*

		while(endIndex >= 0)
		{
		endIndex = dataString.indexOf(',', startIndex);//search for the first/next comma
		//Serial.println(temp1);//DEBUG
		//Serial.println(startIndex);//DEBUG
		//Serial.println(endIndex);//DEBUG

		gpsData[i] = dataString.substring(startIndex, endIndex);//grab the substring the start and the first commas (for the first field) or the substring between two commas

		dataString = dataString.substring(endIndex + 1);//skip over the current comma

		//Serial.print("Data: ");//DEBUG
		//Serial.println(i);//DEBUG
		//Serial.println(gpsData[i]);//DEBUG

		}

		*/

	}
	else if (gpsData[GPS_HEADER_FIELD] == GPS_HD_MIN_RECOMMENDED_DATA)//For GPRMC data
	{
		//FINISH WRITING ME
	}
	else
	{
		//do nothing as this is an error
	}

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

boolean dataPassedFiltering(String inputString, String & outputString)
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
	endIndex = inputString.indexOf(',', startIndex);
	//Grab the GPS Header
	tempString = inputString.substring(startIndex, endIndex);//grab the substring from the start to the first comma

	if (tempString.equals(GPS_HD_FIXED_DATA) || tempString.equals(GPS_HD_MIN_RECOMMENDED_DATA))
	{
		outputString = tempString;
		return true;
	}
	else
	{
		outputString = "";
		return false;
	}
}