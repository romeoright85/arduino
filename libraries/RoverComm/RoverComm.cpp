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
byte RoverComm::getRxDataLength()
{	
	return sizeof(this->_rxDataString);
}
void RoverComm::reset()
{
		this->clearRxData();
		this->_destinationCommType = ROVERCOMM_NONE;
		this->_dataIsValid = false;
		
}
byte RoverComm::getDestinationCommType()
{
	return _destinationCommType;
}

void RoverComm::validateData()
{
	char tempSubstring1[BUFFER_SIZE_4];
	char tempSubstring2[BUFFER_SIZE_1];	
	char tempSubstring3[BUFFER_SIZE_1];	
	char tempSubstring4[BUFFER_SIZE_1];	
	char tempSubstring5[BUFFER_SIZE_1];	
	
	byte commandType;
	
	CharArray::Trim(this->_rxDataString);//remove any leading and trailing whitespaces
	
	//check to see if the data is empty
	if(strcmp(this->_rxDataString,"") == 0)
	{
			//the string was empty
			this->_rxRoverDataPointer->setCommType(ROVERCOMM_NONE);
			this->_dataIsValid = false;//sets the flag for whether the data is valid or not
 			this->_rxRoverDataPointer->clearData();//clear the RoverData since there is no data			
			this->clearRxDataVariables();//clear RoverComm's _rxDataString and index before exiting this function
			return;//end the data validation if the RoverComm Type is invalid, no reason to move on
	}
			
	//==Process for IMU AHRS Data Format==	

	
	//Process Substring Extractions for use with if/else statements below
	CharArray::substring(this->_rxDataString, this->getRxDataLength(), 0, 5, tempSubstring1);//get the first 4 characters
	CharArray::substring(this->_rxDataString, this->getRxDataLength(), 0, 1, tempSubstring2);//get the 1st character
	CharArray::substring(this->_rxDataString, this->getRxDataLength(), 2, 3, tempSubstring3);//get the 3rd character
	CharArray::substring(this->_rxDataString, this->getRxDataLength(), 6, 7, tempSubstring4);//get the 7th character
	CharArray::substring(this->_rxDataString, this->getRxDataLength(), 3, 4, tempSubstring5);//get the 4th character
	
	if( strcmp(tempSubstring1,"!ANG:") == 0 )//compare the first 4 characters to see if it starts with "!ANG:", which means it's IMU data
	{
		//check for correct format - !ANG:...
		//if the rover data format was correct, continue		
		
		#ifdef _DEBUG_OUTPUT_RXDATA_
			Serial.println(F("Raw Rx Data:"));//DEBUG
			Serial.println(this->_rxDataString);//DEBUG
		#endif

		
		//Reroute the IMU AHRS data to CMNC	
		//set the RoverComm Type in the RoverData object
		this->_rxRoverDataPointer->setCommType(ROVERCOMM_CMNC);
		
		
		this->_dataIsValid = true;//sets the flag for whether the data is valid or not
		this->_rxRoverDataPointer->setData(this->_rxDataString);//save the raw data to the RoverData object
		this->clearRxDataVariables();//clear RoverComm's _rxDataString and index before exiting this function
		return;

	}//end if
	//==Process for the Rover Data Format==				
	else if( strcmp(tempSubstring2,"/") == 0 && strcmp(tempSubstring3,"c") && strcmp(tempSubstring4,"*")
	{	

		#ifdef _DEBUG_OUTPUT_RXDATA_
			Serial.println(F("Raw Rx Data:"));//DEBUG
			Serial.println(this->_rxDataString);//DEBUG
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
				this->_dataIsValid = false;//sets the flag for whether the data is valid or not
				this->_rxRoverDataPointer->clearData();//clear the RoverData since there is no data			
				this->clearRxDataVariables();//clear RoverComm's _rxDataString and index before exiting this function
				return;//end the data validation if the RoverComm Type is invalid, no reason to move on
		}//end switch
		
		//For valid RoverComm Types
		this->_dataIsValid = true;//sets the flag for whether the data is valid or not
		this->_rxRoverDataPointer->setData(this->_rxDataString);//save the raw data to the RoverData object
		this->clearRxDataVariables();//clear RoverComm's _rxDataString and index before exiting this function
		return;
			
	}//end else if
	else
	{

		//else the data format was incorrect
		
		this->_rxRoverDataPointer->setCommType(ROVERCOMM_NONE);
		this->_dataIsValid = false;//sets the flag for whether the data is valid or not
		this->_rxRoverDataPointer->clearData();//clear the RoverData since there is no data			
		this->clearRxDataVariables();//clear RoverComm's _rxDataString and index before exiting this function
		return;//end the data validation if the RoverComm Type is invalid, no reason to move on
		
	}//end else	
}
boolean RoverComm::isDataValid()
{
	return this->_dataIsValid;
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
		
		
		