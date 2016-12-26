//MqGasSensor.h
#ifndef _MQ_GAS_SENSOR_H
#define _MQ_GAS_SENSOR_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <string.h>



//Reference:
//http://sandboxelectronics.com/?p=165


	
/*	
Note: MqGasSensor and RoverAnalogSignals are tightly coupled because:
RoverAnalogSignals's getGasValueOf() uses MqGasSensor's getGasPercentage()
MqGasSensor's calibrate() uses RoverAnalogSignals's getRawADCValueOf()
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
	MqGasSensor(byte);//constructor (gas sensor type)
	~MqGasSensor();//destructor
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	float calibrate();//??WRITE LATER
	int getGasPercentage();//??WRITE LATER
	int getPercentage();//??WRITE LATER
	float read();//??WRITE LATER
	float resistanceCalculation();//??WRITE LATER
	
	
private:
	//Non-SW Resettable	
	//SW Resettable
	byte _mqGasSensorType;//holds the sensor type.	
	float mqGasSensorDataCurve[3];
	String _mqGasSensorName;//holds the string of the mq sensor's name
	String _mqGasSensorUnit;//holds the string of the mq sensor's unit
	float _valueOfR0 = 10;//initialize to 10 kohms (got the value from http://sandboxelectronics.com/?p=165)
	
};

#endif 