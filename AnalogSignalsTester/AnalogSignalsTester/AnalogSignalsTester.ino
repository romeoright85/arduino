#include <RoverAnalogSignals.h>

//uncomment the follow defines below in order to see the output (can choose as many or as little as you want
//#define _OUTPUT_MUX1
//#define _OUTPUT_MUX2
//#define _OUTPUT_MUX3
#define _OUTPUT_MUX4


//Global Variables

MqGasSensor * mqGasSensor = new MqGasSensor(GAS_SENSOR_TYPE_MQ2, GAS_BEACONCCA_RIGHTPOINTING, RESISTOR_GAS_BEACONCCA_RIGHTPOINTING);
RoverAnalogSignals * analogSignals = new RoverAnalogSignals();

int val = 0;
double val_Dbl = 0;


RoverReset * resetArray[] = {
	mqGasSensor,
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
	delay(100);//allow some time for the serial port to begin
	Serial.println(F("Calibrating Gas Sensor: ~26 secs"));	
	analogSignals->calibrateGasSensor(mqGasSensor);//this takes a few seconds, measured at about 26 seconds to begin	
	Serial.println(F("Done"));
	
}


void loop() {
	
	delay(1000);

	Serial.println(F("--START--"));
	Serial.println("");

	#ifdef _OUTPUT_MUX1
		//AMUX 1
		Serial.println(F("==AMUX1=="));

		//Ch 0
		val = analogSignals->getRawADCValueOf(VOLTAGE_7D2_RAW);
		Serial.print(F("VOLTAGE_7D2_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getVoltageValueOf(VOLTAGE_7D2_RAW);
		Serial.print(F("VOLTAGE_7D2_ACTUAL: "));
		Serial.println(val_Dbl);

		//Ch 1
		val = analogSignals->getRawADCValueOf(CURRENT_7D2_PRESW25A);
		Serial.print(F("CURRENT_7D2_PRESW25A_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getCurrentValueOf(CURRENT_7D2_PRESW25A, ACS711_25A);
		Serial.print(F("CURRENT_7D2_PRESW25A_ACTUAL: "));
		Serial.println(val_Dbl);

		//Ch 2
		val = analogSignals->getRawADCValueOf(CURRENT_7D2_SW12D5A);
		Serial.print(F("CURRENT_7D2_SW12D5A_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getCurrentValueOf(CURRENT_7D2_SW12D5A, ACS711_12D5A);
		Serial.print(F("CURRENT_7D2_SW12D5A_ACTUAL: "));
		Serial.println(val_Dbl);

		//Ch 3
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING_ACTUAL: "));
		Serial.println(val_Dbl);
	
		//Ch 4
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING);
		Serial.print(F("PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING, RESISTOR_PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING);
		Serial.print(F("PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING_ACTUAL: "));
		Serial.println(val_Dbl);
	
		//Ch 5
		val = analogSignals->getRawADCValueOf(TEMPSENSOR_BEACONCCA_CENTERSIDE);
		Serial.print(F("TEMPSENSOR_BEACONCCA_CENTERSIDE_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_BEACONCCA_CENTERSIDE, RESISTOR_TEMPSENSOR_BEACONCCA_CENTERSIDE);
		Serial.print(F("TEMPSENSOR_BEACONCCA_CENTERSIDE_ACTUAL: "));
		Serial.println(val_Dbl);
	
		//Ch 6
		val = analogSignals->getRawADCValueOf(TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET);
		Serial.print(F("TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET, RESISTOR_TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET);
		Serial.print(F("TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET_ACTUAL: "));
		Serial.println(val_Dbl);


		delay(1000);
		Serial.println("");

	#endif

	#ifdef _OUTPUT_MUX2
		//AMUX 2
		Serial.println(F("==AMUX2=="));

		//Ch 0
		val = analogSignals->getRawADCValueOf(VOLTAGE_5_ANALOGCCA);
		Serial.print(F("VOLTAGE_5_ANALOGCCA_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getVoltageValueOf(VOLTAGE_5_ANALOGCCA);
		Serial.print(F("VOLTAGE_5_ANALOGCCA_ACTUAL: "));
		Serial.println(val_Dbl);

		//Ch 1
		val = analogSignals->getRawADCValueOf(CURRENT_3D3_SW12D5A);
		Serial.print(F("CURRENT_3D3_SW12D5A_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getCurrentValueOf(CURRENT_3D3_SW12D5A, ACS711_12D5A);
		Serial.print(F("CURRENT_3D3_SW12D5A_ACTUAL: "));
		Serial.println(val_Dbl);

		//Ch 2
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING_ACTUAL: "));
		Serial.println(val_Dbl);

		//Ch 3
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING_ACTUAL: "));
		Serial.println(val_Dbl);


		//Ch 4
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING_ACTUAL: "));
		Serial.println(val_Dbl);

		//Ch 5
		val = analogSignals->getRawADCValueOf(TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR);
		Serial.print(F("TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR, RESISTOR_TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR);
		Serial.print(F("TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR_ACTUAL: "));
		Serial.println(val_Dbl);

		//Ch 6
		val = analogSignals->getRawADCValueOf(TEMPSENSOR_DIGITALCCA_MIDDLESIDE);
		Serial.print(F("TEMPSENSOR_DIGITALCCA_MIDDLESIDE_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_DIGITALCCA_MIDDLESIDE, RESISTOR_TEMPSENSOR_DIGITALCCA_MIDDLESIDE);
		Serial.print(F("TEMPSENSOR_DIGITALCCA_MIDDLESIDE_ACTUAL: "));
		Serial.println(val_Dbl);

		delay(1000);
		Serial.println("");

	#endif

	#ifdef _OUTPUT_MUX3
		//AMUX 3
		Serial.println(F("==AMUX3=="));

		//Ch 0
		val = analogSignals->getRawADCValueOf(VOLTAGE_3D3_SW);
		Serial.print(F("VOLTAGE_3D3_SW_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getVoltageValueOf(VOLTAGE_3D3_SW);
		Serial.print(F("VOLTAGE_3D3_SW_ACTUAL: "));
		Serial.println(val_Dbl);

		//Ch 1
		val = analogSignals->getRawADCValueOf(CURRENT_MOTORCTRLR_CH1_12D5A);
		Serial.print(F("CURRENT_MOTORCTRLR_CH1_12D5A_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getCurrentValueOf(CURRENT_MOTORCTRLR_CH1_12D5A, ACS711_12D5A);
		Serial.print(F("CURRENT_MOTORCTRLR_CH1_12D5A_ACTUAL: "));
		Serial.println(val_Dbl);

		//Ch 2
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING_ACTUAL: "));
		Serial.println(val_Dbl);

		//Ch 3
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK);
		Serial.print(F("PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK, RESISTOR_PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK);
		Serial.print(F("PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK_ACTUAL: "));
		Serial.println(val_Dbl);


		//Ch 4
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING);
		Serial.print(F("PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING, RESISTOR_PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING);
		Serial.print(F("PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING_ACTUAL: "));
		Serial.println(val_Dbl);

		//Ch 5
		val = analogSignals->getRawADCValueOf(TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK);
		Serial.print(F("TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK, RESISTOR_TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK);
		Serial.print(F("TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK_ACTUAL: "));
		Serial.println(val_Dbl);

	
		delay(1000);
		Serial.println("");
	#endif

	#ifdef _OUTPUT_MUX4
		//AMUX 4
		Serial.println(F("==AMUX4=="));

		//Ch 0
		val = analogSignals->getRawADCValueOf(GAS_BEACONCCA_RIGHTPOINTING);
		Serial.print(F("GAS_BEACONCCA_RIGHTPOINTING_RAW: "));
		Serial.println(val);
		val = analogSignals->getGasValueOf(mqGasSensor);
		Serial.print(F("GAS_BEACONCCA_RIGHTPOINTING_ACTUAL: "));
		Serial.println(val);

		//Ch 1
		val = analogSignals->getRawADCValueOf(CURRENT_MOTORCTRLR_CH2_12D5A);
		Serial.print(F("CURRENT_MOTORCTRLR_CH2_12D5A_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getCurrentValueOf(CURRENT_MOTORCTRLR_CH2_12D5A, ACS711_12D5A);
		Serial.print(F("CURRENT_MOTORCTRLR_CH2_12D5A_ACTUAL: "));
		Serial.println(val_Dbl);


		//Ch 2
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING_ACTUAL: "));
		Serial.println(val_Dbl);


		//Ch 3
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK);
		Serial.print(F("PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK, RESISTOR_PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK);
		Serial.print(F("PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK_ACTUAL: "));
		Serial.println(val_Dbl);
	
		//Ch 4
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING);
		Serial.print(F("PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING, RESISTOR_PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING);
		Serial.print(F("PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING_ACTUAL: "));
		Serial.println(val_Dbl);

		//Ch 5
		val = analogSignals->getRawADCValueOf(TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE);
		Serial.print(F("TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE, RESISTOR_TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE);
		Serial.print(F("TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE_ACTUAL: "));
		Serial.println(val_Dbl);
		

		delay(1000);
		Serial.println("");

	#endif
	
	Serial.println(F("--END--"));
	//print blank lines for spacing
	Serial.println("");
	Serial.println("");

	delay(4000);
}


