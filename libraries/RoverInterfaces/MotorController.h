//MotorController.h
#ifndef _MOTORCONTROLLER_H
#define _MOTORCONTROLLER_H

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

	#define _MOTORCONTROLLER_DEFINITIONS
	
	/********************************************************************/

	#include <RoverConfig.h>
	
	class MotorController : public virtual RoverReset {
	public:
		//Note: On initial power up the calibration values will be set to the MC_CENTER_POSITION_AFTER_POR and MC_NO_THROTTLE_AFTER_POR values as defined in RoverConfig.h
		MotorController(byte, byte);//constructor (steering pin, throttle pin)
		~MotorController();//destructor
		//Note: By design, the reset will clear any current calibration values and go back to the 	MC_CENTER_POSITION_AFTER_POR and MC_NO_THROTTLE_AFTER_POR values as defined in RoverConfig.h
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)		
		//Note: The int type has to be used since the calibration values may be positive or negative
		void setSteering(int);//sets the current steering (steering amount)
		void setThrottle(int);//sets the current throttle (throttle amount)
		int getSteeringSet();//returns the amount of steering
		int getThrottleSet();//returns the amount of throttle
		//Send the amount with setSteering() until the Rover is stop, then use calibrationSetAsCenter()
		void calibrationSetAsCenter();//set the current steering as the center amount		
		//Send the amount with setThrottle() until the Rover is stop, then use calibrationSetAsStop()
		void calibrationSetAsStop();//set the current throttle as the stop amount		
	private:
		//Non-SW Resettable
			void calibrateSteering(int);// (steering amount to get the center position, ideal is 90)
			void calibrateThrottle(int);// (throttle amount to get the stop position, ideal is 90)
			int boundToServoLimits(int);//bounds the amount (steering or calibration) to the limits of the servo
			byte _steeringPin;
			byte _throttlePin;
			//Calibration values are between 0 and 180 where 90 is center/stop.
			int _steeringCalibrationOffset;
			int _throttleCalibrationOffset;		
			Servo * _steeringControl;
			Servo * _throttleControl;	
	
		//SW Resettable
		int _steeringAmount;
		int _throttleAmount;
	};

	#endif 