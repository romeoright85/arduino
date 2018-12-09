//Used for NAVI - 1

/*
Note:
If used with actual data and not fixed data, you need to program all three arduinos with its corresponding code
NavigationTester_MAIN
NavigationTester_AUXI
NavigationTester_NAVI
Else if you want to use the fixed test data, you only need to program:
RoverNavigationTester_NAVI


Troubleshooting:
If you get all 0.0000 or something weird for heading constantly, you might have forgotten to upload NavigationTes and NavigationTester_MAIN that is required in order to pass heading data over to NavigationTester_NAVI.


Also make sure #define _DEBUG_ALL_SERIALS_WITH_USB_SERIAL_ is commented out in RoverConfig.h 
*/

//Used for NAVI - 1

#include <RoverNavigation.h>
#include <RoverGpsSensor.h>
#include <CharArray.h>
#include <BubbleSort.h>

//How to get the longitude and latitude of a place
//https://support.google.com/maps/answer/18539?co=GENIE.Platform%3DDesktop&hl=en

/*
In this example the desired location is set to:
Desired Lat/Long in Degrees (Hersh's Pizza in South Baltimore)
39.268603, -76.611702
*/

#define DECIMAL_PRECISION	5
#define DESIRED_LATITUDE_COORDINATE 39.268603
#define DESIRED_LONGITUDE_COORDINATE -76.611702
#define COMPASS_DATA_CHAR_BUFFER_SIZE 10
#define COMPASS_SENTENCE_LENGTH 10

//Uncomment to use fixed test data, else if left uncommented, it will use actual the GPS Module's and IMU Compass's data
//#define _DEBUG_USE_FIXED_TEST_DATA





//Uncomment to hide the output when GPS data isn't ready
//Note: For the most part IMU data is always there. (sometimes if a data is bad this code might filter out some). But for GPS data since it needs satellite signals, then have the option to print the data only when the data is ready.
//Uncomment to hide the output when GPS data isn't ready
#define _HIDE_DATA_WHEN_GPS_NOT_READY


//Uncomment to print IMU Data Valid Status
#define _PRINT_IMU_DATA_VALID_STATUS


//Uncomment to print GPS Data Valid Status
#define _PRINT_GPS_DATA_VALID_STATUS


//Uncomment to print IMU Median Completed Status
#define _PRINT_IMU_MEDIAN_COMPLETED_STATUS

//Uncomment to print GPS Median Completed Status
#define _PRINT_GPS_MEDIAN_COMPLETED_STATUS



/*
--------------
When using the Fixed Test Data for Actual/Current Location
--------------
Example:
Actual Lat/Long in Degrees
39.268761, -76.606402 (lower right corner of Riverside Park in South Baltimore)
Desired Lat/Long in Degrees (Hersh's Pizza in South Baltimore)
39.268603, -76.611702
Actual Heading (arbitrarily chosen):
4.2800 degrees

RoverNavigation Calculated Result:
456.7968 m
Google Maps Calculated Result:
about 462.27 m

RoverNavigation Calculated Relative Heading:
-92.1686

Get Motor Steering:
30.0000

Get Motor Throttle:
30.0000



Note:
Use this tool to check your distance and true bearing.
https://www.sunearthtools.com/tools/distance.php

Just subtract actual rover bearing from true bearing to get relative bearing.

Actual Coordinate = The first coordinate in the tool
Desired Coordinate = the second coordinate (coordinate B) in the tool.


From the Rover:
Desired Lat: 39.2686
Desired Lon: -76.6117
Actual Lat: 39.2683
Actual Lon: -76.6111
and
Rover Heading: 158.8700



The results of Distance and True Bearing from the tool is:

Distance 61.5m
(True) Bearing = 302.86 degrees


When compared to the rover calculations is:

Distance: 63.2529
True Bearing: 299.3965

Which is very close.



And using the values from the tool with the meaured rover heading, the relative bearing is:

Formula:
	if abs(trueBearing-heading) > 180
		relativeBearing = -1*(trueBearing-heading)
	else
		relativeBearing = trueBearing-heading
	end if
Calculation:
	302.86-158.8700 = 143.99 (which is less than 180) so
	Relative Bearing: 143.99 degrees (from the tool)


Where as from the rover
	Relative Bearing: 140.5265
	
Which again is very close.

And just checking the steering, the distance is greater than 8 meters and the relative bearing is greater than 90 degrees, so we expect a sharp turn to the right (see map from the tool)

And that's what we get from the Rover:
Get Motor Steering: Sharp Right
Get Motor Throttle: Normal Speed
Rover Nav Status: Still Navigating


See link below for screen shots of the tool:
K:\Working Directory\DESIGN_PROJ\Design Projects\Robot\Workspaces\Arduino\2nd Gen Code\GitHub\arduino\Test Results\Recorded Data\NavigationTester Results 08-12-17v1

*/



