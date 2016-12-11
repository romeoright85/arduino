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
	
	
	
private:
	//Non-SW Resettable
	void clearGpsHelperVariables();//clears the GPS Helper Variables
	void clearRxGpsDataString();//clears the _rxData string
	void clearProcessedGpsDataArray();//clears the _gpsPostProcessedDataArrayArray
	void clearParsedGpsData();//clears all the gps data that was parsed	
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
	String _gpsPreProcessedDataArray[13];//size 15, from 0 to 12.
	   //Notes:
	   //For GPGGA there are 13 fields, the rest won't be used.
	   //For GPRMC there are 10 fields, the rest won't be used.	
	String _gpsPostProcessedDataArray[16];//Persistent GPS Data (Shared between GPGGA and GPRMC, the common data fields are overwritten as they get updates). Size 16, from 0 to 15. 
	//Persistent Parsed GPS Data Variables (GPGGA and GPRMC merged data)
	unsigned int _timeWhenDataWasFixed;
	char _gpsStatus;//A = Active, V = Void
	double _latitude;
	char _latitudeDirection;
	double _longitude;	
	char _longitudeDirection;	
	byte _fixQuality;
	//Fix quality:
		//0 = invalid
		//1 = GPS fix (SPS)
		//2 = DGPS fix
		//3 = PPS fix
		//4 = Real Time Kinematic
		//5 = Float RTK
		//6 = estimated (dead reckoning) (2.3 feature)
		//7 = Manual input mode
		//8 = Simulation mode				   
	byte _sattelitesTracked;
	double _horizontalDilution;
	double _altitude;
	char _altitudeUnit;
	double _speed;
	double _geoidHeight;
	char _geoidHeightUnit;
	double _trackAngle;
	unsigned int _date;
	String _rxChecksum;
	
	
};

#endif 