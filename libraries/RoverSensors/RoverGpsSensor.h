//RoverGpsSensor.h
#ifndef _ROVERGPSSENSOR_H
#define _ROVERGPSSENSOR_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <CharArray.h>


#define _GPS_SENSOR


//Uncomment debug flags below to use them
//#define _DEBUG_OUTPUT_PRE_FILTERED_RAW_RX_DATA
//#define _DEBUG_OUTPUT_PARSED_HEADER
//#define _DEBUG_OUTPUT_FILTERED_DATA_STATUS
//#define _DEBUG_OUTPUT_POST_FILTERED_RAW_RX_DATA
//#define _DEBUG_OUTPUT_PARSING_PROCESS
//#define _DEBUG_OUTPUT_PARSED_GPS_DATA_ARRAY




//Note: I use the term string, when it's really stored in a char array. But I still consider the actual data a string (while being implemented as a char array due to Arduino limitations).

//Reference:
//http://www.gpsinformation.org/dale/nmea.htm
//http://aprs.gids.nl/nmea/
//http://googlecompass.com/MagneticVariationAdjustment.htm

/*
To view in Google Maps

Example Data:

Latitude: 3916.10N
Longitude: 7636.66W

Convert to and search for in Google Maps:

39 16.10 N, 76 36.66 W


Remember: Latitude is 0 to 90 and Longitude is 0 to 180. So Grab the first two characters for longitude and the first three characters for longitude.


https://support.google.com/maps/answer/18539?co=GENIE.Platform%3DDesktop&hl=en

*/

/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/
//define Arduino 1: NAVI in order to use it's config pins
#ifndef _ARD_1_NAVI_H
	#define _ARD_1_NAVI_H
#endif


/********************************************************************/

#include <RoverConfig.h>


//This class parses GPS data
class RoverGpsSensor : public virtual RoverReset {
public:
	RoverGpsSensor();//constructor
	~RoverGpsSensor();//destructor
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)	
	void appendToRxGPSData(char);//append a char to the _rxData string
	void setRxGPSData(char *, byte);//used for debugging, sets the _rxData string to a value (charArray, array size)
	char * getRxGPSData();//print _rxData string
	boolean processRxGPSData();//processes/parses the received gps _rxData string. Returns true if the data is valid
	boolean isGpsDataValid();//Checks the GPS Status and the Fix Quality to see if the data is valid. Usually ran internal to the class (privately), but can be ran outside the class if needed (publicly).
	char * getGpsSentenceId();//returns the GPS sentence ID
	double getGpsTimeWhenDataWasFixed();//returns the time the data was fixed	
	double getGpsLatitude();//returns the gps latitude
	char  getGpsLatitudeDirection();//returns the gps latitude direction	
	double getGpsLongitude();//returns the gps longitude
	char getGpsLongitudeDirection();//returns the gps longitude direction	
	byte getGpsFixQuality(); //returns the gps fix quality (gps fix quality types defined in RoverConfig)
	byte getGpsSatellitesTracked();//returns the number of gps satellites being tracked	
	char * getGoogleMapsCoordinates();//returns the latitude, longitude, and corresponding directions in Google Maps Friendly Format
	
	
//	char _rxData[GPS_DATA_CHAR_BUFFER_SIZE];//DEBUG

	
private:
	//Non-SW Resettable
	void clearGpsDataArray();//clears the GPS Helper Variables
	void clearRxGpsDataString();//clears the _rxData string
	boolean dataPassedFiltering(char *, byte);//(input: received GPS data, array size) returns true if the data passes the filtering (only GPGGA is passed through, everything else is discarded).
	
	


	//SW Resettable
	//Flags
	boolean _validChecksum;	
	//GPS Received Data
	char _rxData[GPS_DATA_CHAR_BUFFER_SIZE];
	//GPS Helper Variables		
	char _gpsDataArray[GPS_GPGGA_FIELDS][GPS_DATA_CHAR_BUFFER_SIZE];//array of character arrays, (max) field size is 14, but using only the first 8 fields for GPGGA (since sometimes the data gets corrupted and doesn't complete the transmission), from 0 to 7.
	
		
};

#endif 