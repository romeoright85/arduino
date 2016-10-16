//MotorPowerControl.h
#ifndef _MOTORPOWERCONTROL_H
#define _MOTORPOWERCONTROL_H

	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>
	
	//To turn on the motor, send a HIGH, else to turn off, send a low. (i.e. it's active high)
	
	/*******************************************************************
	Configure (define) flags before calling #include <RoverConfig.h>
	/********************************************************************/


	//define Arduino 3: MAIN in order to use it's config pins
	#ifndef _ARD_3_MAIN_H
		#define _ARD_3_MAIN_H
	#endif
	

	/********************************************************************/
	#define _MOTORPOWERCONTROL
	
	#include <RoverConfig.h>
	
	class MotorPowerControl : public virtual RoverReset {
	public:
		MotorPowerControl(byte, byte);//constructor (motor fet control output pin, motor enable status input pin)
		~MotorPowerControl();//destructor
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		void setMotorPower(byte);//use constants MTR_ON and MTR_OFF for arguments
		boolean motorIsOn();//true if motor is on, else false if motor is off
		
	private:
		//Non SW Resettable
		byte _motorMosfetPin;
		byte _motorEnableStatusPin;		
	};

	#endif 