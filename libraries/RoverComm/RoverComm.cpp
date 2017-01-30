#include <RoverComm.h>


RoverComm::RoverComm(RoverData * roverData )
{	
	this->_rxRoverDataPointer = roverData;//saving the RoverData pointer for the received data
}
RoverComm::~RoverComm()
{
	//do nothing
}
void RoverComm::appendToRxData(char dataIn)
{
	
	if(this->_rxDataStringCharacterIndex <= ROVER_DATA_BUFFER_SIZE)//make sure there is no buffer overflow
	{
		this->_rxDataString[this->_rxDataStringCharacterIndex] = dataIn;
		this->_rxDataStringCharacterIndex++;//move the cursor to the next position in the array		
	}
	else
	{
		Serial.println(F("BuffOvrFlw"));
	}

}
void RoverComm::setRxData(char * dataString, byte arraySize)
{	
	strncpy(this->_rxDataString, dataString, arraySize);	
}
char * RoverComm::getRxData()
{	
	return this->_rxDataString;
}
int RoverComm::getRxDataLength()
{	
	return CharArray::stringSize(this->_rxDataString,sizeof(this->_rxDataString));
}
void RoverComm::reset()
{
		this->clearRxData();
		this->_destinationCommType = ROVERCOMM_NONE;		
}
byte RoverComm::getDestinationCommType()
{
	return _destinationCommType;
}

