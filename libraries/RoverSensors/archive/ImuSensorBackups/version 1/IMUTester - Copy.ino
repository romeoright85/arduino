#include <ImuSensor.h>

//NOTE: The IMU Must be connected to the Arduino for this code to work.
//See RoverConfig.h for pinouts

//Global Variables

ImuSensor * imuSensor = new ImuSensor();




RoverReset * resetArray[] = { imuSensor };



void setup() {
		
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}


	Serial.begin(9600);

	imuSensor->init();
}


void loop() {
	
	Serial.println("2DEBUG");//DEBUG

	
	/*
	//Declare variables
	float roverRoll;
	float roverPitch;
	float roverYaw;
	float roverHeading;

	//Get IMU Data
	Serial.println(F("IMU Data"));
	imuSensor->readSensor();

	//AHRS = An attitude and heading reference system
	Serial.println(F("Roll/Pitch/Yaw"));
	roverRoll = imuSensor->getRoll();
	Serial.print("Roll: ");
	Serial.println(roverRoll);
	roverPitch = imuSensor->getPitch();
	Serial.print("Pitch: ");
	Serial.println(roverPitch);
	roverYaw = imuSensor->getYaw();
	Serial.print("Yaw: ");
	Serial.println(roverYaw);
	
	//Compass
	Serial.println(F("Compass Heading"));
	roverHeading = imuSensor->getHeading();	
	Serial.print("Heading: ");
	Serial.println(roverHeading);


	Serial.print("AHRS: ");
	imuSensor->printForAHRS();
		
	delay(2000);//DEBUG
		*/		
}


/*

!ANG:0.27,1.56,16.47
!ANG:0.24,1.57,16.46
!ANG:0.26,1.56,16.46
!ANG:0.38,1.61,16.47
!ANG:0.38,1.63,16.46
!ANG:0.42,1.63,16.47
!ANG:0.45,1.61,16.47
!ANG:0.41,1.61,16.47

*/