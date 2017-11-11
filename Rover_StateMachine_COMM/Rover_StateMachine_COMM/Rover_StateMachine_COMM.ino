/*
Note:
The best way to read this code from scratch is look at the global default values, see what state and mode the variables get on power on, then follow the state machine in the loop from the initializing state and mode
*/



/*
Design Notes:
Currently the priority level is not being used to prioritize right now. It's just there as a place holder.
*/

//Rover_StateMachine_COMM



/*
--------------------------------
Regular Operation
--------------------------------
1) MAIN sends COMM System Ready
/4c5--*005
2)  MAIN sends COMM System Go
/4c5--*006 (you might have to send it twice as the serial communication is a little glitchy)
3)
etc.
WRITE ME LATER


--------------------------------
Debug Operation
--------------------------------
//To test code, in RoverConfig uncomment _DEBUG_ALL_SERIALS_WITH_USB_SERIAL_
//To test code while in SYNCHRONIZATION mode, make sure to uncomment _DEBUG_TURN_OFF_ALL_DATA_FILTERS
//To test code and allow redirection in SYNCHRONIZATION, uncomment _DEBUG_ALLOW_REDIRECTION_CH2_IN_SYNC_MODE and _DEBUG_REDIRECTION_NOTICE


To test locally with only one Arduino (best to test the UNO to make sure it can handle the memory needs for the COMM), first make sure if _DEBUG_ALL_SERIALS_WITH_USB_SERIAL_ is uncommented in RoverConfig.h
Can send:
Hi Command
/4c5--*002<any data up to 14 chars>
/4c5--*002hiworld
Note: For this example you should get /5c400*002hiworld since now the message is coming from COMM and going to MAIN.
Bye Commands
/4c5--*003<any data up to 14 chars>
/4c5--*003bye
Note: For this example you should get /5c400*003bye since now the message is coming from COMM and going to MAIN.
Where 4 is coming from MAIN (so it can echo back with a response when using the Hi or Bye commands)
and 5 is to COMM (and not a redirection to another unit)
Can send:
/2c1--*hithere
to test redirection from NAVI (MAIN) to CMNC through COMM
and
/4c4--*hithere
to test redirection from MAIN to MAIN (loopback) through COMM
*/



//Note: To test with USB Serial for all Serial channels, go to RoverConfig and uncomment the flag _DEBUG_ALL_SERIALS_WITH_USB_SERIAL_ as long as _BTFG_COMMAND_ENABLE_OPTION_HI_ and _BTFG_COMMAND_ENABLE_OPTION_BYE_ are set true in the filter in runModeFunction_SYNCHRONIZATION()

//Configuration defines for #includes (must come before the #includes)
#ifndef _ROVER_STATES_AND_MODES
#define _ROVER_STATES_AND_MODES
#endif
#ifndef _COMMAND_CREATION_DEFINITIONS
#define _COMMAND_CREATION_DEFINITIONS //for RoverCommandDefs.h
#endif
#ifndef _ARD_4_COMM_H
#define _ARD_4_COMM_H //Must define this before calling RoverConfig.h (either directly or through another header file), define this flag to turn on COMM definitions
#endif
#ifndef _COMM_BIT_FLAGS_
#define _COMM_BIT_FLAGS_ //For RoverBitFlags.h
#endif
#ifndef _COMM_STATE_MACHINE_VARIABLES_
#define _COMM_STATE_MACHINE_VARIABLES_ //For RoverConfig.h
#endif
#ifndef _ANALOG_LED_BRIGHTNESS_SCALES_
#define _ANALOG_LED_BRIGHTNESS_SCALES_ //For RoverConfig.h
#endif


//#includes
#include <RoverStatesAndModes.h>
#include <RoverCommandDefs.h>
#include <RoverCommandCreator.h>
#include <SoftwareSerial.h>
#include <RoverData.h>
#include <RoverComm.h> //calls RoverConfig.h
#include <HeartLed.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>
#include <PirSensor.h>
#include <RoverHwReset.h>
#include <RoverSleeperServer.h>
#include <RoverSleeperClient.h>
#include <RoverConfig.h>	
#include <avr/pgmspace.h> //To store certain variables in Flash
#include <BooleanBitFlags.h>	
#include <RoverBitFlags.h>	



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
#define _SERIAL_DEBUG_CHANNEL_ _CMNC_SERIAL_
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


						  //============Debugging: Allow Redirect During Synchronization Mode
						  //Uncomment to allow Ch2 (MAIN and COMM) to have redirection when in synchronization mode
#define _DEBUG_ALLOW_REDIRECTION_CH2_IN_SYNC_MODE
//Uncomment to output notice when redirection is occuring
//#define _DEBUG_REDIRECTION_NOTICE
						  //============End Debugging: Allow Redirect During Synchronization Mode
//============Debugging: All Data Filtering Off
//Uncomment in order to allow all data to pass (turn off all data filters) for debugging)
#define _DEBUG_TURN_OFF_ALL_DATA_FILTERS
//============End Debugging: All Data Filtering Off
//============Debugging: Turn off System Ready Status During Synchronization Mode
//Uncomment in order to allow other data to be in the main_msg_queue instead of just System Status
#define _DEBUG_TURN_OFF_SYSTEM_READY_STATUS
//============End Debugging: All Data Filtering Off
//============Debugging: Print timeout counter value
//Uncomment in order to print timeout counter value
//#define _DEBUG_PRINT_TIMEOUT_COUNTER_VALUE_
//============End Debugging: Print timeout counter value
//============Debugging: Disable Comm Sync Timeout
//Uncomment in order to print timeout counter value
#define _DEBUG_DISABLE_COMM_SYNC_TIMEOUT
//============End Debugging: Print timeout counter value







						  //============TEMPORARY Global Declarations (to test to see if the program can handle the memory)

						  //STILL NEED TO INTEGRATE THIS INTO THE FULL CODE
						  //ADD ANY OBJECTS TO THE RESET ARRAY
						  //ADD ANY SW RESETTABLE VARIABLES INTO THE initializeVariables function

//------------------From PirSensorTest
PirSensor * pirSensor = new PirSensor(PIR_PIN, &InterruptDispatch1);//Note: This is my custom function and not attachInterrupt (though it calls it)
volatile boolean motionDetected;
//------------------From RoverHwResetTester_COMM
RoverHwReset * naviHwResetter = new RoverHwReset(NAVI_HW_RESET_CTRL_PIN);
RoverHwReset * auxiHwResetter = new RoverHwReset(AUXI_HW_RESET_CTRL_PIN);
RoverHwReset * mainHwResetter = new RoverHwReset(MAIN_HW_RESET_CTRL_PIN);
//------------------From WakeUpTester_COMM
//Controls the self wakeup of COMM
RoverSleeperServer * sleeperCOMM = new RoverSleeperServer(COMM_WAKEUP_CTRL_PIN, &InterruptDispatch2);//COMM Wakeup Pin Control
RoverSleeperClient * sleeperMAIN = new RoverSleeperClient(MAIN_WAKEUP_CTRL_PIN);



//============END OF TEMPORARY Global Declarations (to test to see if the program can handle the memory)






//============Global Declarations


//=====SW Resettable Variables (reinitialize these variables on software reset)

//Message Queues
byte cmnc_msg_queue = CMD_TAG_NO_MSG; // (command tag, not boolean since use by CREATE_DATA to generate messages as well as TX_COMMUNICATIONS as a flag)
byte main_msg_queue = CMD_TAG_NO_MSG; // (command tag, not boolean since use by CREATE_DATA to generate messages as well as TX_COMMUNICATIONS as a flag)

									  //Flag(s) - Rover Data Channels Status
byte ch1Status = DATA_STATUS_NOT_READY;//for PC USB/CNMC
byte ch2Status = DATA_STATUS_NOT_READY;//for MAIN

									   //Flag(s) - Error
byte flagSet_Error = _BTFG_NONE_;
//Flag(s) - Message Controls
byte flagSet_MessageControl = _BTFG_NONE_;
//Flag(s) - System Status
byte flagSet_SystemStatus = _BTFG_FIRST_TRANSMISSION_;//Default: Set the first transmission flag only, leave everything else unset
//Flag(s) - Command Filter Options - MAIN and CMNC each have their own set since they have separate data filters
//Command Filter Options for CMNC: Set 1
byte commandFilterOptionsSet1_CMNC = _BTFG_NONE_;
//Command Filter Options for CMNC: Set 2
byte commandFilterOptionsSet2_CMNC = _BTFG_NONE_;
//Command Filter Options for MAIN: Set 1
byte commandFilterOptionsSet1_MAIN = _BTFG_NONE_;
//Command Filter Options for MAIN: Set 2
byte commandFilterOptionsSet2_MAIN = _BTFG_NONE_;

