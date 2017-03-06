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


//Includes for Object Headers
#include <CurrentSensorFault.h>
#include <RoverAnalogSignals.h> //calls MqGasSensor.h
#include <UpTime.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>
#include <IrDistanceSensor.h>
#include <StopWatch.h>
#include <LaserControl.h>
#include <RoverData.h>
#include <RoverComm.h> //calls RoverConfig.h
#include <RoverCommand.h>
#include <RoverCommandCreator.h>
#include <RoverSleeperServer.h>





typedef void (*voidFuncPtr)(void);//defining the type voidFuncPtr that is a function pointer that takes no arguments and returns void. It is used later on for the interrupt service routine.

class RoverHeathAndStatus : public virtual RoverReset {
public:
	RoverHeathAndStatus(voidFuncPtr);//constructor (interrupt function pointer for the Rover Sleeper Server)
	~RoverHeathAndStatus();//destructor
	void run();
	void isrUpdate_sleeperAUXI();
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:

//Non-SW Resettable
	static const byte _numOfObjects = 26;
	voidFuncPtr _interruptDispatch_sleeperAUXI;
	void createObjects();
	void initializeObjects();	
	void runBackgroundTasks();
	
	enum class State {
		POWER_ON_RESET,
		INITIALIZE,
		RX_COMMUNICATIONS,
		PROCESS_COMMANDS,
		GET_INPUTS,
		CONTROL_OUTPUTS,
		TX_COMMUNICATIONS,
		GO_TO_SLEEP,
		WAKEUP,
		SW_RESET,
		SHUTDOWN,
		ERROR
	};
	//Enum State
	State _state;
		
//SW Resettable	

//Object Pointers
	
	
	//Current Sensor
	CurrentSensorFault * _currentSensorFault;	
	
	//Rover Analog Signals
	//Note the timers aren't very accurate due to delay caused by the loop() code, such as Serial.println(). But good enough for parallel processing.
	DelayCounter * _counterGasCal;
	GlobalDelayTimer * _timerGasCal;
	DelayCounter * _counterGasRead;
	GlobalDelayTimer * _timerGasRead;
	UpTime * _roverUptime;
	MqGasSensor * _mqGasSensor;
	RoverAnalogSignals * _analogSignals;
		
	//IR Distance Sensors
	IrDistanceSensor * _irDistanceForwardCenter;
	IrDistanceSensor * _irDistanceSideRight;
	IrDistanceSensor * _irDistanceRearCenter;
	IrDistanceSensor * _irDistanceSideLeft;
		
	//IMU Sensor
	DelayCounter * _counter50Hz;
	DelayCounter * _counter10Hz;
	GlobalDelayTimer * _timer50Hz;
	GlobalDelayTimer * _timer10Hz;
	StopWatch * _stopWatch;
	
	//Laser Control
	LaserControl * _leftSidelaser;
	LaserControl * _rightSidelaser;
	
	//RoverData and RoverComm
	//Communication between PC USB and AUXI
	RoverData * _roverData_PC_AUXI;
	RoverComm * _roverComm_PC_AUXI;
	//Communication between MAIN and AUXI
	RoverData * _roverData_MAIN_AUXI;
	RoverComm * _roverComm_MAIN_AUXI;

	//Command Parser
	RoverCommand * _roverCommand;

	//Command Creator
	RoverCommandCreator * _roverCommandCreator;
	
	//Rover Sleeper Server	
	RoverSleeperServer * _sleeperAUXI;//Controls the self wakeup of AUXI
	


	
	RoverReset * resetArray[_numOfObjects] = {				
		//Current Sensor
		_currentSensorFault,
		//Rover Analog Signals
		_counterGasCal,
		_timerGasCal,
		_counterGasRead,
		_timerGasRead,
		_roverUptime,
		_mqGasSensor,
		_analogSignals,
		//IR Distance Sensors
		_irDistanceForwardCenter,
		_irDistanceSideRight,
		_irDistanceRearCenter,
		_irDistanceSideLeft,
		//IMU Sensor
		_counter50Hz,
		_counter10Hz,
		_timer50Hz,
		_timer10Hz,
		_stopWatch,
		//Laser Control
		_leftSidelaser,
		_rightSidelaser,
		//RoverData and RoverComm		
		_roverData_PC_AUXI,
		_roverComm_PC_AUXI,
		_roverData_MAIN_AUXI,
		_roverComm_MAIN_AUXI,
		//Command Parser
		_roverCommand,
		//Command Creator
		_roverCommandCreator,
		//Rover Sleeper Server
		_sleeperAUXI
		
		
	};

	
	
	
	
};

#endif 


		