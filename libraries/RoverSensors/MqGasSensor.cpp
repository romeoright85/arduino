#include <MqGasSensor.h>


MqGasSensor::MqGasSensor(byte mqGasSensorType, byte analogSignalName, double mqGasSensorFixedResistorValue)
{
	//Assign variables
	this->_mqGasSensorType = mqGasSensorType;
	this->_mqGasSensorFixedResistorValue = mqGasSensorFixedResistorValue;
	this->_analogSignalName = analogSignalName;
	
	//Configure the MqGasSensor object based on the sensor type
	switch(this->_mqGasSensorType)
	{
		case GAS_SENSOR_TYPE_MQ2:
			//Flammable Gas & Smoke Sensor		
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_X] = MQ2_X_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y] = MQ2_Y_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE] = MQ2_SLOPE;
			this->_mqGasSensorName = "Flammable Gas & Smoke ";
			this->_mqGasSensorUnit = "ppm";//taken from the "Concentration" row of the datasheet
			this->_mqGasSensorR0CleanAirFactor = MQ2_RO_CLEAN_AIR_FACTOR;			
		break;
		case GAS_SENSOR_TYPE_MQ3:
			//Alcohol Gas Sensor
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_X] = MQ3_X_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y] = MQ3_Y_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE] = MQ3_SLOPE;
			this->_mqGasSensorName = "Alcohol";
			this->_mqGasSensorUnit = "mg/l";//taken from the "Concentration" row of the datasheet
			this->_mqGasSensorR0CleanAirFactor = MQ3_RO_CLEAN_AIR_FACTOR;			
		break;
		case GAS_SENSOR_TYPE_MQ4:
			//Methane Gas Sensor
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_X] = MQ4_X_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y] = MQ4_Y_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE] = MQ4_SLOPE;
			this->_mqGasSensorName = "Methane";
			this->_mqGasSensorUnit = "ppm";//taken from the "Concentration" row of the datasheet
			this->_mqGasSensorR0CleanAirFactor = MQ4_RO_CLEAN_AIR_FACTOR;
		break;
		case GAS_SENSOR_TYPE_MQ6:
			//LPG / Isobutane / Propane Gas Sensor
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_X] = MQ6_X_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y] = MQ6_Y_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE] = MQ6_SLOPE;
			this->_mqGasSensorName = "LPG / Isobutane / Propane";
			this->_mqGasSensorUnit = "ppm";//taken from the "Concentration" row of the datasheet
			this->_mqGasSensorR0CleanAirFactor = MQ6_RO_CLEAN_AIR_FACTOR;
		break;
		case GAS_SENSOR_TYPE_MQ7:
			//Carbon Monoxide Gas Sensor
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_X] = MQ7_X_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y] = MQ7_Y_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE] = MQ7_SLOPE;
			this->_mqGasSensorName = "Carbon Monoxide";
			this->_mqGasSensorUnit = "ppm";//taken from the "Concentration" row of the datasheet
			this->_mqGasSensorR0CleanAirFactor = MQ7_RO_CLEAN_AIR_FACTOR;
		break;
		case GAS_SENSOR_TYPE_MQ9:
			//Carbon Monoxide & Flammable Gas Sensor
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_X] = MQ9_X_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y] = MQ9_Y_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE] = MQ9_SLOPE;
			this->_mqGasSensorName = "Carbon Monoxide & Flammable Gas";
			this->_mqGasSensorUnit = "ppm";//taken from the "Concentration" row of the datasheet
			this->_mqGasSensorR0CleanAirFactor = MQ9_RO_CLEAN_AIR_FACTOR;
		break;
		default:
			//For Invalid Results
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_X] = 0.0;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y] = 0.0;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE] = 0.0;
			this->_mqGasSensorName = "Invalid";
			this->_mqGasSensorUnit = "Error";
			this->_mqGasSensorR0CleanAirFactor = 0.0;
		break;		
	}
	
	
	//initalize/reset the sensor values
	this->reset();
	
}
MqGasSensor::~MqGasSensor()
{
	//do nothing
}
void MqGasSensor::reset()
{	

	/*
	Note:
		_mqGasSensorR0, once calibrated, will represent the resistance of the sensor in environment of 20degC and 65% RH:
			for MQ-2: 1000ppm Methane
			for MQ-3: 0.4 mg/l Alcohol
			for MQ-4: 1000ppm Methane
			for MQ-6: 1000ppm Propane
			for MQ-7: 100ppm C0
			for MQ-9: 1000ppm Propane
	*/

	//reset to 10 kohms (got the value from http://sandboxelectronics.com/?p=165)	
	this->_mqGasSensorR0 = 10.0;
	
}
byte MqGasSensor::getAnalogSignalName()
{
	return this->_analogSignalName;
}
double MqGasSensor::getFixedResistorValue()
{
	return this->_mqGasSensorFixedResistorValue;
}
float MqGasSensor::getR0CleanAirFactor()
{
	return this->_mqGasSensorR0CleanAirFactor;
}
void MqGasSensor::setR0(float valueOfR0)
{
	this->_mqGasSensorR0 = valueOfR0;
}
float MqGasSensor::getR0()
{
	return this->_mqGasSensorR0;
}
void MqGasSensor::setRsRoRatio(double mqGasSensorRsR0Ratio)
{
	this->_mqGasSensorRsR0Ratio = mqGasSensorRsR0Ratio;
	

	
}
double MqGasSensor::getRsR0Ratio()
{
	return this->_mqGasSensorRsR0Ratio;
}
float MqGasSensor::getX()
{
	return this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_X];
}
float MqGasSensor::getY()
{
	return this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y];
}
float MqGasSensor::getSlope()
{
	return this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE];
}	
	