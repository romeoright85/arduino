//Used for NAVI - 1



#include <Coordinates.h>

//Global Variables

/*
	Test Coordinate 1
	12.34, -12.34
	Test Coordinate 2
	56.78, -56.78
*/

Coordinates * coordinate1 = new Coordinates(12.34, -12.34);
Coordinates * coordinate2 = new Coordinates();

Coordinates * resetArray[] = {
	coordinate1,
	coordinate2
};


void setup() {
	
	//SKIP RESET TO TEST TO CONSTRUCTOR INITIALIZATION, test reset below in the loop() instead
	/*
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	*/

	Serial.begin(PC_USB_BAUD_RATE);

}


void loop() {

	

	
	//testing different ways to set the position
	Serial.println(F("TEST CASE 1"));
	Serial.println(F("Coordinate 1:"));
	Serial.print(coordinate1->getLatitude(), 4);
	Serial.print(F(", "));
	Serial.print(coordinate1->getLongitude(), 4);
	Serial.println();	
	Serial.println(F("Coordinate 2:"));
	Serial.print(coordinate2->getLatitude(), 4);
	Serial.print(F(", "));
	Serial.print(coordinate2->getLongitude(), 4);
	Serial.println();	
	coordinate1->setLatitude(7.7);
	coordinate1->setLongitude(8.8);
	Serial.println(F("Coordinate 1:"));
	Serial.print(coordinate1->getLatitude(), 4);
	Serial.print(F(", "));
	Serial.print(coordinate1->getLongitude(), 4);
	Serial.println();	
	coordinate2->setPosition(56.78, -56.78);
	Serial.println(F("Coordinate 2:"));
	Serial.print(coordinate2->getLatitude(), 4);
	Serial.print(F(", "));
	Serial.print(coordinate2->getLongitude(), 4);
	Serial.println();
	Serial.println();

	//testing max and min limits of the latitude/longitude
	Serial.println(F("TEST CASE 2"));
	coordinate1->setPosition(45, 45);
	Serial.println(F("Coordinate 1:"));
	Serial.print(coordinate1->getLatitude(), 4);
	Serial.print(F(", "));
	Serial.print(coordinate1->getLongitude(), 4);
	Serial.println();
	coordinate1->setPosition(90, 180);
	Serial.println(F("Coordinate 1:"));
	Serial.print(coordinate1->getLatitude(), 4);
	Serial.print(F(", "));
	Serial.print(coordinate1->getLongitude(), 4);
	Serial.println();
	coordinate1->setPosition(91, 181);
	Serial.println(F("Coordinate 1:"));
	Serial.print(coordinate1->getLatitude(), 4);
	Serial.print(F(", "));
	Serial.print(coordinate1->getLongitude(), 4);
	Serial.println();
	coordinate1->setPosition(-45, -45);
	Serial.println(F("Coordinate 1:"));
	Serial.print(coordinate1->getLatitude(), 4);
	Serial.print(F(", "));
	Serial.print(coordinate1->getLongitude(), 4);
	Serial.println();
	coordinate1->setPosition(-90, -180);
	Serial.println(F("Coordinate 1:"));
	Serial.print(coordinate1->getLatitude(), 4);
	Serial.print(F(", "));
	Serial.print(coordinate1->getLongitude(), 4);
	Serial.println();
	coordinate1->setPosition(-91, -181);
	Serial.println(F("Coordinate 1:"));
	Serial.print(coordinate1->getLatitude(), 4);
	Serial.print(F(", "));
	Serial.print(coordinate1->getLongitude(), 4);
	Serial.println();



	//test resetting the objects
	Serial.println(F("TEST CASE 3"));
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	Serial.println(F("Coordinate 1:"));
	Serial.print(coordinate1->getLatitude(), 4);
	Serial.print(F(", "));
	Serial.print(coordinate1->getLongitude(), 4);
	Serial.println();


	Serial.println();	
	delay(1000);
}