//Counters
unsigned int timeout_counter = 0; //shared counter, used to detect timeout of MAIN responding back to COMM for any reason (i.e. system go or system ready responses), used to track how long COMM has been waiting for a COMM SW Request back from MAIN, after it sent a ALL_SW_RESET_REQUEST to MAIN (which MAIN might have missed, since it's sent only once), etc. Make sure to clear it out before use and only use it for one purpose at a time.
unsigned int transmission_delay_cnt = 0;//concurrent transmission delay counter






										//Command Parsers
										//Rover Data Pointers for use with either internal processing or outgoing messages
RoverData * roverDataForCOMM;//pointer used access the RoverData which has the command data incoming to COMM
RoverData * roverDataForCMNC;//pointer used access the RoverData which has the command data outgoing to CMNC
RoverData * roverDataForMAIN;//pointer used access the RoverData which has the command data outgoing to MAIN

//------------------From AnalogLedTester
DelayCounter * heartLedCounter = new DelayCounter(DELAY_10_PERIODS);//initialize it to count to 10 periods, though can pass anything here as the heart led will automatically set it to the number of short delay periods (that is also passed to it as DELAY_10_PERIODS) anyways.
HeartLed * heartLed = new HeartLed(HEART_LED_PIN, heartLedCounter, DELAY_10_PERIODS, DELAY_80_PERIODS);
GlobalDelayTimer * heartLedTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, heartLedCounter);



							 //=====End of: SW Resettable Variables




							 //=====Non-SW Resettable Variables (do not reinitialize these variables on software reset)

							 //Software Serial
#ifndef _DEBUG_ALL_SERIALS_WITH_USB_SERIAL_ //where this debug flag is controlled in RoverConfig.h
SoftwareSerial _MAIN_SWSERIAL_(COMM_SW_UART_RX_PIN, COMM_SW_UART_TX_PIN);
#endif

//Message Char Array
char txMsgBuffer_CMNC[UNIV_BUFFER_SIZE];//transmit buffer for CMNC
char txMsgBuffer_MAIN[UNIV_BUFFER_SIZE];//transmit buffer for MAIN
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



//Rover Data and COMMs
//RoverData pointers and RoverComms
//Ch1 is between CMNC and COMM
RoverData * roverDataCh1_COMM = new RoverData();
RoverComm * roverComm_Ch1 = new RoverComm(roverDataCh1_COMM);
//Ch2 is between COMM and MAIN
RoverData * roverDataCh2_COMM = new RoverData();
RoverComm * roverComm_Ch2 = new RoverComm(roverDataCh2_COMM);



//States //(these states will not be re-initalized in initializeVariables() as when it's SW resetted with the COMM SW Reset Request in PROCESS_DATA's commandDirector(), it will already be going to RUN_HOUSEKEEPING_TASKS afterwards)
byte currentState = RUN_HOUSEKEEPING_TASKS;
byte nextState = RUN_HOUSEKEEPING_TASKS;
byte queuedState = RUN_HOUSEKEEPING_TASKS;

//Modes //(this mode will not be re-initalized in initializeVariables() as they're set by the state machine when being SW resetted)
byte currentMode = POWER_ON_AND_HW_RESET;





//=====End of: Non-SW Resettable Variables





//Note: Make sure to add any new objects created to this array
//Note: Declare this after SW Resettable and Non-Resettable variables, else the compiler will complain.
RoverReset * resetArray[] = {
	heartLedCounter,
	heartLed,
	heartLedTimer,
	pirSensor,
	naviHwResetter,
	auxiHwResetter,
	mainHwResetter,
	sleeperCOMM,
	sleeperMAIN,
	roverDataCh1_COMM,
	roverComm_Ch1,
	roverDataCh2_COMM,
	roverComm_Ch2
};//for pointers, pass them directly, for objects pass the address



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
	 //Setup the HW_UART for communications between COMM and CMNC/PC USB
	_CMNC_SERIAL_.begin(CMNC_BAUD_RATE);
	//Setup the SW_UART for communications between COMM and MAIN
	_MAIN_SWSERIAL_.begin(MAIN_BAUD_RATE);

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

	//ADD TIMERS
	heartLedTimer->Running();

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
				case SECURING_LINK:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					//Keep the queuedState the same (unchanged)
					//Keep the currentMode the same (unchanged)
					runModeFunction_SECURING_LINK(currentState);
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
				case SECURING_LINK:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					queuedState = DATA_VALIDATION;
					//Keep the currentMode the same (unchanged)
					runModeFunction_SECURING_LINK(currentState);
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
				case SECURING_LINK:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					queuedState = DATA_FILTER;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SECURING_LINK(currentState);
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
					queuedState = PROCESS_DATA;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYNCHRONIZATION(currentState);
					break;
				case SECURING_LINK:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = READ_INPUTS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SECURING_LINK(currentState);
					break;
				case NORMAL_OPERATIONS:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = READ_INPUTS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_NORMAL_OPERATIONS(currentState);
					break;
				case SYSTEM_SLEEPING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = PROCESS_DATA;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYSTEM_SLEEPING(currentState);
					break;
				case SW_RESETTING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = PROCESS_DATA;
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
				case SECURING_LINK:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = PROCESS_DATA;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SECURING_LINK(currentState);
					break;
				case NORMAL_OPERATIONS:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = PROCESS_DATA;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_NORMAL_OPERATIONS(currentState);
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
					queuedState = CONTROL_OUTPUTS;//Default Next State. This may be overriden by the runModeFunction...()
					currentMode = SYNCHRONIZATION;//Default Next Mode. This may be overriden by the runModeFunction...()
					runModeFunction_SYNCHRONIZATION(currentState);
					break;
				case SECURING_LINK:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = CONTROL_OUTPUTS;//Default Next State. This may be overriden by the runModeFunction...()
					currentMode = SECURING_LINK;//Default Next Mode. This may be overriden by the runModeFunction...()
					runModeFunction_SECURING_LINK(currentState);
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
				case SYNCHRONIZATION:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = CREATE_DATA;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYNCHRONIZATION(currentState);
					break;
				case SECURING_LINK:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = CREATE_DATA;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SECURING_LINK(currentState);
					break;
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
					queuedState = CREATE_DATA;
					//Keep the currentMode the same (unchanged)	
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
				case SECURING_LINK:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = TX_COMMUNICATIONS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SECURING_LINK(currentState);
					break;
				case NORMAL_OPERATIONS:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = TX_COMMUNICATIONS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_NORMAL_OPERATIONS(currentState);
					break;
				case HW_RESETTING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = TX_COMMUNICATIONS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_HW_RESETTING(currentState);
					break;
				case SYSTEM_SLEEPING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = TX_COMMUNICATIONS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYSTEM_SLEEPING(currentState);
					break;
				case SYSTEM_WAKING:
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
				case SECURING_LINK:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					//FIX ME LATER					
					queuedState = RX_COMMUNICATIONS;//Default Next State. This may be overriden by the runModeFunction...()
													//Keep the currentMode the same (unchanged)	
					runModeFunction_SECURING_LINK(currentState);
					break;
				case NORMAL_OPERATIONS:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					//FIX ME LATER					
					queuedState = RX_COMMUNICATIONS;//Default Next State. This may be overriden by the runModeFunction...()
													//Keep the currentMode the same (unchanged)	
					runModeFunction_NORMAL_OPERATIONS(currentState);
					break;
				case HW_RESETTING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = TX_COMMUNICATIONS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_HW_RESETTING(currentState);
					break;
				case SYSTEM_SLEEPING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = RX_COMMUNICATIONS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYSTEM_SLEEPING(currentState);
					break;
				case SYSTEM_WAKING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = RX_COMMUNICATIONS;
					currentMode = SYNCHRONIZATION;//Set mode to SYNCHRONIZATION *begin*		
					runModeFunction_SYSTEM_WAKING(currentState);
					break;
				case SW_RESETTING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = RX_COMMUNICATIONS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SW_RESETTING(currentState);
					break;
				case SYSTEM_ERROR:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					//FIX ME LATER					
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
	//WRITE ME LATER	

}//runPORTasks()
void initializeVariables()
{
	//(re)initialize most global variables (i.e. for software reset)



	//Message Queues
	cmnc_msg_queue = CMD_TAG_NO_MSG; // (command tag, not boolean since use by CREATE_DATA to generate messages as well as TX_COMMUNICATIONS as a flag)
	main_msg_queue = CMD_TAG_NO_MSG; // (command tag, not boolean since use by CREATE_DATA to generate messages as well as TX_COMMUNICATIONS as a flag)
									 //Flag(s) - Rover Data Channels Status
	ch1Status = DATA_STATUS_NOT_READY;
	ch2Status = DATA_STATUS_NOT_READY;

	
	
	//Flag(s) - Error
	flagSet_Error = _BTFG_NONE_;//This is essential the same as calling the set all flags to function to false, but instead it's setting this flagset to _BTFG_NONE_ directly (instead of bit by bit)
	//Flag(s) - Message Controls
	flagSet_MessageControl = _BTFG_NONE_;//This is essential the same as calling the set all flags to function to false, but instead it's setting this flagset to _BTFG_NONE_ directly (instead of bit by bit)
	//Flag(s) - System Status
	flagSet_SystemStatus = _BTFG_FIRST_TRANSMISSION_;//Default: Set the first transmission flag only, leave everything else unset
	//Flag(s) - Command Filter Options
	//This is essential the same as calling the set all flags to function to false, but instead it's setting this flagset to _BTFG_NONE_ directly (instead of bit by bit)
	//Command Filter Options for CMNC: Set 1
	commandFilterOptionsSet1_CMNC = _BTFG_NONE_;
	//Command Filter Options for CMNC: Set 2
	commandFilterOptionsSet2_CMNC = _BTFG_NONE_;
	//Command Filter Options for MAIN: Set 1
	commandFilterOptionsSet1_MAIN = _BTFG_NONE_;
	//Command Filter Options for MAIN: Set 2
	commandFilterOptionsSet2_MAIN = _BTFG_NONE_;

	//Counters
	timeout_counter = 0; //shared counter, used to detect timeout of MAIN responding back to COMM for any reason (i.e. system go or system ready responses), used to track how long COMM has been waiting for a COMM SW Request back from MAIN, after it sent a ALL_SW_RESET_REQUEST to MAIN (which MAIN might have missed, since it's sent only once), etc. Make sure to clear it out before use and only use it for one purpose at a time.
	transmission_delay_cnt = 0;//concurrent transmission delay counter






							   //resetting all objects in this sketch
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		if (!resetArray[i] == NULL)//if the object isn't null
		{
			resetArray[i]->reset();//reset the object	
		}//end if
	}//end for

	clearRoverDataPointers();




} //end of initializeVariables()
void startBackgroundTasks()
{
	//start background tasks
	//WRITE ME LATER
}//end of startBackgroundTasks()
void runBackgroundTasks()
{
	//run background tasks	
}//end of runBackgroundTasks()
byte rxData(RoverComm * roverComm, byte roverCommType) {


	byte counter;
	byte dataStatus = DATA_STATUS_NOT_READY;

	//Note: Make sure parseAndValidateData() is called between (before, after, or in) successive rxData() function calls, as it will clear the string and reset the index (required for the code to work properly)
	if (roverCommType == ROVERCOMM_CMNC || roverCommType == ROVERCOMM_PC_USB)//PC_USB and CMNC are the same for the COMM Arduino. CMNC will be used most of the time, but allow ROVERCOMM_PC_USB to exist just in case debugging code is added.
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

void dataDirector(RoverData * roverData, byte redirectOption, byte &flagSet, byte flagOfInterest)
{
	//Note: This function varies for different Arduinos


	BooleanBitFlags::clearFlagBit(flagSet, flagOfInterest);//initialize flag to false

	byte roverCommType = roverData->getDestinationCommType();//get the roverComm Destination

	if (roverCommType == ROVERCOMM_COMM)
	{
		//if the data is for this unit, COMM
		BooleanBitFlags::setFlagBit(flagSet, flagOfInterest);//set the status such that the data was for this unit, COMM
															 //process it back in the main loop (to prevent software stack from being too deep)
	}//end if
	 //else check to see if the data was for other cases
	else if (redirectOption == DATA_REDIRECT_ENABLED)
	{
		if (roverCommType == ROVERCOMM_CMNC || roverCommType == ROVERCOMM_PC_USB)//PC_USB and CMNC are the same for the COMM Arduino. CMNC will be used most of the time, but allow ROVERCOMM_PC_USB to exist just in case debugging code is added.
		{
			//if the data is for CMNC, transmit the data out from COMM to CMNC
			//Set redirect to CMNC flag to true			
			BooleanBitFlags::setFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_CMNC_);
		}//end else if
		else if (roverCommType == ROVERCOMM_NAVI || roverCommType == ROVERCOMM_AUXI || roverCommType == ROVERCOMM_MAIN)
		{
			//if the data is for either NAVI, AUXI, or MAIN, transmit the data out from COMM to MAIN since COMM only can talk to MAIN and not NAVI or AUXI (and MAIN will process it accordingly or reroute it if needed)
			//Set redirect to MAIN flag to true			
			BooleanBitFlags::setFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_MAIN_);
		}//end else if
		 //else the command type is ROVERCOMM_NONE
		 //invalid RoverComm Type, so do nothing		
	}//end if
	 //else the data was not for this local unit, and redirect was disabled, so do nothing

	return;
}//end of dataDirector()

