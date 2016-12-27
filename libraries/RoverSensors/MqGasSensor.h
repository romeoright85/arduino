//MqGasSensor.h
#ifndef _MQ_GAS_SENSOR_H
#define _MQ_GAS_SENSOR_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <string.h>





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
	
//MOVE THIS mqGasSensorDataCurve TO BE A PRIVATE VARIABLE AND MAKE A GETTER METHOD	
	
//ALSO WRITE CODE FOR IT TO WAIT FOR THE UPTIME TO BE 3 MINUTES BEFORE CALIBRATION
//GO BACK AND WRITE CALIBRATION FUNCTIONS FOR OTHER SENSORS	
	
private:
	//Non-SW Resettable		
	float _mqGasSensorDataCurve[3];//need to make this variable public so the array data can be read from	
	String _mqGasSensorName;//holds the string of the mq sensor's name
	String _mqGasSensorUnit;//holds the string of the mq sensor's unit	
	byte _mqGasSensorType;//holds the sensor type.
	float _mqGasSensorR0CleanAirFactor;
	double _mqGasSensorFixedResistorValue;
	byte _analogSignalName;//holds the analog signal name of the particular instance of this gas sensor, used to find the corresponding channel through the muxes
	
	//SW Resettable	
	float _mqGasSensorR0;//the calibrated resistance (control variable). Initialize to 10 kohms but will be overwritten with calibration. (got the value from http://sandboxelectronics.com/?p=165)
	float _mqGasSensorRsR0Ratio;//the calculated ratio of Rs vs. R0
	
		
};

#endif 