/*
Example Output:

GPS Data Ready
========
Desired Lat: 39.26860
Desired Lon: -76.61170
Actual Lat: 39.27120
Actual Lon: -76.61065
Rover Heading: 251.97000
Distance: 302.83666
True Bearing: 197.43000
Relative Bearing: -54.53999
Get Motor Steering: Wide Left
Get Motor Throttle: Normal Speed
Rover Nav Status: Still Navigating

*/

//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast

#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ _MAIN_SERIAL_ //When using COMM Broadcast, reroute the PC USB output to the channel to MAIN instead
#else
	#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_
#endif


//Global Variables
RoverNavigation * roverNavigation = new RoverNavigation();
RoverGpsSensor * roverGps = new RoverGpsSensor();
double tempValue = 0.0;//temporary variable that is shared and used to print values, etc.



//flags counters and data arrays for GPS and heading data
byte headingDataCounter = 0;//counts the number of heading data collected (and averaged)
byte gpsDataCounter = 0;//counts the number of GPS data collected (and averaged)
//array to hold the GPS samples
double latitudeArray[7];//stores latitude samples for sort and median, size is fixed to 7 due to the fixed (hardcoded) size of the getMedian function
double longitudeArray[7];//stores longitude samples for sort and median, size is fixed to 7 due to the fixed (hardcoded) size of the getMedian function
//array to hold the heading samples
double headingArray[7];//stores heading samples for sort and median, size is fixed to 7 due to the fixed (hardcoded) size of the getMedian function
double tempHeadingData;//holds the temp heading data returned by rxCompassData(). It will get verified for validity before it's assigned to the headingArray.

RoverReset * resetArray[] = {
	roverNavigation,
	roverGps
};


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}

	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	_MAIN_SERIAL_.begin(MAIN_BAUD_RATE);
	_GPS_SERIAL_.begin(GPS_BAUD_RATE);

	delay(1000);
	
	
	
	//Preset desired point
	roverNavigation->setLatitudeDeg(DESIRED_LATITUDE_COORDINATE, TYPE_DESIRED);
	roverNavigation->setLongitudeDeg(DESIRED_LONGITUDE_COORDINATE, TYPE_DESIRED);
	
	
}