void txData(char * txData, byte roverCommType)
{
	//Note: This function varies for different Arduinos
	if (roverCommType == ROVERCOMM_CMNC || roverCommType == ROVERCOMM_PC_USB)//PC_USB and CMNC are the same for the COMM Arduino. CMNC will be used most of the time, but allow ROVERCOMM_PC_USB to exist just in case debugging code is added.
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

void commandDirector(RoverData * roverDataPointer, byte roverComm)
{

	//Note: This function varies for different Arduinos
	//Categorize all commands/data from all sources.					
	//Sort based on priority.
	//Allow for all non-conflicting commands to run.
	//Then only run the highest priority functions for COMM last, so it will overwrite anything else, right before state transition.

	
	#ifdef _DEBUG_TURN_OFF_ALL_DATA_FILTERS
		setAllCommandFiltersTo(true, ROVERCOMM_CMNC);//for CMNC
		setAllCommandFiltersTo(true, ROVERCOMM_MAIN);//for MAIN
	#endif

	byte originRoverCommType;//holds the received data's origin
	byte destinationRoverCommType;//holds the received data's destination
	byte commandTag;//holds received data's commandtag


					//Get the received data's origin and destination
	originRoverCommType = roverDataPointer->getOriginCommType();
	destinationRoverCommType = roverDataPointer->getDestinationCommType();

	//Get the command tag from the Rover Data Object
	commandTag = roverDataPointer->getCommandTag();


	//Setting the roverDataPointer in order to route where the rover command data will be routed to
	//Clears/resets all data pointers before setting them.
	clearRoverDataPointers();
	//Sets the default such that the rover command data goes to the destination of the command. If needed, this can be overwritten by the command tag if/else statements
	setRoverDataPointer(roverDataPointer, destinationRoverCommType);
	//Note: The roverDataPointer should be going to COMM (else it would have been redirected already with dataDirector).
	//However, it can be overwritten in the if/else conditions below based on the command tag for special cases like when it redirects itself to the original sender (i.e. when the command is a request for data/status, like with PIR Status request)


	//=====Non-Conflicting Functions					
	//Run lower priority functions here. (i.e. system ready msgs)
	//Example: If it's Main System Ready, and either it's from MAIN and the MAIN data filter for System Ready is set or it's from CMNC and the CMNc data filter for System Ready is set
	//Main System Ready 
	if (commandTag == CMD_TAG_SYSTEM_READY_STATUS &&
			(
				(roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_) )
				|| (roverComm == ROVERCOMM_CMNC && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_CMNC, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_))
			)
		)
	{

		//so it can stop checking for this message since the MAIN system is known to be ready
		//Set MAIN System Ready flag to true		
		BooleanBitFlags::setFlagBit(flagSet_SystemStatus, _BTFG_MAIN_SYSTEM_READY_);
		//NOTE: Since this is a non-conflicting command, if resetting the timeout_counter here causes an issue, then take that out of the code		
		timeout_counter = 0;//reset counter (for future use)		
	}//end if


	 //=====Conflicting Functions Ordered By Priority
	 //Run highest priority functions here. //this will override any lower priority messages (i.e. system go). This will overwrite anything else. (i.e. system ready)
	 //All HW Reset Request
	else if (commandTag == CMD_TAG_ALL_HW_RESET_REQUEST &&
			(
				(roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_HWRESETREQUEST_) )
				|| (roverComm == ROVERCOMM_CMNC && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_CMNC, _BTFG_COMMAND_ENABLE_OPTION_HWRESETREQUEST_))
			)
		)	 
	{
		//CHECK MY LOGIC LATER/TEST THIS CODE LATER-wrote a quick template, draft
		currentMode = HW_RESETTING;//Set mode to HW_RESETTING *begin*				
		cmnc_msg_queue = CMD_TAG_COMM_HW_RESET_REQUEST;
		main_msg_queue = CMD_TAG_HW_IS_RESETTING;
	}//end else if
	 //COMM SW Request
	else if (commandTag == CMD_TAG_COMM_SW_RESET_REQUEST &&
			(
				(roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_COMMSWRESETREQUEST_) )
				|| (roverComm == ROVERCOMM_CMNC && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_CMNC, _BTFG_COMMAND_ENABLE_OPTION_COMMSWRESETREQUEST_))
			)
		)	 	 
	{
		//CHECK MY LOGIC LATER/TEST THIS CODE LATER-wrote a quick template, draft
		currentMode = INITIALIZATION;//Set mode to INITIALIZATION *begin*	

	}//end else if
	 //ALL SW Request
	else if (commandTag == CMD_TAG_ALL_SW_RESET_REQUEST &&
			(
				(roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_) )
				|| (roverComm == ROVERCOMM_CMNC && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_CMNC, _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_))
			)
		)		 
	{

		//CHECK MY LOGIC LATER/TEST THIS CODE LATER-wrote a quick template, draft
		currentMode = SW_RESETTING;//Set mode to SW_RESETTING *begin*				
		cmnc_msg_queue = CMD_TAG_SW_IS_RESETTING;
		main_msg_queue = CMD_TAG_ALL_SW_RESET_REQUEST;
		timeout_counter = 0;//reset counter (for future use)
	}//end else if
	 //Generic Health Error
	else if (commandTag == CMD_TAG_GENERIC_HEALTH_STATUS_ERROR &&
			(
				(roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_) )
				|| (roverComm == ROVERCOMM_CMNC && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_CMNC, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_))
			)
		)		 
	{
		//CHECK MY LOGIC LATER/TEST THIS CODE LATER-wrote a quick template, draft
		currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*				
		cmnc_msg_queue = CMD_TAG_GENERIC_HEALTH_STATUS_ERROR;
		BooleanBitFlags::setFlagBit(flagSet_Error, _BTFG_GENERIC_HEALTH_ERROR_);
		//Note: the generic_health_error flag can only be cleared with a sw reset or hw reset

		timeout_counter = 0;//reset counter (for future use)
	}//end else if	
	 //System Go (from MAIN)
	else if (commandTag == CMD_TAG_SYSTEM_GO_STATUS &&
			(
				(roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMGO_) )
				|| (roverComm == ROVERCOMM_CMNC && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_CMNC, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMGO_))
			)
		)	
	{

		//Set the system go flag
		BooleanBitFlags::setFlagBit(flagSet_SystemStatus, _BTFG_MAIN_SYSTEM_GO_);
	
		//CHECK MY LOGIC LATER/TEST THIS CODE LATER-wrote a quick template, draft	
		//if for some reason the system ready message was no received before the system go message, go ahead and make it true as any system go must also mean system ready. this doesn't really matter, but just doing it for consistency since the flags are global.
		if (!BooleanBitFlags::flagIsSet(flagSet_SystemStatus, _BTFG_MAIN_SYSTEM_READY_))
		{
			//Set MAIN System Ready flag to true
			BooleanBitFlags::setFlagBit(flagSet_SystemStatus, _BTFG_MAIN_SYSTEM_READY_);
		}//end if

		if (!BooleanBitFlags::flagIsSet(flagSet_SystemStatus, _BTFG_COMMUNICATIONS_SECURE_))//it may have been true, but it went into sleep mode then woke up, so the communications should still be secure, it justs needs to sync up again
		{

			currentMode = SECURING_LINK;//Set mode to SECURING_LINK *begin*				
			cmnc_msg_queue = CMD_TAG_SECURE_LINK_REQUEST;//tells CMNC it's ready for a secure link

		}//end if
		else//the link is already secure from earlier
		{
			currentMode = NORMAL_OPERATIONS;//Set mode to NORMAL_OPERATIONS *begin*				
			cmnc_msg_queue = CMD_TAG_SYSTEM_READY_STATUS;//tells CMNC the system is ready
		}//end else

		 //initialize/reset shared counter before use
		timeout_counter = 0;

	}//end else if
	 //Break Secure Link
	else if (commandTag == CMD_TAG_BREAK_SECURE_LINK &&
			(
				(roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_BREAKSECURELINK_) )
				|| (roverComm == ROVERCOMM_CMNC && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_CMNC, _BTFG_COMMAND_ENABLE_OPTION_BREAKSECURELINK_))
			)
		)	
	{

		//CHECK MY LOGIC LATER/TEST THIS CODE LATER-wrote a quick template, draft	
		currentMode = SECURING_LINK;//Set mode to SECURING_LINK *begin*
									//set flag for secure link broken
		BooleanBitFlags::clearFlagBit(flagSet_SystemStatus, _BTFG_COMMUNICATIONS_SECURE_);
		//initialize/reset shared counter before use
		timeout_counter = 0;

	}//end else if		
	 //Establish Secure Link
	 //This checks to see if the receivedCommand matches any of the known values. Else it's an invalid command
	else if (commandTag == CMD_TAG_ESTABLISH_SECURE_LINK &&
			(
				(roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_ESTABLISHSECURELINK_) )
				|| (roverComm == ROVERCOMM_CMNC && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_CMNC, _BTFG_COMMAND_ENABLE_OPTION_ESTABLISHSECURELINK_))
			)
		)		 
	{


		//WRITE LATER
		//maybe add a check here to check the command data for a string which is the "key code" or "rfid tag" used to establish secure link

		//CHECK MY LOGIC LATER/TEST THIS CODE LATER-wrote a quick template, draft		
		currentMode = NORMAL_OPERATIONS;//Set mode to NORMAL_OPERATIONS *begin*
										//set flag for secure link established
		BooleanBitFlags::setFlagBit(flagSet_SystemStatus, _BTFG_COMMUNICATIONS_SECURE_);
		timeout_counter = 0; //reset for future use		
		cmnc_msg_queue = CMD_TAG_ESTABLISH_SECURE_LINK;//tells CMNC link is now secured
	}//end else if
	 //COMM Sleep Request (usually from MAIN)
	else if (commandTag == CMD_TAG_COMM_SLEEP_REQUEST &&
			(
				(roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_COMMSLEEPREQUEST_) )
				|| (roverComm == ROVERCOMM_CMNC && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_CMNC, _BTFG_COMMAND_ENABLE_OPTION_COMMSLEEPREQUEST_))
			)
		)		 
	{
		//CHECK MY LOGIC LATER/TEST THIS CODE LATER-wrote a quick template, draft			
		//Pre-sleep tasks - Setting up wake tasks before going to sleep
		//Clear the system go flag
		BooleanBitFlags::clearFlagBit(flagSet_SystemStatus, _BTFG_MAIN_SYSTEM_GO_);
		currentMode = SYSTEM_WAKING;//Set mode to SYSTEM_WAKING *begin*
		cmnc_msg_queue = CMD_TAG_SYSTEM_IS_WAKING;
		timeout_counter = 0; //reset for future use				
		 //Run other pre-sleep tasks. (i.e. end software serial, as needed)		
		 //WRITE LATER!!!!
		 /*
		 End software serial??
		 Put COMM to sleep
		 Don't switch states yet. Go to sleep in the current PROCESS_DATA state.
		 The Xbee/Serial will wake up the sleep.
		 Run wake up tasks. (i.e. begin SW serial as needed, etc.)
		 Then it will go to RUN_HOUSEKEEPING_TASKS, while in SYSTEM_WAKING
		 Then it will go to the next state, which will default to CONTROL_OUTPUTS
		 */

	}//end else if		
	 //All Sleep Request
	else if (commandTag == CMD_TAG_ALL_SLEEP_REQUEST &&
			(
				(roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_ALLSLEEPREQUEST_) )
				|| (roverComm == ROVERCOMM_CMNC && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_CMNC, _BTFG_COMMAND_ENABLE_OPTION_ALLSLEEPREQUEST_))
			)
		)			 
	{

		//CHECK MY LOGIC LATER/TEST THIS CODE LATER-wrote a quick template, draft		
		currentMode = SYSTEM_SLEEPING;//Set mode to SYSTEM_SLEEPING *begin*
		main_msg_queue = CMD_TAG_ALL_SLEEP_REQUEST;
		cmnc_msg_queue = CMD_TAG_SYSTEM_IS_SLEEPING;
		timeout_counter = 0; //reset for future use				
	}//end else if			
	 //PIR Status
	else if (commandTag == CMD_TAG_PIR_STATUS &&
			(
				(roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_PIRSTATUS_) )
				|| (roverComm == ROVERCOMM_CMNC && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_CMNC, _BTFG_COMMAND_ENABLE_OPTION_PIRSTATUS_))
			)
		)		 
	{

		//CHECK MY LOGIC LATER/TEST THIS CODE LATER-wrote a quick template, draft		
		//Note: The PIR status message will be created in the CREATE_DATA state
		//Based on which Arduino sent the command, that same Arduino will get a response

		if (originRoverCommType == ROVERCOMM_CMNC || originRoverCommType == ROVERCOMM_PC_USB)//PC_USB and CMNC are the same for the COMM Arduino. CMNC will be used most of the time, but allow ROVERCOMM_PC_USB to exist just in case debugging code is added.
		{
			cmnc_msg_queue = CMD_TAG_PIR_STATUS;
		}//end if
		else if (originRoverCommType == ROVERCOMM_NAVI || originRoverCommType == ROVERCOMM_AUXI || originRoverCommType == ROVERCOMM_MAIN)
		{
			main_msg_queue = CMD_TAG_PIR_STATUS;
		}//end else if	
		 //Clears/resets all data pointers before setting them.
		clearRoverDataPointers();
		//Sets the roverDataPointer to the origin
		setRoverDataPointer(roverDataPointer, originRoverCommType);//override the default and send the response back to the requestor


	}//end else if			
	 //Received Error Messages
	else if (commandTag == CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS &&
			(
				(roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_RXDERRORMESSAGES_) )
				|| (roverComm == ROVERCOMM_CMNC && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_CMNC, _BTFG_COMMAND_ENABLE_OPTION_RXDERRORMESSAGES_))
			)
		)		 	 
	{
		cmnc_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//When COMM receives and error, always send it out to the CMNC so the base station knows there's an error	
	}//end else if					
	 //Hi Command - DEBUG
	else if (commandTag == CMD_TAG_DEBUG_HI_TEST_MSG &&
			(
				(roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_HI_) )
				|| (roverComm == ROVERCOMM_CMNC && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_CMNC, _BTFG_COMMAND_ENABLE_OPTION_HI_))
			)
		)		 	 
	{

		//Based on which Arduino sent the command, that same Arduino will get a response
		if (originRoverCommType == ROVERCOMM_CMNC || originRoverCommType == ROVERCOMM_PC_USB)//PC_USB and CMNC are the same for the COMM Arduino. CMNC will be used most of the time, but allow ROVERCOMM_PC_USB to exist just in case debugging code is added.
		{
			cmnc_msg_queue = CMD_TAG_DEBUG_HI_TEST_MSG;
		}//end if
		else if (originRoverCommType == ROVERCOMM_NAVI || originRoverCommType == ROVERCOMM_AUXI || originRoverCommType == ROVERCOMM_MAIN)
		{
			main_msg_queue = CMD_TAG_DEBUG_HI_TEST_MSG;
		}//end else if		


		 //Clears/resets all data pointers before setting them.
		clearRoverDataPointers();
		//Sets the roverDataPointer to the origin
		setRoverDataPointer(roverDataPointer, originRoverCommType);//override the default and send the response back to the requestor


	}//end if
	 //Bye Command - DEBUG
	else if (commandTag == CMD_TAG_DEBUG_BYE_TEST_MSG &&
			(
				(roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_BYE_) )
				|| (roverComm == ROVERCOMM_CMNC && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_CMNC, _BTFG_COMMAND_ENABLE_OPTION_BYE_))
			)
		)		
	{

		//Based on which Arduino sent the command, that same Arduino will get a response
		if (originRoverCommType == ROVERCOMM_CMNC || originRoverCommType == ROVERCOMM_PC_USB)//PC_USB and CMNC are the same for the COMM Arduino. CMNC will be used most of the time, but allow ROVERCOMM_PC_USB to exist just in case debugging code is added.
		{
			cmnc_msg_queue = CMD_TAG_DEBUG_BYE_TEST_MSG;
		}//end if
		else if (originRoverCommType == ROVERCOMM_NAVI || originRoverCommType == ROVERCOMM_AUXI || originRoverCommType == ROVERCOMM_MAIN)
		{
			main_msg_queue = CMD_TAG_DEBUG_BYE_TEST_MSG;
		}//end else if		

		 //Clears/resets all data pointers before setting them.
		clearRoverDataPointers();
		//Sets the roverDataPointer to the origin
		setRoverDataPointer(roverDataPointer, originRoverCommType);//override the default and send the response back to the requestor

	}//end else if
	 //Invalid - DEBUG
	else if (
			(roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_INVALID_) )
			|| (roverComm == ROVERCOMM_CMNC && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_CMNC, _BTFG_COMMAND_ENABLE_OPTION_INVALID_))
		)		
	{

		//Based on which Arduino sent the command, that same Arduino will get a response
		if (originRoverCommType == ROVERCOMM_CMNC || originRoverCommType == ROVERCOMM_PC_USB)//PC_USB and CMNC are the same for the COMM Arduino. CMNC will be used most of the time, but allow ROVERCOMM_PC_USB to exist just in case debugging code is added.
		{
			cmnc_msg_queue = CMD_TAG_INVALID_CMD;
		}//end if
		else if (originRoverCommType == ROVERCOMM_NAVI || originRoverCommType == ROVERCOMM_AUXI || originRoverCommType == ROVERCOMM_MAIN)
		{
			main_msg_queue = CMD_TAG_INVALID_CMD;
		}//end else if	

		 //Clears/resets all data pointers before setting them.
		clearRoverDataPointers();
		//Sets the roverDataPointer to the origin
		setRoverDataPointer(roverDataPointer, originRoverCommType);//override the default and send the response back to the requestor

	}//end else if
	 //else output nothing	


	return;
}//end of commandDirector()
void createDataFromQueueFor(byte roverCommDestination)
{
	//Note: The origin of the messsage will change every time it passes through an Arduino (i.e. using the RoverCommandProcessor::createCmd() with a Rover Comm Type passed to it). It shows the last originating Arduino that handled the data. If the true origin is required, that should be placed in the command data where it's not altered.

	byte queueOfInterest;
	char * commandDataOfInterest;//holds the rover's command data string
	char createdCommand[ROVER_COMM_SENTENCE_LENGTH];//holds the pointer to the created command
	//Based on the destination roverCommType of interest, set which queue and rover data the outgoing message should be based on
	if (roverCommDestination == ROVERCOMM_CMNC || roverCommDestination == ROVERCOMM_PC_USB)//PC_USB and CMNC are the same for the COMM Arduino. CMNC will be used most of the time, but allow ROVERCOMM_PC_USB to exist just in case debugging code is added.
	{
		queueOfInterest = cmnc_msg_queue;
		if (roverDataForCMNC != NULL)//make sure the roverDataPointer is not NULL
		{
			commandDataOfInterest = roverDataForCMNC->getCommandData();
		}//end if
		else
		{
			commandDataOfInterest = "";//else if it's NULL, set the data to nothing
		}//end else		
	}//end if
	else if (roverCommDestination == ROVERCOMM_MAIN)
	{
		queueOfInterest = main_msg_queue;
		if (roverDataForMAIN != NULL)//make sure the roverDataPointer is not NULL
		{
			commandDataOfInterest = roverDataForMAIN->getCommandData();
		}//end if
		else
		{
			commandDataOfInterest = "";//else if it's NULL, set the data to nothing
		}//end else
	}//end else if
	 //else
	 //do nothing

	
	
	
	//Use the Rover Command Creator to add the headers to the data string (origin, destination, priority level, command tag number, the message string)
	switch (queueOfInterest)
	{


		case CMD_TAG_COMM_HW_RESET_REQUEST:
				RoverCommandCreator::createCmd(ROVERCOMM_COMM, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_COMM_HW_RESET_REQUEST, getMsgString(0), createdCommand);
			break;
		case CMD_TAG_HW_IS_RESETTING:
				RoverCommandCreator::createCmd(ROVERCOMM_COMM, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_HW_IS_RESETTING, getMsgString(0), createdCommand);
			break;
		case CMD_TAG_ALL_SW_RESET_REQUEST:
				RoverCommandCreator::createCmd(ROVERCOMM_COMM, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_ALL_SW_RESET_REQUEST, getMsgString(0), createdCommand);		
			break;
		case CMD_TAG_SW_IS_RESETTING:
				RoverCommandCreator::createCmd(ROVERCOMM_COMM, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_SW_IS_RESETTING, getMsgString(0), createdCommand);		
			break;
		case CMD_TAG_GENERIC_HEALTH_STATUS_ERROR:
				RoverCommandCreator::createCmd(ROVERCOMM_COMM, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_GENERIC_HEALTH_STATUS_ERROR, getMsgString(0), createdCommand);		
			break;
		case CMD_TAG_SECURE_LINK_REQUEST:
				RoverCommandCreator::createCmd(ROVERCOMM_COMM, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_SECURE_LINK_REQUEST, getMsgString(0), createdCommand);		
			break;
		case CMD_TAG_SYSTEM_READY_STATUS:
				RoverCommandCreator::createCmd(ROVERCOMM_COMM, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_SYSTEM_READY_STATUS, getMsgString(0), createdCommand);					
			break;
		case CMD_TAG_ESTABLISH_SECURE_LINK:
				RoverCommandCreator::createCmd(ROVERCOMM_COMM, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_ESTABLISH_SECURE_LINK, getMsgString(0), createdCommand);							
			break;
		case CMD_TAG_SYSTEM_IS_WAKING:
				RoverCommandCreator::createCmd(ROVERCOMM_COMM, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_SYSTEM_IS_WAKING, getMsgString(0), createdCommand);							
			break;
		case CMD_TAG_ALL_SLEEP_REQUEST:
				RoverCommandCreator::createCmd(ROVERCOMM_COMM, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_ALL_SLEEP_REQUEST, getMsgString(0), createdCommand);							
			break;
		case CMD_TAG_PIR_STATUS:
				RoverCommandCreator::createCmd(ROVERCOMM_COMM, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_PIR_STATUS, getMsgString(0), createdCommand);							
				//WRITE ME LATER			
					//ADD IN THE DATA FOR PIR STATUS HERE									
					//RoverCommandCreator::createCmd(ROVERCOMM_COMM, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_PIR_STATUS, ADD PIR STATUS HERE, createdCommand);							
			break;
		case CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS:
				RoverCommandCreator::createCmd(ROVERCOMM_COMM, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS, getMsgString(2), createdCommand);
			break;
		case CMD_TAG_DEBUG_HI_TEST_MSG:
				RoverCommandCreator::createCmd(ROVERCOMM_COMM, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_DEBUG_HI_TEST_MSG, commandDataOfInterest, createdCommand);							
			break;
		case CMD_TAG_DEBUG_BYE_TEST_MSG:
				RoverCommandCreator::createCmd(ROVERCOMM_COMM, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_DEBUG_BYE_TEST_MSG, commandDataOfInterest, createdCommand);										
			break;
		case CMD_TAG_INVALID_CMD:
				RoverCommandCreator::createCmd(ROVERCOMM_COMM, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_INVALID_CMD, getMsgString(0), createdCommand);									
			break;
		default:
				RoverCommandCreator::createCmd(ROVERCOMM_COMM, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_INVALID_CMD, getMsgString(0), createdCommand);//output invalid command
			break;
	}//end switch
	
	
	if (roverCommDestination == ROVERCOMM_CMNC || roverCommDestination == ROVERCOMM_PC_USB)//PC_USB and CMNC are the same for the COMM Arduino. CMNC will be used most of the time, but allow ROVERCOMM_PC_USB to exist just in case debugging code is added.
	{
		sprintf(txMsgBuffer_CMNC, createdCommand);
	}//end if
	else if (roverCommDestination == ROVERCOMM_MAIN)
	{
		sprintf(txMsgBuffer_MAIN, createdCommand);
	}//end else if
	 //else








}//end of createDataFromQueueFor()
void setAllErrorFlagsTo(boolean choice)
{
	BooleanBitFlags::assignFlagBit(flagSet_Error, _BTFG_INVALID_STATE_OR_MODE_ERROR_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_Error, _BTFG_SYNC_ERROR_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_Error, _BTFG_SECURE_LINK_ERROR_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_Error, _BTFG_SW_RESET_ERROR_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_Error, _BTFG_GENERIC_HEALTH_ERROR_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_Error, _BTFG_SLEEPING_ERROR_, choice);
}//end of setAllErrorFlagsTo()
void setAllMessageControlFlagsTo(boolean choice)
{
	BooleanBitFlags::assignFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_CMNC_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_MAIN_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_MessageControl, _BTFG_DATA_WAS_FOR_COMM_CH1_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_MessageControl, _BTFG_DATA_WAS_FOR_COMM_CH2_, choice);
}//end of setAllMessageControlFlagsTo()
void setAllSystemStatusFlagsTo(boolean choice)
{
	BooleanBitFlags::assignFlagBit(flagSet_SystemStatus, _BTFG_MAIN_SYSTEM_READY_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_SystemStatus, _BTFG_MAIN_SYSTEM_GO_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_SystemStatus, _BTFG_COMMUNICATIONS_SECURE_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_SystemStatus, _BTFG_FIRST_TRANSMISSION_, choice);
}//end of setAllSystemStatusFlagsTo()
void setAllCommandFiltersTo(boolean choice, byte roverComm)
{
	//Note: Right now this function doesn't discriminate where the commands are coming from. So if they're all set to true, in theory, for example CMNC can "inject" or "spoof" a command that looks like it's coming from somewhere else.
	//This is a bug that can be fixed later if needed. Keeping it simple for now.

	if(roverComm == ROVERCOMM_CMNC)
	{
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_CMNC, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_CMNC, _BTFG_COMMAND_ENABLE_OPTION_HWRESETREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_CMNC, _BTFG_COMMAND_ENABLE_OPTION_COMMSWRESETREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_CMNC, _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_CMNC, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_CMNC, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMGO_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_CMNC, _BTFG_COMMAND_ENABLE_OPTION_BREAKSECURELINK_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_CMNC, _BTFG_COMMAND_ENABLE_OPTION_ESTABLISHSECURELINK_, choice);

		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_CMNC, _BTFG_COMMAND_ENABLE_OPTION_COMMSLEEPREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_CMNC, _BTFG_COMMAND_ENABLE_OPTION_ALLSLEEPREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_CMNC, _BTFG_COMMAND_ENABLE_OPTION_PIRSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_CMNC, _BTFG_COMMAND_ENABLE_OPTION_RXDERRORMESSAGES_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_CMNC, _BTFG_COMMAND_ENABLE_OPTION_HI_, choice);//DEBUG
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_CMNC, _BTFG_COMMAND_ENABLE_OPTION_BYE_, choice);//DEBUG
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_CMNC, _BTFG_COMMAND_ENABLE_OPTION_INVALID_, choice);//DEBUG
	}
	else if(roverComm == ROVERCOMM_MAIN)
	{
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_HWRESETREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_COMMSWRESETREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMGO_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_BREAKSECURELINK_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_ESTABLISHSECURELINK_, choice);

		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_COMMSLEEPREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_ALLSLEEPREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_PIRSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_RXDERRORMESSAGES_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_HI_, choice);//DEBUG
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_BYE_, choice);//DEBUG
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_INVALID_, choice);//DEBUG
	}
}//end of setAllCommands()
void redirectData(RoverComm * roverComm)
{
	


	/*
	Notes:
	For program efficiency, instead of sending all redirect messages, it sends only one per channel.
	This is because between each message transmission, there needs to be a delay (since the receiving code is designed only to receive so many messages at once.
	And if there are a lot of redirects, it will be stuck in the TX_COMMUNICATIONS for a while.
	*/
	RoverData * roverData;
	byte roverCommType;

	//Get the roverData object from the RoverComm Object
	roverData = roverComm->getRoverDataObject();

	//Get destination from either MAIN's or CMNC's Rover Data
	roverCommType = roverData->getDestinationCommType();//get the destination comm type for the roverData
	
	
	//If the destination is from: 1) MAIN (or AUXI, or NAVI) to CMNC/PC_USB or 2) CMNC to CMNC/PC_USB (loopback)
	if (roverCommType == ROVERCOMM_CMNC || roverCommType == ROVERCOMM_PC_USB)//PC_USB and CMNC are the same for the COMM Arduino. CMNC will be used most of the time, but allow ROVERCOMM_PC_USB to exist just in case debugging code is added.
	{
		//And if redirection to CMNC/PC_USB is allowed
		if (BooleanBitFlags::flagIsSet(flagSet_MessageControl, _BTFG_REDIRECT_TO_CMNC_))
		{
			#ifdef _DEBUG_REDIRECTION_NOTICE
				Serial.println(F("Redirect2CMNC/PC_USB"));
			#endif
			//Then transmit the data out to CMNC/PC_USB
			txData(roverComm->getRxData(), ROVERCOMM_CMNC);
		}//end if		 
	}//end if	
	//Else if the destination is from: 1) CMNC to MAIN (or AUXI, or NAVI) or 2) MAIN (or AUXI, or NAVI) to MAIN (or AUXI, or NAVI) (loopback)
	else if (roverCommType == ROVERCOMM_MAIN || roverCommType == ROVERCOMM_AUXI || roverCommType == ROVERCOMM_NAVI)
	{
		//And if redirection to MAIN (or AUXI, or NAVI) is allowed
		if (BooleanBitFlags::flagIsSet(flagSet_MessageControl, _BTFG_REDIRECT_TO_MAIN_))//Checks to see if redirection is allowed to MAIN, AUXI, or NAVI
		{
			#ifdef _DEBUG_REDIRECTION_NOTICE
				Serial.println(F("Redirect2MAIN"));
			#endif
			//Then transmit the data out to MAIN
			txData(roverComm->getRxData(), ROVERCOMM_MAIN);
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
			heartLed->ledSetLevel(_ONE_THIRD_BRIGHTNESS_);//run the heart led with desired brightness
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
			heartLed->ledSetLevel(_ONE_THIRD_BRIGHTNESS_);//run the heart led with desired brightness
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
			heartLed->ledSetLevel(_ONE_THIRD_BRIGHTNESS_);//run the heart led with desired brightness
			break;
		case RX_COMMUNICATIONS:

			//skip for CMNC

			//rxData() from MAIN
			//1. Reset status flag
			ch2Status = DATA_STATUS_NOT_READY;
			//2. Clear all Rx'ed data before getting new data				
			roverComm_Ch2->clearRxData();
			//3. Receive data
			ch2Status = rxData(roverComm_Ch2, ROVERCOMM_MAIN);//Note: this is a local .ino function		break;
		case DATA_VALIDATION:

			//skip for CMNC

			//parseAndValidateData() from MAIN
			//Process/validate the data that was received
			if (ch2Status == DATA_STATUS_READY)
			{
				//If the data is valid as well as parses it, set the status as such
				if (roverComm_Ch2->parseAndValidateData())
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


			//Reset/clear flags (no data for COMM)
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl, _BTFG_DATA_WAS_FOR_COMM_CH1_);
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl, _BTFG_DATA_WAS_FOR_COMM_CH2_);
			//Reset/Clear redirect to CMNC and redirect to MAIN flags (no redirection needed). They will then be set by any of the calls to dataDirector if there is redirection required from the Arduinos, correspondingly.
			//A bit redundant since this will be cleared again after data transmission. But it's better safe than sorry.
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_CMNC_);
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_MAIN_);

			//Set Command Filter Options
			//First initialize all command choices to false
			setAllCommandFiltersTo(false, ROVERCOMM_CMNC);//for CMNC
			setAllCommandFiltersTo(false, ROVERCOMM_MAIN);//for MAIN
			//Then enable the allowed commands:
			//For CMNC
				//leave false
			//For MAIN
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMGO_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_HWRESETREQUEST_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_COMMSWRESETREQUEST_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_RXDERRORMESSAGES_);//MAYBE NEED TO FIX, not sure if this should be a flag for a command or should be a redirect instead. generic status error message(s) from MAIN (redirected from AUXI)


			//Transmit data and/or execute command(s)

			//Skip for CMNC (since the link isn't secure yet)
			//Note: no reset (hw or sw) allowed from CMNC yet. because if it can take a reset msg, it should be able to secure link. Also there is a secure link timeout, that then goes to error mode and allows for hw/sw reset.
			//no redirections from CMNC


			//For data from MAIN, transmit the data to it's proper destination if it was meant
			//For another Arduino or take any actions if the data was meant for this unit, COMM


			if (ch2Status == DATA_STATUS_VALID)
			{
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action


				#ifdef _DEBUG_ALLOW_REDIRECTION_CH2_IN_SYNC_MODE
							//Allow redirections for debugging purposes
							dataDirector(roverDataCh2_COMM, DATA_REDIRECT_ENABLED, flagSet_MessageControl, _BTFG_DATA_WAS_FOR_COMM_CH2_);//DataDirection will set set the "data was for COMM flag" to true if it was for this Arduino
				#else
							//Set no redirections from MAIN	
							dataDirector(roverDataCh2_COMM, DATA_REDIRECT_DISABLED, flagSet_MessageControl, _BTFG_DATA_WAS_FOR_COMM_CH2_);//DataDirection will set set the "data was for COMM flag" to true if it was for this Arduino
				#endif
				//Note: this is a local .ino function

				/*
				Set filter to throw away all MAIN data except:
				system ready message(s) from MAIN
				system go message(s) from MAIN
				hw reset requests message(s) from MAIN
				sw reset requests message(s) from MAIN
				generic status error message(s) from MAIN (redirected from AUXI)
				*/



			}//end if
			 //else the data was invalid or not ready, so do nothing


			break;
		case PROCESS_DATA:
		
			#ifdef _DEBUG_PRINT_TIMEOUT_COUNTER_VALUE_
				Serial.println(timeout_counter);//DEBUG
			#endif
			
			//Skip Process of PIR status
			//Skip Process CMNC command/data
			//Process MAIN command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
			//Note: Either you should get no data, hw reset, sw reset, generic health status errors, or system ready or system go message(s) from MAIN. as everything else was filtered out.
			//Remember, only  hw reset, sw reset, generic health status error, or system ready or system go message(s) can pass the data filter.



			//Run highest priority functions here. //this will override any lower priority messages (i.e. system go). This will overwrite anything else. (i.e. system ready)
			//Note: If system go or system ready msg has been received from MAIN, see the commandDirector for more info.


			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl, _BTFG_DATA_WAS_FOR_COMM_CH2_))//If there was data from MAIN (Ch2), and it was for COMM
			{
				//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh2_COMM, ROVERCOMM_MAIN);
			}//end if
			
			
			
			//If System Go (from MAIN to COMM) was not received (Note: Messages received could still have been sys ready or no message at all)
			if( ! BooleanBitFlags::flagIsSet(flagSet_SystemStatus, _BTFG_MAIN_SYSTEM_GO_))
			{
				#ifndef _DEBUG_TURN_OFF_SYSTEM_READY_STATUS //normally the main_msg_queue will send the CMD_TAG_SYSTEM_READY_STATUS. Can disable it for debugging purposes
					main_msg_queue = CMD_TAG_SYSTEM_READY_STATUS;//tells MAIN it's ready to synchronize, it should be normally on. only turn off when in debugging to reduce clutter
				#endif
				//If no system go msg from MAIN received && main_system_ready == false (MAIN system not ready yet to set the main_system_ready flag and have not received a system go to switch states yet, then keep incrementing the timeout counter)
				if( ! BooleanBitFlags::flagIsSet(flagSet_SystemStatus, _BTFG_MAIN_SYSTEM_READY_))
				{
					timeout_counter++;
				}//end if
			}//end if		
			#ifndef _DEBUG_DISABLE_COMM_SYNC_TIMEOUT //normally the timeout code would run. Can disable it for debugging purposes
				if(timeout_counter >= COMM_SYNC_TIMEOUT_VALUE)
				{
					currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
					cmnc_msg_queue == CMD_TAG_SYNC_ERROR_STATUS;
					//set sync_error = true
					BooleanBitFlags::setFlagBit(flagSet_Error, _BTFG_SYNC_ERROR_);			
					//(Note: the sync_error flag can only be cleared with a sw reset or hw reset)
					//initialize/reset shared counter before use
					timeout_counter = 0;	
				}//end if	
			#endif
			break;
		case CONTROL_OUTPUTS:
			//Nothing to do here. The heart LED is controlled in each of the runModeFunction functions under the RUN_HOUSEKEEPING_TASKS state.
			break;
		case CREATE_DATA:
			//WRITE ME LATER

			//Creates data for MAIN
			if (main_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_MAIN);
			}//end if
			 //Skip creating data for CMNC
			break;
		case TX_COMMUNICATIONS:
			//Sends data to MAIN
			if (main_msg_queue != CMD_TAG_NO_MSG)
			{
				txData(txMsgBuffer_MAIN, ROVERCOMM_MAIN);
			}//end if
			#ifdef _DEBUG_ALLOW_REDIRECTION_CH2_IN_SYNC_MODE
				 //Allow redirections for debugging purposes
				redirectData(roverComm_Ch2);//This function will redirect data as required, and limit it to one redirection per channel (due to the limits of throughput on the receiving end)
			#else
				 //No redirection in the SYNCHRONIZATION mode				
			#endif			
			//clears message queue(s) and redirect flags		
			cmnc_msg_queue = CMD_TAG_NO_MSG;
			main_msg_queue = CMD_TAG_NO_MSG;
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_CMNC_);
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_MAIN_);
			
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
			heartLed->ledSetLevel(_TWO_THIRDS_BRIGHTNESS_);//run the heart led with desired brightness
			break;
		case RX_COMMUNICATIONS:

			//rxData() from CMNC
			//1. Reset status flag
			ch1Status = DATA_STATUS_NOT_READY;
			//2. Clear all Rx'ed data before getting new data				
			roverComm_Ch1->clearRxData();
			//3. Receive data
			ch1Status = rxData(roverComm_Ch1, ROVERCOMM_CMNC);//Note: this is a local .ino function

			//rxData() from MAIN
			//1. Reset status flag
			ch2Status = DATA_STATUS_NOT_READY;
			//2. Clear all Rx'ed data before getting new data				
			roverComm_Ch2->clearRxData();
			//3. Receive data
			ch2Status = rxData(roverComm_Ch2, ROVERCOMM_MAIN);//Note: this is a local .ino function

			break;
		case DATA_VALIDATION:

			//parseAndValidateData() from CMNC
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


			 //parseAndValidateData() from MAIN
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



			break;
		case DATA_FILTER:

			//Reset/clear flags (no data for COMM)
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl, _BTFG_DATA_WAS_FOR_COMM_CH1_);
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl, _BTFG_DATA_WAS_FOR_COMM_CH2_);
			//Reset/Clear redirect to CMNC and redirect to MAIN flags (no redirection needed). They will then be set by any of the calls to dataDirector if there is redirection required from the Arduinos, correspondingly.
			//A bit redundant since this will be cleared again after data transmission. But it's better safe than sorry.
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_CMNC_);
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_MAIN_);

			
			//Set Command Filter Options
			//First initialize all command choices to false
			setAllCommandFiltersTo(false, ROVERCOMM_CMNC);//for CMNC
			setAllCommandFiltersTo(false, ROVERCOMM_MAIN);//for MAIN
			//Then enable the allowed commands:
			//For CMNC
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_CMNC, _BTFG_COMMAND_ENABLE_OPTION_ESTABLISHSECURELINK_);
			//For MAIN
			//	No filter on MAIN data. (Allow all data from MAIN)
			//No commands from MAIN are filtered, so set all to true.
			setAllCommandFiltersTo(true, ROVERCOMM_MAIN);

			
			
			//Transmit data and/or execute command
			//For data from CMNC, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, COMM
			if (ch1Status == DATA_STATUS_VALID)
			{
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//Set no redirections from MAIN	
				//Note: this is a local .ino function

				dataDirector(roverDataCh1_COMM, DATA_REDIRECT_DISABLED, flagSet_MessageControl, _BTFG_DATA_WAS_FOR_COMM_CH1_);//DataDirection will set the "data was for COMM flag" to true if it was for this Arduino

				/*
				Set filter to throw away all CMNC data except:
				establish secure link message(s) from CMNC
				Note: no reset (hw or sw) allowed from CMNC yet. because if it can take a reset msg, it should be able to secure link. Also there is a secure link timeout, that then goes to error mode and allows for hw/sw reset.
				*/

			}//end if

			//For data from MAIN, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, COMM		
			if (ch2Status == DATA_STATUS_VALID)
			{
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//Set no redirections from MAIN	
				//Note: this is a local .ino function
				dataDirector(roverDataCh2_COMM, DATA_REDIRECT_ENABLED, flagSet_MessageControl, _BTFG_DATA_WAS_FOR_COMM_CH2_);//DataDirection will set the "data was for COMM flag" to true if it was for this Arduino

			}//end if
			//else the data was invalid or not ready, so do nothing				
			
			break;
		case READ_INPUTS:
