#include <DataType.h>


DataType::DataType()
{
	//do nothing
}
DataType::~DataType()
{
	//do nothing
}
char DataType::byteToChar(byte num)
{
	if(num >= 0 && num <= 9)//in range of hexidecimal (0 to 15)
	{
		//Using delegation and calling byteToHex(), but just with a more limited range (subset of the Hexidecimal range)
		return byteToHex(num);
	}//end if
	else//out of range of decimal
	{
		return 'Z';//error
	}//end else
}//end of byteToChar()
char DataType::byteToHex(byte num)
{
	if(num >= 0 && num <= 15)//in range of hexidecimal (0 to 15)
	{
		switch(num)
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
			break;
		}
	}//end if
	else//out of range of hexidecimal
	{
		return 'Z';//error
	}//end else
}//end of byteToHex()
byte DataType::byteToChars(byte num, char * tempCharArray, byte arraySize)
{
		
	if(arraySize < 4)//you need at least 4 bytes for the three characters and the null terminator
	{		
		//don't return an error message im the tempCharArray as you might not be able to fit the error in the message. Just Serial.println() the error.
		Serial.println(F("Err"));
		return 0;//return 0 for false, there was an error
	}//end if
	
	//No need no check if it's within the byte range, the data type itself will handle that. If it's out of range, you will get a strange value for num as a paramater anyways before even going into the function

	byte hundreds = num / 100;
	byte temp = (num - hundreds * 100);
	byte tens = temp / 10;
	byte ones = temp % 10;
		
		
	tempCharArray[0] = DataType::byteToChar(hundreds);
	tempCharArray[1] = DataType::byteToChar(tens);
	tempCharArray[2] = DataType::byteToChar(ones);			
	//Add the null terminating character
	tempCharArray[3] = '\0';
	return 1;//return 1 for true, there were no errors
}//end of byteToChars()
byte DataType::charsToByte(char * inputCharArray)
{
	
	int tempInt;//temporary integer
	//Convert the char array to a byte (which has a range from 0 to 255)
	tempInt = atoi(inputCharArray);
	if( tempInt > 255 || tempInt < 0 )
	{
		return 0;
	}//end if
	else
	{
		return (byte) tempInt;
	}//end else

}//end of charsToByte()
byte DataType::charToByte(char inputChar)
{
	switch(inputChar)
	{
		case '0':
			return 0;
		break;
		case '1':
			return 1;
		break;
		case '2':
			return 2;
		break;
		case '3':
			return 3;
		break;
		case '4':
			return 4;
		break;
		case '5':
			return 5;
		break;
		case '6':
			return 6;
		break;
		case '7':
			return 7;
		break;
		case '8':
			return 8;
		break;
		case '9':
			return 9;
		break;
		default:
			return 0;//default
		break;
	}//end switch
}//end of charToByte()