void loop() {

	
	
	


#ifdef _DEBUG_USE_FIXED_TEST_DATA
	roverNavigation->setHeadingDeg(4.28);
	roverNavigation->setLatitudeDeg(39.268761, TYPE_ACTUAL);
	roverNavigation->setLongitudeDeg(-76.606402, TYPE_ACTUAL);
	allGPSDataGathered = true;
#else

	//=====Get Heading (from AUXI)========
	//Get samples of actual heading from the IMU's Compass for sort and median
	 if(rxCompassData(tempHeadingData))//receive data from the IMU (from AUXI) and check to see if the heading data received is valid
	 {
		#ifdef _PRINT_IMU_DATA_VALID_STATUS
			_SERIAL_DEBUG_CHANNEL_.println(F("IMU Data Valid"));
		#endif
		
		headingArray[headingDataCounter] = tempHeadingData;//assign the temp value to the array
		headingDataCounter++;//increment the global counter
		if( headingDataCounter >= 7)//once 7 samples have been collected for the median
		{
			headingDataCounter = 0;//reset the global counter
			double avgHeading = BubbleSort::getMedian(headingArray[0], headingArray[1], headingArray[2], headingArray[3], headingArray[4], headingArray[5], headingArray[6]);
			if(avgHeading >= 0.0 && avgHeading <= 360.0)//check (again) to see that the heading value is within valid range and makes sense. If there was an error a 9999.9 would have been set. Though the rxCompassData() would return a false, just in case that's not checked, then the 9999.9 would indicate bad data as well.
			{
				roverNavigation->setHeadingDeg(avgHeading);//set it to the actual/official heading value
				
				#ifdef _PRINT_IMU_MEDIAN_COMPLETED_STATUS
					_SERIAL_DEBUG_CHANNEL_.println(F("IMU Median Completed"));
				#endif
			}//end if
			//else do nothing and keep the last set value as is
		}//end if
	 }//end if
	 else//Else notify that the IMU data isn't ready
	 {
		_SERIAL_DEBUG_CHANNEL_.println(F("IMU Data Not Ready"));
	 }//end else
		

	//=====Get Actual (GPS) Coordinates========
	//Get samples of actual GPS coordinates
	
	if(rxGPSData(roverGps))//Receive (via serial) and process gps data
	{
		#ifdef _PRINT_GPS_DATA_VALID_STATUS
			_SERIAL_DEBUG_CHANNEL_.println(F("GPS Data Valid"));
		#endif
		
		//save the lat and long data into the array, which will later be sorted and the median will be extracted
		latitudeArray[gpsDataCounter] = roverGps->getGpsLatitude(DEC_DEG);
		longitudeArray[gpsDataCounter] = roverGps->getGpsLongitude(DEC_DEG);
		gpsDataCounter++;//increment the counter

		if (gpsDataCounter >= 7)//once 7 samples have been collected for the median
		{
			
			gpsDataCounter = 0;//reset the global counter			
			
			double avgLatitude = BubbleSort::getMedian(latitudeArray[0], latitudeArray[1], latitudeArray[2], latitudeArray[3], latitudeArray[4], latitudeArray[5], latitudeArray[6]);//take the median value
			
			double avgLongitude = BubbleSort::getMedian(longitudeArray[0], longitudeArray[1], longitudeArray[2], longitudeArray[3], longitudeArray[4], longitudeArray[5], longitudeArray[6]);//take the median
			
			//check to see if both lat and long are within valid range
			if(( avgLatitude >= 0.0 && avgLatitude <= 90.0) && (avgLongitude >= -180.0 && avgLongitude <= 180.0 ))
			{
				roverNavigation->setLatitudeDeg(avgLatitude , TYPE_ACTUAL);//set it to the actual/official latitude value
				roverNavigation->setLongitudeDeg(avgLongitude, TYPE_ACTUAL);//set it to the actual/official longitude value
				
				
				#ifdef _PRINT_GPS_MEDIAN_COMPLETED_STATUS
					_SERIAL_DEBUG_CHANNEL_.println(F("GPS Median Completed"));
				#endif
				
				
				

				#ifdef _HIDE_DATA_WHEN_GPS_NOT_READY //print data only when the GPS data is ready (i.e. when _HIDE_DATA_WHEN_GPS_NOT_READY is active and defined)
				
					_SERIAL_DEBUG_CHANNEL_.println(F("========"));
					_SERIAL_DEBUG_CHANNEL_.print(F("Desired Lat: "));
					_SERIAL_DEBUG_CHANNEL_.println(roverNavigation->getLatitude(TYPE_DESIRED, UNIT_DEGREES), DECIMAL_PRECISION);//print with the define decimal precision
					_SERIAL_DEBUG_CHANNEL_.print(F("Desired Lon: "));
					_SERIAL_DEBUG_CHANNEL_.println(roverNavigation->getLongitude(TYPE_DESIRED, UNIT_DEGREES), DECIMAL_PRECISION);//print with the define decimal precision
					_SERIAL_DEBUG_CHANNEL_.print(F("Actual Lat: "));
					_SERIAL_DEBUG_CHANNEL_.println(roverNavigation->getLatitude(TYPE_ACTUAL, UNIT_DEGREES), DECIMAL_PRECISION);//print with the define decimal precision
					_SERIAL_DEBUG_CHANNEL_.print(F("Actual Lon: "));
					_SERIAL_DEBUG_CHANNEL_.println(roverNavigation->getLongitude(TYPE_ACTUAL, UNIT_DEGREES), DECIMAL_PRECISION);//print with the define decimal precision
					_SERIAL_DEBUG_CHANNEL_.print(F("Rover Heading: "));
					_SERIAL_DEBUG_CHANNEL_.println(roverNavigation->getHeading(UNIT_DEGREES), DECIMAL_PRECISION);//print with the define decimal precision


					_SERIAL_DEBUG_CHANNEL_.print(F("Distance: "));
					tempValue = roverNavigation->getDistance(UNIT_M);
					_SERIAL_DEBUG_CHANNEL_.println(tempValue, DECIMAL_PRECISION);//print with the define decimal precision
					_SERIAL_DEBUG_CHANNEL_.print(F("True Bearing: "));
					tempValue = roverNavigation->getTrueBearing();
					_SERIAL_DEBUG_CHANNEL_.println(tempValue, DECIMAL_PRECISION);//print with the define decimal precision	

					_SERIAL_DEBUG_CHANNEL_.print(F("Relative Bearing: "));
					tempValue = roverNavigation->getRelativeBearing();
					_SERIAL_DEBUG_CHANNEL_.println(tempValue, DECIMAL_PRECISION);//print with the define decimal precision	

					_SERIAL_DEBUG_CHANNEL_.print(F("Get Motor Steering: "));
					tempValue = roverNavigation->getCalculatedMotorSteering();
					translateMotorSteering(roverNavigation->getCalculatedMotorSteering());

					_SERIAL_DEBUG_CHANNEL_.print(F("Get Motor Throttle: "));
					translateMotorThrottle(roverNavigation->getCalculatedMotorThrottle());


					_SERIAL_DEBUG_CHANNEL_.print(F("Rover Nav Status: "));
					if (roverNavigation->hasReachedDestination())
					{
					_SERIAL_DEBUG_CHANNEL_.println(F("Destination Reached"));
					}
					else
					{
					_SERIAL_DEBUG_CHANNEL_.println(F("Still Navigating"));
					}
				#endif
				
				
			}//end if
			//else throw the whole lat/long pair away and keep the previous value
		
			
			
		}//end if	
	 }//end if
	else//Else notify that the GPS data isn't ready
	{
		_SERIAL_DEBUG_CHANNEL_.println(F("GPS Data Not Ready"));
		
		
		#ifndef _HIDE_DATA_WHEN_GPS_NOT_READY //print data even when the GPS data is not ready (i.e. when _HIDE_DATA_WHEN_GPS_NOT_READY is commented out and not defined)

		_SERIAL_DEBUG_CHANNEL_.println(F("========"));
		_SERIAL_DEBUG_CHANNEL_.print(F("Desired Lat: "));
		_SERIAL_DEBUG_CHANNEL_.println(roverNavigation->getLatitude(TYPE_DESIRED, UNIT_DEGREES), DECIMAL_PRECISION);//print with the define decimal precision
		_SERIAL_DEBUG_CHANNEL_.print(F("Desired Lon: "));
		_SERIAL_DEBUG_CHANNEL_.println(roverNavigation->getLongitude(TYPE_DESIRED, UNIT_DEGREES), DECIMAL_PRECISION);//print with the define decimal precision
		_SERIAL_DEBUG_CHANNEL_.print(F("Actual Lat: "));
		_SERIAL_DEBUG_CHANNEL_.println(roverNavigation->getLatitude(TYPE_ACTUAL, UNIT_DEGREES), DECIMAL_PRECISION);//print with the define decimal precision
		_SERIAL_DEBUG_CHANNEL_.print(F("Actual Lon: "));
		_SERIAL_DEBUG_CHANNEL_.println(roverNavigation->getLongitude(TYPE_ACTUAL, UNIT_DEGREES), DECIMAL_PRECISION);//print with the define decimal precision
		_SERIAL_DEBUG_CHANNEL_.print(F("Rover Heading: "));
		_SERIAL_DEBUG_CHANNEL_.println(roverNavigation->getHeading(UNIT_DEGREES), DECIMAL_PRECISION);//print with the define decimal precision


		_SERIAL_DEBUG_CHANNEL_.print(F("Distance: "));
		tempValue = roverNavigation->getDistance(UNIT_M);
		_SERIAL_DEBUG_CHANNEL_.println(tempValue, DECIMAL_PRECISION);//print with the define decimal precision
		_SERIAL_DEBUG_CHANNEL_.print(F("True Bearing: "));
		tempValue = roverNavigation->getTrueBearing();
		_SERIAL_DEBUG_CHANNEL_.println(tempValue, DECIMAL_PRECISION);//print with the define decimal precision	

		_SERIAL_DEBUG_CHANNEL_.print(F("Relative Bearing: "));
		tempValue = roverNavigation->getRelativeBearing();
		_SERIAL_DEBUG_CHANNEL_.println(tempValue, DECIMAL_PRECISION);//print with the define decimal precision	

		_SERIAL_DEBUG_CHANNEL_.print(F("Get Motor Steering: "));
		tempValue = roverNavigation->getCalculatedMotorSteering();
		translateMotorSteering(roverNavigation->getCalculatedMotorSteering());

		_SERIAL_DEBUG_CHANNEL_.print(F("Get Motor Throttle: "));
		translateMotorThrottle(roverNavigation->getCalculatedMotorThrottle());


		_SERIAL_DEBUG_CHANNEL_.print(F("Rover Nav Status: "));
		if (roverNavigation->hasReachedDestination())
		{
		_SERIAL_DEBUG_CHANNEL_.println(F("Destination Reached"));
		}
		else
		{
		_SERIAL_DEBUG_CHANNEL_.println(F("Still Navigating"));
		}
		#endif
					
									
									
	}
	 
	
#endif




	
	_SERIAL_DEBUG_CHANNEL_.println();//print a newline
	
	delay(500);
	

}//end loop



