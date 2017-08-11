/*
Note:
If used with actual data and not fixed data, you need to program all three arduinos with its corresponding code
NavigationTester_MAIN
NavigationTester_AUXI
NavigationTester_NAVI
Else if you want to use the fixed test data, you only need to program:
RoverNavigationTester_NAVI
*/

//Used for NAVI - 1

#include <RoverNavigation.h>
#include <RoverGpsSensor.h>
#include <CharArray.h>


//How to get the longitude and latitude of a place
//https://support.google.com/maps/answer/18539?co=GENIE.Platform%3DDesktop&hl=en

/*
In this example the desired location is set to:
Desired Lat/Long in Degrees (Hersh's Pizza in South Baltimore)
39.268603, -76.611702
*/


#define DESIRED_LATITUDE_COORDINATE 39.268603
#define DESIRED_LONGITUDE_COORDINATE -76.611702
#define COMPASS_DATA_CHAR_BUFFER_SIZE 10
//Uncomment to use fixed test data, else if left uncommented, it will use actual the GPS Module's and IMU Compass's data
//#define _DEBUG_USE_FIXED_TEST_DATA




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

*/



//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast


#ifdef _DEBUG_COMM_BROADCAST
#define _SERIAL_DEBUG_CHANNEL_ Serial2
#else
#define _SERIAL_DEBUG_CHANNEL_ Serial
#endif


//Global Variables
RoverNavigation * roverNavigation = new RoverNavigation();
RoverGpsSensor * roverGps = new RoverGpsSensor();

//flags for data ready
boolean gpsDataReady;


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

	Serial.begin(PC_USB_BAUD_RATE);
	Serial2.begin(MAIN_BAUD_RATE);
	Serial3.begin(GPS_BAUD_RATE);

	delay(1000);
}


void loop() {

	//reset flags
	gpsDataReady = false;

	//Receive (via serial) and process gps data
	gpsDataReady = rxGPSData(roverGps);

	double value = 0.0;
	double rxdHeading = 0.0;//debug

	//Preset desired point
	roverNavigation->setLatitudeDeg(DESIRED_LATITUDE_COORDINATE, TYPE_DESIRED);
	roverNavigation->setLongitudeDeg(DESIRED_LONGITUDE_COORDINATE, TYPE_DESIRED);



#ifdef _DEBUG_USE_FIXED_TEST_DATA
	roverNavigation->setHeadingDeg(4.28);
	roverNavigation->setLatitudeDeg(39.268761, TYPE_ACTUAL);
	roverNavigation->setLongitudeDeg(-76.606402, TYPE_ACTUAL);
#else
	//get actual heading from the IMU's Compass
	rxdHeading = rxCompassData();
	roverNavigation->setHeadingDeg(rxdHeading);
	
	//get actual GPS coordinates

	if (gpsDataReady)
	{
		_SERIAL_DEBUG_CHANNEL_.println(F("GPS Data Ready"));
		roverNavigation->setLatitudeDeg(roverGps->getGpsLatitude(), TYPE_ACTUAL);
		roverNavigation->setLongitudeDeg(roverGps->getGpsLongitude(), TYPE_ACTUAL);
	}
	else
	{
		_SERIAL_DEBUG_CHANNEL_.println(F("GPS Data Not Ready"));
		roverNavigation->setLatitudeDeg(0.0000, TYPE_ACTUAL);
		roverNavigation->setLongitudeDeg(0.0000, TYPE_ACTUAL);
	}

#endif


	_SERIAL_DEBUG_CHANNEL_.println(F("========"));
	_SERIAL_DEBUG_CHANNEL_.print(F("Desired Lat: "));
	_SERIAL_DEBUG_CHANNEL_.println(roverNavigation->getLatitude(TYPE_DESIRED, UNIT_DEGREES), 4);//print with 4 decimals
	_SERIAL_DEBUG_CHANNEL_.print(F("Desired Lon: "));
	_SERIAL_DEBUG_CHANNEL_.println(roverNavigation->getLongitude(TYPE_DESIRED, UNIT_DEGREES), 4);//print with 4 decimals
	_SERIAL_DEBUG_CHANNEL_.print(F("Actual Lat: "));
	_SERIAL_DEBUG_CHANNEL_.println(roverNavigation->getLatitude(TYPE_ACTUAL, UNIT_DEGREES), 4);//print with 4 decimals
	_SERIAL_DEBUG_CHANNEL_.print(F("Actual Lon: "));
	_SERIAL_DEBUG_CHANNEL_.println(roverNavigation->getLongitude(TYPE_ACTUAL, UNIT_DEGREES), 4);//print with 4 decimals
	_SERIAL_DEBUG_CHANNEL_.print(F("Rover Heading: "));
	_SERIAL_DEBUG_CHANNEL_.println(roverNavigation->getHeading(UNIT_DEGREES), 4);//print with 4 decimals


	_SERIAL_DEBUG_CHANNEL_.print(F("Distance: "));
	value = roverNavigation->getDistance(UNIT_M);
	_SERIAL_DEBUG_CHANNEL_.println(value, 4);//print with 4 decimals
	_SERIAL_DEBUG_CHANNEL_.print(F("True Bearing: "));
	value = roverNavigation->getTrueBearing();
	_SERIAL_DEBUG_CHANNEL_.println(value, 4);//print with 4 decimals	

	_SERIAL_DEBUG_CHANNEL_.print(F("Relative Bearing: "));
	value = roverNavigation->getRelativeBearing();
	_SERIAL_DEBUG_CHANNEL_.println(value, 4);//print with 4 decimals	

	_SERIAL_DEBUG_CHANNEL_.print(F("Get Motor Steering: "));
	value = roverNavigation->getCalculatedMotorSteering();
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
	_SERIAL_DEBUG_CHANNEL_.println();

	delay(2000);
}



