//Rover_StateMachine_COMM

//DEBUG
//Can send /-c5--*hi or /-c5--*bye to test if _DEBUG_ALL_SERIALS_WITH_USB_SERIAL_ is uncommented in RoverConfig.h



//Note: To test with USB Serial for all Serial channels, go to RoverConfig and uncomment the flag _DEBUG_ALL_SERIALS_WITH_USB_SERIAL_ as long as commandEnableOption_Hi and commandEnableOption_Bye are set true in the filter in runModeFunction_SYNCHRONIZATION()

//Configuration defines for #includes (must come before the #includes)
#ifndef _ROVER_STATES_AND_MODES
	#define _ROVER_STATES_AND_MODES
#endif
#ifndef _COMMAND_CREATION_DEFINITIONS
	#define _COMMAND_CREATION_DEFINITIONS
#endif
#ifndef _ARD_4_COMM_H
	#define _ARD_4_COMM_H //Must define this before calling RoverConfig.h (either directly or through another header file), define this flag to turn on COMM definitions
#endif
	

	

//#includes
#include <RoverStatesAndModes.h>
#include <RoverCommandDefs.h>
#include <SoftwareSerial.h>
#include <RoverData.h>
#include <RoverComm.h> //calls RoverConfig.h
#include <RoverCommand.h>
#include <SoftwareSerial.h>
#include <HeartLed.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>
#include <PirSensor.h>
#include <RoverHwReset.h>
#include <RoverSleeperServer.h>
#include <RoverSleeperClient.h>
#include <RoverConfig.h>	
	
	


//============Function Prototypes
void InterruptDispatch1();//For PirSensorTest
void InterruptDispatch2();//For WakeUpTester_COMM, //DEBUG LATER, Was "InterruptDispatch1", but had a name conflict
//============End of Function Prototypes


//============Debugging: Serial Channel Selection
//Used to output debugging messages only when the _DEBUG_COMM_BROADCAST flag is defined
//Uncomment the flag below in order to output debugging messages
//#define _DEBUG_COMM_BROADCAST

//Flag Logic, no need to edit this below
//Reference the "Where Left Off...txt" at: K:\Working Directory\DESIGN_PROJ\Design Projects\Robot\Workspaces\Arduino\2nd Gen Code\GitHub\arduino\Planning
#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_ //for COMM, either way it goes to the PC USB Serial
#else
	#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_
#endif
//============End of Debugging: Serial Channel Selection


//============Debugging: Print Mode and/or State
//Uncomment the flag below in order to print the current state
//#define _DEBUG_PRINT_CURRENT_STATE
//Uncomment the flag below in order to print the current mode
//#define _DEBUG_PRINT_CURRENT_MODE


//Flag Logic, no need to edit this below
#ifdef _DEBUG_PRINT_CURRENT_STATE
	#define _PRINT_STATE_ _SERIAL_DEBUG_CHANNEL_.println
#else
	#define _PRINT_STATE_ void
#endif

#ifdef _DEBUG_PRINT_CURRENT_MODE
	#define _PRINT_MODE_ _SERIAL_DEBUG_CHANNEL_.println
#else
	#define _PRINT_MODE_ void
#endif
//============End Debugging: Print Mode and/or State










//============TEMPORARY Global Declarations (to test to see if the program can handle the memory)

//STILL NEED TO INTEGRATE THIS INTO THE FULL CODE
//ADD ANY OBJECTS TO THE RESET ARRAY
//ADD ANY SW RESETTABLE VARIABLES INTO THE initializeVariables function

//------------------From AnalogLedTester
DelayCounter heartLedCounter = DelayCounter(DELAY_10_PERIODS);//initialize it to count to 10 periods, though can pass anything here as the heart led will automatically set it to the number of short delay periods (that is also passed to it as DELAY_10_PERIODS) anyways.
HeartLed heartLed = HeartLed(HEART_LED_PIN, &heartLedCounter, DELAY_10_PERIODS, DELAY_80_PERIODS);
GlobalDelayTimer mainTimer = GlobalDelayTimer(DELAY_TIMER_RES_5ms, &heartLedCounter);
//------------------From PirSensorTest
PirSensor * pirSensor = new PirSensor(PIR_PIN, &InterruptDispatch1);//Note: This is my custom function and not attachInterrupt (though it calls it)
volatile boolean motionDetected;
//------------------From RoverHwResetTester_COMM
RoverHwReset * naviHwResetter = new RoverHwReset(NAVI_HW_RESET_CTRL_PIN);
RoverHwReset * auxiHwResetter = new RoverHwReset(AUXI_HW_RESET_CTRL_PIN);
RoverHwReset * mainHwResetter = new RoverHwReset(MAIN_HW_RESET_CTRL_PIN);
//------------------From WakeUpTester_COMM
char rxCharData;//DEBUG LATER, Was "rxData", but had a name conflict
//Controls the self wakeup of COMM
RoverSleeperServer * sleeperCOMM = new RoverSleeperServer(COMM_WAKEUP_CTRL_PIN, &InterruptDispatch2);//COMM Wakeup Pin Control
RoverSleeperClient * sleeperMAIN = new RoverSleeperClient(MAIN_WAKEUP_CTRL_PIN);



//============END OF TEMPORARY Global Declarations (to test to see if the program can handle the memory)






//============Global Declarations


//=====SW Resettable Variables (reinitialize these variables on software reset)

//Message Queues
byte cmnc_msg_queue = CMD_TAG_NO_MSG; // (command tag, not boolean since use by CREATE_DATA to generate messages as well as TX_COMMUNICATIONS as a flag)
byte main_msg_queue = CMD_TAG_NO_MSG; // (command tag, not boolean since use by CREATE_DATA to generate messages as well as TX_COMMUNICATIONS as a flag)

//Flag(s) - Error
boolean invalid_state_or_mode_error = false;
boolean sync_error = false;
boolean secure_link_error = false;
boolean sw_reset_error = false;
boolean generic_health_error = false;
boolean sleeping_error = false;
//Flag(s) - Message Controls
boolean redirectToCMNC = false;//redirect data to CMNC from any Arduino since this is a shared flag. Priority will be given to whatever is hardcoded and the other message will be dropped. (but in this case it would only be from MAIN since COMM only had one other source)
boolean redirectToMAIN = false;//redirect data to MAIN from any Arduino since this is a shared flag. Priority will be given to whatever is hardcoded and the other message will be dropped. (but in this case it would only be from CMNC since COMM only had one other source)
//Flag(s) - Status
boolean main_system_ready = false;
boolean communications_secure = false;//(used to keep track is the communications link is already secure or not, and is useful for things like when going to sleep and waking back up and needing to synchronize again without needing to resecure the link)
boolean first_transmission = true;
//Flag(s) - Data was for this local Arduino that is running this sketch (and not something it's connected to)
boolean dataWasForCOMM_Ch1;//for PC USB/CNMC
boolean dataWasForCOMM_Ch2;//for MAIN
//Flag(s) - Data Status
byte ch1Status = DATA_STATUS_NOT_READY;//for PC USB/CNMC
byte ch2Status = DATA_STATUS_NOT_READY;//for MAIN
//Flag(s) - Command Filter Options
boolean commandEnableOption_Hi = false;//DEBUG
boolean commandEnableOption_Bye = false;//DEBUG
boolean commandEnableOption_Invalid = false;//DEBUG
boolean commandEnableOption_EstablishSecureLink = false;
//Counters
unsigned int timeout_counter = 0; //shared counter, used to detect timeout of MAIN responding back to COMM for any reason (i.e. system go or system ready responses), used to track how long COMM has been waiting for a COMM SW Request back from MAIN, after it sent a ALL_SW_RESET_REQUEST to MAIN (which MAIN might have missed, since it's sent only once), etc. Make sure to clear it out before use and only use it for one purpose at a time.
unsigned int transmission_delay_cnt = 0;//concurrent transmission delay counter





