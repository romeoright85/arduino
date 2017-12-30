/*
Note:
The best way to read this code from scratch is look at the global default values, see what state and mode the variables get on power on, then follow the state machine in the loop from the initializing state and mode
*/



/*
Design Notes:
Currently the priority level is not being used to prioritize right now. It's just there as a place holder.
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
//To see states and mode, and uncomment #define _DEBUG_PRINT_CURRENT_STATE and #define _DEBUG_PRINT_CURRENT_MODE in the code below.


To test locally with only one Arduino , first make sure if _DEBUG_ALL_SERIALS_WITH_USB_SERIAL_ is uncommented in RoverConfig.h

On Power On, MAIN is waiting for Systems Ready from COMM, NAVI, and AUXI, before it processes the Systems Go code. It has a timeout on how long it will wait for Systems Go though. This timeout is determined by MAIN_SYNC_TIMEOUT_VALUE.
To disable this timeout, uncomment #define _DEBUG_DISABLE_MAIN_SYNC_TIMEOUT in the code below.

Note: If _DEBUG_DISABLE_MAIN_SYNC_TIMEOUT is not turned on (i.e. disabled) eventually it will timeout and the system will send the following,
Example OUTPUT:
	/4c600*039nodata = Sync Error Status to PC_USB
	/4c500*012nodata = HW Reset Request to COMM
	/4c200*041nodata = Generic System Error to NAVI
	/4c300*041nodata = Generic System Error to AUXI

Note: Can see RoverComm.h for data format.

Can send a systems ready (where the command is 005 according to RoverCommandDefs.h) from each of the Arduinos:
Simulate from COMM:
	/5c400*005
Simulate from NAVI:
	/2c400*005
Simulate from AUXI:
	/3c400*005

Note: Uncomment #define _DEBUG_PRINT_SYSTEMS_READY_ACKNOWLEDGEMENTS below to see the system ready acknowledgements

Note: It seems to require the system ready command from some of the Arduinos to be sent more than once as the data probably gets lost in the mix or something.

Note: Uncomment #define _DEBUG_SKIP_RIGHT_TO_NORMAL_OPERATIONS_ below to jump straight to normal operations and test the auto data, etc.
Example OUTPUT:
	/4c200*0480000000 = ENC_STATUS_MID_LEFT data to NAVI
	/4c300*045off = MTR_PWR_STATUS data to AUXI
	/4c200*0490000000 = ENC_STATUS_MID_RIGHT data to NAVI


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
#include <RoverMessagePackager.h>



//============Function Prototypes
void InterruptDispatch_wheelEncoder_MidLeft();
void InterruptDispatch_wheelEncoder_MidRight();

void InterruptDispatch_WakeUpArduino();//For RoverSleeper
//============End of Function Prototypes


//============Debugging: Serial Channel Selection
//Used to output debugging messages only when the _DEBUG_COMM_BROADCAST flag is defined
//Uncomment the flag below in order to output debugging messages
//#define _DEBUG_COMM_BROADCAST //Normally commented out during normal operations.

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
//#define _DEBUG_PRINT_CURRENT_STATE //Normally commented out during normal operations.
//#define _DEBUG_PRINT_CURRENT_MODE //Normally commented out during normal operations.


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



//============Debugging: Skip to Normal Operations
//Uncomment the flag below to jump straight to normal operations and test the auto data, etc.

//#define _DEBUG_SKIP_RIGHT_TO_NORMAL_OPERATIONS_ //Normally commented out during normal operations.

//============End Debugging: Skip to Normal Operations


//============Debugging: Print System Ready Status
//Uncomment the flag below in order to print the System Ready Status
//#define _DEBUG_PRINT_SYSTEMS_READY_ACKNOWLEDGEMENTS //Normally commented out during normal operations.


#ifdef _DEBUG_PRINT_SYSTEMS_READY_ACKNOWLEDGEMENTS
#define _PRINT_SYSTEM_READY_ _SERIAL_DEBUG_CHANNEL_.println
#else
#define _PRINT_SYSTEM_READY_ void
#endif

//============End Debugging: Print System Ready Status



//============Debugging: Print HW Reset
//Uncomment the flag below in order to print the HW Reset Status
//#define _DEBUG_PRINT_HW_RESET_STATUS //Normally commented out during normal operations.


#ifdef _DEBUG_PRINT_HW_RESET_STATUS
#define _PRINT_HW_RESET_STATUS_ _SERIAL_DEBUG_CHANNEL_.println
#else
#define _PRINT_HW_RESET_STATUS_ void
#endif


//============End Debugging: Print Mode and/or State



//============Debugging: Print Wakeup Status
//Uncomment the flag below in order to print the HW Reset Status
//#define _DEBUG_PRINT_SLEEPING_AND_WAKEUP_STATUS //Normally commented out during normal operations.


#ifdef _DEBUG_PRINT_SLEEPING_AND_WAKEUP_STATUS
#define _PRINT_SLEEPING_AND_WAKEUP_STATUS_ _SERIAL_DEBUG_CHANNEL_.println
#else
#define _PRINT_SLEEPING_AND_WAKEUP_STATUS_ void
#endif


//============End Debugging: Print Wakeup Status




 //============Debugging: Redirection Notice
//Uncomment to output notice when redirection is occurring
//#define _DEBUG_REDIRECTION_NOTICE //Normally commented out during normal operations.
//============End Debugging: Redirection Notice


//============Debugging: All Data Filtering Off
//Uncomment in order to allow all data to pass (turn off all data filters) for debugging)
#define _DEBUG_TURN_OFF_ALL_DATA_FILTERS //Normally commented out during normal operations.
//============End Debugging: All Data Filtering Off






//============Debugging: Disable MAIN Sync Timeout
//Uncomment in order to disable MAIN Sync Timeout (when waiting for Systems Go on startup/power on)
//#define _DEBUG_DISABLE_MAIN_SYNC_TIMEOUT //Normally commented out during normal operations.
//============End Debugging: Disable MAIN Sync Timeout



//============Debugging: Disable Sleep Error Timeout
//Uncomment in order to disable the Sleep Error timeout
//#define _DEBUG_DISABLE_SLEEP_ERROR_TIMEOUT //Normally commented out during normal operations.
//============End Debugging: Disable Sleep Error Timeout


//============Debugging: SW Reset Error Timeout
//Uncomment in order to disable the SW Reset Error and SW Reset Resent timeout
//Note since this uses a dual timeout design, it uses one flag to disable both of the timeouts
//#define _DEBUG_DISABLE_SW_RESET_ERROR_AND_RESEND_TIMEOUT //Normally commented out during normal operations.
//============End Debugging: SW Reset Error Timeout



//============Debugging: Disable System Error Timeout
//Uncomment in order to disable the Sleep Error timeout
//#define _DEBUG_DISABLE_SYSTEM_ERROR_TIMEOUT //Normally commented out during normal operations.
//============End Debugging: Disable System Error Timeout



//============Debugging: Turn off System Ready Status During Synchronization Mode
//Uncomment in order to allow other data to be in the comm_msg_queue, navi_msg_queue, and/or auxi_msg_queue instead of just System Status
#define _DEBUG_TURN_OFF_SYSTEM_READY_STATUS //Normally commented out during normal operations.
//============End Debugging: All Data Filtering Off



//============Debugging: Print timeout counter value
//Uncomment in order to print timeout counter value
//#define _DEBUG_PRINT_TIMEOUT_COUNTER_VALUE_ //Normally commented out during normal operations.
//============End Debugging: Print timeout counter value






//============Global Declarations


//=====SW Resettable Variables (reinitialize these variables on software reset)



//Auto Data Counters
//They can just be byte instead of unsigned int since there aren't that many elements. Also a byte is already positive numbers or zero
byte auto_MAIN_to_COMM_data_cnt = 0;
byte auto_MAIN_to_CMNC_data_cnt = 0;
byte auto_MAIN_to_NAVI_data_cnt = 0;
byte auto_MAIN_to_AUXI_data_cnt = 0;



//Error Origin (used to send out the origin of the error with the error message)
byte error_origin = ROVERCOMM_NONE;

//Flag(s) - Error
byte flagSet_Error1 = _BTFG_NONE_;
//Flag(s) - Message Controls
byte flagSet_MessageControl1 = _BTFG_NONE_;
//Flag(s) - System Status 1
byte flagSet_SystemStatus1 = _BTFG_FIRST_TRANSMISSION_;//Default: Set the first transmission flag only, leave everything else unset
//Flag(s) - System Status 2
byte flagSet_SystemStatus2 = _BTFG_NONE_;
//Flag(s) - System Controls
byte flagSet_SystemControls1 = _BTFG_NONE_;

//Flag(s) - Command Filter Options - PC_USB, COMM, NAVI, and AUXI each have their own set since they have separate data filters

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
unsigned int timeout_counter = 0; //shared counter, used to detect timeout of AUXI and NAVI responding back to MAIN for any reason (i.e. system go or system ready responses), used to track how long MAIN has been waiting for Sleep Requests, SW Resets Acknowledgements, System Error Timeouts, etc.



unsigned int transmission_delay_cnt = 0;//concurrent transmission delay counter



//------------------From CommTester_MAIN

//Message Queues
// (command tag, not boolean since use by CREATE_DATA to generate messages as well as TX_COMMUNICATIONS as a flag)
byte pc_usb_msg_queue = CMD_TAG_NO_MSG;
byte comm_msg_queue = CMD_TAG_NO_MSG;
byte navi_msg_queue = CMD_TAG_NO_MSG;
byte auxi_msg_queue = CMD_TAG_NO_MSG;

//Data Destination Selections
byte comm_cmnc_destination_selection = ROVERCOMM_COMM;//default to COMM

//Flag(s) - Rover Data Channels Status
byte ch1Status = DATA_STATUS_NOT_READY;//for PC_USB
byte ch2Status = DATA_STATUS_NOT_READY;//for COMM
byte ch3Status = DATA_STATUS_NOT_READY;//for NAVI
byte ch4Status = DATA_STATUS_NOT_READY;//for AUXI

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
//Note: These pointers will be (re-)initialized by the function clearRoverDataPointers()
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

//Variables used to latch and save encoder values during the READ_INPUT state
//Note: Having each of these sets of variables (5 bytes for each encoder, where a byte is 1 byte and an int is 2 bytes)  is still less bytes than storing two char arrays of packaged data of length _MAX_ROVER_COMMAND_DATA_LEN_ (which is about 14 bytes)
//MidLeft Encoder
byte wheelEncoder_MidLeft_Direction = MOTOR_STOPPED;
int wheelEncoder_MidLeft_Speed = 0;
int wheelEncoder_MidLeft_Footage = 0;
//MidRight Encoder
byte  wheelEncoder_MidRight_Direction = MOTOR_STOPPED;
int wheelEncoder_MidRight_Speed = 0;
int wheelEncoder_MidRight_Footage = 0;






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
};//for pointers, pass them directly, for objects pass the address


//=====End of: SW Resettable Variables




//=====Non-SW Resettable Variables (do not reinitialize these variables on software reset)


//Auto Data Arrays
//Note: PC_USB doesn't get auto data (since it normally doesn't get monitored, and having data generated all the time would slow the system down)

//COMM (will have to send data through a shared channel with CMNC)
byte auto_MAIN_to_COMM_data_array[] = {
	//add more as needed
};
byte auto_MAIN_to_CMNC_data_array[] = {
	//add more as needed
};


//NAVI
byte auto_MAIN_to_NAVI_data_array[] = {
	CMD_TAG_MTR_PWR_STATUS,
	CMD_TAG_ENC_STATUS_MID_LEFT,
	CMD_TAG_ENC_STATUS_MID_RIGHT
	//add more as needed	
};
//AUXI
byte auto_MAIN_to_AUXI_data_array[] = {
	CMD_TAG_MTR_PWR_STATUS
};


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
const static char msg_strg_3[] PROGMEM = "on";//getMsgString(3)
const static char msg_strg_4[] PROGMEM = "off";//getMsgString(4)
//Note: Make sure to update  the msg_str_table[] array

//Table of Fixed Commaned Strings (array of strings stored in flash)
const char* const msg_str_table[] PROGMEM = {
	msg_strg_0,
	msg_strg_1,
	msg_strg_2,
	msg_strg_3,
	msg_strg_4
};





//States //(these states will not be re-initialized in initializeVariables() as when it's SW resetted with the COMM SW Reset Request in PROCESS_DATA's commandDirector(), it will already be going to RUN_HOUSEKEEPING_TASKS afterwards)
	
	//Current State
	byte currentState = RUN_HOUSEKEEPING_TASKS;
	//Next State
	byte nextState = RUN_HOUSEKEEPING_TASKS;


	//Queued State
	#ifdef _DEBUG_SKIP_RIGHT_TO_NORMAL_OPERATIONS_//the debug case (i.e. to test auto data)
		byte queuedState = RX_COMMUNICATIONS;//DEBUG
	#else //The normal case
		byte queuedState = RUN_HOUSEKEEPING_TASKS;
	#endif


	
//Modes //(this mode will not be re-initialized in initializeVariables() as they're set by the state machine when being SW resetted)

#ifdef _DEBUG_SKIP_RIGHT_TO_NORMAL_OPERATIONS_//the debug case (i.e. to test auto data)
	byte currentMode = NORMAL_OPERATIONS;//DEBUG
#else //The normal case
	byte currentMode = POWER_ON_AND_HW_RESET;
#endif




RoverMessagePackager * roverMessagePackager = new RoverMessagePackager();




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
	//Setup the HW_UART for communications between MAIN and COMM, MAIN and AUXI, MAIN and NAVI, and MAIN and PC USB
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	_PC_USB_SERIAL_.flush();//waits for any outgoing serial data to complete
	
	_COMM_SERIAL_.begin(COMM_BAUD_RATE);
	_COMM_SERIAL_.flush();//waits for any outgoing serial data to complete
	
	_NAVI_SERIAL_.begin(NAVI_BAUD_RATE);
	_NAVI_SERIAL_.flush();//waits for any outgoing serial data to complete
	
	_AUXI_SERIAL_.begin(AUXI_BAUD_RATE);
	_AUXI_SERIAL_.flush();//waits for any outgoing serial data to complete
	
	
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

}//end of interrupt service routine





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
					//shut down motor when in error for safety
					BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);
					error_origin = ROVERCOMM_MAIN;
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
					//shut down motor when in error for safety
					BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);
					error_origin = ROVERCOMM_MAIN;
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
					//shut down motor when in error for safety
					BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);
					error_origin = ROVERCOMM_MAIN;
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
					//shut down motor when in error for safety
					BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);
					error_origin = ROVERCOMM_MAIN;
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
					//shut down motor when in error for safety
					BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);
					error_origin = ROVERCOMM_MAIN;
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
					//shut down motor when in error for safety
					BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);
					error_origin = ROVERCOMM_MAIN;
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
					//shut down motor when in error for safety
					BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);
					error_origin = ROVERCOMM_MAIN;
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
					//shut down motor when in error for safety
					BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);					
					error_origin = ROVERCOMM_MAIN;
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
					//shut down motor when in error for safety
					BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);					
					error_origin = ROVERCOMM_MAIN;
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
			//shut down motor when in error for safety
			BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);					
			error_origin = ROVERCOMM_MAIN;
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
//place holder: Add things here as needed.

}//runPORTasks()
void initializeVariables()
{
	//(re)initialize most global variables (i.e. for software reset)


	//Auto Data Counters
	//They can just be byte instead of unsigned int since there aren't that many elements. Also a byte is already positive numbers or zero
	auto_MAIN_to_COMM_data_cnt = 0;
	auto_MAIN_to_CMNC_data_cnt = 0;
	auto_MAIN_to_NAVI_data_cnt = 0;
	auto_MAIN_to_AUXI_data_cnt = 0;
	
	

	//Error Origin (used to send out the origin of the error with the error message)
	error_origin = ROVERCOMM_NONE;

	//Flag(s) - Error
	flagSet_Error1 = _BTFG_NONE_;
	//Flag(s) - Message Controls
	flagSet_MessageControl1 = _BTFG_NONE_;	
	//Flag(s) - System Status 1
	flagSet_SystemStatus1 = _BTFG_FIRST_TRANSMISSION_;//Default: Set the first transmission flag only, leave everything else unset
	//Flag(s) - System Status 2
	flagSet_SystemStatus2 = _BTFG_NONE_;
	//Flag(s) - System Controls
	flagSet_SystemControls1 = _BTFG_NONE_;
	//Flag(s) - Command Filter Options - MAIN and CMNC each have their own set since they have separate data filters

	//Command Filter Options for PC_USB: Set 1
	commandFilterOptionsSet1_PC_USB = _BTFG_NONE_;
	//Command Filter Options for PC_USB: Set 2
	commandFilterOptionsSet2_PC_USB = _BTFG_NONE_;

	//Command Filter Options for COMM: Set 1
	commandFilterOptionsSet1_COMM = _BTFG_NONE_;
	//Command Filter Options for COMM: Set 2
	commandFilterOptionsSet2_COMM = _BTFG_NONE_;

	//Command Filter Options for NAVI: Set 1
	commandFilterOptionsSet1_NAVI = _BTFG_NONE_;
	//Command Filter Options for NAVI: Set 2
	commandFilterOptionsSet2_NAVI = _BTFG_NONE_;

	//Command Filter Options for AUXI: Set 1
	commandFilterOptionsSet1_AUXI = _BTFG_NONE_;
	//Command Filter Options for AUXI: Set 2
	commandFilterOptionsSet2_AUXI = _BTFG_NONE_;




	//Counters
	timeout_counter = 0; //shared counter, used to detect timeout of MAIN responding back to COMM for any reason (i.e. system go or system ready responses), used to track how long COMM has been waiting for a COMM SW Request back from MAIN, after it sent a ALL_SW_RESET_REQUEST to MAIN (which MAIN might have missed, since it's sent only once), etc. Make sure to clear it out before use and only use it for one purpose at a time.
	transmission_delay_cnt = 0;//concurrent transmission delay counter


	
	//Message Queues
	pc_usb_msg_queue = CMD_TAG_NO_MSG;
	comm_msg_queue = CMD_TAG_NO_MSG;
	navi_msg_queue = CMD_TAG_NO_MSG;
	auxi_msg_queue = CMD_TAG_NO_MSG;

	//Data Destination Selections
	comm_cmnc_destination_selection = ROVERCOMM_COMM;//default to COMM

	//Flag(s) - Rover Data Channels Status
	ch1Status = DATA_STATUS_NOT_READY;//for PC_USB
	ch2Status = DATA_STATUS_NOT_READY;//for COMM
	ch3Status = DATA_STATUS_NOT_READY;//for NAVI
	ch4Status = DATA_STATUS_NOT_READY;//for AUXI

	
	
	//Variables used to latch and save encoder values during the READ_INPUT state
	//Note: Having each of these sets of variables (5 bytes for each encoder, where a byte is 1 byte and an int is 2 bytes)  is still less bytes than storing two char arrays of packaged data of length _MAX_ROVER_COMMAND_DATA_LEN_ (which is about 14 bytes)
	//MidLeft Encoder
	wheelEncoder_MidLeft_Direction = MOTOR_STOPPED;
	wheelEncoder_MidLeft_Speed = 0;
	wheelEncoder_MidLeft_Footage = 0;
	//MidRight Encoder
	wheelEncoder_MidRight_Direction = MOTOR_STOPPED;
	wheelEncoder_MidRight_Speed = 0;
	wheelEncoder_MidRight_Footage = 0;

	
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
//place holder: Add things here as needed.
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
	else if ( roverCommType == ROVERCOMM_COMM || roverCommType == ROVERCOMM_CMNC )//CMNC has to go through COMM
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
			BooleanBitFlags::setFlagBit(flagSet_MessageControl1, _BTFG_REDIRECT_TO_PC_USB_);
		}//end else if	
		else if (roverCommType == ROVERCOMM_COMM || roverCommType == ROVERCOMM_CMNC)//CMNC has to go through COMM
		{
			//if the data is for COMM (CMNC), transmit the data out from MAIN to COMM
			//Set redirect to COMM flag to true			
			BooleanBitFlags::setFlagBit(flagSet_MessageControl1, _BTFG_REDIRECT_TO_COMM_);
		}//end else if
		else if (roverCommType == ROVERCOMM_NAVI)
		{
			//if the data is for NAVI, transmit the data out from MAIN to NAVI
			//Set redirect to NAVI flag to true			
			BooleanBitFlags::setFlagBit(flagSet_MessageControl1, _BTFG_REDIRECT_TO_NAVI_);
		}//end else if
		else if (roverCommType == ROVERCOMM_AUXI)
		{
			//if the data is for AUXI, transmit the data out from MAIN to AUXI
			//Set redirect to AUXI flag to true			
			BooleanBitFlags::setFlagBit(flagSet_MessageControl1, _BTFG_REDIRECT_TO_AUXI_);
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
	else if (roverCommType == ROVERCOMM_COMM || roverCommType == ROVERCOMM_CMNC)//CMNC has to go through COMM
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

	//Note: This function varies for different Arduinos
	//Categorize all commands/data from all sources.					
	//Sort based on priority.
	//Allow for all non-conflicting commands to run.
	//Then only run the highest priority functions for COMM last, so it will overwrite anything else, right before state transition.

	
	#ifdef _DEBUG_TURN_OFF_ALL_DATA_FILTERS
		setAllCommandFiltersTo(true, ROVERCOMM_PC_USB);//for PC_USB
		setAllCommandFiltersTo(true, ROVERCOMM_COMM);//for COMM
		setAllCommandFiltersTo(true, ROVERCOMM_NAVI);//for NAVI
		setAllCommandFiltersTo(true, ROVERCOMM_AUXI);//for AUXI
	#endif

	byte originRoverCommType;//holds the received data's origin
	byte destinationRoverCommType;//holds the received data's destination
	byte commandTag;//holds received data's command tag
	char commandData[_MAX_ROVER_COMMAND_DATA_LEN_];//holds the received data's command data

	//Get the received data's origin and destination
	originRoverCommType = roverDataPointer->getOriginCommType();
	destinationRoverCommType = roverDataPointer->getDestinationCommType();

	//Get the command tag from the Rover Data Object
	commandTag = roverDataPointer->getCommandTag();
	//Get the command data from the Rover Data Object	
	strncpy(commandData, roverDataPointer->getCommandData(), roverDataPointer->getCommandDataLength());

	//Setting the roverDataPointer in order to route where the rover command data will be routed to
	//Clears/resets all data pointers before setting them.
	clearRoverDataPointers();
	//Sets the default such that the rover command data goes to the destination of the command. If needed, this can be overwritten by the command tag if/else statements
	setRoverDataPointer(roverDataPointer, destinationRoverCommType);
	//Note: The roverDataPointer should be going to, MAIN, this unit (else it would have been redirected already with dataDirector).
	//However, it can be overwritten in the if/else conditions below based on the command tag for special cases like when it redirects itself to the original sender (i.e. when the command is a request for data/status, like with PIR Status request)

	//Run highest priority functions first and lower priorities last.
	//Note: Right now the way it's coded, the conflicting and non conflicting functions are all merged together and treated as conflicting. However, one data channel with a lower priority task may still override a higher priority task because the commandDirector for that channel was called later. If needed, fix this later.
	
	
	//COMM HW Reset Request
	if (commandTag == CMD_TAG_COMM_HW_RESET_REQUEST &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_COMMHWRESETREQUEST_) )
				|| (roverComm == ROVERCOMM_COMM && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_COMMHWRESETREQUEST_))
				|| (roverComm == ROVERCOMM_NAVI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_COMMHWRESETREQUEST_))
				|| (roverComm == ROVERCOMM_AUXI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_COMMHWRESETREQUEST_))
			)
		)	 
	{
		currentMode = HW_RESETTING;//Set mode to HW_RESETTING *begin*				
	}//end else if
	//All SW Reset Request
	else if (commandTag == CMD_TAG_ALL_SW_RESET_REQUEST &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_) )
				|| (roverComm == ROVERCOMM_COMM && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_))
				|| (roverComm == ROVERCOMM_NAVI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_))
				|| (roverComm == ROVERCOMM_AUXI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_))
			)
		)	 
	{

		//Create first message here and regenerate later on as needed
		navi_msg_queue = CMD_TAG_NAVI_SW_RESET_REQUEST;
		auxi_msg_queue = CMD_TAG_NAVI_SW_RESET_REQUEST;
		
		//initialize/reset shared flags before use
		BooleanBitFlags::clearFlagBit(flagSet_SystemStatus2, _BTFG_NAVI_ACKNOWLEDGEMENT_);
		BooleanBitFlags::clearFlagBit(flagSet_SystemStatus2, _BTFG_AUXI_ACKNOWLEDGEMENT_);
		BooleanBitFlags::clearFlagBit(flagSet_SystemStatus2, _BTFG_RUN_TASKS_ON_MAIN_NOW_);

		//shut down motor when sw resetting for safety
		BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);
		
		currentMode = SW_RESETTING;//Set mode to SW_RESETTING *begin*				

	}//end else if
	//SW Reset Acknowledgement (usually from NAVI or AUXI)
	else if (commandTag == CMD_TAG_SW_IS_RESETTING_ACK &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SWRESETACKNOWLEDGMENT_) )
				|| (roverComm == ROVERCOMM_COMM && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_SWRESETACKNOWLEDGMENT_))
				|| (roverComm == ROVERCOMM_NAVI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_SWRESETACKNOWLEDGMENT_))
				|| (roverComm == ROVERCOMM_AUXI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_SWRESETACKNOWLEDGMENT_))
			)
		)	 
	{
		
		//Check to see where the command was from		
		if (originRoverCommType == ROVERCOMM_NAVI)//If command was from NAVI
		{
			//navi_acknowledgement = true
			BooleanBitFlags::setFlagBit(flagSet_SystemStatus2, _BTFG_NAVI_ACKNOWLEDGEMENT_);
		}//end if
		else if (originRoverCommType == ROVERCOMM_AUXI)//else if command was from AUXI
		{
			//auxi_acknowledgement = true
			BooleanBitFlags::setFlagBit(flagSet_SystemStatus2, _BTFG_AUXI_ACKNOWLEDGEMENT_);
		}//end else if	
		//else do nothing
		
		
		//once MAIN gets a SW Reset Acknowledgement from both NAVI and AUXI
		if( BooleanBitFlags::flagIsSet(flagSet_SystemStatus2, _BTFG_NAVI_ACKNOWLEDGEMENT_) && BooleanBitFlags::flagIsSet(flagSet_SystemStatus2, _BTFG_AUXI_ACKNOWLEDGEMENT_) )
		{
			//run_task_on_main_now = true
			BooleanBitFlags::setFlagBit(flagSet_SystemStatus2, _BTFG_RUN_TASKS_ON_MAIN_NOW_);
			
		}//end if
		
	}//end else if
	//Received Generic Health Error
	else if (commandTag == CMD_TAG_GENERIC_HEALTH_STATUS_ERROR &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_) )
				|| (roverComm == ROVERCOMM_COMM && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_))
				|| (roverComm == ROVERCOMM_NAVI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_))
				|| (roverComm == ROVERCOMM_AUXI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_))
			)
		)	 
	{
		

//CHECK MY LOGIC LATER/TEST THIS CODE LATER-wrote a quick template, draft	
	
		//turn off the motor when there is a health error for safety
		BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);

		//Assign the error origin to where the data was generated from
		error_origin = originRoverCommType;
				
		//Create first message here and regenerate later on as needed
		pc_usb_msg_queue = CMD_TAG_GENERIC_HEALTH_STATUS_ERROR;//send error out through the PC_USB for debugging
		comm_msg_queue = CMD_TAG_GENERIC_HEALTH_STATUS_ERROR;
		navi_msg_queue = CMD_TAG_GENERIC_HEALTH_STATUS_ERROR;
		auxi_msg_queue = CMD_TAG_GENERIC_HEALTH_STATUS_ERROR;
		
		//set generic_health_error = true
		BooleanBitFlags::setFlagBit(flagSet_Error1, _BTFG_GENERIC_HEALTH_ERROR_);			
		//(Note: the generic_health_error flag can only be cleared with a sw reset or hw reset)			
		
		//initialize/reset shared counter before use
		timeout_counter = 0;
		
		currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*	
		//shut down motor when in error for safety
		BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);					
					
	}//end else if
	
	
	
	
	
		
	//Received Generic System Error
	else if (commandTag == CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_) )
				|| (roverComm == ROVERCOMM_COMM && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_))
				|| (roverComm == ROVERCOMM_NAVI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_))
				|| (roverComm == ROVERCOMM_AUXI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_))
			)
		)	 
	{

	
//CHECK MY LOGIC LATER/TEST THIS CODE LATER-wrote a quick template, draft	
	
		//Assign the error origin to where the data was generated from
		error_origin = originRoverCommType;
				
		//Create first message here and regenerate later on as needed
		comm_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//When COMM receives and error, always send it out to the CMNC so the base station knows there's an error	
		pc_usb_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;
		
		

		//set generic_system_error = true
		BooleanBitFlags::setFlagBit(flagSet_Error1, _BTFG_GENERIC_SYSTEM_ERROR_);
			//(Note: the generic_system_error flag can only be cleared with a sw reset or hw reset)
		
		//No need to reset timeout_counter since not changing modes
		
		//For now just forward it to COMM (CMNC) and PC_USB (as well as other Arduinos), keeping the original destination. No need to go into SYSTEM_ERROR mode just yet. Only health errors need to go to SYSTEM_ERROR mode. Though NAVI and AUXI might go to SYSTEM_ERROR mode.
		
		
		//All errors from AUXI, NAVI, MAIN, COMM, CMNC (PC_USB) should be redirected to COMM, and COMM will redirect it to CMNC
		//Then CMNC will talk to COMM where it can then allow hw and sw resets, etc.
		//Improvement Tip: MAIN can go into error mode if it gets an error message from AUXI, NAVI, COMM, MAIN, CMNC, PC_USB
		//Redirect any system errors from MAIN/NAVI/AUXI to CMNC for manual human in the loop disposition (i.e. hw or sw reset)		
		

	}//end else if
	
	//System Ready	
	else if (commandTag == CMD_TAG_SYSTEM_READY_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_) )
				|| (roverComm == ROVERCOMM_COMM && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_))
				|| (roverComm == ROVERCOMM_NAVI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_))
				|| (roverComm == ROVERCOMM_AUXI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_))
			)
		)	 
	{

		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_COMM)//If command was from COMM
		{
			_PRINT_SYSTEM_READY_(F("COMM Rdy"));
			//set comm_system_ready = true
			BooleanBitFlags::setFlagBit(flagSet_SystemStatus1, _BTFG_COMM_SYSTEM_READY_);
		}//end if
		else if (originRoverCommType == ROVERCOMM_NAVI)//If command was from NAVI
		{
			_PRINT_SYSTEM_READY_(F("NAVI Rdy"));
			//set navi_system_ready = true	
			BooleanBitFlags::setFlagBit(flagSet_SystemStatus1, _BTFG_NAVI_SYSTEM_READY_);
		}//end else if
		else if (originRoverCommType == ROVERCOMM_AUXI)//else if command was from AUXI
		{
			_PRINT_SYSTEM_READY_(F("AUXI Rdy"));
			//set auxi_system_ready = true	
			BooleanBitFlags::setFlagBit(flagSet_SystemStatus1, _BTFG_AUXI_SYSTEM_READY_);			
		}//end else if
		//else do nothing
		
		//Check to see if all systems are ready, so MAIN and start the systems go code/process
		//the status for a particular arduino (i.e. navi_system_ready fpr NAVI) would be set true when the system ready msg was received for that arduino
		if( BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_COMM_SYSTEM_READY_) && BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_NAVI_SYSTEM_READY_) && BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_AUXI_SYSTEM_READY_) )
		{
			comm_msg_queue = CMD_TAG_SYSTEM_GO_STATUS;
			navi_msg_queue = CMD_TAG_SYSTEM_GO_STATUS;				
			auxi_msg_queue = CMD_TAG_SYSTEM_GO_STATUS;
			//reset the timeout counter
			timeout_counter = 0;
			BooleanBitFlags::setFlagBit(flagSet_SystemStatus1, _BTFG_ALL_SYSTEMS_GO_);
			currentMode = NORMAL_OPERATIONS;//Set mode to NORMAL_OPERATIONS *begin*				
		}//end if
	}//end else if
	//All Sleep Request
	else if (commandTag == CMD_TAG_ALL_SLEEP_REQUEST &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_ALLSLEEPREQUEST_) )
				|| (roverComm == ROVERCOMM_COMM && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_ALLSLEEPREQUEST_))
				|| (roverComm == ROVERCOMM_NAVI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_ALLSLEEPREQUEST_))
				|| (roverComm == ROVERCOMM_AUXI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_ALLSLEEPREQUEST_))
			)
		)	 
	{

		//Create first message here and regenerate later on as needed
		navi_msg_queue = CMD_TAG_NAVI_SLEEP_REQUEST;
		auxi_msg_queue = CMD_TAG_AUXI_SLEEP_REQUEST;


		//initialize/reset shared flags before use
		BooleanBitFlags::clearFlagBit(flagSet_SystemStatus2, _BTFG_NAVI_ACKNOWLEDGEMENT_);
		BooleanBitFlags::clearFlagBit(flagSet_SystemStatus2, _BTFG_AUXI_ACKNOWLEDGEMENT_);
		BooleanBitFlags::clearFlagBit(flagSet_SystemStatus2, _BTFG_RUN_TASKS_ON_MAIN_NOW_);
		
		
		//save the state of the motor power before shutting it off to go to sleep
		//Let motor_power_prev_state = enable_mtr_pwr
		if( BooleanBitFlags::flagIsSet(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_) )
		{
			BooleanBitFlags::setFlagBit(flagSet_SystemControls1, _BTFG_MTR_PREV_STATE_);
		}//end if
		else
		{
			BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_MTR_PREV_STATE_);
		}//end else
		
		//set to shut down motor when sleeping for safety
		BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);
		
		currentMode = SYSTEM_SLEEPING;//Set mode to SYSTEM_SLEEPING *begin*				
		

	}//end else if
	//Sleep Request Acknowledgement
	else if (commandTag == CMD_TAG_SYSTEM_IS_SLEEPING_ACK &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SLEEPREQUESTACKNOWLEDGEMENT_) )
				|| (roverComm == ROVERCOMM_COMM && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_SLEEPREQUESTACKNOWLEDGEMENT_))
				|| (roverComm == ROVERCOMM_NAVI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_SLEEPREQUESTACKNOWLEDGEMENT_))
				|| (roverComm == ROVERCOMM_AUXI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_SLEEPREQUESTACKNOWLEDGEMENT_))
			)
		)	 
	{

		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_NAVI)//If command was from NAVI
		{
			//navi_acknowledgement = true
			BooleanBitFlags::setFlagBit(flagSet_SystemStatus2, _BTFG_NAVI_ACKNOWLEDGEMENT_);
			//Put NAVI to sleep
			_PRINT_SLEEPING_AND_WAKEUP_STATUS_(F("NAVI_SLEEP"));//output to PC for debug
			sleeperNAVI->goToSleep();//update awake flag status			
				//(actually NAVI puts itself to sleep after receiving a sleep request command and sending the Sleep Request Acknowledgement, but MAIN still needs to update the sleep status of NAVI before going to sleep itself, so it can wake up NAVI correctly)
				
		}//end if
		else if (originRoverCommType == ROVERCOMM_AUXI)//else if command was from AUXI
		{
			//auxi_acknowledgement = true
			BooleanBitFlags::setFlagBit(flagSet_SystemStatus2, _BTFG_AUXI_ACKNOWLEDGEMENT_);
			//Put AUXI to sleep
			_PRINT_SLEEPING_AND_WAKEUP_STATUS_(F("AUXI_SLEEP"));//output to PC for debug
			sleeperAUXI->goToSleep();//update awake flag status
				//(actually AUXI puts itself to sleep after receiving a sleep request command and sending the Sleep Request Acknowledgement, but MAIN still needs to update the sleep status of AUXI before going to sleep itself, so it can wake up AUXI correctly)
			
			
		}//end else if	
		//else do nothing
		
		//once MAIN gets an ack for system sleeping from both NAVI and AUXI
		if( BooleanBitFlags::flagIsSet(flagSet_SystemStatus2, _BTFG_NAVI_ACKNOWLEDGEMENT_) && BooleanBitFlags::flagIsSet(flagSet_SystemStatus2, _BTFG_AUXI_ACKNOWLEDGEMENT_) )
		{
			//run_task_on_main_now = true
			BooleanBitFlags::setFlagBit(flagSet_SystemStatus2, _BTFG_RUN_TASKS_ON_MAIN_NOW_);		
		}//end if
	}//end else if
	//Set Motor Power Enable
	else if (commandTag == CMD_TAG_SET_MOTOR_POWER_ENABLE &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORPOWERENABLE_) )
				|| (roverComm == ROVERCOMM_COMM && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORPOWERENABLE_))
				|| (roverComm == ROVERCOMM_NAVI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORPOWERENABLE_))
				|| (roverComm == ROVERCOMM_AUXI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORPOWERENABLE_))
			)
		)	 
	{

		if( strcmp( commandData, getMsgString(3) ) == 0 )//if enable motor power, where getMsgString(3) is "on"
		{
			//turn on the motor	enable
			BooleanBitFlags::setFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);//enable_mtr_pwr = true
			comm_msg_queue = CMD_TAG_ENABLING_MTR_PWR;
			navi_msg_queue = CMD_TAG_ENABLING_MTR_PWR;
			auxi_msg_queue = CMD_TAG_ENABLING_MTR_PWR;//to be redirected to CMNC
		}//end if
		else//else disable motor power
		{
			//turn off the motor enable		
			BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);//enable_mtr_pwr = false
			comm_msg_queue = CMD_TAG_DISABLING_MTR_PWR;
			navi_msg_queue = CMD_TAG_DISABLING_MTR_PWR;
			auxi_msg_queue = CMD_TAG_DISABLING_MTR_PWR;//to be redirected to CMNC
		}//end else		
			
	}//end else if
	//Get Motor Power Status
	else if (commandTag == CMD_TAG_MTR_PWR_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_MOTORPOWERSTATUS_) )
				|| (roverComm == ROVERCOMM_COMM && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_MOTORPOWERSTATUS_))
				|| (roverComm == ROVERCOMM_NAVI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_MOTORPOWERSTATUS_))
				|| (roverComm == ROVERCOMM_AUXI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_MOTORPOWERSTATUS_))
			)
		)	 
	{

		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_COMM)//If command was from COMM
		{
			comm_msg_queue = CMD_TAG_MTR_PWR_STATUS;
		}//end if
		else if (originRoverCommType == ROVERCOMM_NAVI)//If command was from NAVI
		{
			navi_msg_queue = CMD_TAG_MTR_PWR_STATUS;
		}//end else if
		else if (originRoverCommType == ROVERCOMM_AUXI)//else if command was from AUXI
		{
			auxi_msg_queue = CMD_TAG_MTR_PWR_STATUS;			
		}//end else if
		//else do nothing

	}//end else if
	//Get Mid Right Encoder Status
	else if (commandTag == CMD_TAG_ENC_STATUS_MID_RIGHT &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_MIDRIGHTENCODERSTATUS_) )
				|| (roverComm == ROVERCOMM_COMM && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_MIDRIGHTENCODERSTATUS_))
				|| (roverComm == ROVERCOMM_NAVI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_MIDRIGHTENCODERSTATUS_))
				|| (roverComm == ROVERCOMM_AUXI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_MIDRIGHTENCODERSTATUS_))
			)
		)	 
	{

		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_COMM)//If command was from COMM
		{
			comm_msg_queue = CMD_TAG_ENC_STATUS_MID_RIGHT;
		}//end if
		else if (originRoverCommType == ROVERCOMM_NAVI)//If command was from NAVI
		{
			navi_msg_queue = CMD_TAG_ENC_STATUS_MID_RIGHT;
		}//end else if
		else if (originRoverCommType == ROVERCOMM_AUXI)//else if command was from AUXI
		{
			auxi_msg_queue = CMD_TAG_ENC_STATUS_MID_RIGHT;			
		}//end else if
		//else do nothing	
	
	}//end else if
	//Get Mid Left Encoder Status
	else if (commandTag == CMD_TAG_ENC_STATUS_MID_LEFT &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_MIDLEFTENCODERSTATUS_) )
				|| (roverComm == ROVERCOMM_COMM && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_MIDLEFTENCODERSTATUS_))
				|| (roverComm == ROVERCOMM_NAVI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_MIDLEFTENCODERSTATUS_))
				|| (roverComm == ROVERCOMM_AUXI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_MIDLEFTENCODERSTATUS_))
			)
		)	 
	{
	
		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_COMM)//If command was from COMM
		{
			comm_msg_queue = CMD_TAG_ENC_STATUS_MID_LEFT;
		}//end if
		else if (originRoverCommType == ROVERCOMM_NAVI)//If command was from NAVI
		{
			navi_msg_queue = CMD_TAG_ENC_STATUS_MID_LEFT;
		}//end else if
		else if (originRoverCommType == ROVERCOMM_AUXI)//else if command was from AUXI
		{
			auxi_msg_queue = CMD_TAG_ENC_STATUS_MID_LEFT;			
		}//end else if
		//else do nothing		
	
	}//end else if	
	 //Hi Command - DEBUG
	else if (commandTag == CMD_TAG_DEBUG_HI_TEST_MSG &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_HI_) )
				|| (roverComm == ROVERCOMM_COMM && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_HI_))
				|| (roverComm == ROVERCOMM_NAVI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_HI_))
				|| (roverComm == ROVERCOMM_AUXI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_HI_))
			)
		)		 	 
	{

		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_COMM)//If command was from COMM
		{
			comm_msg_queue = CMD_TAG_DEBUG_HI_TEST_MSG;
		}//end if
		else if (originRoverCommType == ROVERCOMM_NAVI)//If command was from NAVI
		{
			navi_msg_queue = CMD_TAG_DEBUG_HI_TEST_MSG;
		}//end else if
		else if (originRoverCommType == ROVERCOMM_AUXI)//else if command was from AUXI
		{
			auxi_msg_queue = CMD_TAG_DEBUG_HI_TEST_MSG;			
		}//end else if
		//else do nothing	
	
	}//end if
	 //Bye Command - DEBUG
	else if (commandTag == CMD_TAG_DEBUG_BYE_TEST_MSG &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_BYE_) )
				|| (roverComm == ROVERCOMM_COMM && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_BYE_))
				|| (roverComm == ROVERCOMM_NAVI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_BYE_))
				|| (roverComm == ROVERCOMM_AUXI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_BYE_))
			)
		)		 	 
	{

		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_COMM)//If command was from COMM
		{
			comm_msg_queue = CMD_TAG_DEBUG_BYE_TEST_MSG;
		}//end if
		else if (originRoverCommType == ROVERCOMM_NAVI)//If command was from NAVI
		{
			navi_msg_queue = CMD_TAG_DEBUG_BYE_TEST_MSG;
		}//end else if
		else if (originRoverCommType == ROVERCOMM_AUXI)//else if command was from AUXI
		{
			auxi_msg_queue = CMD_TAG_DEBUG_BYE_TEST_MSG;			
		}//end else if
		//else do nothing	
	
	}//end if
	 //Invalid - DEBUG
	else if (
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_INVALID_) )
				|| (roverComm == ROVERCOMM_COMM && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_INVALID_))
				|| (roverComm == ROVERCOMM_NAVI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_INVALID_))
				|| (roverComm == ROVERCOMM_AUXI && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_INVALID_))
			)	
		)
	{
	
		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_COMM)//If command was from COMM
		{
			comm_msg_queue = CMD_TAG_INVALID_CMD;
		}//end if
		else if (originRoverCommType == ROVERCOMM_NAVI)//If command was from NAVI
		{
			navi_msg_queue = CMD_TAG_INVALID_CMD;
		}//end else if
		else if (originRoverCommType == ROVERCOMM_AUXI)//else if command was from AUXI
		{
			auxi_msg_queue = CMD_TAG_INVALID_CMD;			
		}//end else if
		//else do nothing	
	
	}//end else if
	 //else output nothing	

	return;	
			
}//end of commandDirector()
void createDataFromQueueFor(byte roverCommType)
{


	//Note: The origin of the messsage will change every time it passes through an Arduino (i.e. using the RoverCommandProcessor::createCmd() with a Rover Comm Type passed to it). It shows the last originating Arduino that handled the data. If the true origin is required, that should be placed in the command data where it's not altered.

	byte queueOfInterest;
	char * commandDataOfInterest;//holds the rover's command data string
	char createdCommand[ROVER_COMM_SENTENCE_LENGTH];//holds the pointer to the created command (createdCommand is the output of the method call RoverCommandCreator::createCmd)
					
	//Create variables needed for the data packaging (i.e. encoder status)
	char commandDataCharArray[_MAX_ROVER_COMMAND_DATA_LEN_];
	byte commandDataCharArraySize;
	byte roverCommActualDestination;//holds the actual/final destination of the data
				
				
	//Based on the roverCommType of interest, set which queue and rover data the outgoing message should be based on
	if (roverCommType == ROVERCOMM_PC_USB)
	{
		queueOfInterest = pc_usb_msg_queue;
		roverCommActualDestination = roverCommType;//the rover comm type will be the actual destination for ROVERCOMM_PC_USB since it's the only destination for that data channel.
		if (roverDataForPC_USB != NULL)//make sure the roverDataPointer is not NULL
		{
			commandDataOfInterest = roverDataForPC_USB->getCommandData();
		}//end if
		else
		{
			commandDataOfInterest = "";//else if it's NULL, set the data to nothing
		}//end else		
	}//end if
	else if (roverCommType == ROVERCOMM_COMM || roverCommType == ROVERCOMM_CMNC)
	{
		queueOfInterest = comm_msg_queue;

		//Check to see that the destination for the COMM channel is either COMM or CMNC. Anything else is invalid.
		if(comm_cmnc_destination_selection == ROVERCOMM_COMM || comm_cmnc_destination_selection == ROVERCOMM_CMNC)
		{
			roverCommActualDestination = comm_cmnc_destination_selection;//let the actual destination be determined by comm_cmnc_destination_selection
		}//end if
		else//invalid state, error out
		{
			_SERIAL_DEBUG_CHANNEL_.println(F("ErrUnkDest"));//error, unknown destination
		}//end else
		
		if (roverDataForCOMM != NULL)//make sure the roverDataPointer is not NULL
		{
			commandDataOfInterest = roverDataForCOMM->getCommandData();
		}//end if
		else
		{
			commandDataOfInterest = "";//else if it's NULL, set the data to nothing
		}//end else
	}//end else if
	else if (roverCommType == ROVERCOMM_NAVI)
	{
		queueOfInterest = navi_msg_queue;
		roverCommActualDestination = roverCommType;//the rover comm type will be the actual destination for ROVERCOMM_NAVI since it's the only destination for that data channel.
		if (roverDataForNAVI != NULL)//make sure the roverDataPointer is not NULL
		{
			commandDataOfInterest = roverDataForNAVI->getCommandData();
		}//end if
		else
		{
			commandDataOfInterest = "";//else if it's NULL, set the data to nothing
		}//end else
	}//end else if	
	else if (roverCommType == ROVERCOMM_AUXI)
	{
		queueOfInterest = auxi_msg_queue;
		roverCommActualDestination = roverCommType;//the rover comm type will be the actual destination for ROVERCOMM_AUXI since it's the only destination for that data channel.
		if (roverDataForAUXI != NULL)//make sure the roverDataPointer is not NULL
		{
			commandDataOfInterest = roverDataForAUXI->getCommandData();
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


		//Externally Received Commands	
		case CMD_TAG_COMM_HW_RESET_REQUEST:
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_COMM_HW_RESET_REQUEST, getMsgString(0), createdCommand);
			break;
		case CMD_TAG_ALL_SW_RESET_REQUEST:
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_ALL_SW_RESET_REQUEST, getMsgString(0), createdCommand);
			break;	
		case CMD_TAG_SW_IS_RESETTING_ACK:
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_SW_IS_RESETTING_ACK, getMsgString(0), createdCommand);
			break;
		case CMD_TAG_GENERIC_HEALTH_STATUS_ERROR:		
				RoverCommandCreator::createCmd(error_origin, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_GENERIC_HEALTH_STATUS_ERROR, getMsgString(2), createdCommand);
			break;
		case CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS:		
				RoverCommandCreator::createCmd(error_origin, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS, getMsgString(2), createdCommand);
			break;			
		case CMD_TAG_SYSTEM_READY_STATUS:
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_SYSTEM_READY_STATUS, getMsgString(0), createdCommand);
			break;
		case CMD_TAG_ALL_SLEEP_REQUEST:
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_ALL_SLEEP_REQUEST, getMsgString(0), createdCommand);
			break;
		case CMD_TAG_SYSTEM_IS_SLEEPING_ACK:
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_SYSTEM_IS_SLEEPING_ACK, getMsgString(0), createdCommand);
			break;
		case CMD_TAG_SET_MOTOR_POWER_ENABLE:
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_SET_MOTOR_POWER_ENABLE, getMsgString(0), createdCommand);
			break;
		case CMD_TAG_MTR_PWR_STATUS:
				//if the motor power is on
				if( BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_MTR_POWER_ON_) )
				{
					RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_MTR_PWR_STATUS, getMsgString(3), createdCommand);
				}//end if
				else//the motor power is off
				{
					RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_MTR_PWR_STATUS, getMsgString(4), createdCommand);
				}
			break;			
		case CMD_TAG_ENC_STATUS_MID_RIGHT:				
				//Construct the message for direction, distance, and speed
				RoverMessagePackager::packEncoderStatus(wheelEncoder_MidRight_Direction, wheelEncoder_MidRight_Speed, wheelEncoder_MidRight_Footage, commandDataCharArray, commandDataCharArraySize);
				
				//Create the rover command message with the packaged encoder status
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_ENC_STATUS_MID_RIGHT, commandDataCharArray, createdCommand);
			
			break;					
		case CMD_TAG_ENC_STATUS_MID_LEFT:
		
				//Construct the message for direction, distance, and speed
				RoverMessagePackager::packEncoderStatus(wheelEncoder_MidLeft_Direction, wheelEncoder_MidLeft_Speed, wheelEncoder_MidLeft_Footage, commandDataCharArray, commandDataCharArraySize);
			
				//Create the rover command message with the packaged encoder status
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_ENC_STATUS_MID_LEFT, commandDataCharArray, createdCommand);
				
			break;					
		case CMD_TAG_DEBUG_HI_TEST_MSG:
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_DEBUG_HI_TEST_MSG, commandDataOfInterest, createdCommand);
			break;
		case CMD_TAG_DEBUG_BYE_TEST_MSG:
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_DEBUG_BYE_TEST_MSG, commandDataOfInterest, createdCommand);
			break;
		case CMD_TAG_INVALID_CMD:
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_INVALID_CMD, getMsgString(0), createdCommand);
			break;
			
			
			
		//Internally Generated Commands - Internally Generated by this Arduino. So there are no received command for these types of commands.
		case CMD_TAG_INVALID_STATE_OR_MODE_ERROR_STATUS: //The error message will be redirected out through all the Arduinos and out to CMNC
				//Only allow destination of ROVERCOMM_PC_USB (to go to PC_USB) and ROVERCOMM_CMNC (to go to CMNC, through COMM)
				if(roverCommActualDestination == ROVERCOMM_PC_USB || roverCommActualDestination == ROVERCOMM_CMNC)
				{
					RoverCommandCreator::createCmd(error_origin, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_INVALID_STATE_OR_MODE_ERROR_STATUS, getMsgString(2), createdCommand);
				}//end if				
				//else do nothing. CMD_TAG_INVALID_STATE_OR_MODE_ERROR_STATUS should not be sent to other Arduino channels other than ROVERCOMM_PC_USB and ROVERCOMM_CMNC (through COMM) as other Arduinos are not currently programmed to handle that type of message.
			break;	
		case CMD_TAG_NAVI_SW_RESET_REQUEST:
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_NAVI_SW_RESET_REQUEST, getMsgString(0), createdCommand);
			break;
		case CMD_TAG_COMM_SW_RESET_REQUEST:
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_COMM_SW_RESET_REQUEST, getMsgString(0), createdCommand);
			break;
		case CMD_TAG_SYSTEM_GO_STATUS:
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_SYSTEM_GO_STATUS, getMsgString(0), createdCommand);
			break;
		case CMD_TAG_NAVI_SLEEP_REQUEST:
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_NAVI_SLEEP_REQUEST, getMsgString(0), createdCommand);
			break;
		case CMD_TAG_COMM_SLEEP_REQUEST:
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_COMM_SLEEP_REQUEST, getMsgString(0), createdCommand);
			break;
		case CMD_TAG_ENABLING_MTR_PWR:
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_ENABLING_MTR_PWR, getMsgString(0), createdCommand);
			break;
		case CMD_TAG_DISABLING_MTR_PWR:
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_DISABLING_MTR_PWR, getMsgString(0), createdCommand);
			break;
		case CMD_TAG_SYNC_ERROR_STATUS:
				RoverCommandCreator::createCmd(error_origin, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_SYNC_ERROR_STATUS, getMsgString(2), createdCommand);
			break;
		case CMD_TAG_SLEEP_ERROR_STATUS:
				RoverCommandCreator::createCmd(error_origin, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_SLEEP_ERROR_STATUS, getMsgString(2), createdCommand);
			break;			
		case CMD_TAG_SW_RESET_ERROR_STATUS:
				RoverCommandCreator::createCmd(error_origin, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_SW_RESET_ERROR_STATUS, getMsgString(2), createdCommand);
			break;	
		case CMD_TAG_ALL_HW_RESET_REQUEST:
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_ALL_HW_RESET_REQUEST, getMsgString(0), createdCommand);
			break;			
		default:
				RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_INVALID_CMD, getMsgString(1), createdCommand);//output invalid command
			break;
	}//end switch	
	
	if (roverCommActualDestination == ROVERCOMM_PC_USB)
	{
		sprintf(txMsgBuffer_PC_USB, createdCommand);
	}//end if
	else if (roverCommActualDestination == ROVERCOMM_COMM || roverCommActualDestination == ROVERCOMM_CMNC)
	{
		sprintf(txMsgBuffer_COMM, createdCommand);
	}//end else if
	else if (roverCommActualDestination == ROVERCOMM_NAVI)
	{
		sprintf(txMsgBuffer_NAVI, createdCommand);
	}//end else if
	else if (roverCommActualDestination == ROVERCOMM_AUXI)
	{
		sprintf(txMsgBuffer_AUXI, createdCommand);
	}//end else if
	 //else

	 
	 comm_cmnc_destination_selection = ROVERCOMM_COMM;//once done with creating the data, reset the comm_cmnc_destination_selection variable to default
	 
	return;

}//end of createDataFromQueueFor()
void setAllErrorFlagsTo(boolean choice)
{

	//Note: During (re-)initialization this function doesn't need to be called since the flag variable gets a direct assigned it an initial value. (ex: someFlag = _BTFG_NONE_; )

	BooleanBitFlags::assignFlagBit(flagSet_Error1, _BTFG_INVALID_STATE_OR_MODE_ERROR_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_Error1, _BTFG_SYNC_ERROR_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_Error1, _BTFG_SW_RESET_ERROR_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_Error1, _BTFG_SLEEPING_ERROR_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_Error1, _BTFG_GENERIC_HEALTH_ERROR_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_Error1, _BTFG_GENERIC_SYSTEM_ERROR_, choice);

}//end of setAllErrorFlagsTo()
void setAllMessageControlFlagsTo(boolean choice)
{

	//Note: During (re-)initialization this function doesn't need to be called since the flag variable gets a direct assigned it an initial value. (ex: someFlag = _BTFG_NONE_; )
	
	BooleanBitFlags::assignFlagBit(flagSet_MessageControl1, _BTFG_REDIRECT_TO_PC_USB_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_MessageControl1, _BTFG_REDIRECT_TO_COMM_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_MessageControl1, _BTFG_REDIRECT_TO_NAVI_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_MessageControl1, _BTFG_REDIRECT_TO_AUXI_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH1_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH2_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH3_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH4_, choice);
	
}//end of setAllMessageControlFlagsTo()
void setAllSystemStatusFlagsTo(boolean choice)
{

	//Note: During (re-)initialization this function doesn't need to be called since the flag variable gets a direct assigned it an initial value. (ex: someFlag = _BTFG_NONE_; )

	BooleanBitFlags::assignFlagBit(flagSet_SystemStatus1, _BTFG_FIRST_TRANSMISSION_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_SystemStatus1, _BTFG_MTR_POWER_ON_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_SystemStatus1, _BTFG_COMM_SYSTEM_READY_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_SystemStatus1, _BTFG_NAVI_SYSTEM_READY_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_SystemStatus1, _BTFG_AUXI_SYSTEM_READY_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_SystemStatus1, _BTFG_ALL_SYSTEMS_GO_, choice);
	
	BooleanBitFlags::assignFlagBit(flagSet_SystemStatus2, _BTFG_NAVI_ACKNOWLEDGEMENT_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_SystemStatus2, _BTFG_AUXI_ACKNOWLEDGEMENT_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_SystemStatus2, _BTFG_RUN_TASKS_ON_MAIN_NOW_, choice);

}//end of setAllSystemStatusFlagsTo()
void setAllSystetmControlsFlagsTo(boolean choice)
{
	//Note: During (re-)initialization this function doesn't need to be called since the flag variable gets a direct assigned it an initial value. (ex: someFlag = _BTFG_NONE_; )
	
	BooleanBitFlags::assignFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_, choice);
	BooleanBitFlags::assignFlagBit(flagSet_SystemControls1, _BTFG_MTR_PREV_STATE_, choice);

}//end of setAllSystetmControlsFlagsTo()
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
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_ALLSLEEPREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SLEEPREQUESTACKNOWLEDGEMENT_, choice);
		
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORPOWERENABLE_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_MOTORPOWERSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_MIDRIGHTENCODERSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_MIDLEFTENCODERSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_HI_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_BYE_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_INVALID_, choice);
		
	}//end if
	else if(roverComm == ROVERCOMM_COMM)
	{
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_COMMHWRESETREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_SWRESETACKNOWLEDGMENT_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_ALLSLEEPREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_SLEEPREQUESTACKNOWLEDGEMENT_, choice);
		
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORPOWERENABLE_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_MOTORPOWERSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_MIDRIGHTENCODERSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_MIDLEFTENCODERSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_HI_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_BYE_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_INVALID_, choice);
		
	}//end else if
	else if(roverComm == ROVERCOMM_NAVI)
	{
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_COMMHWRESETREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_SWRESETACKNOWLEDGMENT_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_ALLSLEEPREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_SLEEPREQUESTACKNOWLEDGEMENT_, choice);
		
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORPOWERENABLE_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_MOTORPOWERSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_MIDRIGHTENCODERSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_MIDLEFTENCODERSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_HI_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_BYE_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_INVALID_, choice);
		
	}//end else if	
	else if(roverComm == ROVERCOMM_AUXI)
	{
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_COMMHWRESETREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_SWRESETACKNOWLEDGMENT_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_ALLSLEEPREQUEST_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_SLEEPREQUESTACKNOWLEDGEMENT_, choice);
		
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORPOWERENABLE_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_MOTORPOWERSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_MIDRIGHTENCODERSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_MIDLEFTENCODERSTATUS_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_HI_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_BYE_, choice);
		BooleanBitFlags::assignFlagBit(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_INVALID_, choice);
		
	}//end else if		
		
}//end of setAllCommands()
void redirectData(RoverComm * roverComm)
{
	//Note: The redirect data function get its destination from the received data itself and not these flags. And it calls txData on it's own so it's not affected by createDataFromQueueFor() either.
	
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
	
	
	//If the destination is from: 1) COMM (CMNC), NAVI, AUXI to PC_USB or 2) PC_USB to PC_USB (loopback)
	if (roverCommType == ROVERCOMM_PC_USB)
	{
		//And if redirection to PC_USB is allowed
		if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_REDIRECT_TO_PC_USB_))
		{
			#ifdef _DEBUG_REDIRECTION_NOTICE
				Serial.println(F("Redirect2PC_USB"));
			#endif
			//Then transmit the data out to PC_USB
			txData(roverComm->getRxData(), ROVERCOMM_PC_USB);
		}//end if		 
	}//end if	
	//Else if the destination is from: 1) PC_USB, NAVI, AUXI to COMM (CMNC) or 2) COMM (CMNC) to COMM (CMNC) (loopback)
	else if (roverCommType == ROVERCOMM_COMM || roverCommType == ROVERCOMM_CMNC)//CMNC has to go through COMM
	{
		//And if redirection to COMM (CMNC) is allowed
		if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_REDIRECT_TO_COMM_))//Checks to see if redirection is allowed to COMM
		{
			#ifdef _DEBUG_REDIRECTION_NOTICE
				Serial.println(F("Redirect2COMM"));
			#endif
			//Then transmit the data out to COMM (CMNC)
			txData(roverComm->getRxData(), ROVERCOMM_COMM);
		}//end if		 
	}//end if		
	//Else if the destination is from: 1) PC_USB, COMM (CMNC), AUXI to NAVI or 2) NAVI to NAVI (loopback)
	else if (roverCommType == ROVERCOMM_NAVI)
	{
		//And if redirection to NAVI is allowed
		if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_REDIRECT_TO_NAVI_))//Checks to see if redirection is allowed to NAVI
		{
			#ifdef _DEBUG_REDIRECTION_NOTICE
				Serial.println(F("Redirect2NAVI"));
			#endif
			//Then transmit the data out to NAVI
			txData(roverComm->getRxData(), ROVERCOMM_NAVI);
		}//end if		 
	}//end if
	//Else if the destination is from: 1) PC_USB, COMM (CMNC), NAVI to AUXI or 2) AUXI to AUXI (loopback)
	else if (roverCommType == ROVERCOMM_AUXI)
	{
		//And if redirection to AUXI is allowed
		if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_REDIRECT_TO_AUXI_))//Checks to see if redirection is allowed to AUXI
		{
			#ifdef _DEBUG_REDIRECTION_NOTICE
				Serial.println(F("Redirect2AUXI"));
			#endif
			//Then transmit the data out to AUXI
			txData(roverComm->getRxData(), ROVERCOMM_AUXI);
		}//end if		 
	}//end if
	
	return;
	
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
		case RX_COMMUNICATIONS: //Mode: POWER_ON_AND_HW_RESET
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case DATA_VALIDATION: //Mode: POWER_ON_AND_HW_RESET
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case DATA_FILTER: //Mode: POWER_ON_AND_HW_RESET
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;	
		case READ_INPUTS: //Mode: POWER_ON_AND_HW_RESET
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case PROCESS_DATA: //Mode: POWER_ON_AND_HW_RESET
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case CONTROL_OUTPUTS: //Mode: POWER_ON_AND_HW_RESET
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case CREATE_DATA: //Mode: POWER_ON_AND_HW_RESET
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case TX_COMMUNICATIONS: //Mode: POWER_ON_AND_HW_RESET
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)	
			break;			
		default: //default state
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
		case RX_COMMUNICATIONS: //Mode: INITIALIZATION
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case DATA_VALIDATION: //Mode: INITIALIZATION
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case DATA_FILTER: //Mode: INITIALIZATION
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;	
		case READ_INPUTS: //Mode: INITIALIZATION
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case PROCESS_DATA: //Mode: INITIALIZATION
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case CONTROL_OUTPUTS: //Mode: INITIALIZATION
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case CREATE_DATA: //Mode: INITIALIZATION
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case TX_COMMUNICATIONS: //Mode: INITIALIZATION
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)				
			break;
		default: //default state
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
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_COMMHWRESETREQUEST_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_);
			//For NAVI			
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_);
			//For AUXI
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_);

			
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
			//Read Motor Status
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
				//Note: If system ready msg, hw reset request, generic system error, or All SW Reset Request from COMM/CMNC, see "Command Options" below for more info.
				//Note: Either you should get HW or SW reset, generic system error, or system ready messages from COMM. as everything else was filtered out
				//No redirections in SYNCHRONIZATION.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH2_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh2_COMM, ROVERCOMM_COMM);
			}//end if				
			//Process NAVI command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//Note: If system ready msg, or generic system error received from NAVI, see "Command Options" below for more info.
				//Note: Either you should get system ready messages, or generic system error from NAVI. as everything else was filtered out
				//No redirections in SYNCHRONIZATION.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH3_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh3_COMM, ROVERCOMM_NAVI);
			}//end if				
			//Process AUXI command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//Note: If system ready msg, generic system error, or generic health error received from AUXI, see "Command Options" below for more info.
				//Note: Either you should get system ready messages, generic system error, or generic health error from AUXI. as everything else was filtered out	
				//No redirections in SYNCHRONIZATION.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH4_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh4_COMM, ROVERCOMM_AUXI);
			}//end if

							
			//Run highest priority functions here (after command director). //this will override any lower priority messages (i.e. system go). This will overwrite anything else. (i.e. system ready)
	
	
	
			#ifndef _DEBUG_DISABLE_MAIN_SYNC_TIMEOUT //normally the timeout code would run. Can disable it for debugging purposes
				//If all systems are not ready, and it's not yet a systems go
				if( ! BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_ALL_SYSTEMS_GO_) )
				{
					//increment counter
					timeout_counter++;
					//if MAIN has been stuck in SYNCHRONIZATION for a long time while waiting on NAVI, AUXI, or COMM, it will send a sync error status
					if(timeout_counter >= MAIN_SYNC_TIMEOUT_VALUE)
					{
						currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		
						//shut down motor when in error for safety
						error_origin = ROVERCOMM_MAIN;
						BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);					
						comm_msg_queue = CMD_TAG_SYNC_ERROR_STATUS;							
						pc_usb_msg_queue = CMD_TAG_SYNC_ERROR_STATUS;											
						//set sync_error = true
						BooleanBitFlags::setFlagBit(flagSet_Error1, _BTFG_SYNC_ERROR_);			
						//(Note: the sync_error flag can only be cleared with a sw reset or hw reset)
						//initialize/reset shared counter before use
						timeout_counter = 0;	
					}//end if
				}//end if		
			#endif
			break;		
		case CONTROL_OUTPUTS: //Mode: SYNCHRONIZATION
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;			
		case CREATE_DATA: //Mode: SYNCHRONIZATION
			//Creates data for PC_USB
			if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_PC_USB);
				
				//skip auto data	
				
			}//end if
			//Creates data for COMM
			if (comm_msg_queue != CMD_TAG_NO_MSG)
			{
			
				if(comm_cmnc_destination_selection == ROVERCOMM_COMM)//data is for COMM
				{
					createDataFromQueueFor(ROVERCOMM_COMM);
				}//end if
				else if(comm_cmnc_destination_selection == ROVERCOMM_CMNC) //data is for CMNC
				{
					createDataFromQueueFor(ROVERCOMM_CMNC);
				}//end else if
				else//invalid state, error out
				{
					_SERIAL_DEBUG_CHANNEL_.println(F("ErrUnkDest"));//error, unknown destination
				}//end else
				
				//skip auto data
								
			}//end if
			//Creates data for NAVI
			if (navi_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_NAVI);
				
				//skip auto data	
				
			}//end if
			//Creates data for AUXI
			if (auxi_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_AUXI);
				
				//skip auto data	
				
				
			}//end if			
			
			//Clear Motor Power Status
			BooleanBitFlags::clearFlagBit(flagSet_SystemStatus1, _BTFG_MTR_POWER_ON_);
			
			break;
		case TX_COMMUNICATIONS: //Mode: SYNCHRONIZATION
		
			//Note: No redirection during SYNCHRONIZATION.

			//Sends data to PC_USB
			if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
			{
				txData(txMsgBuffer_PC_USB, ROVERCOMM_PC_USB);
			}//end if
			//Sends data to COMM
			if (comm_msg_queue != CMD_TAG_NO_MSG)
			{
				txData(txMsgBuffer_COMM, ROVERCOMM_COMM);//Note: This just sends the data as created through the COMM channel. Whether it goes to CMNC or COMM, that would be determined in the createDataFromQueueFor().
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
		default: //default state
			 //This code should never execute, if it does, there is a logical or programming error
			runModeFunction_default();//no state needed, all states do the same thing
			break;
	}//end switch
}//end of runModeFunction_SYNCHRONIZATION()
void runModeFunction_NORMAL_OPERATIONS(byte currentState)
{

	_PRINT_MODE_(F("MODE: NORMAL_OPERATIONS"));
	switch (currentState)
	{
		case RUN_HOUSEKEEPING_TASKS: //Mode: NORMAL_OPERATIONS
			runBackgroundTasks();
			break;
		case RX_COMMUNICATIONS: //Mode: NORMAL_OPERATIONS

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
		case DATA_VALIDATION: //Mode: NORMAL_OPERATIONS

		
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
		case DATA_FILTER: //Mode: NORMAL_OPERATIONS

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
			
			/*

				NOTE: THIS PART OF CODE IS CUT OUT TO MAKE IT MORE EFFICIENT. Jumping straight to enabling all commands to be allowed.

				//First initialize all command choices to false
				setAllCommandFiltersTo(false, ROVERCOMM_PC_USB);//for PC_USB
				setAllCommandFiltersTo(false, ROVERCOMM_COMM);//for COMM
				setAllCommandFiltersTo(false, ROVERCOMM_NAVI);//for NAVI
				setAllCommandFiltersTo(false, ROVERCOMM_AUXI);//for AUXI
			*/
			
			//Then enable the allowed commands for this mode:
			//For PC_USB
			//No filter on PC_USB data. (Allow all data from PC_USB)
			//No commands from PC_USB are filtered, so set all to true.
			setAllCommandFiltersTo(true, ROVERCOMM_PC_USB);			
			//For COMM
			//No commands from COMM are filtered, so set all to true.
			setAllCommandFiltersTo(true, ROVERCOMM_COMM);			
			//For NAVI			
			//No commands from NAVI are filtered, so set all to true.
			setAllCommandFiltersTo(true, ROVERCOMM_NAVI);			
			//For AUXI
			//No commands from AUXI are filtered, so set all to true.
			setAllCommandFiltersTo(true, ROVERCOMM_AUXI);			

			
			//Transmit data and/or execute command
						
			//For data from PC_USB, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, MAIN
			if (ch1Status == DATA_STATUS_VALID)
			{
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//Allow redirections for PC_USB
				//Note: this is a local .ino function

				dataDirector(roverDataCh1_COMM, DATA_REDIRECT_ENABLED, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH1_);//DataDirection will set the "data was for MAIN flag" to true if it was for this Arduino

				/*
				Allow all data from PC_USB.
				*/

			}//end if

			//For data from COMM, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, MAIN
			if (ch2Status == DATA_STATUS_VALID)
			{
			
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//Allow redirections for COMM
				//Note: this is a local .ino function

				dataDirector(roverDataCh2_COMM, DATA_REDIRECT_ENABLED, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH2_);//DataDirection will set the "data was for MAIN flag" to true if it was for this Arduino
					

				/*
				Allow all data from COMM.
				*/

				
			}//end if
			
			//For data from NAVI, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, MAIN
			if (ch3Status == DATA_STATUS_VALID)
			{
			
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//Allow redirections for NAVI
				//Note: this is a local .ino function

				dataDirector(roverDataCh3_COMM, DATA_REDIRECT_ENABLED, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH3_);//DataDirection will set the "data was for MAIN flag" to true if it was for this Arduino
				
				/*
				Allow all data from NAVI.
				*/

				
			}//end if
			
			
			//For data from AUXI, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, MAIN
			if (ch4Status == DATA_STATUS_VALID)
			{
			
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//Allow redirections for AUXI
				//Note: this is a local .ino function

				dataDirector(roverDataCh4_COMM, DATA_REDIRECT_ENABLED, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH4_);//DataDirection will set the "data was for MAIN flag" to true if it was for this Arduino
				
				/*
				Allow all data from AUXI.
				*/

				
			}//end if		

			
			break;	
		case READ_INPUTS: //Mode: NORMAL_OPERATIONS

			//Read Encoder - MidLeft
			wheelEncoder_MidLeft_Direction = wheelEncoder_MidLeft->getDirection();
			wheelEncoder_MidLeft_Speed = wheelEncoder_MidLeft->getSpeed();
			wheelEncoder_MidLeft_Footage = wheelEncoder_MidLeft->getFootage();
			//Read Encoder - MidRight
			wheelEncoder_MidRight_Direction = wheelEncoder_MidRight->getDirection();
			wheelEncoder_MidRight_Speed = wheelEncoder_MidRight->getSpeed();
			wheelEncoder_MidRight_Footage = wheelEncoder_MidRight->getFootage();		
		
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
		case PROCESS_DATA: //Mode: NORMAL_OPERATIONS

			#ifdef _DEBUG_PRINT_TIMEOUT_COUNTER_VALUE_
				Serial.println(timeout_counter);//DEBUG
			#endif
			
			//Process Encoders
				//Encoder Statuses: When applicable, the Encoder Statuses are captured in READ_INPUTS and stores in a set of variables, the message is queued up by commandDirector of PROCESS_DATA, and then processed in CREATE_DATA with createDataFromQueueFor. The variables will keep their values until overwritten in another visit to the READ_INPUTS state.
		
			//Read Motor Status
				//Motor Power Status: When applicable, the Motor Power Status is captured in READ_INPUTS with a flag, the message is queued up by commandDirector of PROCESS_DATA, and then processed in CREATE_DATA with createDataFromQueueFor, then the flag is cleared.
						
			
			//Run lower priority functions here.
			//These messages and flags may be overrided with commandDirector()			
			
		
			
			//Process PC_USB command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//All other messages are allowed from PC_USB. Use with caution.
				
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH1_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh1_COMM, ROVERCOMM_PC_USB);
			}//end if			
			//Process COMM command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//Note: If system ready msg, hw reset request, or All SW Reset Request from COMM/CMNC, see "Command Options" below for more info.
				//Note: Either you should get HW or SW reset, or system ready messages from COMM. as everything else was filtered out
				
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH2_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh2_COMM, ROVERCOMM_COMM);
			}//end if				
			//Process NAVI command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//Note: If system ready msg received from NAVI, see "Command Options" below for more info.
				//Note: Either you should get system ready messages from NAVI. as everything else was filtered out
				
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH3_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh3_COMM, ROVERCOMM_NAVI);
			}//end if				
			//Process AUXI command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//Note: If system ready msg received from AUXI, see "Command Options" below for more info.
				//Note: Either you should get system ready messages or generic health errors from AUXI. as everything else was filtered out
				
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH4_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh4_COMM, ROVERCOMM_AUXI);
			}//end if
							
			//Run highest priority functions here (after command director). //this will override any lower priority messages (i.e. system go). This will overwrite anything else. (i.e. system ready)
				
			break;		
		case CONTROL_OUTPUTS: //Mode: NORMAL_OPERATIONS
				//if motor enable is on
				if(BooleanBitFlags::flagIsSet(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_))
				{
					//Turn motor MOSFET on
					mtrPowerCtrlr->setMotorPower(MTR_ENABLED);
				}//end if
				else//else motor enable is off
				{
					//Turn motor MOSFET off
					mtrPowerCtrlr->setMotorPower(MTR_DISABLED);
				}//end else
			break;		
		case CREATE_DATA: //Mode: NORMAL_OPERATIONS

			//Creates data for PC_USB
			if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_PC_USB);
				
				//skip auto data	
				
				
			}//end if
			//PC_USB doesn't get auto data (since it normally doesn't get monitored, and having data generated all the time would slow the system down)
			if (comm_msg_queue != CMD_TAG_NO_MSG)//if there is normal (non auto) data to send out through COMM
			{
				if(comm_cmnc_destination_selection == ROVERCOMM_COMM)//data is for COMM
				{
					createDataFromQueueFor(ROVERCOMM_COMM);
				}//end if
				else if(comm_cmnc_destination_selection == ROVERCOMM_CMNC) //data is for CMNC
				{
					createDataFromQueueFor(ROVERCOMM_CMNC);
				}//end else if
				else//invalid state, error out
				{
					_SERIAL_DEBUG_CHANNEL_.println(F("ErrUnkDest"));//error, unknown destination
				}//end else
			}//end if	
			//Since this is a shared data channel, create message corresponding to the next auto data for COMM, then for CMNC			
			else if( auto_MAIN_to_COMM_data_cnt < sizeof(auto_MAIN_to_COMM_data_array) )
				//if there is auto data for COMM and it has not been all sent yet
				//Note: Since the counter is a byte, it's lowest value is 0. And the array size can't be smaller than zero. So this can only be true if the array has data, i.e. it's size is greater than 0 and the counter is less than the size of the array. If the array is empty, the size would be 0 and the counter's lowest value would be 0, so it would be equal and not less than, so the if statement would be still false.
			{
				//since there is no custom data, then send the next auto data.
					//create message corresponding to the next auto data for COMM.

					//Assign the next auto message to the queue
					comm_msg_queue = auto_MAIN_to_COMM_data_array[auto_MAIN_to_COMM_data_cnt];

					comm_cmnc_destination_selection = ROVERCOMM_COMM;
					
					//Create the message
					createDataFromQueueFor(ROVERCOMM_COMM);
					
					//Loop/Increment the auto data for the next iteration
					auto_MAIN_to_COMM_data_cnt++;

					//Note: Though auto data increments now, preparing for the next iteration, the queue data was already assigned above and is "latched" or "locked" in for this iteration. As the queue and not the auto data is referred for the rest of this loop iteration.

			}//end else if
			else if ( auto_MAIN_to_CMNC_data_cnt < sizeof(auto_MAIN_to_CMNC_data_array) )		//if there is auto data for CMNC and it has not been all sent yet
				//Note: Since the counter is a byte, it's lowest value is 0. And the array size can't be smaller than zero. So this can only be true if the array has data, i.e. it's size is greater than 0 and the counter is less than the size of the array. If the array is empty, the size would be 0 and the counter's lowest value would be 0, so it would be equal and not less than, so the if statement would be still false.			
			{
					//since there is no custom data, then send the next auto data.
					//create message corresponding to the next auto data for CMNC.

					//Assign the next auto message to the queue
					comm_msg_queue = auto_MAIN_to_CMNC_data_array[auto_MAIN_to_CMNC_data_cnt];

					comm_cmnc_destination_selection = ROVERCOMM_CMNC;
					
					//Create the message
					createDataFromQueueFor(ROVERCOMM_CMNC);
					
					//Loop/Increment the auto data for the next iteration
					auto_MAIN_to_CMNC_data_cnt++;

					//Note: Though auto data increments now, preparing for the next iteration, the queue data was already assigned above and is "latched" or "locked" in for this iteration. As the queue and not the auto data is referred for the rest of this loop iteration.

			}//end else if
			//else do nothing since there was no message and no auto data to send
		
			
			//Creates data for NAVI
			if (navi_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_NAVI);
			}//end if
			else if( auto_MAIN_to_NAVI_data_cnt < sizeof(auto_MAIN_to_NAVI_data_array) )		//if there is auto data for NAVI and it has not been all sent yet
					//Note: Since the counter is a byte, it's lowest value is 0. And the array size can't be smaller than zero. So this can only be true if the array has data, i.e. it's size is greater than 0 and the counter is less than the size of the array. If the array is empty, the size would be 0 and the counter's lowest value would be 0, so it would be equal and not less than, so the if statement would be still false.
			{					
			
				//since there is no custom data, then send the next auto data.
				//create message corresponding to the next auto data for NAVI.
				
				//Assign the next auto message to the queue
				navi_msg_queue = auto_MAIN_to_NAVI_data_array[auto_MAIN_to_NAVI_data_cnt];

				//Create the message
				createDataFromQueueFor(ROVERCOMM_NAVI);
				
				//Loop/Increment the auto data for the next iteration
								
				auto_MAIN_to_NAVI_data_cnt++;
					
				//Note: Though auto data increments now, preparing for the next iteration, the queue data was already assigned above and is "latched" or "locked" in for this iteration. As the queue and not the auto data is referred for the rest of this loop iteration.
				
			}//end else if
			//else do nothing since there was no message and no auto data			
			
			//Creates data for AUXI
			if (auxi_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_AUXI);
			}//end if	
			else if( auto_MAIN_to_AUXI_data_cnt < sizeof(auto_MAIN_to_AUXI_data_array) )		//if there is auto data for AUXI and it has not been all sent yet
					//Note: Since the counter is a byte, it's lowest value is 0. And the array size can't be smaller than zero. So this can only be true if the array has data, i.e. it's size is greater than 0 and the counter is less than the size of the array. If the array is empty, the size would be 0 and the counter's lowest value would be 0, so it would be equal and not less than, so the if statement would be still false.
			{			

				//since there is no custom data, then send the next auto data.
				//create message corresponding to the next auto data for AUXI.

							
				//Assign the next auto message to the queue
				auxi_msg_queue = auto_MAIN_to_AUXI_data_array[auto_MAIN_to_AUXI_data_cnt];

				//Create the message
				createDataFromQueueFor(ROVERCOMM_AUXI);
				
				//Loop/Increment the auto data for the next iteration
								
				auto_MAIN_to_AUXI_data_cnt++;
								
				//Note: Though auto data increments now, preparing for the next iteration, the queue data was already assigned above and is "latched" or "locked" in for this iteration. As the queue and not the auto data is referred for the rest of this loop iteration.
				
			}//end else if
			//else do nothing since there was no message and no auto data			

				
			//reset the auto data counters as needed
			if ( auto_MAIN_to_COMM_data_cnt >= sizeof(auto_MAIN_to_COMM_data_array) && sizeof(auto_MAIN_to_COMM_data_array) > 0)
			//if the counter is equal to or greater than the size of the array and the array isn't empty
			{
				//reset the counter
				auto_MAIN_to_COMM_data_cnt = 0;
			}//end if
			if (auto_MAIN_to_CMNC_data_cnt >= sizeof(auto_MAIN_to_CMNC_data_array) && sizeof(auto_MAIN_to_CMNC_data_array) > 0)
			//if the counter is equal to or greater than the size of the array and the array isn't empty
			{
				//reset the counter
				auto_MAIN_to_CMNC_data_cnt = 0;
			}//end if	
			if ( auto_MAIN_to_NAVI_data_cnt >= sizeof(auto_MAIN_to_NAVI_data_array) && sizeof(auto_MAIN_to_NAVI_data_array) > 0)
			//if the counter is equal to or greater than the size of the array and the array isn't empty
			{
				//reset the counter
				auto_MAIN_to_NAVI_data_cnt = 0;
			}//end if		
			if ( auto_MAIN_to_AUXI_data_cnt >= sizeof(auto_MAIN_to_AUXI_data_array) && sizeof(auto_MAIN_to_AUXI_data_array) > 0)
			//if the counter is equal to or greater than the size of the array and the array isn't empty
			{
				//reset the counter
				auto_MAIN_to_AUXI_data_cnt = 0;
			}//end if

			
				
			//Clear Motor Power Status
			BooleanBitFlags::clearFlagBit(flagSet_SystemStatus1, _BTFG_MTR_POWER_ON_);
	
			
			break;
		case TX_COMMUNICATIONS: //Mode: NORMAL_OPERATIONS

		//Interweave primary transmissions and redirection, to allow the receiving end have time to process each incoming data
	
			if(BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_FIRST_TRANSMISSION_))//check to see if this is the first transmission
			{							
				//1. Sends data to PC_USB
				if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
				{
					txData(txMsgBuffer_PC_USB, ROVERCOMM_PC_USB);
				}//end if
				//2. Sends data to COMM
				if (comm_msg_queue != CMD_TAG_NO_MSG)
				{
					txData(txMsgBuffer_COMM, ROVERCOMM_COMM);//Note: This just sends the data as created through the COMM channel. Whether it goes to CMNC or COMM, that would be determined in the createDataFromQueueFor().
				}//end if				
				//3. Sends data to NAVI
				if (navi_msg_queue != CMD_TAG_NO_MSG)
				{
					txData(txMsgBuffer_NAVI, ROVERCOMM_NAVI);
				}//end if					
				//4. Sends data to AUXI
				if (auxi_msg_queue != CMD_TAG_NO_MSG)
				{
					txData(txMsgBuffer_AUXI, ROVERCOMM_AUXI);
				}//end if				
				//5. Check to see if there are any second messages to send
				if (
					BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_REDIRECT_TO_PC_USB_)
					|| BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_REDIRECT_TO_COMM_)
					|| BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_REDIRECT_TO_NAVI_)
					|| BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_REDIRECT_TO_AUXI_)
					)		
				{
					BooleanBitFlags::clearFlagBit(flagSet_SystemStatus1, _BTFG_FIRST_TRANSMISSION_);//clear the flag
					//reset the counter before use
					transmission_delay_cnt = 0;
					queuedState = TX_COMMUNICATIONS;//override the default state (usually would be RX_COMMUNICATIONS)
				}//end if
				else//there is no second transmission, move on
				{					
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
				}//end else
			}//end if	
			else//this is not the first transmission
			{
			
				if(transmission_delay_cnt >= CONCURRENT_TRANSMISSION_DELAY) //once the desired delay has been reached, continue with the code
				{
					//Send the second set of messages
					redirectData(roverComm_Ch1);//This function will redirect data as required, and limit it to one redirection per channel (due to the limits of throughput on the receiving end)
					redirectData(roverComm_Ch2);//This function will redirect data as required, and limit it to one redirection per channel (due to the limits of throughput on the receiving end)	
					redirectData(roverComm_Ch3);//This function will redirect data as required, and limit it to one redirection per channel (due to the limits of throughput on the receiving end)	
					redirectData(roverComm_Ch4);//This function will redirect data as required, and limit it to one redirection per channel (due to the limits of throughput on the receiving end)	
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
				}//end if
				else//the desired delay has not been reached yet, so just increment the count
				{
					transmission_delay_cnt++;
				}//end else			
			}//end else
			break;				
		default: //default state
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
		case RX_COMMUNICATIONS: //Mode: HW_RESETTING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case DATA_VALIDATION: //Mode: HW_RESETTING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case DATA_FILTER: //Mode: HW_RESETTING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;	
		case READ_INPUTS: //Mode: HW_RESETTING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case PROCESS_DATA: //Mode: HW_RESETTING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;			
		case CONTROL_OUTPUTS: //Mode: HW_RESETTING

			_PRINT_HW_RESET_STATUS_(F("Resetting COMM..."));//DEBUG
			
			commHwResetter->performHwReset();	
			//NOTE: Add a delay here if needed (i.e. 1 Second)
			_PRINT_HW_RESET_STATUS_(F("Reset Complete!"));//DEBUG
			
			currentMode = SYNCHRONIZATION;//Set mode to SYNCHRONIZATION *begin*
						
			//Queue up system ready messages			
			pc_usb_msg_queue = CMD_TAG_SYSTEM_READY_STATUS;
			comm_msg_queue = CMD_TAG_SYSTEM_READY_STATUS;
			navi_msg_queue = CMD_TAG_SYSTEM_READY_STATUS;				
			auxi_msg_queue = CMD_TAG_SYSTEM_READY_STATUS;
						
			//initialize/reset shared counter before use
			timeout_counter = 0;
			
			//Note: The state machine should go to CREATE_DATA next.
		
			break;		
		case CREATE_DATA: //Mode: HW_RESETTING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case TX_COMMUNICATIONS: //Mode: HW_RESETTING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)						
			break;
		default: //default state
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
		case DATA_VALIDATION: //Mode: SYSTEM_SLEEPING
		
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
		case DATA_FILTER: //Mode: SYSTEM_SLEEPING
		
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
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_);			
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_);			
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_ALLSLEEPREQUEST_);
			//For NAVI			
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_SLEEPREQUESTACKNOWLEDGEMENT_);	
			//For AUXI
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_SLEEPREQUESTACKNOWLEDGEMENT_);	

			
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
				All SW Reset Requests from COMM/CMNC				
				generic system error message(s) from COMM/CMNC
				All Sleep (Re-)Request from COMM/CMNC (to restart the sleep process again)
					Note: Allow sleep (Re-)Request to override the sleep process if needed
					Note: No need to worry about allowing HW requests to override when in SYSTEM_SLEEPING with MAIN.
						Since when there is a HW reset, it will first start by the COMM resetting MAIN, which will take MAIN out of the SYSTEM_SLEEPING mode anyways.
						After POR, MAIN will be able to HW reset COMM when MAIN is in the SYNCHRONIZATION mode.					
					TROUBLESHOOTING TIP: Make sure it doesn't keep getting stuck in the sleep request state.
				Note: There is no Sleeping Request Acknowledgement from COMM, since it is the one that starts off the sleeping process then puts itself to sleep.							
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
				Sleeping Request Acknowledgement from NAVI	
				generic system error message(s) from NAVI
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
				System Is Sleeping Acknowledgement from AUXI
				generic system error message(s) from AUXI
				generic health errors from AUXI
				*/			
				
			}//end if	
		
			break;	
		case READ_INPUTS: //Mode: SYSTEM_SLEEPING
		
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
		case PROCESS_DATA: //Mode: SYSTEM_SLEEPING

			#ifdef _DEBUG_PRINT_TIMEOUT_COUNTER_VALUE_
				Serial.println(timeout_counter);//DEBUG
			#endif
			
			//Skip Encoders
			//Read Motor Status
				//Motor Power Status: When applicable, the Motor Power Status is captured in READ_INPUTS with a flag, the message is queued up by commandDirector of PROCESS_DATA, and then processed in CREATE_DATA with createDataFromQueueFor, then the flag is cleared.
						
			
			//Run lower priority functions here.
			//These messages and flags may be overrided with commandDirector()			
			
			
			//if run_task_on_main_now = false, one or more of the System Sleeping Acknowledgements have not been received yet
			if( ! BooleanBitFlags::flagIsSet(flagSet_SystemStatus2, _BTFG_RUN_TASKS_ON_MAIN_NOW_))
			//aka navi_acknowledgement == false or auxi_acknowledgement == false
			{
				//Note: If all acknowledgements were received, run_task_on_main_now would be true
				//Regenerate the messages as needed
				//check each arduino to see which hasn't sent a Sleeping Request Acknowledgement to MAIN yet.

				if( ! BooleanBitFlags::flagIsSet(flagSet_SystemStatus2, _BTFG_NAVI_ACKNOWLEDGEMENT_) )
				{
					navi_msg_queue = CMD_TAG_NAVI_SLEEP_REQUEST;//(tells NAVI to go to sleep)
				}//end if

				
				if( ! BooleanBitFlags::flagIsSet(flagSet_SystemStatus2, _BTFG_AUXI_ACKNOWLEDGEMENT_) )
				{
					auxi_msg_queue = CMD_TAG_AUXI_SLEEP_REQUEST;//(tells AUXI to go to sleep)
				}//end if		

				//increment counter. Note: The counter may be incremented even though sleep acknowledgement was just received, but once it's processed below, it will override any errors if all the acknowledgements were received. So no worries increment the timeout counter and checking for timeout here.

				timeout_counter++;
				
				
				//if MAIN has been stuck in SYSTEM_SLEEPING for a long time while waiting on NAVI and/or AUXI for sleep request acknowledgements
				
				#ifndef _DEBUG_DISABLE_SLEEP_ERROR_TIMEOUT //normally the timeout code would run. Can disable it for debugging purposes
					if(timeout_counter >= SLEEPING_ERROR_TIMEOUT_VALUE)
					{
						//Set mode to SYSTEM_ERROR
						currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*
						//enable_mtr_pwr = false							
						BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);//shut down motor when in error for safety
						error_origin = ROVERCOMM_MAIN;						
						pc_usb_msg_queue == CMD_TAG_SLEEP_ERROR_STATUS;
						comm_msg_queue == CMD_TAG_SLEEP_ERROR_STATUS;
						//set sleeping_error = true
						BooleanBitFlags::setFlagBit(flagSet_Error1, _BTFG_SLEEPING_ERROR_);
						//(Note: the sleeping_error flag can only be cleared with a sw reset or hw reset)					
						//initialize/reset shared counter before use
						timeout_counter = 0;
					}//end if
				#endif				
			}//end if
			else//run_task_on_main_now = true and navi_acknowledgement and auxi_acknowledgement flags are true, all the System Sleeping Acknowledgements have been received
			{
				//so clear the flags
				BooleanBitFlags::clearFlagBit(flagSet_SystemStatus2, _BTFG_NAVI_ACKNOWLEDGEMENT_);
				BooleanBitFlags::clearFlagBit(flagSet_SystemStatus2, _BTFG_AUXI_ACKNOWLEDGEMENT_);
				//Note: navi_acknowledgement and auxi_acknowledgement will be cleared before use, but do it here anyways just in case
						
				//If both acknowledgements are received, allow the Sleep Request Acknowledgement command to have the highest priority on the message queues, modes, and states (over error messages). It will override it since run_task_on_main_now = true and the else block of code here will run.
					
				comm_msg_queue = CMD_TAG_COMM_SLEEP_REQUEST;//MAIN sends COMM a COMM Sleep request, so COMM can 
				//go to sleep
				//initialize/reset shared counter for future use and to prevent being stuck in a loop
				timeout_counter = 0;	
		
				
				//Note: run_task_on_main_now will be cleared later in TX_COMMUNICATIONS when it's done being used by that state
			}//end else
	
			//Run highest priority functions here. //this will override any lower priority messages (see below)
	
			//Process PC_USB command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//All other messages are allowed from PC_USB. Use with caution.
				//No redirections in SYSTEM_SLEEPING.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH1_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh1_COMM, ROVERCOMM_PC_USB);
			}//end if			
			//Process COMM command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//Note: Either you should get no data, generic system error, All SW Reset Requests, or All Sleep (Re-)Request from COMM/CMNC. as everything else was filtered out		
				//No redirections in SYSTEM_SLEEPING.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH2_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh2_COMM, ROVERCOMM_COMM);
			}//end if				
			//Process NAVI command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//Note: Either you should get no data, generic system error, or Sleeping Request Acknowledgement from NAVI. as everything else was filtered out
				//No redirections in SYSTEM_SLEEPING.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH3_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh3_COMM, ROVERCOMM_NAVI);
			}//end if				
			//Process AUXI command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//Note: Either you should get no data, generic system error, generic health error, or Sleeping Request Acknowledgement from AUXI. as everything else was filtered out		
				//No redirections in SYSTEM_SLEEPING.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH4_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh4_COMM, ROVERCOMM_AUXI);
			}//end if

	

		
			break;		
		case CONTROL_OUTPUTS: //Mode: SYSTEM_SLEEPING

				//enable_mtr_pwr should be false. It is set in All Sleep Request of commandDirector.

				if( ! BooleanBitFlags::flagIsSet(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_))
				{	
					//Turn motor MOSFET off
					mtrPowerCtrlr->setMotorPower(MTR_DISABLED);
				}//end if
				else//there is an error in the code logic
				{
					_SERIAL_DEBUG_CHANNEL_.println(F("MtrPwrCtrlErr"));//Motor Power Controller Error
				}//end else				
				
				//Note: Do not go to sleep yet, have to send out COMM_SLEEP_REQUEST to COMM.
				
			break;		
		case CREATE_DATA: //Mode: SYSTEM_SLEEPING

			//Creates data for PC_USB
			if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_PC_USB);
			}//end if
			//Creates data for COMM
			if (comm_msg_queue != CMD_TAG_NO_MSG)
			{
				//Note: The data should be COMM_SLEEP_REQUEST.
				//Create COMM sleep request after acknowledgements are received from both AUXI and NAVI (it should be cleared out to CMD_TAG_NO_MSG after the request has been sent, in TX_COMMUNICATIONS, so it doesn't get stuck in a loop)

				if(comm_cmnc_destination_selection == ROVERCOMM_COMM)//data is for COMM
				{
					createDataFromQueueFor(ROVERCOMM_COMM);
				}//end if
				else if(comm_cmnc_destination_selection == ROVERCOMM_CMNC) //data is for CMNC
				{
					createDataFromQueueFor(ROVERCOMM_CMNC);
				}//end else if
				else//invalid state, error out
				{
					_SERIAL_DEBUG_CHANNEL_.println(F("ErrUnkDest"));//error, unknown destination
				}//end else
				
				//skip auto data

			}//end if
			//Creates data for NAVI
			if (navi_msg_queue != CMD_TAG_NO_MSG)
			{
				//Note: The data should be NAVI_SLEEP_REQUEST. (it should be cleared out to CMD_TAG_NO_MSG after the request has been sent, in TX_COMMUNICATIONS, so it doesn't get stuck in a loop)
				createDataFromQueueFor(ROVERCOMM_NAVI);
				
				//skip auto data	
				
			}//end if
			//Creates data for AUXI
			if (auxi_msg_queue != CMD_TAG_NO_MSG)
			{
				//Note: The data should be AUXI_SLEEP_REQUEST. (it should be cleared out to CMD_TAG_NO_MSG after the request has been sent, in TX_COMMUNICATIONS, so it doesn't get stuck in a loop)
				createDataFromQueueFor(ROVERCOMM_AUXI);
				
				//skip auto data					
				
			}//end if			
			
			//Clear Motor Power Status
			BooleanBitFlags::clearFlagBit(flagSet_SystemStatus1, _BTFG_MTR_POWER_ON_);		
		
			break;
		case TX_COMMUNICATIONS: //Mode: SYSTEM_SLEEPING

			//Note: No redirection during SYSTEM_SLEEPING.
			
			//Sends data to PC_USB
			if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
			{
				txData(txMsgBuffer_PC_USB, ROVERCOMM_PC_USB);
			}//end if
			//Sends data to COMM
			if (comm_msg_queue != CMD_TAG_NO_MSG)
			{
				txData(txMsgBuffer_COMM, ROVERCOMM_COMM);//Note: This just sends the data as created through the COMM channel. Whether it goes to CMNC or COMM, that would be determined in the createDataFromQueueFor().
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



			if( BooleanBitFlags::flagIsSet(flagSet_SystemStatus2, _BTFG_RUN_TASKS_ON_MAIN_NOW_) )//run_task_on_main_now == true
			{
				//run_task_on_main_now = false
				BooleanBitFlags::clearFlagBit(flagSet_SystemStatus2, _BTFG_RUN_TASKS_ON_MAIN_NOW_);//clear the flag
				
				//MAIN Sleeps itself once the request from MAIN to COMM for COMM to sleep itself has been sent
				//TROUBLESHOOT TIP: If this COMM sleep request is missed by COMM, then COMM will need to start the sleep process again since MAIN already slept. If this happens COMM will go into error mode after timing out and wait for a HW reset (as MAIN and possibly NAVI and AUXI are asleep and won't respond to a SW reset request)
					//Improvement Tip: I could add a wakeup step for SW resets just in case, any of the Arduinos are asleep, before going the SW reset, but this will get complicated/messy. Good enough for now.
				
				//SETUP FOR WAKEUP
				
				//setup this mode ahead of time before going to sleep
				currentMode = SYSTEM_WAKING;//Set mode to SYSTEM_WAKING *begin*			
				
				queuedState = CONTROL_OUTPUTS;//Go to CONTROL_OUTPUTS in order to wake NAVI and AUXI from sleep and to restore the motor prev state. Overriding the default next state, which was RX_COMMUNICATIONS.

				//Restore previous motor state: enable_mtr_pwr = motor_power_prev_state
				if( BooleanBitFlags::flagIsSet(flagSet_SystemControls1, _BTFG_MTR_PREV_STATE_) )
				{
					BooleanBitFlags::setFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);
				}//end if
				else
				{
					BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);
				}//end else
				

				//clear the flag for future reuse
				//motor_power_prev_state = false					
				BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_MTR_PREV_STATE_);
				
				//Run other pre-sleep tasks. (i.e. end software serial, as needed)
					//No SW Serials used for MAIN
					//Do nothing for now. Place holder.
	
					_PRINT_SLEEPING_AND_WAKEUP_STATUS_(F("MAIN_Sleep"));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
				
	
				delay(100);//add some delay to allow the serial print to finish before going to sleep
	
				//END OF SETUP FOR WAKEUP
				
				//GOING TO SLEEP
				//Put MAIN to sleep
				sleeperMAIN->goToSleep();//will put MAIN to sleep (COMM will wake up MAIN externally)
				//Don't switch states yet. Go to sleep in the current TX_COMMUNICATIONS state.

				//WAKING UP
				//COMM will wake up MAIN from the sleep.				
				sleeperMAIN->hasAwoken();//This updates the status and detaches the interrupt for MAIN once MAIN is awaken externally by COMM.
				
				//Note: Make sure to begin (again) any Software Serial here
				//No SW Serials used for MAIN


				delay(100);// let everybody get up and running for a sec

				//Run wake up tasks. (i.e. begin SW serial as needed, etc.)
					//No SW Serials used for MAIN
					//Do nothing for now. Place holder.
				
				
				_PRINT_SLEEPING_AND_WAKEUP_STATUS_(F("MAIN_Wake"));//output to PC for debug
									
									
				//While in the SYSTEM_WAKING mode, after going to RUN_HOUSEKEEPING_TASKS, it will go to the next state, which is set to CONTROL_OUTPUTS
								
				
			}//end if
			/*
			else the system is not ready to sleep yet as all the acknowledgements haven't been received (i.e. run_task_on_main_now == false)
				
				Just keep the default.
				Mode: SYSTEM_SLEEPING
				The next state is RX_COMMUNICATIONS
				
			*/
			
			break;				
		default: //default state
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
		case RX_COMMUNICATIONS: //Mode: SYSTEM_WAKING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case DATA_VALIDATION: //Mode: SYSTEM_WAKING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case DATA_FILTER: //Mode: SYSTEM_WAKING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;	
		case READ_INPUTS: //Mode: SYSTEM_WAKING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case PROCESS_DATA: //Mode: SYSTEM_WAKING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;			
		case CONTROL_OUTPUTS: //Mode: SYSTEM_WAKING

			//Wake up NAVI (toggles the wakeup pin to low, then back to high)
					
			if ( ! sleeperNAVI->isAwake() )
			{
				//Wake Up
				sleeperNAVI->wakeUp();//Toggles the wakeup pin to low (then back to high). The low level on the interrupt pin wakes up NAVI.
				//Post Wake Up tasks
				_PRINT_SLEEPING_AND_WAKEUP_STATUS_(F("NAVI_WAKE"));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
			}//end if
			else
			{
				_PRINT_SLEEPING_AND_WAKEUP_STATUS_(F("NAVI_WOKE"));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
			}//end else
	
	
	
			//Wake up AUXI (toggles the wakeup pin to low, then back to high)
			if ( ! sleeperAUXI->isAwake() )
			{
				//Wake Up
				sleeperAUXI->wakeUp();//Toggles the wakeup pin to low (then back to high). The low level on the interrupt pin wakes up AUXI.
				//Post Wake Up tasks
				_PRINT_SLEEPING_AND_WAKEUP_STATUS_(F("AUXI_WAKE"));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
			}//end if
			else
			{
				_PRINT_SLEEPING_AND_WAKEUP_STATUS_(F("AUXI_WOKE"));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
			}//end else

			
			
			//if motor enable is on
			if(BooleanBitFlags::flagIsSet(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_))
			{
				//Turn motor MOSFET on
				mtrPowerCtrlr->setMotorPower(MTR_ENABLED);
			}//end if
			else//else motor enable is off
			{
				//Turn motor MOSFET off
				mtrPowerCtrlr->setMotorPower(MTR_DISABLED);
			}//end else
						
						
						
			currentMode = SYNCHRONIZATION;//Set mode to SYNCHRONIZATION *begin*
			
			//Queue up system ready messages
			pc_usb_msg_queue = CMD_TAG_SYSTEM_READY_STATUS;
			comm_msg_queue = CMD_TAG_SYSTEM_READY_STATUS;
			navi_msg_queue = CMD_TAG_SYSTEM_READY_STATUS;				
			auxi_msg_queue = CMD_TAG_SYSTEM_READY_STATUS;
		
			//initialize/reset shared counter before use
			timeout_counter = 0;						
			
			//Note: The state machine should go to CREATE_DATA next.
			
			break;		
		case CREATE_DATA: //Mode: SYSTEM_WAKING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case TX_COMMUNICATIONS: //Mode: SYSTEM_WAKING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)				
			break;			
		default: //default state
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
		case DATA_VALIDATION: //Mode: SW_RESETTING

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
		case DATA_FILTER: //Mode: SW_RESETTING
		
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
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_);	
			//For NAVI			
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_SWRESETACKNOWLEDGMENT_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_);	
			//For AUXI
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_SWRESETACKNOWLEDGMENT_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_);	

			
			//Transmit data and/or execute command
						
			//For data from PC_USB, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, MAIN
			if (ch1Status == DATA_STATUS_VALID)
			{
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//No redirections in SW_RESETTING.
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
				//No redirections in SW_RESETTING.
				//Note: this is a local .ino function

				dataDirector(roverDataCh2_COMM, DATA_REDIRECT_DISABLED, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH2_);//DataDirection will set the "data was for MAIN flag" to true if it was for this Arduino
				
				/*
				Set filter to throw away all COMM data except:
				generic system error message(s) from COMM/CMNC
				All SW Reset (Re-)Request from COMM/CMNC (to restart the SW reset process again)
					Note: Allow All SW Reset (Re-)Request to override the sw reset process if needed
					Note: No need to worry about allowing HW requests to override when in SW_RESETTING with MAIN.
							Since when there is a HW reset, it will first start by the COMM resetting MAIN, which will take MAIN out of the SW_RESETTING mode anyways.
							After POR, MAIN will be able to HW reset COMM when MAIN is in the SYNCHRONIZATION mode.					
					TROUBLESHOOTING TIP: Make sure it doesn't keep getting stuck in the re-resetting state.
				*/				

			}//end if
			
			//For data from NAVI, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, MAIN
			if (ch3Status == DATA_STATUS_VALID)
			{
			
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//No redirections in SW_RESETTING.
				//Note: this is a local .ino function

				dataDirector(roverDataCh3_COMM, DATA_REDIRECT_DISABLED, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH3_);//DataDirection will set the "data was for MAIN flag" to true if it was for this Arduino
				
				/*
				Set filter to throw away all NAVI data except:
				SW Reset Acknowledgement from NAVI
				generic system error message(s) from NAVI
				*/		
				
			}//end if
			
			
			//For data from AUXI, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, MAIN
			if (ch4Status == DATA_STATUS_VALID)
			{
			
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//No redirections in SW_RESETTING.
				//Note: this is a local .ino function

				dataDirector(roverDataCh4_COMM, DATA_REDIRECT_DISABLED, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH4_);//DataDirection will set the "data was for MAIN flag" to true if it was for this Arduino
				
				/*
				Set filter to throw away all AUXI data except:
				SW Reset Acknowledgement from AUXI						
				generic system error message(s) from AUXI
				generic health errors from AUXI
				*/			
				
			}//end if			
		
		
			break;	
		case READ_INPUTS: //Mode: SW_RESETTING
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
		case PROCESS_DATA: //Mode: SW_RESETTING

		
		
			#ifdef _DEBUG_PRINT_TIMEOUT_COUNTER_VALUE_
				Serial.println(timeout_counter);//DEBUG
			#endif
			
			//Skip Encoders
			//Read Motor Status
				//Motor Power Status: When applicable, the Motor Power Status is captured in READ_INPUTS with a flag, the message is queued up by commandDirector of PROCESS_DATA, and then processed in CREATE_DATA with createDataFromQueueFor, then the flag is cleared.
						
			
			//Run lower priority functions here.
			//These messages and flags may be overrided with commandDirector()			
	
			
			//Process PC_USB command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//All other messages are allowed from PC_USB. Use with caution.
				//No redirections in SW_RESETTING.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH1_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh1_COMM, ROVERCOMM_PC_USB);
			}//end if			
			//Process COMM command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//Note: Either you should get no data, generic system error, or All SW Reset (Re-)Request from COMM/CMNC. as everything else was filtered out.	
				//No redirections in SW_RESETTING.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH2_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh2_COMM, ROVERCOMM_COMM);
			}//end if				
			//Process NAVI command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//Note: Either you should get no data, generic system error, or SW Reset Acknowledgement from NAVI. as everything else was filtered out.
				//No redirections in SW_RESETTING.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH3_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh3_COMM, ROVERCOMM_NAVI);
			}//end if				
			//Process AUXI command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//Note: Either you should get no data, generic system error, generic health error, or SW Reset Acknowledgement from AUXI. as everything else was filtered out.
				//No redirections in SW_RESETTING.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH4_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh4_COMM, ROVERCOMM_AUXI);
			}//end if

							
			//Run highest priority functions here. //this will override any lower priority messages

			//For SW_RESETTING, it uses a dual timeout design
			//Note: SW_RESET_ERROR_TIMEOUT_VALUE should be greater than SW_RESET_RESEND_TIMEOUT_VALUE
			

			//if run_task_on_main_now = false, one or more of the SW Reset Acknowledgements have not been received yet
			if( ! BooleanBitFlags::flagIsSet(flagSet_SystemStatus2, _BTFG_RUN_TASKS_ON_MAIN_NOW_))
			//aka navi_acknowledgement == false or auxi_acknowledgement == false
			{				
				
				
				//Note: If all acknowledgements were received, run_task_on_main_now would be true
					//increment the loop count while waiting wait for AUXI or NAVI SW Reset Acknowledgement to MAIN
				
							
				//increment counter. Note: The counter may be incremented even though SW Reset Acknowledgement was just received, but once it's processed below, it will override any errors if all the acknowledgements were received. So no worries increment the timeout counter and checking for timeout here.
				
				timeout_counter++;
				
												
				#ifndef _DEBUG_DISABLE_SW_RESET_ERROR_AND_RESEND_TIMEOUT //normally the timeout code would run. Can disable it for debugging purposes.
					//if MAIN has been stuck in SW_RESETTING for a long time while waiting on NAVI and/or AUXI for SW Request acknowledgements
					//Note since this uses a dual timeout design, it uses one flag to disable both of the timeouts
					if(timeout_counter >= SW_RESET_ERROR_TIMEOUT_VALUE)
					{
						//Set mode to SYSTEM_ERROR
						currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*
						//enable_mtr_pwr = false
						BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);//shut down motor when in error for safety		
						error_origin = ROVERCOMM_MAIN;						
						//Create the error message for the message queues for the first time
						pc_usb_msg_queue = CMD_TAG_SW_RESET_ERROR_STATUS;//send error out through the PC_USB for debugging
						comm_msg_queue = CMD_TAG_SW_RESET_ERROR_STATUS;//To let the Arduino know MAIN is in error and the motor will be shut off, etc.
						navi_msg_queue = CMD_TAG_SW_RESET_ERROR_STATUS;//To let the Arduino know MAIN is in error and the motor will be shut off, etc.
						auxi_msg_queue = CMD_TAG_SW_RESET_ERROR_STATUS;//To let the Arduino know MAIN is in error and the motor will be shut off, etc.
						//set sw_reset_error = true
						BooleanBitFlags::setFlagBit(flagSet_Error1, _BTFG_SW_RESET_ERROR_);						
						//(Note: the sw_reset_error flag can only be cleared with a hw reset)
						//initialize/reset shared counter before use
						timeout_counter = 0;					
					}//end if
					//else if it just waited a little bit, it should try resending the SW reset request to AUXI or NAVI from MAIN
					else if(timeout_counter >= SW_RESET_RESEND_TIMEOUT_VALUE)
					{
						//Regenerate the messages as needed
							
						//Note: It should send the request periodically and not continuously so the system has time to process the request and it doesn't get stuck in a loop. it will get cleared out in TX_COMMUNICATIONS after the messages are sent.
							
						//check each arduino to see which hasn't sent a SW Reset Acknowledgement to MAIN yet.
						
						
						if( ! BooleanBitFlags::flagIsSet(flagSet_SystemStatus2, _BTFG_NAVI_ACKNOWLEDGEMENT_) )
						{
							navi_msg_queue = CMD_TAG_NAVI_SW_RESET_REQUEST;//(tells NAVI to do a SW reset)
						}//end if

						
						if( ! BooleanBitFlags::flagIsSet(flagSet_SystemStatus2, _BTFG_AUXI_ACKNOWLEDGEMENT_) )
						{
							auxi_msg_queue = CMD_TAG_AUXI_SW_RESET_REQUEST;//(tells AUXI to do a SW reset)
						}//end if
												
						//Don't reset timeout_counter, keep counting and see if it will reach the SW_RESET_ERROR_TIMEOUT_VALUE
						
							
					}//end else if
				#endif				
			}//end if			
			else//run_task_on_main_now = true aka navi_acknowledgement and auxi_acknowledgement flags are true, all the SW Reset Acknowledgements have been received
			{
				//so clear the flags
				BooleanBitFlags::clearFlagBit(flagSet_SystemStatus2, _BTFG_NAVI_ACKNOWLEDGEMENT_);
				BooleanBitFlags::clearFlagBit(flagSet_SystemStatus2, _BTFG_AUXI_ACKNOWLEDGEMENT_);
						
				//Note: navi_acknowledgement and auxi_acknowledgement will be cleared before use, but do it here anyways just in case
				
				
				//If both acknowledgements are received, allow the SW Reset Acknowledgement command to have the highest priority on the message queues, modes, and states (over error messages). It will override it since run_task_on_main_now = true and the else block of code here will run.
				
				comm_msg_queue = CMD_TAG_COMM_SW_RESET_REQUEST;//MAIN sends COMM a COMM SW request, so COMM can do a SW reset
				
				//initialize/reset shared counter for future use and to prevent being stuck in a loop
				timeout_counter = 0;			
				
				//Note: run_task_on_main_now will be cleared later in TX_COMMUNICATIONS when it's done being used by that state
			}//end else
	
			break;		
		case CONTROL_OUTPUTS: //Mode: SW_RESETTING


			//enable_mtr_pwr should be false. It is set in All SW Reset Request of commandDirector.

			if( ! BooleanBitFlags::flagIsSet(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_))
			{	
				//Turn motor MOSFET off
				mtrPowerCtrlr->setMotorPower(MTR_DISABLED);
			}//end if
			else//there is an error in the code logic
			{
				_SERIAL_DEBUG_CHANNEL_.println(F("MtrPwrCtrlErr"));//Motor Power Controller Error
			}//end else				

			break;		
		case CREATE_DATA: //Mode: SW_RESETTING
			//Creates data for PC_USB
			if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_PC_USB);
				
				//skip auto data	
				
				
			}//end if
			//Creates data for COMM
			if (comm_msg_queue != CMD_TAG_NO_MSG)
			{
			
				if(comm_cmnc_destination_selection == ROVERCOMM_COMM)//data is for COMM
				{
					createDataFromQueueFor(ROVERCOMM_COMM);
				}//end if
				else if(comm_cmnc_destination_selection == ROVERCOMM_CMNC) //data is for CMNC
				{
					createDataFromQueueFor(ROVERCOMM_CMNC);
				}//end else if
				else//invalid state, error out
				{
					_SERIAL_DEBUG_CHANNEL_.println(F("ErrUnkDest"));//error, unknown destination
				}//end else
				
				//skip auto data
								
			}//end if
			//Creates data for NAVI
			if (navi_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_NAVI);
				
				//skip auto data					
				
			}//end if
			//Creates data for AUXI
			if (auxi_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_AUXI);
				
				//skip auto data	
				
			}//end if			
			
			//Clear Motor Power Status
			BooleanBitFlags::clearFlagBit(flagSet_SystemStatus1, _BTFG_MTR_POWER_ON_);
			
			break;
		case TX_COMMUNICATIONS: //Mode: SW_RESETTING


			//Note: No redirection during SW_RESETTING.
			
			//Sends data to PC_USB
			if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
			{
				txData(txMsgBuffer_PC_USB, ROVERCOMM_PC_USB);
			}//end if
			//Sends data to COMM
			if (comm_msg_queue != CMD_TAG_NO_MSG)
			{
				txData(txMsgBuffer_COMM, ROVERCOMM_COMM);//Note: This just sends the data as created through the COMM channel. Whether it goes to CMNC or COMM, that would be determined in the createDataFromQueueFor().
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



			if( BooleanBitFlags::flagIsSet(flagSet_SystemStatus2, _BTFG_RUN_TASKS_ON_MAIN_NOW_) )//run_task_on_main_now == true
			{
				//run_task_on_main_now = false
				BooleanBitFlags::clearFlagBit(flagSet_SystemStatus2, _BTFG_RUN_TASKS_ON_MAIN_NOW_);//clear the flag
				
				//MAIN SW resets itself once the request from MAIN to COMM for COMM to sw reset itself has been sent
				//TROUBLESHOOT TIP: If this COMM sw reset request is missed by COMM, then COMM will need to start the All SW Reset Request process again since MAIN already SW resetted and should be waiting in the SYNCHRONIZATION mode
				currentMode = INITIALIZATION;//Set mode to INITIALIZATION *begin*		
				//By Default: The next state is RX_COMMUNICATIONS
				
			}//end if
			/*
			else the system is not ready to sw reset yet as all the acknowledgements haven't been received (i.e. run_task_on_main_now == false)
				
				Just keep the default.
				Mode: SW_RESETTING
				The next state is RX_COMMUNICATIONS
				
			*/		
		
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
		case RUN_HOUSEKEEPING_TASKS: //Mode: SYSTEM_ERROR
			runBackgroundTasks();
			break;
		case RX_COMMUNICATIONS: //Mode: SYSTEM_ERROR

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
		case DATA_VALIDATION: //Mode: SYSTEM_ERROR

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
		case DATA_FILTER: //Mode: SYSTEM_ERROR

		
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
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_COMM, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_MOTORPOWERSTATUS_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_MIDRIGHTENCODERSTATUS_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet2_COMM, _BTFG_COMMAND_ENABLE_OPTION_MIDLEFTENCODERSTATUS_);
			//For NAVI			
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_NAVI, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_MOTORPOWERSTATUS_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_MIDRIGHTENCODERSTATUS_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet2_NAVI, _BTFG_COMMAND_ENABLE_OPTION_MIDLEFTENCODERSTATUS_);	
			//For AUXI
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_AUXI, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_MOTORPOWERSTATUS_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_MIDRIGHTENCODERSTATUS_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet2_AUXI, _BTFG_COMMAND_ENABLE_OPTION_MIDLEFTENCODERSTATUS_);	

			
			//Transmit data and/or execute command
						
			//For data from PC_USB, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, MAIN
			if (ch1Status == DATA_STATUS_VALID)
			{
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//Allow redirections for PC_USB
				//Note: this is a local .ino function

				dataDirector(roverDataCh1_COMM, DATA_REDIRECT_ENABLED, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH1_);//DataDirection will set the "data was for MAIN flag" to true if it was for this Arduino

				/*
				Allow all data from PC_USB.
				*/

			}//end if

			//For data from COMM, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, MAIN
			if (ch2Status == DATA_STATUS_VALID)
			{
			
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//Allow redirections for COMM
				//Note: this is a local .ino function

				dataDirector(roverDataCh2_COMM, DATA_REDIRECT_ENABLED, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH2_);//DataDirection will set the "data was for MAIN flag" to true if it was for this Arduino
					

				/*
				Set filter to throw away all COMM data except:
					generic system error message(s) from COMM/CMNC
					all sw reset request message(s) from COMM
					mid left encoder requests (used for debugging)
					mid right encoder requests (used for debugging)
					motor power status requests (used for debugging)
					Note: Allow all COMM/CMNC data to be redirected so AUXI/NAVI can send requested data back. Each Arduino will filter out what it will allow in error mode.						
					Note: There is no need for HW requests here, since when there is a HW reset, it will first start by the COMM resetting MAIN, which will take MAIN out of the SYSTEM_ERROR mode anyways.
						After POR, MAIN will be able to HW reset COMM when MAIN is in the SYNCHRONIZATION mode.		
				*/				

				
			}//end if
			
			//For data from NAVI, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, MAIN
			if (ch3Status == DATA_STATUS_VALID)
			{
			
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//Allow redirections for NAVI
				//Note: this is a local .ino function

				dataDirector(roverDataCh3_COMM, DATA_REDIRECT_ENABLED, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH3_);//DataDirection will set the "data was for MAIN flag" to true if it was for this Arduino
				
				/*
				Set filter to throw away all NAVI data except:
				generic system error message(s) from NAVI
				mid left encoder requests (used for debugging)
				mid right encoder requests (used for debugging)
				motor power status requests (used for debugging)
				//NOTE: Allow system data to be passed/redirected from NAVI to MAIN, AUXI or COMM or CMNC
				//Note: All SW and HW requests should be initiated originally from COMM (and not NAVI or AUXI)
				*/	

				
			}//end if
			
			
			//For data from AUXI, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, MAIN
			if (ch4Status == DATA_STATUS_VALID)
			{
			
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//Allow redirections for AUXI
				//Note: this is a local .ino function

				dataDirector(roverDataCh4_COMM, DATA_REDIRECT_ENABLED, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH4_);//DataDirection will set the "data was for MAIN flag" to true if it was for this Arduino
				
				/*
				Set filter to throw away all AUXI data except:
				mid left encoder requests (used for debugging)
				mid right encoder requests (used for debugging)
				motor power status requests (used for debugging)
				generic system error message(s) from AUXI
				generic health errors from AUXI
				//NOTE: Allow system data to be passed/redirected from AUXI to MAIN, NAVI or COMM or CMNC
				//Note: All SW and HW requests should be initiated originally from COMM (and not NAVI or AUXI)
				*/		

				
			}//end if		
		
		
		
			break;	
		case READ_INPUTS: //Mode: SYSTEM_ERROR

			//Read Encoder - MidLeft
			wheelEncoder_MidLeft_Direction = wheelEncoder_MidLeft->getDirection();
			wheelEncoder_MidLeft_Speed = wheelEncoder_MidLeft->getSpeed();
			wheelEncoder_MidLeft_Footage = wheelEncoder_MidLeft->getFootage();
			//Read Encoder - MidRight
			wheelEncoder_MidRight_Direction = wheelEncoder_MidRight->getDirection();
			wheelEncoder_MidRight_Speed = wheelEncoder_MidRight->getSpeed();
			wheelEncoder_MidRight_Footage = wheelEncoder_MidRight->getFootage();		
		
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
		case PROCESS_DATA: //Mode: SYSTEM_ERROR
	
			#ifdef _DEBUG_PRINT_TIMEOUT_COUNTER_VALUE_
				Serial.println(timeout_counter);//DEBUG
			#endif
			
			//Process Encoders
				//Encoder Statuses: When applicable, the Encoder Statuses are captured in READ_INPUTS and stores in a set of variables, the message is queued up by commandDirector of PROCESS_DATA, and then processed in CREATE_DATA with createDataFromQueueFor. The variables will keep their values until overwritten in another visit to the READ_INPUTS state.
		
			//Read Motor Status
				//Motor Power Status: When applicable, the Motor Power Status is captured in READ_INPUTS with a flag, the message is queued up by commandDirector of PROCESS_DATA, and then processed in CREATE_DATA with createDataFromQueueFor, then the flag is cleared.
						
			
			//Run lower priority functions here.
			//These messages and flags may be overrided with commandDirector()			
			
		
			
			//Process PC_USB command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//All other messages are allowed from PC_USB. Use with caution.
				
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH1_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh1_COMM, ROVERCOMM_PC_USB);
			}//end if			
			//Process COMM command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//Note: Either you should get All SW requests, motor power status, mid left or mid right encoder status requests, or generic system errors. as everything else was filtered out
				
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH2_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh2_COMM, ROVERCOMM_COMM);
			}//end if				
			//Process NAVI command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//Note: Either you should get generic system errors, motor power status, mid left or mid right encoder status requests, or redirections from NAVI. as everything else was filtered out
				
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH3_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh3_COMM, ROVERCOMM_NAVI);
			}//end if				
			//Process AUXI command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//Note: Either you should get generic system errors, motor power status, mid left or mid right encoder status requests, redirections and generic health errors from AUXI. as everything else was filtered out
				
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_MAIN_CH4_))//If there was data from MAIN (Ch2), and it was for COMM
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh4_COMM, ROVERCOMM_AUXI);
			}//end if
							
			//Run highest priority functions here (after command director). //this will override any lower priority messages (i.e. system go). This will overwrite anything else. (i.e. system ready)
				
				
			
			//Recreate/regenerate any error messages (but allow them to be overwritten by higher priority messages)
			//Improvement Tip: Maybe can send NAVI and AUXI the error messages as well so they can react to it. But for now good enough.
			if( BooleanBitFlags::flagIsSet(flagSet_Error1, _BTFG_SYNC_ERROR_) )//if sync_error == true
			{
				//(Note: the sync_error flag can only be cleared with a sw reset or hw reset)					
				
				pc_usb_msg_queue = CMD_TAG_SYNC_ERROR_STATUS; //send error out through the PC_USB for debugging

				if( error_origin != ROVERCOMM_COMM)//Make sure don't send it back to itself to avoid an infinite loop
				{
					comm_msg_queue = CMD_TAG_SYNC_ERROR_STATUS;//send error to comm which will send a copy to cmnc as well
				}//end if			
				if( error_origin != ROVERCOMM_AUXI)//Make sure don't send it back to itself to avoid an infinite loop
				{
					auxi_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//also send a copy to AUXI so every Arduino will know of the error
				}//end if							
				if( error_origin != ROVERCOMM_NAVI)//Make sure don't send it back to itself to avoid an infinite loop
				{
					navi_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//also send a copy to NAVI so every Arduino will know of the error
				}//end if
				
				//(Note: the sync_error flag can only be cleared with a sw reset or hw reset)				
				
			}//end if				
			else if(BooleanBitFlags::flagIsSet(flagSet_Error1, _BTFG_SW_RESET_ERROR_))//if sw_reset_error == true
			{						
				pc_usb_msg_queue = CMD_TAG_SW_RESET_ERROR_STATUS; //send error out through the PC_USB for debugging
				
				if( error_origin != ROVERCOMM_COMM)//Make sure don't send it back to itself to avoid an infinite loop
				{
					comm_msg_queue = CMD_TAG_SW_RESET_ERROR_STATUS;//send error to comm which will send a copy to cmnc as well
				}																		
				if( error_origin != ROVERCOMM_NAVI)//Make sure don't send it back to itself to avoid an infinite loop
				{
					navi_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//also send a copy to NAVI so every Arduino will know of the error
				}//end if	
				if( error_origin != ROVERCOMM_AUXI)//Make sure don't send it back to itself to avoid an infinite loop
				{
					auxi_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//also send a copy to AUXI so every Arduino will know of the error
				}//end if							
				
				//(Note: the sw_reset_error flag can only be cleared with a hw reset)
				//Troubleshooting tip, if it's a sw_reset_error, it will need a HW reset. But SYSTEM_ERROR will allow for both sw and hw resets because it's designed to handle any errors in general. So the user will have to know to send a HW reset in order to clear a SW reset error.
				
			}//end else if

			else if( BooleanBitFlags::flagIsSet(flagSet_Error1, _BTFG_SLEEPING_ERROR_) )//if sleeping_error == true 
			{
			
				pc_usb_msg_queue = CMD_TAG_SLEEP_ERROR_STATUS; //send error out through the PC_USB for debugging

				if( error_origin != ROVERCOMM_COMM)//Make sure don't send it back to itself to avoid an infinite loop
				{
					comm_msg_queue = CMD_TAG_SLEEP_ERROR_STATUS;//send error to comm which will send a copy to cmnc as well
				}						
				if( error_origin != ROVERCOMM_NAVI)//Make sure don't send it back to itself to avoid an infinite loop
				{
					navi_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//also send a copy to NAVI so every Arduino will know of the error
				}//end if	
				if( error_origin != ROVERCOMM_AUXI)//Make sure don't send it back to itself to avoid an infinite loop
				{
					auxi_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//also send a copy to AUXI so every Arduino will know of the error
				}//end if									
				
				//(Note: the sleeping_error flag can only be cleared with a sw reset or hw reset)				
				
			}//end else if
			else if( BooleanBitFlags::flagIsSet(flagSet_Error1, _BTFG_INVALID_STATE_OR_MODE_ERROR_) )//if invalid_state_or_mode_error == true
			{
			
				pc_usb_msg_queue = CMD_TAG_INVALID_STATE_OR_MODE_ERROR_STATUS;
				
				if( error_origin != ROVERCOMM_COMM)//Make sure don't send it back to itself to avoid an infinite loop
				{
					comm_msg_queue = CMD_TAG_INVALID_STATE_OR_MODE_ERROR_STATUS;//with CMNC as the destination						
				}						
				if( error_origin != ROVERCOMM_NAVI)//Make sure don't send it back to itself to avoid an infinite loop
				{
					navi_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//also send a copy to NAVI so every Arduino will know of the error
				}//end if	
				if( error_origin != ROVERCOMM_AUXI)//Make sure don't send it back to itself to avoid an infinite loop
				{
					auxi_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//also send a copy to AUXI so every Arduino will know of the error
				}//end if			
				
				//(Note: the invalid_state_or_mode_error flag can only be cleared with a sw reset or hw reset)
				
			}//end else if
			else if( BooleanBitFlags::flagIsSet(flagSet_Error1, _BTFG_GENERIC_HEALTH_ERROR_) )//if generic_health_error == true
			{
				pc_usb_msg_queue = CMD_TAG_GENERIC_HEALTH_STATUS_ERROR; //send error out through the PC_USB for debugging

				if( error_origin != ROVERCOMM_COMM)//Make sure don't send it back to itself to avoid an infinite loop
				{
					comm_msg_queue = CMD_TAG_GENERIC_HEALTH_STATUS_ERROR;//send error to comm which will send a copy to cmnc as well
				}						
				if( error_origin != ROVERCOMM_NAVI)//Make sure don't send it back to itself to avoid an infinite loop
				{
					navi_msg_queue = CMD_TAG_GENERIC_HEALTH_STATUS_ERROR;//also send a copy to NAVI so every Arduino will know of the error
				}//end if	
				if( error_origin != ROVERCOMM_AUXI)//Make sure don't send it back to itself to avoid an infinite loop
				{
					auxi_msg_queue = CMD_TAG_GENERIC_HEALTH_STATUS_ERROR;//also send a copy to AUXI so every Arduino will know of the error
				}//end if		
				
				//(Note: the generic_health_error flag can only be cleared with a sw reset or hw reset)				
								
			}//end else if				
			else if( BooleanBitFlags::flagIsSet(flagSet_Error1, _BTFG_GENERIC_SYSTEM_ERROR_) )//if generic_system_error == true
			{
				pc_usb_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS; //send error out through the PC_USB for debugging
				
				if( error_origin != ROVERCOMM_COMM)//Make sure don't send it back to itself to avoid an infinite loop
				{
					comm_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//send error to comm which will send a copy to cmnc as well
				}						
				if( error_origin != ROVERCOMM_NAVI)//Make sure don't send it back to itself to avoid an infinite loop
				{
					navi_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//also send a copy to NAVI so every Arduino will know of the error
				}//end if	
				if( error_origin != ROVERCOMM_AUXI)//Make sure don't send it back to itself to avoid an infinite loop
				{
					auxi_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//also send a copy to AUXI so every Arduino will know of the error
				}//end if					

				//(Note: the generic_system_error flag can only be cleared with a sw reset or hw reset)
				
			}//end else if	
			else//default: set to generic_system_error
			{
				//Set generic_system_error = true
				BooleanBitFlags::setFlagBit(flagSet_Error1, _BTFG_GENERIC_SYSTEM_ERROR_);
				//(Note: the generic_system_error flag can only be cleared with a sw reset or hw reset)
				
				pc_usb_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS; //send error out through the PC_USB for debugging
				
				if( error_origin != ROVERCOMM_COMM)//Make sure don't send it back to itself to avoid an infinite loop
				{
					comm_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//send error to comm which will send a copy to cmnc as well
				}							
				if( error_origin != ROVERCOMM_NAVI)//Make sure don't send it back to itself to avoid an infinite loop
				{
					navi_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//also send a copy to NAVI so every Arduino will know of the error
				}//end if	
				if( error_origin != ROVERCOMM_AUXI)//Make sure don't send it back to itself to avoid an infinite loop
				{
					auxi_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//also send a copy to AUXI so every Arduino will know of the error
				}//end if	
			}//end else	

	
			
			
			
			//Note: Any other messages created for COMM/CMNC has priority over error messages. Error messages are just for status, but any other messages may be used for debugging.											

		
			//Run highest priority functions here. //this will override any lower priority messages
	
			//increment the loop count while MAIN is still in SYSTEM_ERROR. This should take highest priority.
			timeout_counter++;				
			
			
			#ifndef _DEBUG_DISABLE_SYSTEM_ERROR_TIMEOUT //normally the timeout code would run. Can disable it for debugging purposes
				//if MAIN has been stuck in SYSTEM_ERROR for a long time, request for COMM to do a hw reset
				if(timeout_counter >= MAIN_SYSTEM_ERROR_TIMEOUT_VALUE)
				{
					comm_msg_queue = CMD_TAG_ALL_HW_RESET_REQUEST;
					//do not clear the counter. allow it to keep sending ALL_HW_RESET_REQUEST to COMM until a HW reset is done by COMM to MAIN
				}//end if
			#endif	
			
			break;		
		case CONTROL_OUTPUTS: //Mode: SYSTEM_ERROR

			//enable_mtr_pwr should be false. It is set when the mode was just switched to SYSTEM_ERROR, i.e. SYSTEM_ERROR *begin*		

			if( ! BooleanBitFlags::flagIsSet(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_))
			{	
				//Turn motor MOSFET off
				mtrPowerCtrlr->setMotorPower(MTR_DISABLED);
			}//end if
			else//there is an error in the code logic
			{
				_SERIAL_DEBUG_CHANNEL_.println(F("MtrPwrCtrlErr"));//Motor Power Controller Error
			}//end else				
					
			break;		
		case CREATE_DATA: //Mode: SYSTEM_ERROR

			//Creates data for PC_USB
			if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_PC_USB);
				
				/*
					For SYNC_ERROR_STATUS, SLEEP_ERROR_STATUS,
					SW_RESET_ERROR_STATUS, GENERIC_SYSTEM_ERROR_STATUS,
					CMD_TAG_GENERIC_HEALTH_STATUS_ERROR, INVALID_STATE_ERROR_STATUS, in createDataFromQueueFor, create the message using error_origin as the message origin
				*/
				
				//skip auto data	
				
			}//end if
			//Creates data for COMM
			if (comm_msg_queue != CMD_TAG_NO_MSG)
			{
			
				/*
					For SYNC_ERROR_STATUS, SLEEP_ERROR_STATUS,
					SW_RESET_ERROR_STATUS, GENERIC_SYSTEM_ERROR_STATUS,
					CMD_TAG_GENERIC_HEALTH_STATUS_ERROR, in createDataFromQueueFor, create the message using error_origin as the message origin
				*/
				
				if(comm_cmnc_destination_selection == ROVERCOMM_COMM)//data is for COMM
				{
					createDataFromQueueFor(ROVERCOMM_COMM);
				}//end if
				else if(comm_cmnc_destination_selection == ROVERCOMM_CMNC) //data is for CMNC
				{
					createDataFromQueueFor(ROVERCOMM_CMNC);
				}//end else if
				else//invalid state, error out
				{
					_SERIAL_DEBUG_CHANNEL_.println(F("ErrUnkDest"));//error, unknown destination
				}//end else
				
				//skip auto data
								
			}//end if			
			//Creates data for NAVI
			if (navi_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_NAVI);
				
				/*
					For GENERIC_SYSTEM_ERROR_STATUS, CMD_TAG_GENERIC_HEALTH_STATUS_ERROR in createDataFromQueueFor, create the message using error_origin as the message origin
				*/
				
				//skip auto data	
				
			}//end if
			//Creates data for AUXI
			if (auxi_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_AUXI);
				
				
				/*
					For GENERIC_SYSTEM_ERROR_STATUS, CMD_TAG_GENERIC_HEALTH_STATUS_ERROR in createDataFromQueueFor, create the message using error_origin as the message origin
				*/
				
				//skip auto data					
				
			}//end if			
			
			//Clear Motor Power Status
			BooleanBitFlags::clearFlagBit(flagSet_SystemStatus1, _BTFG_MTR_POWER_ON_);
					
		
			break;
		case TX_COMMUNICATIONS: //Mode: SYSTEM_ERROR

			//Interweave primary transmissions and redirection, to allow the receiving end have time to process each incoming data
	
			if(BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_FIRST_TRANSMISSION_))//check to see if this is the first transmission
			{							
				//1. Sends data to PC_USB
				if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
				{
					txData(txMsgBuffer_PC_USB, ROVERCOMM_PC_USB);
				}//end if
				//2. Sends data to COMM
				if (comm_msg_queue != CMD_TAG_NO_MSG)
				{
					txData(txMsgBuffer_COMM, ROVERCOMM_COMM);//Note: This just sends the data as created through the COMM channel. Whether it goes to CMNC or COMM, that would be determined in the createDataFromQueueFor().
				}//end if				
				//3. Sends data to NAVI
				if (navi_msg_queue != CMD_TAG_NO_MSG)
				{
					txData(txMsgBuffer_NAVI, ROVERCOMM_NAVI);
				}//end if					
				//4. Sends data to AUXI
				if (auxi_msg_queue != CMD_TAG_NO_MSG)
				{
					txData(txMsgBuffer_AUXI, ROVERCOMM_AUXI);
				}//end if				
				//5. Check to see if there are any second messages to send
				if (
					BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_REDIRECT_TO_PC_USB_)
					|| BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_REDIRECT_TO_COMM_)
					|| BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_REDIRECT_TO_NAVI_)
					|| BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_REDIRECT_TO_AUXI_)
					)		
				{
					BooleanBitFlags::clearFlagBit(flagSet_SystemStatus1, _BTFG_FIRST_TRANSMISSION_);//clear the flag
					//reset the counter before use
					transmission_delay_cnt = 0;
					queuedState = TX_COMMUNICATIONS;//override the default state (usually would be RX_COMMUNICATIONS)
				}//end if
				else//there is no second transmission, move on
				{					
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
				}//end else
			}//end if	
			else//this is not the first transmission
			{
			
				if(transmission_delay_cnt >= CONCURRENT_TRANSMISSION_DELAY) //once the desired delay has been reached, continue with the code
				{
					//Send the second set of messages
					redirectData(roverComm_Ch1);//This function will redirect data as required, and limit it to one redirection per channel (due to the limits of throughput on the receiving end)
					redirectData(roverComm_Ch2);//This function will redirect data as required, and limit it to one redirection per channel (due to the limits of throughput on the receiving end)	
					redirectData(roverComm_Ch3);//This function will redirect data as required, and limit it to one redirection per channel (due to the limits of throughput on the receiving end)	
					redirectData(roverComm_Ch4);//This function will redirect data as required, and limit it to one redirection per channel (due to the limits of throughput on the receiving end)	
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
				}//end if
				else//the desired delay has not been reached yet, so just increment the count
				{
					transmission_delay_cnt++;
				}//end else			
			}//end else		
		
			break;				
		default: //default state
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
	comm_msg_queue = CMD_TAG_INVALID_STATE_OR_MODE_ERROR_STATUS;
	pc_usb_msg_queue = CMD_TAG_INVALID_STATE_OR_MODE_ERROR_STATUS;
	navi_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;
	auxi_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;
				
	error_origin = ROVERCOMM_MAIN;

	//Set the mode to SYSTEM_ERROR (though it might already be set to that in certain circumstances)
	currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*
	//Note: For now don't set the queuedState. But if it doesn't work as expected (i.e. there is a programming logic error), set it to CONTROL_OUTPUTS.
	//shut down motor when in error for safety
	BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_ENABLE_MTR_POWER_);		
	
	
		
	//Set Invalid State Error Flag
	//Note: The Invalid State Error Flag cann only be cleared with a sw reset or hw reset
	BooleanBitFlags::setFlagBit(flagSet_Error1, _BTFG_INVALID_STATE_OR_MODE_ERROR_);

	//initialize/reset shared counter before use
	timeout_counter = 0;
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
	roverDataForMAIN = NULL;
	roverDataForPC_USB = NULL;
	roverDataForCOMM = NULL;
	roverDataForNAVI = NULL;
	roverDataForAUXI = NULL;
	
}//end of clearRoverDataPointer()

void setRoverDataPointer(RoverData * roverDataPointer, byte roverCommType)
{
	//This sets the roverDataPointer to the desired roverCommType.
	//Note: This function can be called more than once to set more than one roverDataPointer to the same data (i.e. if the same data needs to be shared in multiple places)
	if (roverCommType == ROVERCOMM_PC_USB)
	{
		roverDataForPC_USB = roverDataPointer;
	}//end if
	else if (roverCommType == ROVERCOMM_COMM || roverCommType == ROVERCOMM_CMNC)//CMNC has to go through COMM
	{
		roverDataForCOMM = roverDataPointer;
	}//end else if
	else if (roverCommType == ROVERCOMM_NAVI)
	{
		roverDataForNAVI = roverDataPointer;
	}//end else if
	else if (roverCommType == ROVERCOMM_AUXI)
	{
		roverDataForAUXI = roverDataPointer;
	}//end else if
	else//the roverCommType should be for this local Arduino (i.e. ROVERCOMM_MAIN)
	{
		roverDataForMAIN = roverDataPointer;
	}//end else
}//end of setRoverDataPointer()