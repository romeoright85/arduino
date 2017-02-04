//Used for NAVI - 1

#include <RoverConfig.h>

#include <RoverCalibration.h>
#include <GimbalController.h>
#include <MotorController.h>
//Global Variables




RoverReset * resetArray[] = {


};


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	gimbalReset();



	Serial.begin(9600);
	gimbalSetPins(SERVO_PAN_PIN, SERVO_TILT_PIN);
	motorControllerSetPins(MTR_RC_CTRL_STEERING_PIN, MTR_RC_CTRL_THROTTLE_PIN);
}


void loop() {

	//Tasks always running in the background with every loop() cycle

	int val;

	val = 0;
	motorControllerSetSteering(val);
	motorControllerSetThrottle(val);
	gimbalSetPan(val);
	gimbalSetTilt(val);
	delay(1000);
	val = 45;
	motorControllerSetSteering(val);
	motorControllerSetThrottle(val);
	gimbalSetPan(val);
	gimbalSetTilt(val);
	delay(1000);
	val = 90;
	motorControllerSetSteering(val);
	motorControllerSetThrottle(val);
	gimbalSetPan(val);
	gimbalSetTilt(val);
	delay(1000);	
	val = 135;
	motorControllerSetSteering(val);
	motorControllerSetThrottle(val);
	gimbalSetPan(val);
	gimbalSetTilt(val);
	delay(1000);
	val = 180;
	motorControllerSetSteering(val);
	motorControllerSetThrottle(val);
	gimbalSetPan(val);
	gimbalSetTilt(val);
	delay(1000);
	

}

