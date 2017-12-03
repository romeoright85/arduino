/*
Note:
The best way to read this code from scratch is look at the global default values, see what state and mode the variables get on power on, then follow the state machine in the loop from the initializing state and mode
*/



/*
Design Notes:
Currently the priority level is not being used to prioritize right now. It's just there as a placeholder.
*/

//Rover_StateMachine_MAIN



/*
--------------------------------
Regular Operation
--------------------------------
//No commands are sent to MAIN directly during regular operation.


--------------------------------
Debug Operation
--------------------------------
//To test code, in RoverConfig uncomment _DEBUG_ALL_SERIALS_WITH_USB_SERIAL_


To test locally with only one Arduino (best to test the MEGA to make sure it can handle the memory needs for the COMM), first make sure if _DEBUG_ALL_SERIALS_WITH_USB_SERIAL_ is uncommented in RoverConfig.h
Can send:
//WRITE ME LATER
*/



//Configuration defines for #includes (must come before the #includes)
#ifndef _ROVER_STATES_AND_MODES
#define _ROVER_STATES_AND_MODES
#endif
#ifndef _COMMAND_CREATION_DEFINITIONS
#define _COMMAND_CREATION_DEFINITIONS //for RoverCommandDefs.h
#endif
#ifndef _ARD_3_MAIN_H
#define _ARD_3_MAIN_H //Must define this before calling RoverConfig.h (either directly or through another header file), define this flag to turn on COMM definitions
#endif
#ifndef _MAIN_BIT_FLAGS_
#define _MAIN_BIT_FLAGS_ //For RoverBitFlags.h
#endif
#ifndef _MAIN_STATE_MACHINE_VARIABLES_
#define _MAIN_STATE_MACHINE_VARIABLES_ //For RoverConfig.h
#endif



//#includes
#include <RoverStatesAndModes.h>
#include <RoverCommandDefs.h>
#include <RoverCommandCreator.h>
#include <RoverData.h>
#include <RoverComm.h> //calls RoverConfig.h
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>
#include <RoverHwReset.h>
#include <RoverSleeperServer.h>
#include <RoverSleeperClient.h>
#include <RoverConfig.h>	
#include <avr/pgmspace.h> //To store certain variables in Flash
#include <BooleanBitFlags.h>	
#include <RoverBitFlags.h>	
#include <MotorPowerControl.h>
#include <WheelEncoderSensor.h>



//============Function Prototypes
void InterruptDispatch_wheelEncoder_MidLeft();
void InterruptDispatch_wheelEncoder_MidRight();
void InterruptDispatch_WakeUpArduino();//For RoverSleeper
//============End of Function Prototypes


//============Debugging: Serial Channel Selection
//Used to output debugging messages only when the _DEBUG_COMM_BROADCAST flag is defined
//Uncomment the flag below in order to output debugging messages
//#define _DEBUG_COMM_BROADCAST

//Flag Logic, no need to edit this below
//Reference the "Where Left Off...txt" at: K:\Working Directory\DESIGN_PROJ\Design Projects\Robot\Workspaces\Arduino\2nd Gen Code\GitHub\arduino\Planning
#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ _COMM_SERIAL_ //When using COMM Broadcast, reroute the PC USB output to the channel to COMM instead
#else
	#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_
#endif

//============End of Debugging: Serial Channel Selection




//============Debugging: Print Mode and/or State
//Uncomment the flag below in order to print the current state and/or mode
//#define _DEBUG_PRINT_CURRENT_STATE
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


 //============Debugging: Redirection Notice
//Uncomment to output notice when redirection is occuring
//#define _DEBUG_REDIRECTION_NOTICE
//============End Debugging: Redirection Notice


//============Debugging: All Data Filtering Off
//Uncomment in order to allow all data to pass (turn off all data filters) for debugging)
#define _DEBUG_TURN_OFF_ALL_DATA_FILTERS
//============End Debugging: All Data Filtering Off

//============Debugging: Turn off System Ready Status During Synchronization Mode
//Uncomment in order to allow other data to be in the comm_msg_queue, navi_msg_queue, and/or auxi_msg_queue instead of just System Status
#define _DEBUG_TURN_OFF_SYSTEM_READY_STATUS
//============End Debugging: All Data Filtering Off



//============Debugging: Print timeout counter value
//Uncomment in order to print timeout counter value
//#define _DEBUG_PRINT_TIMEOUT_COUNTER_VALUE_
//============End Debugging: Print timeout counter value


//============Debugging: Print Sleep/Wake Status
//Uncomment in order to print out the Sleep/Wake Status
#define _DEBUG_OUTPUT_SLEEP_WAKE_STATUS_
//============End Debugging: Print Sleep/Wake Status


//============Global Declarations


//=====SW Resettable Variables (reinitialize these variables on software reset)

//Message Queues
byte pc_usb_msg_queue = CMD_TAG_NO_MSG;
byte comm_msg_queue = CMD_TAG_NO_MSG;
byte navi_msg_queue = CMD_TAG_NO_MSG;
byte auxi_msg_queue = CMD_TAG_NO_MSG;

//Flag(s) - Rover Data Channels Status
byte ch1Status = DATA_STATUS_NOT_READY;//for PC_USB
byte ch2Status = DATA_STATUS_NOT_READY;//for COMM
byte ch3Status = DATA_STATUS_NOT_READY;//for NAVI
byte ch4Status = DATA_STATUS_NOT_READY;//for AUXI

//Flag(s) - Error
byte flagSet_Error1 = _BTFG_NONE_;
//Flag(s) - Message Controls
byte flagSet_MessageControl1 = _BTFG_NONE_;
//Flag(s) - System Status 1
byte flagSet_SystemStatus1 = _BTFG_FIRST_TRANSMISSION_;//Default: Set the first transmission flag only, leave everything else unset
//Flag(s) - System Status 2
//TEMPLATE//byte flagSet_SystemStatus2 = _BTFG_NONE_;
//Flag(s) - Command Filter Options - MAIN and CMNC each have their own set since they have separate data filters

//Command Filter Options for PC_USB: Set 1
byte commandFilterOptionsSet1_PC_USB = _BTFG_NONE_;
//Command Filter Options for PC_USB: Set 2
byte commandFilterOptionsSet2_PC_USB = _BTFG_NONE_;

//Command Filter Options for COMM: Set 1
byte commandFilterOptionsSet1_COMM = _BTFG_NONE_;
//Command Filter Options for COMM: Set 2
byte commandFilterOptionsSet2_COMM = _BTFG_NONE_;

//Command Filter Options for NAVI: Set 1
byte commandFilterOptionsSet1_NAVI = _BTFG_NONE_;
//Command Filter Options for NAVI: Set 2
byte commandFilterOptionsSet2_NAVI = _BTFG_NONE_;

//Command Filter Options for AUXI: Set 1
byte commandFilterOptionsSet1_AUXI = _BTFG_NONE_;
//Command Filter Options for AUXI: Set 2
byte commandFilterOptionsSet2_AUXI = _BTFG_NONE_;




//Counters
unsigned int timeout_counter = 0; //shared counter, used to detect timeout of MAIN responding back to COMM for any reason (i.e. system go or system ready responses), used to track how long COMM has been waiting for a COMM SW Request back from MAIN, after it sent a ALL_SW_RESET_REQUEST to MAIN (which MAIN might have missed, since it's sent only once), etc. Make sure to clear it out before use and only use it for one purpose at a time.
//TEMPLATE//unsigned int transmission_delay_cnt = 0;//concurrent transmission delay counter



