//Used for NAVI - 1



#include <RoverNavigation.h>

//How to get the longitude and latitude of a place
//https://support.google.com/maps/answer/18539?co=GENIE.Platform%3DDesktop&hl=en


//Global Variables

RoverNavigation * roverNavigation = new RoverNavigation();

RoverReset * resetArray[] = {
	roverNavigation
};


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}

	Serial.begin(PC_USB_BAUD_RATE);

}


void loop() {
	
	/*
		Example:
		Actual Lat/Long in Degrees
		39.268761, -76.606402 (lower right corner of Riverside Park in South Baltimore)
		Desired Lat/Long in Degrees (Hersh's Pizza in South Baltimore)
		39.268603, -76.611702

		RoverNavigation Calculated Result:
		456.7968 m
		Google Maps Calculated Result:
		about 462.27 m

	*/


	double value = 0.0;

	roverNavigation->setLatitudeDeg(39.268603, TYPE_DESIRED);
	roverNavigation->setLongitudeDeg(-76.611702, TYPE_DESIRED);
	roverNavigation->setLatitudeDeg(39.268761, TYPE_ACTUAL);
	roverNavigation->setLongitudeDeg(-76.606402, TYPE_ACTUAL);
	
	


	Serial.println(F("========"));
	Serial.println(F("Desired Lat/Lon"));
	Serial.println(roverNavigation->getLatitude(TYPE_DESIRED, UNIT_DEGREES),4);//print with 4 decimals
	Serial.println(roverNavigation->getLongitude(TYPE_DESIRED, UNIT_DEGREES),4);//print with 4 decimals
	Serial.println(F("Actual Lat/Lon"));
	Serial.println(roverNavigation->getLatitude(TYPE_ACTUAL, UNIT_DEGREES),4);//print with 4 decimals
	Serial.println(roverNavigation->getLongitude(TYPE_ACTUAL, UNIT_DEGREES),4);//print with 4 decimals
	Serial.println(F("Distance"));
	value = roverNavigation->getDistance(UNIT_M);
	Serial.println(value,4);//print with 4 decimals
	Serial.println(F("True Bearing"));
	value = roverNavigation->getTrueBearing();
	Serial.println(value, 4);//print with 4 decimals	
	
	float heading = 0.0;//test value
	Serial.println(F("Let Heading be:"));
	Serial.println(heading);
	Serial.println(F("Relative Bearing:"));
	value = roverNavigation->calculateRelativeBearing(heading, roverNavigation->getTrueBearing());
	Serial.println(value, 4);//print with 4 decimals	
	
	Serial.println();


	delay(1000);
}
