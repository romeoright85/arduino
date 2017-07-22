//MotorController.h
#ifndef _MOTORCONTROLLER_H
#define _MOTORCONTROLLER_H

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
	
	
	
		//Note: By design, the reset will clear any current calibration values and go back to the 	MC_CENTER_POSITION_AFTER_POR and MC_NO_THROTTLE_AFTER_POR values as defined in RoverConfig.h
		void motorControllerReset();//software resets the motor controller		
		void motorControllerPowerOnCalibration(BufferSelect *);//calibrates the motor controller upon start up by exercising the full range of the channels. Will only work when Rover is in Auto Mode
		void motorControllerSetPins(byte, byte);//(steering pin, throttle pin) sets the pinouts for the steering and throttle channels
		//Note: The int type has to be used since the calibration values may be positive or negative
		void motorControllerSetSteering(int);//sets the current steering (ideal steering amount), automatically includes the motorControllerSteeringCalibrationOffset in its calculations so you can just give it ideal numbers (180 max right, 90 center,  0 max left)
		void motorControllerSetThrottle(int);//sets the current throttle (ideal throttle amount), automatically includes the motorControllerThrottleCalibrationOffset in its calculations so you can just give it ideal numbers (180 max reverse, 90 stop, 0 max forward)
		int motorControllerGetSteeringSet();//returns the amount of steering
		int motorControllerGetThrottleSet();//returns the amount of throttle			
		//Note: On initial power up the calibration values will be set to the MC_CENTER_POSITION_AFTER_POR and MC_NO_THROTTLE_AFTER_POR values as defined in RoverConfig.h
		//Send the amount with motorControllerGetSteeringSet() until the Rover is stop, then use motorControllerCalibrationSetAsCenter()
		void motorControllerCalibrationSetAsCenter();//set the current steering as the center amount		
		//Send the amount with motorControllerGetThrottleSet() until the Rover is stop, then use motorControllerCalibrationSetAsStop()
		void motorControllerCalibrationSetAsStop();//set the current throttle as the stop amount		
		
		void motorControllerCalibrateSteering(int);// (steering amount to get the center position, ideal is 90)
		void motorControllerCalibrateThrottle(int);// (throttle amount to get the stop position, ideal is 90)
		int motorControllerBoundToServoLimits(int);//bounds the amount (steering or calibration) to the limits of the servo
	
		//Non-SW Resettable			
		byte motorControllerSteeringPin;
		byte motorControllerThrottlePin;
		Servo motorControllerSteeringControl;
		Servo motorControllerThrottleControl;	
			
		//SW Resettable
		//Calibration values are between 0 and 180 where 90 is the center/middle/stop.
		int motorControllerSteeringCalibrationOffset;
		int motorControllerThrottleCalibrationOffset;
		int motorControllerSteeringAmount;
		int motorControllerThrottleAmount;	

	#endif 