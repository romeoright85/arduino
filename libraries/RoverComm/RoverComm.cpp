#include <RoverComm.h>


RoverComm::RoverComm(RoverData * roverData )
{	
	this->_rxRoverDataPointer = roverData;//saving the RoverData pointer for the received data
}
RoverComm::~RoverComm()
{
	//do nothing
}
RoverData * RoverComm::getRoverDataObject()
{
	return this->_rxRoverDataPointer;
}//end getRoverDataObject()
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
		this->_rxDataStringCharacterIndex = 0;
		this->clearRxData();		
}


boolean RoverComm::parseAndValidateData()
{
	//Note: Need char length + 1 since the terminating char /0 is added on with CharArray::substring()
	char imuSubstringANG[BUFFER_SIZE_6];
	char dataFrameFwdSlash[BUFFER_SIZE_2];
	char dataFrameLowercaseC[BUFFER_SIZE_2];
	char dataFrameAsterisk[BUFFER_SIZE_2];
	char cmdDataOriginRvrComm[BUFFER_SIZE_2];
	char cmdDataDestinationRvrComm[BUFFER_SIZE_2];
	char cmdDataCommandDataCharArray[_MAX_ROVER_COMMAND_DATA_LEN_];
	char cmdDataCommandTagCharArray[CMD_DATA_CMD_TAG_ARRAY_SIZE];
	byte commandType;
	
	//Clears RoverData object
	this->_rxRoverDataPointer->reset();//clears the origin and destination rover comm type, the rover command data, and rover command tag before starting anything else

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
		this->_rxRoverDataPointer->reset();//clears the origin and destination rover comm type, the rover command data, and rover command tag		
		this->reset();//clear RoverComm's _rxDataString and index before exiting this function
		return false;//end the data validation if the RoverComm Type is invalid, no reason to move on. Returns false for invalid data.
	}
			
	//Rover Data Format
	//The format is /OcDLL*tttdddd... (Note: The d's can range from none to up to _MAX_ROVER_COMMAND_DATA_LEN_ - 1, i.e. 15-1=14. Minus 1 due to null character. So hence dddd....)
	
	//Process/Parse the received data into Substring for use with if/else statements below
	CharArray::substring(this->_rxDataString, this->getRxDataLength(), 0, 5, imuSubstringANG);//get the first 4 characters, to test to see if it's IMU data (i.e. "ANG!")
	CharArray::substring(this->_rxDataString, this->getRxDataLength(), 0, 1, dataFrameFwdSlash);//get the 0th element of the character array, to test to see if it's Rover Command Data Frame (i.e. '/')
	CharArray::substring(this->_rxDataString, this->getRxDataLength(), 2, 3, dataFrameLowercaseC);//get the 2nd element of the character array, to test to see if it's Rover Command Data Frame (i.e. 'c')
	CharArray::substring(this->_rxDataString, this->getRxDataLength(), 6, 7, dataFrameAsterisk);//get the 6th element of the character array, to test to see if it's Rover Command Data Frame (i.e. '*')
	CharArray::substring(this->_rxDataString, this->getRxDataLength(), 1, 2, cmdDataOriginRvrComm);//get the 1st element of the character array, the command data origin
	CharArray::substring(this->_rxDataString, this->getRxDataLength(), 3, 4, cmdDataDestinationRvrComm);//get the 3rd element of the character array, the command data destination

	#ifdef _DEBUG_SHOW_EXTRACTED_SUBSTRINGS_
		Serial.println(F("IMU Substring for ANG!:"));//DEBUG
		Serial.println(imuSubstringANG);//DEBUG	
		Serial.println(F("Data Frame for /:"));//DEBUG
		Serial.println(dataFrameFwdSlash);//DEBUG	
		Serial.println(F("Data Frame for c:"));//DEBUG
		Serial.println(dataFrameLowercaseC);//DEBUG	
		Serial.println(F("Data Frame for *:"));//DEBUG
		Serial.println(dataFrameAsterisk);//DEBUG	
		Serial.println(F("Origin Rover Comm:"));//DEBUG
		Serial.println(cmdDataOriginRvrComm);//DEBUG	
		Serial.println(F("Destination Rover Comm:"));//DEBUG
		Serial.println(cmdDataDestinationRvrComm);//DEBUG	
	#endif



	//==Process for IMU AHRS Data Format==	

	//Check to see if the received data has the !ANG format
	if( strcmp(imuSubstringANG,"!ANG:") == 0 )//compare the first 4 characters to see if it starts with "!ANG:", which means it's IMU data
	{
		//check for correct format - !ANG:...
		//if the rover data format was correct, continue		
		
		#ifdef _DEBUG_RX_STAGES_
			Serial.println(F("IMU Rx Data"));//DEBUG			
		#endif

		//Reroute the IMU AHRS data to CMNC	
		//set the destination RoverComm Type in the RoverData object		
		this->_rxRoverDataPointer->setDestinationCommType(ROVERCOMM_CMNC);		
		//move on with setting the IMU data
		this->_rxRoverDataPointer->setIMUData(this->_rxDataString, this->getRxDataLength());//save the raw data as the IMU data in the RoverData object
		//If the data is valid and true is being returned, then do not clear the data yet, as it might be used for redirection. Instead, data should be cleared before receiving new data (i.e. before rxData() is called)
		return true;//Returns true for valid data.
	}//end if
	//==Process for the Rover Data Format==	
	//Check to see if the received data has the /-c---* format, where - are don't cares as they're not part of the data frame
	else if( strcmp(dataFrameFwdSlash,"/") == 0 && strcmp(dataFrameLowercaseC,"c") == 0 && strcmp(dataFrameAsterisk,"*") == 0)
	{	

		#ifdef _DEBUG_RX_STAGES_
			Serial.println(F("Cmd Rx Data"));//DEBUG			
		#endif
		
		//validate the parsed command data origin Rover Comm Type (i.e. origin ID), then set it if it's valid	
		if( ! this->validateThenSetOriginRoverCommType(cmdDataOriginRvrComm) )//if the validateThenSetDestinationRoverCommType returned false
		{
			//the origin Rover Comm Type was invalid
			this->_rxRoverDataPointer->reset();//clears the origin and destination rover comm type, the rover command data, and rover command tag		
			this->reset();//clear RoverComm's _rxDataString and index before exiting this function
			return false;//end the data validation if the RoverComm Type is invalid, no reason to move on. Returns false for invalid data.		
		}//end if
		
		
		//validate the parsed command data destination Rover Comm Type (i.e. destination ID), then set it if it's valid
		if( ! this->validateThenSetDestinationRoverCommType(cmdDataDestinationRvrComm) )//if the validateThenSetDestinationRoverCommType returned false
		{
			//the destination Rover Comm Type was invalid
			this->_rxRoverDataPointer->reset();//clears the origin and destination rover comm type, the rover command data, and rover command tag		
			this->reset();//clear RoverComm's _rxDataString and index before exiting this function
			return false;//end the data validation if the RoverComm Type is invalid, no reason to move on. Returns false for invalid data.		
		}//end if
		
				
		#ifdef _DEBUG_OUTPUT_COMMAND_ORIGIN_
			Serial.print(F("Origin: "));//DEBUG
			Serial.println(this->_rxRoverDataPointer->getOriginCommType());//DEBUG
		#endif		
	
		#ifdef _DEBUG_OUTPUT_COMMAND_DESTINATION_
			Serial.print(F("Destination: "));//DEBUG
			Serial.println(this->_rxRoverDataPointer->getDestinationCommType());//DEBUG
		#endif

		
	
		//For valid origin and destination Rover Comm Types	
			
		//1. Set the rover command data
		//1a. Extract the command data from the _rxDataString
		CharArray::substring(this->_rxDataString, CharArray::stringSize(this->_rxDataString, this->getRxDataLength()), 10, cmdDataCommandDataCharArray);//With No End Index, goes to the end of the array or to the terminating character (input char array, array size, start index, output char array). Note the array size you can use the stringSize() function as a helper. Note: Start index can be as small as 0.
		//1b. Set the command data to the value of _commandData in the Rover Data object
		this->_rxRoverDataPointer->setCommandData(cmdDataCommandDataCharArray, sizeof(cmdDataCommandDataCharArray));
		
		//2. Set the rover command tag
		//2a. Extract the command tag from the _rxDataString
		CharArray::substring(this->_rxDataString, CharArray::stringSize(this->_rxDataString, this->getRxDataLength()), 7, 10, cmdDataCommandTagCharArray);//grab the first 3 numbers and stop before the 4th number (element 3)
		
		//2b. Convert the command tag char array to a byte and use it to set the value of _commandTag in the Rover Data object
		this->_rxRoverDataPointer->setCommandTag(DataType::charsToByte(cmdDataCommandTagCharArray));
		
		#ifdef _DEBUG_OUTPUT_COMMAND_TAG_
			Serial.print(F("Cmd Tag: "));//DEBUG
			Serial.println(this->_rxRoverDataPointer->getCommandTag());//DEBUG
		#endif	
		
		//If the data is valid and true is being returned, then do not clear the data yet, as it might be used for redirection. Instead, data should be cleared before receiving new data (i.e. before rxData() is called)
		return true;//Returns true for valid data.
			
	}//end else if
	else
	{
		#ifdef _DEBUG_RX_STAGES_
			Serial.println(F("Not Valid Rx Data"));//DEBUG			
		#endif
		
		//else the data format was incorrect. It was not in the correct format for rover command tag/data or imu data.
		this->_rxRoverDataPointer->reset();//clears the origin and destination rover comm type, the rover command data, and rover command tag	
		this->reset();//clear RoverComm's _rxDataString and index before exiting this function
		return false;//end the data validation if the RoverComm Type is invalid, no reason to move on. Returns false for invalid data.
		
	}//end else	
}
void RoverComm::clearRxData()
{		 
	memset(this->_rxDataString,0,sizeof(this->_rxDataString));	
}
boolean RoverComm::validateThenSetOriginRoverCommType(char * roverCommTypeCharArray)
{
	byte commandType = atoi(roverCommTypeCharArray);//convert the string to a number. If the string isn't a valid number, the default output is 0.	
	//check RoverComm type validity and then store the RoverComm Type in the RoverData object
	switch(commandType)
	{
		case ROVERCOMM_NONE:
			this->_rxRoverDataPointer->setOriginCommType(ROVERCOMM_NONE);			
		break;
		case ROVERCOMM_CMNC:
			this->_rxRoverDataPointer->setOriginCommType(ROVERCOMM_CMNC);			
		break;
		case ROVERCOMM_NAVI:
			this->_rxRoverDataPointer->setOriginCommType(ROVERCOMM_NAVI);			
		break;
		case ROVERCOMM_AUXI:
			this->_rxRoverDataPointer->setOriginCommType(ROVERCOMM_AUXI);			
		break;
		case ROVERCOMM_MAIN:
			this->_rxRoverDataPointer->setOriginCommType(ROVERCOMM_MAIN);			
		break ;
		case ROVERCOMM_COMM:
			this->_rxRoverDataPointer->setOriginCommType(ROVERCOMM_COMM);			
		break;
		case ROVERCOMM_PC_USB:
			this->_rxRoverDataPointer->setOriginCommType(ROVERCOMM_PC_USB);			
		break;
		default:
			//the RoverComm Type didn't match any of the results
			this->_rxRoverDataPointer->reset();//clears the origin and destination rover comm type, the rover command data, and rover command tag		
			this->reset();//clear RoverComm's _rxDataString and index before exiting this function
			return false;//end the data validation if the RoverComm Type is invalid, no reason to move on. Returns false for invalid data.
	}//end switch
	
	return true;		
}
boolean RoverComm::validateThenSetDestinationRoverCommType(char * roverCommTypeCharArray)
{
	byte commandType = atoi(roverCommTypeCharArray);//convert the string to a number. If the string isn't a valid number, the default output is 0.	
	//check RoverComm type validity and then store the RoverComm Type in the RoverData object
	switch(commandType)
	{
		case ROVERCOMM_NONE:
			this->_rxRoverDataPointer->setDestinationCommType(ROVERCOMM_NONE);			
		break;		
		case ROVERCOMM_CMNC:
			this->_rxRoverDataPointer->setDestinationCommType(ROVERCOMM_CMNC);			
		break;
		case ROVERCOMM_NAVI:
			this->_rxRoverDataPointer->setDestinationCommType(ROVERCOMM_NAVI);			
		break;
		case ROVERCOMM_AUXI:
			this->_rxRoverDataPointer->setDestinationCommType(ROVERCOMM_AUXI);			
		break;
		case ROVERCOMM_MAIN:
			this->_rxRoverDataPointer->setDestinationCommType(ROVERCOMM_MAIN);			
		break ;
		case ROVERCOMM_COMM:
			this->_rxRoverDataPointer->setDestinationCommType(ROVERCOMM_COMM);			
		break;
			case ROVERCOMM_PC_USB:
			this->_rxRoverDataPointer->setDestinationCommType(ROVERCOMM_PC_USB);			
		break;
		default:
			//the RoverComm Type didn't match any of the results
			this->_rxRoverDataPointer->reset();//clears the origin and destination rover comm type, the rover command data, and rover command tag		
			this->reset();//clear RoverComm's _rxDataString and index before exiting this function
			return false;//end the data validation if the RoverComm Type is invalid, no reason to move on. Returns false for invalid data.
	}//end switch
	
	return true;	
}