//uncomment to print debugging information
//Note: Since MotorController.cpp isn't calling MotorController.h (since global variables define it in and can't have duplication since MotorController.h is called by the main .ino file already), then put this debug verbose flag here
//#define _DEBUG_VERBOSE



#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <Servo.h>
#include <BufferSelect.h>



/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/
//define Arduino 1: NAVI in order to use it's config pins
#ifndef _ARD_1_NAVI_H
	#define _ARD_1_NAVI_H
#endif

#define _MOTORCONTROLLER_DEFINITIONS

/********************************************************************/
#include <RoverConfig.h>

#define _SERVOSIGNAL_CALIBRATIONS
#define _MOTORCONTROLLER_CALIBRATIONS
#include <RoverCalibration.h>


//Non-SW Resettable			
extern byte motorControllerSteeringPin;
extern byte motorControllerThrottlePin;
extern Servo motorControllerSteeringControl;
extern Servo motorControllerThrottleControl;	

//SW Resettable
//Calibration values are between 0 and 180 where 90 is the center/middle/stop.
extern int motorControllerSteeringCalibrationOffset;
extern int motorControllerThrottleCalibrationOffset;
extern int motorControllerSteeringAmount;
extern int motorControllerThrottleAmount;	


//Note: Some functions have to be on top of another if one is calling the other, then the calling one has to be defined after the one being called.

int motorControllerBoundToServoLimits(int amount)
{
	//Adjust the amount to boundary limitations
	if(amount>=SRVO_MAX_RANGE)
	{
		return SRVO_MAX_RANGE;
	}		
	else	if(amount<=SRVO_MIN_RANGE)
	{
		return SRVO_MIN_RANGE;
	}
	else
	{
		return amount;
	}
}
void motorControllerCalibrateSteering(int steeringActualAmount)
{
	
	//Example 1: If the ideal is 90 for center but the actual center is 92 then 92 - 90 = 2, which is the _steeringCalibrationOffset 
	//Example 2: If the ideal is 90 for center but the actual center is 87 then 87 - 90 = -3, which is the _steeringCalibrationOffset 
	motorControllerSteeringCalibrationOffset = steeringActualAmount - MC_CENTER_POSITION_IDEAL;
	
}
void motorControllerCalibrateThrottle(int throttleActualAmount)
{
	
	//Example 1: If the ideal is 90 for stop but the actual stop is 92 then 92 - 90 = 2, which is the _throttleCalibrationOffset 
	//Example 2: If the ideal is 90 for stop but the actual stop is 87 then 87 - 90 = -3, which is the _throttleCalibrationOffset 
	motorControllerThrottleCalibrationOffset = throttleActualAmount - MC_NO_THROTTLE_IDEAL;
	
}
void motorControllerReset()
{	
	//At HW or SW Reset, the values will be set to MC_CENTER_POSITION_AFTER_POR and MC_NO_THROTTLE_AFTER_POR as defined in RoverCalibration.h
	motorControllerCalibrateSteering(MC_CENTER_POSITION_AFTER_POR);
	motorControllerCalibrateThrottle(MC_NO_THROTTLE_AFTER_POR);
}








void motorControllerSetPins( byte steeringPin, byte throttlePin)
{
	
	//Set the pins
	motorControllerSteeringPin = steeringPin;
	motorControllerThrottlePin = throttlePin;	
	
	//set the pins
	motorControllerSteeringControl.attach(motorControllerSteeringPin);
	motorControllerThrottleControl.attach(motorControllerThrottlePin);	
	
	//Initialize
	motorControllerReset();
	
}


void motorControllerSetSteering(int steeringAmount)
{
	//Add the calibration offset amount (could be a positive or negative offset) to the desired amount to get the adjusted amount
	steeringAmount = steeringAmount + motorControllerSteeringCalibrationOffset;
	
	//Adjust the amount to boundary limitations	
	motorControllerSteeringAmount = motorControllerBoundToServoLimits(steeringAmount);
	
	//Execute with the final adjusted amount
	motorControllerSteeringControl.write(motorControllerSteeringAmount);	
	
}
void motorControllerSetThrottle(int throttleAmount)
{


	//Add the calibration offset amount (could be a positive or negative offset) to the desired amount to get the adjusted amount
	throttleAmount = throttleAmount + motorControllerThrottleCalibrationOffset;
		
	//Adjust the amount to boundary limitations	
	motorControllerThrottleAmount = motorControllerBoundToServoLimits(throttleAmount);
		
	//Execute with the final adjusted amount
	motorControllerThrottleControl.write(motorControllerThrottleAmount);		

}
int motorControllerGetSteeringSet()
{
	
	return motorControllerSteeringAmount;//can be values between SRVO_MIN_RANGE to SRVO_MAX_RANGE
	
}
int motorControllerGetThrottleSet()
{
	
	return motorControllerThrottleAmount;//can be values between SRVO_MIN_RANGE to SRVO_MAX_RANGE
		
}

void motorControllerCalibrationSetAsCenter()
{	
	motorControllerCalibrateSteering(motorControllerGetSteeringSet());//get the current amount set and use it as the calibration amount
}
void motorControllerCalibrationSetAsStop()
{
	motorControllerCalibrateThrottle(motorControllerGetThrottleSet());//get the current amount set and use it as the calibration amount
}

void motorControllerPowerOnCalibration(BufferSelect * roverBuffer)
{
	//Only run the power on calibration if the roverBuffer is set to auto mode, else do nothing, since in manual mode, the calibration is done with the R/C remote controller
	if(roverBuffer->inAutoMode())
	{
		Serial.println(F("Pwr On Mtr Cal - Start"));
		//Start at stop and center
		motorControllerSetSteering(MC_CENTER_POSITION_IDEAL);
		motorControllerSetThrottle(MC_NO_THROTTLE_IDEAL);				
		delay(1200);
		//Turn right max
		motorControllerSetSteering(MC_MAX_RIGHT_POSITION_IDEAL);
		delay(1200);
		//Turn left max
		motorControllerSetSteering(MC_MAX_LEFT_POSITION_IDEAL);
		delay(1200);
		//Return to Center
		motorControllerSetSteering(MC_CENTER_POSITION_IDEAL);
		//Go Forward Max
		motorControllerSetThrottle(MC_MAX_FWD_THROTTLE_IDEAL);
		delay(1200);
		//Go Reverse Max
		motorControllerSetThrottle(MC_MAX_REV_THROTTLE_IDEAL);
		delay(1200);
		//Return to stop		
		motorControllerSetThrottle(MC_NO_THROTTLE_IDEAL);				
		Serial.println(F("Pwr On Mtr Cal - Done"));
	}//end if
}

