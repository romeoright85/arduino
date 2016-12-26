//RoverAnalogSignals.h
#ifndef _ROVERANALOGSIGNALS_H
#define _ROVERANALOGSIGNALS_H

	#include <Arduino.h>
	#include <RoverDebug.h>	
	#include <RoverReset.h>
	#include <AnalogMuxSensor.h>
	#include <RoverVcc.h>
	#include <MqGasSensor.h>

	
	//References:
	//Lux Calculations
	//http://emant.com/316002.page
	//Currrent Calulcations
	//ACS711_12D5A
	//https://www.pololu.com/product/2197
	//ACS711_25A
	//https://www.pololu.com/product/2198
	
	
	/*	
	Note: MqGasSensor and RoverAnalogSignals are tightly coupled because:
	RoverAnalogSignals's getGasValueOf() uses MqGasSensor's getGasPercentage()
	MqGasSensor's calibrate() uses RoverAnalogSignals's getRawADCValueOf()
	*/	
		
	
	
	
	//turn on the analog names in RoverConfig.h
	#define _ROVERANALOGNAMES
	#define _ROVERCURRENTSENSORMODELS
	

	
	/*******************************************************************
	Configure (define) flags before calling #include <RoverConfig.h>
	/********************************************************************/
	//define Arduino 2: AUXI in order to use it's config pins
	#ifndef _ARD_2_AUXI_H
		#define _ARD_2_AUXI_H
	#endif
	
	/********************************************************************/
	
	#include <RoverConfig.h>
	
	
	#define _TEMP_CONSTANTS
	#define _FIXED_RESISTORS
	#include <RoverCalibration.h>
	
	class RoverAnalogSignals : public virtual RoverReset, public RoverVcc {
	public:
		RoverAnalogSignals();//constructor
		~RoverAnalogSignals();//destructor
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		unsigned int getRawADCValueOf(byte);//returns the raw analog value by Analog Signal Name (Analog Signal Name)
		double getVoltageValueOf(byte);//returns the voltage value by Analog Signal Name (Analog Signal Name)
		double getCurrentValueOf(byte, byte);//returns the current value by Analog Signal Name based on the current sensor model (Analog Signal Name, current sensor model)
		double getLightValueOf(byte, double);//returns the current value by Analog Signal Name. The fixed resistor used with the voltage divider is passed as well. (Analog Signal Name, fixed resistor value)
		double getTempValueOf(byte, double);//returns the temperature value by Analog Signal Name. The fixed resistor used with the voltage divider is passed as well. (Analog Signal Name, fixed resistor value)
		double getGasValueOf(byte, double);//returns the gas value by Analog Signal Name. The fixed resistor used with the voltage divider is passed as well. (Analog Signal Name, fixed resistor value)
		
		
	private:
		double calculateResistance(long, double, double);//converts the output voltage and measured Vcc to resistance (in ohms) based on the fixed resistor used in the voltage divider(Vcc, output voltage, fixed resistance)
	
		//AnalogMuxSensor objects
		AnalogMuxSensor * _amux1;
		AnalogMuxSensor * _amux2;
		AnalogMuxSensor * _amux3;
		AnalogMuxSensor * _amux4;
		AnalogMuxSensor * _amux5;
		AnalogMuxSensor * _amux6;
		AnalogMuxSensor * _amux7;
		AnalogMuxSensor * _amux8;
		
		//holds pointers to AnalogMuxSensor
		AnalogMuxSensor * _muxArray[8];
		
		//holds pointers to the reset array
		RoverReset * _resetArray[8];
		
		
		//The array below are used to store the cross reference between which analog mux has which analog signal (name)
		byte _amux1AnalogNames[8];
		byte _amux2AnalogNames[8];
		byte _amux3AnalogNames[8];
		byte _amux4AnalogNames[8];
		byte _amux5AnalogNames[8];
		byte _amux6AnalogNames[8];
		byte _amux7AnalogNames[8];
		byte _amux8AnalogNames[8];
		
		AnalogMuxSensor * findMuxBySignalName(byte);//returns the first mux in the _muxArray with the analog signal name (using a for loop). The intention is not to use the same name twice, else you'd only get the first mux that has it. (analog signal name)
				
	};

	#endif 