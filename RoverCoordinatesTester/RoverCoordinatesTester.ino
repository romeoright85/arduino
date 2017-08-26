#include <Coordinates.h>
#include <RoverConfig.h>

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

	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);

}


void loop() {




	//testing different ways to set the position
	_PC_USB_SERIAL_.println(F("TEST CASE 1"));
	_PC_USB_SERIAL_.println(F("Coordinate 1:"));
	_PC_USB_SERIAL_.print(coordinate1->getLatitudeDeg(), 4);
	_PC_USB_SERIAL_.print(F(", "));
	_PC_USB_SERIAL_.print(coordinate1->getLongitudeDeg(), 4);
	_PC_USB_SERIAL_.println();
	_PC_USB_SERIAL_.println(F("Coordinate 2:"));
	_PC_USB_SERIAL_.print(coordinate2->getLatitudeDeg(), 4);
	_PC_USB_SERIAL_.print(F(", "));
	_PC_USB_SERIAL_.print(coordinate2->getLongitudeDeg(), 4);
	_PC_USB_SERIAL_.println();
	coordinate1->setLatitudeDeg(7.7);
	coordinate1->setLongitudeDeg(8.8);
	_PC_USB_SERIAL_.println(F("Coordinate 1:"));
	_PC_USB_SERIAL_.print(coordinate1->getLatitudeDeg(), 4);
	_PC_USB_SERIAL_.print(F(", "));
	_PC_USB_SERIAL_.print(coordinate1->getLongitudeDeg(), 4);
	_PC_USB_SERIAL_.println();
	coordinate2->setPositionDeg(56.78, -56.78);
	_PC_USB_SERIAL_.println(F("Coordinate 2:"));
	_PC_USB_SERIAL_.print(coordinate2->getLatitudeDeg(), 4);
	_PC_USB_SERIAL_.print(F(", "));
	_PC_USB_SERIAL_.print(coordinate2->getLongitudeDeg(), 4);
	_PC_USB_SERIAL_.println();
	_PC_USB_SERIAL_.println();

	//testing max and min limits of the latitude/longitude
	_PC_USB_SERIAL_.println(F("TEST CASE 2"));
	coordinate1->setPositionDeg(45, 45);
	_PC_USB_SERIAL_.println(F("Coordinate 1:"));
	_PC_USB_SERIAL_.print(coordinate1->getLatitudeDeg(), 4);
	_PC_USB_SERIAL_.print(F(", "));
	_PC_USB_SERIAL_.print(coordinate1->getLongitudeDeg(), 4);
	_PC_USB_SERIAL_.println();
	coordinate1->setPositionDeg(90, 180);
	_PC_USB_SERIAL_.println(F("Coordinate 1:"));
	_PC_USB_SERIAL_.print(coordinate1->getLatitudeDeg(), 4);
	_PC_USB_SERIAL_.print(F(", "));
	_PC_USB_SERIAL_.print(coordinate1->getLongitudeDeg(), 4);
	_PC_USB_SERIAL_.println();
	coordinate1->setPositionDeg(91, 181);
	_PC_USB_SERIAL_.println(F("Coordinate 1:"));
	_PC_USB_SERIAL_.print(coordinate1->getLatitudeDeg(), 4);
	_PC_USB_SERIAL_.print(F(", "));
	_PC_USB_SERIAL_.print(coordinate1->getLongitudeDeg(), 4);
	_PC_USB_SERIAL_.println();
	coordinate1->setPositionDeg(-45, -45);
	_PC_USB_SERIAL_.println(F("Coordinate 1:"));
	_PC_USB_SERIAL_.print(coordinate1->getLatitudeDeg(), 4);
	_PC_USB_SERIAL_.print(F(", "));
	_PC_USB_SERIAL_.print(coordinate1->getLongitudeDeg(), 4);
	_PC_USB_SERIAL_.println();
	coordinate1->setPositionDeg(-90, -180);
	_PC_USB_SERIAL_.println(F("Coordinate 1:"));
	_PC_USB_SERIAL_.print(coordinate1->getLatitudeDeg(), 4);
	_PC_USB_SERIAL_.print(F(", "));
	_PC_USB_SERIAL_.print(coordinate1->getLongitudeDeg(), 4);
	_PC_USB_SERIAL_.println();
	coordinate1->setPositionDeg(-91, -181);
	_PC_USB_SERIAL_.println(F("Coordinate 1:"));
	_PC_USB_SERIAL_.print(coordinate1->getLatitudeDeg(), 4);
	_PC_USB_SERIAL_.print(F(", "));
	_PC_USB_SERIAL_.print(coordinate1->getLongitudeDeg(), 4);
	_PC_USB_SERIAL_.println();



	//test resetting the objects
	_PC_USB_SERIAL_.println(F("TEST CASE 3"));
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	_PC_USB_SERIAL_.println(F("Coordinate 1:"));
	_PC_USB_SERIAL_.print(coordinate1->getLatitudeDeg(), 4);
	_PC_USB_SERIAL_.print(F(", "));
	_PC_USB_SERIAL_.print(coordinate1->getLongitudeDeg(), 4);
	_PC_USB_SERIAL_.println();


	_PC_USB_SERIAL_.println();
	delay(1000);
}
