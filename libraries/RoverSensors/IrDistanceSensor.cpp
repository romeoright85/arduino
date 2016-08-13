#include <IrDistanceSensor.h>

#include <Arduino.h>


IrDistanceSensor::IrDistanceSensor(byte IrSensorPin)
{
	this->IrSensorPin = IrSensorPin;	
}

IrDistanceSensor::~IrDistanceSensor()
{
	//do nothing
}

int IrDistanceSensor::getDistance(byte mode)
{

	//initialize variables
	int analogRawData;
	double voltage = 0;
	const int referenceVolts = 5;

	//Note: the type of distance is "int" so the value will be truncated. but since the sensor isn't that accurate in the first place due to the approximated equation, no big deal.
	distance = 0;//Inherited from DistanceSensor.h

	analogRawData = analogRead(IrSensorPin);//get the raw analog data
	voltage = analogRawData / 1023.0 * referenceVolts;//calculate the voltage
	 
	//select mode for returning the distance value
	switch (mode)
	{			
		case UNIT_CM:
			//DEBUG: WRITE THE MATH TO CONVERT THE ANALOG READING TO ACTUAL DISTANCE MEASURED LATER
			//12.628*voltage_in_v ^-1.043			
			distance = (int)(12.628*pow(voltage, -1.043));	
			break;
		case UNIT_M:
			//DEBUG: WRITE THE MATH TO CONVERT THE ANALOG READING TO ACTUAL DISTANCE MEASURED LATER
			//0.12628*voltage_in_v ^-1.043			
			distance = (int)(0.12628*pow(voltage, -1.043));
			break;
		case UNIT_IN:
			//DEBUG: WRITE THE MATH TO CONVERT THE ANALOG READING TO ACTUAL DISTANCE MEASURED LATER
			//4.9717*voltage_in_v ^-1.043			
			distance = (int)(4.9717*pow(voltage, -1.043));
			break;
		case UNIT_FT:
			//DEBUG: WRITE THE MATH TO CONVERT THE ANALOG READING TO ACTUAL DISTANCE MEASURED LATER
			//0.4143*voltage_in_v ^-1.043		
			distance = (int)(0.4143*pow(voltage, -1.043));
			break;
	}//end switch

	return distance;

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

