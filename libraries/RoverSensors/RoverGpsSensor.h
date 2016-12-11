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

//define Arduino 2: AUXI in order to use it's config pins
#ifndef _ARD_2_AUXI_H
	#define _ARD_2_AUXI_H
#endif

//define Arduino 3: MAIN in order to use it's config pins
#ifndef _ARD_3_MAIN_H
	#define _ARD_3_MAIN_H
#endif

//define Arduino 4: COMM in order to use it's config pins
#ifndef _ARD_4_COMM_H
	#define _ARD_4_COMM_H		
#endif

/********************************************************************/

#include <RoverConfig.h>


//This class parses GPS data
class RoverGpsSensor : public virtual RoverReset {
public:
	RoverGpsSensor();//constructor
	~RoverGpsSensor();//destructor
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	void clearGpsDataString();//clears the _rxData string
	void appendToRxGPSData(char);//append a char to the _rxData string
	boolean processRxGPSData();//processes/parses the received gps _rxData string. Returns true if the data is valid and the checksum is valid
	int getGpsTimeWhenDataWasFixed();//returns the time the data was fixed
	double getGpsLatitude();//returns the gps latitude
	double getGpsLongitude();//returns the gps longitude
	byte getGpsDirection(); //returns the gps direction (gps direction types defined in RoverConfig)
	byte getGpsFixQuality(); //returns the gps fix quality (gps fix quality types defined in RoverConfig)
	byte getGpsSatellitesTracked();//returns the number of gps satellites being tracked
	double getGpsAltitude();//returns the gps altitude
	
	
private:
	//Non-SW Resettable
	boolean validateChecksum();//returns true if the checksum is valid, else returns false (status is based on calculations)
	boolean isGpsDataValid();//returns true when GPS data is valid (status is extracted from the parsed GPS data)
	//SW Resettable
	//Flags
	boolean _validChecksum;
	//GPS data
	String _rxData;	
	//Parsed gps data
	boolean _validData;
	int _timeWhenDataWasFixed;
	double _latitude;
	double _longitude;
	byte _direction;
	byte _fixQuality;
	byte _sattelitesTracked;
	double _altitude;
	byte _rxChecksum;
	
	
	
};

#endif 