void translateMotorSteering(byte motorSteeringValue)
{
	switch (motorSteeringValue)
	{
	case 150:
		_SERIAL_DEBUG_CHANNEL_.println(F("Sharp Right"));
		break;
	case 120:
		_SERIAL_DEBUG_CHANNEL_.println(F("Wide Right"));
		break;
	case 90:
		_SERIAL_DEBUG_CHANNEL_.println(F("Center"));
		break;
	case 60:
		_SERIAL_DEBUG_CHANNEL_.println(F("Wide Left"));
		break;
	case 30:
		_SERIAL_DEBUG_CHANNEL_.println(F("Sharp Left"));
		break;
	default:
		_SERIAL_DEBUG_CHANNEL_.println(F("Unknown Error"));
		break;
	}//end switch
}
void translateMotorThrottle(byte motorThrottleValue)
{
	switch (motorThrottleValue)
	{
	case 90:
		_SERIAL_DEBUG_CHANNEL_.println(F("Stopped"));
		break;
	case 60:
		_SERIAL_DEBUG_CHANNEL_.println(F("Slow Speed"));
		break;
	case 30:
		_SERIAL_DEBUG_CHANNEL_.println(F("Normal Speed"));
		break;
	default:
		_SERIAL_DEBUG_CHANNEL_.println(F("Unknown Error"));
		break;
	}//end switch

}


