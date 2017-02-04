//Used for NAVI - 1

#include <RoverConfig.h>

#include <RoverCalibration.h>
#include <GimbalController.h>
//Global Variables




RoverReset * resetArray[] = {


};


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	Serial.begin(9600);
	gimbalSetPins(SERVO_PAN_PIN, SERVO_TILT_PIN);
	gimbalReset();
}


void loop() {

	//Tasks always running in the background with every loop() cycle

	gimbalSetPan(0);
	gimbalSetTilt(0);
	delay(1000);
	gimbalSetPan(45);
	gimbalSetTilt(45);
	delay(1000);
	gimbalSetPan(90);
	gimbalSetTilt(90);
	delay(1000);	
	gimbalSetPan(135);
	gimbalSetTilt(135);
	delay(1000);
	gimbalSetPan(180);
	gimbalSetTilt(180);
	delay(1000);
	

}