//=====Non-SW Resettable Variables (do not reinitialize these variables on software reset)

//States
byte currentState = RUN_HOUSEKEEPING_TASKS;
byte nextState = RUN_HOUSEKEEPING_TASKS;
byte queuedState = RUN_HOUSEKEEPING_TASKS;

//Modes
byte currentMode = POWER_ON_AND_HW_RESET;

//Software Serial
#ifndef _DEBUG_ALL_SERIALS_WITH_USB_SERIAL_ //where this debug flag is controlled in RoverConfig.h
	SoftwareSerial _MAIN_SWSERIAL_(COMM_SW_UART_RX_PIN, COMM_SW_UART_TX_PIN);
#endif

//Rover Data and COMMs
//RoverData pointers and RoverComms
//Ch1 is between CMNC and COMM
RoverData * roverDataCh1_COMM = new RoverData();
RoverComm * roverComm_Ch1 = new RoverComm(roverDataCh1_COMM);
//Ch2 is between COMM and MAIN
RoverData * roverDataCh2_COMM = new RoverData();
RoverComm * roverComm_Ch2 = new RoverComm(roverDataCh2_COMM);
//Command Parser
RoverCommand * roverCommand = new RoverCommand();




RoverReset * resetArray[] = {
	roverDataCh1_COMM,
	roverComm_Ch1,
	roverDataCh2_COMM,
	roverComm_Ch2,
	roverCommand
};//for pointers, pass them directly, for objects pass the address


//=====End of: Non-SW Resettable Variables



//=====End of: SW Resettable Variables

//============End of Global Declarations



void setup() {


	//resetting all objects in this sketch
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		if (!resetArray[i] == NULL)//if the object isn't null
		{
			resetArray[i]->reset();//reset the object	
		}
	}


	//Serial Communications
	//Setup the HW_UART for communications between COMM and CMNC/PC USB
	_CMNC_SERIAL_.begin(CMNC_BAUD_RATE);
	//Setup the SW_UART for communications between COMM and MAIN
	_MAIN_SWSERIAL_.begin(MAIN_BAUD_RATE);

	

}//end of setup()


