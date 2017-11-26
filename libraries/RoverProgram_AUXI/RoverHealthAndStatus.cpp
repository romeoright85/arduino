//Used for AUXI - 2

#include <RoverHealthAndStatus.h>

//Note: Include ImuSensor.h here as it won't work right when including it in RoverHealthAndStatus.h since it's not a class but a bunch of functions and variable declarations
#include <ImuSensor.h>

#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ _MAIN_SERIAL_ //When using COMM Broadcast, reroute the PC USB output to the channel to MAIN instead
#else
	#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_
#endif


RoverHealthAndStatus::RoverHealthAndStatus(voidFuncPtr interruptDispatch_sleeperAUXI)
{
	this->_interruptDispatch_sleeperAUXI = interruptDispatch_sleeperAUXI;
	
	//Initialize the Finite State Machine
	this->_state = State::POWER_ON_RESET;	
}
RoverHealthAndStatus::~RoverHealthAndStatus()
{
	//do nothing
}
void RoverHealthAndStatus::reset()
{
	
	//resetting all objects
	for (byte i = 0; i < sizeof(this->resetArray) / sizeof(this->resetArray[0]); i++)
	{
		this->resetArray[i]->reset();		
	}//end for
}
void RoverHealthAndStatus::isrUpdate_sleeperAUXI()
{
	this->_sleeperAUXI->isrUpdate();
}
void RoverHealthAndStatus::createObjects()
{
		
		//State (Design Pattern) Machine(s)
		this->_holdStateMachine_Auxi = new HoldStateMachine_Auxi();
		
		
		//Current Sensor Fault
		this->_currentSensorFault = new CurrentSensorFault(CURRENT_FAULT_1_7D2V_25A_PRESW_PIN, CURRENT_FAULT_2_3D3V_12D5A_SW_PIN, CURRENT_FAULT_3_MCTRLRCH1_12D5A_PIN, CURRENT_FAULT_4_MCTRLRCH2_12D5A_PIN, CURRENT_FAULT_5_7D2_12D5A_SW_PIN, CURRENT_SENSOR_RESET_PIN);
				
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
		
		//IMU Sensor
		this->_counter50Hz = new DelayCounter(DELAY_4_PERIODS);//initialize it to count to 4 periods
		this->_counter10Hz = new DelayCounter(DELAY_2_PERIODS);//initialize it to count to 2 periods
		this->_timer50Hz = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, this->_counter50Hz);//set each period to be 5ms long (delay interval)
		this->_timer10Hz = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, this->_counter10Hz);//set each period to be 5ms long (delay interval)
		this->_stopWatch = new StopWatch();
	
		//Laser Control
		this->_leftSidelaser = new LaserControl(LEFT_LASER_CTRL_PIN);
		this->_rightSidelaser = new LaserControl(RIGHT_LASER_CTRL_PIN);
		
		//RoverData and RoverComm
		this->_roverData_PC_AUXI = new RoverData();
		this->_roverComm_PC_AUXI = new RoverComm(_roverData_PC_AUXI);
		this->_roverData_MAIN_AUXI = new RoverData();
		this->_roverComm_MAIN_AUXI = new RoverComm(_roverData_MAIN_AUXI);

		//Command Parser
		this->_roverCommand = new RoverCommand();

		//Command Creator
		this->_roverCommandProcessor = new RoverCommandProcessor();
	
		//Rover Sleeper Server
		this->_sleeperAUXI = new RoverSleeperServer(AUXI_WAKEUP_CTRL_PIN, this->_interruptDispatch_sleeperAUXI);//AUXI Wakeup Pin Control
	
	
}
void RoverHealthAndStatus::runBackgroundTasks()
{
	//Rover UpTime
	this->_roverUptime->run();	
	
//FINISH ME	
}

	
void RoverHealthAndStatus::run()//Finite State Machine (FSM)
{
	
	//Run Background Tasks Every Loop
	this->runBackgroundTasks();
	
	
	switch(this->_state)
	{
		case State::POWER_ON_RESET:
		#ifdef _DEBUG_PRINT_STATE_			
			SERIAL_DEBUG_CHANNEL.println(F("POWER_ON_RESET"));//DEBUG					
		#endif
			//Create Objects On Power On
			this->createObjects();				
			//Set next state
			this->_state = State::INITIALIZE;
			break;				
		case State::INITIALIZE:
		#ifdef _DEBUG_PRINT_STATE_			
			SERIAL_DEBUG_CHANNEL.println(F("INITIALIZE"));//DEBUG			
		#endif			
			//Reset/Initialize All Objects
			this->reset();				
			//Set next state
			this->_state = State::RX_COMMUNICATIONS;			
			break;					
		case State::RX_COMMUNICATIONS:
		#ifdef _DEBUG_PRINT_STATE_			
			SERIAL_DEBUG_CHANNEL.println(F("RX_COMMUNICATIONS"));//DEBUG			
		#endif		
			//Set next state
			this->_state = State::PROCESS_COMMANDS;
			break;			
		case State::PROCESS_COMMANDS:
		#ifdef _DEBUG_PRINT_STATE_			
			SERIAL_DEBUG_CHANNEL.println(F("PROCESS_COMMANDS"));//DEBUG			
		#endif
			//Set next state
			this->_state = State::READ_INPUTS;
			break;		
		case State::READ_INPUTS:
		#ifdef _DEBUG_PRINT_STATE_
			SERIAL_DEBUG_CHANNEL.println(F("READ_INPUTS"));//DEBUG			
		#endif
		
			//Check Current Sensors
			if(this->_currentSensorFault->anyFaulted())
			{
				//Set the hold state
				
//LEFT OFF HERE
//NEED TO WRITE A 	CURRENT HOLD STATE
//NEED TO PASS DATA BACK AND FORTH BETWEEN THE FSM and the SDPM
				//this->_holdStateMachine_Auxi->setNextState(this->getCurrentFaultHoldStateAuxi());
				//Set next state
				this->_state = State::HOLD;
				break;
			}
			
			
			
			
			
			
			
			
			
			
			//Set next state
			this->_state = State::CONTROL_OUTPUTS;
			break;		
		case State::CONTROL_OUTPUTS:
		#ifdef _DEBUG_PRINT_STATE_			
			SERIAL_DEBUG_CHANNEL.println(F("CONTROL_OUTPUTS"));//DEBUG			
		#endif			
			//Set next state
			this->_state = State::TX_COMMUNICATIONS;
			break;		
		case State::TX_COMMUNICATIONS:
		#ifdef _DEBUG_PRINT_STATE_			
			SERIAL_DEBUG_CHANNEL.println(F("TX_COMMUNICATIONS"));//DEBUG			
		#endif
			//Set next state
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
			//Set next state
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
			//Set next state
			this->_state = State::RX_COMMUNICATIONS;
			break;			
		case State::SW_RESET:
			//Same as INITIALIZE
			//Set next state
			this->_state = State::INITIALIZE;
			break;				
		case State::HOLD:
		#ifdef _DEBUG_PRINT_STATE_
			SERIAL_DEBUG_CHANNEL.println(F("HOLD"));//DEBUG
		#endif
			//Hold State (Design Pattern) Machine - Hold SDPM
			//Note: Only Run the Hold State (Design Pattern) Machine when in the Hold State of the Finite State Machine
			//Run the sub/child "Hold State (Design Pattern) Machine" until it requests and exit
			this->_holdStateMachine_Auxi->run();


			
			
			//Process RX/TX commands here until you get an exit status. Pass the data in and out of the Hold State Machine
//WRITE LATER

			if(this->_holdStateMachine_Auxi->exitHoldStatus())//exit the hold state
			{
			#ifdef _DEBUG_OUTPUT			
				SERIAL_DEBUG_CHANNEL.println(F("EXIT HOLD"));//DEBUG			
			#endif
				//Set next state
				this->_state = State::RX_COMMUNICATIONS;	
			}
			else//stay in the hold staye
			{
				//Set next state
				this->_state = State::HOLD;
			}

		
	//Set next state
	this->_state = State::RX_COMMUNICATIONS;	
			
			break;				
		case State::SHUTDOWN:
		#ifdef _DEBUG_PRINT_STATE_
			SERIAL_DEBUG_CHANNEL.println(F("SHUTDOWN"));//DEBUG
		#endif
			//Set next state
			this->_state = State::POWER_ON_RESET;
			break;							
		case State::ERROR:
		#ifdef _DEBUG_PRINT_STATE_
			SERIAL_DEBUG_CHANNEL.println(F("ERROR"));//DEBUG
		#endif
			//Shut off any movement to the rover
			//Transmit error message
			//Look for direction on what needs to be done
			//Else stay in error state
			//Set next state
			this->_state = State::ERROR;
			break;		
		default:
			//Set next state
			this->_state = State::ERROR;
			break;					
	}//end switch
}
