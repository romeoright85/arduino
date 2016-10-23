#include <RoverHwReset.h>


//Global Variables

RoverHwReset * naviHwResetter = new RoverHwReset(NAVI_HW_RESET_CTRL_PIN);
RoverHwReset * auxiHwResetter = new RoverHwReset(AUXI_HW_RESET_CTRL_PIN);
RoverHwReset * mainHwResetter = new RoverHwReset(MAIN_HW_RESET_CTRL_PIN);


RoverReset * resetArray[] = {
	naviHwResetter,
	auxiHwResetter,
	mainHwResetter
};


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	Serial.begin(9600);
}


void loop() {

	delay(1000);
	Serial.println(F("Running..."));
	delay(4000);
	Serial.println(F("Resetting NAVI..."));
	naviHwResetter->performHwReset();
	Serial.println(F("Resetting AUXI..."));
	auxiHwResetter->performHwReset();
	Serial.println(F("Resetting MAIN..."));
	mainHwResetter->performHwReset();
	delay(1000);
	Serial.println(F("Reset Complete!"));
}