void loop() {
  




	//State Machine
	switch (currentState)
	{
		case RUN_HOUSEKEEPING_TASKS:
			_PRINT_STATE_(F("STATE: RUN_HOUSEKEEPING_TASKS"));

			switch (currentMode)
			{
				case POWER_ON_AND_HW_RESET:
					runModeFunction_POWER_ON_AND_HW_RESET(currentState);
					queuedState = RUN_HOUSEKEEPING_TASKS;//Set next aka queued state (since in RUN_HOUSEKEEPING_TASKS) to: RUN_HOUSEKEEPING_TASKS
					currentMode = INITIALIZATION;//Set mode to INITIALIZATION *begin*				
					break;
				case INITIALIZATION:
					runModeFunction_INITIALIZATION(currentState);
					queuedState = RX_COMMUNICATIONS;// Set next state to RX_COMMUNICATIONS
					currentMode = SYNCHRONIZATION;//Set mode to SYNCHRONIZATION *begin*
					break;
				case SYNCHRONIZATION:		
					runModeFunction_SYNCHRONIZATION(currentState);
					//Keep the queuedState the same (unchanged)
					//Keep the currentMode the same (unchanged)				
					break;
				case SECURING_LINK:		
					runModeFunction_SECURING_LINK(currentState);
					//Keep the queuedState the same (unchanged)
					//Keep the currentMode the same (unchanged)
					break;
				case NORMAL_OPERATIONS:		
					runModeFunction_NORMAL_OPERATIONS(currentState);
					//Keep the queuedState the same (unchanged)
					//Keep the currentMode the same (unchanged)
					break;
				case HW_RESETTING:		
					runModeFunction_HW_RESETTING(currentState);
					//Keep the queuedState the same (unchanged)
					//Keep the currentMode the same (unchanged)
					break;
				case SYSTEM_SLEEPING:		
					runModeFunction_SYSTEM_SLEEPING(currentState);
					//Keep the queuedState the same (unchanged)
					//Keep the currentMode the same (unchanged)
					break;
				case SYSTEM_WAKING:		
					runModeFunction_SYSTEM_WAKING(currentState);
					//Keep the queuedState the same (unchanged)
					//Keep the currentMode the same (unchanged)
					break;					
				case SW_RESETTING:		
					runModeFunction_SW_RESETTING(currentState);
					//Keep the queuedState the same (unchanged)
					//Keep the currentMode the same (unchanged)
					break;
				case SYSTEM_ERROR:		
					runModeFunction_SYSTEM_ERROR(currentState);
					//Keep the queuedState the same (unchanged)
					//Keep the currentMode the same (unchanged)
					break;												
				default: //default mode
					runModeFunction_default();//no state needed, all states do the same thing
					queuedState = CONTROL_OUTPUTS;
					currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
				break;
			}//end switch
			//Advance to the queued (saved) state
			nextState = queuedState;//Setting the Queued State as the Next State while in RUN_HOUSEKEEPING_TASKS state. And then when this state ends, outside the switch case for states, the Next State will change into the Current State.
				//This happens only when in the RUN_HOUSEKEEPING_TASKS state.
				//All other states will always go to the RUN_HOUSEKEEPING_TASKS as it's next state in order to run housekeeping tasks with every loop.
			break;
		case RX_COMMUNICATIONS:
				_PRINT_STATE_(F("STATE: RX_COMMUNICATIONS"));
			switch (currentMode)
			{
				case SYNCHRONIZATION:		
					runModeFunction_SYNCHRONIZATION(currentState);
					queuedState = DATA_VALIDATION;
					//Keep the currentMode the same (unchanged)	
					break;
				case SECURING_LINK:		
					runModeFunction_SECURING_LINK(currentState);
					queuedState = DATA_VALIDATION;
					break;
				case NORMAL_OPERATIONS:		
					runModeFunction_NORMAL_OPERATIONS(currentState);
					queuedState = DATA_VALIDATION;
					break;
				case SYSTEM_SLEEPING:		
					runModeFunction_SYSTEM_SLEEPING(currentState);
					queuedState = DATA_VALIDATION;
					break;
				case SW_RESETTING:		
					runModeFunction_SW_RESETTING(currentState);
					queuedState = DATA_VALIDATION;
					break;
				case SYSTEM_ERROR:		
					runModeFunction_SYSTEM_ERROR(currentState);
					queuedState = DATA_VALIDATION;
					break;		
				default: //default mode
					runModeFunction_default();//no state needed, all states do the same thing
					queuedState = CONTROL_OUTPUTS;
					currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
				break;
			}//end switch			
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state
			break;			
		case DATA_VALIDATION:
			_PRINT_STATE_(F("STATE: DATA_VALIDATION"));
			switch (currentMode)
			{
				case SYNCHRONIZATION:		
					runModeFunction_SYNCHRONIZATION(currentState);
					queuedState = DATA_FILTER;		
					//Keep the currentMode the same (unchanged)	
					break;
				case SECURING_LINK:		
					runModeFunction_SECURING_LINK(currentState);
					queuedState = DATA_FILTER;		
					//Keep the currentMode the same (unchanged)	
					break;	
				case NORMAL_OPERATIONS:		
					runModeFunction_NORMAL_OPERATIONS(currentState);
					queuedState = DATA_FILTER;		
					//Keep the currentMode the same (unchanged)	
					break;	
				case SYSTEM_SLEEPING:		
					runModeFunction_SYSTEM_SLEEPING(currentState);
					queuedState = DATA_FILTER;		
					//Keep the currentMode the same (unchanged)	
					break;											
				case SW_RESETTING:		
					runModeFunction_SW_RESETTING(currentState);
					queuedState = DATA_FILTER;		
					//Keep the currentMode the same (unchanged)	
					break;							
				case SYSTEM_ERROR:		
					runModeFunction_SYSTEM_ERROR(currentState);
					queuedState = DATA_FILTER;		
					//Keep the currentMode the same (unchanged)	
					break;									
				default: //default mode
					runModeFunction_default();//no state needed, all states do the same thing
					queuedState = CONTROL_OUTPUTS;
					currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
				break;
			}//end switch	
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state
			break;
		case DATA_FILTER:
			_PRINT_STATE_(F("STATE: DATA_FILTER"));
			switch (currentMode)
			{
				case SYNCHRONIZATION:		
					runModeFunction_SYNCHRONIZATION(currentState);
					queuedState = PROCESS_DATA;
					//Keep the currentMode the same (unchanged)	
					break;
				case SECURING_LINK:		
					runModeFunction_SECURING_LINK(currentState);
					queuedState = READ_INPUTS;		
					//Keep the currentMode the same (unchanged)	
					break;	
				case NORMAL_OPERATIONS:		
					runModeFunction_NORMAL_OPERATIONS(currentState);
					queuedState = READ_INPUTS;		
					//Keep the currentMode the same (unchanged)	
					break;	
				case SYSTEM_SLEEPING:		
					runModeFunction_SYSTEM_SLEEPING(currentState);
					queuedState = PROCESS_DATA;		
					//Keep the currentMode the same (unchanged)	
					break;											
				case SW_RESETTING:		
					runModeFunction_SW_RESETTING(currentState);
					queuedState = PROCESS_DATA;		
					//Keep the currentMode the same (unchanged)	
					break;							
				case SYSTEM_ERROR:		
					runModeFunction_SYSTEM_ERROR(currentState);
					queuedState = READ_INPUTS;		
					//Keep the currentMode the same (unchanged)	
					break;					
				default: //default mode
					runModeFunction_default();//no state needed, all states do the same thing
					queuedState = CONTROL_OUTPUTS;
					currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
				break;
			}//end switch	
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state
			break;
		case READ_INPUTS:	
			_PRINT_STATE_(F("STATE: READ_INPUTS"));
			switch (currentMode)
			{
				case SECURING_LINK:		
					runModeFunction_SECURING_LINK(currentState);
					queuedState = PROCESS_DATA;		
					//Keep the currentMode the same (unchanged)	
					break;	
				case NORMAL_OPERATIONS:		
					runModeFunction_NORMAL_OPERATIONS(currentState);
					queuedState = PROCESS_DATA;		
					//Keep the currentMode the same (unchanged)	
					break;	
				case SYSTEM_ERROR:		
					runModeFunction_SYSTEM_ERROR(currentState);
					queuedState = PROCESS_DATA;		
					//Keep the currentMode the same (unchanged)	
					break;					
				default: //default mode
					runModeFunction_default();//no state needed, all states do the same thing
					queuedState = CONTROL_OUTPUTS;
					currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
				break;
			}//end switch	
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state		
			break;			
		case PROCESS_DATA:
			_PRINT_STATE_(F("STATE: PROCESS_DATA"));
			switch (currentMode)
			{
				case SYNCHRONIZATION:		
					runModeFunction_SYNCHRONIZATION(currentState);
					queuedState = CONTROL_OUTPUTS;//DEBUG, WRITE CONDITIONAL STATEMENTS LATER AS THIS MAY BE OVERRIDDEN
					currentMode = SYNCHRONIZATION;//DEBUG, WRITE CONDITIONAL STATEMENTS LATER AS THIS MAY BE OVERRIDDEN
					break;
				case SECURING_LINK:		
					runModeFunction_SECURING_LINK(currentState);
					queuedState = CONTROL_OUTPUTS;//DEBUG, WRITE CONDITIONAL STATEMENTS LATER AS THIS MAY BE OVERRIDDEN
					currentMode = SECURING_LINK;//DEBUG, WRITE CONDITIONAL STATEMENTS LATER AS THIS MAY BE OVERRIDDEN
					break;	
				case NORMAL_OPERATIONS:		
					runModeFunction_NORMAL_OPERATIONS(currentState);
					queuedState = CONTROL_OUTPUTS;//DEBUG, WRITE CONDITIONAL STATEMENTS LATER AS THIS MAY BE OVERRIDDEN
					currentMode = NORMAL_OPERATIONS;//DEBUG, WRITE CONDITIONAL STATEMENTS LATER AS THIS MAY BE OVERRIDDEN
					break;	
				case SYSTEM_SLEEPING:		
					runModeFunction_SYSTEM_SLEEPING(currentState);
					queuedState = CONTROL_OUTPUTS;//DEBUG, WRITE CONDITIONAL STATEMENTS LATER AS THIS MAY BE OVERRIDDEN
					currentMode = SYSTEM_SLEEPING;//DEBUG, WRITE CONDITIONAL STATEMENTS LATER AS THIS MAY BE OVERRIDDEN
					break;											
				case SW_RESETTING:		
					runModeFunction_SW_RESETTING(currentState);
					queuedState = CONTROL_OUTPUTS;//DEBUG, WRITE CONDITIONAL STATEMENTS LATER AS THIS MAY BE OVERRIDDEN
					currentMode = SW_RESETTING;//DEBUG, WRITE CONDITIONAL STATEMENTS LATER AS THIS MAY BE OVERRIDDEN
					break;							
				case SYSTEM_ERROR:		
					runModeFunction_SYSTEM_ERROR(currentState);
					queuedState = CONTROL_OUTPUTS;//DEBUG, WRITE CONDITIONAL STATEMENTS LATER AS THIS MAY BE OVERRIDDEN
					currentMode = SYSTEM_ERROR;//DEBUG, WRITE CONDITIONAL STATEMENTS LATER AS THIS MAY BE OVERRIDDEN
					break;					
				default: //default mode
					runModeFunction_default();//no state needed, all states do the same thing
					queuedState = CONTROL_OUTPUTS;
					currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
				break;
			}//end switch	
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state
			break;
		case CONTROL_OUTPUTS:
			_PRINT_STATE_(F("STATE: CONTROL_OUTPUTS"));
			switch (currentMode)
			{
				case SYNCHRONIZATION:		
					runModeFunction_SYNCHRONIZATION(currentState);
					queuedState = CREATE_DATA;
					//Keep the currentMode the same (unchanged)	
					break;
				case SECURING_LINK:		
					runModeFunction_SECURING_LINK(currentState);
					queuedState = CREATE_DATA;		
					//Keep the currentMode the same (unchanged)	
					break;	
				case NORMAL_OPERATIONS:		
					runModeFunction_NORMAL_OPERATIONS(currentState);
					queuedState = CREATE_DATA;		
					//Keep the currentMode the same (unchanged)	
					break;	
				case HW_RESETTING:		
					runModeFunction_HW_RESETTING(currentState);
					queuedState = CREATE_DATA;		
					//Keep the currentMode the same (unchanged)	
					break;						
				case SYSTEM_SLEEPING:		
					runModeFunction_SYSTEM_SLEEPING(currentState);
					queuedState = CREATE_DATA;		
					//Keep the currentMode the same (unchanged)	
					break;									
				case SYSTEM_WAKING:		
					runModeFunction_SYSTEM_SLEEPING(currentState);
					queuedState = CREATE_DATA;		
					//Keep the currentMode the same (unchanged)	
					break;							
				case SW_RESETTING:		
					runModeFunction_SW_RESETTING(currentState);
					queuedState = CREATE_DATA;		
					//Keep the currentMode the same (unchanged)	
					break;							
				case SYSTEM_ERROR:		
					runModeFunction_SYSTEM_ERROR(currentState);
					queuedState = CREATE_DATA;		
					//Keep the currentMode the same (unchanged)	
					break;
				default: //default mode
					runModeFunction_default();//no state needed, all states do the same thing
					queuedState = CONTROL_OUTPUTS;
					currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
				break;
			}//end switch	
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state
			break;			
		case CREATE_DATA:
			_PRINT_STATE_(F("STATE: CREATE_DATA"));
			switch (currentMode)
			{
				case SYNCHRONIZATION:		
					runModeFunction_SYNCHRONIZATION(currentState);
					queuedState = TX_COMMUNICATIONS;
					//Keep the currentMode the same (unchanged)	
					break;
				case SECURING_LINK:		
					runModeFunction_SECURING_LINK(currentState);
					queuedState = TX_COMMUNICATIONS;		
					//Keep the currentMode the same (unchanged)	
					break;	
				case NORMAL_OPERATIONS:		
					runModeFunction_NORMAL_OPERATIONS(currentState);
					queuedState = TX_COMMUNICATIONS;		
					//Keep the currentMode the same (unchanged)	
					break;	
				case HW_RESETTING:		
					runModeFunction_HW_RESETTING(currentState);
					queuedState = TX_COMMUNICATIONS;		
					//Keep the currentMode the same (unchanged)	
					break;						
				case SYSTEM_SLEEPING:		
					runModeFunction_SYSTEM_SLEEPING(currentState);
					queuedState = TX_COMMUNICATIONS;		
					//Keep the currentMode the same (unchanged)	
					break;									
				case SYSTEM_WAKING:		
					runModeFunction_SYSTEM_SLEEPING(currentState);
					queuedState = TX_COMMUNICATIONS;		
					//Keep the currentMode the same (unchanged)	
					break;							
				case SW_RESETTING:		
					runModeFunction_SW_RESETTING(currentState);
					queuedState = TX_COMMUNICATIONS;		
					//Keep the currentMode the same (unchanged)	
					break;							
				case SYSTEM_ERROR:		
					runModeFunction_SYSTEM_ERROR(currentState);
					queuedState = TX_COMMUNICATIONS;		
					//Keep the currentMode the same (unchanged)	
					break;					
				default: //default mode
					runModeFunction_default();//no state needed, all states do the same thing
					queuedState = CONTROL_OUTPUTS;
					currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
				break;
			}//end switch	
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state
			break;
		case TX_COMMUNICATIONS:
			_PRINT_STATE_(F("STATE: TX_COMMUNICATIONS"));
			switch (currentMode)
			{
				case SYNCHRONIZATION:		
					runModeFunction_SYNCHRONIZATION(currentState);
					queuedState = RX_COMMUNICATIONS;
					//Keep the currentMode the same (unchanged)	
					break;					
				case SECURING_LINK:		
					runModeFunction_SECURING_LINK(currentState);					
//FIX ME LATER					
					queuedState = RX_COMMUNICATIONS;//DEBUG, WRITE CONDITIONAL STATEMENTS LATER AS THIS MAY BE OVERRIDDEN
					//Keep the currentMode the same (unchanged)	
					break;					
				case NORMAL_OPERATIONS:		
					runModeFunction_NORMAL_OPERATIONS(currentState);					
//FIX ME LATER					
					queuedState = RX_COMMUNICATIONS;//DEBUG, WRITE CONDITIONAL STATEMENTS LATER AS THIS MAY BE OVERRIDDEN
					//Keep the currentMode the same (unchanged)	
					break;					
				case HW_RESETTING:		
					runModeFunction_HW_RESETTING(currentState);					
					queuedState = TX_COMMUNICATIONS;
					//Keep the currentMode the same (unchanged)	
					break;					
				case SYSTEM_SLEEPING:		
					runModeFunction_SYSTEM_SLEEPING(currentState);					
					queuedState = RX_COMMUNICATIONS;
					//Keep the currentMode the same (unchanged)	
					break;					
				case SYSTEM_WAKING:		
					runModeFunction_SYSTEM_WAKING(currentState);					
					queuedState = RX_COMMUNICATIONS;
					currentMode = SYNCHRONIZATION;//Set mode to SYNCHRONIZATION *begin*		
					break;					
				case SW_RESETTING:		
					runModeFunction_SW_RESETTING(currentState);					
					queuedState = RX_COMMUNICATIONS;
					//Keep the currentMode the same (unchanged)	
					break;				
				case SYSTEM_ERROR:		
					runModeFunction_SYSTEM_ERROR(currentState);					
//FIX ME LATER					
					queuedState = RX_COMMUNICATIONS;//DEBUG, WRITE CONDITIONAL STATEMENTS LATER AS THIS MAY BE OVERRIDDEN
					//Keep the currentMode the same (unchanged)	
					break;				
				default: //default mode
					runModeFunction_default();//no state needed, all states do the same thing
					queuedState = CONTROL_OUTPUTS;
					currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
				break;
			}//end switch	
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state
			break;		
		default: //default state
			_PRINT_STATE_(F("STATE: default"));
			runModeFunction_default();//no state needed, all states do the same thing
			queuedState = CONTROL_OUTPUTS;
			currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state
			break;
	}//end switch


	//Advance to the next state (happens after every loop through the switch case for state selection)
	currentState = nextState;//go to the next state
  
  
}//end of loop()