//LEFT OFF HERE
			//WRITE ME LATER
			break;
		case PROCESS_DATA:
			#ifdef _DEBUG_PRINT_TIMEOUT_COUNTER_VALUE_
				Serial.println(timeout_counter);//DEBUG
			#endif
			
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

			redirectData(roverComm_Ch1);//This function will redirect data as required, and limit it to one redirection per channel (due to the limits of throughput on the receiving end)
			redirectData(roverComm_Ch2);//This function will redirect data as required, and limit it to one redirection per channel (due to the limits of throughput on the receiving end)

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
			heartLed->breathing();//run the heart led in breathing mode
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
			#ifdef _DEBUG_PRINT_TIMEOUT_COUNTER_VALUE_
				Serial.println(timeout_counter);//DEBUG
			#endif
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


			redirectData(roverComm_Ch1);//This function will redirect data as required, and limit it to one redirection per channel (due to the limits of throughput on the receiving end)
			redirectData(roverComm_Ch2);//This function will redirect data as required, and limit it to one redirection per channel (due to the limits of throughput on the receiving end)

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
			heartLed->ledSetLevel(_ONE_THIRD_BRIGHTNESS_);//run the heart led with desired brightness
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
			heartLed->ledSetLevel(_ONE_THIRD_BRIGHTNESS_);//run the heart led with desired brightness
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
			#ifdef _DEBUG_PRINT_TIMEOUT_COUNTER_VALUE_
				Serial.println(timeout_counter);//DEBUG
			#endif
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
			heartLed->ledSetLevel(_TWO_THIRDS_BRIGHTNESS_);//run the heart led with desired brightness
			break;
		case PROCESS_DATA:
			#ifdef _DEBUG_PRINT_TIMEOUT_COUNTER_VALUE_
				Serial.println(timeout_counter);//DEBUG
			#endif
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
			heartLed->ledSetLevel(_ONE_THIRD_BRIGHTNESS_);//run the heart led with desired brightness
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
			#ifdef _DEBUG_PRINT_TIMEOUT_COUNTER_VALUE_
				Serial.println(timeout_counter);//DEBUG
			#endif
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
			heartLed->ledSetLevel(_THREE_THIRDS_BRIGHTNESS_);//run the heart led with desired brightness
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
			#ifdef _DEBUG_PRINT_TIMEOUT_COUNTER_VALUE_
				Serial.println(timeout_counter);//DEBUG
			#endif
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
	
	heartLed->ledSetLevel(_ONE_THIRD_BRIGHTNESS_);//run the heart led with desired brightness

	//Set Invalid State Error Flag
	//Note: The Invalid State Error Flag cann only be cleared with a sw reset or hw reset
	BooleanBitFlags::setFlagBit(flagSet_Error, _BTFG_INVALID_STATE_OR_MODE_ERROR_);


	//initialize/reset shared counter before use
	timeout_counter = 0;
}//end of runStateFunction_default

 //====End of: Mode Functions
 //============End of Function Definitions






