//RoverHeathAndStatus.h
#ifndef _ROVERHEATHANDSTATUS_H
#define _ROVERHEATHANDSTATUS_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>


//Uncomment to debug
#define _DEBUG_PRINT_STATE_
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast









/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/

//define Arduino 2: AUXI in order to use it's config pins
#ifndef _ARD_2_AUXI_H
	#define _ARD_2_AUXI_H
#endif

/********************************************************************/

#include <RoverConfig.h>


#include <LaserControl.h>
#include <CurrentSensorFault.h>
#include <RoverData.h>
#include <RoverComm.h> //calls RoverConfig.h
#include <RoverCommand.h>
#include <RoverCommandCreator.h>
#include <RoverAnalogSignals.h> //calls MqGasSensor.h
#include <UpTime.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>
#include <IrDistanceSensor.h>
#include <RoverSleeperServer.h>



typedef void (*voidFuncPtr)(void);//defining the type voidFuncPtr that is a function pointer that takes no arguments and returns void. It is used later on for the interrupt service routine.

class RoverHeathAndStatus : public virtual RoverReset {
public:
	RoverHeathAndStatus(voidFuncPtr);//constructor
	~RoverHeathAndStatus();//destructor
	void run();
	void isrUpdate_sleeperAUXI();
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:

	//Non-SW Resettable
	static const byte _numOfObjects = 20;
	void createObjects();
	void initializeObjects();
	voidFuncPtr _interruptDispatch_sleeperAUXI;
	
	enum class State {
		ERROR,
		POWER_ON_RESET,
		INITIALIZE,
		RX_COMMUNICATIONS,
		PROCESS_COMMANDS,
		GET_INPUTS,
		CONTROL_OUTPUTS,
		TX_COMMUNICATIONS,
		GO_TO_SLEEP,
		WAKEUP,
		SHUTDOWN
	};
	//Enum State
	State _state;
		
	//SW Resettable	
			
	//Laser Control
	LaserControl * _leftSidelaser;
	LaserControl * _rightSidelaser;
	//Current Sensor
	CurrentSensorFault * _currentSensorFault;	
	//RoverData and RoverComm
	//Communication between AUXI and PC USB
	RoverData * _roverData_PC_AUXI;
	RoverComm * _roverComm_PC_AUXI;
	//Communication between AUXI and MAIN
	RoverData * _roverData_MAIN_AUXI;
	RoverComm * _roverComm_MAIN_AUXI;

	//Command Parser
	RoverCommand * _roverCommand;

	//Rover Analog Signals
	//Note the timers aren't very accurate due to delay caused by the loop() code, such as Serial.println(). But good enough for parallel processing.
	DelayCounter * _counterGasCal;
	GlobalDelayTimer * _timerGasCal;
	DelayCounter * _counterGasRead;
	GlobalDelayTimer * _timerGasRead;
	UpTime * _roverUptime;
	MqGasSensor * _mqGasSensor;
	RoverAnalogSignals * _analogSignals;


	//Command Creator
	RoverCommandCreator * _roverCommandCreator;

	//IR Distance Sensors
	IrDistanceSensor * _irDistanceForwardCenter;
	IrDistanceSensor * _irDistanceSideRight;
	IrDistanceSensor * _irDistanceRearCenter;
	IrDistanceSensor * _irDistanceSideLeft;

	//Rover Sleeper Server
	
	//Controls the self wakeup of AUXI
	RoverSleeperServer * _sleeperAUXI;

	
	RoverReset * resetArray[_numOfObjects] = {				
		_leftSidelaser,
		_rightSidelaser,
		_currentSensorFault,
		_roverData_PC_AUXI,
		_roverComm_PC_AUXI,
		_roverData_MAIN_AUXI,
		_roverComm_MAIN_AUXI,
		_roverCommand,
		_counterGasCal,
		_timerGasCal,
		_counterGasRead,
		_timerGasRead,
		_roverUptime,
		_mqGasSensor,
		_analogSignals,
		_irDistanceForwardCenter,
		_irDistanceSideRight,
		_irDistanceRearCenter,
		_irDistanceSideLeft,
		_sleeperAUXI
	};

	
	
	
	
};

#endif 


		