boolean rxCompassData(double &headingValue) {

	byte rxdCharacterIndex = 0;//initialize the cursor to the beginning of the array
	byte charsToRxdBeforeTimeout;//counts the number of characters received while waiting for the start of the compass data (i.e. $) before timing out
	char rxData[COMPASS_DATA_CHAR_BUFFER_SIZE];
	char tempChar;
	boolean foundStart = false;


	//Check availability of serial data
	if (_MAIN_SERIAL_.available())
	{
		do
		{
			if ((char)_MAIN_SERIAL_.read() == '$')//look for the start of the compass data (do NOT include it in the data string if found)
			{
				foundStart = true;
				delay(1);
				break;//break out of the loop since the header was found
			}
			delay(1);
		} while (charsToRxdBeforeTimeout <= COMPASS_SENTENCE_LENGTH);
		if(foundStart)
		{
			while (_MAIN_SERIAL_.available())
			{
				tempChar = (char)_MAIN_SERIAL_.read();

				if (tempChar == '\r' || tempChar == '\n')//if either newline or return carriage is detected, end the while loop
				{
					break;//end of the data sent
				}
				else if (rxdCharacterIndex <= COMPASS_DATA_CHAR_BUFFER_SIZE)//make sure there is no buffer overflow
				{
					rxData[rxdCharacterIndex] = tempChar;//save the character received into the char array (string)
					rxdCharacterIndex++;//move the cursor to the next position in the array		
				}//end if
				else
				{
					_PC_USB_SERIAL_.println(F("CmpBuffOvrFlw"));
					headingValue = 9999.9;//default error value
					return false;//return false since buffer overflow
				}//end else
			}//end while
		}
		else//if no start character was found and time out has occurred, do nothing
		{
			headingValue = 9999.9;//default error value
			return false;//return false since did not receive the start of data
		}//end else
	}//end if
	else//if no data received over serial
	{
		headingValue = 9999.9;//default error value
		return false;//return true since using default data
	}//end else

	CharArray::Trim(rxData);//trim any white spaces in the character array
		
	headingValue = atof(rxData);
	//IMPROVEMENT TIP: This assumes all numbers were received. It may error if any characters are received. Currently there are no checks or error corrections. Can implement one later.
	
	if(headingValue >= 0.0 && headingValue <= 360.0)//checks to see if the heading value is within range
	{	
		return true;//return true once all data is received properly				
	}//end if
	else
	{
		headingValue = 9999.9;//default error value
		return false;//return true since using default data
	}//end else

}