//------------------From CommTester_MAIN
//RoverData and RoverComms
//Ch1 is between MAIN and PC_USB
RoverData * roverDataCh1_COMM = new RoverData();
RoverComm * roverComm_Ch1 = new RoverComm(roverDataCh1_COMM);
//Ch3 is between MAIN and COMM
RoverData * roverDataCh2_COMM = new RoverData();
RoverComm * roverComm_Ch2 = new RoverComm(roverDataCh2_COMM);
//Ch3 is between MAIN and NAVI
RoverData * roverDataCh3_COMM = new RoverData();
RoverComm * roverComm_Ch3 = new RoverComm(roverDataCh3_COMM);
//Ch4 is between MAIN and AUXI
RoverData * roverDataCh4_COMM = new RoverData();
RoverComm * roverComm_Ch4 = new RoverComm(roverDataCh4_COMM);

//Rover Data Pointers for use with either internal processing or outgoing messages
RoverData * roverDataForMAIN;//pointer used access the RoverData which has the command data incoming to MAIN
RoverData * roverDataForPC_USB;//pointer used access the RoverData which has the command data outgoing to PC_USB
RoverData * roverDataForCOMM;//pointer used access the RoverData which has the command data outgoing to COMM
RoverData * roverDataForNAVI;//pointer used access the RoverData which has the command data outgoing to NAVI
RoverData * roverDataForAUXI;//pointer used access the RoverData which has the command data outgoing to AUXI




//------------------From RoverHwResetTester_MAIN
RoverHwReset * commHwResetter = new RoverHwReset(COMM_HW_RESET_CTRL_PIN);


//------------------From WakeUpTester_MAIN
RoverSleeperServer * sleeperMAIN = new RoverSleeperServer(MAIN_WAKEUP_CTRL_PIN, &InterruptDispatch_WakeUpArduino);//MAIN Wakeup Pin Control
RoverSleeperClient * sleeperAUXI = new RoverSleeperClient(AUXI_WAKEUP_CTRL_PIN);
RoverSleeperClient * sleeperNAVI = new RoverSleeperClient(NAVI_WAKEUP_CTRL_PIN);



//------------------From MotorAndServoTester_MAIN
MotorPowerControl * mtrPowerCtrlr = new MotorPowerControl(MTR_FET_CTRL_PIN, MTR_ENABLE_STATUS);
DelayCounter * midLeftSyncCounter = new DelayCounter(DELAY_200_PERIODS);//initialize it to count to 1 periods x 1ms delay timer resolution = 1ms before the count has reached flag goes true
GlobalDelayTimer * midLeftSyncTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, midLeftSyncCounter);//everytime the delay interval (resolution) is reached, it will increment the delay counter. The standard resolution used for the Rover has been 5mS so it's not too small where it has to increment the counter often, but not to big where it won't work for many different classes without being too slow or fast
DelayCounter * midRightSyncCounter = new DelayCounter(DELAY_200_PERIODS);//initialize it to count to 1 periods x 1ms delay timer resolution = 1ms before the count has reached flag goes true
GlobalDelayTimer * midRightSyncTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, midRightSyncCounter);//everytime the delay interval (resolution) is reached, it will increment the delay counter. The standard resolution used for the Rover has been 5mS so it's not too small where it has to increment the counter often, but not to big where it won't work for many different classes without being too slow or fast


//Note: Remember to update all fields of the constructor. All the fields are unique to/distinct for each motor. You can't share the counter, because it gets reset for each one. And each timer get's only one counter, so you need a timer for each one as well.
WheelEncoderSensor * wheelEncoder_MidLeft = new WheelEncoderSensor(ENCODER_A_MID_LEFT, ENCODER_B_MID_LEFT, LEFT_MOUNTED, &InterruptDispatch_wheelEncoder_MidLeft, midLeftSyncCounter);
WheelEncoderSensor * wheelEncoder_MidRight = new WheelEncoderSensor(ENCODER_A_MID_RIGHT, ENCODER_B_MID_RIGHT, RIGHT_MOUNTED, &InterruptDispatch_wheelEncoder_MidRight, midRightSyncCounter);


//WRITE ME LATER, ADD MORE LATER



//Note: Make sure to add any new objects created to this array
//Note: Declare this after SW Resettable and Non-Resettable variables, else the compiler will complain.
RoverReset * resetArray[] = {	
	roverDataCh1_COMM,
	roverComm_Ch1,
	roverDataCh2_COMM,
	roverComm_Ch2,
	roverDataCh3_COMM,
	roverComm_Ch3,
	roverDataCh4_COMM,
	roverComm_Ch4,	
	commHwResetter,
	sleeperMAIN,
	sleeperAUXI,
	sleeperNAVI,
	mtrPowerCtrlr,
	midLeftSyncCounter,
	midLeftSyncTimer,
	midRightSyncCounter,
	midRightSyncTimer,
	wheelEncoder_MidLeft,
	wheelEncoder_MidRight
//WRITE ME LATER	
};//for pointers, pass them directly, for objects pass the address


//=====End of: SW Resettable Variables




//=====Non-SW Resettable Variables (do not reinitialize these variables on software reset)


//Message Char Array
char txMsgBuffer_PC_USB[UNIV_BUFFER_SIZE];//transmit buffer for PC_USB
char txMsgBuffer_COMM[UNIV_BUFFER_SIZE];//transmit buffer for COMM (CMNC)
char txMsgBuffer_NAVI[UNIV_BUFFER_SIZE];//transmit buffer for NAVI
char txMsgBuffer_AUXI[UNIV_BUFFER_SIZE];//transmit buffer for AUXI
char programMem2RAMBuffer[_MAX_PROGMEM_BUFF_STR_LEN_];//Buffer to use for Message Strings


//Fixed Message Strings (to store in flash)
const static char msg_strg_0[] PROGMEM = "nodata";//getMsgString(0)
const static char msg_strg_1[] PROGMEM = "invlcmd";//getMsgString(1)
const static char msg_strg_2[] PROGMEM = "error";//getMsgString(2)
//Note: Make sure to update  the msg_str_table[] array

//Table of Fixed Commaned Strings (array of strings stored in flash)
const char* const msg_str_table[] PROGMEM = {
	msg_strg_0,
	msg_strg_1,
	msg_strg_2
};





//States //(these states will not be re-initalized in initializeVariables() as when it's SW resetted with the COMM SW Reset Request in PROCESS_DATA's commandDirector(), it will already be going to RUN_HOUSEKEEPING_TASKS afterwards)
byte currentState = RUN_HOUSEKEEPING_TASKS;
byte nextState = RUN_HOUSEKEEPING_TASKS;
byte queuedState = RUN_HOUSEKEEPING_TASKS;

//Modes //(this mode will not be re-initalized in initializeVariables() as they're set by the state machine when being SW resetted)
byte currentMode = POWER_ON_AND_HW_RESET;





//=====End of: Non-SW Resettable Variables






//============End of Global Declarations



void setup() {


	//resetting all objects in this sketch
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		if (!resetArray[i] == NULL)//if the object isn't null
		{
			resetArray[i]->reset();//reset the object	
		}//end if
	}//end for


	 //Serial Communications
