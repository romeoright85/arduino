//LaserControl.h
#ifndef _TEMPLATE_H
#define _TEMPLATE_H

	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>
	
	//The laser is active high. So when high, the laser is on.
	
	
	#define _LASERCONTROL_MODES
	
	/*******************************************************************
	Configure (define) flags before calling #include <RoverConfig.h>
	/********************************************************************/


	//define Arduino 2: AUXI in order to use it's config pins
	#ifndef _ARD_2_AUXI_H
		#define _ARD_2_AUXI_H
	#endif

	
	/********************************************************************/

	#include <RoverConfig.h>
	
	class LaserControl : public virtual RoverReset {
	public:
		LaserControl(byte);//constructor (laser output pin)
		~LaserControl();//destructor
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		
		void laserEnable(byte);//use constants LASER_ON and LASER_OFF for arguments
		boolean isLaserOn();//returns true if the laser is on, else false if laser is off
		
	private:
		//Non-SW Resettable
		byte _laserControlPin;
		
		//SW Resettable
		boolean _isLaserOn;
	};
	
	
	

	
	
	
	
	

	#endif 