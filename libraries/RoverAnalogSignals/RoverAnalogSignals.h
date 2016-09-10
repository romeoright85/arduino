//RoverAnalogSignals.h
#ifndef _ROVERANALOGSIGNALS_H
#define _ROVERANALOGSIGNALS_H

	#include <Arduino.h>
	#include <RoverDebug.h>	
	#include <RoverReset.h>
	#include <AnalogMuxSensor.h>
	
	
	//turn on the analog names in RoverConfig.h
	#define _ROVERANALOGNAMES
	#include <RoverConfig.h>

	
	
	/*******************************************************************
	Configure (define) flags before calling #include <RoverConfig.h>
	/********************************************************************/
	//define Arduino 2: AUXI in order to use it's config pins
	#ifndef _ARD_2_AUXI_H
		#define _ARD_2_AUXI_H
	#endif
	
	/********************************************************************/

	#include <RoverConfig.h>
	
	class RoverAnalogSignals : public virtual RoverReset {
	public:
		RoverAnalogSignals();//constructor
		~RoverAnalogSignals();//destructor
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		int getRawAnalogValueOf(byte);//returns the raw analog value by Analog Signal Name (Analog Signal Name)
	private:
		AnalogMuxSensor * _amux1;
		AnalogMuxSensor * _amux2;
		AnalogMuxSensor * _amux3;
		AnalogMuxSensor * _amux4;
		AnalogMuxSensor * _amux5;
		AnalogMuxSensor * _amux6;
		AnalogMuxSensor * _amux7;
		AnalogMuxSensor * _amux8;
		AnalogMuxSensor * _muxArray[8];//holds pointers to AnalogMuxSensor
		//The array below are used to store the cross reference between which analog mux has which analog signal (name)
		byte _amux1AnalogNames[8];
		byte _amux2AnalogNames[8];
		byte _amux3AnalogNames[8];
		byte _amux4AnalogNames[8];
		byte _amux5AnalogNames[8];
		byte _amux6AnalogNames[8];
		byte _amux7AnalogNames[8];
		byte _amux8AnalogNames[8];
		
		AnalogMuxSensor * findMuxBySignalName(byte);//returns the first mux in the _muxArray with the analog signal name (using a for loop). The intention is not to use the same name twice, else you'd only get the first mux that has it. (analog signal name)
		
	};

	#endif 