//WRITE ME LATER

	//Setting Up Timer Interrupt
	OCR0A = 0x7F;//Set the timer to interrupt somewhere in the middle of it's count, say 127 aka 7F in hex (since Timer0 is 8 bit and counts from 0 to 255)
	TIMSK0 |= _BV(OCIE0A);//Activating the Timer Interrupt by setting the Mask Register
						  /*
						  Reference:
						  https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers
						  http://forum.arduino.cc/index.php?topic=3240.0
						  https://protostack.com.au/2010/09/timer-interrupts-on-an-atmega168/
						  */


}//end of setup()



SIGNAL(TIMER0_COMPA_vect)//Interrupt Service Routine
{
	//Tasks always running in the background, called by the timer about every 1 ms
	//This will allow the millis value to be checked every millisecond and not get missed.
	//Timer(s)
	midLeftSyncTimer->Running();
	midRightSyncTimer->Running();
//WRITE ME LATER

}





void loop() {


	

	//State Machine
	switch (currentState)
	{
		case RUN_HOUSEKEEPING_TASKS:
			_PRINT_STATE_(F("STATE: RUN_HOUSEKEEPING_TASKS"));

			switch (currentMode)
			{
				case POWER_ON_AND_HW_RESET:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					queuedState = RUN_HOUSEKEEPING_TASKS;//Set next aka queued state (since in RUN_HOUSEKEEPING_TASKS) to: RUN_HOUSEKEEPING_TASKS
					currentMode = INITIALIZATION;//Set mode to INITIALIZATION *begin*				
					runModeFunction_POWER_ON_AND_HW_RESET(currentState);
					break;
				case INITIALIZATION:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					queuedState = RX_COMMUNICATIONS;// Set next state to RX_COMMUNICATIONS
					currentMode = SYNCHRONIZATION;//Set mode to SYNCHRONIZATION *begin*
					runModeFunction_INITIALIZATION(currentState);
					break;
				case SYNCHRONIZATION:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					//Keep the queuedState the same (unchanged)
					//Keep the currentMode the same (unchanged)				
					runModeFunction_SYNCHRONIZATION(currentState);
					break;
				case NORMAL_OPERATIONS:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					//Keep the queuedState the same (unchanged)
					//Keep the currentMode the same (unchanged)
					runModeFunction_NORMAL_OPERATIONS(currentState);
					break;
				case HW_RESETTING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					//Keep the queuedState the same (unchanged)
					//Keep the currentMode the same (unchanged)
					runModeFunction_HW_RESETTING(currentState);				
					break;
				case SYSTEM_SLEEPING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					//Keep the queuedState the same (unchanged)
					//Keep the currentMode the same (unchanged)
					runModeFunction_SYSTEM_SLEEPING(currentState);					
					break;
				case SYSTEM_WAKING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					//Keep the queuedState the same (unchanged)
					//Keep the currentMode the same (unchanged)
					runModeFunction_SYSTEM_WAKING(currentState);
					break;
				case SW_RESETTING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					//Keep the queuedState the same (unchanged)
					//Keep the currentMode the same (unchanged)
					runModeFunction_SW_RESETTING(currentState);
					break;
				case SYSTEM_ERROR:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					//Keep the queuedState the same (unchanged)
					//Keep the currentMode the same (unchanged)
					runModeFunction_SYSTEM_ERROR(currentState);
					break;
				default: //default mode
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					queuedState = CONTROL_OUTPUTS;
					currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
					runModeFunction_default();//no state needed, all states do the same thing
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
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					queuedState = DATA_VALIDATION;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYNCHRONIZATION(currentState);
					break;
				case NORMAL_OPERATIONS:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					queuedState = DATA_VALIDATION;
					//Keep the currentMode the same (unchanged)
					runModeFunction_NORMAL_OPERATIONS(currentState);
					break;
				case SYSTEM_SLEEPING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					queuedState = DATA_VALIDATION;
					//Keep the currentMode the same (unchanged)
					runModeFunction_SYSTEM_SLEEPING(currentState);
					break;
				case SW_RESETTING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					queuedState = DATA_VALIDATION;
					//Keep the currentMode the same (unchanged)
					runModeFunction_SW_RESETTING(currentState);
					break;
				case SYSTEM_ERROR:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					queuedState = DATA_VALIDATION;
					//Keep the currentMode the same (unchanged)
					runModeFunction_SYSTEM_ERROR(currentState);
					break;
				default: //default mode
					 //Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					queuedState = CONTROL_OUTPUTS;
					currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
					runModeFunction_default();//no state needed, all states do the same thing
					break;
			}//end switch			
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state
			break;
		case DATA_VALIDATION:
			_PRINT_STATE_(F("STATE: DATA_VALIDATION"));
			switch (currentMode)
			{
				case SYNCHRONIZATION:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes					
					queuedState = DATA_FILTER;
					//Keep the currentMode the same (unchanged)						
					runModeFunction_SYNCHRONIZATION(currentState);
					break;
				case NORMAL_OPERATIONS:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes					
					queuedState = DATA_FILTER;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_NORMAL_OPERATIONS(currentState);
					break;
				case SYSTEM_SLEEPING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					queuedState = DATA_FILTER;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYSTEM_SLEEPING(currentState);
					break;
				case SW_RESETTING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes					
					queuedState = DATA_FILTER;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SW_RESETTING(currentState);
					break;
				case SYSTEM_ERROR:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					queuedState = DATA_FILTER;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYSTEM_ERROR(currentState);
					break;
				default: //default mode
					 //Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					queuedState = CONTROL_OUTPUTS;
					currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
					runModeFunction_default();//no state needed, all states do the same thing
					break;
			}//end switch	
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state
			break;
		case DATA_FILTER:
			_PRINT_STATE_(F("STATE: DATA_FILTER"));
			switch (currentMode)
			{
				case SYNCHRONIZATION:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					queuedState = READ_INPUTS;//to just read motor power status
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYNCHRONIZATION(currentState);
					break;
				case NORMAL_OPERATIONS:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = READ_INPUTS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_NORMAL_OPERATIONS(currentState);
					break;
				case SYSTEM_SLEEPING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = READ_INPUTS;//to just read motor power status
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYSTEM_SLEEPING(currentState);
					break;
				case SW_RESETTING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = READ_INPUTS;//to just read motor power status
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SW_RESETTING(currentState);
					break;
				case SYSTEM_ERROR:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = READ_INPUTS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYSTEM_ERROR(currentState);
					break;
				default: //default mode
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = CONTROL_OUTPUTS;
					currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
					runModeFunction_default();//no state needed, all states do the same thing
					break;
			}//end switch	
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state
			break;
		case READ_INPUTS:
			_PRINT_STATE_(F("STATE: READ_INPUTS"));
			switch (currentMode)
			{
				case SYNCHRONIZATION:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					queuedState = PROCESS_DATA;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYNCHRONIZATION(currentState);
					break;
				case NORMAL_OPERATIONS:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = PROCESS_DATA;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_NORMAL_OPERATIONS(currentState);
					break;
				case SYSTEM_SLEEPING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = PROCESS_DATA;//to just read motor power status
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYSTEM_SLEEPING(currentState);
					break;		
				case SW_RESETTING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = PROCESS_DATA;//to just read motor power status
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SW_RESETTING(currentState);
					break;			
				case SYSTEM_ERROR:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = PROCESS_DATA;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYSTEM_ERROR(currentState);
					break;
				default: //default mode
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = CONTROL_OUTPUTS;
					currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
					runModeFunction_default();//no state needed, all states do the same thing
					break;
			}//end switch	
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state		
			break;
		case PROCESS_DATA:
			_PRINT_STATE_(F("STATE: PROCESS_DATA"));
			switch (currentMode)
			{
				case SYNCHRONIZATION:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = CREATE_DATA;//Default Next State. This may be overriden by the runModeFunction...()
					currentMode = SYNCHRONIZATION;//Default Next Mode. This may be overriden by the runModeFunction...()
					runModeFunction_SYNCHRONIZATION(currentState);
					break;
				case NORMAL_OPERATIONS:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = CONTROL_OUTPUTS;//Default Next State. This may be overriden by the runModeFunction...()
					currentMode = NORMAL_OPERATIONS;//Default Next Mode. This may be overriden by the runModeFunction...()
					runModeFunction_NORMAL_OPERATIONS(currentState);
					break;
				case SYSTEM_SLEEPING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = CONTROL_OUTPUTS;//Default Next State. This may be overriden by the runModeFunction...()
					currentMode = SYSTEM_SLEEPING;//Default Next Mode. This may be overriden by the runModeFunction...()
					runModeFunction_SYSTEM_SLEEPING(currentState);
					break;
				case SW_RESETTING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = CONTROL_OUTPUTS;//Default Next State. This may be overriden by the runModeFunction...()
					currentMode = SW_RESETTING;//Default Next Mode. This may be overriden by the runModeFunction...()
					runModeFunction_SW_RESETTING(currentState);
					break;
				case SYSTEM_ERROR:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = CONTROL_OUTPUTS;//Default Next State. This may be overriden by the runModeFunction...()
					currentMode = SYSTEM_ERROR;//Default Next Mode. This may be overriden by the runModeFunction...()
					runModeFunction_SYSTEM_ERROR(currentState);
					break;
				default: //default mode
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = CONTROL_OUTPUTS;
					currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
					runModeFunction_default();//no state needed, all states do the same thing
					break;
			}//end switch	
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state
			break;
		case CONTROL_OUTPUTS:
			_PRINT_STATE_(F("STATE: CONTROL_OUTPUTS"));
			switch (currentMode)
			{
				case NORMAL_OPERATIONS:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = CREATE_DATA;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_NORMAL_OPERATIONS(currentState);
					break;
				case HW_RESETTING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = CREATE_DATA;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_HW_RESETTING(currentState);
					break;
				case SYSTEM_SLEEPING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = CREATE_DATA;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYSTEM_SLEEPING(currentState);
					break;
				case SYSTEM_WAKING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = RX_COMMUNICATIONS;
					currentMode = SYNCHRONIZATION;//Set mode to SYNCHRONIZATION *begin*				
					runModeFunction_SYSTEM_SLEEPING(currentState);
					break;
				case SW_RESETTING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = CREATE_DATA;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SW_RESETTING(currentState);
					break;
				case SYSTEM_ERROR:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = CREATE_DATA;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYSTEM_ERROR(currentState);
					break;
				default: //default mode
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = CONTROL_OUTPUTS;
					currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
					runModeFunction_default();//no state needed, all states do the same thing
					break;
			}//end switch	
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state
			break;
		case CREATE_DATA:
			_PRINT_STATE_(F("STATE: CREATE_DATA"));
			switch (currentMode)
			{
				case SYNCHRONIZATION:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = TX_COMMUNICATIONS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYNCHRONIZATION(currentState);
					break;
				case NORMAL_OPERATIONS:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = TX_COMMUNICATIONS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_NORMAL_OPERATIONS(currentState);
					break;
				case SYSTEM_SLEEPING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = TX_COMMUNICATIONS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYSTEM_SLEEPING(currentState);
					break;
				case SW_RESETTING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = TX_COMMUNICATIONS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SW_RESETTING(currentState);
					break;
				case SYSTEM_ERROR:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = TX_COMMUNICATIONS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYSTEM_ERROR(currentState);
					break;
				default: //default mode
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = CONTROL_OUTPUTS;
					currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
					runModeFunction_default();//no state needed, all states do the same thing
					break;
			}//end switch	
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state
			break;
		case TX_COMMUNICATIONS:
			_PRINT_STATE_(F("STATE: TX_COMMUNICATIONS"));
			switch (currentMode)
			{
				case SYNCHRONIZATION:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = RX_COMMUNICATIONS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYNCHRONIZATION(currentState);
					break;
				case NORMAL_OPERATIONS:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = RX_COMMUNICATIONS;//Default Next State. This may be overriden by the runModeFunction...()
					//Keep the currentMode the same (unchanged)	
					runModeFunction_NORMAL_OPERATIONS(currentState);
					break;
				case SYSTEM_SLEEPING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = RX_COMMUNICATIONS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYSTEM_SLEEPING(currentState);
					break;
				case SW_RESETTING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = RX_COMMUNICATIONS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SW_RESETTING(currentState);
					break;
				case SYSTEM_ERROR:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = RX_COMMUNICATIONS;//Default Next State. This may be overriden by the runModeFunction...()
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYSTEM_ERROR(currentState);				
					break;
				default: //default mode
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = CONTROL_OUTPUTS;
					currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
					runModeFunction_default();//no state needed, all states do the same thing
					break;
			}//end switch	
			
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state
			
			break;
		default: //default state
			_PRINT_STATE_(F("STATE: default"));
			//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes							
			queuedState = CONTROL_OUTPUTS;
			currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state
			runModeFunction_default();//no state needed, all states do the same thing
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
//PLACEHOLDER: Add things here as needed.

}//runPORTasks()
void initializeVariables()
{
	//(re)initialize most global variables (i.e. for software reset)

//WRITE ME LATER

} //end of initializeVariables()
void startBackgroundTasks()
{
	//start background tasks
//PLACEHOLDER: Add things here as needed.
}//end of startBackgroundTasks()
void runBackgroundTasks()
{
	//run background tasks	
	
	//Wheel Encoders
	wheelEncoder_MidLeft->sensorOnline();
	wheelEncoder_MidRight->sensorOnline();
	
}//end of runBackgroundTasks()
byte rxData(RoverComm * roverComm, byte roverCommType) {

	byte counter;
	byte dataStatus = DATA_STATUS_NOT_READY;

	//Note: Make sure parseAndValidateData() is called between (before, after, or in) successive rxData() function calls, as it will clear the string and reset the index (required for the code to work properly)
	if ( roverCommType == ROVERCOMM_PC_USB )
	{
		if (_PC_USB_SERIAL_.available() > 1)
		{
			//initialize the counter
			counter = 0;
			while (_PC_USB_SERIAL_.available() > 0 && counter <= ROVER_COMM_SENTENCE_LENGTH)//while there is data on the Serial RX Buffer and the length is not over the max GPS sentence length
			{
				//Read one character of serial data at a time
				//Note: Must type cast the Serial.Read to a char since not saving it to a char type first.
				roverComm->appendToRxData((char)_PC_USB_SERIAL_.read());//construct the string one char at a time
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
	else if ( roverCommType == ROVERCOMM_COMM )
	{
		if (_COMM_SERIAL_.available() > 1)
		{
			//initialize the counter
			counter = 0;
			while (_COMM_SERIAL_.available() > 0 && counter <= ROVER_COMM_SENTENCE_LENGTH)//while there is data on the Serial RX Buffer and the length is not over the max GPS sentence length
			{
				//Read one character of serial data at a time
				//Note: Must type cast the Serial.Read to a char since not saving it to a char type first
				roverComm->appendToRxData((char)_COMM_SERIAL_.read());//construct the string one char at a time
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
	else if ( roverCommType == ROVERCOMM_NAVI )
	{
		if (_NAVI_SERIAL_.available() > 1)
		{
			//initialize the counter
			counter = 0;
			while (_NAVI_SERIAL_.available() > 0 && counter <= ROVER_COMM_SENTENCE_LENGTH)//while there is data on the Serial RX Buffer and the length is not over the max GPS sentence length
			{
				//Read one character of serial data at a time
				//Note: Must type cast the Serial.Read to a char since not saving it to a char type first
				roverComm->appendToRxData((char)_NAVI_SERIAL_.read());//construct the string one char at a time
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
	else if ( roverCommType == ROVERCOMM_AUXI )
	{
		if (_AUXI_SERIAL_.available() > 1)
		{
			//initialize the counter
			counter = 0;
			while (_AUXI_SERIAL_.available() > 0 && counter <= ROVER_COMM_SENTENCE_LENGTH)//while there is data on the Serial RX Buffer and the length is not over the max GPS sentence length
			{
				//Read one character of serial data at a time
				//Note: Must type cast the Serial.Read to a char since not saving it to a char type first
				roverComm->appendToRxData((char)_AUXI_SERIAL_.read());//construct the string one char at a time
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

void dataDirector(RoverData * roverData, byte redirectOption, byte &flagSet, byte flagOfInterest)
{

	//Note: This function varies for different Arduinos


	BooleanBitFlags::clearFlagBit(flagSet, flagOfInterest);//initialize flag to false

	byte roverCommType = roverData->getDestinationCommType();//get the roverComm Destination

	if (roverCommType == ROVERCOMM_MAIN)//if the data is for this Arduino unit
	{
		//if the data is for this unit, MAIN
		BooleanBitFlags::setFlagBit(flagSet, flagOfInterest);//set the status such that the data was for this unit, MAIN
		//process it back in the main loop (to prevent software stack from being too deep)
	}//end if
	 //else check to see if the data was for other cases
	else if (redirectOption == DATA_REDIRECT_ENABLED)
	{
		if (roverCommType == ROVERCOMM_PC_USB)
		{
			//if the data is for PC_USB, transmit the data out from MAIN to PC_USB
			//Set redirect to PC_USB flag to true			
			BooleanBitFlags::setFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_PC_USB_);
		}//end else if	
		else if (roverCommType == ROVERCOMM_COMM)
		{
			//if the data is for COMM, transmit the data out from MAIN to COMM
			//Set redirect to COMM flag to true			
			BooleanBitFlags::setFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_COMM_);
		}//end else if
		else if (roverCommType == ROVERCOMM_NAVI)
		{
			//if the data is for NAVI, transmit the data out from MAIN to NAVI
			//Set redirect to NAVI flag to true			
			BooleanBitFlags::setFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_NAVI_);
		}//end else if
		else if (roverCommType == ROVERCOMM_AUXI)
		{
			//if the data is for AUXI, transmit the data out from MAIN to AUXI
			//Set redirect to AUXI flag to true			
			BooleanBitFlags::setFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_AUXI_);
		}//end else if		
		 //else the command type is ROVERCOMM_NONE
		 //invalid RoverComm Type, so do nothing		
	}//end if
	 //else the data was not for this local unit, and/or redirect was disabled, so do nothing

	return;
	
}//end of dataDirector()

void txData(char * txData, byte roverCommType)
{
	//Note: This function varies for different Arduinos
	if (roverCommType == ROVERCOMM_PC_USB)
	{
		//transmit the data to PC_USB
		_PC_USB_SERIAL_.println(txData);
	}//end if
	else if (roverCommType == ROVERCOMM_COMM)
	{
		//transmit the data to COMM
		_COMM_SERIAL_.println(txData);
	}//end else if
	else if (roverCommType == ROVERCOMM_NAVI)
	{
		//transmit the data to NAVI
		_NAVI_SERIAL_.println(txData);
	}//end else if
	else if (roverCommType == ROVERCOMM_AUXI)
	{
		//transmit the data to AUXI
		_AUXI_SERIAL_.println(txData);
	}//end else if
	else
	{
		//do nothing
	}//end else
}//end of txData()

void commandDirector(RoverData * roverDataPointer, byte roverComm)
{
//LEFT OFF HERE
//WRITE ME LATER



//TEMPLATE FOR System Ready

	

			//Check to see if all systems are ready for systems go		
			//the status for a particular arduino (i.e. navi_system_ready fpr NAVI) would be set true when the system ready msg was received for that arduino
			if( BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_COMM_SYSTEM_READY_) && BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_NAVI_SYSTEM_READY_) && BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_AUXI_SYSTEM_READY_) )
			{
				comm_msg_queue = CMD_TAG_SYSTEM_GO_STATUS;
				navi_msg_queue = CMD_TAG_SYSTEM_GO_STATUS;				
				auxi_msg_queue = CMD_TAG_SYSTEM_GO_STATUS;
				BooleanBitFlags::setFlagBit(flagSet_SystemStatus1, _BTFG_ALL_SYSTEMS_GO_);
				currentMode = NORMAL_OPERATIONS;//Set mode to NORMAL_OPERATIONS *begin*				
			}//end if
//END OF TEMPLATE			
			
			
}//end of commandDirector()
void createDataFromQueueFor(byte roverCommDestination)
{
//WRITE ME LATER
//LEFT OFF HERE

}//end of createDataFromQueueFor()
void setAllErrorFlagsTo(boolean choice)
{
//WRITE ME LATER
}//end of setAllErrorFlagsTo()
void setAllMessageControlFlagsTo(boolean choice)
{
//WRITE ME LATER
}//end of setAllMessageControlFlagsTo()
void setAllSystemStatusFlagsTo(boolean choice)
{
//WRITE ME LATER
}//end of setAllSystemStatusFlagsTo()
void setAllCommandFiltersTo(boolean choice, byte roverComm)
{
	//Note: Right now this function doesn't discriminate where the commands are coming from. So if they're all set to true, in theory, for example CMNC can "inject" or "spoof" a command that looks like it's coming from somewhere else.
	//This is a bug that can be fixed later if needed. Keeping it simple for now.

	if(roverComm == ROVERCOMM_PC_USB)
	{
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_COMMHWRESETREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SWRESETACKNOWLEDGMENT_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_ALLSLEEPREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SLEEPREQUESTACKNOWLEDGEMENT_, choice);
		
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORPOWERENABLE_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_MOTORPOWERSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_MIDRIGHTENCODERSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_MIDLEFTENCODERSTATUS_, choice);
		
	}//end if
	else if(roverComm == ROVERCOMM_COMM)
	{
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_COMMHWRESETREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_SWRESETACKNOWLEDGMENT_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_ALLSLEEPREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_SLEEPREQUESTACKNOWLEDGEMENT_, choice);
		
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORPOWERENABLE_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_MOTORPOWERSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_MIDRIGHTENCODERSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_MIDLEFTENCODERSTATUS_, choice);
		
	}//end else if
	else if(roverComm == ROVERCOMM_NAVI)
	{
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_COMMHWRESETREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_SWRESETACKNOWLEDGMENT_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_ALLSLEEPREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_SLEEPREQUESTACKNOWLEDGEMENT_, choice);
		
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORPOWERENABLE_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_MOTORPOWERSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_MIDRIGHTENCODERSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_MIDLEFTENCODERSTATUS_, choice);
		
	}//end else if	
	else if(roverComm == ROVERCOMM_AUXI)
	{
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_COMMHWRESETREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_SWRESETACKNOWLEDGMENT_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_ALLSLEEPREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_SLEEPREQUESTACKNOWLEDGEMENT_, choice);
		
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORPOWERENABLE_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_MOTORPOWERSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_MIDRIGHTENCODERSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_MIDLEFTENCODERSTATUS_, choice);
		
	}//end else if		
		
}//end of setAllCommands()
void redirectData(RoverComm * roverComm)
{
//WRITE ME LATER
}//End of redirectData()


