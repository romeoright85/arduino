#include <RoverAnalogSignals.h>


//Global Variables


RoverAnalogSignals * analogSignals = new RoverAnalogSignals();


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
	
	delay(1000);

	Serial.println(F("--START--"));
	Serial.println("");

	//AMUX 1
	Serial.println(F("==AMUX1=="));

	//Ch 0
	val = analogSignals->getRawADCValueOf(VOLTAGE_7D2_RAW);
	Serial.print(F("VOLTAGE_7D2_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(VOLTAGE_7D2_RAW, VOLTAGE_VALUE, NO_RESISTOR);
	Serial.print(F("VOLTAGE_7D2_ACTUAL: "));
	Serial.println(val_Dbl);

	//Ch 1
	val = analogSignals->getRawADCValueOf(CURRENT_7D2_PRESW25A);
	Serial.print(F("CURRENT_7D2_PRESW25A_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(CURRENT_7D2_PRESW25A, CURRENT_VALUE, NO_RESISTOR);
	Serial.print(F("CURRENT_7D2_PRESW25A_ACTUAL: "));
	Serial.println(val_Dbl);

	//Ch 2
	val = analogSignals->getRawADCValueOf(CURRENT_7D2_SW12D5A);
	Serial.print(F("CURRENT_7D2_SW12D5A_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(CURRENT_7D2_SW12D5A, CURRENT_VALUE, NO_RESISTOR);
	Serial.print(F("CURRENT_7D2_SW12D5A_ACTUAL: "));
	Serial.println(val_Dbl);

	//Ch 3
	val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING);
	Serial.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING, PHOTO_VALUE, NO_RESISTOR);
	Serial.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING_ACTUAL: "));
	Serial.println(val_Dbl);
	
	//Ch 4
	val = analogSignals->getRawADCValueOf(PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING);
	Serial.print(F("PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING, PHOTO_VALUE, NO_RESISTOR);
	Serial.print(F("PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING_ACTUAL: "));
	Serial.println(val_Dbl);
	
	//Ch 5
	val = analogSignals->getRawADCValueOf(TEMPSENSOR_BEACONCCA_CENTERSIDE);
	Serial.print(F("TEMPSENSOR_BEACONCCA_CENTERSIDE_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(TEMPSENSOR_BEACONCCA_CENTERSIDE, TEMP_VALUE, NO_RESISTOR);
	Serial.print(F("TEMPSENSOR_BEACONCCA_CENTERSIDE_ACTUAL: "));
	Serial.println(val_Dbl);
	
	//Ch 6
	val = analogSignals->getRawADCValueOf(TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET);
	Serial.print(F("TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET, TEMP_VALUE, NO_RESISTOR);
	Serial.print(F("TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET_ACTUAL: "));
	Serial.println(val_Dbl);


	delay(1000);
	Serial.println("");

	//AMUX 2
	Serial.println(F("==AMUX2=="));

	//Ch 0
	val = analogSignals->getRawADCValueOf(VOLTAGE_5_ANALOGCCA);
	Serial.print(F("VOLTAGE_5_ANALOGCCA_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(VOLTAGE_5_ANALOGCCA, VOLTAGE_VALUE, NO_RESISTOR);
	Serial.print(F("VOLTAGE_5_ANALOGCCA_ACTUAL: "));
	Serial.println(val_Dbl);

	//Ch 1
	val = analogSignals->getRawADCValueOf(CURRENT_3D3_SW12D5A);
	Serial.print(F("CURRENT_3D3_SW12D5A_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(CURRENT_3D3_SW12D5A, CURRENT_VALUE, NO_RESISTOR);
	Serial.print(F("CURRENT_3D3_SW12D5A_ACTUAL: "));
	Serial.println(val_Dbl);

	//Ch 2
	val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING);
	Serial.print(F("PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING, PHOTO_VALUE, NO_RESISTOR);
	Serial.print(F("PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING_ACTUAL: "));
	Serial.println(val_Dbl);

	//Ch 3
	val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING);
	Serial.print(F("PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING, PHOTO_VALUE, NO_RESISTOR);
	Serial.print(F("PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING_ACTUAL: "));
	Serial.println(val_Dbl);


	//Ch 4
	val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING);
	Serial.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING, PHOTO_VALUE, NO_RESISTOR);
	Serial.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING_ACTUAL: "));
	Serial.println(val_Dbl);

	//Ch 5
	val = analogSignals->getRawADCValueOf(TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR);
	Serial.print(F("TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR, TEMP_VALUE, NO_RESISTOR);
	Serial.print(F("TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR_ACTUAL: "));
	Serial.println(val_Dbl);

	//Ch 6
	val = analogSignals->getRawADCValueOf(TEMPSENSOR_DIGITALCCA_MIDDLESIDE);
	Serial.print(F("TEMPSENSOR_DIGITALCCA_MIDDLESIDE_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(TEMPSENSOR_DIGITALCCA_MIDDLESIDE, TEMP_VALUE, NO_RESISTOR);
	Serial.print(F("TEMPSENSOR_DIGITALCCA_MIDDLESIDE_ACTUAL: "));
	Serial.println(val_Dbl);

	delay(1000);
	Serial.println("");

	//AMUX 3
	Serial.println(F("==AMUX3=="));

	//Ch 0
	val = analogSignals->getRawADCValueOf(VOLTAGE_3D3_SW);
	Serial.print(F("VOLTAGE_3D3_SW_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(VOLTAGE_3D3_SW, VOLTAGE_VALUE, NO_RESISTOR);
	Serial.print(F("VOLTAGE_3D3_SW_ACTUAL: "));
	Serial.println(val_Dbl);

	//Ch 1
	val = analogSignals->getRawADCValueOf(CURRENT_MOTORCTRLR_CH1_12D5A);
	Serial.print(F("CURRENT_MOTORCTRLR_CH1_12D5A_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(CURRENT_MOTORCTRLR_CH1_12D5A, CURRENT_VALUE, NO_RESISTOR);
	Serial.print(F("CURRENT_MOTORCTRLR_CH1_12D5A_ACTUAL: "));
	Serial.println(val_Dbl);

	//Ch 2
	val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING);
	Serial.print(F("PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING, PHOTO_VALUE, NO_RESISTOR);
	Serial.print(F("PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING_ACTUAL: "));
	Serial.println(val_Dbl);

	//Ch 3
	val = analogSignals->getRawADCValueOf(PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK);
	Serial.print(F("PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK, PHOTO_VALUE, NO_RESISTOR);
	Serial.print(F("PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK_ACTUAL: "));
	Serial.println(val_Dbl);


	//Ch 4
	val = analogSignals->getRawADCValueOf(PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING);
	Serial.print(F("PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING, PHOTO_VALUE, NO_RESISTOR);
	Serial.print(F("PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING_ACTUAL: "));
	Serial.println(val_Dbl);

	//Ch 5
	val = analogSignals->getRawADCValueOf(TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK);
	Serial.print(F("TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK, TEMP_VALUE, NO_RESISTOR);
	Serial.print(F("TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK_ACTUAL: "));
	Serial.println(val_Dbl);

	
	delay(1000);
	Serial.println("");

	//AMUX 4
	Serial.println(F("==AMUX4=="));

	//Ch 0
	val = analogSignals->getRawADCValueOf(GAS_BEACONCCA_RIGHTPOINTING);
	Serial.print(F("GAS_BEACONCCA_RIGHTPOINTING_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(GAS_BEACONCCA_RIGHTPOINTING, GAS_VALUE, NO_RESISTOR);
	Serial.print(F("GAS_BEACONCCA_RIGHTPOINTING_ACTUAL: "));
	Serial.println(val_Dbl);

	//Ch 1
	val = analogSignals->getRawADCValueOf(CURRENT_MOTORCTRLR_CH2_12D5A);
	Serial.print(F("CURRENT_MOTORCTRLR_CH2_12D5A_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(CURRENT_MOTORCTRLR_CH2_12D5A, CURRENT_VALUE, NO_RESISTOR);
	Serial.print(F("CURRENT_MOTORCTRLR_CH2_12D5A_ACTUAL: "));
	Serial.println(val_Dbl);


	//Ch 2
	val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING);
	Serial.print(F("PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING, PHOTO_VALUE, NO_RESISTOR);
	Serial.print(F("PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING_ACTUAL: "));
	Serial.println(val_Dbl);


	//Ch 3
	val = analogSignals->getRawADCValueOf(PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK);
	Serial.print(F("PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK, PHOTO_VALUE, NO_RESISTOR);
	Serial.print(F("PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK_ACTUAL: "));
	Serial.println(val_Dbl);
	
	//Ch 4
	val = analogSignals->getRawADCValueOf(PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING);
	Serial.print(F("PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING, PHOTO_VALUE, NO_RESISTOR);
	Serial.print(F("PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING_ACTUAL: "));
	Serial.println(val_Dbl);

	//Ch 5
	val = analogSignals->getRawADCValueOf(TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE);
	Serial.print(F("TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE_RAW: "));
	Serial.println(val);
	val_Dbl = analogSignals->getADCValueOf_As(TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE, TEMP_VALUE, NO_RESISTOR);
	Serial.print(F("TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE_ACTUAL: "));
	Serial.println(val_Dbl);
		
	Serial.println("");
	Serial.println(F("--END--"));
	Serial.println("");
	Serial.println("");

	delay(5000);
}


