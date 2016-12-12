//RoverGpsSensor.h
#ifndef _ROVERGPSSENSOR_H
#define _ROVERGPSSENSOR_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <string.h>


#define _GPS_SENSOR

//Reference:
//http://www.gpsinformation.org/dale/nmea.htm
//http://aprs.gids.nl/nmea/
//http://googlecompass.com/MagneticVariationAdjustment.htm

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
	boolean processRxGPSData();//processes/parses the received gps _rxData string. Returns true if the data is valid and the checksum is valid	
	boolean isGpsDataValid();//Checks the GPS Status and the Fix Quality to see if the data is valid. Usually ran internal to the class (privately), but can be ran outside the class if needed (publicly).
	unsigned int getGpsTimeWhenDataWasFixed();//returns the time the data was fixed
	char getGpsStatus();//returns either A = Active or V = Void	
	double getGpsLatitude();//returns the gps latitude
	char  getGpsLatitudeDirection();//returns the gps latitude direction	
	double getGpsLongitude();//returns the gps longitude
	char getGpsLongitudeDirection();//returns the gps longitude direction	
	byte getGpsFixQuality(); //returns the gps fix quality (gps fix quality types defined in RoverConfig)
	byte getGpsSatellitesTracked();//returns the number of gps satellites being tracked	
	double getGpsHorizontalDilution();//Horizontal dilution of position
	double getGpsAltitude();//returns the gps altitude
	char getGpsAltitudeUnit();//returns the unit of the Altitude (should be M)
	double getGpsSpeed();//returns speed over the ground in knots
	double getGpsGeoidHeight();//Height of geoid (mean sea level) above WGS84 ellipsoid
	char getGpsGeoidHeightUnit();//returns the unit of the Geoid Height (should be M)
	double getGpsTrackAngle();//returns Track angle in degrees True
	unsigned int getGpsDate();//returns Date - 23rd of March 1994
	String getGpsGPGGAChecksum();//returns the last received GPGGA checksum in hex.
	String getGpsGPRMCChecksum();//returns the last received GPGGA checksum in hex.
	
	
	
private:
	//Non-SW Resettable
	void clearGpsHelperVariables();//clears the GPS Helper Variables
	void clearRxGpsDataString();//clears the _rxData string
	void clearProcessedGpsDataArray();//clears the _gpsPostProcessedDataArrayArray	
	boolean dataPassedFiltering(String , String & );//(input: received GPS data, output: GPS header) returns true if the data passes the filtering (only GPGGA and GPRMC data is passed through, everything else is discarded). It also passes by reference the gps header (GPGGA, GPRMC, or <blank>)	
	boolean validateChecksum(String , String &, String & );//(input: received GPS data, output: GPS data between the $ and *, output: checksum in two digit hex). Returns true if the checksum is valid, else returns false. Also returns by reference the GPS data without the $ at the beginning or the ending part (i.e. without the * or anything after, like the checksum) and also by reference the two digit checksum hex that was extracted from the received GPS data.
	String twoDigitDecimalToHexConverter(byte);//returns the two digit hex of the two digit decimal
	char decimalToHex(byte);//returns the one digit hex of the single digit decimal
	//SW Resettable
	//Flags
	boolean _validChecksum;	
	//GPS Received Data
	String _rxData;
	//GPS Helper Variables
	byte _startIndex;
	byte _endIndex;	
	String _gpsPreProcessedDataArray[14];//(max) size 14, GPGGA is from 0 to 13 and GPRMC is from 0 to 10.
	   //Notes:
	   //For GPGGA 14 fields are used, the rest are not processed.
	   //For GPRMC 11 fields are used, the rest are not processed.
	String _gpsPostProcessedDataArray[18];//Persistent GPS Data (Shared between GPGGA and GPRMC, the common data fields are overwritten as they get updates). Size 18, from 0 to 17. 
	
	
	
};

#endif 