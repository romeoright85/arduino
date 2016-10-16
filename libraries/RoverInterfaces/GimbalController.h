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
		
	
	
	class GimbalController : public virtual RoverReset {
	public:
		GimbalController(byte,byte);//constructor (pan pin, tilt pin)
		~GimbalController();//destructor
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		
		void setPan(int);//sets the current pan (pan amount)
		void setTilt(int);//sets the current throttle (throttle amount)
		int getPanSet();//returns the amount of pan
		int getTiltSet();//returns the amount of tilt
		//Send the amount with setPan() until the Rover is center, then use calibrationSetAsCenter()
		void calibrationSetAsCenter();//set the current pan as the center amount		
		//Send the amount with setTilt() until the Rover is middle, then use calibrationSetAsMiddle()
		void calibrationSetAsMiddle();//set the current tilt as the middle amount		
		
	private:
		//Non-SW Resettable
			void calibratePan(int);// (steering amount to get the center position, ideal is 90)
			void calibrateTilt(int);// (throttle amount to get the stop position, ideal is 90)
			int boundToServoLimits(int);//bounds the amount (steering or calibration) to the limits of the servo
			byte _panPin;
			byte _tiltPin;
			//Calibration values are between 0 and 180 where 90 is center/stop.
			int _panCalibrationOffset;
			int _tiltCalibrationOffset;		
			Servo * _panControl;
			Servo * _tiltControl;	
	
		//SW Resettable
		int _panAmount;
		int _tiltAmount;
	};

	#endif 
	
	
	
	