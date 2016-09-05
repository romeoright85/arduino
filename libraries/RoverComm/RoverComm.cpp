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
	this->getRxData() += dataIn;
}
String RoverComm::getTxData()
{	
	return _txDataString;
}
String RoverComm::getRxData()
{
	return _rxDataString;
}
void RoverComm::reset()
{
		//received data string
		_rxDataString = "";
		//transmit data strings
		_txDataString = "";
}
byte RoverComm::getDestinationCommType()
{
	return _destinationCommType;
}

void RoverComm::validateData()
{
	
	String rxDataString = this->getRxData();
		
	//WRITE ME LATER
	//check to see if the data is empty
	//check for correct format (i.e. has the correct delimeters and at the right locations)
	//parse out the destination RoverComm Type
	//check RoverComm type validity	
	//store the RoverComm Type in the RoverData object
	this->_rxRoverDataPointer->setCommType(ROVERCOMM_COMM);//DEBUG
	//sets the falg for whether the data is valid or not
	_dataIsValid = true;//DEBUG
}
boolean RoverComm::isDataValid()
{
	return _dataIsValid;
}

		
		
		
		
		
		
		
		
		