#include <MqGasSensor.h>


MqGasSensor::MqGasSensor(byte mqGasSensorType)
{
	this->mqGasSensorType = mqGasSensorType;
	
	
	
	
	switch(this->mqGasSensorType)
	{
		case GAS_SENSOR_TYPE_MQ2:
			//Flammable Gas & Smoke Sensor		
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_X] = MQ2_X_PT;
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y] = MQ2_Y_PT;
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE] = MQ2_SLOPE;
			this->_mqGasSensorName = "Flammable Gas & Smoke ";
			this->_mqGasSensorUnit = "ppm";//taken from the "Concentration" row of the datasheet
		break;
		case GAS_SENSOR_TYPE_MQ3:
			//Alcohol Gas Sensor
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_X] = MQ3_X_PT;
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y] = MQ3_Y_PT;
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE] = MQ3_SLOPE;
			this->_mqGasSensorName = "Alcohol";
			this->_mqGasSensorUnit = "mg/l";//taken from the "Concentration" row of the datasheet
		break;
		case GAS_SENSOR_TYPE_MQ4:
			//Methane Gas Sensor
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_X] = MQ4_X_PT;
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y] = MQ4_Y_PT;
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE] = MQ4_SLOPE;
			this->_mqGasSensorName = "Methane";
			this->_mqGasSensorUnit = "ppm";//taken from the "Concentration" row of the datasheet
		break;
		case GAS_SENSOR_TYPE_MQ6:
			//LPG / Isobutane / Propane Gas Sensor
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_X] = MQ6_X_PT;
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y] = MQ6_Y_PT;
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE] = MQ6_SLOPE;
			this->_mqGasSensorName = "LPG / Isobutane / Propane";
			this->_mqGasSensorUnit = "ppm";//taken from the "Concentration" row of the datasheet
		break;
		case GAS_SENSOR_TYPE_MQ7:
			//Carbon Monoxide Gas Sensor
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_X] = MQ7_X_PT;
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y] = MQ7_Y_PT;
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE] = MQ7_SLOPE;
			this->_mqGasSensorName = "Carbon Monoxide";
			this->_mqGasSensorUnit = "ppm";//taken from the "Concentration" row of the datasheet
		break;
		case GAS_SENSOR_TYPE_MQ9:
			//Carbon Monoxide & Flammable Gas Sensor
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_X] = MQ9_X_PT;
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y] = MQ9_Y_PT;
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE] = MQ9_SLOPE;
			this->_mqGasSensorName = "Carbon Monoxide & Flammable Gas";
			this->_mqGasSensorUnit = "ppm";//taken from the "Concentration" row of the datasheet
		break;
		default:
			//For Invalid Results
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_X] = 0;
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_Y] = 0;
			mqGasSensorDataCurve[GAS_SENSOR_CURVE_SLOPE] = 0;
			this->_mqGasSensorName = "Invalid";
			this->_mqGasSensorUnit = "Error";
		break;		
	}
	

 


	
	
}
MqGasSensor::~MqGasSensor()
{
	//do nothing
}
void MqGasSensor::reset()
{
}

