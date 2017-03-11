//RoverCaptain.h
#ifndef _ROVERCAPTAIN_H
#define _ROVERCAPTAIN_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>

//Uncomment to debug
#define _DEBUG_PRINT_STATE_
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast



/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/
//define Arduino 3: MAIN in order to use it's config pins
#ifndef _ARD_3_MAIN_H
	#define _ARD_3_MAIN_H
#endif



/********************************************************************/

#include <RoverConfig.h>


//Includes for Object Headers
#include <RoverHwReset.h>
#include <MotorPowerControl.h>
#include <WheelEncoderSensor.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>
#include <RoverData.h>
#include <RoverComm.h> //calls RoverConfig.h
#include <RoverCommand.h>
#include <RoverCommandCreator.h>
#include <RoverSleeperServer.h>
#include <RoverSleeperClient.h>



typedef void (*voidFuncPtr)(void);//defining the type voidFuncPtr that is a function pointer that takes no arguments and returns void. It is used later on for the interrupt service routine.

class RoverCaptain : public virtual RoverReset {
public:
	RoverCaptain(voidFuncPtr, voidFuncPtr, voidFuncPtr);//constructor (interrupt function pointer for the Rover Sleeper Server, Left Wheel Encoder, and Right Wheel Encoder)
	~RoverCaptain();//destructor	
	void run();
	void isrUpdate_sleeperMAIN();
	void isrUpdate_wheelEncoder_MidLeft();
	void isrUpdate_wheelEncoder_MidRight();
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:
//Non-SW Resettable
	static const byte _numOfObjects = 21;
	voidFuncPtr _interruptDispatch_sleeperMAIN;
	voidFuncPtr _interruptDispatch_wheelEncoder_MidLeft;
	voidFuncPtr _interruptDispatch_wheelEncoder_MidRight;
	void createObjects();
	void initializeObjects();	
	void runBackgroundTasks();
	
	enum class State {
		POWER_ON_RESET,
		INITIALIZE,
		RX_COMMUNICATIONS,
		PROCESS_COMMANDS,
		READ_INPUTS,
		CONTROL_OUTPUTS,
		TX_COMMUNICATIONS,
		GO_TO_SLEEP,
		WAKEUP,
		SW_RESET,
		HW_RESET_COMM,		
		HOLD,
		SHUTDOWN,		
		ERROR
	};
	//Enum State
	State _state;
	
//SW Resettable	

//Object Pointers
	
	//HW Resetter
	RoverHwReset * _commHwResetter;
	
	//Motor Power Control
	MotorPowerControl * _mtrPowerCtrlr;
	
	//Wheel Encoder
	DelayCounter * _midLeftSyncCounter;
	GlobalDelayTimer * _midLeftSyncTimer;
	DelayCounter * _midRightSyncCounter;
	GlobalDelayTimer * _midRightSyncTimer;
	WheelEncoderSensor * _wheelEncoder_MidLeft;
	WheelEncoderSensor * _wheelEncoder_MidRight;

	//RoverData and RoverComm
	//Communication between PC USB and MAIN
	RoverData * _roverData_PC_MAIN;
	RoverComm * _roverComm_PC_MAIN;
	//Communication between COMM and MAIN
	RoverData * _roverData_COMM_MAIN;
	RoverComm * _roverComm_COMM_MAIN;
	//Communication between NAVI and MAIN
	RoverData * _roverData_NAVI_MAIN;
	RoverComm * _roverComm_NAVI_MAIN;
	//Communication is between AUXI and MAIN
	RoverData * _roverData_AUXI_MAIN;
	RoverComm * _roverComm_AUXI_MAIN;

	//Command Parser
	RoverCommand * _roverCommand;

	//Command Creator
	RoverCommandCreator * _roverCommandCreator;
	
	//Rover Sleeper Server	
	RoverSleeperServer * _sleeperMAIN;
	
	//Rover Sleeper Client
	RoverSleeperClient * _sleeperAUXI;
	RoverSleeperClient * _sleeperNAVI;


	
	RoverReset * resetArray[_numOfObjects] = {		
		//HW Resetter
		_commHwResetter,
		//Motor Power Control
		_mtrPowerCtrlr,
		//Wheel Encoder
		_midLeftSyncCounter,
		_midLeftSyncTimer,
		_midRightSyncCounter,
		_midRightSyncTimer,
		_wheelEncoder_MidLeft,
		_wheelEncoder_MidRight,		
		//RoverData and RoverComm
		_roverData_PC_MAIN,
		_roverComm_PC_MAIN,
		_roverData_COMM_MAIN,
		_roverComm_COMM_MAIN,
		_roverData_NAVI_MAIN,
		_roverComm_NAVI_MAIN,
		_roverData_AUXI_MAIN,
		_roverComm_AUXI_MAIN,			
		//Command Parser
		_roverCommand,
		//Command Creator
		_roverCommandCreator,
		//Rover Sleeper Server	
		_sleeperMAIN,
		//Rover Sleeper Client
		_sleeperAUXI,
		_sleeperNAVI
	};
		
	
};

#endif 