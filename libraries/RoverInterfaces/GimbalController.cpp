//uncomment to print debugging information
//Note: Since GimbalController.cpp isn't calling GimbalController.h (since global variables define it in and can't have duplication since GimbalController.h is called by the main .ino file already), then put this debug verbose flag here
#define _DEBUG_VERBOSE


#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>
#include <Servo.h>


extern byte gimbalPanPin;
extern byte gimbalTiltPin;
//Calibration values are between 0 and 180 where 90 is center/stop.
extern int gimbalPanCalibrationOffset;
extern int gimbalTiltCalibrationOffset;		
Servo gimbalPanControl;
Servo gimbalTiltControl;	

//SW Resettable
extern int gimbalPanAmount;
extern int gimbalTiltAmount;


/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/
//define Arduino 1: NAVI in order to use it's config pins
#ifndef _ARD_1_NAVI_H
	#define _ARD_1_NAVI_H
#endif

#define _GIMBALCONTROLLER_DEFINITIONS

/********************************************************************/

#include <RoverConfig.h>

#define _SERVOSIGNAL_CALIBRATIONS
#define _GIMBALCONTROLLER_CALIBRATIONS
#include <RoverCalibration.h>
	
	
int gimbalBoundToServoLimits(int amount)
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
void gimbalCalibratePan(int panActualAmount)
{
	
	//Example 1: If the ideal is 90 for center but the actual center is 92 then 92 - 90 = 2, which is the _panCalibrationOffset 
	//Example 2: If the ideal is 90 for center but the actual center is 87 then 87 - 90 = -3, which is the _panCalibrationOffset 
	gimbalPanCalibrationOffset = panActualAmount - GC_CENTER_POSITION_IDEAL;
	
}
void gimbalCalibrateTilt(int tiltActualAmount)
{
	
	//Example 1: If the ideal is 90 for stop but the actual stop is 92 then 92 - 90 = 2, which is the _tiltCalibrationOffset 
	//Example 2: If the ideal is 90 for stop but the actual stop is 87 then 87 - 90 = -3, which is the _tiltCalibrationOffset 
	gimbalTiltCalibrationOffset = tiltActualAmount - GC_MIDDLE_POSITION_IDEAL;
	
}
void gimbalReset()
{	
	//At HW or SW Reset, the values will be set to GC_CENTER_POSITION_AFTER_POR and GC_MIDDLE_POSITION_AFTER_POR as defined in RoverCalibration.h
	gimbalCalibratePan(GC_CENTER_POSITION_AFTER_POR);
	gimbalCalibrateTilt(GC_MIDDLE_POSITION_AFTER_POR);
}
void gimbalSetPins( byte panPin, byte tiltPin)
{
	
	//Set the pins
	gimbalPanPin = panPin;
	gimbalTiltPin = tiltPin;	

	
	
	//set the pins
	gimbalPanControl.attach(gimbalPanPin);
	gimbalTiltControl.attach(gimbalTiltPin);	
	
	//Initialize
	gimbalReset();
}


void gimbalSetPan(int panAmount)
{
	//Add the calibration offset amount (could be a positive or negative offset) to the desired amount to get the adjusted amount
	panAmount = panAmount + gimbalPanCalibrationOffset;
	
	//Adjust the amount to boundary limitations	
	gimbalPanAmount = gimbalBoundToServoLimits(panAmount);
	
	
	#ifdef _DEBUG_VERBOSE
		Serial.print(F("gimbalPanAmount: "));//DEBUG
		Serial.println(gimbalPanAmount);//DEBUG
	#endif
	
	//Execute with the final adjusted amount
	gimbalPanControl.write(gimbalPanAmount);	
	
}
void gimbalSetTilt(int tiltAmount)
{

	//Add the calibration offset amount (could be a positive or negative offset) to the desired amount to get the adjusted amount
	tiltAmount = tiltAmount + gimbalTiltCalibrationOffset;
		
	//Adjust the amount to boundary limitations	
	gimbalTiltAmount = gimbalBoundToServoLimits(tiltAmount);
			
	#ifdef _DEBUG_VERBOSE
		Serial.print(F("gimbalTiltAmount: "));//DEBUG
		Serial.println(gimbalTiltAmount);//DEBUG
	#endif		
		
	//Execute with the final adjusted amount
	gimbalTiltControl.write(gimbalTiltAmount);		

}
int gimbalGetPanSet()
{
	
	return gimbalPanAmount;//can be values between SRVO_MIN_RANGE to SRVO_MAX_RANGE
	
}
int gimbalGetTiltSet()
{
	
	return gimbalTiltAmount;//can be values between SRVO_MIN_RANGE to SRVO_MAX_RANGE
		
}



void gimbalCalibrationSetAsCenter()
{	
	gimbalCalibratePan(gimbalGetPanSet());//get the current amount set and use it as the calibration amount
}
void gimbalCalibrationSetAsMiddle()
{
	gimbalCalibrateTilt(gimbalGetTiltSet());//get the current amount set and use it as the calibration amount
}

	