//MqGasSensor.h
#ifndef _MQ_GAS_SENSOR_H
#define _MQ_GAS_SENSOR_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <CharArray.h>






/*
References:

			It needs about 3 minutes to warm up in order to get correct values.
			Need to calibrate the sensor in clean air.
			-Preheat the sensor for 24 hours, then run a one time calibration.

			https://www.youtube.com/watch?v=fBo3Yq9LK1U
			http://sandboxelectronics.com/?p=165
			http://mkme.org/forum/viewtopic.php?f=2&t=656
			http://playground.arduino.cc/Main/MQGasSensors
			https://www.google.com/amp/www.instructables.com/id/How-to-use-MQ2-Gas-Sensor-Arduino-Tutorial/
			https://www.youtube.com/watch?v=BIf_mpnsZvY
			http://circuitdigest.com/microcontroller-projects/arduino-smoke-detector-on-pcb-using-mq2-gas-sensor
			https://www.youtube.com/watch?v=QYSDSKn2Vf8
*/

/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/

//define Arduino 2: AUXI in order to use it's config pins
#ifndef _ARD_2_AUXI_H
	#define _ARD_2_AUXI_H
#endif


/********************************************************************/

#define _MQ_GAS_SENSOR_DEFINITIONS
#define _MQ_GAS_SENSOR_CALIBRATIONS

#include <RoverConfig.h>
#include <RoverCalibration.h>


//Fixed Strings (to store in flash)
//Null
const static char mq_gas_string_0[] PROGMEM = "Invalid";//copyStringFlash2CharBuffer(0)
const static char mq_gas_string_1[] PROGMEM = "Error";//copyStringFlash2CharBuffer(1)
//MQ2
const static char mq_gas_string_2[] PROGMEM = "Flammable Gas & Smoke";//copyStringFlash2CharBuffer(2)
const static char mq_gas_string_3[] PROGMEM = "ppm";//taken from the "Concentration" row of the datasheet, copyStringFlash2CharBuffer(3)
//MQ3
const static char mq_gas_string_4[] PROGMEM = "Alcohol";//copyStringFlash2CharBuffer(4)
const static char mq_gas_string_5[] PROGMEM = "mg/l";//taken from the "Concentration" row of the datasheet, copyStringFlash2CharBuffer(5)
//MQ4
const static char mq_gas_string_6[] PROGMEM = "Methane";//copyStringFlash2CharBuffer(6)
const static char mq_gas_string_7[] PROGMEM = "ppm";//taken from the "Concentration" row of the datasheet, copyStringFlash2CharBuffer(7)
//MQ6
const static char mq_gas_string_8[] PROGMEM = "LPG / Isobutane / Propane";//copyStringFlash2CharBuffer(8)
const static char mq_gas_string_9[] PROGMEM = "ppm";//taken from the "Concentration" row of the datasheet, copyStringFlash2CharBuffer(9)
//MQ7
const static char mq_gas_string_10[] PROGMEM = "Carbon Monoxide";//copyStringFlash2CharBuffer(10)
const static char mq_gas_string_11[] PROGMEM = "ppm";//taken from the "Concentration" row of the datasheet, copyStringFlash2CharBuffer(11)
//MQ9
const static char mq_gas_string_12[] PROGMEM = "Carbon Monoxide & Flammable Gas";//copyStringFlash2CharBuffer(12)
const static char mq_gas_string_13[] PROGMEM = "ppm";//taken from the "Concentration" row of the datasheet, copyStringFlash2CharBuffer(13)


//Note: Make sure to update  the mq_gas_string_table[] array

//Table of Fixed Strings (array of strings stored in flash)
const char* const mq_gas_string_table[] PROGMEM = {
	mq_gas_string_0,
	mq_gas_string_1,
	mq_gas_string_2,
	mq_gas_string_3,
	mq_gas_string_4,
	mq_gas_string_5,
	mq_gas_string_6,
	mq_gas_string_7,
	mq_gas_string_8,
	mq_gas_string_9,
	mq_gas_string_10,
	mq_gas_string_11,
	mq_gas_string_12,
	mq_gas_string_13
};	

