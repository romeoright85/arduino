#include <RoverComm.h>


/*
		==Data Format==
		The format is /OcDLL*CCCC... (Note: There could be more than four C's so hence CCCC...)
		The /, c, and * are format identifiers. For commands the headers are as such: /-c---*----
		The O shows the origin where the message came from (Origin ID): 0=CMNC (external), 1=NAVI (internal), 2=AUXI (internal), 3=MAIN (internal), 4=COMM (internal)
		The D shows the destination Arduino it's going to (Destination ID): 0=CMNC (external), 1=NAVI (internal), 2=AUXI (internal), 3=MAIN (internal), 4=COMM (internal)
		The LL shows command priority level it should be in the lookup table
		The C's (four or more) are the letters that designate the command. The length of the letters will be determined by the lookup's priority and destination
		
		
		(where - are don't cares and ... means it can vary in length)
		Any messages for
			CMNC: 
				/-c0--*----.... 
			NAVI:
				/-c1--*----.... 
			AUXI:
				/-c2--*----.... 
			MAIN:
				/-c3--*----.... 				
			COMM:
				/-c4--*----.... 
*/	
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
	_rxDataString.concat(dataIn);		
}


void RoverComm::reset()
{
		_rxDataString = "";
		_destinationCommType = ROVERCOMM_NONE;
		_dataIsValid = false;
		
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
			_dataIsValid = false;//sets the flag for whether the data is valid or not
			this->_rxRoverDataPointer->setData("");//clear the RoverData since there is no data			
			this->_rxDataString = "";//clear RoverComm's _rxDataString before exiting this function
			return;//end the data validation if the RoverComm Type is invalid, no reason to move on
	}
	
		
	//check for correct format - for proper delimeters, /-c---*-..., where - are don't cares and ... means the length may vary
	//if( !(( this->_rxDataString.substring(0,1)=="/" ) && ( this->_rxDataString.substring(2,3)=="c" ) && ( this->_rxDataString.substring(7,7)=="*" )) )
	if( !( this->_rxDataString.substring(0,1) == "/" && this->_rxDataString.substring(2,3) == "c" && this->_rxDataString.substring(6,7) == "*") )	//DEBUG
	{
			//the data format was incorrect
			this->_rxRoverDataPointer->setCommType(ROVERCOMM_NONE);
			_dataIsValid = false;//sets the flag for whether the data is valid or not
			this->_rxRoverDataPointer->setData("");//clear the RoverData since there is no data			
			this->_rxDataString = "";//clear RoverComm's _rxDataString before exiting this function
			return;//end the data validation if the RoverComm Type is invalid, no reason to move on
	}
	
	
	//parse out the destination RoverComm Type (i.e. destination ID)
	commandType = this->_rxDataString.substring(3,4).toInt();//convert the string to a number. If the string isn't a valid number, the default output is 0

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
			_dataIsValid = false;//sets the flag for whether the data is valid or not
			this->_rxRoverDataPointer->setData("");//clear the RoverData since there is no data			
			this->_rxDataString = "";//clear RoverComm's _rxDataString before exiting this function
			return;//end the data validation if the RoverComm Type is invalid, no reason to move on
	}//end switch
	
	//For valid RoverComm Types
	_dataIsValid = true;//sets the flag for whether the data is valid or not
	this->_rxRoverDataPointer->setData(this->_rxDataString);//save the raw data to the RoverData object
	this->_rxDataString = "";//clear RoverComm's _rxDataString before exiting this function
	return;
		
}
boolean RoverComm::isDataValid()
{
	return _dataIsValid;
}

		
		
		
		
		
		