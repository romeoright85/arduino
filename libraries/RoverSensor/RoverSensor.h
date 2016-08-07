//RoverSensor.h
#ifndef _ROVERSENSOR_H
#define _ROVERSENSOR_H

#include <Arduino.h>




		class RoverSensor {
		public:
			RoverSensor();//constructor
			~RoverSensor();//destructor
			void setName(String);
			String getName();
		private:
			String sensorName;
			static int sensorID;//the ID/object counter
		};


#endif 