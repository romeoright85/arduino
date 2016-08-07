//Sensor.h
#ifndef _SENSOR_H
#define _SENSOR_H

	using namespace std;

	#include <string.h>
	#include <map>

		class Sensor {
		public:
			Sensor();//constructor
			~Sensor();//destructor
			void setProperty(string propertyName, string propertyValue);
			string getProperty(string propertyName);
			void setName(string);
			string getName();
		private:
			map<string, string> properties;//contains properties of the sensor
			string sensorName;
			static sensorID = 0;//initialize the ID/object counter
		};


#endif 