#include <RoverCaptain.h>


#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ Serial2
#else
	#define _SERIAL_DEBUG_CHANNEL_ Serial
#endif


RoverCaptain::RoverCaptain(voidFuncPtr interruptDispatch_sleeperMAIN, voidFuncPtr interruptDispatch_wheelEncoder_MidLeft, voidFuncPtr interruptDispatch_wheelEncoder_MidRight)
{
	this->_interruptDispatch_sleeperMAIN = interruptDispatch_sleeperMAIN;
	this->_interruptDispatch_wheelEncoder_MidLeft = interruptDispatch_wheelEncoder_MidLeft;
	this->_interruptDispatch_wheelEncoder_MidRight = interruptDispatch_wheelEncoder_MidRight;
	
	this->_state = State::POWER_ON_RESET;
}
RoverCaptain::~RoverCaptain()
{
	//do nothing
}
void RoverCaptain::reset()
{
	
	//resetting all objects
	for (byte i = 0; i < sizeof(this->resetArray) / sizeof(this->resetArray[0]); i++)
	{
		this->resetArray[i]->reset();
	}//end for
}
void RoverCaptain::isrUpdate_sleeperMAIN()
{
	this->_sleeperMAIN->isrUpdate();
}
void RoverCaptain::isrUpdate_wheelEncoder_MidLeft()
{
	this->_wheelEncoder_MidLeft->isrUpdate();
}
void RoverCaptain::isrUpdate_wheelEncoder_MidRight()
{
	this->_wheelEncoder_MidRight->isrUpdate();
}
void RoverCaptain::createObjects()
{
	//HW Resetter
	this->_commHwResetter = new RoverHwReset(COMM_HW_RESET_CTRL_PIN);
	
	//Motor Power Control
	this->_mtrPowerCtrlr = new MotorPowerControl(MTR_FET_CTRL_PIN, MTR_ENABLE_STATUS);
	
	//Wheel Encoder	
	//The WheelEncoder will wait for 1sec (1000 periods * 1mS) between each wheel encoder calculation
	this->_midLeftSyncCounter = new DelayCounter(DELAY_200_PERIODS);//initialize it to count to 1 periods x 1ms delay timer resolution = 1ms before the count has reached flag goes true
	this->_midLeftSyncTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, this->_midLeftSyncCounter);//everytime the delay interval (resolution) is reached, it will increment the delay counter. The standard resolution used for the Rover has been 5mS so it's not too small where it has to increment the counter often, but not to big where it won't work for many different classes without being too slow or fast
	this->_midRightSyncCounter = new DelayCounter(DELAY_200_PERIODS);//initialize it to count to 1 periods x 1ms delay timer resolution = 1ms before the count has reached flag goes true
	this->_midRightSyncTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, this->_midRightSyncCounter);//everytime the delay interval (resolution) is reached, it will increment the delay counter. The standard resolution used for the Rover has been 5mS so it's not too small where it has to increment the counter often, but not to big where it won't work for many different classes without being too slow or fast
	this->_wheelEncoder_MidLeft = new WheelEncoderSensor(ENCODER_A_MID_LEFT, ENCODER_B_MID_LEFT, LEFT_MOUNTED, this->_interruptDispatch_wheelEncoder_MidLeft, this->_midLeftSyncCounter);
	this->_wheelEncoder_MidRight = new WheelEncoderSensor(ENCODER_A_MID_RIGHT, ENCODER_B_MID_RIGHT, RIGHT_MOUNTED, this->_interruptDispatch_wheelEncoder_MidRight, this->_midRightSyncCounter);

	//RoverData and RoverComm
	//Communication between MAIN and PC USB
	this->_roverData_PC_MAIN = new RoverData();
	this->_roverComm_PC_MAIN = new RoverComm(this->_roverData_PC_MAIN);
	//Communication between MAIN and COMM
	this->_roverData_COMM_MAIN = new RoverData();
	this->_roverComm_COMM_MAIN = new RoverComm(this->_roverData_COMM_MAIN);
	//Communication between MAIN and NAVI
	this->_roverData_NAVI_MAIN = new RoverData();
	this->_roverComm_NAVI_MAIN = new RoverComm(this->_roverData_NAVI_MAIN);
	//Communication is between MAIN and AUXI
	this->_roverData_AUXI_MAIN = new RoverData();
	this->_roverComm_AUXI_MAIN = new RoverComm(this->_roverData_AUXI_MAIN);

	//Command Parser
	this->_roverCommand = new RoverCommand();
		
	//Command Creator
	this->_roverCommandCreator = new RoverCommandCreator();
	
	//Rover Sleeper Server	
	this->_sleeperMAIN = new RoverSleeperServer(MAIN_WAKEUP_CTRL_PIN, this->_interruptDispatch_sleeperMAIN);//MAIN Wakeup Pin Control
	
	//Rover Sleeper Client
	this->_sleeperAUXI = new RoverSleeperClient(AUXI_WAKEUP_CTRL_PIN);
	this->_sleeperNAVI = new RoverSleeperClient(NAVI_WAKEUP_CTRL_PIN);




}
void RoverCaptain::initializeObjects()
{		

//FINISH ME

}
void RoverCaptain::runBackgroundTasks()
{		
	//Wheel Encoders
	this->_midLeftSyncTimer->Running();
	this->_midRightSyncTimer->Running();		
	this->_wheelEncoder_MidLeft->sensorOnline();
	this->_wheelEncoder_MidRight->sensorOnline();
}
void RoverCaptain::run()
{
	//Run Background Tasks Every Loop
	this->runBackgroundTasks();

	
	switch(this->_state)
	{
		case State::POWER_ON_RESET:
		#ifdef _DEBUG_PRINT_STATE_			
			_SERIAL_DEBUG_CHANNEL_.println(F("POWER_ON_RESET"));//DEBUG					
		#endif
			//Create Objects On Power On
			this->createObjects();
			this->reset();			
			//Set next state
			this->_state = State::INITIALIZE;
			break;				
		case State::INITIALIZE:
		#ifdef _DEBUG_PRINT_STATE_			
			_SERIAL_DEBUG_CHANNEL_.println(F("INITIALIZE"));//DEBUG			
		#endif			
			//Initialize Objects
			this->initializeObjects();			
			//Set next state
			this->_state = State::RX_COMMUNICATIONS;			
			break;					
		case State::RX_COMMUNICATIONS:
		#ifdef _DEBUG_PRINT_STATE_			
			_SERIAL_DEBUG_CHANNEL_.println(F("RX_COMMUNICATIONS"));//DEBUG			
		#endif		
			this->_state = State::PROCESS_COMMANDS;
			break;			
		case State::PROCESS_COMMANDS:
		#ifdef _DEBUG_PRINT_STATE_			
			_SERIAL_DEBUG_CHANNEL_.println(F("PROCESS_COMMANDS"));//DEBUG			
		#endif
			this->_state = State::GET_INPUTS;
			break;		
		case State::GET_INPUTS:
		#ifdef _DEBUG_PRINT_STATE_
			_SERIAL_DEBUG_CHANNEL_.println(F("GET_INPUTS"));//DEBUG			
		#endif
			this->_state = State::CONTROL_OUTPUTS;
			break;		
		case State::CONTROL_OUTPUTS:
		#ifdef _DEBUG_PRINT_STATE_			
			_SERIAL_DEBUG_CHANNEL_.println(F("CONTROL_OUTPUTS"));//DEBUG			
		#endif			
			this->_state = State::TX_COMMUNICATIONS;
			break;		
		case State::TX_COMMUNICATIONS:
		#ifdef _DEBUG_PRINT_STATE_			
			_SERIAL_DEBUG_CHANNEL_.println(F("TX_COMMUNICATIONS"));//DEBUG			
		#endif
			this->_state = State::RX_COMMUNICATIONS;
			break;		
		case State::GO_TO_SLEEP:
		#ifdef _DEBUG_PRINT_STATE_			
			_SERIAL_DEBUG_CHANNEL_.println(F("GO_TO_SLEEP"));//DEBUG
		#endif
//FINISH ME			
			this->_state = State::WAKEUP;
			break;		
		case State::WAKEUP:
			//Wake Up
//FINISH ME			
			#ifdef _DEBUG_PRINT_STATE_			
				_SERIAL_DEBUG_CHANNEL_.println(F("WAKEUP"));//DEBUG
			#endif
			this->_state = State::RX_COMMUNICATIONS;
			break;		
		case State::SW_RESET:
			//Same as INITIALIZE
			this->_state = State::INITIALIZE;
			break;			
		case State::HW_RESET_COMM:
			//It will reset COMM then go back to it's normal operation
			this->_state = State::RX_COMMUNICATIONS;
			break;			
		case State::SHUTDOWN:
		#ifdef _DEBUG_PRINT_STATE_
			_SERIAL_DEBUG_CHANNEL_.println(F("SHUTDOWN"));//DEBUG
		#endif
			this->_state = State::POWER_ON_RESET;
			break;				
		case State::ERROR:
		#ifdef _DEBUG_PRINT_STATE_
			_SERIAL_DEBUG_CHANNEL_.println(F("ERROR"));//DEBUG
		#endif
			//Shut off any movement to the rover
			//Transmit error message
			//Look for direction on what needs to be done
			//Else stay in error state
			this->_state = State::ERROR;
			break;		
		default:
			this->_state = State::ERROR;
			break;					
	}//end switch	
}