//Used for AUXI - 2
//Used for NAVI - 1
//Used for COMM - 4
//Used for MAIN - 3


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

	roverNavigation->setDesiredLatitudeDeg(39.268603);
	roverNavigation->setDesiredLongitudeDeg(-76.611702);
	roverNavigation->setActualLatitudeDeg(39.268761);
	roverNavigation->setActualLongitudeDeg(-76.606402);
	
	


	Serial.println("========");
	Serial.println(roverNavigation->getDesiredLatitudeDeg(),4);//print with 4 decimals
	Serial.println(roverNavigation->getDesiredLongitudeDeg(),4);//print with 4 decimals
	Serial.println();
	Serial.println(roverNavigation->getActualLatitudeDeg(),4);//print with 4 decimals
	Serial.println(roverNavigation->getActualLongitudeDeg(),4);//print with 4 decimals
	Serial.println();
	value = roverNavigation->calculateDistance(UNIT_M);
	Serial.println(value,4);//print with 4 decimals
	Serial.println();		
	value = roverNavigation->getTrueBearing();
	Serial.println(value, 4);//print with 4 decimals
	Serial.println();
	delay(1000);
}
