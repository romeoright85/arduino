//AnalogMuxSensor.h
#ifndef _ANALOGMUXSENSOR_H
#define _ANALOGMUXSENSOR_H
	
	#include <Arduino.h>
	#include <RoverDebug.h>	
	#include <RoverReset.h>
	#include <RoverAdc.h>
	#include <RoverVcc.h>
	
	//turn on the flag for AMUX Channels (defined in RoverConfig.h)
	#define _ROVERAMUXCHANNELS
	

	
	/*******************************************************************
	Configure (define) flags before calling #include <RoverConfig.h>
	/********************************************************************/

	//define Arduino 2: AUXI in order to use it's config pins
	#ifndef _ARD_2_AUXI_H
		#define _ARD_2_AUXI_H
	#endif

	/********************************************************************/
	#include <RoverConfig.h>


	class AnalogMuxSensor : public virtual RoverReset, public RoverVcc {
		public:
			AnalogMuxSensor(byte, byte, byte, byte, byte []);//constructor (sel 0 pin, sel 1 pin, sel 2 pin, opamp out pin, array of analogNames)
			~AnalogMuxSensor();//destructor
			virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
			unsigned int getRawADCValueOf(byte);//returns the raw analog value by Analog Signal Name (Analog Signal Name)
			double getVoltageValueOf(byte);//returns the voltage value (in Volts, with a range of 0-5V) by Analog Signal Name (Analog Signal Name)
			boolean hasAnalogName(byte);//returns true if it has the desired Analog Signal Name(Analog Signal Name)

		//private:
			//SW Resetted
			byte _AMUX_SEL_0_PIN;
			byte _AMUX_SEL_1_PIN;
			byte _AMUX_SEL_2_PIN;
			//Not SW Resetted
			byte _opAmpOutputPin;
			byte _analogNames[8];//holds the analog names corresponding to the 8 channels
			unsigned int readRawADCValueOfAmuxChannel(byte);//(AMUX Channel 0 through 8)
			double readVoltageValueOfAmuxChannel(byte);//(AMUX Channel 0 through 8), returns a value of 0V to 5V. Note: If a resistor divider is used, it will have to be further processed in another function. This is just the reading of the ADC pin.
			void selectMuxChannel(byte);//sends the select signals to the AMUX to route the designed channel
			//RoverAdc  Object
			RoverAdc * _roverAdc;//used to get various types of analog readings
			
		
			
	};




#endif 