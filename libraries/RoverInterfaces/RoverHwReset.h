//RoverHwReset.h
#ifndef _ROVERHWRESET_H
#define _ROVERHWRESET_H

	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>
	
	
	//Arduino HW Resets are active low
	//UNO:
	//http://arduino.cc/en/uploads/Main/Arduino_Uno_Rev3-schematic.pdf
	//MEGA:
    //http://arduino.cc/en/uploads/Main/arduino-mega2560_R3-sch.pdf
  
  
  
	/*******************************************************************
	Configure (define) flags before calling #include <RoverConfig.h>
	/********************************************************************/

	//define Arduino 3: MAIN in order to use it's config pins
	#ifndef _ARD_3_MAIN_H
		#define _ARD_3_MAIN_H
	#endif
	
	//define Arduino 4: COMM in order to use it's config pins
	#ifndef _ARD_4_COMM_H
		#define _ARD_4_COMM_H		
	#endif
	
	/********************************************************************/

	#include <RoverConfig.h>
	
	class RoverHwReset : public virtual RoverReset {
	public:
	
		//Note: For Arduino the HW Reset pin is active low		
		RoverHwReset(byte);//constructor (hardware reset pin)	
		~RoverHwReset();//destructor
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		void performHwReset();//does a hardware reset
	private:
		//Non-SW Resettable
		byte _hwResetPin;
		
		//SW Resettable
		
	};

	#endif 