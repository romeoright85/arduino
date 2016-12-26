//This code is just a modified subset of AnalogSignalsTester.ino that focuses on the MQ Gas Sensors

#include <RoverAnalogSignals.h>
#include <MqGasSensor.h>


//Global Variables


RoverAnalogSignals * analogSignals = new RoverAnalogSignals();
MqGasSensor * mqGasSensor = new MqGasSensor(GAS_SENSOR_TYPE_MQ2);

int val = 0;//the analog value of interest
double val_Dbl = 0;

RoverReset * resetArray[] = {
	analogSignals
};


void setup() {
	//put this before the reset since the reset might Serial Print in debug mode

	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}

	Serial.begin(9600);

}


void loop() {


	//Ch 0
	val = analogSignals->getRawADCValueOf(GAS_BEACONCCA_RIGHTPOINTING);
	Serial.print(F("GAS_BEACONCCA_RIGHTPOINTING_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getGasValueOf(GAS_BEACONCCA_RIGHTPOINTING, RESISTOR_GAS_BEACONCCA_RIGHTPOINTING);
	Serial.print(F("GAS_BEACONCCA_RIGHTPOINTING_ACTUAL: "));
	Serial.println(val_Dbl);

	delay(5000);
}


