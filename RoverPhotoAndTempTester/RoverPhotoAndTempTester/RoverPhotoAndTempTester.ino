
#include <RoverAdc.h>

#include <RoverConfig.h>

//Global Variables

RoverAdc * roverAdc = new RoverAdc();

RoverReset * resetArray[] = {
	roverAdc
};



//Pinouts
#define PHOTOCELL_1_PIN		0
#define PHOTOCELL_2_PIN		1
#define THERMISTOR_PIN		2


//Analog Names
#define PHOTOCELL_1		0
#define PHOTOCELL_2		1
#define THERMISTOR		2


//Fixed Resistors
#define PHOTOCELL_1_FIXED_RESISTOR		10000
#define PHOTOCELL_2_FIXED_RESISTOR		10000
#define THERMISTOR_FIXED_RESISTOR		10000

//Thermistor Constants
#define	TEMP_CONSTANT_T0	298.15
#define	TEMP_CONSTANT_B	4050
#define	TEMP_CONSTANT_R0	10000


//Unit
#define CELSIUS		0
#define KELVIN		1



//Uncomment to configure debug outputs
//#define _DEBUG_CALC_RES_
//#define _HIDE_LIGHT_1
//#define _HIDE_LIGHT_2
//#define _HIDE_TEMP

void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}

	Serial.begin(PC_USB_BAUD_RATE);

}


void loop() {

	byte setUnit = CELSIUS;

#ifndef _HIDE_LIGHT_1
	Serial.print(F("Photo 1 (Lux): "));
	Serial.println(getLightValueOf(PHOTOCELL_1, PHOTOCELL_2_FIXED_RESISTOR));
#endif
#ifndef _HIDE_LIGHT_2
	Serial.print(F("Photo 2 (Lux): "));
	Serial.println(getLightValueOf(PHOTOCELL_2, PHOTOCELL_2_FIXED_RESISTOR));
#endif
#ifndef _HIDE_TEMP
	Serial.print(F("Temp: "));
	Serial.print(getTempValueOf(THERMISTOR, THERMISTOR_FIXED_RESISTOR, setUnit));
	if (setUnit == CELSIUS)
	{
		Serial.println(F(" oC"));
	}
	else
	{
		Serial.println(F(" oK"));
	}
#endif

	


	delay(500);
}






double getLightValueOf(byte analogSignalName, double fixedResistorValue)
{

	double measuredVcc = roverAdc->readVcc() / 1000.0;//this function is inherited, convert millivolts into volts

	double outputVoltage;
	double resistanceInOhms;


	if (analogSignalName == PHOTOCELL_1)
	{
		outputVoltage = roverAdc->voltageRead(PHOTOCELL_1_PIN);
	}
	else if (analogSignalName == PHOTOCELL_2)
	{
		outputVoltage = roverAdc->voltageRead(PHOTOCELL_2_PIN);
	}
	else
	{
		outputVoltage = 0.0;//error value
	}
	
	//Convert voltage output of resistor divider to measured resistance
	resistanceInOhms = calculateResistance(measuredVcc, outputVoltage, fixedResistorValue);//resistance in Ohms
	//Convert resistance to lux
	/*
	Lux = (500 / RLDR)
	the formula uses the RLDR expressed in k Ohm
	http://forum.arduino.cc/index.php?topic=141815.0
	https://learn.adafruit.com/photocells/using-a-photocell
	Note: You can also use the "Axel Benz" formula by first measuring the minimum and maximum resistance value with the multimeter and then finding the resistor value with: Pull-Down-Resistor = squareroot(Rmin * Rmax), this will give you slightly better range calculations
	https://arduinodiy.wordpress.com/2014/07/07/chosing-a-pull-down-resistor-for-an-ldr-axel-benz-formula/
	*/

	return 500.0 / (resistanceInOhms / 1000.0);//convert resistance from Ohms to KOhms, then convert that to Lux and return Lux

}
double getTempValueOf(byte analogSignalName, double fixedResistorValue, byte unit)
{

	/*
	Steinhart–Hart equation
	https://arduinodiy.wordpress.com/2015/11/10/measuring-temperature-with-ntc-the-steinhart-hart-formula/
	https://en.wikipedia.org/wiki/Steinhart%E2%80%93Hart_equation
	http://www.eidusa.com/Electronics_Kits_TEMP_THERMISTOR_1.htm
	https://playground.arduino.cc/ComponentLib/Thermistor2
	*/

	double measuredVcc = roverAdc->readVcc() / 1000.0;//this function is inherited, convert millivolts into volts

	double outputVoltage;
	double resistanceInOhms;

	if ( analogSignalName == THERMISTOR )
	{
		outputVoltage = roverAdc->voltageRead(THERMISTOR_PIN);
	}
	else
	{
		outputVoltage = 0.0;//error value
	}
		
	//Convert voltage output of resistor divider to measured resistance
	resistanceInOhms = calculateResistance(measuredVcc, outputVoltage, fixedResistorValue);

	//Convert resistance to temperature (in Kelvins)
	if( unit == CELSIUS )
	{
		return 1.0 / (1.0 / TEMP_CONSTANT_T0 + 1.0 / TEMP_CONSTANT_B * log(resistanceInOhms / TEMP_CONSTANT_R0)) -273;	//In Celsius
	}
	else//unit == KELVIN or default
	{
		return 1.0 / (1.0 / TEMP_CONSTANT_T0 + 1.0 / TEMP_CONSTANT_B * log(resistanceInOhms / TEMP_CONSTANT_R0));	//In Kelvins
	}

	
}


double calculateResistance(double measuredVcc, double outputVoltage, double fixedResistorValue)
{
	//Convert voltage to resistance
	//Original Equation: Vo = Vin * Rl / ( Rf + Rl )
	//Derived Equation: Rl = Vo * Rf / ( Vin + Vo )
	//Note: Vcc is Vin in this case.
	//returns resistance in ohms
	double resistance;
	resistance = outputVoltage * fixedResistorValue / (measuredVcc + outputVoltage);

#ifdef _DEBUG_CALC_RES_
	Serial.print(F("Vo: "));//DEBUG
	Serial.println(outputVoltage);//DEBUG		
	Serial.print(F("Fixed Res: "));//DEBUG
	Serial.println(fixedResistorValue);//DEBUG	
	Serial.print(F("Measured Vcc: "));//DEBUG
	Serial.println(measuredVcc);//DEBUG	
	Serial.print(F("Calculated Resistance: "));//DEBUG
	Serial.println(resistance);//DEBUG	
#endif

	return resistance;
}