boolean rxGPSData(RoverGpsSensor * roverGps) {

	//Note: Make sure processRxGPSData() is called between (before, after, or in) successive rxGPSData() function calls, as it will clear the string and reset the index (required for the code to work properly)


	byte numberOfAttempts = 0;//counts the number of times attempting to wait for a valid gps data string
	byte gpsCharactersToReceiveBeforeTimeout;//counts the number of characters received while waiting for the start of the gps data (i.e. $) before timing out
	boolean foundStart = false;
	boolean validGpsData = false;
	byte counter;


	while (numberOfAttempts <= GPS_RX_DATA_ATTEMPTS)
	{

		//Check availability of serial data
		if (_GPS_SERIAL_.available())
		{
			//initialize the counter
			gpsCharactersToReceiveBeforeTimeout = 0;
			//Wait for the GPS start of data (i.e. $) else for a time out
			do
			{
				if ((char)_GPS_SERIAL_.read() == '$')//look for the start of the GPS data (do NOT include it in the gps data string if found)
				{
					foundStart = true;
					delay(1);
					break;//break out of the loop since the header was found
				}
				delay(1);
			} while (gpsCharactersToReceiveBeforeTimeout <= GPS_SENTENCE_LENGTH);




			//If time-out has NOT occurred, keep processing the GPS data
			if (foundStart)
			{
				//initialize the counter
				counter = 0;

				//Gather the rest of the GPS String (AFTER the $, so $ is not included)
				while (_GPS_SERIAL_.available() && _GPS_SERIAL_.peek() != '$' && counter <= GPS_SENTENCE_LENGTH)//while there is still data on the Serial RX Buffer, another sentence has not started, and the length is not over the max GPS sentence length
				{


					//Read one character of serial data at a time
					//Note: Must type cast the _PC_USB_SERIAL_.Read to a char since not saving it to a char type first					

					roverGps->appendToRxGPSData((char)_GPS_SERIAL_.read());//construct the string one char at a time
																	  //DEBUG: Add as needed
					counter++;
					delay(1);//add a small delay between each transmission to reduce noisy and garbage characters


				}//end while



				 //Process and validate GPS Data
				validGpsData = roverGps->processRxGPSData();


				//If the received gps data is valid, return validGpsData and exit out of this function (no more trial attempts needed)
				if (validGpsData)
				{
					return validGpsData;
				}
				//else the GPS data was invalid, so make another attempt to find valid GPS data


			}//end if
			 //else if time out has occurred, go to the next trial		

		}//end if
		 //else if there is no serial data available do nothing, go to the next trial

		 //Increment trial counter
		numberOfAttempts++;

	}//end while

	 //Reached the max attempts to receive valid GPS Data
	return validGpsData;//If the code has reached this point, this value will be false. No valid GPS data found, and max attempts to find it has been reached.

}//end rxGPSData
