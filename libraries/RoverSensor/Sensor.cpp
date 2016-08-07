#include <Sensor.h>


Sensor::Sensor()
{
	string sensorName = "default" + sensorID++;
	setName(sensorName);
	sensorID++;//increment the ID/object counter for the next sensor object to be created
}
Sensor::~Sensor()
{
	//do nothing
}
void Sensor::setProperty(string propertyName, string propertyValue)
{
	properties[property_name] = propertyValue;
}

string Sensor::getProperty(string propertyName)
{
	//search for the property value that corresponds to the property name and return it
	return properties.find(propertyName);
}

void Sensor::setName(string name)
{
	sensorName = name;
}

string Sensor::getName()
{
	return sensorName;
}
