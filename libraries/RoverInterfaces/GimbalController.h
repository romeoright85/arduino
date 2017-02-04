//GimbalController.h
#ifndef _GIMBALCONTROLLER_H
#define _GIMBALCONTROLLER_H

	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>
	#include <Servo.h>
	
	
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
		
	
	void gimbalReset();//resets the gimbal controller
	void gimbalSetPins(byte, byte);//(pan pin, tilt pin) sets the pin otus for the pan and tilt servos
	void gimbalSetPan(int);//sets the current pan (pan amount)
	void gimbalSetTilt(int);//sets the current throttle (throttle amount)
	int gimbalGetPanSet();//returns the amount of pan
	int gimbalGetTiltSet();//returns the amount of tilt
	//Send the amount with setPan() until the Rover is center, then use calibrationSetAsCenter()
	void gimbalCalibrationSetAsCenter();//set the current pan as the center amount		
	//Send the amount with setTilt() until the Rover is middle, then use calibrationSetAsMiddle()
	void gimbalCalibrationSetAsMiddle();//set the current tilt as the middle amount		

	

	void gimbalCalibratePan(int);// (steering amount to get the center position, ideal is 90)
	void gimbalCalibrateTilt(int);// (throttle amount to get the stop position, ideal is 90)
	int gimbalBoundToServoLimits(int);//bounds the amount (steering or calibration) to the limits of the servo
	byte gimbalPanPin;
	byte gimbalTiltPin;
	//Calibration values are between 0 and 180 where 90 is center/stop.
	int gimbalPanCalibrationOffset;
	int gimbalTiltCalibrationOffset;		
//	Servo gimbalPanControl;
//	Servo gimbalTiltControl;	

	//SW Resettable
	int gimbalPanAmount;
	int gimbalTiltAmount;

#endif 
	
	
	
	