boolean RoverComm::validateData()
{
	char tempSubstring1[BUFFER_SIZE_6];
	char tempSubstring2[BUFFER_SIZE_2];	
	char tempSubstring3[BUFFER_SIZE_2];	
	char tempSubstring4[BUFFER_SIZE_2];	
	char tempSubstring5[BUFFER_SIZE_2];	
	
	byte commandType;

	#ifdef _DEBUG_OUTPUT_RXDATA_
		Serial.println(F("Pre Trim Rx Data:"));//DEBUG
		Serial.println(this->_rxDataString);//DEBUG
		Serial.println(F("Data length:"));//DEBUG
		Serial.println(this->getRxDataLength());//DEBUG
	#endif

	
	CharArray::Trim(this->_rxDataString);//remove any leading and trailing whitespaces
	
	#ifdef _DEBUG_OUTPUT_RXDATA_
		Serial.println(F("Post Trim Rx Data:"));//DEBUG
		Serial.println(this->_rxDataString);//DEBUG
		Serial.println(F("Data length:"));//DEBUG
		Serial.println(this->getRxDataLength());//DEBUG		
	#endif
	
	//check to see if the data is empty
	if(strcmp(this->_rxDataString,"") == 0)
	{
		#ifdef _DEBUG_RX_STAGES_
			Serial.println(F("Empty Rx Data"));//DEBUG			
		#endif
		
		//the string was empty
		this->_rxRoverDataPointer->setCommType(ROVERCOMM_NONE);			
		this->_rxRoverDataPointer->clearData();//clear the RoverData since there is no data			
		this->clearRxDataVariables();//clear RoverComm's _rxDataString and index before exiting this function
		return false;//end the data validation if the RoverComm Type is invalid, no reason to move on. Returns false for invalid data.
	}
			
	//==Process for IMU AHRS Data Format==	

	
	//Process Substring Extractions for use with if/else statements below
	CharArray::substring(this->_rxDataString, this->getRxDataLength(), 0, 5, tempSubstring1);//get the first 4 characters
	CharArray::substring(this->_rxDataString, this->getRxDataLength(), 0, 1, tempSubstring2);//get the 1st character
	CharArray::substring(this->_rxDataString, this->getRxDataLength(), 2, 3, tempSubstring3);//get the 3rd character
	CharArray::substring(this->_rxDataString, this->getRxDataLength(), 6, 7, tempSubstring4);//get the 7th character
	CharArray::substring(this->_rxDataString, this->getRxDataLength(), 3, 4, tempSubstring5);//get the 4th character

	#ifdef _DEBUG_SHOW_TEMPSUBSTRINGS_
		Serial.println(F("Tempsubstring 1:"));//DEBUG
		Serial.println(tempSubstring1);//DEBUG	
		Serial.println(F("Tempsubstring 2:"));//DEBUG
		Serial.println(tempSubstring2);//DEBUG	
		Serial.println(F("Tempsubstring 3:"));//DEBUG
		Serial.println(tempSubstring3);//DEBUG	
		Serial.println(F("Tempsubstring 4:"));//DEBUG
		Serial.println(tempSubstring4);//DEBUG	
		Serial.println(F("Tempsubstring 5:"));//DEBUG
		Serial.println(tempSubstring5);//DEBUG	
	#endif
	
	if( strcmp(tempSubstring1,"!ANG:") == 0 )//compare the first 4 characters to see if it starts with "!ANG:", which means it's IMU data
	{
		//check for correct format - !ANG:...
		//if the rover data format was correct, continue		
		
		#ifdef _DEBUG_RX_STAGES_
			Serial.println(F("IMU Rx Data"));//DEBUG			
		#endif

		
		//Reroute the IMU AHRS data to CMNC	
		//set the RoverComm Type in the RoverData object
		this->_rxRoverDataPointer->setCommType(ROVERCOMM_CMNC);				
		this->_rxRoverDataPointer->setData(this->_rxDataString, this->getRxDataLength());//save the raw data to the RoverData object
		this->clearRxDataVariables();//clear RoverComm's _rxDataString and index before exiting this function
		return true;//Returns true for valid data.

	}//end if
	//==Process for the Rover Data Format==				
	else if( strcmp(tempSubstring2,"/") == 0 && strcmp(tempSubstring3,"c") == 0 && strcmp(tempSubstring4,"*") == 0)
	{	

		#ifdef _DEBUG_RX_STAGES_
			Serial.println(F("Cmd Rx Data"));//DEBUG			
		#endif

	//check for correct format - for proper delimeters, /-c---*-..., where - are don't cares and ... means the length may vary
	//else if the rover data format was correct, continue	
		//parse out the message's destination, RoverComm Type (i.e. destination ID)
		
		commandType = atoi(tempSubstring5);//convert the string to a number. If the string isn't a valid number, the default output is 0.

		#ifdef _DEBUG_OUTPUT_CMDTYPE_
			Serial.println(F("commandType:"));//DEBUG
			Serial.println(commandType);//DEBUG
		#endif

		
		
		//check RoverComm type validity and then store the RoverComm Type in the RoverData object
		switch(commandType)
		{
			case ROVERCOMM_CMNC:
				this->_rxRoverDataPointer->setCommType(ROVERCOMM_CMNC);
			break;
			case ROVERCOMM_NAVI:
				this->_rxRoverDataPointer->setCommType(ROVERCOMM_NAVI);
			break;
			case ROVERCOMM_AUXI:
				this->_rxRoverDataPointer->setCommType(ROVERCOMM_AUXI);
			break;
			case ROVERCOMM_MAIN:
				this->_rxRoverDataPointer->setCommType(ROVERCOMM_MAIN);
			break ;
			case ROVERCOMM_COMM:
				this->_rxRoverDataPointer->setCommType(ROVERCOMM_COMM);
			break;
			default:
				//the RoverComm Type didn't match any of the results
				this->_rxRoverDataPointer->setCommType(ROVERCOMM_NONE);				
				this->_rxRoverDataPointer->clearData();//clear the RoverData since there is no data			
				this->clearRxDataVariables();//clear RoverComm's _rxDataString and index before exiting this function
				return false;//end the data validation if the RoverComm Type is invalid, no reason to move on. Returns false for invalid data.
		}//end switch
		
		//For valid RoverComm Types		
		this->_rxRoverDataPointer->setData(this->_rxDataString, this->getRxDataLength());//save the raw data to the RoverData object
		this->clearRxDataVariables();//clear RoverComm's _rxDataString and index before exiting this function
		return true;//Returns true for valid data.
			
	}//end else if
	else
	{
		#ifdef _DEBUG_RX_STAGES_
			Serial.println(F("Not Valid Rx Data"));//DEBUG			
		#endif
		
		//else the data format was incorrect
		
		this->_rxRoverDataPointer->setCommType(ROVERCOMM_NONE);
		
		this->_rxRoverDataPointer->clearData();//clear the RoverData since there is no data			
		this->clearRxDataVariables();//clear RoverComm's _rxDataString and index before exiting this function
		return false;//end the data validation if the RoverComm Type is invalid, no reason to move on. Returns false for invalid data.
		
	}//end else	
}
void RoverComm::clearRxData()
{		 
	memset(this->_rxDataString,0,sizeof(this->_rxDataString));	
}
		
void RoverComm::clearRxDataVariables()
{
	
	this->_rxDataStringCharacterIndex = 0;
	
	clearRxData();	
}
		
		
		