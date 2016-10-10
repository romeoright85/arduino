//BufferSelect.h
#ifndef _BUFFERSELECT_H
#define _BUFFERSELECT_H

	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>

	#define _BUFFERSELECT_MODES	
	
	
	//When the buffer select pin is low, it's in manual mode. When it's high, it's in auto mode.


	/*******************************************************************
	Configure (define) flags before calling #include <RoverConfig.h>
	/********************************************************************/
	//define Arduino 1: NAVI in order to use it's config pins
	#ifndef _ARD_1_NAVI_H
		#define _ARD_1_NAVI_H
	#endif

	/********************************************************************/

	#include <RoverConfig.h>
	
	class BufferSelect : public virtual RoverReset {
	public:
		BufferSelect(byte);//constructor (buffer select pin)
		~BufferSelect();//destructor
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		void driverMode(byte);//use constants AUTO_DRIVE and MANUAL_DRIVE for arguments
		boolean inAutoMode();//returns true if it's in auto mode (driven by the MCU), else if it's driven by the RC Remote controller, it's in manual mode
	private:
		//Non SW Resettable
		byte _bufferSelectPin;
		//SW Resettable
		boolean _isInAutoMode;
	};

	#endif 