void translateMotorSteering(byte value)
{
	switch (value)
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
void translateMotorThrottle(byte value)
{
	switch (value)
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


double rxCompassData() {

	byte rxdCharacterIndex = 0;//initialize the cursor to the beginning of the array
	char rxData[COMPASS_DATA_CHAR_BUFFER_SIZE];
	char defaultData[] = "0.0000";

	//Check availabiltiy of serial data
	if (Serial2.available())
	{
		while (Serial2.available())
		{
			if (rxdCharacterIndex <= COMPASS_DATA_CHAR_BUFFER_SIZE)//make sure there is no buffer overflow
			{				
				rxData[rxdCharacterIndex] = (char)Serial2.read();
				rxdCharacterIndex++;//move the cursor to the next position in the array		
			}//end if
			else
			{
				Serial.println(F("BuffOvrFlw"));
			}//end else
		}//end while
	}//end if
	else
	{
		strncpy(rxData, defaultData, sizeof(defaultData)/sizeof(defaultData[0]));
	}

	CharArray::Trim(rxData);//truim any white spaces in the character array
		
	return atof(rxData);

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

		//Check availabiltiy of serial data
		if (Serial3.available())
		{
			//initialize the counter
			gpsCharactersToReceiveBeforeTimeout = 0;
			//Wait for the GPS start of data (i.e. $) else for a time out
			do
			{
				if ((char)Serial3.read() == '$')//look for the start of the GPS data (do NOT include it in the gps data string if found)
				{
					foundStart = true;
					delay(1);
					break;//break out of the loop since the header was found
				}
				delay(1);
			} while (gpsCharactersToReceiveBeforeTimeout <= GPS_SENTENCE_LENGTH);




			//If timeout has NOT occured, keep processing the GPS data
			if (foundStart)
			{
				//initialize the counter
				counter = 0;

				//Gather the rest of the GPS String (AFTER the $, so $ is not included)
				while (Serial3.available() && Serial3.peek() != '$' && counter <= GPS_SENTENCE_LENGTH)//while there is still data on the Serial RX Buffer, another sentence has not started, and the length is not over the max GPS sentence length
				{


					//Read one character of serial data at a time
					//Note: Must type cast the Serial.Read to a char since not saving it to a char type first					

					roverGps->appendToRxGPSData((char)Serial3.read());//construct the string one char at a time
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