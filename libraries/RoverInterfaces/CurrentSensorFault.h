//CurrentSensorFault.h
#ifndef _CURRENTSENSORFAULT_H
#define _CURRENTSENSORFAULT_H

	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>
	
		
	
	/*******************************************************************
	Configure (define) flags before calling #include <RoverConfig.h>
	/********************************************************************/

	//define Arduino 2: AUXI in order to use it's config pins
	#ifndef _ARD_2_AUXI_H
		#define _ARD_2_AUXI_H
	#endif
	
	/********************************************************************/

	#include <RoverConfig.h>
	
	class CurrentSensorFault : public virtual RoverReset {
	public:
		//CURRENT RESET: The current reset pin is actually a transistor controller Vcc to the current sensors. You need to power cycle the current sensors to reset it.
		//The reset circuit (SW_VCC_CTRL) is active low.
		//Normally the PNP transistor's gate is pulled low, so the output (SW_VCC) is Vcc. To turn off Vcc, send it an high and it will turn off the PNP transistor.
		//Reference (i.e. P/N: ACS711): https://www.pololu.com/product/2197
		//Note: All current sensors share the same fault reset pin
		
		//CURRENT FAULT: It is active low. Overcurrent FAULT output latches low when current magnitude exceeds the specified current limit.
				
		CurrentSensorFault(byte, byte, byte, byte, byte, byte);//constructor (fault pin 1, fault pin 2, fault pin 3, fault pin 4, fault pin 4, fault reset pin)
		~CurrentSensorFault();//destructor
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		void resetCurrentSensors();//Note: do not call this function in the constructor, as the constructor may be called globally but this function uses delay()s which won't work in the global space
		void clearFaultedCurrentSensors();
		boolean * getFaultedSensors();
		boolean anyFaulted();
		
		
	private:
		//Non-SW Resettable
		byte _currentSensorFaultPins[5];
		byte _currentSensors_ResetPin;
				
		//SW Resettable
		boolean _faultedCurrentSensors[5];
	};

	#endif 