//============Function Definitions


//====Misc Functions
void runPORTasks()
{
	//run POR tasks
//WRITE ME LATER	
	
}//runPORTasks()
void initializeVariables()
{
	//(re)initialize most global variables (i.e. for software reset)

	
	
	
		
	
	
	
	
	
	
	
	//Message Queues
	cmnc_msg_queue = CMD_TAG_NO_MSG; // (command tag, not boolean since use by CREATE_DATA to generate messages as well as TX_COMMUNICATIONS as a flag)
	main_msg_queue = CMD_TAG_NO_MSG; // (command tag, not boolean since use by CREATE_DATA to generate messages as well as TX_COMMUNICATIONS as a flag)

	//Flag(s) - Error
	invalid_state_or_mode_error = false;
	sync_error = false;
	secure_link_error = false;
	sw_reset_error = false;
	generic_health_error = false;
	sleeping_error = false;
	//Flag(s) - Message Controls
	redirectToCMNC = false;
	redirectToMAIN = false;
	//Flag(s) - Status
	main_system_ready = false;
	communications_secure = false;//(used to keep track is the communications link is already secure or not, and is useful for things like when going to sleep and waking back up and needing to synchronize again without needing to resecure the link)
	first_transmission = true;
	//Flag(s) - Data was for this local Arduino that is running this sketch (and not something it's connected to)
	dataWasForCOMM_Ch1 = false;//for PC USB/CNMC
	dataWasForCOMM_Ch2 = false;//for MAIN
	//Status(es) - Rover Data Channels
	ch1Status = DATA_STATUS_NOT_READY;
	ch2Status = DATA_STATUS_NOT_READY;
	//Flag(s) - Command Filter Options
	commandEnableOption_Hi = false;//DEBUG
	commandEnableOption_Bye = false;//DEBUG
	commandEnableOption_Invalid = false;//DEBUG
	commandEnableOption_EstablishSecureLink = false;
//ADD MORE COMMAND OPTIONS HERE (remember to update setAllCommandsTo() as well)


	//Counters
	timeout_counter = 0; //shared counter, used to detect timeout of MAIN responding back to COMM for any reason (i.e. system go or system ready responses), used to track how long COMM has been waiting for a COMM SW Request back from MAIN, after it sent a ALL_SW_RESET_REQUEST to MAIN (which MAIN might have missed, since it's sent only once), etc. Make sure to clear it out before use and only use it for one purpose at a time.
	transmission_delay_cnt = 0;//concurrent transmission delay counter
	
} //end of initializeVariables()
void startBackgroundTasks()
{
	//start background tasks
//WRITE ME LATER
}//end of startBackgroundTasks()
void runBackgroundTasks()
{
	//run background tasks
//WRITE ME LATER
}//end of runBackgroundTasks()
byte rxData(RoverComm * roverComm, byte roverCommType) {


	byte counter;
	byte dataStatus = DATA_STATUS_NOT_READY;
	
	//Note: Make sure validateData() is called between (before, after, or in) successive rxData() function calls, as it will clear the string and reset the index (required for the code to work properly)
	if (roverCommType == ROVERCOMM_CMNC)
	{

		if (_CMNC_SERIAL_.available() > 1)
		{
	
			//initialize the counter
			counter = 0;

			while (_CMNC_SERIAL_.available() > 0 && counter <= ROVER_COMM_SENTENCE_LENGTH)//while there is data on the Serial RX Buffer and the length is not over the max GPS sentence length
			{
				//Read one character of serial data at a time
				//Note: Must type cast the _CMNC_SERIAL_.Read to a char since not saving it to a char type first
				roverComm->appendToRxData((char)_CMNC_SERIAL_.read());//construct the string one char at a time
				counter++;
				delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
			}//end while

			dataStatus = DATA_STATUS_READY;
		}//end if
		else
		{
			dataStatus = DATA_STATUS_NOT_READY;
		}//end else
	}//end if
	else if (roverCommType == ROVERCOMM_MAIN)
	{
	
	
		if (_MAIN_SWSERIAL_.available() > 1)
		{
		
		
			//initialize the counter
			counter = 0;
			
			while (_MAIN_SWSERIAL_.available() > 0 && counter <= ROVER_COMM_SENTENCE_LENGTH)//while there is data on the Serial RX Buffer and the length is not over the max GPS sentence length
			{
				//Read one character of serial data at a time
				//Note: Must type cast the Serial.Read to a char since not saving it to a char type first
				roverComm->appendToRxData((char)_MAIN_SWSERIAL_.read());//construct the string one char at a time
				counter++;
				delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
			}//end while
			dataStatus = DATA_STATUS_READY;
		}//end if
		else
		{
			dataStatus = false;
		}//end DATA_STATUS_NOT_READY
	}//end else if
	else
	{
		//invalid RoverComm Type, so do nothing
		dataStatus = DATA_STATUS_NOT_READY;
	}//end else

	
	return dataStatus;

}//end of rxData()