void InterruptDispatch1() {

	//WRITE ME LATER!!

	//pirSensor->isrUpdate();
}//emd of InterruptDispatch1()

void InterruptDispatch2() {
	//Have to keep the ISR short else the program won't work
	sleeperCOMM->isrUpdate();//update the awake flag to reflect current status
}//end of InterruptDispatch2()




char * getMsgString(byte arrayIndex) {
	
	if( arrayIndex < sizeof(msg_str_table)/sizeof(msg_str_table[0]))
	{
		memset(programMem2RAMBuffer, 0, sizeof(programMem2RAMBuffer));//clear char array buffer
		return strcpy_P(programMem2RAMBuffer, (char*)pgm_read_word(&(msg_str_table[arrayIndex])));//copy the fixed string from flash into the char buffer
	}//end if
	else
	{
		Serial.println(F("ArrayOvflw"));
		while(1);//hold the code here until it's fixed
	}
}//end of getMsgString()



void clearRoverDataPointers()
{
	//Clears/resets all data pointers
	roverDataForCOMM = NULL;
	roverDataForCMNC = NULL;
	roverDataForMAIN = NULL;
}//end of clearRoverDataPointer()

void setRoverDataPointer(RoverData * roverDataPointer, byte roverCommType)
{
	//This sets the roverDataPointer to the desired roverCommType.
	//Note: This function can be called more than once to set more than one roverDataPointer to the same data (i.e. if the same data needs to be shared in multiple places)
	if (roverCommType == ROVERCOMM_CMNC || roverCommType == ROVERCOMM_PC_USB)//PC_USB and CMNC are the same for the COMM Arduino. CMNC will be used most of the time, but allow ROVERCOMM_PC_USB to exist just in case debugging code is added.
	{
		roverDataForCMNC = roverDataPointer;
	}//end if
	else if (roverCommType == ROVERCOMM_NAVI || roverCommType == ROVERCOMM_AUXI || roverCommType == ROVERCOMM_MAIN)
	{
		roverDataForMAIN = roverDataPointer;
	}//end else if
	else//the roverCommType should be for this local Arduino (i.e. ROVERCOMM_COMM)
	{
		roverDataForCOMM = roverDataPointer;
	}//end else
}//end of setRoverDataPointer()
