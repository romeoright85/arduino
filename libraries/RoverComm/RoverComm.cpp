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
	//Note: For some reason I couldn't call this->getRxData().concat(dataIn), so I got rid of the method getRxData() that was used to return _rxDataString and I am manually calling _rxDataString
	this->_rxDataString.concat(dataIn);		
}

void RoverComm::setRxData(String stringIn)
{
	this->_rxDataString = stringIn;
	
}
void RoverComm::reset()
{
		this->_rxDataString = "";
		this->_destinationCommType = ROVERCOMM_NONE;
		this->_dataIsValid = false;
		
}
byte RoverComm::getDestinationCommType()
{
	return _destinationCommType;
}

void RoverComm::validateData()
{
	
	byte commandType;
	
	
	
	
	this->_rxDataString.trim();//remove any leading and trailing whitespaces
	
	//check to see if the data is empty
	if(this->_rxDataString.equals(""))
	{
			//the string was empty
			this->_rxRoverDataPointer->setCommType(ROVERCOMM_NONE);
			this->_dataIsValid = false;//sets the flag for whether the data is valid or not
			this->_rxRoverDataPointer->setData("");//clear the RoverData since there is no data			
			this->_rxDataString = "";//clear RoverComm's _rxDataString before exiting this function
			return;//end the data validation if the RoverComm Type is invalid, no reason to move on
	}
			
	//==Process for IMU AHRS Data Format==	
	if( this->_rxDataString.substring(0,5) == "!ANG:" )
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
		this->_rxDataString = "";//clear RoverComm's _rxDataString before exiting this function
		return;

	}//end if
	//==Process for the Rover Data Format==		
	else if(  this->_rxDataString.substring(0,1) == "/" && this->_rxDataString.substring(2,3) == "c" && this->_rxDataString.substring(6,7) == "*" )//DEBUG
	{	

		#ifdef _DEBUG_OUTPUT_RXDATA_
			Serial.println(F("Raw Rx Data:"));//DEBUG
			Serial.println(this->_rxDataString);//DEBUG
		#endif

	//check for correct format - for proper delimeters, /-c---*-..., where - are don't cares and ... means the length may vary
	//else if the rover data format was correct, continue	
		//parse out the message's destination, RoverComm Type (i.e. destination ID)
		commandType = this->_rxDataString.substring(3,4).toInt();//convert the string to a number. If the string isn't a valid number, the default output is 0

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
				this->_rxRoverDataPointer->setData("");//clear the RoverData since there is no data			
				this->_rxDataString = "";//clear RoverComm's _rxDataString before exiting this function
				return;//end the data validation if the RoverComm Type is invalid, no reason to move on
		}//end switch
		
		//For valid RoverComm Types
		this->_dataIsValid = true;//sets the flag for whether the data is valid or not
		this->_rxRoverDataPointer->setData(this->_rxDataString);//save the raw data to the RoverData object
		this->_rxDataString = "";//clear RoverComm's _rxDataString before exiting this function
		return;
			
	}//end else if
	else
	{

		//else the data format was incorrect
		
		this->_rxRoverDataPointer->setCommType(ROVERCOMM_NONE);
		this->_dataIsValid = false;//sets the flag for whether the data is valid or not
		this->_rxRoverDataPointer->setData("");//clear the RoverData since there is no data			
		this->_rxDataString = "";//clear RoverComm's _rxDataString before exiting this function
		return;//end the data validation if the RoverComm Type is invalid, no reason to move on
		
	}//end else	
}
boolean RoverComm::isDataValid()
{
	return this->_dataIsValid;
}

		
		
		
		
		
		