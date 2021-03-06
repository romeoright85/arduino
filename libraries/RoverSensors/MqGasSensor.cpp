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
			this->copyStringFlash2CharBuffer(this->_mqGasSensorName, MQ_SENSOR_MQ2_NAME);
			this->copyStringFlash2CharBuffer(this->_mqGasSensorUnit, MQ_SENSOR_MQ2_UNIT);			
			this->_mqGasSensorR0CleanAirFactor = MQ2_RO_CLEAN_AIR_FACTOR;			
		break;
		case GAS_SENSOR_TYPE_MQ3:
			//Alcohol Gas Sensor
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_X] = MQ3_X_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y] = MQ3_Y_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE] = MQ3_SLOPE;			
			this->copyStringFlash2CharBuffer(this->_mqGasSensorName, MQ_SENSOR_MQ3_NAME);
			this->copyStringFlash2CharBuffer(this->_mqGasSensorUnit, MQ_SENSOR_MQ3_UNIT);			
			this->_mqGasSensorR0CleanAirFactor = MQ3_RO_CLEAN_AIR_FACTOR;			
		break;
		case GAS_SENSOR_TYPE_MQ4:
			//Methane Gas Sensor
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_X] = MQ4_X_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y] = MQ4_Y_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE] = MQ4_SLOPE;			
			this->copyStringFlash2CharBuffer(this->_mqGasSensorName, MQ_SENSOR_MQ4_NAME);
			this->copyStringFlash2CharBuffer(this->_mqGasSensorUnit, MQ_SENSOR_MQ4_UNIT);			
			this->_mqGasSensorR0CleanAirFactor = MQ4_RO_CLEAN_AIR_FACTOR;
		break;
		case GAS_SENSOR_TYPE_MQ6:
			//LPG / Isobutane / Propane Gas Sensor
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_X] = MQ6_X_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y] = MQ6_Y_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE] = MQ6_SLOPE;
			this->copyStringFlash2CharBuffer(this->_mqGasSensorName, MQ_SENSOR_MQ6_NAME);
			this->copyStringFlash2CharBuffer(this->_mqGasSensorUnit, MQ_SENSOR_MQ6_UNIT);
			this->_mqGasSensorR0CleanAirFactor = MQ6_RO_CLEAN_AIR_FACTOR;
		break;
		case GAS_SENSOR_TYPE_MQ7:
			//Carbon Monoxide Gas Sensor
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_X] = MQ7_X_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y] = MQ7_Y_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE] = MQ7_SLOPE;
			this->copyStringFlash2CharBuffer(this->_mqGasSensorName, MQ_SENSOR_MQ7_NAME);
			this->copyStringFlash2CharBuffer(this->_mqGasSensorUnit, MQ_SENSOR_MQ7_UNIT);
			this->_mqGasSensorR0CleanAirFactor = MQ7_RO_CLEAN_AIR_FACTOR;
		break;
		case GAS_SENSOR_TYPE_MQ9:
			//Carbon Monoxide & Flammable Gas Sensor
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_X] = MQ9_X_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y] = MQ9_Y_PT;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE] = MQ9_SLOPE;			
			this->copyStringFlash2CharBuffer(this->_mqGasSensorName, MQ_SENSOR_MQ9_NAME);
			this->copyStringFlash2CharBuffer(this->_mqGasSensorUnit, MQ_SENSOR_MQ9_UNIT);			
			this->_mqGasSensorR0CleanAirFactor = MQ9_RO_CLEAN_AIR_FACTOR;
		break;
		default:
			//For Invalid Results
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_X] = 0.0;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y] = 0.0;
			this->_mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE] = 0.0;			
			this->copyStringFlash2CharBuffer(this->_mqGasSensorName, MQ_SENSOR_NULL_NAME);
			this->copyStringFlash2CharBuffer(this->_mqGasSensorUnit, MQ_SENSOR_NULL_UNIT);			
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
	
	this->_calibrationRuns = 0;
	this->_calibrationSum = 0.0;
	this->_readRuns = 0;
	this->_readSum = 0.0;	
	
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
boolean MqGasSensor::gasSensorWarmedUp(byte minutes)
{
	
	if(minutes >= GAS_SENSOR_WARM_UP_TIME)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}
//Calibration Sum
void MqGasSensor::setCalibrationSum(float calibrationSum)
{
	this->_calibrationSum = calibrationSum;
}
float MqGasSensor::getCalibrationSum()
{
	return this->_calibrationSum;
}
//Calibration Runs
void MqGasSensor::setCalibrationRuns(byte calibrationRuns)
{
	this->_calibrationRuns = calibrationRuns;
}
byte MqGasSensor::getCalibrationRuns()
{
	return this->_calibrationRuns;
}
//Read Runs
void MqGasSensor::setReadRuns(byte readRuns)
{
	this->_readRuns = readRuns;
}
byte MqGasSensor::getReadRuns()
{
	return this->_readRuns;
}
//Read Sums
void MqGasSensor::setReadSum(float readSum)
{
	this->_readSum = readSum;
}
float MqGasSensor::getReadSum()
{
	return this->_readSum;
}
char * MqGasSensor::getMqGasSensorName()
{
	return this->_mqGasSensorName;
}
char * MqGasSensor::getMqGasSensorUnit()
{
	return this->_mqGasSensorUnit;
}
byte MqGasSensor::getMqGasSensorNameLength()
{
	return CharArray::stringSize(this->_mqGasSensorName,sizeof(this->_mqGasSensorName));	
}
byte MqGasSensor::getMqGasSensorUnitLength()
{
	return CharArray::stringSize(this->_mqGasSensorUnit,sizeof(this->_mqGasSensorUnit));
}
char * MqGasSensor::copyStringFlash2CharBuffer(char * charBuffer, byte arrayIndex) {
	memset(charBuffer, 0, sizeof(charBuffer));//clear char array buffer
	return strcpy_P(charBuffer, (char*)pgm_read_word(&(mq_gas_string_table[arrayIndex])));//copy the fixed string from flash into the char buffer
}//end of copyStringFlash2CharBuffer()

