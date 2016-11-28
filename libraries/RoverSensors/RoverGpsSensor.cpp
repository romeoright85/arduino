#include <RoverGpsSensor.h>


RoverGpsSensor::RoverGpsSensor()
{
	this->reset();
}
RoverGpsSensor::~RoverGpsSensor()
{
	//do nothing
}
void RoverGpsSensor::reset()
{
	
	//Flags
	this->_validChecksum = false;
	//GPS Data
	this->clearGpsDataString();
	//Parsed data
	this->_validData = false;	
	this->_timeWhenDataWasFixed = 0;
	this->_latitude = 0.0;
	this->_longitude = 0.0;
	this->_direction = GPS_DIR_UNKOWN;
	this->_fixQuality = GPS_FQ_INVALID;
	this->_sattelitesTracked = 0;
	this->_altitude = 0.0;
	this->_rxChecksum = 0;
	
	
}
void RoverGpsSensor::clearGpsDataString()
{
		this->_rxData = "";
}
void RoverGpsSensor::appendToRxGPSData(char dataIn)
{
		this->_rxData.concat(dataIn);		
}
boolean RoverGpsSensor::processRxGPSData()
{
//Parse gps data
//Example Raw Data: $GPGGA,142103.400,3916.2242,N,07636.6542,W,1,3,3.90,183.6,M,-33.6,M,,*6B
//Example Data Received by this function: GPGGA,142103.400,3916.2242,N,07636.6542,W,1,3,3.90,183.6,M,-33.6,M,,*6B
	//Note: The data starts after the $ since the code that runs before this function will strip out the $	
//Reference:
//https://www.arduino.cc/en/Reference/StringObject
//http://stackoverflow.com/questions/11068450/arduino-c-language-parsing-string-with-delimiter-input-through-serial-interfa



	byte commaIndex;

	commaIndex = this->_rxData.indexOf(',');
= this->_rxData.substring(0,commaIndex);
	
	

//WRITE ME LATER		
//reference
//split string
//http://stackoverflow.com/questions/11068450/arduino-c-language-parsing-string-with-delimiter-input-through-serial-interfa
//decimal to hex

//use these defines for your gps header detection
//remember $ won't be included in the data string
//		#define GPS_HD_FIXED_DATA						"GPGGA"
//		#define GPS_HD_MIN_RECOMMENDED_DATA	"GPRMC"


	
	
	
	
	
	
//	this->_validData = ??
//	this->_timeWhenDataWasFixed = ??
//	this->_latitude = ??
//	this->_longitude = ??
//	this->_direction = ??
//	this->_fixQuality = ??
//	this->_sattelitesTracked = ??
//	this->_altitude = ??
//	this->_rxChecksum = ??
	
	
	
	
	//Return from the function if the GPS data is invalid (status is extracted from the parsed GPS data) or the GPS checksum is invalid
	if(!this->validateChecksum() || !this->isGpsDataValid())
	{
		//End the function if 
		this->reset();//clear the gps data
		return false;
	}//end if
	else
	{
		//Clear the GPS data string for future use
		this->clearGpsDataString();
		return true;
	}//end else	
		
}
boolean RoverGpsSensor::isGpsDataValid()
{	
	return this->_validData;
}
int RoverGpsSensor::getGpsTimeWhenDataWasFixed()
{	
	return this->_timeWhenDataWasFixed;
}
double RoverGpsSensor::getGpsLatitude()
{	
	return this->_latitude;
}
double RoverGpsSensor::getGpsLongitude()
{	
	return this->_longitude;
}
byte RoverGpsSensor::getGpsDirection()
{	
	return this->_direction;
}
byte RoverGpsSensor::getGpsFixQuality()
{	
	return this->_fixQuality;	
}
byte RoverGpsSensor::getGpsSatellitesTracked()
{
	return this->_sattelitesTracked;
}
double RoverGpsSensor::getGpsAltitude()
{
	return this->_altitude;
}
boolean RoverGpsSensor::validateChecksum()
{
	
	byte calculcatedChecksum = 0;
	
//WRITE HOW TO CHECK THE CHECKSUM LATER
//REFERENCE: K:\Working Directory\DESIGN_PROJ\Design Projects\Robot\Workspaces\Arduino\GPS_Arduino_MEGAv21

//calculcatedChecksum = ???
	
	if(	this->_rxChecksum == calculcatedChecksum)//DEBUG, write me later
	{
		this->_validChecksum = true;
	}
	else
	{
		this->_validChecksum = false;
	}
	return this->_validChecksum;
}