class MqGasSensor : public virtual RoverReset {
public:
	MqGasSensor(byte, byte ,double);//constructor (gas sensor type, analog signal name, fixed resistor value)
	~MqGasSensor();//destructor
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	byte getAnalogSignalName();//returns the _analogSignalName of this instance of the gas sensor
	double getFixedResistorValue();//returns the _mqGasSensorFixedResistorValue of this instance of the gas sensor
	float getR0CleanAirFactor();//gets the gas sensor instance's _mqGasSensorR0CleanAirFactor (which is based on the gas sensor type. Set by the constructor of this MqGasSensor class)
	void setR0(float);//sets the gas sensor instance's _mqGasSensorR0
	float getR0();	//gets the gas sensor instance's _mqGasSensorR0
	void setRsRoRatio(double);//sets the gas sensor instance's _mqGasSensorRsR0Ratio
	double getRsR0Ratio();//gets the gas sensor instance's _mqGasSensorRsR0Ratio
	float getX();//gets the X point on the data curve (from _mqGasSensorDataCurve[])
	float getY();//gets the Y point on the data curve (from _mqGasSensorDataCurve[])
	float getSlope();//gets the slope of the curve (from _mqGasSensorDataCurve[])
	boolean gasSensorWarmedUp(byte);//(minutes of uptime) returns true when the gas sensor has warmed up for at least GAS_SENSOR_WARM_UP_TIME, else it returns false	
	void setCalibrationSum(float);//(the value to set the sum at) used for MQ sensor calibration. Keeps track of the accumulated/sum value use for averaging.
	void setCalibrationRuns(byte);//(the value to set the sample runs at) used for MQ sensor calibration. Keeps track of the number of samples that have been taken.
	float getCalibrationSum();//used for MQ sensor calibration. Returns the accumulated/sum value use for averaging.
	byte getCalibrationRuns();//used for MQ sensor calibration. Returns the number of samples that have been taken.
	void setReadSum(float);//(the value to set the sum at) used for MQ sensor reads. Keeps track of the accumulated/sum value use for averaging.
	float getReadSum();//used for MQ sensor reads. Returns the number of samples that have been taken.
	void setReadRuns(byte);//(the value to set the sample runs at) used for MQ sensor reads. Keeps track of the number of samples that have been taken.
	byte getReadRuns();//used for MQ sensor reads. Returns the accumulated/sum value use for averaging.
	char * getMqGasSensorName();//print _mqGasSensorName string
	char * getMqGasSensorUnit();//print _mqGasSensorUnit string
	byte getMqGasSensorNameLength();//get length of _mqGasSensorName string
	byte getMqGasSensorUnitLength();//get length of _mqGasSensorUnit string
	
	
private:
	//Non-SW Resettable		
	float _mqGasSensorDataCurve[3];//need to make this variable public so the array data can be read from	
	char _mqGasSensorName[MQ_SENSOR_NAME_BUFFER_SIZE];//holds the string of the mq sensor's name
	char _mqGasSensorUnit[MQ_SENSOR_UNIT_BUFFER_SIZE];//holds the string of the mq sensor's unit	
	byte _mqGasSensorType;//holds the sensor type.
	float _mqGasSensorR0CleanAirFactor;
	double _mqGasSensorFixedResistorValue;
	byte _analogSignalName;//holds the analog signal name of the particular instance of this gas sensor, used to find the corresponding channel through the muxes
	
	
	char * copyStringFlash2CharBuffer(char *, byte);//gets the string from flash memory and puts it into the local char buffer
	
	//SW Resettable	
	float _mqGasSensorR0;//the calibrated resistance (control variable). Initialize to 10 kohms but will be overwritten with calibration. (got the value from http://sandboxelectronics.com/?p=165)
	float _mqGasSensorRsR0Ratio;//the calculated ratio of Rs vs. R0
	byte _calibrationRuns;//used for sensor calibration. It's  the accumulated/sum value use for averaging.
	float _calibrationSum;//used for sensor calibration. It's the number of samples that have been taken.
	byte _readRuns;//used for sensor read. It's  the accumulated/sum value use for averaging.
	float _readSum;//used for sensor read. It's the number of samples that have been taken.

	
};

#endif 