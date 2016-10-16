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

	
	/********************************************************************/

	#include <RoverConfig.h>
	
	class GimbalController : public virtual RoverReset {
	public:
		GimbalController(byte,byte);//constructor (pan pin, tilt pin)
		~GimbalController();//destructor
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	private:
		//Non-SW Resettable
		byte _panPin;
		byte _tiltPin;
		//SW Resettable
	};

	#endif 