boolean dataDirector(RoverData * roverData, byte redirectOption)
{
	//Note: This function varies for different Arduinos

	boolean dataWasForThisArduino = false;//initialize local flag to false
	byte roverCommType = roverData->getCommType();//get the roverComm Destination
		
	if (roverCommType == ROVERCOMM_COMM)
	{
		//if the data is for this unit, CMNC
		dataWasForThisArduino = true;//set the status such that the data was for this unit, COMM
		//process it back in the main loop (to prevent software stack from being too deep)
	}//end if
	//else check to see if the data was for other cases
	else if(redirectOption == DATA_REDIRECT_ENABLED)
	{
		if (roverCommType == ROVERCOMM_CMNC)
		{
			//if the data is for CMNC, transmit the data out from COMM to CMNC
			redirectToCMNC = true;			
		}//end else if
		else if (roverCommType == ROVERCOMM_NAVI || roverCommType == ROVERCOMM_AUXI || roverCommType == ROVERCOMM_MAIN)
		{
			//if the data is for either NAVI, AUXI, or MAIN, transmit the data out from COMM to MAIN since COMM only can talk to MAIN and not NAVI or AUXI (and MAIN will process it accordingly or reroute it if needed)
			redirectToMAIN = true;
		}//end else if
		//else the command type is ROVERCOMM_NONE
		//invalid RoverComm Type, so do nothing		
	}//end if
	//else the data was not for this local unit, and redirect was disabled, so do nothing
	
	return dataWasForThisArduino;
}//end of dataDirector()

void txData(char * txData, byte roverCommType)
{
	//Note: This function varies for different Arduinos

	if (roverCommType == ROVERCOMM_COMM || roverCommType == ROVERCOMM_CMNC || roverCommType == ROVERCOMM_PC_USB)
	{
		//transmit the data to CMNC or through the USB of this Arduino (i.e. for debug) [in this case, it means the same thing]
		_CMNC_SERIAL_.println(txData);
	}//end if
	else if (roverCommType == ROVERCOMM_MAIN)
	{
		//transmit the data to MAIN
		_MAIN_SWSERIAL_.println(txData);
	}//end else if
	else
	{
		//do nothing
	}//end else
}//end of txData()

void commandDirector(char * roverCommand)
{
	//Note: This function varies for different Arduinos


	//Categorize all commands/data from all sources.					
	//Sort based on priority.
	//Allow for all non-conflicting commands to run.
	//Then only run the highest priority functions for COMM last, so it will overwrite anything else, right before state transition.
					
	
//Run lower priority functions here. (i.e. system ready msgs)
					
	
	
	//=========TEMP CODE BELOW
	//WRITE ME LATER

	//MOVE THE TX CODE OUT OF HERE
	//ACTUALLY THE TX CODE IS SUPPOSED TO BE DONE LATER. (same with controlling outputs)
	//ALL THAT SHOULD BE DONE HERE IS PUTTING MESSAGE IN MESSAGE QUEUES AND/OR SETTING FLAGS

	
	//This checks to see if the roverCommand matches any of the known values. Else it's an invalid command
	if (strcmp(roverCommand, "hi") == 0 && commandEnableOption_Hi == true)
	{
		txData("Valid Cmd! =)", ROVERCOMM_CMNC);
		txData("Rx'd:", ROVERCOMM_CMNC);
		txData(roverCommand, ROVERCOMM_CMNC);
	}//end if
	else if (strcmp(roverCommand, "bye") == 0 && commandEnableOption_Bye == true)
	{
		txData("Valid Cmd! =)", ROVERCOMM_CMNC);
		txData("Rx'd:", ROVERCOMM_CMNC);
		txData(roverCommand, ROVERCOMM_CMNC);
	}//end else if
	else if(commandEnableOption_EstablishSecureLink == true)//DEBUG, DELETE ME AND USE BELOW LATER
	//else if(strcmp(roverCommand, "??ADD SECURE LINK MESSAGE HERE???") == 0 && commandEnableOption_EstablishSecureLink == true)//DEBUG, FIX ME LATER
	{
		//WRITE ME LATER
		//establish secure link logic here
	}
	else
	{
		if(commandEnableOption_Invalid == true)
		{
			txData("Invalid Cmd! =(", ROVERCOMM_CMNC);
			txData("Rx'd:", ROVERCOMM_CMNC);
			txData(roverCommand, ROVERCOMM_CMNC);
		}
	}//end else

	//=========END OF TEMP CODE BELOW
	
	
}//end of commandDirector()


