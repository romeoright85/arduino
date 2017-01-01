#include <IrDistanceSensor.h>

#include <Arduino.h>


IrDistanceSensor::IrDistanceSensor(byte irSensorPin)
{
	
	this->_irSensorPin = irSensorPin;	
	this->_roverAdc = new RoverAdc();
	
}

IrDistanceSensor::~IrDistanceSensor()
{
	//do nothing
}

int IrDistanceSensor::getDistance(byte mode)
{

	//initialize variables
	double voltage = 0.0;
	double avgVoltage = 0.0;
	
	//Note: the type of distance is "int" so the value will be truncated. but since the sensor isn't that accurate in the first place due to the approximated equation, no big deal.
	this->_distance = 0;//Inherited from DistanceSensor.h
		
	
	for(byte i = 0; i < INFRARED_SENSOR_SAMPLE_TIMES; i++)
	{
	
		voltage = this->_roverAdc->voltageRead(this->_irSensorPin);//get the raw analog data
		
		//overwrite actual data with test case data if in debugging
		#ifdef _DEBUG_TEST_CASE //tests with random but object detected pulse width numbers			
			voltage = 5.0*random(0,100)/100;//DEBUG
			Serial.print(F("Voltage: "));//DEBUG
			Serial.println(voltage);			
		#endif	
		
		//accumulate voltage values
		avgVoltage += voltage;
		
	}//end for

	avgVoltage = avgVoltage/INFRARED_SENSOR_SAMPLE_TIMES;
	
	#ifdef _DEBUG_TEST_CASE //tests with random but object detected pulse width numbers						
		Serial.print(F("Avg Voltage: "));//DEBUG
		Serial.println(avgVoltage);			
	#endif	

	//select mode for returning the distance value
	switch (mode)
	{			
		case UNIT_CM:
			//DEBUG: WRITE THE MATH TO CONVERT THE ANALOG READING TO ACTUAL DISTANCE MEASURED LATER
			//12.628*voltage_in_v ^-1.043			
			this->_distance = (int)(12.628*pow(avgVoltage, -1.043));	
			break;
		case UNIT_M:
			//DEBUG: WRITE THE MATH TO CONVERT THE ANALOG READING TO ACTUAL DISTANCE MEASURED LATER
			//0.12628*voltage_in_v ^-1.043			
			this->_distance = (int)(0.12628*pow(avgVoltage, -1.043));
			break;
		case UNIT_IN:
			//DEBUG: WRITE THE MATH TO CONVERT THE ANALOG READING TO ACTUAL DISTANCE MEASURED LATER
			//4.9717*voltage_in_v ^-1.043			
			this->_distance = (int)(4.9717*pow(avgVoltage, -1.043));
			break;
		case UNIT_FT:
			//DEBUG: WRITE THE MATH TO CONVERT THE ANALOG READING TO ACTUAL DISTANCE MEASURED LATER
			//0.4143*voltage_in_v ^-1.043		
			this->_distance = (int)(0.4143*pow(avgVoltage, -1.043));
			break;
	}//end switch

	return this->_distance;

}

void IrDistanceSensor::reset()
{
	//software reset
	this->_distance = 0;//Inherited from DistanceSensor.h
}




//References:
//Sharp Sensor Model: GP2D120XJ00F
//https://acroname.com/blog/linearizing-sharp-ranger-data1024*3
//https://www.sparkfun.com/products/retired/8959
//not same model but reference only: http://oomlout.com/PROX/PROX-Guide.pdf
//http://luckylarry.co.uk/arduino-projects/arduino-using-a-sharp-ir-sensor-for-distance-calculation/
//K:\Working Directory\DESIGN_PROJ\Design Projects\Inventory\Inventory Datasheets\Sparkfun\SEN-08959
//distance _in_cm=12.628*voltage_in_v ^-1.043 (eyeballed datasheet for data points, then used excel to create a graph and added a trendline to get the equation)
//make sure to convert the analogRead value (0 to 1024) to voltage

