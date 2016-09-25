#define _IMUDATATYPES //used with RoverConfig.h
#include <ImuSensor.h>


//Global Variables

ImuSensor * imuSensor = new ImuSensor();

RoverReset * resetArray[] = { imuSensor };
int gyroXYZData[3];
float compassHeading;
int accelerometerXYZData[3];

void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	Serial.begin(9600);

	while (!imuSensor->init());//must not be done in the global, but either in the setup() or the loop()

}


void loop() {
		
	//Get IMU Data
	Serial.println(F("IMU Data"));
	imuSensor->readSensor();
			
	//Gyro
	Serial.println(F("Gyro XYZ"));
	imuSensor->getGyroXYZData(gyroXYZData);
	Serial.println(gyroXYZData[X_DATA]);//DEBUG
	Serial.println(gyroXYZData[Y_DATA]);//DEBUG
	Serial.println(gyroXYZData[Z_DATA]);//DEBUG
	
	//Compass
	Serial.println(F("Compass Heading"));
	compassHeading = imuSensor->getCompassHeading();
	Serial.println(compassHeading);//DEBUG

	//Accelerometer
	Serial.println(F("Accelerometer XYZ"));
	imuSensor->getAccelerometerXYZData(accelerometerXYZData);
	Serial.println(accelerometerXYZData[X_DATA]);//DEBUG
	Serial.println(accelerometerXYZData[Y_DATA]);//DEBUG
	Serial.println(accelerometerXYZData[Z_DATA]);//DEBUG

	delay(2000);//DEBUG
	/*
	//Reset IMU Data
	Serial.println(F("IMU Reset"));
	imuSensor->reset();
		
	//Gyro
	Serial.println(F("Gyro XYZ"));
	imuSensor->getGyroXYZData(gyroXYZData);
	Serial.println(gyroXYZData[X_DATA]);//DEBUG
	Serial.println(gyroXYZData[Y_DATA]);//DEBUG
	Serial.println(gyroXYZData[Z_DATA]);//DEBUG

	//Compass
	Serial.println(F("Compass Heading"));
	compassHeading = imuSensor->getCompassHeading();
	Serial.println(compassHeading);//DEBUG

	//Accelerometer
	Serial.println(F("Accelerometer XYZ"));
	imuSensor->getAccelerometerXYZData(accelerometerXYZData);
	Serial.println(accelerometerXYZData[X_DATA]);//DEBUG
	Serial.println(accelerometerXYZData[Y_DATA]);//DEBUG
	Serial.println(accelerometerXYZData[Z_DATA]);//DEBUG

	delay(2000);//DEBUG
	*/
}