void setAllCommandsTo(boolean choice)
{
	//Note: Right now this function doesn't discriminate where the commands are coming from. So if they're all set to true, in theory, for example CMNC can "inject" or "spoof" a command that looks like it's coming from somewhere else.
	//This is a bug that can be fixed later if needed. Keeping it simple for now.
	
	commandEnableOption_Hi = choice;
	commandEnableOption_Bye = choice;
	commandEnableOption_Invalid = choice;
//ADD MORE COMMAND OPTIONS HERE
}//end of setAllCommands()
void redirectData()
{

	byte roverCommType;

	roverCommType = roverDataCh2_COMM->getCommType();//get the roverComm Destination for roverDataCh2_COMM
	
	if(redirectToCMNC)
	{
		//Priority of the redirect is given by the order of the if/else statement.  All other redirect messages going to the same destination will get dropped/lost.
			//Note: For the COMM there is only one other channel, so it always gets the priority
		//Priority 1: MAIN to CMNC
		if (roverCommType == ROVERCOMM_CMNC)
		{
			//if the data is for CMNC, transmit the data out from COMM to CMNC
			txData(roverDataCh2_COMM->getData(), ROVERCOMM_CMNC);		
		}//end if
	}//end if	
		
	roverCommType = roverDataCh1_COMM->getCommType();//get the roverComm Destination for roverDataCh1_COMM
		
	if(redirectToMAIN)
	{
		//Priority of the redirect is given by the order of the if/else statement.  All other redirect messages going to the same destination will get dropped/lost.
			//Note: For the COMM there is only one other channel, so it always gets the priority
		//Priority 1: CMNC to MAIN
		if (roverCommType == ROVERCOMM_NAVI || roverCommType == ROVERCOMM_AUXI || roverCommType == ROVERCOMM_MAIN)
		{
			//if the data is for MAIN, transmit the data out from COMM to CMNC
			txData(roverDataCh1_COMM->getData(), ROVERCOMM_MAIN);		
		}//end if
	}//end if	
		
}//End of redirectData()
				
				
//====End of: Misc Functions


//====Mode Functions