//====End of: Misc Functions


//====Mode Functions

void runModeFunction_POWER_ON_AND_HW_RESET(byte currentState)
{
	_PRINT_MODE_(F("MODE: POWER_ON_AND_HW_RESET"));
	switch (currentState)
	{
		case RUN_HOUSEKEEPING_TASKS: //Mode: POWER_ON_AND_HW_RESET
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
		case RUN_HOUSEKEEPING_TASKS: //Mode: INITIALIZATION
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
		case RUN_HOUSEKEEPING_TASKS: //Mode: SYNCHRONIZATION
			runBackgroundTasks();
			break;
		case RX_COMMUNICATIONS: //Mode: SYNCHRONIZATION

			//rxData() from PC_USB
			//1. Reset status flag
			ch1Status = DATA_STATUS_NOT_READY;
			//2. Clear all Rx'ed data before getting new data				
			roverComm_Ch1->clearRxData();
			//3. Receive data
			ch1Status = rxData(roverComm_Ch1, ROVERCOMM_PC_USB);//Note: this is a local .ino function

			//rxData() from COMM
			//1. Reset status flag
			ch2Status = DATA_STATUS_NOT_READY;
			//2. Clear all Rx'ed data before getting new data				
			roverComm_Ch2->clearRxData();
			//3. Receive data
			ch2Status = rxData(roverComm_Ch2, ROVERCOMM_COMM);//Note: this is a local .ino function
			
			//rxData() from NAVI
			//1. Reset status flag
			ch3Status = DATA_STATUS_NOT_READY;
			//2. Clear all Rx'ed data before getting new data				
			roverComm_Ch3->clearRxData();
			//3. Receive data
			ch3Status = rxData(roverComm_Ch3, ROVERCOMM_NAVI);//Note: this is a local .ino function

			//rxData() from AUXI
			//1. Reset status flag
			ch4Status = DATA_STATUS_NOT_READY;
			//2. Clear all Rx'ed data before getting new data				
			roverComm_Ch4->clearRxData();
			//3. Receive data
			ch4Status = rxData(roverComm_Ch4, ROVERCOMM_AUXI);//Note: this is a local .ino function
	
			break;
		case DATA_VALIDATION: //Mode: SYNCHRONIZATION

			//parseAndValidateData() from PC_USB
			//Process/validate the data that was received
			if (ch1Status == DATA_STATUS_READY)
			{
				//If the data is valid, set the status as such
				if (roverComm_Ch1->parseAndValidateData())
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


			//parseAndValidateData() from COMM
			//Process/validate the data that was received
			if (ch2Status == DATA_STATUS_READY)
			{
				//If the data is valid, set the status as such
				if (roverComm_Ch2->parseAndValidateData())
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

			 //parseAndValidateData() from NAVI
			//Process/validate the data that was received
			if (ch3Status == DATA_STATUS_READY)
			{
				//If the data is valid, set the status as such
				if (roverComm_Ch3->parseAndValidateData())
				{
					ch3Status = DATA_STATUS_VALID;//if data is valid once it's validated, set the flag
				}//end if
				 //Else the data is invalid, so set the status as such
				else
				{
					ch3Status = DATA_STATUS_INVALID;
				}//end else
			}//end if
			 //Else, since the data isn't ready, leave the status as DATA_STATUS_NOT_READY

			//parseAndValidateData() from AUXI
			//Process/validate the data that was received
			if (ch4Status == DATA_STATUS_READY)
			{
				//If the data is valid, set the status as such
				if (roverComm_Ch4->parseAndValidateData())
				{
					ch4Status = DATA_STATUS_VALID;//if data is valid once it's validated, set the flag
				}//end if
				 //Else the data is invalid, so set the status as such
				else
				{
					ch4Status = DATA_STATUS_INVALID;
				}//end else
			}//end if
			 //Else, since the data isn't ready, leave the status as DATA_STATUS_NOT_READY


		
		
			break;		
		case DATA_FILTER: //Mode: SYNCHRONIZATION

			//Reset/clear flags (no data was for MAIN)
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH1_);
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH2_);
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH3_);
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH4_);
			
			//Reset/Clear redirect to CMNC and redirect to MAIN flags (no redirection needed). They will then be set by any of the calls to dataDirector if there is redirection required from the Arduinos, correspondingly.
			//A bit redundant since this will be cleared again after data transmission. But it's better safe than sorry.
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl1, _BTFG_REDIRECT_TO_PC_USB_);
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl1, _BTFG_REDIRECT_TO_COMM_);
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl1, _BTFG_REDIRECT_TO_NAVI_);
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl1, _BTFG_REDIRECT_TO_AUXI_);
			
			//Set Command Filter Options
			//First initialize all command choices to false
			setAllCommandFiltersTo(false, ROVERCOMM_PC_USB);//for PC_USB
			setAllCommandFiltersTo(false, ROVERCOMM_COMM);//for COMM
			setAllCommandFiltersTo(false, ROVERCOMM_NAVI);//for NAVI
			setAllCommandFiltersTo(false, ROVERCOMM_AUXI);//for AUXI
			//Then enable the allowed commands for this mode:
			//For PC_USB
			//No filter on PC_USB data. (Allow all data from PC_USB)
			//No commands from PC_USB are filtered, so set all to true.
			setAllCommandFiltersTo(true, ROVERCOMM_PC_USB);			
			//For COMM
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_COMMHWRESETREQUEST_);	
			//For NAVI			
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_);	
			//For AUXI
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_);	

			
			//Transmit data and/or execute command
						
			//For data from PC_USB, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, MAIN
			if (ch1Status == DATA_STATUS_VALID)
			{
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//No redirections in SYNCHRONIZATION.
				//Note: this is a local .ino function

				dataDirector(roverDataCh1_COMM, DATA_REDIRECT_DISABLED, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH1_);//DataDirection will set the "data was for MAIN flag" to true if it was for this Arduino

				/*
				Allow all data from PC_USB.
				*/

			}//end if

			//For data from COMM, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, MAIN
			if (ch2Status == DATA_STATUS_VALID)
			{
			
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//No redirections in SYNCHRONIZATION.
				//Note: this is a local .ino function

				dataDirector(roverDataCh2_COMM, DATA_REDIRECT_DISABLED, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH2_);//DataDirection will set the "data was for MAIN flag" to true if it was for this Arduino
				
				/*
				Set filter to throw away all COMM data except:
				system ready message(s) from COMM	
				All SW Reset Request from COMM/CMNC (to restart the SW reset process again)				
				comm hw reset request message(s), from COMM (used to hw reset the COMM after the COMM has hw reset MAIN, NAVI, and AUXI)
				*/				

			}//end if
			
			//For data from NAVI, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, MAIN
			if (ch3Status == DATA_STATUS_VALID)
			{
			
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//No redirections in SYNCHRONIZATION.
				//Note: this is a local .ino function

				dataDirector(roverDataCh3_COMM, DATA_REDIRECT_DISABLED, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH3_);//DataDirection will set the "data was for MAIN flag" to true if it was for this Arduino
				
				/*
				Set filter to throw away all NAVI data except:
				system ready message(s) from NAVI
				*/		
				
			}//end if
			
			
			//For data from AUXI, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, MAIN
			if (ch4Status == DATA_STATUS_VALID)
			{
			
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//No redirections in SYNCHRONIZATION.
				//Note: this is a local .ino function

				dataDirector(roverDataCh4_COMM, DATA_REDIRECT_DISABLED, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH4_);//DataDirection will set the "data was for MAIN flag" to true if it was for this Arduino
				
				/*
				Set filter to throw away all AUXI data except:
				system ready message(s) from AUXI
				*/			
				
			}//end if				

			break;	
		case READ_INPUTS: //Mode: SYNCHRONIZATION
			//Skip Encoders
			//Read Motor Power Status
			if (mtrPowerCtrlr->motorIsOn())//if motor is currently on
			{
				BooleanBitFlags::setFlagBit(flagSet_SystemStatus1, _BTFG_MTR_POWER_ON_);
				//Note: The motor power status flag will be cleared after the CREATE_DATA state.
			}//end if
			else
			{
				BooleanBitFlags::clearFlagBit(flagSet_SystemStatus1, _BTFG_MTR_POWER_ON_);
			}//end else
			break;	
		case PROCESS_DATA: //Mode: SYNCHRONIZATION

			#ifdef _DEBUG_PRINT_TIMEOUT_COUNTER_VALUE_
				Serial.println(timeout_counter);//DEBUG
			#endif
			
			//Skip Encoders
			//Motor Power Status: When applicable, the Motor Power Status is captured in READ_INPUTS with a flag, the message is queued up by commandDirector of PROCESS_DATA, and then processed in CREATE_DATA with createDataFromQueueFor, then the flag is cleared.
						
			
			//Run lower priority functions here.
			//These messages and flags may be overrided with commandDirector()			
			
			#ifndef _DEBUG_TURN_OFF_SYSTEM_READY_STATUS //normally the comm_msg_queue, navi_msg_queue, and/or auxi_msg_queue will send the CMD_TAG_SYSTEM_READY_STATUS. Can disable it for debugging purposes
				//check each arduino to see which isn't ready yet and keep having it send out system ready status from MAIN
				if( ! BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_COMM_SYSTEM_READY_))
				{
					comm_msg_queue = CMD_TAG_SYSTEM_READY_STATUS;
				}//end if
				if( ! BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_NAVI_SYSTEM_READY_))
				{
					navi_msg_queue = CMD_TAG_SYSTEM_READY_STATUS;				
				}//end if
				if( ! BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_AUXI_SYSTEM_READY_))
				{
					auxi_msg_queue = CMD_TAG_SYSTEM_READY_STATUS;
				}//end if		
			#endif						
			
			//Process PC_USB command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//All other messages are allowed from PC_USB. Use with caution.
				//No redirections in SYNCHRONIZATION.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH1_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh1_COMM, ROVERCOMM_PC_USB);
			}//end if			
			//Process COMM command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//Note: If system ready msg, hw reset request, or All SW Reset Request from COMM/CMNC, see "Command Options" below for more info.
				//Note: Either you should get HW or SW reset, or system ready messages from COMM. as everything else was filtered out
				//No redirections in SYNCHRONIZATION.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH2_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh2_COMM, ROVERCOMM_COMM);
			}//end if				
			//Process NAVI command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//Note: If system ready msg received from NAVI, see "Command Options" below for more info.
				//Note: Either you should get system ready messages from NAVI. as everything else was filtered out
				//No redirections in SYNCHRONIZATION.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH3_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh3_COMM, ROVERCOMM_NAVI);
			}//end if				
			//Process AUXI command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//Note: If system ready msg received from AUXI, see "Command Options" below for more info.
				//Note: Either you should get system ready messages or generic health errors from AUXI. as everything else was filtered out
				//No redirections in SYNCHRONIZATION.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH4_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh4_COMM, ROVERCOMM_AUXI);
			}//end if

							
			//Run highest priority functions here (after command director). //this will override any lower priority messages (i.e. system go). This will overwrite anything else. (i.e. system ready)
	
			//If all systems are not ready, and it's not yet a systems go
			if( ! BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_ALL_SYSTEMS_GO_) )
			{
				//increment counter
				timeout_counter++;
				//if MAIN has been stuck in SYNCHRONIZATION for a long time while waiting on NAVI, AUXI, or COMM, it will send a sync error status
				if(timeout_counter >= MAIN_SYNC_TIMEOUT_VALUE)
				{
					currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
					comm_msg_queue = CMD_TAG_SYNC_ERROR_STATUS;							
					pc_usb_msg_queue = CMD_TAG_SYNC_ERROR_STATUS;											
					//set sync_error = true
					BooleanBitFlags::setFlagBit(flagSet_Error1, _BTFG_SYNC_ERROR_);			
					//(Note: the sync_error flag can only be cleared with a sw reset or hw reset)
					//initialize/reset shared counter before use
					timeout_counter = 0;	
				}//end if
			}//end if		
			break;		
		case CREATE_DATA: //Mode: SYNCHRONIZATION
			//Creates data for PC_USB
			if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_PC_USB);
			}//end if
			//Creates data for COMM
			if (comm_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_COMM);
			}//end if
			//Creates data for NAVI
			if (navi_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_NAVI);
			}//end if
			//Creates data for AUXI
			if (auxi_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_AUXI);
			}//end if			
			//Clear Motor Power Status
			BooleanBitFlags::clearFlagBit(flagSet_SystemStatus1, _BTFG_MTR_POWER_ON_);
			break;
		case TX_COMMUNICATIONS: //Mode: SYNCHRONIZATION
			//Sends data to PC_USB
			if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
			{
				txData(txMsgBuffer_PC_USB, ROVERCOMM_PC_USB);
			}//end if
			//Sends data to COMM
			if (comm_msg_queue != CMD_TAG_NO_MSG)
			{
				txData(txMsgBuffer_COMM, ROVERCOMM_COMM);
			}//end if
			//Sends data to NAVI
			if (navi_msg_queue != CMD_TAG_NO_MSG)
			{
				txData(txMsgBuffer_NAVI, ROVERCOMM_NAVI);
			}//end if
			//Sends data to AUXI
			if (auxi_msg_queue != CMD_TAG_NO_MSG)
			{
				txData(txMsgBuffer_AUXI, ROVERCOMM_AUXI);
			}//end if
			//clears message queue(s) and redirect flags		
			pc_usb_msg_queue = CMD_TAG_NO_MSG;
			comm_msg_queue = CMD_TAG_NO_MSG;
			navi_msg_queue = CMD_TAG_NO_MSG;
			auxi_msg_queue = CMD_TAG_NO_MSG;
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl1, _BTFG_REDIRECT_TO_PC_USB_);
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl1, _BTFG_REDIRECT_TO_COMM_);
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl1, _BTFG_REDIRECT_TO_NAVI_);
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl1, _BTFG_REDIRECT_TO_AUXI_);
			//reset the first transmission flag
			BooleanBitFlags::setFlagBit(flagSet_SystemStatus1, _BTFG_FIRST_TRANSMISSION_);
			break;				
		default: //default state, if the state is not listed, it should never be called from this mode. If it does, there is a logical or programming error.
			 //This code should never execute, if it does, there is a logical or programming error
			runModeFunction_default();//no state needed, all states do the same thing
			break;
	}//end switch
}//end of runModeFunction_SYNCHRONIZATION()
void runModeFunction_NORMAL_OPERATIONS(byte currentState)
{

//LEFT OFF HERE
	_PRINT_MODE_(F("MODE: NORMAL_OPERATIONS"));
	switch (currentState)
	{
		case RUN_HOUSEKEEPING_TASKS: //Mode: NORMAL_OPERATIONS
			runBackgroundTasks();
			break;
		case RX_COMMUNICATIONS: //Mode: NORMAL_OPERATIONS
//WRITE ME LATER
			break;
		case DATA_VALIDATION: //Mode: NORMAL_OPERATIONS
//WRITE ME LATER
			break;		
		case DATA_FILTER: //Mode: NORMAL_OPERATIONS
//WRITE ME LATER
			break;	
		case READ_INPUTS: //Mode: NORMAL_OPERATIONS
//WRITE ME LATER
			break;	
		case PROCESS_DATA: //Mode: NORMAL_OPERATIONS
//WRITE ME LATER
			break;		
		case CONTROL_OUTPUTS: //Mode: NORMAL_OPERATIONS
//WRITE ME LATER
			break;		
		case CREATE_DATA: //Mode: NORMAL_OPERATIONS
//WRITE ME LATER
			break;
		case TX_COMMUNICATIONS: //Mode: NORMAL_OPERATIONS
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
		case RUN_HOUSEKEEPING_TASKS: //Mode: HW_RESETTING
			runBackgroundTasks();
			break;
		case CONTROL_OUTPUTS: //Mode: HW_RESETTING
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
		case RUN_HOUSEKEEPING_TASKS: //Mode: SYSTEM_SLEEPING
			runBackgroundTasks();
			break;
		case RX_COMMUNICATIONS: //Mode: SYSTEM_SLEEPING
//WRITE ME LATER
			break;
		case DATA_VALIDATION: //Mode: SYSTEM_SLEEPING
//WRITE ME LATER
			break;		
		case DATA_FILTER: //Mode: SYSTEM_SLEEPING
//WRITE ME LATER
			break;	
		case READ_INPUTS: //Mode: SYSTEM_SLEEPING
//WRITE ME LATER
			break;	
		case PROCESS_DATA: //Mode: SYSTEM_SLEEPING
//WRITE ME LATER
			break;		
		case CONTROL_OUTPUTS: //Mode: SYSTEM_SLEEPING
//WRITE ME LATER
			break;		
		case CREATE_DATA: //Mode: SYSTEM_SLEEPING
//WRITE ME LATER
			break;
		case TX_COMMUNICATIONS: //Mode: SYSTEM_SLEEPING
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
		case RUN_HOUSEKEEPING_TASKS: //Mode: SYSTEM_WAKING
			runBackgroundTasks();
			break;
		case CONTROL_OUTPUTS: //Mode: SYSTEM_WAKING
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
		case RUN_HOUSEKEEPING_TASKS: //Mode: SW_RESETTING
			runBackgroundTasks();
			break;
		case RX_COMMUNICATIONS: //Mode: SW_RESETTING
//WRITE ME LATER
			break;
		case DATA_VALIDATION: //Mode: SW_RESETTING
//WRITE ME LATER
			break;		
		case DATA_FILTER: //Mode: SW_RESETTING
//WRITE ME LATER
			break;	
		case READ_INPUTS: //Mode: SW_RESETTING
//WRITE ME LATER
			break;	
		case PROCESS_DATA: //Mode: SW_RESETTING
//WRITE ME LATER
			break;		
		case CONTROL_OUTPUTS: //Mode: SW_RESETTING
//WRITE ME LATER
			break;		
		case CREATE_DATA: //Mode: SW_RESETTING
//WRITE ME LATER
			break;
		case TX_COMMUNICATIONS: //Mode: SW_RESETTING
//WRITE ME LATER
			break;				
		default: //default state, if the state is not listed, it should never be called from this mode. If it does, there is a logical or programming error.
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
		case RUN_HOUSEKEEPING_TASKS: //Mode: SYSTEM_ERROR
			runBackgroundTasks();
			break;
		case RX_COMMUNICATIONS: //Mode: SYSTEM_ERROR
//WRITE ME LATER
			break;
		case DATA_VALIDATION: //Mode: SYSTEM_ERROR
//WRITE ME LATER
			break;		
		case DATA_FILTER: //Mode: SYSTEM_ERROR
//WRITE ME LATER
			break;	
		case READ_INPUTS: //Mode: SYSTEM_ERROR
//WRITE ME LATER
			break;	
		case PROCESS_DATA: //Mode: SYSTEM_ERROR
//WRITE ME LATER
			break;		
		case CONTROL_OUTPUTS: //Mode: SYSTEM_ERROR
//WRITE ME LATER
			break;		
		case CREATE_DATA: //Mode: SYSTEM_ERROR
//WRITE ME LATER
			break;
		case TX_COMMUNICATIONS: //Mode: SYSTEM_ERROR
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
//WRITE ME LATER
}//end of runStateFunction_default

 //====End of: Mode Functions
 //============End of Function Definitions






void InterruptDispatch_wheelEncoder_MidLeft() {
	wheelEncoder_MidLeft->isrUpdate();
}//emd of InterruptDispatch_wheelEncoder_MidLeft()

void InterruptDispatch_wheelEncoder_MidRight() {
	wheelEncoder_MidRight->isrUpdate();
}//end of InterruptDispatch_wheelEncoder_MidRight()

void InterruptDispatch_WakeUpArduino() {
	//Have to keep the ISR short else the program won't work
	sleeperMAIN->isrUpdate();//update the awake flag to reflect current status
}//end of InterruptDispatch_WakeUpArduino()




char * getMsgString(byte arrayIndex) {
//WRITE ME LATER
}//end of getMsgString()



void clearRoverDataPointers()
{
//WRITE ME LATER
}//end of clearRoverDataPointer()

void setRoverDataPointer(RoverData * roverDataPointer, byte roverCommType)
{
//WRITE ME LATER
}//end of setRoverDataPointer()