#include <RoverSensor.h>
int RoverSensor::sensorID = 0;//initialize the ID/object counter

RoverSensor::RoverSensor()
{

	String sensorName = "SensorID: " + String(sensorID);
	setName(sensorName);
	RoverSensor::sensorID++;//increment the ID/object counter for the next sensor object to be created
}
RoverSensor::~RoverSensor()
{
	//do nothing
}

void RoverSensor::setName(String name)
{
	sensorName = name;
}

String RoverSensor::getName()
{
	return sensorName;
}
