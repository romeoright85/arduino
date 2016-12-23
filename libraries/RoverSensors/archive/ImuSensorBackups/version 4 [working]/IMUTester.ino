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
	
	Serial.println(F("MAIN LOOP"));//DEBUG
	delay(10);
	
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