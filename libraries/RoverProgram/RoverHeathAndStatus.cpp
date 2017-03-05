#include <RoverHeathAndStatus.h>

#ifdef _DEBUG_COMM_BROADCAST
	#define SERIAL_DEBUG_CHANNEL Serial2
#else
	#define SERIAL_DEBUG_CHANNEL Serial
#endif




RoverHeathAndStatus::RoverHeathAndStatus(voidFuncPtr interruptDispatch_sleeperAUXI)
{
	this->_interruptDispatch_sleeperAUXI = interruptDispatch_sleeperAUXI;
	this->_state = State::POWER_ON_RESET;
	
}
RoverHeathAndStatus::~RoverHeathAndStatus()
{
	//do nothing
}
void RoverHeathAndStatus::reset()
{
	
	//resetting all objects
	for (byte i = 0; i < sizeof(this->resetArray) / sizeof(this->resetArray[0]); i++)
	{
		this->resetArray[i]->reset();		
	}//end for

}
void RoverHeathAndStatus::isrUpdate_sleeperAUXI()
{
	this->_sleeperAUXI->isrUpdate();
}
void RoverHeathAndStatus::initializeObjects()
{		
	//Turn off lasers
	this->_leftSidelaser->laserEnable(LASER_OFF);
	this->_rightSidelaser->laserEnable(LASER_OFF);
}
void RoverHeathAndStatus::createObjects()
{
		//Laser Control
		this->_leftSidelaser = new LaserControl(LEFT_LASER_CTRL_PIN);
		this->_rightSidelaser = new LaserControl(RIGHT_LASER_CTRL_PIN);
		
		//Current Sensor Fault
		this->_currentSensorFault = new CurrentSensorFault(CURRENT_FAULT_1_7D2V_25A_PRESW_PIN, CURRENT_FAULT_2_3D3V_12D4A_SW_PIN, CURRENT_FAULT_3_MCTRLRCH1_12D5A_PIN, CURRENT_FAULT_4_MCTRLRCH2_12D5A_PIN, CURRENT_FAULT_5_7D2_12D5A_SW_PIN, CURRENT_SENSOR_RESET_PIN);
				
		//RoverData and RoverComm
		this->_roverData_PC_AUXI = new RoverData();
		this->_roverComm_PC_AUXI = new RoverComm(_roverData_PC_AUXI);
		this->_roverData_MAIN_AUXI = new RoverData();
		this->_roverComm_MAIN_AUXI = new RoverComm(_roverData_MAIN_AUXI);

		//Command Parser
		this->_roverCommand = new RoverCommand();

		//Command Creator
		this->_roverCommandCreator = new RoverCommandCreator();

		//RoverAnalogSignals
		//Note the timers aren't very accurate due to delay caused by the loop() code, such as Serial.println(). But good enough for parallel processing.
		this->_counterGasCal = new DelayCounter(DELAY_1_PERIODS);//initialize it to count to 1 periods
		this->_timerGasCal = new GlobalDelayTimer(DELAY_TIMER_RES_1ms, this->_counterGasCal);//set each period to be 5ms long (delay interval)
		this->_counterGasRead = new DelayCounter(DELAY_1_PERIODS);//initialize it to count to 1 periods
		this->_timerGasRead = new GlobalDelayTimer(DELAY_TIMER_RES_1ms, this->_counterGasRead);//set each period to be 5ms long (delay interval)
		this->_roverUptime = new UpTime();
		this->_mqGasSensor = new MqGasSensor(GAS_SENSOR_TYPE_MQ2, GAS_BEACONCCA_RIGHTPOINTING, RESISTOR_GAS_BEACONCCA_RIGHTPOINTING);
		this->_analogSignals = new RoverAnalogSignals();
		
		//IR Distance Sensor
		this->_irDistanceForwardCenter = new  IrDistanceSensor(FORWARD_CENTER_IR_DIST_SENSOR_PIN);
		this->_irDistanceSideRight = new  IrDistanceSensor(SIDE_RIGHT_IR_DIST_SENSOR_PIN);
		this->_irDistanceRearCenter = new  IrDistanceSensor(REAR_CENTER_IR_DIST_SENSOR_PIN);
		this->_irDistanceSideLeft = new IrDistanceSensor(SIDE_LEFT_IR_DIST_SENSOR_PIN);
		
		//Rover Sleeper Server
		this->_sleeperAUXI = new RoverSleeperServer(AUXI_WAKEUP_CTRL_PIN, this->_interruptDispatch_sleeperAUXI);//AUXI Wakeup Pin Control
}

	
	
