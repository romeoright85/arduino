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
RoverComm::RoverComm(byte commType, RoverData * roverData )
{	
	this->_thisUnit_CommType = commType;//set the RoverComm Type of this unit
	roverData = this->_thisUnit_RoverDataPointer;//saving this unit's RoverData pointer to the external pointer
}
RoverComm::~RoverComm()
{
	//do nothing
}
byte RoverComm::getThisUnitsCommType()
{
	return this->_thisUnit_CommType;
}
void RoverComm::appendToRxData(char dataIn, byte commType)
{
	this->getRxData(commType) += dataIn;
}
void RoverComm::processReceivedData()
{
	RoverData * rxRoverData = new RoverData();//create a new RoverData object for the received RoverData each time (it has to be destroyed manually later)
	String dataString;
	dataString = this->getRxData(ROVERCOMM_CMNC);//copy string (destination, source)
	byte rxCommType;
	
	rxRoverData->setData(dataString);//get the received CMNC data string and set it to the rxRoverData object's data string
	if(rxRoverData->validData())//validate the rxRoverData object's data by checking to see if the data is not empty and is in the correct format
	{
		rxCommType = rxRoverData->getCommType();//extract the RoverComm Type from the rxRoverData object
				
		if( rxCommType == this->getThisUnitsCommType() )//if the RoverComm type matches with the one for this unit (arduino)
		{			
			this->_thisUnit_RoverDataPointer = rxRoverData;//then set this unit's RoverData pointer to the address the current rxRoverData pointer is pointing to
			//IMPORTANT: manually delete the rxRoverData object later once it's done being used
		}
		else
		{
			//reroute the data if it's meant for another unit (arduino)
			dataSelector(rxCommType, ROVERCOMM_DATA_DIR_TX) = dataString;//copy the dataString to the corresponding transmit string based on the RoverComm Type.
			delete rxRoverData;//delete the rxRoverData now since you don't need it anymore
			
			this->_thisUnit_RoverDataPointer = NULL;//null out the pointer since it no longer has an object to point to
		}		
	}
	
}
String RoverComm::getTxData(byte commType)
{	
	return dataSelector(commType, ROVERCOMM_DATA_DIR_TX);
}
String RoverComm::getRxData(byte commType)
{
	return dataSelector(commType, ROVERCOMM_DATA_DIR_RX);
}
void RoverComm::reset()
{
		//received data strings
		this->_rxDataString_CMNC = "";
		this->_rxDataString_NAVI = "";
		this->_rxDataString_AUXI = "";
		this->_rxDataString_MAIN = "";
		this->_rxDataString_COMM = "";
		//transmit data strings
		this->_txDataString_CMNC = "";
		this->_txDataString_NAVI = "";
		this->_txDataString_AUXI = "";
		this->_txDataString_MAIN = "";
		this->_txDataString_COMM = "";	
		
		
		this->_thisUnit_RoverDataPointer = NULL;//null out the pointer
		
		//DEBUG, HOPEFULLY THIS WON'T CAUSE A MEMORY LEAK IF ANYTHING IT WAS ONCE POINTING TO IS NO LONGER BEING USED BUT WAS NOT DELETED
		
}
String RoverComm::dataSelector(byte commType, byte dataDirection)
{
	
	if(dataDirection == ROVERCOMM_DATA_DIR_RX)
	{
		switch(commType)
		{
			case ROVERCOMM_CMNC:
				return this->_rxDataString_CMNC;
			break;
			case ROVERCOMM_NAVI:
				return this->_rxDataString_NAVI;
			break;		
			case ROVERCOMM_AUXI:
				return this->_rxDataString_AUXI;
			break;	
			case ROVERCOMM_MAIN:
				return this->_rxDataString_MAIN;
			break;		
			case ROVERCOMM_COMM:
				return this->_rxDataString_COMM;
			break;				
			default:
				return "";//invalid response
		}//end switch
	}//end if
	else if(dataDirection == ROVERCOMM_DATA_DIR_TX)
	{
		switch(commType)
		{
			case ROVERCOMM_CMNC:
				return this->_txDataString_CMNC;
			break;
			case ROVERCOMM_NAVI:
				return this->_txDataString_NAVI;
			break;		
			case ROVERCOMM_AUXI:
				return this->_txDataString_AUXI;
			break;	
			case ROVERCOMM_MAIN:
				return this->_txDataString_MAIN;
			break;		
			case ROVERCOMM_COMM:
				return this->_txDataString_COMM;
			break;				
			default:
				return "";//invalid response
		}//end switch
	}//end else if
	else
	{
		return "";//invalid response
	}//end else
}


		
		
		
		
		
		
		
		
		
		
		