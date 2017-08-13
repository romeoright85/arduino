//RoverAnalogSignals.h
#ifndef _ROVERANALOGSIGNALS_H
#define _ROVERANALOGSIGNALS_H

	#include <Arduino.h>
	#include <RoverDebug.h>	
	#include <RoverReset.h>
	#include <AnalogMuxSensor.h>
	#include <RoverVcc.h>
	#include <MqGasSensor.h>
	#include <DelayCounter.h>

	
	//References:
	
	//Lux Calculations
	//https://learn.adafruit.com/photocells/using-a-photocell
	//http://emant.com/316002.page
	
	//Currrent Calulcations
	//ACS711_12D5A
	//https://www.pololu.com/product/2197
	//ACS711_25A
	//https://www.pololu.com/product/2198
	
	//MQ Gas Calculations
	//http://sandboxelectronics.com/?p=165

	//Thermal Calculations
	//https://learn.adafruit.com/thermistor/using-a-thermistor
	

	//uncomment defines below for debugging
	//#define _DEBUG_GAS_SENSOR_CALIBRATION_STATUS_
	//#define _DEBUG_GAS_SENSOR_READ_STATUS_
	//#define _DEBUG_CALIBRATED_R0_	
	//#define _DEBUG_RS_R0_RATIO_
	//#define _DEBUG_RS_
	//#define _DEBUG_PRINT_CURVE_DATA_
	//#define _DEBUG_GAS_SENSOR_MATH_STEPS_
	//#define __DEBUG_CALC_RES_	
	//#define _DEBUG_MEASURED_VOLTAGE_
	#define _DEBUG_7D2V_SCALING_FACTOR_

	//turn on the analog names in RoverConfig.h
	#define _ROVERANALOGNAMES
	#define _ROVERCURRENTSENSORMODELS
	//Uncomment to debug
	//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast


	
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
		void calibrateGasSensor(MqGasSensor *, byte, DelayCounter *);//(MqGasSensor object, minutes of Rover Uptime, delay counter object) calibrates the MQ Gas Sensor after waiting for GAS_SENSOR_WARM_UP_TIME to pass. The DelayCounter object is used for delays in between sampling.
		unsigned int getRawADCValueOf(byte);//returns the raw analog value by Analog Signal Name (Analog Signal Name)
		double getVoltageValueOf(byte);//returns the voltage value (in Volts, with a range of 0-5V) by Analog Signal Name (Analog Signal Name)
		double getCurrentValueOf(byte, byte);//returns the current value in Amps by Analog Signal Name based on the current sensor model (Analog Signal Name, current sensor model)
		double getLightValueOf(byte, double);//returns the current value by Analog Signal Name. The fixed resistor used with the voltage divider is passed as well. (Analog Signal Name, fixed resistor value)
		double getTempValueOf(byte, double);//returns the temperature value (in Kelvins) by Analog Signal Name. The fixed resistor used with the voltage divider is passed as well. (Analog Signal Name, fixed resistor value)
		int getGasValueOf(MqGasSensor *);//(MqGasSensor object) Returns the ppm of the target gas of the MqGasSensor object (Note: the ppm can be greater than 255, so return int instead of byte).
			//Note: Make sure to check for analogSignals->gasSensorIsCalibrated() to be true before using values from the getGasValueOf()
		char * getMqGasSensorName(MqGasSensor *);//prints the MQ Gas Sensor's Name
		char * getMqGasSensorUnit(MqGasSensor *);//prints the MQ Gas Sensor's Unit			
		boolean gasSensorIsCalibrated();//Returns true when the gas sensor has warmed up and is calibrated.
		boolean gasSensorDoneReading();//Returns true when the gas sensor is done reading.
		void readGasSensor(MqGasSensor *, DelayCounter *);//(MqGasSensor object, delay counter object) Returns the sensing resistance. Samples are taken by reading the MQ Gas sensor based on values set by GAS_SENSOR_READ_SAMPLE_INTERVAL and GAS_SENSOR_READ_SAMPLE_TIMES.  The DelayCounter object is used for delays in between sampling.	
		void setAverageRead(float);//(the value to set the final read at) used to store the final value of MQ sensor reads. It's the average value of the _readSum samples.
		float getAverageRead();//used for MQ sensor reads. Returns the final average value of the _readSum samples.
		
	private:
		double calculateResistance(double, double, double);//converts the output voltage and measured Vcc to resistance (in ohms) based on the fixed resistor used in the voltage divider(Vcc, output voltage, fixed resistance)
		double calculateGasSensorResistance(MqGasSensor *);//(MqGasSensor object, delay counter object) gets the output resistance of the Gas Sensor. It uses calculateResistance() with values from the MqGasSensor object.	
		void calculateGasSensorRsRoRatio(MqGasSensor *);//(MqGasSensor object) Calculates the ratio of the sensor resistance vs. the calibrated resistance (control variable) and stores it in the MqGasSensor instance's member variable.
		void clearCalibrationStatus();//used to clear/reset calibration status/flags
		void clearReadStatus();//used to clear/reset read status/flags
		 
		
		//Non-SW Resettable	
		
		AnalogMuxSensor * findMuxBySignalName(byte);//returns the first mux in the _muxArray with the analog signal name (using a for loop). The intention is not to use the same name twice, else you'd only get the first mux that has it. (analog signal name)
		
		//holds pointers to AnalogMuxSensor
		AnalogMuxSensor * _muxArray[8];
		
		//holds pointers to the reset array
		//8 muxes
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
		
		
		
		
		
		//SW Resettable
		
		
		float _averageRead;//used for sensor read. It's the average value of the _readSum samples.
		
		//Gas sensor flags
		//For Calibration
		boolean _isGasSensorIsCalibrated;		
		boolean _firstRunOfCalibration;//used to make sure certain tasks are only ran on the first iteration of the function call (until it has been reset)
		//For Read
		boolean _gasSensorDoneReading;//used to flag that the MQ gas sensor is done reading/sampling			
		boolean _firstRunOfRead;//used to make sure certain tasks are only ran on the first iteration of the function call (until it has been reset, or the read function has completed)
		
	
	
	
		//AnalogMuxSensor objects
		AnalogMuxSensor * _amux1;
		AnalogMuxSensor * _amux2;
		AnalogMuxSensor * _amux3;
		AnalogMuxSensor * _amux4;
		AnalogMuxSensor * _amux5;
		AnalogMuxSensor * _amux6;
		AnalogMuxSensor * _amux7;
		AnalogMuxSensor * _amux8;	

		
				
				
				
	};

	#endif 