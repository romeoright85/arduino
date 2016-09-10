#include <RoverAnalogSignals.h>


//Global Variables

//turn on the analog names in RoverConfig.h
#define _ROVERANALOGNAMES
#include <RoverConfig.h>

RoverAnalogSignals * analogSignals = new RoverAnalogSignals();

int val = 0;//the analog value of interest

RoverReset * resetArray[] = { analogSignals };


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
	
	delay(1000);

	Serial.println(F("--START--"));
	Serial.println("");

	//AMUX 1
	Serial.println(F("==AMUX1=="));
	val = analogSignals->getRawAnalogValueOf(VOLTAGE_7D2_RAW);
	Serial.print(F("VOLTAGE_7D2_RAW: "));
	Serial.println(val);

	val = analogSignals->getRawAnalogValueOf(CURRENT_7D2_PRESW25A);
	Serial.print(F("CURRENT_7D2_PRESW25A: "));
	Serial.println(val);

	val = analogSignals->getRawAnalogValueOf(CURRENT_7D2_SW12D5A);
	Serial.print(F("CURRENT_7D2_SW12D5A: "));
	Serial.println(val);

	val = analogSignals->getRawAnalogValueOf(PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING);
	Serial.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING: "));
	Serial.println(val);
	
	val = analogSignals->getRawAnalogValueOf(PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING);
	Serial.print(F("PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING: "));
	Serial.println(val);
	
	val = analogSignals->getRawAnalogValueOf(TEMPSENSOR_BEACONCCA_CENTERSIDE);
	Serial.print(F("TEMPSENSOR_BEACONCCA_CENTERSIDE: "));
	Serial.println(val);
	
	val = analogSignals->getRawAnalogValueOf(TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET);
	Serial.print(F("TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET: "));
	Serial.println(val);

	delay(1000);
	Serial.println("");

	//AMUX 2
	Serial.println(F("==AMUX2=="));
	val = analogSignals->getRawAnalogValueOf(VOLTAGE_5_ANALOGCCA);
	Serial.print(F("VOLTAGE_5_ANALOGCCA: "));
	Serial.println(val);

	val = analogSignals->getRawAnalogValueOf(CURRENT_3D3_SW12D5A);
	Serial.print(F("CURRENT_3D3_SW12D5A: "));
	Serial.println(val);

	val = analogSignals->getRawAnalogValueOf(PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING);
	Serial.print(F("PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING: "));
	Serial.println(val);

	val = analogSignals->getRawAnalogValueOf(PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING);
	Serial.print(F("PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING: "));
	Serial.println(val);

	val = analogSignals->getRawAnalogValueOf(PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING);
	Serial.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING: "));
	Serial.println(val);

	val = analogSignals->getRawAnalogValueOf(TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR);
	Serial.print(F("TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR: "));
	Serial.println(val);

	val = analogSignals->getRawAnalogValueOf(TEMPSENSOR_DIGITALCCA_MIDDLESIDE);
	Serial.print(F("TEMPSENSOR_DIGITALCCA_MIDDLESIDE: "));
	Serial.println(val);

	delay(1000);
	Serial.println("");

	//AMUX 3
	Serial.println(F("==AMUX3=="));
	val = analogSignals->getRawAnalogValueOf(VOLTAGE_3D3_SW);
	Serial.print(F("VOLTAGE_3D3_SW: "));
	Serial.println(val);

	val = analogSignals->getRawAnalogValueOf(CURRENT_MOTORCTRLR_CH1_12D5A);
	Serial.print(F("CURRENT_MOTORCTRLR_CH1_12D5A: "));
	Serial.println(val);

	val = analogSignals->getRawAnalogValueOf(PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING);
	Serial.print(F("PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING: "));
	Serial.println(val);

	val = analogSignals->getRawAnalogValueOf(PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK);
	Serial.print(F("PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK: "));
	Serial.println(val);

	val = analogSignals->getRawAnalogValueOf(PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING);
	Serial.print(F("PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING: "));
	Serial.println(val);

	val = analogSignals->getRawAnalogValueOf(TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK);
	Serial.print(F("TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK: "));
	Serial.println(val);
	
	delay(1000);
	Serial.println("");

	//AMUX 4
	Serial.println(F("==AMUX4=="));
	val = analogSignals->getRawAnalogValueOf(GAS_BEACONCCA_RIGHTPOINTING);
	Serial.print(F("GAS_BEACONCCA_RIGHTPOINTING: "));
	Serial.println(val);

	val = analogSignals->getRawAnalogValueOf(CURRENT_MOTORCTRLR_CH2_12D5A);
	Serial.print(F("CURRENT_MOTORCTRLR_CH2_12D5A: "));
	Serial.println(val);

	val = analogSignals->getRawAnalogValueOf(PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING);
	Serial.print(F("PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING: "));
	Serial.println(val);

	val = analogSignals->getRawAnalogValueOf(PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK);
	Serial.print(F("PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK: "));
	Serial.println(val);
	
	val = analogSignals->getRawAnalogValueOf(PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING);
	Serial.print(F("PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING: "));
	Serial.println(val);

	val = analogSignals->getRawAnalogValueOf(TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE);
	Serial.print(F("TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE: "));
	Serial.println(val);
	
	Serial.println("");
	Serial.println(F("--END--"));
	Serial.println("");
	Serial.println("");

	delay(5000);
}


