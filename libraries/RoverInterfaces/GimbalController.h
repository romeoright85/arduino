//GimbalController.h
#ifndef _GIMBALCONTROLLER_H
#define _GIMBALCONTROLLER_H

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
	
	#define _GIMBALCONTROLLER_DEFINITIONS
	
	/********************************************************************/
	
	#include <RoverConfig.h>
	
	#define _SERVOSIGNAL_CALIBRATIONS
	#define _GIMBALCONTROLLER_CALIBRATIONS
	#include <RoverCalibration.h>
		
	
	
	
	
	//Note: By design, the reset will clear any current calibration values and go back to the 	GC_CENTER_POSITION_AFTER_POR and GC_MIDDLE_POSITION_AFTER_POR and MC_NO_THROTTLE_AFTER_POR values as defined in RoverConfig.h	
	void gimbalReset();//software resets the gimbal controller
	void gimbalSetPins(byte, byte);//(pan pin, tilt pin) sets the pinouts for the pan and tilt servos
	//Note: The int type has to be used since the calibration values may be positive or negative
	void gimbalSetPan(int);//sets the current pan (pan amount)
	void gimbalSetTilt(int);//sets the current throttle (throttle amount)
	int gimbalGetPanSet();//returns the amount of pan
	int gimbalGetTiltSet();//returns the amount of tilt	
	//Note: On initial power up the calibration values will be set to the GC_CENTER_POSITION_AFTER_POR and GC_MIDDLE_POSITION_AFTER_POR values as defined in RoverConfig.h
	//Send the amount with gimbalSetPan() until the Rover is center, then use gimbalCalibrationSetAsCenter()
	void gimbalCalibrationSetAsCenter();//set the current pan as the center amount		
	//Send the amount with gimbalSetTilt() until the Rover is middle, then use gimbalCalibrationSetAsMiddle()
	void gimbalCalibrationSetAsMiddle();//set the current tilt as the middle amount		
	void gimbalCalibratePan(int);// (steering amount to get the center position, ideal is 90)
	void gimbalCalibrateTilt(int);// (throttle amount to get the stop position, ideal is 90)
	int gimbalBoundToServoLimits(int);//bounds the amount (steering or calibration) to the limits of the servo
	void gimbalFunctionalDemo(BufferSelect *);//demos the functionality of the gimbal pan and tilt (good for demo and/or testing). Will only work when Rover Buffer is in Auto Mode.
	
	//Non-SW Resettable
	byte gimbalPanPin;
	byte gimbalTiltPin;	
	Servo gimbalPanControl;
	Servo gimbalTiltControl;	
	
	//SW Resettable
	//Calibration values are between 0 and 180 where 90 is the center/middle/stop.
	int gimbalPanCalibrationOffset;
	int gimbalTiltCalibrationOffset;
	int gimbalPanAmount;
	int gimbalTiltAmount;

#endif 
	
	
	
	