#define _IMUDATATYPES //used with RoverConfig.h
#include <ImuSensor.h>


//Global Variables

ImuSensor * imuSensor = new ImuSensor();

RoverReset * resetArray[] = { imuSensor };
int gyroData[3];
int compassData[3];
int accelerometerData[3] = { 3,1,4 };

void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	
	Serial.begin(9600);

}


void loop() {
	imuSensor->readIMUSensor();
	imuSensor->getAccelerometerData(accelerometerData);

	char charBuffer[50];
	//sprintf(charBuffer, "");//DEBUG
	//Serial.println(charBuffer);
	Serial.println(accelerometerData[0]);//DEBUG
	Serial.println(accelerometerData[1]);//DEBUG
	Serial.println(accelerometerData[2]);//DEBUG
	delay(1000);//DEBUG
}
