#include <AnalogMuxSensor.h>
#include <RoverAnalogSignals.h>


//Global Variables

//turn on the analog names in RoverConfig.h
#define _ROVERANALOGNAMES
#include <RoverConfig.h>

AnalogMuxSensor * analogMux;

RoverAnalogSignals * analogSignals = new RoverAnalogSignals();

int val = 0;//the analog value of interest

RoverReset * resetArray[] = { analogSignals };


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}

	Serial.begin(9600);

}


void loop() {

	analogMux = analogSignals->getMuxWith(VOLTAGE_7D2_RAW);
	val = analogMux->getRawAnalogValue(VOLTAGE_7D2_RAW);
	Serial.print(F("Analog val: "));
	Serial.println(val);
	delay(1000);
}