void RoverHeathAndStatus::run()
{

	switch(this->_state)
	{
		case State::ERROR:
		#ifdef _DEBUG_PRINT_STATE_
			SERIAL_DEBUG_CHANNEL.println(F("ERROR"));//DEBUG
		#endif
			//Shut off any movement to the rover
			//Transmit error message
			//Look for direction on what needs to be done
			//Else stay in error state
			this->_state = State::ERROR;
			break;	
		case State::POWER_ON_RESET:
		#ifdef _DEBUG_PRINT_STATE_			
			SERIAL_DEBUG_CHANNEL.println(F("POWER_ON_RESET"));//DEBUG					
		#endif
			//Create Objects On Power On
			this->createObjects();
			this->reset();		
			
			//Set next state
			this->_state = State::INITIALIZE;
			break;				
		case State::INITIALIZE:
		#ifdef _DEBUG_PRINT_STATE_			
			SERIAL_DEBUG_CHANNEL.println(F("INITIALIZE"));//DEBUG			
		#endif			
			//Initialize Objects
			this->initializeObjects();			
			//Set next state
			//this->_state = State::RX_COMMUNICATIONS;
			this->_state = State::GO_TO_SLEEP;//DEBUG
			break;					
		case State::RX_COMMUNICATIONS:
		#ifdef _DEBUG_PRINT_STATE_			
			SERIAL_DEBUG_CHANNEL.println(F("RX_COMMUNICATIONS"));//DEBUG			
		#endif
			this->_state = State::PROCESS_COMMANDS;
			break;			
		case State::PROCESS_COMMANDS:
		#ifdef _DEBUG_PRINT_STATE_			
			SERIAL_DEBUG_CHANNEL.println(F("PROCESS_COMMANDS"));//DEBUG			
		#endif
			this->_state = State::GET_INPUTS;
			break;		
		case State::GET_INPUTS:
		#ifdef _DEBUG_PRINT_STATE_
			SERIAL_DEBUG_CHANNEL.println(F("GET_INPUTS"));//DEBUG			
		#endif
			this->_state = State::CONTROL_OUTPUTS;
			break;		
		case State::CONTROL_OUTPUTS:
		#ifdef _DEBUG_PRINT_STATE_			
			SERIAL_DEBUG_CHANNEL.println(F("CONTROL_OUTPUTS"));//DEBUG			
		#endif			
			this->_state = State::TX_COMMUNICATIONS;
			break;		
		case State::TX_COMMUNICATIONS:
		#ifdef _DEBUG_PRINT_STATE_			
			SERIAL_DEBUG_CHANNEL.println(F("TX_COMMUNICATIONS"));//DEBUG			
		#endif
			this->_state = State::RX_COMMUNICATIONS;
			break;		
		case State::GO_TO_SLEEP:
		#ifdef _DEBUG_PRINT_STATE_			
			SERIAL_DEBUG_CHANNEL.println(F("GO_TO_SLEEP"));//DEBUG
		#endif
			delay(100);//add some delay to allow the serial print to finish before going to sleep
			//Go to sleep
			//Note: Make sure to end any Software Serial here
			 //No SW Serials used for AUXI
			this->_sleeperAUXI->goToSleep();//will sleep and can be awoken by MAIN
			//The AUXI will go to sleep here.
			this->_state = State::WAKEUP;
			break;		
		case State::WAKEUP:
			//Wake Up
			this->_sleeperAUXI->hasAwoken();
			//Note: Make sure to begin (again) any Software Serial here
			//No SW Serials used for AUXI
			//Post Wake Up tasks
			delay(100);// let everybody get up and running for a sec			
			#ifdef _DEBUG_PRINT_STATE_			
				SERIAL_DEBUG_CHANNEL.println(F("WAKEUP"));//DEBUG
			#endif
			this->_state = State::RX_COMMUNICATIONS;
			break;			
		case State::SHUTDOWN:
		#ifdef _DEBUG_PRINT_STATE_
			SERIAL_DEBUG_CHANNEL.println(F("SHUTDOWN"));//DEBUG
		#endif
			this->_state = State::POWER_ON_RESET;
			break;		
		default:
			this->_state = State::ERROR;
			break;		
	}//end switch
}