void runModeFunction_POWER_ON_AND_HW_RESET(byte currentState)
{
	_PRINT_MODE_(F("MODE: POWER_ON_AND_HW_RESET"));

	switch (currentState)
	{
		case RUN_HOUSEKEEPING_TASKS:
			runPORTasks();
			break;
		default: //default state, if the state is not listed, it should never be called from this mode. If it does, there is a logical or programming error.
			//This code should never execute, if it does, there is a logical or programming error
			runModeFunction_default();//no state needed, all states do the same thing
			break;
	}//end switch
}//end of runStateFunction_POWER_ON_AND_HW_RESET
void runModeFunction_INITIALIZATION(byte currentState)
{
	_PRINT_MODE_(F("MODE: INITIALIZATION"));

	switch (currentState)
	{
		case RUN_HOUSEKEEPING_TASKS:
			//initialize / reinitialize all variables
			initializeVariables();
			//start background tasks
			startBackgroundTasks();
			//initialize/reset shared counter before use
			timeout_counter = 0;
		break;
		default: //default state, if the state is not listed, it should never be called from this mode. If it does, there is a logical or programming error.
			//This code should never execute, if it does, there is a logical or programming error
			runModeFunction_default();//no state needed, all states do the same thing
			break;
	}//end switch
}//end of runModeFunction_INITIALIZATION
void runModeFunction_SYNCHRONIZATION(byte currentState)
{
	_PRINT_MODE_(F("MODE: SYNCHRONIZATION"));
	switch (currentState)
	{
		case RUN_HOUSEKEEPING_TASKS:
			runBackgroundTasks();			
			break;
		case RX_COMMUNICATIONS:
			
			//skip for CMNC
				
			//rxData() from MAIN
				//1. Reset status flag
				ch2Status = DATA_STATUS_NOT_READY;				
				//2. Clear data before getting new data				
				roverDataCh2_COMM->clearData();
				//3. Receive data
				ch2Status = rxData(roverComm_Ch2, ROVERCOMM_MAIN);//Note: this is a local .ino function
			break;
		case DATA_VALIDATION:
			
			//skip for CMNC
			
			//validateData() from MAIN
				//Process/validate the data that was received
				if ( ch2Status == DATA_STATUS_READY)
				{
					//If the data is valid, set the status as such
					if(roverComm_Ch2->validateData())
					{
						ch2Status = DATA_STATUS_VALID;//if data is valid once it's validated, set the flag
					}
					//Else the data is invalid, so set the status as such
					else
					{
						ch2Status = DATA_STATUS_INVALID;
					}
				}
				//Else, since the data isn't ready, leave the status as DATA_STATUS_NOT_READY
				
			break;
		case DATA_FILTER:
			
			
			//Reset flags to default (no data for COMM)
			dataWasForCOMM_Ch1 = false;
			dataWasForCOMM_Ch2 = false;
			//Reset flags to default (no redirection needed). They will then be set by any of the calls to dataDirector if there is redirection required from the Arduinos, correspondingly.
			redirectToCMNC = false;
			redirectToMAIN = false;
			
			
			//Transmit data and/or execute command

			//Skip for CMNC (since the link isn't secure yet)
					//Note: no reset (hw or sw) allowed from CMNC yet. because if it can take a reset msg, it should be able to secure link. Also there is a secure link timeout, that then goes to error mode and allows for hw/sw reset.
					//no redirections from CMNC

			
			//For data from MAIN, transmit the data to it's proper destination if it was meant
				//For another Arduino or take any actions if the data was meant for this unit, COMM
				
				
				if (ch2Status==DATA_STATUS_VALID)
				{
					//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
					//Set no redirections from MAIN	
					//Note: this is a local .ino function
					dataWasForCOMM_Ch2 = dataDirector(roverDataCh2_COMM, DATA_REDIRECT_DISABLED);//DataDirection will set dataWasForCOMM_Ch2 to true if it was for this Arduino
					
					/*
						Set filter to throw away all MAIN data except:
							system ready message(s) from MAIN
							system go message(s) from MAIN
							hw reset requests message(s) from MAIN
							sw reset requests message(s) from MAIN
							generic status error message(s) from MAIN (redirected from AUXI)
					*/
					
					//Set Command Filter Options
					//First initialize all command choices to false
					setAllCommandsTo(false);
					//Then enable the allowed commands:

					//TEMP DEBUG CODE

						/*
//LEFT OFF HERE
						WRITE ME LATER
						PUT IN THE ACTUAL COMMAND OPTIONS LATER
									//filter and throw away all MAIN data except:
										//system ready message(s) from MAIN
										//system go message(s) from MAIN
										//hw reset requests message(s) from MAIN
										//sw reset requests message(s) from MAIN
										//generic status error message(s) from MAIN (redirected from AUXI)
						*/


						commandEnableOption_Hi = true;//DEBUG	
						commandEnableOption_Bye  = true;//DEBUG, FOR DEBUGGING, can disable this to see that the filter works
						commandEnableOption_Invalid = true;//DEBUG


					//END OF TEMP DEBUG CODE

				}//end if
				//else the data was invalid or not ready, so do nothing

				
			break;
		case PROCESS_DATA:
			//WRITE ME LATER


			//Skip Process of PIR status
			//Skip Process CMNC command/data
			//Process MAIN command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//Note: Either you should get no data, hw reset, sw reset, generic health status errors, or system ready or system go message(s) from MAIN. as everything else was filtered out.
				//Remember, only  hw reset, sw reset, generic health status error, or system ready or system go message(s) can pass the data filter.



			if(dataWasForCOMM_Ch2)//If there was data from MAIN (Ch2), and it was for COMM
			{
				//1. First send the RoverData to the roverCommand's parser to get the command
				roverCommand->parseCommand(roverDataCh2_COMM->getData(), roverDataCh2_COMM->getDataLength());
						





						
				//2. Then run the command director to run the allowed commands
				commandDirector(roverCommand->getCommand());
			}//end if

					//WRITE ME LATER
					//FINISH ME
					
					/*

						
						
						If !(system go msg received from MAIN aka can be system ready or no msg)
							main_msg_queue = SYSTEM_READY_STATUS (tells MAIN it's ready to synchronize)
						end if
						Note: If system go or system ready msg has been received from MAIN, see "Command Options" below for more info.
	
						//Run highest priority functions here. //this will override any lower priority messages (i.e. system go). This will overwrite anything else. (i.e. system ready)
							
						
						If no system go msg from MAIN received && main_system_ready == false (MAIN system not ready yet to set the main_system_ready flag and have not received a system go to switch states yet, then keep incrementing the timeout counter)
							timeout_counter++
						end if								
						if timeout_counter >= COMM_SYNC_TIMEOUT_VALUE
							Set mode to SYSTEM_ERROR *begin*
							cmnc_msg_queue == SYNC_ERROR_STATUS
							set sync_error = true
							(Note: the sync_error flag can only be cleared with a sw reset or hw reset)
							//initialize/reset shared counter before use
							timeout_counter = 0;
						end if	



				*/



	


			break;
		case CONTROL_OUTPUTS:
			//WRITE ME LATER
			break;
		case CREATE_DATA:
			//WRITE ME LATER
			break;
		case TX_COMMUNICATIONS:
			//WRITE ME LATER
			
			redirectData();//This function will redirect data as required
			
			
			break;					
		default: //default state, if the state is not listed, it should never be called from this mode. If it does, there is a logical or programming error.
				//This code should never execute, if it does, there is a logical or programming error
				runModeFunction_default();//no state needed, all states do the same thing
			break;
	}//end switch	
}//end of runModeFunction_SYNCHRONIZATION()
void runModeFunction_SECURING_LINK(byte currentState)
{
	_PRINT_MODE_(F("MODE: SECURING_LINK"));
	switch (currentState)
	{
		case RUN_HOUSEKEEPING_TASKS:
			runBackgroundTasks();
			break;
		case RX_COMMUNICATIONS:
				
			//rxData() from CMNC
				//1. Reset status flag
				ch1Status = DATA_STATUS_NOT_READY;				
				//2. Clear data before getting new data				
				roverDataCh1_COMM->clearData();
				//3. Receive data
				ch1Status = rxData(roverComm_Ch1, ROVERCOMM_CMNC);//Note: this is a local .ino function
				
			//rxData() from MAIN
				//1. Reset status flag
				ch2Status = DATA_STATUS_NOT_READY;				
				//2. Clear data before getting new data				
				roverDataCh2_COMM->clearData();
				//3. Receive data
				ch2Status = rxData(roverComm_Ch2, ROVERCOMM_MAIN);//Note: this is a local .ino function
				
			break;
		case DATA_VALIDATION:
			
			//validateData() from CMNC
				//Process/validate the data that was received
				if ( ch1Status == DATA_STATUS_READY)
				{
					//If the data is valid, set the status as such
					if(roverComm_Ch1->validateData())
					{
						ch1Status = DATA_STATUS_VALID;//if data is valid once it's validated, set the flag
					}//end if
					//Else the data is invalid, so set the status as such
					else
					{
						ch1Status = DATA_STATUS_INVALID;
					}//end else
				}//end if
				//Else, since the data isn't ready, leave the status as DATA_STATUS_NOT_READY
				
				
			//validateData() from MAIN
				//Process/validate the data that was received
				if ( ch2Status == DATA_STATUS_READY)
				{
					//If the data is valid, set the status as such
					if(roverComm_Ch2->validateData())
					{
						ch2Status = DATA_STATUS_VALID;//if data is valid once it's validated, set the flag
					}//end if
					//Else the data is invalid, so set the status as such
					else
					{
						ch2Status = DATA_STATUS_INVALID;
					}//end else
				}//end if
				//Else, since the data isn't ready, leave the status as DATA_STATUS_NOT_READY
				
				
				
			break;
		case DATA_FILTER:
	
			//Reset flags to default (no data for COMM)
			dataWasForCOMM_Ch1 = false;
			dataWasForCOMM_Ch2 = false;
			//Reset flags to default (no redirection needed). They will then be set by any of the calls to dataDirector if there is redirection required from the Arduinos, correspondingly.
			redirectToCMNC = false;
			redirectToMAIN = false;
			
			
			
			//Transmit data and/or execute command
				//For data from CMNC, transmit the data to it's proper destination if it was meant for another Arduino
				//or take any actions if the data was meant for this unit, COMM
				if (ch2Status==DATA_STATUS_VALID)
				{
					//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
					//Set no redirections from MAIN	
					//Note: this is a local .ino function
					dataWasForCOMM_Ch2 = dataDirector(roverDataCh2_COMM, DATA_REDIRECT_DISABLED);//DataDirection will set dataWasForCOMM_Ch2 to true if it was for this Arduino
		
							
					/*
						Set filter to throw away all CMNC data except:
							establish secure link message(s) from CMNC
							Note: no reset (hw or sw) allowed from CMNC yet. because if it can take a reset msg, it should be able to secure link. Also there is a secure link timeout, that then goes to error mode and allows for hw/sw reset.
					*/
					
					//Set Command Filter Options
					//First initialize all command choices to false
					setAllCommandsTo(false);
					//Then enable the allowed commands:
					commandEnableOption_EstablishSecureLink = true;				
		
				}//end if
			
				

				//For data from MAIN, transmit the data to it's proper destination if it was meant for another Arduino
				//or take any actions if the data was meant for this unit, COMM		
				if (ch2Status==DATA_STATUS_VALID)
				{
					//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
					//Set no redirections from MAIN	
					//Note: this is a local .ino function
					dataWasForCOMM_Ch2 = dataDirector(roverDataCh2_COMM, DATA_REDIRECT_DISABLED);//DataDirection will set dataWasForCOMM_Ch2 to true if it was for this Arduino
		
							
					/*
						No filter on MAIN data. (Allow all data from MAIN)
					*/
					
					//Set Command Filter Options
					//No commands from MAIN are filtered, so set all to true.
					setAllCommandsTo(true);
		
				}//end if
				//else the data was invalid or not ready, so do nothing						
			break;
		case READ_INPUTS:
			//WRITE ME LATER
//LEFT OFF HERE
			
			break;
		case PROCESS_DATA:
			//WRITE ME LATER
			break;
		case CONTROL_OUTPUTS:
			//WRITE ME LATER
			break;
		case CREATE_DATA:
			//WRITE ME LATER
			break;
		case TX_COMMUNICATIONS:
			//WRITE ME LATER
			
						
			redirectData();//This function will redirect data as required
					
			
			
			break;					
			default: //default state, if the state is not listed, it should never be called from this mode. If it does, there is a logical or programming error.
				//This code should never execute, if it does, there is a logical or programming error
				runModeFunction_default();//no state needed, all states do the same thing
			break;
	}//end switch	
}//end of runModeFunction_SECURING_LINK()
void runModeFunction_NORMAL_OPERATIONS(byte currentState)
{
	_PRINT_MODE_(F("MODE: NORMAL_OPERATIONS"));
	switch (currentState)
	{
		case RUN_HOUSEKEEPING_TASKS:
			runBackgroundTasks();
			break;
		case RX_COMMUNICATIONS:
			//WRITE ME LATER
			break;
		case DATA_VALIDATION:
			//WRITE ME LATER
			break;
		case DATA_FILTER:
			//WRITE ME LATER
			break;
		case READ_INPUTS:
			//WRITE ME LATER
			break;
		case PROCESS_DATA:
			//WRITE ME LATER
			break;
		case CONTROL_OUTPUTS:
			//WRITE ME LATER
			break;
		case CREATE_DATA:
			//WRITE ME LATER
			break;
		case TX_COMMUNICATIONS:
			//WRITE ME LATER
			break;					
		default: //default state, if the state is not listed, it should never be called from this mode. If it does, there is a logical or programming error.
				//This code should never execute, if it does, there is a logical or programming error
				runModeFunction_default();//no state needed, all states do the same thing
			break;
	}//end switch		
}//end of runModeFunction_NORMAL_OPERATIONS()
void runModeFunction_HW_RESETTING(byte currentState)
{
	_PRINT_MODE_(F("MODE: HW_RESETTING"));
	switch (currentState)
	{
		case RUN_HOUSEKEEPING_TASKS:
			runBackgroundTasks();
			break;
		case CONTROL_OUTPUTS:
			//WRITE ME LATER
			break;
		case CREATE_DATA:
			//WRITE ME LATER
			break;
		case TX_COMMUNICATIONS:
			//WRITE ME LATER
			break;					
		default: //default state, if the state is not listed, it should never be called from this mode. If it does, there is a logical or programming error.
				//This code should never execute, if it does, there is a logical or programming error
				runModeFunction_default();//no state needed, all states do the same thing
			break;
	}//end switch	
}//end of runModeFunction_HW_RESETTING()
void runModeFunction_SYSTEM_SLEEPING(byte currentState)
{
	_PRINT_MODE_(F("MODE: SYSTEM_SLEEPING"));
	switch (currentState)
	{
		case RUN_HOUSEKEEPING_TASKS:
			runBackgroundTasks();
			break;
		case RX_COMMUNICATIONS:
			//WRITE ME LATER
			break;
		case DATA_VALIDATION:
			//WRITE ME LATER
			break;
		case DATA_FILTER:
			//WRITE ME LATER
			break;
		case PROCESS_DATA:
			//WRITE ME LATER
			break;
		case CONTROL_OUTPUTS:
			//WRITE ME LATER
			break;
		case CREATE_DATA:
			//WRITE ME LATER
			break;
		case TX_COMMUNICATIONS:
			//WRITE ME LATER
			break;					
		default: //default state, if the state is not listed, it should never be called from this mode. If it does, there is a logical or programming error.
				//This code should never execute, if it does, there is a logical or programming error
				runModeFunction_default();//no state needed, all states do the same thing
			break;
	}//end switch	
}//end of runModeFunction_SYSTEM_SLEEPING()
void runModeFunction_SYSTEM_WAKING(byte currentState)
{
	_PRINT_MODE_(F("MODE: SYSTEM_WAKING"));
	switch (currentState)
	{
		case RUN_HOUSEKEEPING_TASKS:
			runBackgroundTasks();
			break;
		case PROCESS_DATA:
			//WRITE ME LATER
			break;
		case CONTROL_OUTPUTS:
			//WRITE ME LATER
			break;
		case CREATE_DATA:
			//WRITE ME LATER
			break;
		case TX_COMMUNICATIONS:
			//WRITE ME LATER
			break;					
		default: //default state, if the state is not listed, it should never be called from this mode. If it does, there is a logical or programming error.
				//This code should never execute, if it does, there is a logical or programming error
				runModeFunction_default();//no state needed, all states do the same thing
			break;
	}//end switch	
}//end of runModeFunction_SYSTEM_WAKING()
void runModeFunction_SW_RESETTING(byte currentState)
{
	_PRINT_MODE_(F("MODE: SW_RESETTING"));
	switch (currentState)
	{
		case RUN_HOUSEKEEPING_TASKS:
			runBackgroundTasks();
			break;
		case RX_COMMUNICATIONS:
			//WRITE ME LATER
			break;
		case DATA_VALIDATION:
			//WRITE ME LATER
			break;
		case DATA_FILTER:
			//WRITE ME LATER
			break;
		case PROCESS_DATA:
			//WRITE ME LATER
			break;
		case CONTROL_OUTPUTS:
			//WRITE ME LATER
			break;
		case CREATE_DATA:
			//WRITE ME LATER
			break;
		case TX_COMMUNICATIONS:
			//WRITE ME LATER
			break;					
		default: //default state
				//This code should never execute, if it does, there is a logical or programming error
				runModeFunction_default();//no state needed, all states do the same thing
			break;
	}//end switch	
}//end of runModeFunction_SW_RESETTING()
void runModeFunction_SYSTEM_ERROR(byte currentState)
{
	_PRINT_MODE_(F("MODE: SYSTEM_ERROR"));
	switch (currentState)
	{
		case RUN_HOUSEKEEPING_TASKS:
			runBackgroundTasks();
			break;
		case RX_COMMUNICATIONS:
			//WRITE ME LATER
			break;
		case DATA_VALIDATION:
			//WRITE ME LATER
			break;
		case DATA_FILTER:
			//WRITE ME LATER
			break;
		case READ_INPUTS:
			//WRITE ME LATER
			break;
		case PROCESS_DATA:
			//WRITE ME LATER
			break;
		case CONTROL_OUTPUTS:
			//WRITE ME LATER
			break;
		case CREATE_DATA:
			//WRITE ME LATER
			break;
		case TX_COMMUNICATIONS:
			//WRITE ME LATER
			break;					
		default: //default state, if the state is not listed, it should never be called from this mode. If it does, there is a logical or programming error.
				//This code should never execute, if it does, there is a logical or programming error
				runModeFunction_default();//no state needed, all states do the same thing
			break;
	}//end switch	
}//end of runModeFunction_SYSTEM_ERROR()
void runModeFunction_default()
{
	_PRINT_MODE_(F("MODE: default"));
	_SERIAL_DEBUG_CHANNEL_.println(F("UnExpErr"));//unexpected error
	//No switch case needed for the states, all states do the same thing
	cmnc_msg_queue = CMD_TAG_INVALID_STATE_ERROR_STATUS;
	invalid_state_or_mode_error = true;//Note: the invalid_state_or_mode_error flag can only be cleared with a sw reset or hw reset
	//initialize/reset shared counter before use
	timeout_counter = 0;	
}//end of runStateFunction_default
 
 //====End of: Mode Functions
//============End of Function Definitions






void InterruptDispatch1() {
	//pirSensor->isrUpdate();
}

void InterruptDispatch2() {
	//Have to keep the ISR short else the program won't work
	sleeperCOMM->isrUpdate();//update the awake flag to reflect current status
}