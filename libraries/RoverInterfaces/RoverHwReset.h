//RoverHwReset.h
#ifndef _ROVERHWRESET_H
#define _ROVERHWRESET_H

	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>
	
	
	//Note: Since all the Arduinos use this class, you have to define them (i.e. #define _ARD_2_AUXI_H, #define _ARD_1_NAVI_H, #define _ARD_3_MAIN_H, or #define _ARD_4_COMM_H) in each of its .ino as there are shared naming conventions and will cause a conflict otherwise.
	
	//Arduino HW Resets are active low
	//UNO:
	//http://arduino.cc/en/uploads/Main/Arduino_Uno_Rev3-schematic.pdf
	//MEGA:
    //http://arduino.cc/en/uploads/Main/arduino-mega2560_R3-sch.pdf
  
  

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