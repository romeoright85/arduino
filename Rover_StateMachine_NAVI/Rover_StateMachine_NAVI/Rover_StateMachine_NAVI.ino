//============NAVI Template Below (derived from MAIN/COMM/and NAVI so may have variables from each of these state machines================


/*
Note:
The best way to read this code from scratch is look at the global default values, see what state and mode the variables get on power on, then follow the state machine in the loop from the initializing state and mode
*/



/*
Design Notes:
Currently the priority level is not being used to prioritize right now. It's just there as a placeholder.
*/

//Rover_StateMachine_NAVI



/*
--------------------------------
Regular Operation
--------------------------------
//No commands are sent to NAVI directly during regular operation.


--------------------------------
Debug Operation
--------------------------------
//To test code, in RoverConfig uncomment _DEBUG_ALL_SERIALS_WITH_USB_SERIAL_


To test locally with only one Arduino , first make sure if _DEBUG_ALL_SERIALS_WITH_USB_SERIAL_ is uncommented in RoverConfig.h

//WRITE ME LATER

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
#ifndef _ARD_1_NAVI_H
#define _ARD_1_NAVI_H //Must define this before calling RoverConfig.h (either directly or through another header file), define this flag to turn on COMM definitions
#endif
#ifndef _DRIVESETTING_DEFINITIONS
#define _DRIVESETTING_DEFINITIONS //For RoverConfig.h
#endif
#ifndef _NAVI_BIT_FLAGS_
#define _NAVI_BIT_FLAGS_ //For RoverBitFlags.h
#endif
#ifndef _NAVI_STATE_MACHINE_VARIABLES_
#define _NAVI_STATE_MACHINE_VARIABLES_ //For RoverConfig.h
#endif
#ifndef _ROVER_SHARED_QUEUE_DEFINITIONS
#define _ROVER_SHARED_QUEUE_DEFINITIONS //For RoverConfig.h
#endif
#ifndef _ENABLE_BUBBLESORT_CLASS_
#define _ENABLE_BUBBLESORT_CLASS_ //For RoverConfig.h
#endif
#ifndef _MOTORCONTROLLER_DEFINITIONS
#define _MOTORCONTROLLER_DEFINITIONS
#endif
#ifndef _ULTRASONIC_SENSOR_DEFINITIONS
#define _ULTRASONIC_SENSOR_DEFINITIONS
#endif
#ifndef _INFRARED_SENSOR_DEFINITIONS
#define _INFRARED_SENSOR_DEFINITIONS
#endif
#ifndef _WHEEL_ENCODER_DEFINITIONS
#define _WHEEL_ENCODER_DEFINITIONS
#endif
#ifndef _GPS_SENSOR
#define _GPS_SENSOR
#endif
#ifndef _LED_SET_TYPES
#define _LED_SET_TYPES
#endif
#ifndef _ROVER_WAYPOINT_DESTINATIONS_
#define _ROVER_WAYPOINT_DESTINATIONS_
#endif




//#includes
#include <RoverStatesAndModes.h>
#include <RoverCommandDefs.h>
#include <RoverCommandCreator.h>
#include <RoverData.h>
#include <RoverComm.h> //calls RoverConfig.h
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>
#include <DelayCounter.h>
#include <WheelEncoderSensor.h>
#include <BufferSelect.h>
#include <MotorController.h>
#include <GimbalController.h>
#include <RoverCalibration.h>
#include <RoverSleeperServer.h>
#include <RoverSleeperClient.h>
#include <UltrasonicSensor.h>
#include <IrDistanceSensor.h>
#include <RoverMessagePackager.h>
#include <avr/pgmspace.h> //To store certain variables in Flash
#include <BooleanBitFlags.h>	
#include <RoverBitFlags.h>	
#include <RoverNavigation.h>
#include <RoverGpsSensor.h>
#include <CharArray.h>
#include <BubbleSort.h>
#include <DataType.h>
#include <LedController_NAVI.h>
#include <RoverConfig.h>	
//WRITE MORE LATER
//ADD MORE LATER


//============Function Prototypes
void InterruptDispatch_wheelEncoder_FrontLeft();
void InterruptDispatch_wheelEncoder_FrontRight();
void InterruptDispatch_wheelEncoder_RearLeft();
void InterruptDispatch_wheelEncoder_RearRight();

void InterruptDispatch_WakeUpArduino();//For RoverSleeper
//============End of Function Prototypes


//============Debugging: Serial Channel Selection
//Used to output debugging messages only when the _DEBUG_COMM_BROADCAST flag is defined
//Uncomment the flag below in order to output debugging messages
//#define _DEBUG_COMM_BROADCAST

//Flag Logic, no need to edit this below
//Reference the "Where Left Off...txt" at: K:\Working Directory\DESIGN_PROJ\Design Projects\Robot\Workspaces\Arduino\2nd Gen Code\GitHub\arduino\Planning
#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ _MAIN_SERIAL_ //When using COMM Broadcast, reroute the PC USB output to the channel to MAIN instead
#else
	#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_
#endif


//============End of Debugging: Serial Channel Selection



//============Debugging: Print GPS Data Status
//Uncomment to print GPS Data Valid Status
//#define _PRINT_GPS_DATA_STATUS
//============End Debugging: Print GPS Data Status


//============Debugging: Print GPS Median Completed
//Uncomment to print GPS Median Completed Status
//#define _PRINT_GPS_MEDIAN_COMPLETED_STATUS
//============End Debugging: Print GPS Median Completed





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







//============Debugging: Print Wakeup Status
//Uncomment the flag below in order to print the Wake Up Status
//#define _DEBUG_PRINT_SLEEPING_AND_WAKEUP_STATUS //Normally commented out during normal operations.


#ifdef _DEBUG_PRINT_SLEEPING_AND_WAKEUP_STATUS
#define _PRINT_SLEEPING_AND_WAKEUP_STATUS_ _SERIAL_DEBUG_CHANNEL_.println
#else
#define _PRINT_SLEEPING_AND_WAKEUP_STATUS_ void
#endif


//============End Debugging: Print Wakeup Status





//============Debugging: Skip to Normal Operations
//Uncomment the flag below to jump straight to normal operations and test the auto data, etc.

//#define _DEBUG_SKIP_RIGHT_TO_NORMAL_OPERATIONS_ //Normally commented out during normal operations.

//============End Debugging: Skip to Normal Operations


 //============Debugging: Print IMU Median Completed Status
//Uncomment to print IMU Median Completed Status
//#define _PRINT_IMU_MEDIAN_COMPLETED_STATUS
//============End Debugging: Print IMU Median Completed Status

 //============Debugging: Print GPS Median Completed Status
//Uncomment to print GPS Median Completed Status
//#define _PRINT_GPS_MEDIAN_COMPLETED_STATUS
//============End Debugging: Print GPS Median Completed Status

//============Debugging: All Data Filtering Off
//Uncomment in order to allow all data to pass (turn off all data filters) for debugging
//#define _DEBUG_TURN_OFF_ALL_DATA_FILTERS
//============End Debugging: All Data Filtering Off


//============Debugging: Turn off System Ready Status During Synchronization Mode
//Uncomment in order to allow other data to be in the main_pri_msg_queue instead of just System Status
//#define _DEBUG_TURN_OFF_SYSTEM_READY_STATUS //Normally commented out during normal operations.
//============End Debugging: Turn off System Ready 



//============Debugging: Print timeout counter value
//Uncomment in order to print timeout counter value
//#define _DEBUG_PRINT_TIMEOUT_COUNTER_VALUE_
//============End Debugging: Print timeout counter value


//============Debugging: Disable NAVI Sync Timeout
//Uncomment in order to disable the COMM Sync timeout
//#define _DEBUG_DISABLE_NAVI_SYNC_TIMEOUT //Normally commented out during normal operations.
//============End Debugging: Disable NAVI Sync Timeout


//============Debugging: Print Drive Selection Status
//Uncomment in order to print out the Sleep/Wake Status
#define _DEBUG_OUTPUT_DRIVE_SELECTION_STATUS
//============End Debugging: Print Drive Selection Status



//============Debugging: Print Sleep/Wake Status
//Uncomment in order to print out the Sleep/Wake Status
#define _DEBUG_OUTPUT_SLEEP_WAKE_STATUS_
//============End Debugging: Print Sleep/Wake Status



//============Global Declarations


//=====SW Resettable Variables (reinitialize these variables on software reset)


//Auto Data Counters
//They can just be byte instead of unsigned int since there aren't that many elements. Also a byte is already positive numbers or zero
byte auto_NAVI_to_COMM_data_cnt = 0;
byte auto_NAVI_to_CMNC_data_cnt = 0;
byte auto_NAVI_to_MAIN_data_cnt = 0;
byte auto_NAVI_to_AUXI_data_cnt = 0;



byte motor_turn_value = SET_GO_STRAIGHT;
byte prev_motor_turn_value = SET_GO_STRAIGHT; //used to hold the previous state, before going to sleep	
byte motor_speed_value = SET_STOP_SPEED;
byte prev_motor_speed_value = SET_STOP_SPEED; //used to hold the previous state, before going to sleep	
byte gimbal_pan_value = SET_CENTER_PAN;
byte prev_gimbal_pan_value = SET_CENTER_PAN; //used to hold the previous state, before going to sleep
byte gimbal_tilt_value = SET_MIDDLE_TILT;
byte prev_gimbal_tilt_value = SET_MIDDLE_TILT; //used to hold the previous state, before going to sleep
byte drive_setting = AUTONOMOUS_DRIVE;//can be AUTONOMOUS_DRIVE, SEMI_AUTO_DRIVE, or MANUAL_DRIVE. 
	//this is independent of the _BTFG_REMOTE_CTRL_SELECTED_ flag (i.e. buffer_remote_ctrl_selected), since for semi-auto the drive setting stays the same but the buffer select might change if while the rover is manually controlled, an object is detected and the rover takes over. The buffer select can only be controlled internally through the drive setting option and not directly.
byte prev_drive_setting = AUTONOMOUS_DRIVE;//used to hold the previous state, before going to sleep



byte universal_led_mode = LED_SET_ALL_DEFAULT;
byte prev_universal_led_mode = LED_SET_ALL_DEFAULT;//used to hold the previous state, before going to sleep
byte hazard_light_state = LED_SET_ALL_DEFAULT;
byte prev_hazard_light_state = LED_SET_ALL_DEFAULT;//used to hold the previous state, before going to sleep
byte fog_light_state = LED_SET_ALL_DEFAULT;
byte prev_fog_light_state = LED_SET_ALL_DEFAULT;//used to hold the previous state, before going to sleep
byte underglow_light_state = LED_SET_ALL_DEFAULT;
byte prev_underglow_light_state = LED_SET_ALL_DEFAULT;//used to hold the previous state, before going to sleep
byte ir_beacon_state = LED_SET_ALL_DEFAULT;
byte prev_ir_beacon_state = LED_SET_ALL_DEFAULT;//used to hold the previous state, before going to sleep
byte blue_beacon_state = LED_SET_ALL_DEFAULT;
byte prev_blue_beacon_state = LED_SET_ALL_DEFAULT;//used to hold the previous state, before going to sleep
byte beacon_led_direction = LED_SET_ALL_DEFAULT;
byte prev_beacon_led_direction = LED_SET_ALL_DEFAULT;//used to hold the previous state, before going to sleep
byte rover_motion = LED_SET_ALL_DEFAULT;
byte prev_rover_motion = LED_SET_ALL_DEFAULT;//used to hold the previous state, before going to sleep
byte rover_error_type = LED_SET_ALL_DEFAULT;
byte prev_rover_error_type = LED_SET_ALL_DEFAULT;//used to hold the previous state, before going to sleep
				
				




//TEMPLATE//byte wheelEncoder_MidLeft_Direction = MOTOR_STOPPED;//used to store values passed in from MAIN
byte wheelEncoder_MidRight_Direction = MOTOR_STOPPED;//used to store values passed in from MAIN
//TEMPLATE//int wheelEncoder_MidLeft_Speed = 0;//used to store values passed in from MAIN
int wheelEncoder_MidRight_Speed = 0;//used to store values passed in from MAIN
//TEMPLATE//int wheelEncoder_MidLeft_Footage = 0;//used to store values passed in from MAIN
int wheelEncoder_MidRight_Footage = 0;//used to store values passed in from MAIN

	
	

//Error Origin (used to send out the origin of the error with the error message)
byte error_origin = ROVERCOMM_NONE;


//Flag(s) - Error
byte flagSet_Error1 = _BTFG_NONE_;
//Flag(s) - Message Controls
byte flagSet_MessageControl1 = _BTFG_NONE_;
//Flag(s) - System Status 1
byte flagSet_SystemStatus1 = _BTFG_FIRST_TRANSMISSION_;//Default: Set the first transmission flag only, leave everything else unset
//Flag(s) - Command Filter Options - MAIN and PC_USB each have their own set since they have separate data filters
//Command Filter Options for PC_USB: Set 1
byte commandFilterOptionsSet1_PC_USB = _BTFG_NONE_;
//Command Filter Options for PC_USB: Set 2
byte commandFilterOptionsSet2_PC_USB = _BTFG_NONE_;
//Command Filter Options for PC_USB: Set 3
byte commandFilterOptionsSet3_PC_USB = _BTFG_NONE_;
//Command Filter Options for PC_USB: Set 4
byte commandFilterOptionsSet4_PC_USB = _BTFG_NONE_;
//Command Filter Options for PC_USB: Set 5
byte commandFilterOptionsSet5_PC_USB = _BTFG_NONE_;
//Command Filter Options for PC_USB: Set 6
byte commandFilterOptionsSet6_PC_USB = _BTFG_NONE_;
//Command Filter Options for PC_USB: Set 7
byte commandFilterOptionsSet7_PC_USB = _BTFG_NONE_;
//Command Filter Options for MAIN: Set 1
byte commandFilterOptionsSet1_MAIN = _BTFG_NONE_;
//Command Filter Options for MAIN: Set 2
byte commandFilterOptionsSet2_MAIN = _BTFG_NONE_;
//Command Filter Options for MAIN: Set 3
byte commandFilterOptionsSet3_MAIN = _BTFG_NONE_;
//Command Filter Options for MAIN: Set 4
byte commandFilterOptionsSet4_MAIN = _BTFG_NONE_;
//Command Filter Options for MAIN: Set 5
byte commandFilterOptionsSet5_MAIN = _BTFG_NONE_;
//Command Filter Options for MAIN: Set 6
byte commandFilterOptionsSet6_MAIN = _BTFG_NONE_;
//Command Filter Options for MAIN: Set 7
byte commandFilterOptionsSet7_MAIN = _BTFG_NONE_;



//Flag(s) - System Controls
byte flagSet_SystemControls1 = _BTFG_NONE_;


//Counters
unsigned int timeout_counter = 0; //shared counter, used to detect timeout of NAVI responding back to MAIN for any reason 

	//WRITE MORE LATER - add comments on what else timeout_counter is used for. Just search for timeout_counter++ once the code is done and see all the places it's used in and for what purposes
	
	
unsigned int transmission_delay_cnt = 0;//concurrent transmission delay counter



//------------------From CommTester_MAIN
//Message Queues
// (command tag, not boolean since use by CREATE_DATA to generate messages as well as TX_COMMUNICATIONS as a flag)
byte pc_usb_msg_queue = CMD_TAG_NO_MSG;// PC_USB won't get autodata, as it would make the code really complex with a lot of duplication. If needed, you can always reroute the serial channels using #ifdef
byte main_pri_msg_queue = CMD_TAG_NO_MSG;// primary message queue
byte main_sec_msg_queue = CMD_TAG_NO_MSG;//secondary message queue
	

//Data Destination Selections
byte pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;//default to MAIN, as you don't want just any data leaking out to CMNC (data security)

byte sec_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;//default to MAIN, as you don't want just any data leaking out to CMNC (data security)



//Flag(s) - Rover Data Channels Status
byte ch1Status = DATA_STATUS_NOT_READY;//for PC_USB
byte ch2Status = DATA_STATUS_NOT_READY;//for MAIN




//RoverData and RoverComms
//Ch1 is between NAVI and PC USB
RoverData * roverDataCh1_COMM = new RoverData();
RoverComm * roverComm_Ch1 = new RoverComm(roverDataCh1_COMM);
//Ch3 is between NAVI and MAIN
RoverData * roverDataCh2_COMM = new RoverData();
RoverComm * roverComm_Ch2 = new RoverComm(roverDataCh2_COMM);


//Rover Data Pointers for use with either internal processing or outgoing messages
//Note: These pointers will be (re-)initialized by the function clearRoverDataPointers()
//Note: These pointers are used by setRoverDataPointer(), as well as other places.
RoverData * roverDataForNAVI;//pointer used access the RoverData which has the command data incoming to NAVI, holds the data (and not just the command) if it's needed. Sometimes the data is not used, but is there just in case it's needed later. i.e. example data would be strings such as "nodata", "invlcmd", or actual values like lat/lon, speed, heading, etc.
RoverData * roverDataForPC_USB;//pointer used access the RoverData which has the command data outgoing to PC_USB
RoverData * roverDataForMAIN;//pointer used access the RoverData which has the command data outgoing to MAIN.






//------------------From WakeUpTester_NAVI
RoverSleeperServer * sleeperNAVI = new RoverSleeperServer(NAVI_WAKEUP_CTRL_PIN, &InterruptDispatch_WakeUpArduino);//NAVI Wakeup Pin Control



//------------------From MotorAndServoTester_NAVI
BufferSelect * roverBuffer = new BufferSelect(BUFFER_SELECT_PIN);

//The WheelEncoder will wait for 1sec (1000 periods * 1mS) between each wheel encoder calculation
DelayCounter * frontLeftSyncCounter = new DelayCounter(DELAY_200_PERIODS);//initialize it to count to 1 periods x 1ms delay timer resolution = 1ms before the count has reached flag goes true
GlobalDelayTimer * frontLeftSyncTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, frontLeftSyncCounter);//everytime the delay interval (resolution) is reached, it will increment the delay counter. The standard resolution used for the Rover has been 5mS so it's not too small where it has to increment the counter often, but not to big where it won't work for many different classes without being too slow or fast

DelayCounter * frontRightSyncCounter = new DelayCounter(DELAY_200_PERIODS);//initialize it to count to 1 periods x 1ms delay timer resolution = 1ms before the count has reached flag goes true
GlobalDelayTimer * frontRightSyncTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, frontRightSyncCounter);//everytime the delay interval (resolution) is reached, it will increment the delay counter. The standard resolution used for the Rover has been 5mS so it's not too small where it has to increment the counter often, but not to big where it won't work for many different classes without being too slow or fast

DelayCounter * rearLeftSyncCounter = new DelayCounter(DELAY_200_PERIODS);//initialize it to count to 1 periods x 1ms delay timer resolution = 1ms before the count has reached flag goes true
GlobalDelayTimer * rearLeftSyncTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, rearLeftSyncCounter);//everytime the delay interval (resolution) is reached, it will increment the delay counter. The standard resolution used for the Rover has been 5mS so it's not too small where it has to increment the counter often, but not to big where it won't work for many different classes without being too slow or fast

DelayCounter * rearRightSyncCounter = new DelayCounter(DELAY_200_PERIODS);//initialize it to count to 1 periods x 1ms delay timer resolution = 1ms before the count has reached flag goes true
GlobalDelayTimer * rearRightSyncTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, rearRightSyncCounter);//everytime the delay interval (resolution) is reached, it will increment the delay counter. The standard resolution used for the Rover has been 5mS so it's not too small where it has to increment the counter often, but not to big where it won't work for many different classes without being too slow or fast






//Note: Remember to update all fields of the constructor. All the fields are unique to/distinct for each motor. You can't share the counter, because it gets reset for each one. And each timer get's only one counter, so you need a timer for each one as well.
WheelEncoderSensor * wheelEncoder_FrontLeft = new WheelEncoderSensor(ENCODER_A_FRONT_LEFT, ENCODER_B_FRONT_LEFT, LEFT_MOUNTED, &InterruptDispatch_wheelEncoder_FrontLeft, frontLeftSyncCounter);
WheelEncoderSensor * wheelEncoder_FrontRight = new WheelEncoderSensor(ENCODER_A_FRONT_RIGHT, ENCODER_B_FRONT_RIGHT, RIGHT_MOUNTED, &InterruptDispatch_wheelEncoder_FrontRight, frontRightSyncCounter);
WheelEncoderSensor * wheelEncoder_RearLeft = new WheelEncoderSensor(ENCODER_A_REAR_LEFT, ENCODER_B_REAR_LEFT, LEFT_MOUNTED, &InterruptDispatch_wheelEncoder_RearLeft, rearLeftSyncCounter);
WheelEncoderSensor * wheelEncoder_RearRight = new WheelEncoderSensor(ENCODER_A_REAR_RIGHT, ENCODER_B_REAR_RIGHT, RIGHT_MOUNTED, &InterruptDispatch_wheelEncoder_RearRight, rearRightSyncCounter);





//------------------From UltrasonicSensorTest
UltrasonicSensor * uSon_FwdLeft = new UltrasonicSensor(FORWARD_LEFT_ULTSNC_TRIG_PIN, FORWARD_LEFT_ULTSNC_ECHO_PIN);
UltrasonicSensor * uSon_FwdCenter = new UltrasonicSensor(FORWARD_CENTER_ULTSNC_TRIG_PIN, FORWARD_CENTER_ULTSNC_ECHO_PIN);
UltrasonicSensor * uSon_FwdRight = new UltrasonicSensor(FORWARD_RIGHT_ULTSNC_TRIG_PIN, FORWARD_RIGHT_ULTSNC_ECHO_PIN);
UltrasonicSensor * uSon_SideRight = new UltrasonicSensor(SIDE_RIGHT_ULTSNC_TRIG_PIN, SIDE_RIGHT_ULTSNC_ECHO_PIN);
UltrasonicSensor * uSon_RearCenter = new UltrasonicSensor(REAR_CENTER_ULTSNC_TRIG_PIN, REAR_CENTER_ULTSNC_ECHO_PIN);
UltrasonicSensor * uSon_SideLeft = new UltrasonicSensor(SIDE_LEFT_ULTSNC_TRIG_PIN, SIDE_LEFT_ULTSNC_ECHO_PIN);


int uSonDistanceMeasured[ULTRASONIC_SENSORS_ARRAY_SIZE] = {0};//initialize all elements to zero
int irDistanceMeasured[INFRARED_SENSORS_ARRAY_SIZE] = {0};//initialize all elements to zero
byte allWheelEncodersDirection[ALL_WHEEL_ENCODERS_SENSORS_ARRAY_SIZE] = {0};//initialize all elements to zero. Stores wheel encoder direction values from MAIN as well as from NAVI. Note: A MOTOR_STOPPED value is 0 for Direction.
int allWheelEncodersFootage[ALL_WHEEL_ENCODERS_SENSORS_ARRAY_SIZE] = {0};//initialize all elements to zero. Stores wheel encoder values from MAIN as well as from NAVI. Note: A 0 value for Footage is 0 for Footage.
int allWheelEncodersSpeed[ALL_WHEEL_ENCODERS_SENSORS_ARRAY_SIZE] = {0};//initialize all elements to zero. Stores wheel encoder values from MAIN as well as from NAVI. Note: A 0 value for Speed is 0 for Speed.


//------------------From IrDistanceSensorTest

IrDistanceSensor * irDistanceForwardCenter = new  IrDistanceSensor(FORWARD_CENTER_IR_DIST_SENSOR_PIN);
IrDistanceSensor * irDistanceSideRight = new  IrDistanceSensor(SIDE_RIGHT_IR_DIST_SENSOR_PIN);
IrDistanceSensor * irDistanceRearCenter = new  IrDistanceSensor(REAR_CENTER_IR_DIST_SENSOR_PIN);
IrDistanceSensor * irDistanceSideLeft = new IrDistanceSensor(SIDE_LEFT_IR_DIST_SENSOR_PIN);


//------------------From NavigationTester_NAVI
RoverNavigation * roverNavigation = new RoverNavigation();
RoverGpsSensor * roverGps = new RoverGpsSensor();
//flags counters and data arrays for GPS and heading data
byte headingDataCounter = 0;//counts the number of heading data collected (and averaged)
byte gpsDataCounter = 0;//counts the number of GPS data collected (and averaged)
//array to hold the GPS samples
double latitudeArray[_BUBBLESORT_MEDIAN_ARRAY_SIZE_];//stores latitude (in decimal-degrees) samples for sort and median, size is fixed to 7 due to the fixed (hardcoded) size of the getMedian function
double longitudeArray[_BUBBLESORT_MEDIAN_ARRAY_SIZE_];//stores longitude (in decimal-degrees) samples for sort and median, size is fixed to 7 due to the fixed (hardcoded) size of the getMedian function
//array to hold the heading samples
double headingArray[_BUBBLESORT_MEDIAN_ARRAY_SIZE_];//stores heading samples for sort and median, size is fixed to 7 due to the fixed (hardcoded) size of the getMedian function
double tempHeadingData;//holds the temp heading data taken from the command data received by AUXI. It will get verified for validity before it's assigned to the headingArray.

//IMPROVEMENT TIP: Allow the rover to add more than one destination coordinate in the future.


//------------------From LedController_NAVI_Tester
DelayCounter * ledControllerDelayCounter = new DelayCounter(DELAY_100_PERIODS);//initialize it to count to 100 periods (so 100 periods x 5ms = 500ms). This is only the initial/default delay. It may change in the code dynamically as needed.
GlobalDelayTimer * ledControllerTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, ledControllerDelayCounter);//arbitrarily chose 5ms resolution for the timer. Can change this later to something else if I want
LedController_NAVI * ledController_NAVI = new LedController_NAVI(ledControllerDelayCounter, DELAY_25_PERIODS, DELAY_100_PERIODS);//the short delay is 25 periods (25x5ms=125ms) and the long delay is 100 periods (100x5ms=500ms)






//Note: Make sure to add any new objects created to this array
//Note: Declare this after SW Resettable and Non-Resettable variables, else the compiler will complain.
RoverReset * resetArray[] = {	
	roverDataCh1_COMM,
	roverComm_Ch1,
	roverDataCh2_COMM,
	roverComm_Ch2,
	sleeperNAVI,
	roverBuffer,
	frontLeftSyncCounter,
	frontLeftSyncTimer,
	frontRightSyncCounter,
	frontRightSyncTimer,
	rearLeftSyncCounter,
	rearLeftSyncTimer,
	rearRightSyncCounter,
	rearRightSyncTimer,
	wheelEncoder_FrontLeft,
	wheelEncoder_FrontRight,
	wheelEncoder_RearLeft,
	wheelEncoder_RearRight,
	uSon_FwdLeft,
	uSon_FwdCenter,
	uSon_FwdRight,
	uSon_SideRight,
	uSon_RearCenter,
	uSon_SideLeft,
	irDistanceForwardCenter,
	irDistanceSideRight,
	irDistanceRearCenter, 
	irDistanceSideLeft,
	roverNavigation,
	roverGps,
	ledControllerDelayCounter,
	ledControllerTimer,
	ledController_NAVI
};//for pointers, pass them directly, for objects pass the address


//=====End of: SW Resettable Variables




//=====Non-SW Resettable Variables (do not reinitialize these variables on software reset)

//Holds ultrasonic sensors in an array so can loop through them more efficiently
UltrasonicSensor * uSonSensors[ULTRASONIC_SENSORS_ARRAY_SIZE];//The objects will be assigned in the setup() function.
//Holds IR sensors in an array so can loop through them more efficiently
IrDistanceSensor * irDistanceSensors[INFRARED_SENSORS_ARRAY_SIZE];//The objects will be assigned in the setup() function.
WheelEncoderSensor * naviWheelEncoders[NAVI_WHEEL_ENCODERS_SENSORS_ARRAY_SIZE];//The objects will be assigned in the setup() function.




//Note: Remember MAIN currently only receives and processes generic system error and generic health errors. Also it can't redirect in some modes (i.e. SYNCHRONIZATION) so sending it an error (i.e. sync error) won't do any good.



//Auto Data Arrays
//Note: PC_USB doesn't get auto data (since it normally doesn't get monitored, and having data generated all the time would slow the system down)


byte auto_NAVI_to_COMM_data_array[] = {
};
byte auto_NAVI_to_CMNC_data_array[] = {
	CMD_TAG_ENC_STATUS_FRT_LEFT,
	CMD_TAG_ENC_STATUS_FRT_RIGHT,
	CMD_TAG_ENC_STATUS_REAR_LEFT,
	CMD_TAG_ENC_STATUS_REAR_RIGHT,
	CMD_TAG_IR_DISTANCE_FWD_CTR_STATUS,
	CMD_TAG_IR_DISTANCE_SIDE_RT_STATUS,
	CMD_TAG_IR_DISTANCE_SIDE_LT_STATUS,
	CMD_TAG_IR_DISTANCE_REAR_CTR_STATUS,
	CMD_TAG_GIMBAL_PAN_STATUS,
	CMD_TAG_GIMBAL_TILT_STATUS,
	CMD_TAG_MOTOR_SPEED_STATUS,
	CMD_TAG_MOTOR_TURN_STATUS,
	CMD_TAG_LATITUDE_STATUS,
	CMD_TAG_LONGITUDE_STATUS,
	CMD_TAG_ULTSNC_DISTANCE_FWD_LT_STATUS,
	CMD_TAG_ULTSNC_DISTANCE_FWD_CTR_STATUS,
	CMD_TAG_ULTSNC_DISTANCE_FWD_RT_STATUS,
	CMD_TAG_ULTSNC_DISTANCE_SIDE_RT_STATUS,
	CMD_TAG_ULTSNC_DISTANCE_SIDE_LT_STATUS,
	CMD_TAG_ULTSNC_DISTANCE_REAR_CTR_STATUS
};
byte auto_NAVI_to_MAIN_data_array[] = {
};
byte auto_NAVI_to_AUXI_data_array[] = {
};


	

//Message Char Array
char txMsgBuffer_PC_USB[UNIV_BUFFER_SIZE];//transmit buffer for PC_USB
char txMsgBuffer_Pri_MAIN[UNIV_BUFFER_SIZE];//primary transmit buffer for MAIN
char txMsgBuffer_Sec_MAIN[UNIV_BUFFER_SIZE];//secondary transmit buffer for MAIN
char programMem2RAMBuffer[_MAX_PROGMEM_BUFF_STR_LEN_];//Buffer to use for Message Strings


//Fixed Message Strings (to store in flash)
const static char msg_strg_0[] PROGMEM = "nodata";//getMsgString(0)
const static char msg_strg_1[] PROGMEM = "invlcmd";//getMsgString(1)
const static char msg_strg_2[] PROGMEM = "error";//getMsgString(2)
const static char msg_strg_3[] PROGMEM = "semi";//getMsgString(3)
const static char msg_strg_4[] PROGMEM = "manu";//getMsgString(4)
const static char msg_strg_5[] PROGMEM = "auto";//getMsgString(5)
const static char msg_strg_6[] PROGMEM = "on";//getMsgString(6)
const static char msg_strg_7[] PROGMEM = "off";//getMsgString(7)



//Note: Make sure to update  the msg_str_table[] array

//Table of Fixed Commaned Strings (array of strings stored in flash)
const char* const msg_str_table[] PROGMEM = {
	msg_strg_0,
	msg_strg_1,
	msg_strg_2,
	msg_strg_3,
	msg_strg_4,
	msg_strg_5,
	msg_strg_6,
	msg_strg_7
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


	//Assigning object pointers to the Ultrasonic Array
	uSonSensors[ULTRASONIC_FWD_LEFT] = uSon_FwdLeft;
	uSonSensors[ULTRASONIC_SIDE_RIGHT] = uSon_SideRight;
	uSonSensors[ULTRASONIC_FWD_CENTER] = uSon_FwdCenter;
	uSonSensors[ULTRASONIC_REAR_CENTER] = uSon_RearCenter;
	uSonSensors[ULTRASONIC_FWD_RIGHT] = uSon_FwdRight;
	uSonSensors[ULTRASONIC_SIDE_LEFT] = uSon_SideLeft;

	//Assigning object pointers to the IR Distance Sensor Array
	irDistanceSensors[INFRARED_SENSOR_FWD_CENTER] = irDistanceForwardCenter;
	irDistanceSensors[INFRARED_SENSOR_FWD_SIDE_RIGHT] = irDistanceSideRight;
	irDistanceSensors[INFRARED_SENSOR_REAR_CENTER] = irDistanceRearCenter;
	irDistanceSensors[INFRARED_SENSOR_FWD_SIDE_LEFT] = irDistanceSideLeft;

	//Assigning object pointers to the NAVI Wheel Encoders Array
	naviWheelEncoders[WHEEL_ENC_FRONT_LEFT] = wheelEncoder_FrontLeft;
	naviWheelEncoders[WHEEL_ENC_FRONT_RIGHT] = wheelEncoder_FrontRight;
	naviWheelEncoders[WHEEL_ENC_REAR_LEFT] = wheelEncoder_RearLeft;
	naviWheelEncoders[WHEEL_ENC_REAR_RIGHT] = wheelEncoder_RearRight;
	

	
	 //Serial Communications
	//Setup the HW_UART for communications between NAVI and MAIN, NAVI and the GPS, and NAVI and PC USB
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	_PC_USB_SERIAL_.flush();//waits for any outgoing serial data to complete
	
	_MAIN_SERIAL_.begin(MAIN_BAUD_RATE);
	_MAIN_SERIAL_.flush();//waits for any outgoing serial data to complete
	
	_GPS_SERIAL_.begin(GPS_BAUD_RATE);
	_GPS_SERIAL_.flush();//waits for any outgoing serial data to complete
	
	 

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

	frontLeftSyncTimer->Running();
	frontRightSyncTimer->Running();
	rearLeftSyncTimer->Running();
	rearRightSyncTimer->Running();
	ledControllerTimer->Running();

//ADD MORE TIMERS IF NEEDED

}





void loop() {

	uSonSensors[ULTRASONIC_FWD_LEFT] = uSon_FwdLeft;
	uSonSensors[ULTRASONIC_SIDE_RIGHT] = uSon_SideRight;
	uSonSensors[ULTRASONIC_FWD_CENTER] = uSon_FwdCenter;
	uSonSensors[ULTRASONIC_REAR_CENTER] = uSon_RearCenter;
	uSonSensors[ULTRASONIC_FWD_RIGHT] = uSon_FwdRight;
	uSonSensors[ULTRASONIC_SIDE_LEFT] = uSon_SideLeft;



	

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
				case SYSTEM_ERROR:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					queuedState = DATA_VALIDATION;
					//Keep the currentMode the same (unchanged)
					runModeFunction_SYSTEM_ERROR(currentState);
					break;
				default: //default mode					
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
				case SYSTEM_ERROR:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes
					//Keep the queuedState the same (unchanged)
					//Keep the currentMode the same (unchanged)
					runModeFunction_SYSTEM_ERROR(currentState);
					break;
				default: //default mode					
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
					queuedState = PROCESS_DATA;//inputs not needed to be read yet during the SYNCHRONIZATION stage
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYNCHRONIZATION(currentState);
					break;
				case NORMAL_OPERATIONS:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = READ_INPUTS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_NORMAL_OPERATIONS(currentState);
					break;
				case SYSTEM_ERROR:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = READ_INPUTS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYSTEM_ERROR(currentState);
					break;
				default: //default mode					
					runModeFunction_default();//no state needed, all states do the same thing
					break;
			}//end switch	
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state
			break;
		case READ_INPUTS:
			_PRINT_STATE_(F("STATE: READ_INPUTS"));
			switch (currentMode)
			{
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
					queuedState = CONTROL_OUTPUTS;//Default Next State. This may be overridden by the runModeFunction...()
					currentMode = SYNCHRONIZATION;//Default Next Mode. This may be overridden by the runModeFunction...()
					runModeFunction_SYNCHRONIZATION(currentState);
					break;
				case NORMAL_OPERATIONS:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes				
					queuedState = PLAN_ROUTE;//Default Next State. This may be overridden by the runModeFunction...()
					currentMode = NORMAL_OPERATIONS;//Default Next Mode. This may be overridden by the runModeFunction...()
					runModeFunction_NORMAL_OPERATIONS(currentState);
					break;
				case SYSTEM_ERROR:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = CONTROL_OUTPUTS;//Default Next State. This may be overridden by the runModeFunction...()
					currentMode = SYSTEM_ERROR;//Default Next Mode. This may be overridden by the runModeFunction...()
					runModeFunction_SYSTEM_ERROR(currentState);
					break;
				default: //default mode					
					runModeFunction_default();//no state needed, all states do the same thing
					break;
			}//end switch	
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state
			break;
		case PLAN_ROUTE:
			_PRINT_STATE_(F("STATE: PLAN_ROUTE"));
			switch (currentMode)
			{
				case NORMAL_OPERATIONS:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = OBJECT_AVOIDANCE;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_NORMAL_OPERATIONS(currentState);
					break;
				default: //default mode					
					runModeFunction_default();//no state needed, all states do the same thing
					break;
			}//end switch	
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state
			break;
		case OBJECT_AVOIDANCE:
			_PRINT_STATE_(F("STATE: OBJECT_AVOIDANCE"));
			switch (currentMode)
			{
				case NORMAL_OPERATIONS:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = CONTROL_OUTPUTS;
					//Keep the currentMode the same (unchanged)	
					runModeFunction_NORMAL_OPERATIONS(currentState);
					break;
				default: //default mode					
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
					queuedState = CREATE_DATA;//Default Next State. This may be overridden by the runModeFunction...()
					currentMode = SYNCHRONIZATION;//Default Next Mode. This may be overridden by the runModeFunction...()
					runModeFunction_SYNCHRONIZATION(currentState);
					break;
				case NORMAL_OPERATIONS:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = CREATE_DATA;
					//Keep the currentMode the same (unchanged)
					runModeFunction_NORMAL_OPERATIONS(currentState);
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
					queuedState = RX_COMMUNICATIONS;//Default Next State. This may be overridden by the runModeFunction...()
					//Keep the currentMode the same (unchanged)	
					runModeFunction_NORMAL_OPERATIONS(currentState);
					break;
				case SYSTEM_SLEEPING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = CONTROL_OUTPUTS;//setting up for SYSTEM_WAKING
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYSTEM_SLEEPING(currentState);
					break;
				case SW_RESETTING:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = RUN_HOUSEKEEPING_TASKS;
					currentMode = INITIALIZATION;//Set mode to INITIALIZATION *begin*
					runModeFunction_SW_RESETTING(currentState);
					break;					
				case SYSTEM_ERROR:
					//Set the states and modes before calling runModeFunction...() as this function may override the default next/queued state and modes								
					queuedState = RX_COMMUNICATIONS;//Default Next State. This may be overridden by the runModeFunction...()
					//Keep the currentMode the same (unchanged)	
					runModeFunction_SYSTEM_ERROR(currentState);			
					break;
				default: //default mode					
					runModeFunction_default();//no state needed, all states do the same thing			
					break;
			}//end switch	
			
			nextState = RUN_HOUSEKEEPING_TASKS;//this is the same for every mode of this state
			
			break;
		default: //default state
			_PRINT_STATE_(F("STATE: default"));			
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
	ledController_NAVI->setUniversalLEDMode(LED_STARTUP_MODE);

//WRITE ME LATER

} //end of initializeVariables()
void startBackgroundTasks()
{
	//start background tasks
//place holder: Add things here as needed.
}//end of startBackgroundTasks()
void runBackgroundTasks()
{
	//run background tasks
	
	//Control the LEDs of the Arduino
	ledController_NAVI->runLedController();
	
	//Wheel Encoders
	wheelEncoder_FrontLeft->sensorOnline();
	wheelEncoder_FrontRight->sensorOnline();
	wheelEncoder_RearLeft->sensorOnline();
	wheelEncoder_RearRight->sensorOnline();
	

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
	else if ( roverCommType == ROVERCOMM_COMM || roverCommType == ROVERCOMM_CMNC || roverCommType == ROVERCOMM_MAIN || roverCommType == ROVERCOMM_AUXI)//COMM, CMNC, MAIN, and AUXI all go through MAIN
	{
		if (_MAIN_SERIAL_.available() > 1)
		{
			//initialize the counter
			counter = 0;
			while (_MAIN_SERIAL_.available() > 0 && counter <= ROVER_COMM_SENTENCE_LENGTH)//while there is data on the Serial RX Buffer and the length is not over the max GPS sentence length
			{
				//Read one character of serial data at a time
				//Note: Must type cast the Serial.Read to a char since not saving it to a char type first
				roverComm->appendToRxData((char)_MAIN_SERIAL_.read());//construct the string one char at a time
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

void dataDirector(RoverData * roverData, byte &flagSet, byte flagOfInterest)//there is no redirection for NAVI, so the redirectOption variable was removed from this function (unlike in MAIN's and COMM's state machine)
{

	//Note: This function varies for different Arduinos

	BooleanBitFlags::clearFlagBit(flagSet, flagOfInterest);//initialize flag to false

	byte roverCommType = roverData->getDestinationCommType();//get the roverComm Destination

	if (roverCommType == ROVERCOMM_NAVI)//if the data is for this Arduino unit
	{
		//if the data is for this unit, NAVI
		BooleanBitFlags::setFlagBit(flagSet, flagOfInterest);//set the status such that the data was for this unit, MAIN
		//process it back in the main loop (to prevent software stack from being too deep)
	}//end if
	//else do nothing
	 
	//NAVI doesn't have or need redirection since it only talks to MAIN. But it does have two message queues, primary and secondary. If for some reason the a non-NAVI message was sent to NAVI, it will be ignored.

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
	else if (roverCommType == ROVERCOMM_COMM || roverCommType == ROVERCOMM_CMNC || roverCommType == ROVERCOMM_MAIN || roverCommType == ROVERCOMM_AUXI)//CMNC, COMM, MAIN, and AUXI all have to go through MAIN
	{
		//transmit the data to COMM
		_MAIN_SERIAL_.println(txData);
	}//end else if
	else
	{
		//do nothing
	}//end else	
}//end of txData()

void commandDirector(RoverData * roverDataPointer, byte roverComm)
{

	//Note: This function runs when the data was meant for this unit.
	
	//Note: This function varies for different Arduinos
	//Categorize all commands/data from all sources.					
	//Sort based on priority.
	//Allow for all non-conflicting commands to run.
	//Then only run the highest priority functions for COMM last, so it will overwrite anything else, right before state transition.

	
	#ifdef _DEBUG_TURN_OFF_ALL_DATA_FILTERS
		setAllCommandFiltersTo(true, ROVERCOMM_PC_USB);//for PC_USB
		setAllCommandFiltersTo(true, ROVERCOMM_MAIN);//for MAIN
	#endif

	byte originRoverCommType;//holds the received data's origin
	byte destinationRoverCommType;//holds the received data's destination
	byte commandTag;//holds received data's command tag
	char commandData[_MAX_ROVER_COMMAND_DATA_LEN_];//holds the received data's command data
	byte commandDataLength;//length of the commandData
	
	
	//Get the received data's origin and destination
	originRoverCommType = roverDataPointer->getOriginCommType();
	destinationRoverCommType = roverDataPointer->getDestinationCommType();

	//Get the command tag from the Rover Data Object
	commandTag = roverDataPointer->getCommandTag();
	//Get the command data from the Rover Data Object	
	commandDataLength = roverDataPointer->getCommandDataLength();
	strncpy(commandData, roverDataPointer->getCommandData(), commandDataLength);	
	
	//Setting the roverDataPointer in order to route where the rover command data will be routed to
	//Clears/resets all data pointers before setting them.
	clearRoverDataPointers();
	//Sets the default such that the rover command data goes to the destination of the command. If needed, this can be overwritten by the command tag if/else statements
	setRoverDataPointer(roverDataPointer, destinationRoverCommType);
	//Note: The roverDataPointer should be going to, NAVI, this unit (else it would have been filtered out, since there is no redirection)
	
	//Run highest priority functions first and lower priorities last.
	//Note: Right now the way it's coded, the conflicting and non conflicting functions are all merged together and treated as conflicting. However, one data channel with a lower priority task may still override a higher priority task because the commandDirector for that channel was called later. If needed, fix this later.
	
	//NAVI SW Reset Request
	if (commandTag == CMD_TAG_NAVI_SW_RESET_REQUEST &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_NAVISWRESETREQUEST_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_NAVISWRESETREQUEST_))				
			)
		)	 
	{

		//Create first (and only) sleeping acknowledgment here. Since for NAVI/AUXI, it will only send out one acknowledgment then do a SW reset.
		main_pri_msg_queue = CMD_TAG_SW_IS_RESETTING_ACK;//Send status back to MAIN

		pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;
		
		
		//Set all LEDs to default/off, since it will be refreshed at RUN_HOUSEKEEPING_TASKS. (Note: The gimbal, motor, drive setting, and buffer will be set to default and controlled in the next state, CONTROL_OUTPUTS)
			
		universal_led_mode = LED_SET_ALL_DEFAULT;
		hazard_light_state = LED_SET_ALL_DEFAULT;
		fog_light_state = LED_SET_ALL_DEFAULT;
		underglow_light_state = LED_SET_ALL_DEFAULT;
		ir_beacon_state = LED_SET_ALL_DEFAULT;
		blue_beacon_state = LED_SET_ALL_DEFAULT;
		beacon_led_direction = LED_SET_ALL_DEFAULT;
		rover_motion = LED_SET_ALL_DEFAULT;
		rover_error_type = LED_SET_ALL_DEFAULT;

		currentMode = SW_RESETTING;//Set mode to SW_RESETTING *begin*
		//Note: The actual SW reset will happen after TX_COMMUNICATIONS where it goes into INITIALIZATION.
					
	}//end else if	
	//Received Generic Health Error
	else if (commandTag == CMD_TAG_GENERIC_HEALTH_STATUS_ERROR &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_))		
			)
		)		 	 
	{	
	
		//If the error goes away in AUXI, the system should come back to normal.
		//AUXI will keep sending NAVI a GENERIC_HEALTH_STATUS_ERROR as long as AUXI has a health error. As soon as this message is gone, everything should go back to normal. 
		//The next state should be PLAN_ROUTE as normal (though motors will turn off, it can still keep calculating)		
		//Turn off all LEDs and motors when there is a generic health error. But no need to put the system in error.		
		motor_turn_value = SET_GO_STRAIGHT;
		motor_speed_value = SET_STOP_SPEED;		
		gimbal_pan_value = SET_CENTER_PAN;
		gimbal_tilt_value = SET_MIDDLE_TILT;		
		
		BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_);//buffer_remote_ctrl_selected = false 
		
		drive_setting = AUTONOMOUS_DRIVE;//can be AUTONOMOUS_DRIVE, SEMI_AUTO_DRIVE, or MANUAL_DRIVE
		
		//Put LEDs to error pattern
		universal_led_mode = LED_SET_GENERIC_HEALTH_ERROR;
		rover_error_type = LED_SET_GENERIC_HEALTH_ERROR;
				
		//Create first message here and regenerate later on as needed
		pc_usb_msg_queue = CMD_TAG_GENERIC_HEALTH_STATUS_ERROR; //send error out through the PC_USB for debugging

		
		if( error_origin != ROVERCOMM_MAIN)//Make sure don't send it back to itself to avoid an infinite loop
		{
			 main_pri_msg_queue = CMD_TAG_GENERIC_HEALTH_STATUS_ERROR;//send a generic system error to main which will send a copy to cmnc as well (MAIN only accepts generic health and generic system errors at the moment. Also only generic health and generic system errors are usually left unfiltered in many states like SYNCHRONIZATION. else you have to send a message that should redirect to cmnc directly, but it would bypass MAIN and won't error MAIN out. Sometimes you want MAIN to error out on any error.)
			 
			 pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;
		}//end if			
	
		
		//set generic_health_error = true
		BooleanBitFlags::setFlagBit(flagSet_Error1, _BTFG_GENERIC_HEALTH_ERROR_);			
		//(Note: the generic_health_error flag can only be cleared with a sw reset or hw reset)		

		//Assign the error_origin to where the data was generated from
		if (originRoverCommType == ROVERCOMM_CMNC)//If command was from CMNC
		{
			 error_origin = ROVERCOMM_CMNC;
		}//end else if		
		else if (originRoverCommType == ROVERCOMM_NAVI)//If command was from NAVI
		{
			error_origin = ROVERCOMM_NAVI;
		}//end if
		else if (originRoverCommType == ROVERCOMM_AUXI)//If command was from AUXI
		{
			error_origin = ROVERCOMM_AUXI;
		}//end else if		
		else if (originRoverCommType == ROVERCOMM_MAIN)//If command was from MAIN
		{
			error_origin = ROVERCOMM_MAIN;
		}//end else if
		else if (originRoverCommType == ROVERCOMM_COMM)//else if command was from COMM
		{
			error_origin = ROVERCOMM_COMM;
		}//end else if
		else if (originRoverCommType == ROVERCOMM_PC_USB)//else if command was from COMM
		{
			error_origin = ROVERCOMM_PC_USB;
		}//end else if
		else
		{
			error_origin = ROVERCOMM_NONE;
		}//end else
		
	}//end else if	
	//Received Generic System Error
	else if (commandTag == CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_))		
			)
		)		 	 
	{	
	
		//For now just forward it to MAIN (CMNC) and PC_USB (as well as other Arduinos), keeping the original destination. No need to go into SYSTEM_ERROR mode just yet. Only health errors need to go to SYSTEM_ERROR mode. Only health errors need to go to SYSTEM_ERROR mode. Though NAVI and AUXI might go to SYSTEM_ERROR mode.	
	
		//Create first message here and regenerate later on as needed
		
		pc_usb_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;
		
		if( error_origin != ROVERCOMM_MAIN)//Make sure don't send it back to itself to avoid an infinite loop
		{
			main_pri_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//send a generic system error to main which will send a copy to cmnc as well (MAIN only accepts generic health and generic system errors at the moment. Also only generic health and generic system errors are usually left unfiltered in many states like SYNCHRONIZATION. else you have to send a message that should redirect to cmnc directly, but it would bypass MAIN and won't error MAIN out. Sometimes you want MAIN to error out on any error.)
			
			pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;
			
		}//end if
				
		
		//set generic_system_error = true
		BooleanBitFlags::setFlagBit(flagSet_Error1, _BTFG_GENERIC_SYSTEM_ERROR_);
			//(Note: the generic_system_error flag can only be cleared with a sw reset or hw reset)
		
		//Assign the error_origin to where the data was generated from
		if (originRoverCommType == ROVERCOMM_CMNC)//If command was from CMNC
		{
			 error_origin = ROVERCOMM_CMNC;
		}//end else if		
		else if (originRoverCommType == ROVERCOMM_NAVI)//If command was from NAVI
		{
			error_origin = ROVERCOMM_NAVI;
		}//end if
		else if (originRoverCommType == ROVERCOMM_AUXI)//If command was from AUXI
		{
			error_origin = ROVERCOMM_AUXI;
		}//end else if		
		else if (originRoverCommType == ROVERCOMM_MAIN)//If command was from MAIN
		{
			error_origin = ROVERCOMM_MAIN;
		}//end else if
		else if (originRoverCommType == ROVERCOMM_COMM)//else if command was from COMM
		{
			error_origin = ROVERCOMM_COMM;
		}//end else if
		else if (originRoverCommType == ROVERCOMM_PC_USB)//else if command was from PC_USB
		{
			error_origin = ROVERCOMM_PC_USB;
		}//end else if
		else
		{
			error_origin = ROVERCOMM_NONE;
		}//end else		
		
		
		//All errors from MAIN, NAVI, AUXI, COMM, CMNC, PC_USB should be redirected to MAIN, and MAIN will redirect it to CMNC
		//Then CMNC will talk to COMM where it can then allow hw and sw resets, etc.
		//Improvement Tip: NAVI can go into error mode if it gets an error message from MAIN, NAVI, AUXI, COMM, CMNC, PC_USB		
		
		
	}//end if	
	//System Go
	else if (commandTag == CMD_TAG_SYSTEM_GO_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMGO_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMGO_))		
			)
		)		 	 
	{	
	
		//set system go flag
		BooleanBitFlags::setFlagBit(flagSet_SystemStatus1, _BTFG_MAIN_SYSTEM_GO_);
		//Set mode to NORMAL_OPERATIONS *begin*
		currentMode = NORMAL_OPERATIONS;
		//initialize/reset shared counter before use
		timeout_counter = 0;
		
		
	}//end else if	
	//MAIN System Ready
	else if (commandTag == CMD_TAG_SYSTEM_READY_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_MAINSYSTEMREADY_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_MAINSYSTEMREADY_))		
			)
		)		 	 
	{	
		
		BooleanBitFlags::setFlagBit(flagSet_SystemStatus1, _BTFG_MAIN_SYSTEM_READY_);//main_system_ready = true
		//(so it can stop checking for this message since the MAIN system is known to be ready)
		
		//initialize/reset shared counter before use
		timeout_counter = 0;//for future use
		//NOTE: Since this is a non-conflicting command, if resetting the timeout_counter here causes an issue, then take that out of the code
		
	}//end else if	
	//NAVI Sleep Request
	else if (commandTag == CMD_TAG_NAVI_SLEEP_REQUEST &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_NAVISLEEPREQUEST_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_NAVISLEEPREQUEST_))		
			)
		)		 	 
	{	
	

		//save the motor, gimbal buffer states before shutting them off to go to sleep
		BooleanBitFlags::clearFlagBit(flagSet_SystemStatus1, _BTFG_MAIN_SYSTEM_GO_);
		
		prev_motor_turn_value = motor_turn_value;
		prev_motor_speed_value = motor_speed_value;
		prev_gimbal_pan_value = gimbal_pan_value;
		prev_gimbal_tilt_value = gimbal_tilt_value;
		prev_drive_setting = drive_setting;		
		//Save previous buffer remote control: prev_buffer_remote_ctrl_selected = buffer_remote_ctrl_selected
		if( BooleanBitFlags::flagIsSet(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_) )
		{
			BooleanBitFlags::setFlagBit(flagSet_SystemControls1, _BTFG_PREV_REMOTE_CTRL_SELECTED_);
		}//end if
		else
		{
			BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_PREV_REMOTE_CTRL_SELECTED_);
		}//end else
		
		motor_turn_value = SET_GO_STRAIGHT;
		motor_speed_value = SET_STOP_SPEED;
		gimbal_pan_value = SET_CENTER_PAN;
		gimbal_tilt_value = SET_MIDDLE_TILT;
		drive_setting = AUTONOMOUS_DRIVE;
		BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_);
				
				
		//Create first (and only) sleeping acknowledgment here. Since for NAVI/AUXI, it will only send out one acknowledgment then go to sleep.
		main_pri_msg_queue = CMD_TAG_SYSTEM_IS_SLEEPING_ACK;//Send status back to MAIN
		
		pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;
		currentMode = SYSTEM_SLEEPING;//Set mode to SYSTEM_SLEEPING *begin*	
		
	}//end else if
	//Get Drive Setting
	else if (commandTag == CMD_TAG_DRIVE_SETTING_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GETDRIVESETTING_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETDRIVESETTING_))		
			)
		)		 	 
	{	
		
		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			pc_usb_msg_queue = CMD_TAG_DRIVE_SETTING_STATUS;
		}//end else if		
		else if (
			originRoverCommType == ROVERCOMM_CMNC ||
			originRoverCommType == ROVERCOMM_COMM ||
			originRoverCommType == ROVERCOMM_MAIN ||
			originRoverCommType == ROVERCOMM_AUXI
		)//If command was from CMNC, COMM, MAIN, AUXI
		{
			main_pri_msg_queue = CMD_TAG_DRIVE_SETTING_STATUS;
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;
		}//end if
		//else do nothing
	
	}//end else if	
	//Set Drive Setting
	else if (commandTag == CMD_TAG_SET_DRIVE_SETTING &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SETDRIVESETTING_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SETDRIVESETTING_))		
			)
		)		 	 
	{	
	
		if(strcmp( commandData, getMsgString(3) ) == 0)//commandData == "semi"
		{
			drive_setting = SEMI_AUTO_DRIVE;		
		}//end if
		else if(strcmp( commandData, getMsgString(4) ) == 0)//commandData == "manu"
		{
			drive_setting = MANUAL_DRIVE;
		}//end else if
		else if(strcmp( commandData, getMsgString(5) ) == 0)////commandData == "auto"
		{
			drive_setting = AUTONOMOUS_DRIVE;
		}//end else if
		//else do nothing since invalid choice
		
	}//end else if		
	//Set Motor Power Status (received from MAIN)
	else if (commandTag == CMD_TAG_MTR_PWR_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORPOWERSTATUS_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORPOWERSTATUS_))		
			)
		)		 	 
	{	

		//Set or clear status flag for Motor Power Status, _BTFG_MTR_POWER_IS_ON_ depending on the data received from MAIN
		if(strcmp( commandData, getMsgString(6) ) == 0)//commandData == "on"
		{
			BooleanBitFlags::setFlagBit(flagSet_SystemControls1, _BTFG_MTR_POWER_IS_ON_);
		}//end if
		else if(strcmp( commandData, getMsgString(7) ) == 0)//commandData == "off"
		{
			BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_MTR_POWER_IS_ON_);
		}//end else if
		//else do nothing since invalid choice
		
	}//end else if		
	
	//Set Mid Right Encoder Status (Status Received from MAIN)
	else if (commandTag == CMD_TAG_ENC_STATUS_MID_RIGHT &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SETMIDRIGHTENCODERSTATUS_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SETMIDRIGHTENCODERSTATUS_))		
			)
		)		 	 
	{	
	
		RoverMessagePackager::unpackEncoderStatus(commandData, commandDataLength, allWheelEncodersDirection[WHEEL_ENC_MID_RIGHT], allWheelEncodersSpeed[WHEEL_ENC_MID_RIGHT], allWheelEncodersFootage[WHEEL_ENC_MID_RIGHT]);
		
	}//end else if				
	//Set Mid Left Encoder Status (Status Received from MAIN)
	else if (commandTag == CMD_TAG_ENC_STATUS_MID_LEFT &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SETMIDLEFTENCODERSTATUS_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SETMIDLEFTENCODERSTATUS_))		
			)
		)		 	 
	{	
	
		RoverMessagePackager::unpackEncoderStatus(commandData, commandDataLength, allWheelEncodersDirection[WHEEL_ENC_MID_LEFT], allWheelEncodersSpeed[WHEEL_ENC_MID_LEFT], allWheelEncodersFootage[WHEEL_ENC_MID_LEFT]);
		
	}//end else if				
	//Set Heading (Status Received from AUXI)
	else if (commandTag == CMD_TAG_SET_HEADING &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SETHEADING_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SETHEADING_))		
			)
		)		 	 
	{	
	
		CharArray::Trim(commandData);//trim any white spaces in the character array
				
		tempHeadingData = atof(commandData);//convert the character array to a double/float value
		
		//IMPROVEMENT TIP: This assumes only numbers were received. It may error if any characters are received. Currently there are no checks or error corrections. Can implement one later.
	
		if(tempHeadingData >= 0.0 && tempHeadingData <= 360.0)//checks to see if the heading value is within range
		{	
			BooleanBitFlags::setFlagBit(flagSet_SystemStatus1, _BTFG_HEADING_DATA_READY_);//set the valid data flag if the data is within range

			//Note: Then tempHeadingData will get processed further in PROCESS_DATA by processHeading() for any data with a valid data flag

		}//end if
		else
		{
			BooleanBitFlags::clearFlagBit(flagSet_SystemStatus1, _BTFG_HEADING_DATA_READY_);//else clear the valid data flag if the data is out of range
		}//end else
		
	}//end else if					

	//Run Motor Calibration
	else if (commandTag == CMD_TAG_CALIBRATE_MOTOR_CONTROLLER &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_RUNMOTORCALIBRATION_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_RUNMOTORCALIBRATION_))		
			)
		)		 	 
	{	
	
			//WARNING: Make sure to run motor calibration when the rover is lifted and the wheels are off the ground.
	
			//Note: When motor calibration is ran, it will reset the motor states, drive settings, as well as the LED states to default states.
			
			//Note: Since Run Motor Calibration is a special step, it won't wait for the CONTROL_OUTPUTS state. It will just do all of its work in this function, then return the rover to a default state. (in order to make the state machine easier to code)
			
			_SERIAL_DEBUG_CHANNEL_.println(F("Mtr Cal Start"));//Send start status message
			
			
			//LEDs - Set to default (directly - without going through variables like motor_turn_value, etc.) - Control the LEDS in real time (don't wait for the CONTROL_OUTPUTS state)	
			ledController_NAVI->setUniversalLEDMode(LED_ALL_OFF_MODE);
			ledController_NAVI->setHazardLightsMode(LED_HAZARDS_OFF);
			ledController_NAVI->setFogLightMode(LED_FOG_OFF);
			ledController_NAVI->setUnderglowLightMode(LED_UNDERGLOW_OFF);
			ledController_NAVI->setIRBeaconLightMode(LED_IR_BEACON_ALL_OFF);
			ledController_NAVI->setBlueBeaconLightMode(LED_BLUE_BEACON_ALL_OFF);
			ledController_NAVI->setBeaconDirection(LED_DIRECTION_NONE);
			ledController_NAVI->setRoverMotion(LED_MOTION_STANDARD);
			ledController_NAVI->setErrorType(LED_ERROR_TYPE_NONE);

			
			//Motors - Stop motors (directly - without going through variables like universal_led_mode, etc.) - Control the motors in real time (don't wait for the CONTROL_OUTPUTS state)
			motorControllerSetSteering(SET_GO_STRAIGHT);
			motorControllerSetThrottle(SET_STOP_SPEED);
			
			//Note: The previous _BTFG_REMOTE_CTRL_SELECTED_ (i.e. buffer_remote_ctrl_selected isn't saved for motor calibration. It will just be set to default when the motor calibration is done)
			
			//Rover Buffer - Set Rover buffer to auto drive (directly - without going through variables like drive_setting, _BTFG_REMOTE_CTRL_SELECTED_, etc.) - Control the rover buffer in real time (don't wait for the CONTROL_OUTPUTS, PLAN_ROUTE, or OBJECT_AVOIDANCE states).
			roverBuffer->driverMode(AUTO_DRIVE);
			//Note: The motor calibration only runs if the roverBuffer is in auto drive. See motorControllerPowerOnCalibration() in MotorController.cpp

			//Delay to allow rover to stop any motion/momentum
			delay(1000);//wait for 1 seconds
		
			//Run motor calibration
			//Run motor controller calibration
			motorControllerPowerOnCalibration(roverBuffer);//calibrate if buffer select is in auto mode, else do nothing (defined in MotorController.h - where MotorController.h/MotorController.cpp are not classes)
			
			//Delay to allow rover to stop any motion/momentum
			delay(500);//wait for 0.5 seconds
			
			//Once Motor Calibration is done, return the LEDs, motors, rover buffer, and drive settings to default again
			
			//LEDs - Set to default
			universal_led_mode = LED_SET_ALL_DEFAULT;
			hazard_light_state = LED_SET_ALL_DEFAULT;
			fog_light_state = LED_SET_ALL_DEFAULT;
			underglow_light_state = LED_SET_ALL_DEFAULT;
			ir_beacon_state = LED_SET_ALL_DEFAULT;
			blue_beacon_state = LED_SET_ALL_DEFAULT;
			beacon_led_direction = LED_SET_ALL_DEFAULT;
			rover_motion = LED_SET_ALL_DEFAULT;
			rover_error_type = LED_SET_ALL_DEFAULT;	
			//Motors - Set to default
			motor_turn_value = SET_GO_STRAIGHT;
			motor_speed_value = SET_STOP_SPEED;			
			//Rover Buffer - Set to Auto Drive - Clear the flag (default)
			BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_);
			//Drive Settings - to Autonomous Drive
			drive_setting = AUTONOMOUS_DRIVE;
			
			_SERIAL_DEBUG_CHANNEL_.println(F("Mtr Cal Cmpltd"));//Send completion status message
			
			//DEBUG TIP: Not sure what will happen since I am controlling all the outputs and adding delays in this function. Also I return motors, etc. to default. Not sure if that will break the state machine. Can debug it later if it's an issue because the assumptions are wrong.
		
		
	}//end else if				
	
	
	//Run Gimbal Demo
	else if (commandTag == CMD_TAG_RUN_GIMBAL_DEMO &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_RUNGIMBALDEMO_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_RUNGIMBALDEMO_))		
			)
		)		 	 
	{	
		//Note: When gimbal demo is ran, it will restore the gimbal states and rover buffer.

		//Note: Since Run Gimbal Calibration is a special step, it won't wait for the CONTROL_OUTPUTS state. It will just do all of its work in this function, then return the rover to a default state. (in order to make the state machine easier to code)		
		
		_SERIAL_DEBUG_CHANNEL_.println(F("Gimbal Demo Start"));//Send start status message
		
		
		//Save the previous gimbal values
		prev_gimbal_pan_value = gimbal_pan_value;
		prev_gimbal_tilt_value = gimbal_tilt_value;
		
		
		//Save previous buffer remote control: prev_buffer_remote_ctrl_selected = buffer_remote_ctrl_selected, so it can be restored after the Gimbal Demo
		if( BooleanBitFlags::flagIsSet(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_) )
		{
			BooleanBitFlags::setFlagBit(flagSet_SystemControls1, _BTFG_PREV_REMOTE_CTRL_SELECTED_);
		}//end if
		else
		{
			BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_PREV_REMOTE_CTRL_SELECTED_);
		}//end else

		//Now for this Gimbal Demo, set it to auto mode (buffer_remote_ctrl_selected = false)
		BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_);
		
		//Rover Buffer - Set Rover buffer to auto drive (directly - without going through variables like drive_setting, _BTFG_REMOTE_CTRL_SELECTED_, etc.) - Control the rover buffer in real time (don't wait for the CONTROL_OUTPUTS, PLAN_ROUTE, or OBJECT_AVOIDANCE states).
		roverBuffer->driverMode(AUTO_DRIVE);
			//Note: The gimbal demo only runs if the roverBuffer is in auto drive. See gimbalFunctionalDemo() in GimbalController.cpp		
		
		//Gimbals - Set to center and middle before running the demo. (directly - without going through variables like gimbal_pan_value, etc.) - Control the gimbal in real time (don't wait for the CONTROL_OUTPUTS state)
				
		//Control Gimbal Controller's Pan			
		gimbalSetPan(SET_CENTER_PAN);
		//Control Gimbal Controller's Tilt			
		gimbalSetTilt(SET_MIDDLE_TILT);
		
		//Delay to allow rover to stop any motion/momentum
		delay(1000);//wait for 1 seconds
		
		//Run Gimbal Demo
		gimbalFunctionalDemo(roverBuffer);
		//run gimbal demo if buffer select is in auto mode, else do nothing (defined in GimbalController.h - where GimbalController.h/GimbalController.cpp are not classes)
			
		//Delay to allow rover to stop any motion/momentum
		delay(500);//wait for 0.5 second
			
			
		//Once Gimbal Demo is done, return the rover buffer to it's previous state and return the 

		//Restore previous buffer remote control: buffer_remote_ctrl_selected = prev_buffer_remote_ctrl_selected
		if( BooleanBitFlags::flagIsSet(flagSet_SystemControls1, _BTFG_PREV_REMOTE_CTRL_SELECTED_) )
		{
			BooleanBitFlags::setFlagBit(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_);
			roverBuffer->driverMode(AUTO_DRIVE);
		}//end if
		else
		{
			BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_);
			roverBuffer->driverMode(MANUAL_DRIVE);
		}//end else
		
		//Restore the Gimbal Settings
		gimbal_pan_value = prev_gimbal_pan_value;
		gimbal_tilt_value = prev_gimbal_tilt_value;

		//Control Gimbal Controller's Pan to restore the previous position	
		gimbalSetPan(gimbal_pan_value);
		//Control Gimbal Controller's Tilt to restore the previous position		
		gimbalSetTilt(gimbal_tilt_value);
		

	}//end else if			
	//Set Gimbal Pan
	else if (commandTag == CMD_TAG_SET_PAN_VALUE &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet3_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SETGIMBALPAN_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet3_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SETGIMBALPAN_))		
			)
		)		 	 
	{	
	
		byte tempData;//holds the data temporarily until it can be verified
		
		CharArray::Trim(commandData);//trim any white spaces in the character array
		
		tempData = DataType::charsToByte(commandData);
		
		//Verify the data
		if(tempData >= 0 && tempData <= 180)//checks to see if the value is within range
		{	
			gimbal_pan_value = tempData;
		}//end if
		//else the data is invalid and rejected so do nothing
				
	}//end else if			
	//Get Gimbal Pan Status
	else if (commandTag == CMD_TAG_GIMBAL_PAN_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet3_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GETGIMBALPANSTATUS_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet3_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETGIMBALPANSTATUS_))		
			)
		)		 	 
	{	

		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			pc_usb_msg_queue = CMD_TAG_GIMBAL_PAN_STATUS;
		}//end else if		
		else if (
			originRoverCommType == ROVERCOMM_CMNC ||
			originRoverCommType == ROVERCOMM_COMM ||
			originRoverCommType == ROVERCOMM_MAIN ||
			originRoverCommType == ROVERCOMM_AUXI
		)//If command was from CMNC, COMM, MAIN, AUXI
		{
			main_pri_msg_queue = CMD_TAG_GIMBAL_PAN_STATUS;
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;
		}//end if
		//else do nothing
		
	}//end else if		
	//Set Gimbal Tilt
	else if (commandTag == CMD_TAG_SET_TILT_VALUE &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet3_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SETGIMBALTILT_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet3_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SETGIMBALTILT_))		
			)
		)		 	 
	{	
	
		byte tempData;//holds the data temporarily until it can be verified
		
		CharArray::Trim(commandData);//trim any white spaces in the character array
		
		tempData = DataType::charsToByte(commandData);
		
		//Verify the data
		if(tempData >= 0 && tempData <= 180)//checks to see if the value is within range
		{	
			gimbal_tilt_value = tempData;
		}//end if
		//else the data is invalid and rejected so do nothing
				
	}//end else if			
	//Get Gimbal Tilt Status
	else if (commandTag == CMD_TAG_GIMBAL_TILT_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet3_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GETGIMBALTILTSTATUS_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet3_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETGIMBALTILTSTATUS_))		
			)
		)		 	 
	{	
	
		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			pc_usb_msg_queue = CMD_TAG_GIMBAL_TILT_STATUS;
		}//end else if		
		else if (
			originRoverCommType == ROVERCOMM_CMNC ||
			originRoverCommType == ROVERCOMM_COMM ||
			originRoverCommType == ROVERCOMM_MAIN ||
			originRoverCommType == ROVERCOMM_AUXI
		)//If command was from CMNC, COMM, MAIN, AUXI
		{
			main_pri_msg_queue = CMD_TAG_GIMBAL_TILT_STATUS;
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;
		}//end if
		//else do nothing
				
	}//end else if			
	//Set Motor Speed
	else if (commandTag == CMD_TAG_SET_MOTOR_SPEED &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet3_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORSPEED_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet3_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORSPEED_))		
			)
		)		 	 
	{	
	
		byte tempData;//holds the data temporarily until it can be verified
		
		CharArray::Trim(commandData);//trim any white spaces in the character array
		
		tempData = DataType::charsToByte(commandData);
		
		//Verify the data
		if(tempData >= 0 && tempData <= 180)//checks to see if the value is within range
		{	
			motor_speed_value = tempData;
		}//end if
		//else the data is invalid and rejected so do nothing
				
	}//end else if				
	//Get Motor Speed Status
	else if (commandTag == CMD_TAG_MOTOR_SPEED_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet3_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GETMOTORSPEEDSTATUS_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet3_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETMOTORSPEEDSTATUS_))		
			)
		)		 	 
	{	
	
		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			pc_usb_msg_queue = CMD_TAG_MOTOR_SPEED_STATUS;
		}//end else if		
		else if (
			originRoverCommType == ROVERCOMM_CMNC ||
			originRoverCommType == ROVERCOMM_COMM ||
			originRoverCommType == ROVERCOMM_MAIN ||
			originRoverCommType == ROVERCOMM_AUXI
		)//If command was from CMNC, COMM, MAIN, AUXI
		{
			main_pri_msg_queue = CMD_TAG_MOTOR_SPEED_STATUS;
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;
		}//end if
		//else do nothing		
		
	}//end else if				
	//Set Motor Turn
	else if (commandTag == CMD_TAG_SET_MOTOR_TURN &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet3_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORTURN_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet3_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORTURN_))		
			)
		)		 	 
	{	
	
		byte tempData;//holds the data temporarily until it can be verified
		
		CharArray::Trim(commandData);//trim any white spaces in the character array
		
		tempData = DataType::charsToByte(commandData);
		
		//Verify the data
		if(tempData >= 0 && tempData <= 180)//checks to see if the value is within range
		{	
			motor_turn_value = tempData;
		}//end if
		//else the data is invalid and rejected so do nothing
		
		
	}//end else if		
	//Get Motor Turn Status
	else if (commandTag == CMD_TAG_MOTOR_TURN_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet3_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GETMOTORTURNSTATUS_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet3_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETMOTORTURNSTATUS_))		
			)
		)		 	 
	{	
	
		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			pc_usb_msg_queue = CMD_TAG_MOTOR_TURN_STATUS;
		}//end else if		
		else if (
			originRoverCommType == ROVERCOMM_CMNC ||
			originRoverCommType == ROVERCOMM_COMM ||
			originRoverCommType == ROVERCOMM_MAIN ||
			originRoverCommType == ROVERCOMM_AUXI
		)//If command was from CMNC, COMM, MAIN, AUXI
		{
			main_pri_msg_queue = CMD_TAG_MOTOR_TURN_STATUS;
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;
		}//end if
		//else do nothing
		
	}//end else if		
	/*
	IMPROVEMENT TIP
	Set Rover into LED Debug Mode
		In LED debug mode, the rover sets Universal LED Mode to Default,required before user can control LEDs discretely with userDiscreteLEDControl().
		It prevents the rover from overriding the LEDs until the debug mode is removed
		Allow the user to set on or off for any LEDs.
		But use packaged data in order to reduce the number of required commands.
		See "LED Names (for discrete control)" in RoverConfig.h
		Have a command for setting
			Beacon LED Set
			Headlight LED Set
			Taillights LED Set
			Underglow LED Set
			Side Signal Light LED Set
			Maybe the packaged commandData can be in the following format
			
		Reference NAVI State Machine_add_date_when_archive.txt
	*/
	//Get Latitude
	else if (commandTag == CMD_TAG_LATITUDE_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet5_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GETLATITUDE_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet5_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETLATITUDE_))		
			)
		)		 	 
	{	

		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			pc_usb_msg_queue = CMD_TAG_LATITUDE_STATUS;
		}//end else if		
		else if (
			originRoverCommType == ROVERCOMM_CMNC ||
			originRoverCommType == ROVERCOMM_COMM ||
			originRoverCommType == ROVERCOMM_MAIN ||
			originRoverCommType == ROVERCOMM_AUXI
		)//If command was from CMNC, COMM, MAIN, AUXI
		{
			main_pri_msg_queue = CMD_TAG_LATITUDE_STATUS;
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;
		}//end if
		//else do nothing
	
	}//end else if			
	//Get Longitude
	else if (commandTag == CMD_TAG_LONGITUDE_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet5_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GETLONGITUDE_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet5_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETLONGITUDE_))		
			)
		)		 	 
	{	
	
		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			pc_usb_msg_queue = CMD_TAG_LONGITUDE_STATUS;
		}//end else if		
		else if (
			originRoverCommType == ROVERCOMM_CMNC ||
			originRoverCommType == ROVERCOMM_COMM ||
			originRoverCommType == ROVERCOMM_MAIN ||
			originRoverCommType == ROVERCOMM_AUXI
		)//If command was from CMNC, COMM, MAIN, AUXI
		{
			main_pri_msg_queue = CMD_TAG_LONGITUDE_STATUS;
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;
		}//end if
		//else do nothing
		
	}//end else if		
	//Get GPS Fix Quality
	else if (commandTag == CMD_TAG_GPS_FIX_QUALITY_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet5_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GETGPSFIXQUALITY_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet5_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETGPSFIXQUALITY_))		
			)
		)		 	 
	{	
	
		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			pc_usb_msg_queue = CMD_TAG_GPS_FIX_QUALITY_STATUS;
		}//end else if		
		else if (
			originRoverCommType == ROVERCOMM_CMNC ||
			originRoverCommType == ROVERCOMM_COMM ||
			originRoverCommType == ROVERCOMM_MAIN ||
			originRoverCommType == ROVERCOMM_AUXI
		)//If command was from CMNC, COMM, MAIN, AUXI
		{
			main_pri_msg_queue = CMD_TAG_GPS_FIX_QUALITY_STATUS;
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;
		}//end if
		//else do nothing
		
	}//end else if			
	//Get GPS Satellites Tracked
	else if (commandTag == CMD_TAG_GPS_SATELLITES_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet5_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GETGPSSATELLITESTRACKED_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet5_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETGPSSATELLITESTRACKED_))		
			)
		)		 	 
	{	
	
	
		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			pc_usb_msg_queue = CMD_TAG_GPS_SATELLITES_STATUS;
		}//end else if		
		else if (
			originRoverCommType == ROVERCOMM_CMNC ||
			originRoverCommType == ROVERCOMM_COMM ||
			originRoverCommType == ROVERCOMM_MAIN ||
			originRoverCommType == ROVERCOMM_AUXI
		)//If command was from CMNC, COMM, MAIN, AUXI
		{
			main_pri_msg_queue = CMD_TAG_GPS_SATELLITES_STATUS;
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;
		}//end if
		//else do nothing
		
	}//end else if			
	//Set Latitude Destination
	else if (commandTag == CMD_TAG_SET_LATITUDE_DEST &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet5_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SETLATITUDEDESTINATION_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet5_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SETLATITUDEDESTINATION_))		
			)
		)		 	 
	{	
	
		byte tempData;//holds the data temporarily until it can be verified
		
		CharArray::Trim(commandData);//trim any white spaces in the character array
				
		tempData = atof(commandData);//convert the character array to a double/float value
		
		//IMPROVEMENT TIP: This assumes only numbers were received. It may error if any characters are received. Currently there are no checks or error corrections. Can implement one later.
	
		if(tempData >= -90.0 && tempData <= 90.0)//checks to see if the value is within range
		{	
			roverNavigation->setLatitudeDeg(tempData, TYPE_DESIRED);
		}//end if
		
	}//end else if			
	//Set Longitude Destination
	else if (commandTag == CMD_TAG_SET_LONGITUDE_DEST &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet5_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_SETLONGITUDEDESTINATION_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet5_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SETLONGITUDEDESTINATION_))		
			)
		)		 	 
	{	
		
		byte tempData;//holds the data temporarily until it can be verified
		
		CharArray::Trim(commandData);//trim any white spaces in the character array
				
		tempData = atof(commandData);//convert the character array to a double/float value
		
		//IMPROVEMENT TIP: This assumes only numbers were received. It may error if any characters are received. Currently there are no checks or error corrections. Can implement one later.
	
		if(tempData >= -180.0 && tempData <= 180.0)//checks to see if the value is within range
		{	
			roverNavigation->setLongitudeDeg(tempData, TYPE_DESIRED);
		}//end if
		
	}//end else if			
	//Get Ultrasonic Distance Forward Left
	else if (commandTag == CMD_TAG_ULTSNC_DISTANCE_FWD_LT_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet6_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCEFORWARDLEFT_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet6_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCEFORWARDLEFT_))		
			)
		)		 	 
	{	

		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			pc_usb_msg_queue = CMD_TAG_ULTSNC_DISTANCE_FWD_LT_STATUS;
		}//end else if		
		else if (
			originRoverCommType == ROVERCOMM_CMNC ||
			originRoverCommType == ROVERCOMM_COMM ||
			originRoverCommType == ROVERCOMM_MAIN ||
			originRoverCommType == ROVERCOMM_AUXI
		)//If command was from CMNC, COMM, MAIN, AUXI
		{
			main_pri_msg_queue = CMD_TAG_ULTSNC_DISTANCE_FWD_LT_STATUS;
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;
		}//end if
		//else do nothing
	
	
	}//end else if					
	//Get Ultrasonic Distance Forward Center
	else if (commandTag == CMD_TAG_ULTSNC_DISTANCE_FWD_CTR_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet6_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCEFORWARDCENTER_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet6_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCEFORWARDCENTER_))		
			)
		)		 	 
	{	
	

		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			pc_usb_msg_queue = CMD_TAG_ULTSNC_DISTANCE_FWD_CTR_STATUS;
		}//end else if		
		else if (
			originRoverCommType == ROVERCOMM_CMNC ||
			originRoverCommType == ROVERCOMM_COMM ||
			originRoverCommType == ROVERCOMM_MAIN ||
			originRoverCommType == ROVERCOMM_AUXI
		)//If command was from CMNC, COMM, MAIN, AUXI
		{
			main_pri_msg_queue = CMD_TAG_ULTSNC_DISTANCE_FWD_CTR_STATUS;
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;
		}//end if
		//else do nothing
	
	}//end else if						
	//Get Ultrasonic Distance Forward Right	
	else if (commandTag == CMD_TAG_ULTSNC_DISTANCE_FWD_RT_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet6_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCEFORWARDRIGHT_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet6_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCEFORWARDRIGHT_))		
			)
		)		 	 
	{	
	

		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			pc_usb_msg_queue = CMD_TAG_ULTSNC_DISTANCE_FWD_RT_STATUS;
		}//end else if		
		else if (
			originRoverCommType == ROVERCOMM_CMNC ||
			originRoverCommType == ROVERCOMM_COMM ||
			originRoverCommType == ROVERCOMM_MAIN ||
			originRoverCommType == ROVERCOMM_AUXI
		)//If command was from CMNC, COMM, MAIN, AUXI
		{
			main_pri_msg_queue = CMD_TAG_ULTSNC_DISTANCE_FWD_RT_STATUS;
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;
		}//end if
		//else do nothing	
	
		
	}//end else if		
	//Get Ultrasonic Distance Side Right
	else if (commandTag == CMD_TAG_ULTSNC_DISTANCE_SIDE_RT_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet6_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCESIDERIGHT_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet6_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCESIDERIGHT_))		
			)
		)		 	 
	{	
	
		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			pc_usb_msg_queue = CMD_TAG_ULTSNC_DISTANCE_SIDE_RT_STATUS;
		}//end else if		
		else if (
			originRoverCommType == ROVERCOMM_CMNC ||
			originRoverCommType == ROVERCOMM_COMM ||
			originRoverCommType == ROVERCOMM_MAIN ||
			originRoverCommType == ROVERCOMM_AUXI
		)//If command was from CMNC, COMM, MAIN, AUXI
		{
			main_pri_msg_queue = CMD_TAG_ULTSNC_DISTANCE_SIDE_RT_STATUS;
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;
		}//end if
		//else do nothing	
	
		
	}//end else if				
	//Get Ultrasonic Distance Side Left
	else if (commandTag == CMD_TAG_ULTSNC_DISTANCE_SIDE_LT_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet6_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCESIDELEFT_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet6_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCESIDELEFT_))		
			)
		)		 	 
	{	
	
		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			pc_usb_msg_queue = CMD_TAG_ULTSNC_DISTANCE_SIDE_LT_STATUS;
		}//end else if		
		else if (
			originRoverCommType == ROVERCOMM_CMNC ||
			originRoverCommType == ROVERCOMM_COMM ||
			originRoverCommType == ROVERCOMM_MAIN ||
			originRoverCommType == ROVERCOMM_AUXI
		)//If command was from CMNC, COMM, MAIN, AUXI
		{
			main_pri_msg_queue = CMD_TAG_ULTSNC_DISTANCE_SIDE_LT_STATUS;
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;
		}//end if
		//else do nothing	
		
	}//end else if		
	//Get Ultrasonic Distance Rear Center
	else if (commandTag == CMD_TAG_ULTSNC_DISTANCE_REAR_CTR_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet6_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCEREARCENTER_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet6_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCEREARCENTER_))		
			)
		)		 	 
	{	
	

		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			pc_usb_msg_queue = CMD_TAG_ULTSNC_DISTANCE_REAR_CTR_STATUS;
		}//end else if		
		else if (
			originRoverCommType == ROVERCOMM_CMNC ||
			originRoverCommType == ROVERCOMM_COMM ||
			originRoverCommType == ROVERCOMM_MAIN ||
			originRoverCommType == ROVERCOMM_AUXI
		)//If command was from CMNC, COMM, MAIN, AUXI
		{
			main_pri_msg_queue = CMD_TAG_ULTSNC_DISTANCE_REAR_CTR_STATUS;
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;
		}//end if
		//else do nothing	
		
	}//end else if		
	//Get IR Distance Forward Center Status
	else if (commandTag == CMD_TAG_IR_DISTANCE_FWD_CTR_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet7_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GETIRDISTANCEFORWARDCENTERSTATUS_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet7_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETIRDISTANCEFORWARDCENTERSTATUS_))		
			)
		)		 	 
	{	
	
		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			pc_usb_msg_queue = CMD_TAG_IR_DISTANCE_FWD_CTR_STATUS;
		}//end else if		
		else if (
			originRoverCommType == ROVERCOMM_CMNC ||
			originRoverCommType == ROVERCOMM_COMM ||
			originRoverCommType == ROVERCOMM_MAIN ||
			originRoverCommType == ROVERCOMM_AUXI
		)//If command was from CMNC, COMM, MAIN, AUXI
		{
			main_pri_msg_queue = CMD_TAG_IR_DISTANCE_FWD_CTR_STATUS;
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;
		}//end if
		//else do nothing	
		
	}//end else if		
	//Get IR Distance Side Right Status
	else if (commandTag == CMD_TAG_IR_DISTANCE_SIDE_RT_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet7_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GETIRDISTANCESIDERIGHTSTATUS_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet7_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETIRDISTANCESIDERIGHTSTATUS_))		
			)
		)		 	 
	{	
	
		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			pc_usb_msg_queue = CMD_TAG_IR_DISTANCE_SIDE_RT_STATUS;
		}//end else if		
		else if (
			originRoverCommType == ROVERCOMM_CMNC ||
			originRoverCommType == ROVERCOMM_COMM ||
			originRoverCommType == ROVERCOMM_MAIN ||
			originRoverCommType == ROVERCOMM_AUXI
		)//If command was from CMNC, COMM, MAIN, AUXI
		{
			main_pri_msg_queue = CMD_TAG_IR_DISTANCE_SIDE_RT_STATUS;
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;
		}//end if
		//else do nothing		
		
	}//end else if		
	//Get IR Distance Side Left Status
	else if (commandTag == CMD_TAG_IR_DISTANCE_SIDE_LT_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet7_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GETIRDISTANCESIDELEFTSTATUS_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet7_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETIRDISTANCESIDELEFTSTATUS_))		
			)
		)		 	 
	{	
	
		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			pc_usb_msg_queue = CMD_TAG_IR_DISTANCE_SIDE_LT_STATUS;
		}//end else if		
		else if (
			originRoverCommType == ROVERCOMM_CMNC ||
			originRoverCommType == ROVERCOMM_COMM ||
			originRoverCommType == ROVERCOMM_MAIN ||
			originRoverCommType == ROVERCOMM_AUXI
		)//If command was from CMNC, COMM, MAIN, AUXI
		{
			main_pri_msg_queue = CMD_TAG_IR_DISTANCE_SIDE_LT_STATUS;
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;
		}//end if
		//else do nothing
		
	}//end else if		
	//Get IR Distance Rear Center Status
	else if (commandTag == CMD_TAG_IR_DISTANCE_REAR_CTR_STATUS &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet7_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_GETIRDISTANCEREARCENTERSTATUS_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet7_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETIRDISTANCEREARCENTERSTATUS_))		
			)
		)		 	 
	{	
	
		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			pc_usb_msg_queue = CMD_TAG_IR_DISTANCE_REAR_CTR_STATUS;
		}//end else if		
		else if (
			originRoverCommType == ROVERCOMM_CMNC ||
			originRoverCommType == ROVERCOMM_COMM ||
			originRoverCommType == ROVERCOMM_MAIN ||
			originRoverCommType == ROVERCOMM_AUXI
		)//If command was from CMNC, COMM, MAIN, AUXI
		{
			main_pri_msg_queue = CMD_TAG_IR_DISTANCE_REAR_CTR_STATUS;
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;
		}//end if
		//else do nothing
		
		
	}//end else if
	 //Hi Command - DEBUG
	else if (commandTag == CMD_TAG_DEBUG_HI_TEST_MSG &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet7_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_HI_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet7_MAIN, _BTFG_COMMAND_ENABLE_OPTION_HI_))		
			)
		)		 	 
	{

		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			 pc_usb_msg_queue = CMD_TAG_DEBUG_HI_TEST_MSG;
		}//end else if				
		else if ( originRoverCommType == ROVERCOMM_COMM || originRoverCommType == ROVERCOMM_CMNC || originRoverCommType == ROVERCOMM_MAIN || originRoverCommType == ROVERCOMM_AUXI )//If command was from COMM, CMNC, MAIN, or AUXI
		{
			main_pri_msg_queue = CMD_TAG_DEBUG_HI_TEST_MSG;//to be sent back to the origin (i.e. CMNC, COMM, MAIN, or AUXI)
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;//set whatever the origin is, to the destination selection
		}//end if		
		//else do nothing	
	}//end if
	 //Bye Command - DEBUG
	else if (commandTag == CMD_TAG_DEBUG_BYE_TEST_MSG &&
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet7_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_BYE_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet7_MAIN, _BTFG_COMMAND_ENABLE_OPTION_BYE_))		
			)
		)		 	 
	{

		//Check to see where the command was from
		if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
		{
			 pc_usb_msg_queue = CMD_TAG_DEBUG_BYE_TEST_MSG;
		}//end else if				
		else if ( originRoverCommType == ROVERCOMM_COMM || originRoverCommType == ROVERCOMM_CMNC || originRoverCommType == ROVERCOMM_MAIN || originRoverCommType == ROVERCOMM_AUXI )//If command was from COMM, CMNC, MAIN, or AUXI
		{
			main_pri_msg_queue = CMD_TAG_DEBUG_BYE_TEST_MSG;//to be sent back to the origin (i.e. CMNC, COMM, MAIN, or AUXI)
			pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;//set whatever the origin is, to the destination selection
		}//end if		
		//else do nothing	
	
	}//end if
	 //Invalid - DEBUG
	else if (
			(
				(roverComm == ROVERCOMM_PC_USB && BooleanBitFlags::flagIsSet(commandFilterOptionsSet7_PC_USB, _BTFG_COMMAND_ENABLE_OPTION_INVALID_) )
				|| (roverComm == ROVERCOMM_MAIN && BooleanBitFlags::flagIsSet(commandFilterOptionsSet7_MAIN, _BTFG_COMMAND_ENABLE_OPTION_INVALID_))		
			)	
		)
	{
	
			//Check to see where the command was from
			if (originRoverCommType == ROVERCOMM_PC_USB)//If command was from PC_USB
			{
				 pc_usb_msg_queue = CMD_TAG_INVALID_CMD;
			}//end else if				
			else if ( originRoverCommType == ROVERCOMM_COMM || originRoverCommType == ROVERCOMM_CMNC || originRoverCommType == ROVERCOMM_MAIN || originRoverCommType == ROVERCOMM_AUXI )//If command was from COMM, CMNC, MAIN, or AUXI
			{
				main_pri_msg_queue = CMD_TAG_INVALID_CMD;//to be sent back to the origin (i.e. CMNC, COMM, MAIN, or AUXI)
				pri_comm_cmnc_main_auxi_destination_selection = originRoverCommType;//set whatever the origin is, to the destination selection
			}//end if		
			//else do nothing	
	
	}//end else if
	 //else output nothing	

	return;

}//end of commandDirector()
void createDataFromQueueFor(byte roverCommType, byte queueSelection)
{


	//Note: createDataFromQueueFor() is only used to create outgoing messages. So it isn't used for internal processing since internally it doesn't need to send a message to itself.

	
	//Note:
	//queueSelection is only used for AUXI and NAVI since they are "leaves" at the end of the network "tree"
	//The queueSelection is as defined in RoverConfig.h under:
	//	_ROVER_SHARED_QUEUE_DEFINITIONS
	//i.e.
	//	PC_USB_MSG_QUEUE
	//	PRIMARY_MSG_QUEUE
	//	SECONDARY_MSG_QUEUE
	


	//Note: The origin of the message will change every time it passes through an Arduino (i.e. using the RoverCommandProcessor::createCmd() with a Rover Comm Type passed to it). It shows the last originating Arduino that handled the data. If the true origin is required, that should be placed in the command data where it's not altered.

	byte queueOfInterest;
	char * commandDataOfInterest;//holds the rover's command data string
	char createdCommand[ROVER_COMM_SENTENCE_LENGTH];//created command string (char array) (createdCommand is the output of the method call RoverCommandCreator::createCmd)
					
	//Create variables needed for the data packaging (i.e. encoder status)
	char commandDataCharArray[_MAX_ROVER_COMMAND_DATA_LEN_];//used with the RoverMessagePackager
	byte commandDataCharArraySize;//used with the RoverMessagePackager
	byte roverCommActualDestination;//holds the actual/final destination of the data
				
	//Note: The queueSelection is which data queue/variable is being used to store the data. Where as the roverCommActualDestination is a value that is encoded in the data itself and sent out as a string. The queueSelection is used to allow this Arduino to send multiple different messages by storing different messages in different queues.
				
	//Based on the roverCommType of interest, set which queue and rover data the outgoing message should be based on
	if (roverCommType == ROVERCOMM_PC_USB)
	{
		if(queueSelection == PC_USB_MSG_QUEUE)
		//Note: In theory it can just default to this, but since the code should be easily legible, go ahead and detect for a queueSelection of PC_USB_MSG_QUEUE.		
		{
			queueOfInterest = pc_usb_msg_queue;
		}//end if
		else//invalid state, error out (since for PC_USB it should only go to the pc_usb_msg_queue)
		{
			_SERIAL_DEBUG_CHANNEL_.println(F("ErrUnkQueueSel"));//error, unknown Queue Selection
		}//end else	
		
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
	else if ( roverCommType == ROVERCOMM_COMM || roverCommType == ROVERCOMM_CMNC || roverCommType == ROVERCOMM_MAIN || roverCommType == ROVERCOMM_AUXI )
	{
		
		if(queueSelection == PRIMARY_MSG_QUEUE)
		{
			queueOfInterest = main_pri_msg_queue;
			roverCommActualDestination = pri_comm_cmnc_main_auxi_destination_selection;
		}//end if
		else if (queueSelection == SECONDARY_MSG_QUEUE)
		{
			queueOfInterest = main_sec_msg_queue;
			roverCommActualDestination = sec_comm_cmnc_main_auxi_destination_selection;
		}//end else if
		else//invalid state, error out
		{
			_SERIAL_DEBUG_CHANNEL_.println(F("ErrUnkQueueSel"));//error, unknown Queue Selection
		}//end else
				
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

		/*
			Note:
			First start with all the commands from commandDirector().
				It should probably go under the "Externally Received Commands" category.
			But since these commands don't always mirror commandDirector() received commands, delete the ones that don't make sense.
				For example. sometimes they are acknowledgments instead of requests/commands. So go through all the outgoing queues and make sure you get the right name.
			i.e. use "CMD_TAG_SW_IS_RESETTING_ACK" instead of "CMD_TAG_NAVI_SW_RESET_REQUEST" for createDataFromQueueFor() for the NAVI Arduino.
			
			Then go through and search for assignments to these variables to see if there are any other commands:
				pc_usb_msg_queue, main_pri_msg_queue, main_sec_msg_queue
			as well as all the options for autoData. i.e. auto_NAVI_to_COMM_data_array, etc.
			They should probably go under "Internally Generated Commands - Internally Generated by this Arduino. So there are no received command for these types of commands."
				
		*/
		
		//Externally Received Commands	
//LEFT OFF HERE
		case CMD_TAG_SW_IS_RESETTING_ACK:
//WRITE ME LATER		
			break;
		case CMD_TAG_GENERIC_HEALTH_STATUS_ERROR:
//WRITE ME LATER		
			break;	
		case CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS:
//WRITE ME LATER		
			break;	
		case CMD_TAG_SYSTEM_IS_SLEEPING_ACK:
//WRITE ME LATER		
			break;	
		case CMD_TAG_DRIVE_SETTING_STATUS:
//WRITE ME LATER
			break;	
		case CMD_TAG_SET_DRIVE_SETTING:
//WRITE ME LATER		
			break;	
		case CMD_TAG_MTR_PWR_STATUS:
//WRITE ME LATER		
			break;	
		case CMD_TAG_ENC_STATUS_MID_RIGHT:
//WRITE ME LATER		
			break;	
		case CMD_TAG_ENC_STATUS_MID_LEFT:
//WRITE ME LATER		
			break;	
		case CMD_TAG_GIMBAL_PAN_STATUS:
//WRITE ME LATER		
			break;	
		case CMD_TAG_GIMBAL_TILT_STATUS:
//WRITE ME LATER		
			break;	
		case CMD_TAG_MOTOR_SPEED_STATUS:
//WRITE ME LATER		
			break;	
		case CMD_TAG_MOTOR_TURN_STATUS:
//WRITE ME LATER		
			break;	
		case CMD_TAG_LATITUDE_STATUS:
//WRITE ME LATER		
			break;	
		case CMD_TAG_LONGITUDE_STATUS:
//WRITE ME LATER		
			break;	
		case CMD_TAG_GPS_FIX_QUALITY_STATUS:
//WRITE ME LATER		
			break;	
		case CMD_TAG_GPS_SATELLITES_STATUS:
//WRITE ME LATER		
			break;	
		case CMD_TAG_ULTSNC_DISTANCE_FWD_LT_STATUS:
//WRITE ME LATER		
			break;	
		case CMD_TAG_ULTSNC_DISTANCE_FWD_CTR_STATUS:
//WRITE ME LATER		
			break;	
		case CMD_TAG_ULTSNC_DISTANCE_FWD_RT_STATUS:
//WRITE ME LATER		
			break;	
		case CMD_TAG_ULTSNC_DISTANCE_SIDE_RT_STATUS:
//WRITE ME LATER		
			break;	
		case CMD_TAG_ULTSNC_DISTANCE_SIDE_LT_STATUS:
//WRITE ME LATER		
			break;	
		case CMD_TAG_ULTSNC_DISTANCE_REAR_CTR_STATUS:
//WRITE ME LATER		
			break;	
		case CMD_TAG_IR_DISTANCE_FWD_CTR_STATUS:
//WRITE ME LATER		
			break;	
		case CMD_TAG_IR_DISTANCE_SIDE_RT_STATUS:
//WRITE ME LATER		
			break;	
		case CMD_TAG_IR_DISTANCE_SIDE_LT_STATUS:
//WRITE ME LATER		
			break;	
		case CMD_TAG_IR_DISTANCE_REAR_CTR_STATUS:
//WRITE ME LATER		
			break;
		case CMD_TAG_DEBUG_HI_TEST_MSG:
				RoverCommandCreator::createCmd(ROVERCOMM_NAVI, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_DEBUG_HI_TEST_MSG, commandDataOfInterest, createdCommand);
			break;
		case CMD_TAG_DEBUG_BYE_TEST_MSG:
				RoverCommandCreator::createCmd(ROVERCOMM_NAVI, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_DEBUG_BYE_TEST_MSG, commandDataOfInterest, createdCommand);
			break;
		case CMD_TAG_INVALID_CMD:
				RoverCommandCreator::createCmd(ROVERCOMM_NAVI, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_INVALID_CMD, getMsgString(0), createdCommand);
			break;			
		//Internally Generated Commands - Internally Generated by this Arduino. So there are no received command for these types of commands.
		case CMD_TAG_INVALID_STATE_OR_MODE_ERROR_STATUS: //The error message will be redirected out through all the Arduinos and out to CMNC
				//Only allow destination of ROVERCOMM_PC_USB (to go to PC_USB) and ROVERCOMM_CMNC (to go to CMNC, through MAIN, then COMM)
				if(roverCommActualDestination == ROVERCOMM_PC_USB || roverCommActualDestination == ROVERCOMM_CMNC)
				{
					RoverCommandCreator::createCmd(error_origin, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_INVALID_STATE_OR_MODE_ERROR_STATUS, getMsgString(2), createdCommand);
				}//end if				
				//else do nothing. CMD_TAG_INVALID_STATE_OR_MODE_ERROR_STATUS should not be sent to other Arduino channels other than ROVERCOMM_PC_USB and ROVERCOMM_CMNC (through MAIN, then COMM) as other Arduinos are not currently programmed to handle that type of message.
			break;
		case CMD_TAG_SYNC_ERROR_STATUS:
			//WRITE ME LATER		
			break;
		case CMD_TAG_SLEEP_ERROR_STATUS:
			//WRITE ME LATER		
			break;			
		case CMD_TAG_SW_RESET_ERROR_STATUS:
			//WRiTE ME LATER
			break;				
		default:
				RoverCommandCreator::createCmd(ROVERCOMM_NAVI, roverCommActualDestination, CMD_PRI_LVL_0, CMD_TAG_INVALID_CMD, getMsgString(1), createdCommand);//output invalid command
			break;
	}//end switch	
	
		
	
	
	if (roverCommActualDestination == ROVERCOMM_PC_USB)
	{
		sprintf(txMsgBuffer_PC_USB, createdCommand);
	}//end if
	else if ( roverCommActualDestination == ROVERCOMM_COMM || roverCommActualDestination == ROVERCOMM_CMNC || roverCommActualDestination == ROVERCOMM_MAIN || roverCommActualDestination == ROVERCOMM_AUXI )
	{
		if(queueSelection == PRIMARY_MSG_QUEUE)
		{
			sprintf(txMsgBuffer_Pri_MAIN, createdCommand);
		}//end if
		else if (queueSelection == SECONDARY_MSG_QUEUE)
		{
			sprintf(txMsgBuffer_Sec_MAIN, createdCommand);
		}//end else if
		else//invalid state, error out
		{
			_SERIAL_DEBUG_CHANNEL_.println(F("ErrUnkQueueSel"));//error, unknown Queue Selection
		}//end else		
	}//end else if	
	 //else

	 
	 pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;//once done with creating the data, reset the pri_comm_cmnc_main_auxi_destination_selection variable to default
	 sec_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;//once done with creating the data, reset the sec_comm_cmnc_main_auxi_destination_selection variable to default
	 
	return;

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
	//WRITE ME LATER
}//end of setAllCommands()

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
		case PLAN_ROUTE: //Mode: POWER_ON_AND_HW_RESET
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;			
		case OBJECT_AVOIDANCE: //Mode: POWER_ON_AND_HW_RESET
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
			runBackgroundTasks();
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
		case PLAN_ROUTE: //Mode: INITIALIZATION
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;			
		case OBJECT_AVOIDANCE: //Mode: INITIALIZATION
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

			//rxData() from MAIN
			//1. Reset status flag
			ch2Status = DATA_STATUS_NOT_READY;
			//2. Clear all Rx'ed data before getting new data				
			roverComm_Ch2->clearRxData();
			//3. Receive data
			ch2Status = rxData(roverComm_Ch2, ROVERCOMM_MAIN);//Note: this is a local .ino function
						
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
		case DATA_FILTER: //Mode: SYNCHRONIZATION

			//Reset/clear flags (no data was for NAVI)
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_NAVI_CH1_);
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_NAVI_CH2_);
			
				
			//Set Command Filter Options
			//First initialize all command choices to false
			setAllCommandFiltersTo(false, ROVERCOMM_PC_USB);//for PC_USB
			setAllCommandFiltersTo(false, ROVERCOMM_MAIN);//for MAIN
			
			//Then enable the allowed commands for this mode:
			//For PC_USB
			//No filter on PC_USB data. (Allow all data from PC_USB)
			//No commands from PC_USB are filtered, so set all to true.
			setAllCommandFiltersTo(true, ROVERCOMM_PC_USB);			
			//For MAIN
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_NAVISWRESETREQUEST_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_MAINSYSTEMREADY_);				
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SYSTEMGO_);	
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_);
			
	
			
			//Transmit data and/or execute command
						
			//For data from PC_USB, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, NAVI
			if (ch1Status == DATA_STATUS_VALID)
			{
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//Note: There are no redirections for the NAVI Arduino since it is a node at the end of the network tree.
				//Note: this is a local .ino function

				dataDirector(roverDataCh1_COMM, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_NAVI_CH1_);//DataDirection will set the "data was for NAVI flag" to true if it was for this Arduino

				/*
				Allow all data from PC_USB.
				*/

			}//end if

			//For data from MAIN, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, NAVI
			if (ch2Status == DATA_STATUS_VALID)
			{
			
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//Note: There are no redirections for the NAVI Arduino since it is a node at the end of the network tree.
				//Note: this is a local .ino function

				dataDirector(roverDataCh2_COMM, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_NAVI_CH2_);//DataDirection will set the "data was for NAVI flag" to true if it was for this Arduino
				
				/*
				Set filter to throw away all MAIN data except:

				*/				

			}//end if		
		
			break;	
		case READ_INPUTS: //Mode: SYNCHRONIZATION
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case PROCESS_DATA: //Mode: SYNCHRONIZATION

			#ifdef _DEBUG_PRINT_TIMEOUT_COUNTER_VALUE_
				Serial.println(timeout_counter);//DEBUG
			#endif
			
			
			//Run lower priority functions here.
			//These messages and flags may be overrided with commandDirector()			

			
			//If System Go (from MAIN to NAVI) was not received (Note: Messages received could still have been sys ready or no message at all)
			if( ! BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_MAIN_SYSTEM_GO_))
			{
			
				//Note: You still want to send a system ready, even if you received a system ready, since when MAIN sends a system ready, it has nothing to do with received a system ready from this Arduino.
				
				#ifndef _DEBUG_TURN_OFF_SYSTEM_READY_STATUS //normally the main_pri_msg_queue will send the CMD_TAG_SYSTEM_READY_STATUS. Can disable it for debugging purposes.
					main_pri_msg_queue = CMD_TAG_SYSTEM_READY_STATUS;//to be sent to MAIN, tells MAIN it's ready to synchronize, it should be normally on. only turn off when in debugging to reduce clutter
					
					pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;
					
					//Note: If system go or system ready msg has been received from MAIN, see the commandDirector for more info.
		
				#endif
				//If no system go msg from MAIN received && main_system_ready == false (MAIN system not ready yet to set the main_system_ready flag and have not received a system go to switch states yet, then keep incrementing the timeout counter)
				if( ! BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_MAIN_SYSTEM_READY_))
				{
					timeout_counter++;
					#ifndef _DEBUG_DISABLE_NAVI_SYNC_TIMEOUT //normally the timeout code would run. Can disable it for debugging purposes.
						if(timeout_counter >= NAVI_SYNC_TIMEOUT_VALUE)
						{
							currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*
							//PROCESS_DATA has a next state of CONTROL_OUTPUTS already. So no need to set the next queuedState to CONTROL_OUTPUTS						
														
							//Set motor controller signals to stop and center
							motor_turn_value = SET_GO_STRAIGHT;
							motor_speed_value = SET_STOP_SPEED;

							//Set gimbal controller middle and center
							gimbal_pan_value = SET_CENTER_PAN;
							gimbal_tilt_value = SET_MIDDLE_TILT;

							//Set buffer select to remote control selected = false so the rover is in control of the emergency stop (but the SYSTEM_ERROR state will allow commands to overrride this if desired, and set it to manual)
							BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_);//buffer_remote_ctrl_selected = false 
											
							drive_setting = AUTONOMOUS_DRIVE;//since it's at SYSTEM_ERROR and the rover should have control
							
							error_origin = ROVERCOMM_NAVI;
							main_pri_msg_queue == CMD_TAG_SYNC_ERROR_STATUS;
							pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;
							//set sync_error = true
							BooleanBitFlags::setFlagBit(flagSet_Error1, _BTFG_SYNC_ERROR_);			
							//(Note: the sync_error flag can only be cleared with a sw reset or hw reset)
							//initialize/reset shared counter before use
							timeout_counter = 0;	
						}//end if	
					#endif
				}//end if
			}//end if					
			
			
			
			

			//Process PC_USB command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//All other messages are allowed from PC_USB. Use with caution.
				//Note: There are no redirections for the NAVI Arduino since it is a node at the end of the network tree.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_NAVI_CH1_))//If there was data from PC_USB (Ch1), and it was for NAVI
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh1_COMM, ROVERCOMM_PC_USB);
			}//end if			
			//Process MAIN command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				
				//Note: Either you should get no data, system ready messages, system go messages, navi sw reset requests, generic health errors, generic system errors. as everything else was filtered out.
				//Note: There are no redirections for the NAVI Arduino since it is a node at the end of the network tree.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_NAVI_CH2_))//If there was data from MAIN (Ch2), and it was for NAVI
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh2_COMM, ROVERCOMM_MAIN);
			}//end if				

			
			//Skip Ultrasonic Distance Sensors
			//Skip IR Distance Sensors
			//Skip Heading (for AUXI-external)			
			//Skip Motor power status (for MAIN-external)
			//Skip Wheel Encoders (for MAIN-external and for NAVI-internal)
			//Skip GPS
							
			//Run highest priority functions here (after command director). //this will override any lower priority messages (i.e. system go). This will overwrite anything else. (i.e. system ready)
	
			break;
		case PLAN_ROUTE: //Mode: SYNCHRONIZATION
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;			
		case OBJECT_AVOIDANCE: //Mode: SYNCHRONIZATION
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;					
		case CONTROL_OUTPUTS: //Mode: SYNCHRONIZATION
		
			//Since Navigation is skipped for SYNCHRONIZATION, set default values for motors and gimbal here at the CONTROL_OUTPUTS state

	
			//Set motor and gimbal to default values
			motor_turn_value = SET_GO_STRAIGHT;
			motor_speed_value = SET_STOP_SPEED;
			gimbal_pan_value = SET_CENTER_PAN;
			gimbal_tilt_value = SET_MIDDLE_TILT;
			
			//turn buffer select to non-remote (local) control
			BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_);//buffer_remote_ctrl_selected = false 
			
			drive_setting = AUTONOMOUS_DRIVE;//since it's at SYNCHRONIZATION and the rover should have control				
				
			
			
			

			//Control Buffer Select
			//if buffer_remote_ctrl_selected == true
			if( BooleanBitFlags::flagIsSet(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_))
			{
				#ifdef _DEBUG_OUTPUT_DRIVE_SELECTION_STATUS
					_SERIAL_DEBUG_CHANNEL_.println(F("MANUAL DRIVE"));
				#endif
				roverBuffer->driverMode(MANUAL_DRIVE);
			}//end if
			//buffer_remote_ctrl_selected == false
			else
			{
				#ifdef _DEBUG_OUTPUT_DRIVE_SELECTION_STATUS
					_SERIAL_DEBUG_CHANNEL_.println(F("AUTO DRIVE"));
				#endif
				roverBuffer->driverMode(AUTO_DRIVE);
				
				//When in auto drive, control the motors and the gimbal
				
				//Control Motor Controller's Turn			
				motorControllerSetSteering(motor_turn_value);//Should be motor_turn_value = SET_GO_STRAIGHT

				//Control Motor Controller's Speed			
				motorControllerSetThrottle(motor_speed_value);//Should be motor_speed_value = SET_STOP_SPEED			

				//Control Gimbal Controller's Pan			
				gimbalSetPan(gimbal_pan_value);//Should be gimbal_pan_value = SET_CENTER_PAN

				//Control Gimbal Controller's Tilt			
				gimbalSetTilt(gimbal_tilt_value);//Should be gimbal_tilt_value = SET_MIDDLE_TILT

			
			}//end else

				
			//LEDs will be controlled by RUN_HOUSEKEEPING_TASKS (i.e. runBackgroundTasks()) since it requires attention with every loop
			
			//The Ultrasonic's trigger will be controlled when the sensor is read, since the trigger is part of the reading process						
	
			break;
		case CREATE_DATA: //Mode: SYNCHRONIZATION

			//Creates data for PC_USB
			if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_PC_USB, PC_USB_MSG_QUEUE);
				
				//skip auto data	
				
			}//end if
			
			
			//Creates data for MAIN (primary queue)
			if (main_pri_msg_queue != CMD_TAG_NO_MSG)
			{
			
				if(pri_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_COMM)//data is for COMM
				{
					createDataFromQueueFor(ROVERCOMM_COMM, PRIMARY_MSG_QUEUE);
				}//end if
				else if(pri_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_CMNC) //data is for CMNC
				{
					createDataFromQueueFor(ROVERCOMM_CMNC, PRIMARY_MSG_QUEUE);
				}//end else if
				else if(pri_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_MAIN) //data is for MAIN
				{
					createDataFromQueueFor(ROVERCOMM_MAIN, PRIMARY_MSG_QUEUE);
				}//end else if
				else if(pri_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_AUXI) //data is for AUXI
				{
					createDataFromQueueFor(ROVERCOMM_AUXI, PRIMARY_MSG_QUEUE);
				}//end else if
				else//invalid state, error out
				{
					_SERIAL_DEBUG_CHANNEL_.println(F("ErrUnkDest"));//error, unknown destination
				}//end else
				
				
								
			}//end if
										
			//skip auto data for SYNCHRONIZATION
						
			//skip second message queue for SYNCHRONIZATION			
			
			
			break;
		case TX_COMMUNICATIONS: //Mode: SYNCHRONIZATION

			//Note: There are no redirections for the NAVI Arduino since it is a node at the end of the network tree.

			//1. Sends data to PC_USB
			if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
			{
				txData(txMsgBuffer_PC_USB, ROVERCOMM_PC_USB);
			}//end if
			//2. Sends data to MAIN (primary queue)
			if (main_pri_msg_queue != CMD_TAG_NO_MSG)
			{
				txData(txMsgBuffer_Pri_MAIN, ROVERCOMM_MAIN);//Note: This just sends the data as created through the MAIN channel. Whether it goes to COMM, CMNC, MAIN, or AUXI that would be determined in the createDataFromQueueFor().
			}//end if
			
			//Only the primary message queue is sent (the system ready msg to MAIN), and everything else can be ignored since the system is still synching up.
			
			//3. Clears message queue(s)
			pc_usb_msg_queue = CMD_TAG_NO_MSG;
			main_pri_msg_queue = CMD_TAG_NO_MSG;
			main_sec_msg_queue = CMD_TAG_NO_MSG;
			pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;//default to MAIN
			sec_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;//default to MAIN			
						
			//4. Reset the first transmission flag
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

//LEFT OFF HERE
//WRITE ME LATER


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

			//rxData() from MAIN
			//1. Reset status flag
			ch2Status = DATA_STATUS_NOT_READY;
			//2. Clear all Rx'ed data before getting new data				
			roverComm_Ch2->clearRxData();
			//3. Receive data
			ch2Status = rxData(roverComm_Ch2, ROVERCOMM_MAIN);//Note: this is a local .ino function
					
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
		case DATA_FILTER: //Mode: NORMAL_OPERATIONS


			//Reset/clear flags (no data was for NAVI)
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_NAVI_CH1_);
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_NAVI_CH2_);
										
			//Set Command Filter Options
			//First initialize all command choices to false
			setAllCommandFiltersTo(false, ROVERCOMM_PC_USB);//for PC_USB
			setAllCommandFiltersTo(false, ROVERCOMM_MAIN);//for MAIN
			
			//Then enable the allowed commands for this mode:
			//For PC_USB
			//No filter on PC_USB data. (Allow all data from PC_USB)
			//No commands from PC_USB are filtered, so set all to true.
			setAllCommandFiltersTo(true, ROVERCOMM_PC_USB);			
			//For MAIN
			setAllCommandFiltersTo(true, ROVERCOMM_MAIN);			
			//No filter on MAIN data. (Allow all data from MAIN)
			//No commands from MAIN are filtered, so set all to true.
			
			
			//Transmit data and/or execute command
						
			//For data from PC_USB, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, NAVI
			if (ch1Status == DATA_STATUS_VALID)
			{
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//Note: There are no redirections for the NAVI Arduino since it is a node at the end of the network tree.
				//Note: this is a local .ino function

				dataDirector(roverDataCh1_COMM, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_NAVI_CH1_);//DataDirection will set the "data was for NAVI flag" to true if it was for this Arduino

				/*
				Allow all data from PC_USB.
				*/

			}//end if

			//For data from MAIN, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, NAVI
			if (ch2Status == DATA_STATUS_VALID)
			{
			
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//Note: There are no redirections for the NAVI Arduino since it is a node at the end of the network tree.
				//Note: this is a local .ino function

				dataDirector(roverDataCh2_COMM, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_NAVI_CH2_);//DataDirection will set the "data was for NAVI flag" to true if it was for this Arduino
				
				/*
				Set filter to throw away all MAIN data except:

				*/				

			}//end if		
		
		
			break;	
		case READ_INPUTS: //Mode: NORMAL_OPERATIONS
		
		
			//Read All Ultrasonic Distance Sensors
				//Note: The Ultrasonic's trigger will implicitly be controlled when the sensor is read, since the trigger is part of the reading process	
			for (byte i = 0; i < ULTRASONIC_SENSORS_ARRAY_SIZE; i++)
			{
				uSonDistanceMeasured[i] = uSonSensors[i]->getDistance(UNIT_CM);//store the ultrasonic's distance in the corresponding spot in the uSonDistanceMeasured[] array
			}//end for
			
			//Read IR Distance Sensors
			for (byte i = 0; i < INFRARED_SENSORS_ARRAY_SIZE; i++)
			{
				irDistanceMeasured[i] = irDistanceSensors[i]->getDistance(UNIT_CM);//store the ultrasonic's distance in the corresponding spot in the irDistanceMeasured[] array
			}//end for

				
			//Read NAVI Wheel Encoders
			for (byte i = 0; i < NAVI_WHEEL_ENCODERS_SENSORS_ARRAY_SIZE; i++)
			{
			
					allWheelEncodersDirection[i] = naviWheelEncoders[i]->getDirection();//As defined in RoverConfig.h under "//Motor Directions"
					allWheelEncodersFootage[i] = naviWheelEncoders[i]->getFootage();//distance traveled in feet
					allWheelEncodersSpeed[i] = naviWheelEncoders[i]->getSpeed();//in inches per second

			}//end for		
			//Note: For the MAIN Encoders, the mid right and mid left data will be received through serial communication from MAIN and stored. See commandDirector().
			
			//Read GPS			
			//Get samples of actual GPS coordinates
			if(rxGPSData(roverGps))//Receive (via serial) and process gps data
			{
				#ifdef _PRINT_GPS_DATA_STATUS
					_SERIAL_DEBUG_CHANNEL_.println(F("GPS Data Valid"));
				#endif
				BooleanBitFlags::setFlagBit(flagSet_SystemStatus1, _BTFG_GPS_DATA_READY_);
			 }//end if
			else//Else notify that the GPS data isn't ready
			{
				#ifdef _PRINT_GPS_DATA_STATUS
					_SERIAL_DEBUG_CHANNEL_.println(F("GPS Data Not Ready"));
				#endif		
				BooleanBitFlags::clearFlagBit(flagSet_SystemStatus1, _BTFG_GPS_DATA_READY_);
			}//end else
			break;

		case PROCESS_DATA: //Mode: NORMAL_OPERATIONS		
		

			#ifdef _DEBUG_PRINT_TIMEOUT_COUNTER_VALUE_
				Serial.println(timeout_counter);//DEBUG
			#endif
			
			
			//Run lower priority functions here.
			//These messages and flags may be overrided with commandDirector()			

			//Process PC_USB command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//All other messages are allowed from PC_USB. Use with caution.
				//Note: There are no redirections for the NAVI Arduino since it is a node at the end of the network tree.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_NAVI_CH1_))//If there was data from PC_USB (Ch1), and it was for NAVI
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh1_COMM, ROVERCOMM_PC_USB);
			}//end if			
			//Process MAIN command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//All messages are allowed from MAIN.
				//Note: There are no redirections for the NAVI Arduino since it is a node at the end of the network tree.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_NAVI_CH2_))//If there was data from MAIN (Ch2), and it was for NAVI
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh2_COMM, ROVERCOMM_MAIN);
			}//end if				

			

			//Process ultrasonic distance sensors
				//Note: Nothing else needed to process for ultrasonics. It's already taken care of in the READ_INPUTS state
			//Process ir distance sensors
				//Note: Nothing else needed to process for ir distance sensors. It's already taken care of in the READ_INPUTS state
			//Process heading (for AUXI-external)
			
			//If Heading data is ready and valid
			 if(BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_HEADING_DATA_READY_))
			 {
				processHeading(tempHeadingData);
			 }//end if
			 //else do nothing since the data is invalid

			//Process motor power status (for MAIN-external)
				//Note: Nothing else needed to process for the motor power status. It's already taken care of by the commandDirector() in this PROCESS_DATA state.
			
			//Process wheel encoders (for MAIN-external and for NAVI-internal)			
				//Note: Nothing else needed to process for the NAVI wheel encoders. It's already taken care of in the READ_INPUTS state
				//Note: Nothing else needed to process for the MAIN wheel encoders. It's already taken care of by the commandDirector() in this PROCESS_DATA state.
			
			//Process GPS		
			//When GPS data is ready and valid
			if( BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_GPS_DATA_READY_) )
			{
				//save the lat and long data into the array, which will later be sorted and the median will be extracted
				processGPS(roverGps->getGpsLatitude(DEC_DEG), roverGps->getGpsLongitude(DEC_DEG));//where the latitude and longitude are in decimal degrees
			}//end if
			//else do nothing since the data is invalid
			
		
			//Run highest priority functions here (after command director). //this will override any lower priority messages (i.e. system go). This will overwrite anything else. (i.e. system ready)
		

			break;
/* TEMPLATE			
		case PLAN_ROUTE: //Mode: NORMAL_OPERATIONS
//TEMPLATE		
		
Set ideal (non object in way) course/speed in the PLAN_ROUTE state. Then actual course speed will be either this ideal or if there is an object in the way, it will be overrided in the OBJECT_AVOIDANCE state
		
		//SEE NavigationTester_NAVI.ino
		
		
i.e.
///////////////////END OF EXAMPLE

					_SERIAL_DEBUG_CHANNEL_.print(F("Distance: "));
					tempValue = roverNavigation->getDistance(UNIT_M);
					_SERIAL_DEBUG_CHANNEL_.println(tempValue, DECIMAL_PRECISION);//print with the define decimal precision
					_SERIAL_DEBUG_CHANNEL_.print(F("True Bearing: "));
					tempValue = roverNavigation->getTrueBearing();
					_SERIAL_DEBUG_CHANNEL_.println(tempValue, DECIMAL_PRECISION);//print with the define decimal precision	

					_SERIAL_DEBUG_CHANNEL_.print(F("Relative Bearing: "));
					tempValue = roverNavigation->getRelativeBearing();
					_SERIAL_DEBUG_CHANNEL_.println(tempValue, DECIMAL_PRECISION);//print with the define decimal precision	

					_SERIAL_DEBUG_CHANNEL_.print(F("Get Motor Steering: "));
					tempValue = roverNavigation->getCalculatedMotorSteering();
					translateMotorSteering(roverNavigation->getCalculatedMotorSteering());

					_SERIAL_DEBUG_CHANNEL_.print(F("Get Motor Throttle: "));
					translateMotorThrottle(roverNavigation->getCalculatedMotorThrottle());


					_SERIAL_DEBUG_CHANNEL_.print(F("Rover Nav Status: "));
					if (roverNavigation->hasReachedDestination())
					{
					_SERIAL_DEBUG_CHANNEL_.println(F("Destination Reached"));
					}
					else
					{
					_SERIAL_DEBUG_CHANNEL_.println(F("Still Navigating"));
					}
///////////////////END OF EXAMPLE
					

		
		case OBJECT_AVOIDANCE: //Mode: NORMAL_OPERATIONS
//TEMPLATE		
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;					
*/						
		case CONTROL_OUTPUTS: //Mode: NORMAL_OPERATIONS

		//Control Buffer Select
			//if buffer_remote_ctrl_selected == true
			if( BooleanBitFlags::flagIsSet(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_))
			{
				#ifdef _DEBUG_OUTPUT_DRIVE_SELECTION_STATUS
					_SERIAL_DEBUG_CHANNEL_.println(F("MANUAL DRIVE"));
				#endif
				roverBuffer->driverMode(MANUAL_DRIVE);
			}//end if
			//buffer_remote_ctrl_selected == false
			else
			{
				#ifdef _DEBUG_OUTPUT_DRIVE_SELECTION_STATUS
					_SERIAL_DEBUG_CHANNEL_.println(F("AUTO DRIVE"));
				#endif
				roverBuffer->driverMode(AUTO_DRIVE);
				
				//When in auto drive, control the motors and the gimbal
				
				//Control Motor Controller's Turn			
				motorControllerSetSteering(motor_turn_value);//the value was determined by the PLAN_ROUTE and/or OBJECT_AVOIDANCE state
					
				//Control Motor Controller's Speed			
				motorControllerSetThrottle(motor_speed_value);//the value was determined by the PLAN_ROUTE and/or OBJECT_AVOIDANCE state
				
				//Control Gimbal Controller's Pan			
				gimbalSetPan(gimbal_pan_value);//the value was determined by the PLAN_ROUTE and/or OBJECT_AVOIDANCE state
				
				//Control Gimbal Controller's Tilt			
				gimbalSetTilt(gimbal_tilt_value);//the value was determined by the PLAN_ROUTE and/or OBJECT_AVOIDANCE state
			
			}//end else

			
			//LEDs will be controlled by RUN_HOUSEKEEPING_TASKS (i.e. runBackgroundTasks()) since it requires attention with every loop
			
			//The Ultrasonic's trigger will be controlled when the sensor is read, since the trigger is part of the reading process						
	
			break;
		case CREATE_DATA: //Mode: NORMAL_OPERATIONS

			//Creates data for PC_USB
			if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_PC_USB, PC_USB_MSG_QUEUE);
				
				//skip auto data	
				
			}//end if
			
			
			//Creates data for MAIN (primary queue)
			if (main_pri_msg_queue != CMD_TAG_NO_MSG)
			{
			
				if(pri_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_COMM)//data is for COMM
				{
					createDataFromQueueFor(ROVERCOMM_COMM, PRIMARY_MSG_QUEUE);
				}//end if
				else if(pri_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_CMNC) //data is for CMNC
				{
					createDataFromQueueFor(ROVERCOMM_CMNC, PRIMARY_MSG_QUEUE);
				}//end else if
				else if(pri_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_MAIN) //data is for MAIN
				{
					createDataFromQueueFor(ROVERCOMM_MAIN, PRIMARY_MSG_QUEUE);
				}//end else if
				else if(pri_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_AUXI) //data is for AUXI
				{
					createDataFromQueueFor(ROVERCOMM_AUXI, PRIMARY_MSG_QUEUE);
				}//end else if
				else//invalid state, error out
				{
					_SERIAL_DEBUG_CHANNEL_.println(F("ErrUnkDest"));//error, unknown destination
				}//end else
								
			}//end if
			//Auto data code for Primary Queue			
			else if( auto_NAVI_to_COMM_data_cnt < sizeof(auto_NAVI_to_COMM_data_array) )//if there is auto data for COMM and it has not been all sent yet
				//if there is auto data for COMM and it has not been all sent yet
				//Note: Since the counter is a byte, it's lowest value is 0. And the array size can't be smaller than zero. So this can only be true if the array has data, i.e. it's size is greater than 0 and the counter is less than the size of the array. If the array is empty, the size would be 0 and the counter's lowest value would be 0, so it would be equal and not less than, so the if statement would be still false.
			{
				//since there is no custom data, then send the next auto data.
					//create message corresponding to the next auto data for COMM.

					//Assign the next auto message to the queue
					main_pri_msg_queue = auto_NAVI_to_COMM_data_array[auto_NAVI_to_COMM_data_cnt];

					pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_COMM;
					
					//Create the message
					createDataFromQueueFor(ROVERCOMM_COMM, PRIMARY_MSG_QUEUE);
					
					//Loop/Increment the auto data for the next iteration
					auto_NAVI_to_COMM_data_cnt++;

					//Note: Though auto data increments now, preparing for the next iteration, the queue data was already assigned above and is "latched" or "locked" in for this iteration. As the queue and not the auto data is referred for the rest of this loop iteration.

			}//end else if
			else if ( auto_NAVI_to_CMNC_data_cnt < sizeof(auto_NAVI_to_CMNC_data_array) )//if there is auto data for CMNC and it has not been all sent yet
				//Note: Since the counter is a byte, it's lowest value is 0. And the array size can't be smaller than zero. So this can only be true if the array has data, i.e. it's size is greater than 0 and the counter is less than the size of the array. If the array is empty, the size would be 0 and the counter's lowest value would be 0, so it would be equal and not less than, so the if statement would be still false.			
			{
					//since there is no custom data, then send the next auto data.
					//create message corresponding to the next auto data for CMNC.

					//Assign the next auto message to the queue
					main_pri_msg_queue = auto_NAVI_to_CMNC_data_array[auto_NAVI_to_CMNC_data_cnt];

					pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_CMNC;
					
					//Create the message
					createDataFromQueueFor(ROVERCOMM_CMNC, PRIMARY_MSG_QUEUE);
					
					//Loop/Increment the auto data for the next iteration
					auto_NAVI_to_CMNC_data_cnt++;

					//Note: Though auto data increments now, preparing for the next iteration, the queue data was already assigned above and is "latched" or "locked" in for this iteration. As the queue and not the auto data is referred for the rest of this loop iteration.

			}//end else if
			else if ( auto_NAVI_to_MAIN_data_cnt < sizeof(auto_NAVI_to_MAIN_data_array) )//if there is auto data for MAIN and it has not been all sent yet
				//Note: Since the counter is a byte, it's lowest value is 0. And the array size can't be smaller than zero. So this can only be true if the array has data, i.e. it's size is greater than 0 and the counter is less than the size of the array. If the array is empty, the size would be 0 and the counter's lowest value would be 0, so it would be equal and not less than, so the if statement would be still false.			
			{
					//since there is no custom data, then send the next auto data.
					//create message corresponding to the next auto data for CMNC.

					//Assign the next auto message to the queue
					main_pri_msg_queue = auto_NAVI_to_MAIN_data_array[auto_NAVI_to_MAIN_data_cnt];

					pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_CMNC;
					
					//Create the message
					createDataFromQueueFor(ROVERCOMM_CMNC, PRIMARY_MSG_QUEUE);
					
					//Loop/Increment the auto data for the next iteration
					auto_NAVI_to_MAIN_data_cnt++;

					//Note: Though auto data increments now, preparing for the next iteration, the queue data was already assigned above and is "latched" or "locked" in for this iteration. As the queue and not the auto data is referred for the rest of this loop iteration.

			}//end else if				
			else if ( auto_NAVI_to_AUXI_data_cnt < sizeof(auto_NAVI_to_AUXI_data_array) )//if there is auto data for AUXI and it has not been all sent yet
				//Note: Since the counter is a byte, it's lowest value is 0. And the array size can't be smaller than zero. So this can only be true if the array has data, i.e. it's size is greater than 0 and the counter is less than the size of the array. If the array is empty, the size would be 0 and the counter's lowest value would be 0, so it would be equal and not less than, so the if statement would be still false.			
			{
					//since there is no custom data, then send the next auto data.
					//create message corresponding to the next auto data for CMNC.

					//Assign the next auto message to the queue
					main_pri_msg_queue = auto_NAVI_to_AUXI_data_array[auto_NAVI_to_AUXI_data_cnt];

					pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_CMNC;
					
					//Create the message
					createDataFromQueueFor(ROVERCOMM_CMNC, PRIMARY_MSG_QUEUE);
					
					//Loop/Increment the auto data for the next iteration
					auto_NAVI_to_AUXI_data_cnt++;

					//Note: Though auto data increments now, preparing for the next iteration, the queue data was already assigned above and is "latched" or "locked" in for this iteration. As the queue and not the auto data is referred for the rest of this loop iteration.

			}//end else if						
			//else do nothing since there was no message and no auto data to send
					
			
			
		
			//Creates data for MAIN (secondary queue)
			if (main_sec_msg_queue != CMD_TAG_NO_MSG)
			{
			
				if(sec_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_COMM)//data is for COMM
				{
					createDataFromQueueFor(ROVERCOMM_COMM, SECONDARY_MSG_QUEUE);
				}//end if
				else if(sec_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_CMNC) //data is for CMNC
				{
					createDataFromQueueFor(ROVERCOMM_CMNC, SECONDARY_MSG_QUEUE);
				}//end else if
				else if(sec_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_MAIN) //data is for MAIN
				{
					createDataFromQueueFor(ROVERCOMM_MAIN, SECONDARY_MSG_QUEUE);
				}//end else if
				else if(sec_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_AUXI) //data is for AUXI
				{
					createDataFromQueueFor(ROVERCOMM_AUXI, SECONDARY_MSG_QUEUE);
				}//end else if
				else//invalid state, error out
				{
					_SERIAL_DEBUG_CHANNEL_.println(F("ErrUnkDest"));//error, unknown destination
				}//end else
								
			}//end if
			//Auto data code for Secondary Queue			
			else if( auto_NAVI_to_COMM_data_cnt < sizeof(auto_NAVI_to_COMM_data_array) )//if there is auto data for COMM and it has not been all sent yet
				//if there is auto data for COMM and it has not been all sent yet
				//Note: Since the counter is a byte, it's lowest value is 0. And the array size can't be smaller than zero. So this can only be true if the array has data, i.e. it's size is greater than 0 and the counter is less than the size of the array. If the array is empty, the size would be 0 and the counter's lowest value would be 0, so it would be equal and not less than, so the if statement would be still false.
			{
				//since there is no custom data, then send the next auto data.
					//create message corresponding to the next auto data for COMM.

					//Assign the next auto message to the queue
					main_sec_msg_queue = auto_NAVI_to_COMM_data_array[auto_NAVI_to_COMM_data_cnt];

					sec_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_COMM;
					
					//Create the message
					createDataFromQueueFor(ROVERCOMM_COMM, SECONDARY_MSG_QUEUE);
					
					//Loop/Increment the auto data for the next iteration
					auto_NAVI_to_COMM_data_cnt++;

					//Note: Though auto data increments now, preparing for the next iteration, the queue data was already assigned above and is "latched" or "locked" in for this iteration. As the queue and not the auto data is referred for the rest of this loop iteration.

			}//end else if
			else if ( auto_NAVI_to_CMNC_data_cnt < sizeof(auto_NAVI_to_CMNC_data_array) )//if there is auto data for CMNC and it has not been all sent yet
				//Note: Since the counter is a byte, it's lowest value is 0. And the array size can't be smaller than zero. So this can only be true if the array has data, i.e. it's size is greater than 0 and the counter is less than the size of the array. If the array is empty, the size would be 0 and the counter's lowest value would be 0, so it would be equal and not less than, so the if statement would be still false.			
			{
					//since there is no custom data, then send the next auto data.
					//create message corresponding to the next auto data for CMNC.

					//Assign the next auto message to the queue
					main_sec_msg_queue = auto_NAVI_to_CMNC_data_array[auto_NAVI_to_CMNC_data_cnt];

					sec_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_CMNC;
					
					//Create the message
					createDataFromQueueFor(ROVERCOMM_CMNC, SECONDARY_MSG_QUEUE);
					
					//Loop/Increment the auto data for the next iteration
					auto_NAVI_to_CMNC_data_cnt++;

					//Note: Though auto data increments now, preparing for the next iteration, the queue data was already assigned above and is "latched" or "locked" in for this iteration. As the queue and not the auto data is referred for the rest of this loop iteration.

			}//end else if
			else if ( auto_NAVI_to_MAIN_data_cnt < sizeof(auto_NAVI_to_MAIN_data_array) )//if there is auto data for MAIN and it has not been all sent yet
				//Note: Since the counter is a byte, it's lowest value is 0. And the array size can't be smaller than zero. So this can only be true if the array has data, i.e. it's size is greater than 0 and the counter is less than the size of the array. If the array is empty, the size would be 0 and the counter's lowest value would be 0, so it would be equal and not less than, so the if statement would be still false.			
			{
					//since there is no custom data, then send the next auto data.
					//create message corresponding to the next auto data for CMNC.

					//Assign the next auto message to the queue
					main_sec_msg_queue = auto_NAVI_to_MAIN_data_array[auto_NAVI_to_MAIN_data_cnt];

					sec_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_CMNC;
					
					//Create the message
					createDataFromQueueFor(ROVERCOMM_CMNC, SECONDARY_MSG_QUEUE);
					
					//Loop/Increment the auto data for the next iteration
					auto_NAVI_to_MAIN_data_cnt++;

					//Note: Though auto data increments now, preparing for the next iteration, the queue data was already assigned above and is "latched" or "locked" in for this iteration. As the queue and not the auto data is referred for the rest of this loop iteration.

			}//end else if				
			else if ( auto_NAVI_to_AUXI_data_cnt < sizeof(auto_NAVI_to_AUXI_data_array) )//if there is auto data for AUXI and it has not been all sent yet
				//Note: Since the counter is a byte, it's lowest value is 0. And the array size can't be smaller than zero. So this can only be true if the array has data, i.e. it's size is greater than 0 and the counter is less than the size of the array. If the array is empty, the size would be 0 and the counter's lowest value would be 0, so it would be equal and not less than, so the if statement would be still false.			
			{
					//since there is no custom data, then send the next auto data.
					//create message corresponding to the next auto data for CMNC.

					//Assign the next auto message to the queue
					main_sec_msg_queue = auto_NAVI_to_AUXI_data_array[auto_NAVI_to_AUXI_data_cnt];

					sec_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_CMNC;
					
					//Create the message
					createDataFromQueueFor(ROVERCOMM_CMNC, SECONDARY_MSG_QUEUE);
					
					//Loop/Increment the auto data for the next iteration
					auto_NAVI_to_AUXI_data_cnt++;

					//Note: Though auto data increments now, preparing for the next iteration, the queue data was already assigned above and is "latched" or "locked" in for this iteration. As the queue and not the auto data is referred for the rest of this loop iteration.

			}//end else if						
			//else do nothing since there was no message and no auto data to send
								
			

					
			//Once all the counters are equal to or greater than the size of the arrays (or even if the array is empty with size 0), reset all the counters)
			if (
				auto_NAVI_to_COMM_data_cnt >= sizeof(auto_NAVI_to_COMM_data_array) &&
				auto_NAVI_to_CMNC_data_cnt >= sizeof(auto_NAVI_to_CMNC_data_array) &&
				auto_NAVI_to_MAIN_data_cnt >= sizeof(auto_NAVI_to_MAIN_data_array) &&
				auto_NAVI_to_AUXI_data_cnt >= sizeof(auto_NAVI_to_AUXI_data_array)
				)
			{
				auto_NAVI_to_CMNC_data_cnt = 0;
				auto_NAVI_to_COMM_data_cnt = 0;
				auto_NAVI_to_MAIN_data_cnt = 0;
				auto_NAVI_to_AUXI_data_cnt = 0;
			}//end if

			break;
		case TX_COMMUNICATIONS: //Mode: NORMAL_OPERATIONS

			//Note: There are no redirections for the NAVI Arduino since it is a node at the end of the network tree.
	
			//Interweave primary transmissions and the secondary transmission, to allow the receiving end have time to process each incoming data
	
			if(BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_FIRST_TRANSMISSION_))//check to see if this is the first transmission
			{		
			
				//1. Sends data to PC_USB
				if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
				{
					txData(txMsgBuffer_PC_USB, ROVERCOMM_PC_USB);
				}//end if
				//2. Sends data to MAIN (primary queue)
				if (main_pri_msg_queue != CMD_TAG_NO_MSG)
				{
					txData(txMsgBuffer_Pri_MAIN, ROVERCOMM_MAIN);//Note: This just sends the data as created through the MAIN channel. Whether it goes to COMM, CMNC, MAIN, or AUXI that would be determined in the createDataFromQueueFor().
				}//end if
				//3. Check to see if there are any second messages to send
				if ( main_sec_msg_queue != CMD_TAG_NO_MSG )		
				{
					BooleanBitFlags::clearFlagBit(flagSet_SystemStatus1, _BTFG_FIRST_TRANSMISSION_);//clear the flag
					//reset the counter before use
					transmission_delay_cnt = 0;
					queuedState = TX_COMMUNICATIONS;//override the default state (usually would be RX_COMMUNICATIONS)
				}//end if
				else//there is no second transmission, move on
				{					
					//clears message queue(s)
					pc_usb_msg_queue = CMD_TAG_NO_MSG;
					main_pri_msg_queue = CMD_TAG_NO_MSG;
					main_sec_msg_queue = CMD_TAG_NO_MSG;
					pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;//default to MAIN
					sec_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;//default to MAIN			
					//reset the first transmission flag
					BooleanBitFlags::setFlagBit(flagSet_SystemStatus1, _BTFG_FIRST_TRANSMISSION_);						
				}//end else					
			}//end if			
			else//this is not the first transmission
			{
					
				if(transmission_delay_cnt >= CONCURRENT_TRANSMISSION_DELAY) //once the desired delay has been reached, continue with the code
				{								
			
				
					txData(txMsgBuffer_Sec_MAIN, ROVERCOMM_MAIN);//Note: This just sends the data as created through the MAIN channel. Whether it goes to COMM, CMNC, MAIN, or AUXI that would be determined in the createDataFromQueueFor().
				
					//clears message queue(s)
					pc_usb_msg_queue = CMD_TAG_NO_MSG;
					main_pri_msg_queue = CMD_TAG_NO_MSG;
					main_sec_msg_queue = CMD_TAG_NO_MSG;
					pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;//default to MAIN
					sec_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;//default to MAIN			
					//reset the first transmission flag
					BooleanBitFlags::setFlagBit(flagSet_SystemStatus1, _BTFG_FIRST_TRANSMISSION_);
							
				}//end if
				else//the desired delay has not been reached yet, so just increment the count
				{
					transmission_delay_cnt++;
					queuedState = TX_COMMUNICATIONS;//override the default state (usually would be RX_COMMUNICATIONS)
				}//end else			
			}//end else
			break;		
		default: //default state
//TEMPLATE		
			 //This code should never execute, if it does, there is a logical or programming error			
			runModeFunction_default();//no state needed, all states do the same thing
			break;
		
	}//end switch

}//end of runModeFunction_NORMAL_OPERATIONS()
void runModeFunction_SYSTEM_SLEEPING(byte currentState)
{
	_PRINT_MODE_(F("MODE: SYSTEM_SLEEPING"));

//LEFT OFF HERE
//WRITE ME LATER


	switch (currentState)
	{
		case RUN_HOUSEKEEPING_TASKS: //Mode: SYSTEM_SLEEPING
			runBackgroundTasks();
			break;
		case RX_COMMUNICATIONS: //Mode: SYSTEM_SLEEPING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case DATA_VALIDATION: //Mode: SYSTEM_SLEEPING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case DATA_FILTER: //Mode: SYSTEM_SLEEPING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;	
		case READ_INPUTS: //Mode: SYSTEM_SLEEPING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case PROCESS_DATA: //Mode: SYSTEM_SLEEPING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case PLAN_ROUTE: //Mode: SYSTEM_SLEEPING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;			
		case OBJECT_AVOIDANCE: //Mode: SYSTEM_SLEEPING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		
		case CONTROL_OUTPUTS: //Mode: SYSTEM_SLEEPING
		
			//Since Navigation is skipped for SYSTEM_SLEEPING, set default values for motors and gimbal here at the CONTROL_OUTPUTS state


			//Set motor and gimbal to default values
			motor_turn_value = SET_GO_STRAIGHT;
			motor_speed_value = SET_STOP_SPEED;
			gimbal_pan_value = SET_CENTER_PAN;
			gimbal_tilt_value = SET_MIDDLE_TILT;
			
			//turn buffer select to non-remote (local) control
			BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_);//buffer_remote_ctrl_selected = false 
				
			drive_setting = AUTONOMOUS_DRIVE;//since it's at SYSTEM_SLEEPING and the rover should have control
				

			//Control Buffer Select
			//if buffer_remote_ctrl_selected == true
			if( BooleanBitFlags::flagIsSet(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_))
			{
				#ifdef _DEBUG_OUTPUT_DRIVE_SELECTION_STATUS
					_SERIAL_DEBUG_CHANNEL_.println(F("MANUAL DRIVE"));
				#endif
				roverBuffer->driverMode(MANUAL_DRIVE);
			}//end if
			//buffer_remote_ctrl_selected == false
			else
			{
				#ifdef _DEBUG_OUTPUT_DRIVE_SELECTION_STATUS
					_SERIAL_DEBUG_CHANNEL_.println(F("AUTO DRIVE"));
				#endif
				roverBuffer->driverMode(AUTO_DRIVE);
				
				//When in auto drive, control the motors and the gimbal
				
				//Control Motor Controller's Turn			
				motorControllerSetSteering(motor_turn_value);//Should be motor_turn_value = SET_GO_STRAIGHT

				//Control Motor Controller's Speed			
				motorControllerSetThrottle(motor_speed_value);//Should be motor_speed_value = SET_STOP_SPEED			

				//Control Gimbal Controller's Pan			
				gimbalSetPan(gimbal_pan_value);//Should be gimbal_pan_value = SET_CENTER_PAN

				//Control Gimbal Controller's Tilt			
				gimbalSetTilt(gimbal_tilt_value);//Should be gimbal_tilt_value = SET_MIDDLE_TILT

			
			}//end else

				
			//LEDs will be controlled by RUN_HOUSEKEEPING_TASKS (i.e. runBackgroundTasks()) since it requires attention with every loop
			
			//The Ultrasonic's trigger will be controlled when the sensor is read, since the trigger is part of the reading process	
			
			break;
		case CREATE_DATA: //Mode: SYSTEM_SLEEPING

			//Creates data for PC_USB
			if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_PC_USB, PC_USB_MSG_QUEUE);
				
				//skip auto data	
				
			}//end if
			
			
			//Creates data for MAIN (primary queue)
			if (main_pri_msg_queue != CMD_TAG_NO_MSG)
			{
			
				if(pri_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_COMM)//data is for COMM
				{
					createDataFromQueueFor(ROVERCOMM_COMM, PRIMARY_MSG_QUEUE);
				}//end if
				else if(pri_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_CMNC) //data is for CMNC
				{
					createDataFromQueueFor(ROVERCOMM_CMNC, PRIMARY_MSG_QUEUE);
				}//end else if
				else if(pri_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_MAIN) //data is for MAIN
				{
					createDataFromQueueFor(ROVERCOMM_MAIN, PRIMARY_MSG_QUEUE);
				}//end else if
				else if(pri_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_AUXI) //data is for AUXI
				{
					createDataFromQueueFor(ROVERCOMM_AUXI, PRIMARY_MSG_QUEUE);
				}//end else if
				else//invalid state, error out
				{
					_SERIAL_DEBUG_CHANNEL_.println(F("ErrUnkDest"));//error, unknown destination
				}//end else
								
			}//end if
										
			//skip auto data for SYSTEM_SLEEPING
						
			//skip second message queue for SYSTEM_SLEEPING
			
			break;
		case TX_COMMUNICATIONS: //Mode: SYSTEM_SLEEPING


			//Note: There are no redirections for the NAVI Arduino since it is a node at the end of the network tree.

			//1. Sends data to PC_USB
			if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
			{
				txData(txMsgBuffer_PC_USB, ROVERCOMM_PC_USB);
			}//end if
			//2. Sends data to MAIN (primary queue)
			if (main_pri_msg_queue != CMD_TAG_NO_MSG)
			{
				txData(txMsgBuffer_Pri_MAIN, ROVERCOMM_MAIN);//Note: This just sends the data as created through the MAIN channel. Whether it goes to COMM, CMNC, MAIN, or AUXI that would be determined in the createDataFromQueueFor().
			}//end if
			
			//Only the primary message queue is sent (the system ready msg to MAIN), and everything else can be ignored since the system is still synching up.
			
			//3. Clears message queue(s)
			pc_usb_msg_queue = CMD_TAG_NO_MSG;
			main_pri_msg_queue = CMD_TAG_NO_MSG;
			main_sec_msg_queue = CMD_TAG_NO_MSG;
			pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;//default to MAIN
			sec_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;//default to MAIN			
						
			//4. Reset the first transmission flag
			BooleanBitFlags::setFlagBit(flagSet_SystemStatus1, _BTFG_FIRST_TRANSMISSION_);						
			
	
			//Note: If MAIN misses this message, MAIN will go into sleeping error and would require a SW reset or HW reset to take the Rover out of this error. (AUXI can't resend the sleeping acknowledgement since it already went to sleep)	
	
			//Troubleshooting tip: If MAIN keeps missing this message, can send it twice through the main_pri_msg_queue and then the main_sec_msg_queue as well.

			
			//SETUP FOR WAKEUP
				
				//setup this mode ahead of time before going to sleep
				currentMode = SYSTEM_WAKING;//Set mode to SYSTEM_WAKING *begin*			
				
				queuedState = CONTROL_OUTPUTS;//Go to CONTROL_OUTPUTS in order to restore previous laser states

				//Restore previous states
				//Motor Turn/Speed Settings
				motor_turn_value = prev_motor_turn_value;
				motor_speed_value = prev_motor_speed_value;
				//Gimbal Settings
				gimbal_pan_value = prev_gimbal_pan_value;
				gimbal_tilt_value = prev_gimbal_tilt_value;
				
				//Drive Settings
				drive_setting = prev_drive_setting;				
				
				//Restore previous buffer remote control: buffer_remote_ctrl_selected = prev_buffer_remote_ctrl_selected
				if( BooleanBitFlags::flagIsSet(flagSet_SystemControls1, _BTFG_PREV_REMOTE_CTRL_SELECTED_) )
				{
					BooleanBitFlags::setFlagBit(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_);
				}//end if
				else
				{
					BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_);
				}//end else
							
				//LED States
				prev_universal_led_mode = universal_led_mode;
				prev_hazard_light_state = hazard_light_state;
				prev_fog_light_state = fog_light_state;
				prev_underglow_light_state = underglow_light_state;
				prev_ir_beacon_state = ir_beacon_state;
				prev_blue_beacon_state = blue_beacon_state;
				prev_beacon_led_direction = beacon_led_direction;
				prev_rover_motion = rover_motion;
				prev_rover_error_type = rover_error_type;

				
	
				//clear the flags for future reuse
				prev_motor_turn_value = SET_GO_STRAIGHT;
				prev_motor_speed_value = SET_STOP_SPEED;
				prev_gimbal_pan_value = SET_CENTER_PAN;
				prev_gimbal_tilt_value = SET_MIDDLE_TILT;
				prev_drive_setting = AUTONOMOUS_DRIVE;
				BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_PREV_REMOTE_CTRL_SELECTED_);//prev_buffer_remote_ctrl_selected = false
				prev_universal_led_mode = LED_SET_ALL_DEFAULT;
				prev_hazard_light_state = LED_SET_ALL_DEFAULT;
				prev_fog_light_state = LED_SET_ALL_DEFAULT;
				prev_underglow_light_state = LED_SET_ALL_DEFAULT;
				prev_ir_beacon_state = LED_SET_ALL_DEFAULT;
				prev_blue_beacon_state = LED_SET_ALL_DEFAULT;
				prev_beacon_led_direction = LED_SET_ALL_DEFAULT;
				prev_rover_motion = LED_SET_ALL_DEFAULT;
				prev_rover_error_type = LED_SET_ALL_DEFAULT;
				

				//Run other pre-sleep tasks. (i.e. end software serial, as needed)
					//No SW Serials used for MAIN
					//Do nothing for now. Place holder.
				
				_PRINT_SLEEPING_AND_WAKEUP_STATUS_(F("NAVI_Sleep"));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
				
				
				delay(100);//add some delay to allow the serial print to finish before going to sleep

			//END OF SETUP FOR WAKEUP
					
			//GOING TO SLEEP
				//Put NAVI to sleep
				sleeperNAVI->goToSleep();//will put NAVI to sleep (MAIN will wake up NAVI externally)			
				
				//Don't switch states yet. Go to sleep in the current TX_COMMUNICATIONS state.

			//WAKING UP
				//MAIN will wake up NAVI from the sleep.
				sleeperNAVI->hasAwoken();//This updates the status and detaches the interrupt for NAVI once NAVI is awaken externally by MAIN.
				
				delay(100);// let everybody get up and running for a sec

				//Run wake up tasks. (i.e. begin SW serial as needed, etc.)
					//Note: Make sure to begin (again) any Software Serial here
					//No SW Serials used for NAVI
					//Do nothing for now. Place holder.
					
					
				_PRINT_SLEEPING_AND_WAKEUP_STATUS_(F("NAVI_Wake"));//output to PC for debug
										
				//While in the SYSTEM_WAKING mode, after going to RUN_HOUSEKEEPING_TASKS, it will go to the next state, which is set to CONTROL_OUTPUTS

				
			break;			
		default: //default state
//TEMPLATE		
			 //This code should never execute, if it does, there is a logical or programming error			
			runModeFunction_default();//no state needed, all states do the same thing
			break;

	}//end switch


}//end of runModeFunction_SYSTEM_SLEEPING()
void runModeFunction_SYSTEM_WAKING(byte currentState)
{
	_PRINT_MODE_(F("MODE: SYSTEM_WAKING"));

//LEFT OFF HERE
//WRITE ME LATER


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
		case PLAN_ROUTE: //Mode: SYSTEM_WAKING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;			
		case OBJECT_AVOIDANCE: //Mode: SYSTEM_WAKING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case CONTROL_OUTPUTS: //Mode: SYSTEM_WAKING
		
			//Since Navigation is skipped for SYSTEM_WAKING, set default values for motors and gimbal here at the CONTROL_OUTPUTS state

			//Set motor and gimbal to default values
			motor_turn_value = SET_GO_STRAIGHT;
			motor_speed_value = SET_STOP_SPEED;
			gimbal_pan_value = SET_CENTER_PAN;
			gimbal_tilt_value = SET_MIDDLE_TILT;
			
			//turn buffer select to non-remote (local) control
			BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_);//buffer_remote_ctrl_selected = false 
				
			drive_setting = AUTONOMOUS_DRIVE;//since it's at SYSTEM_WAKING and the rover should have control
							

			//Control Buffer Select
			//if buffer_remote_ctrl_selected == true
			if( BooleanBitFlags::flagIsSet(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_))
			{
				#ifdef _DEBUG_OUTPUT_DRIVE_SELECTION_STATUS
					_SERIAL_DEBUG_CHANNEL_.println(F("MANUAL DRIVE"));
				#endif
				roverBuffer->driverMode(MANUAL_DRIVE);
			}//end if
			//buffer_remote_ctrl_selected == false
			else
			{
				#ifdef _DEBUG_OUTPUT_DRIVE_SELECTION_STATUS
					_SERIAL_DEBUG_CHANNEL_.println(F("AUTO DRIVE"));
				#endif
				roverBuffer->driverMode(AUTO_DRIVE);
				
				//When in auto drive, control the motors and the gimbal
				
				//Control Motor Controller's Turn			
				motorControllerSetSteering(motor_turn_value);//Should be motor_turn_value = SET_GO_STRAIGHT

				//Control Motor Controller's Speed			
				motorControllerSetThrottle(motor_speed_value);//Should be motor_speed_value = SET_STOP_SPEED			

				//Control Gimbal Controller's Pan			
				gimbalSetPan(gimbal_pan_value);//Should be gimbal_pan_value = SET_CENTER_PAN

				//Control Gimbal Controller's Tilt			
				gimbalSetTilt(gimbal_tilt_value);//Should be gimbal_tilt_value = SET_MIDDLE_TILT

			
			}//end else

				
			//LEDs will be controlled by RUN_HOUSEKEEPING_TASKS (i.e. runBackgroundTasks()) since it requires attention with every loop
			
			//The Ultrasonic's trigger will be controlled when the sensor is read, since the trigger is part of the reading process		
		
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
	
//TEMPLATE		
			 //This code should never execute, if it does, there is a logical or programming error			
			runModeFunction_default();//no state needed, all states do the same thing
			break;

	}//end switch


}//end of runModeFunction_SYSTEM_WAKING()
void runModeFunction_SW_RESETTING(byte currentState)
{
	_PRINT_MODE_(F("MODE: SW_RESETTING"));
//LEFT OFF HERE
//WRITE ME LATER


	switch (currentState)
	{
		case RUN_HOUSEKEEPING_TASKS: //Mode: SW_RESETTING
			runBackgroundTasks();
			break;
		case RX_COMMUNICATIONS: //Mode: SW_RESETTING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case DATA_VALIDATION: //Mode: SW_RESETTING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case DATA_FILTER: //Mode: SW_RESETTING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;	
		case READ_INPUTS: //Mode: SW_RESETTING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case PROCESS_DATA: //Mode: SW_RESETTING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;
		case PLAN_ROUTE: //Mode: SW_RESETTING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;			
		case OBJECT_AVOIDANCE: //Mode: SW_RESETTING
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;					
		case CONTROL_OUTPUTS: //Mode: SW_RESETTING
		
			//Since Navigation is skipped for SYNCHRONIZATION, set default values for motors and gimbal here at the CONTROL_OUTPUTS state

			//turn buffer select to non-remote (local) control
			BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_);//buffer_remote_ctrl_selected = false 

			drive_setting = AUTONOMOUS_DRIVE;//since it's at SW_RESETTING and the rover should have control
				
			//Set motor and gimbal to default values
			motor_turn_value = SET_GO_STRAIGHT;
			motor_speed_value = SET_STOP_SPEED;
			gimbal_pan_value = SET_CENTER_PAN;
			gimbal_tilt_value = SET_MIDDLE_TILT;

			//Control Buffer Select
			//if buffer_remote_ctrl_selected == true
			if( BooleanBitFlags::flagIsSet(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_))
			{
				#ifdef _DEBUG_OUTPUT_DRIVE_SELECTION_STATUS
					_SERIAL_DEBUG_CHANNEL_.println(F("MANUAL DRIVE"));
				#endif
				roverBuffer->driverMode(MANUAL_DRIVE);
			}//end if
			//buffer_remote_ctrl_selected == false
			else
			{
				#ifdef _DEBUG_OUTPUT_DRIVE_SELECTION_STATUS
					_SERIAL_DEBUG_CHANNEL_.println(F("AUTO DRIVE"));
				#endif
				roverBuffer->driverMode(AUTO_DRIVE);
				
				//When in auto drive, control the motors and the gimbal
				
				//Control Motor Controller's Turn			
				motorControllerSetSteering(motor_turn_value);//Should be motor_turn_value = SET_GO_STRAIGHT

				//Control Motor Controller's Speed			
				motorControllerSetThrottle(motor_speed_value);//Should be motor_speed_value = SET_STOP_SPEED			

				//Control Gimbal Controller's Pan			
				gimbalSetPan(gimbal_pan_value);//Should be gimbal_pan_value = SET_CENTER_PAN

				//Control Gimbal Controller's Tilt			
				gimbalSetTilt(gimbal_tilt_value);//Should be gimbal_tilt_value = SET_MIDDLE_TILT

			
			}//end else

				
			//LEDs will be controlled by RUN_HOUSEKEEPING_TASKS (i.e. runBackgroundTasks()) since it requires attention with every loop
			
			//The Ultrasonic's trigger will be controlled when the sensor is read, since the trigger is part of the reading process						
		
			break;
		case CREATE_DATA: //Mode: SW_RESETTING

			//Creates data for PC_USB
			if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_PC_USB, PC_USB_MSG_QUEUE);
				
				//skip auto data	
				
			}//end if
			
			
			//Creates data for MAIN (primary queue)
			if (main_pri_msg_queue != CMD_TAG_NO_MSG)
			{
			
				if(pri_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_COMM)//data is for COMM
				{
					createDataFromQueueFor(ROVERCOMM_COMM, PRIMARY_MSG_QUEUE);
				}//end if
				else if(pri_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_CMNC) //data is for CMNC
				{
					createDataFromQueueFor(ROVERCOMM_CMNC, PRIMARY_MSG_QUEUE);
				}//end else if
				else if(pri_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_MAIN) //data is for MAIN
				{
					createDataFromQueueFor(ROVERCOMM_MAIN, PRIMARY_MSG_QUEUE);
				}//end else if
				else if(pri_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_AUXI) //data is for AUXI
				{
					createDataFromQueueFor(ROVERCOMM_AUXI, PRIMARY_MSG_QUEUE);
				}//end else if
				else//invalid state, error out
				{
					_SERIAL_DEBUG_CHANNEL_.println(F("ErrUnkDest"));//error, unknown destination
				}//end else
				
				
								
			}//end if
										
			//skip auto data for SW_RESETTING
						
			//skip second message queue for SW_RESETTING					
		
		
			break;
		case TX_COMMUNICATIONS: //Mode: SW_RESETTING
		
			//Note: There are no redirections for the NAVI Arduino since it is a node at the end of the network tree.

			//1. Sends data to PC_USB
			if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
			{
				txData(txMsgBuffer_PC_USB, ROVERCOMM_PC_USB);
			}//end if
			//2. Sends data to MAIN (primary queue)
			if (main_pri_msg_queue != CMD_TAG_NO_MSG)
			{
				txData(txMsgBuffer_Pri_MAIN, ROVERCOMM_MAIN);//Note: This just sends the data as created through the MAIN channel. Whether it goes to COMM, CMNC, MAIN, or AUXI that would be determined in the createDataFromQueueFor().
			}//end if
			
			//Only the primary message queue is sent (the system ready msg to MAIN), and everything else can be ignored since the system is still synching up.
			
			//3. Clears message queue(s)
			pc_usb_msg_queue = CMD_TAG_NO_MSG;
			main_pri_msg_queue = CMD_TAG_NO_MSG;
			main_sec_msg_queue = CMD_TAG_NO_MSG;
			pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;//default to MAIN
			sec_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;//default to MAIN			
						
			//4. Reset the first transmission flag
			BooleanBitFlags::setFlagBit(flagSet_SystemStatus1, _BTFG_FIRST_TRANSMISSION_);						
			//Note: If MAIN misses this message, MAIN will go into SW reset error and re-request for a SW reset			
			
			//Troubleshooting tip: If MAIN keeps missing this message, can send it twice through the main_pri_msg_queue and then the main_sec_msg_queue as well.

			currentMode = INITIALIZATION;//Set mode to INITIALIZATION *begin*		
			//By Default: The next state is RX_COMMUNICATIONS	
	
			break;			
		default: //default state
//TEMPLATE		
			 //This code should never execute, if it does, there is a logical or programming error			
			runModeFunction_default();//no state needed, all states do the same thing
			break;
	}//end switch

}//end of runModeFunction_SW_RESETTING()
void runModeFunction_SYSTEM_ERROR(byte currentState)
{
	_PRINT_MODE_(F("MODE: SYSTEM_ERROR"));

//LEFT OFF HERE
//WRITE ME LATER


	switch (currentState)
	{
		case RUN_HOUSEKEEPING_TASKS: //Mode: SYSTEM_ERROR
//WRITE LATER
			break;
		case RX_COMMUNICATIONS: //Mode: SYSTEM_ERROR
		
			//rxData() from PC_USB
			//1. Reset status flag
			ch1Status = DATA_STATUS_NOT_READY;
			//2. Clear all Rx'ed data before getting new data				
			roverComm_Ch1->clearRxData();
			//3. Receive data
			ch1Status = rxData(roverComm_Ch1, ROVERCOMM_PC_USB);//Note: this is a local .ino function

			//rxData() from MAIN
			//1. Reset status flag
			ch2Status = DATA_STATUS_NOT_READY;
			//2. Clear all Rx'ed data before getting new data				
			roverComm_Ch2->clearRxData();
			//3. Receive data
			ch2Status = rxData(roverComm_Ch2, ROVERCOMM_MAIN);//Note: this is a local .ino function
		
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
		case DATA_FILTER: //Mode: SYSTEM_ERROR


			//Reset/clear flags (no data was for NAVI)
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_NAVI_CH1_);
			BooleanBitFlags::clearFlagBit(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_NAVI_CH2_);
				
			//Set Command Filter Options
			//First initialize all command choices to false
			setAllCommandFiltersTo(false, ROVERCOMM_PC_USB);//for PC_USB
			setAllCommandFiltersTo(false, ROVERCOMM_MAIN);//for MAIN
			
			//Then enable the allowed commands for this mode:
			//For PC_USB
			//No filter on PC_USB data. (Allow all data from PC_USB)
			//No commands from PC_USB are filtered, so set all to true.
			setAllCommandFiltersTo(true, ROVERCOMM_PC_USB);			
			//For MAIN
			//Flag Set 1
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_NAVISWRESETREQUEST_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet1_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_);
			//Flag Set 2
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETDRIVESETTING_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SETDRIVESETTING_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORPOWERSTATUS_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SETMIDRIGHTENCODERSTATUS_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SETMIDLEFTENCODERSTATUS_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet2_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SETHEADING_);
			
			//Flag Set 3
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet3_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETGIMBALPANSTATUS_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet3_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETGIMBALTILTSTATUS_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet3_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORSPEED_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet3_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETMOTORSPEEDSTATUS_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet3_MAIN, _BTFG_COMMAND_ENABLE_OPTION_SETMOTORTURN_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet3_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETMOTORTURNSTATUS_);
			//Flag Set 4
			//None
			//Flag Set 5
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet5_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETLATITUDE_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet5_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETLONGITUDE_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet5_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETGPSFIXQUALITY_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet5_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETGPSSATELLITESTRACKED_);
			//Flag Set 6
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet6_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCEFORWARDLEFT_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet6_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCEFORWARDCENTER_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet6_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCEFORWARDRIGHT_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet6_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCESIDERIGHT_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet6_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCESIDELEFT_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet6_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCEREARCENTER_);
			//Flag Set 7
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet7_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETIRDISTANCEFORWARDCENTERSTATUS_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet7_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETIRDISTANCESIDERIGHTSTATUS_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet7_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETIRDISTANCESIDELEFTSTATUS_);
			BooleanBitFlags::setFlagBit(commandFilterOptionsSet7_MAIN, _BTFG_COMMAND_ENABLE_OPTION_GETIRDISTANCEREARCENTERSTATUS_);
			
		
			//Transmit data and/or execute command
						
			//For data from PC_USB, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, NAVI
			if (ch1Status == DATA_STATUS_VALID)
			{
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//Note: There are no redirections for the NAVI Arduino since it is a node at the end of the network tree.
				//Note: this is a local .ino function

				dataDirector(roverDataCh1_COMM, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_NAVI_CH1_);//DataDirection will set the "data was for NAVI flag" to true if it was for this Arduino

				/*
				Allow all data from PC_USB.
				*/

			}//end if

			//For data from MAIN, transmit the data to it's proper destination if it was meant for another Arduino
			//or take any actions if the data was meant for this unit, NAVI
			if (ch2Status == DATA_STATUS_VALID)
			{
			
				//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
				//Note: There are no redirections for the NAVI Arduino since it is a node at the end of the network tree.
				//Note: this is a local .ino function

				dataDirector(roverDataCh2_COMM, flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_NAVI_CH2_);//DataDirection will set the "data was for NAVI flag" to true if it was for this Arduino
				
				/*
				Set filter to throw away all MAIN data except:

				*/				

			}//end if		
				
		
		
		
			break;	
		case READ_INPUTS: //Mode: SYSTEM_ERROR

	
			//Read All Ultrasonic Distance Sensors
				//Note: The Ultrasonic's trigger will implicitly be controlled when the sensor is read, since the trigger is part of the reading process	
			for (byte i = 0; i < ULTRASONIC_SENSORS_ARRAY_SIZE; i++)
			{
				uSonDistanceMeasured[i] = uSonSensors[i]->getDistance(UNIT_CM);//store the ultrasonic's distance in the corresponding spot in the uSonDistanceMeasured[] array
			}//end for
			
			//Read IR Distance Sensors
			for (byte i = 0; i < INFRARED_SENSORS_ARRAY_SIZE; i++)
			{
				irDistanceMeasured[i] = irDistanceSensors[i]->getDistance(UNIT_CM);//store the ultrasonic's distance in the corresponding spot in the irDistanceMeasured[] array
			}//end for

				
			//Read NAVI Wheel Encoders
			for (byte i = 0; i < NAVI_WHEEL_ENCODERS_SENSORS_ARRAY_SIZE; i++)
			{
			
					allWheelEncodersDirection[i] = naviWheelEncoders[i]->getDirection();//As defined in RoverConfig.h under "//Motor Directions"
					allWheelEncodersFootage[i] = naviWheelEncoders[i]->getFootage();//distance travelled in feet
					allWheelEncodersSpeed[i] = naviWheelEncoders[i]->getSpeed();//in inches per second

			}//end for		
			//Note: For the MAIN Encoders, the mid right and mid left data will be received through serial communication from MAIN and stored. See commandDirector().
			
			
			//Read GPS
			//Get samples of actual GPS coordinates

			if(rxGPSData(roverGps))//Receive (via serial) and process gps data
			{
				#ifdef _PRINT_GPS_DATA_STATUS
					_SERIAL_DEBUG_CHANNEL_.println(F("GPS Data Valid"));
				#endif
				BooleanBitFlags::setFlagBit(flagSet_SystemStatus1, _BTFG_GPS_DATA_READY_);
			 }//end if
			else//Else notify that the GPS data isn't ready
			{
				#ifdef _PRINT_GPS_DATA_STATUS
					_SERIAL_DEBUG_CHANNEL_.println(F("GPS Data Not Ready"));
				#endif		
				BooleanBitFlags::clearFlagBit(flagSet_SystemStatus1, _BTFG_GPS_DATA_READY_);
			}//end else
		
			break;
		case PROCESS_DATA: //Mode: SYSTEM_ERROR

			#ifdef _DEBUG_PRINT_TIMEOUT_COUNTER_VALUE_
				Serial.println(timeout_counter);//DEBUG
			#endif
			
			
			//Run lower priority functions here.
			//These messages and flags may be overrided with commandDirector()			

			//Process PC_USB command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//All other messages are allowed from PC_USB. Use with caution.
				//Note: There are no redirections for the NAVI Arduino since it is a node at the end of the network tree.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_NAVI_CH1_))//If there was data from PC_USB (Ch1), and it was for NAVI
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh1_COMM, ROVERCOMM_PC_USB);
			}//end if			
			//Process MAIN command/data to see if it has priority or is non-conflicting (see "Command Options" below for more info)
				//All messages are allowed from MAIN.
				//Note: There are no redirections for the NAVI Arduino since it is a node at the end of the network tree.
			if (BooleanBitFlags::flagIsSet(flagSet_MessageControl1, _BTFG_DATA_WAS_FOR_NAVI_CH2_))//If there was data from MAIN (Ch2), and it was for NAVI
			{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
				commandDirector(roverDataCh2_COMM, ROVERCOMM_MAIN);
			}//end if				

			

			//Process ultrasonic distance sensors
				//Note: Nothing else needed to process for ultrasonics. It's already taken care of in the READ_INPUTS state
			//Process ir distance sensors
				//Note: Nothing else needed to process for ir distance sensors. It's already taken care of in the READ_INPUTS state
			//Process heading (for AUXI-external)
			
			//If Heading data is ready and valid
			 if(BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_HEADING_DATA_READY_))
			 {
				processHeading(tempHeadingData);
			 }//end if
			 //else do nothing since the data is invalid

			//Process motor power status (for MAIN-external)
				//Note: Nothing else needed to process for the motor power status. It's already taken care of by the commandDirector() in this PROCESS_DATA state.
			
			//Process wheel encoders (for MAIN-external and for NAVI-internal)			
				//Note: Nothing else needed to process for the NAVI wheel encoders. It's already taken care of in the READ_INPUTS state
				//Note: Nothing else needed to process for the MAIN wheel encoders. It's already taken care of by the commandDirector() in this PROCESS_DATA state.
			
			//Process GPS		
			//When GPS data is ready and valid
			if( BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_GPS_DATA_READY_) )
			{
				//save the lat and long data into the array, which will later be sorted and the median will be extracted
				processGPS(roverGps->getGpsLatitude(DEC_DEG), roverGps->getGpsLongitude(DEC_DEG));//where the latitude and longitude are in decimal degrees
			}//end if
			//else do nothing since the data is invalid
			
		
			//Run highest priority functions here (after command director). //this will override any lower priority messages (i.e. system go). This will overwrite anything else. (i.e. system ready)
		

		
			//Recreate/regenerate any error messages (but allow them to be overwritten by higher priority messages)
			//Improvement Tip: Maybe can send NAVI and AUXI the error messages as well so they can react to it. But for now good enough.
			if(BooleanBitFlags::flagIsSet(flagSet_Error1, _BTFG_SYNC_ERROR_))
			{
				//(Note: the sync_error flag can only be cleared with a sw reset or hw reset)		
				pc_usb_msg_queue = CMD_TAG_SYNC_ERROR_STATUS;
			
			
				if( error_origin != ROVERCOMM_MAIN)//Make sure don't send it back to itself to avoid an infinite loop
				{
					 main_pri_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//send a generic system error to main which will send a copy to comm, then to cmnc as well (MAIN only accepts generic health and generic system errors at the moment. Also only generic health and generic system errors are usually left unfiltered in many states like SYNCHRONIZATION. else you have to send a message that should redirect to cmnc directly, but it would bypass MAIN and won't error MAIN out. Sometimes you want MAIN to error out on any error.)
					 
					 pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;
				}//end if
			}//end if				
			else if(BooleanBitFlags::flagIsSet(flagSet_Error1, _BTFG_SW_RESET_ERROR_))//if sw_reset_error == true
			{						
				pc_usb_msg_queue = CMD_TAG_SW_RESET_ERROR_STATUS; //send error out through the PC_USB for debugging
				
				if( error_origin != ROVERCOMM_MAIN)//Make sure don't send it back to itself to avoid an infinite loop
				{
					 main_pri_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//send a generic system error to main which will send a copy to comm, then to cmnc as well (MAIN only accepts generic health and generic system errors at the moment. Also only generic health and generic system errors are usually left unfiltered in many states like SYNCHRONIZATION. else you have to send a message that should redirect to cmnc directly, but it would bypass MAIN and won't error MAIN out. Sometimes you want MAIN to error out on any error.)
					 
					 pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;
				}																		
				
				//(Note: the sw_reset_error flag can only be cleared with a hw reset)
				
				//Troubleshooting tip, if it's a sw_reset_error, it will need a HW reset. But SYSTEM_ERROR will allow for both sw and hw resets because it's designed to handle any errors in general. So the user will have to know to send a HW reset in order to clear a SW reset error.
				
			}//end else if
			else if( BooleanBitFlags::flagIsSet(flagSet_Error1, _BTFG_SLEEPING_ERROR_) )//if sleeping_error == true 
			{
			
				pc_usb_msg_queue = CMD_TAG_SLEEP_ERROR_STATUS; //send error out through the PC_USB for debugging

				if( error_origin != ROVERCOMM_MAIN)//Make sure don't send it back to itself to avoid an infinite loop
				{
					 main_pri_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//send a generic system error to main which will send a copy to comm, then to cmnc as well (MAIN only accepts generic health and generic system errors at the moment. Also only generic health and generic system errors are usually left unfiltered in many states like SYNCHRONIZATION. else you have to send a message that should redirect to cmnc directly, but it would bypass MAIN and won't error MAIN out. Sometimes you want MAIN to error out on any error.)
 
					pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;
				}						
				//(Note: the sleeping_error flag can only be cleared with a sw reset or hw reset)				
				
			}//end else if
			else if( BooleanBitFlags::flagIsSet(flagSet_Error1, _BTFG_INVALID_STATE_OR_MODE_ERROR_) )//if invalid_state_or_mode_error == true
			{
			
				pc_usb_msg_queue = CMD_TAG_INVALID_STATE_OR_MODE_ERROR_STATUS;
				
				if( error_origin != ROVERCOMM_MAIN)//Make sure don't send it back to itself to avoid an infinite loop
				{
					 main_pri_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//to be sent to COMM (first), which will process it, then send a copy to CMNC
					 
					 pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_COMM;
				}						
				
				//(Note: the invalid_state_or_mode_error flag can only be cleared with a sw reset or hw reset)
				
			}//end else if
			else if( BooleanBitFlags::flagIsSet(flagSet_Error1, _BTFG_GENERIC_HEALTH_ERROR_) )//if generic_health_error == true
			{
				pc_usb_msg_queue = CMD_TAG_GENERIC_HEALTH_STATUS_ERROR; //send error out through the PC_USB for debugging

				if( error_origin != ROVERCOMM_MAIN)//Make sure don't send it back to itself to avoid an infinite loop
				{
					main_pri_msg_queue = CMD_TAG_GENERIC_HEALTH_STATUS_ERROR;//to be sent to COMM (first), which will process it, then send a copy to CMNC
					
					pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_COMM;
				}						
				
				//(Note: the generic_health_error flag can only be cleared with a sw reset or hw reset)				
								
			}//end else if				
			else if( BooleanBitFlags::flagIsSet(flagSet_Error1, _BTFG_GENERIC_SYSTEM_ERROR_) )//if generic_system_error == true
			{
				pc_usb_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS; //send error out through the PC_USB for debugging
				
				if( error_origin != ROVERCOMM_MAIN)//Make sure don't send it back to itself to avoid an infinite loop
				{
					main_pri_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//to be sent to COMM (first), which will process it, then send a copy to CMNC
					
					pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_COMM;
				}						

				//(Note: the generic_system_error flag can only be cleared with a sw reset or hw reset)
				
			}//end else if	
			else//default: set to generic_system_error
			{
				//Set generic_system_error = true
				BooleanBitFlags::setFlagBit(flagSet_Error1, _BTFG_GENERIC_SYSTEM_ERROR_);
				//(Note: the generic_system_error flag can only be cleared with a sw reset or hw reset)
				
				pc_usb_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS; //send error out through the PC_USB for debugging
				
				if( error_origin != ROVERCOMM_MAIN)//Make sure don't send it back to itself to avoid an infinite loop
				{
					main_pri_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//to be sent to COMM (first), which will process it, then send a copy to CMNC
					
					pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_COMM;
				}							
			}//end else	
			break;
		case PLAN_ROUTE: //Mode: SYSTEM_ERROR
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;			
		case OBJECT_AVOIDANCE: //Mode: SYSTEM_ERROR
			//Nothing to do here.
			//Keep as a place holder. (also to define the state so it doesn't go into default and then error out)
			break;					
		case CONTROL_OUTPUTS: //Mode: SYSTEM_ERROR

			//Since Navigation is skipped for SYNCHRONIZATION, set default values for motors and gimbal here at the CONTROL_OUTPUTS state

			//turn buffer select to non-remote (local) control
			BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_);//buffer_remote_ctrl_selected = false 
				
			//Set motor and gimbal to default values
			motor_turn_value = SET_GO_STRAIGHT;
			motor_speed_value = SET_STOP_SPEED;
			gimbal_pan_value = SET_CENTER_PAN;
			gimbal_tilt_value = SET_MIDDLE_TILT;

			//Control Buffer Select
			//if buffer_remote_ctrl_selected == true
			if( BooleanBitFlags::flagIsSet(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_))
			{
				#ifdef _DEBUG_OUTPUT_DRIVE_SELECTION_STATUS
					_SERIAL_DEBUG_CHANNEL_.println(F("MANUAL DRIVE"));
				#endif
				roverBuffer->driverMode(MANUAL_DRIVE);
			}//end if
			//buffer_remote_ctrl_selected == false
			else
			{
				#ifdef _DEBUG_OUTPUT_DRIVE_SELECTION_STATUS
					_SERIAL_DEBUG_CHANNEL_.println(F("AUTO DRIVE"));
				#endif
				roverBuffer->driverMode(AUTO_DRIVE);
				
				//When in auto drive, control the motors and the gimbal
				
				//Control Motor Controller's Turn			
				motorControllerSetSteering(motor_turn_value);//Should be motor_turn_value = SET_GO_STRAIGHT

				//Control Motor Controller's Speed			
				motorControllerSetThrottle(motor_speed_value);//Should be motor_speed_value = SET_STOP_SPEED			

				//Control Gimbal Controller's Pan			
				gimbalSetPan(gimbal_pan_value);//Should be gimbal_pan_value = SET_CENTER_PAN

				//Control Gimbal Controller's Tilt			
				gimbalSetTilt(gimbal_tilt_value);//Should be gimbal_tilt_value = SET_MIDDLE_TILT

			
			}//end else

				
			//LEDs will be controlled by RUN_HOUSEKEEPING_TASKS (i.e. runBackgroundTasks()) since it requires attention with every loop
			
			//The Ultrasonic's trigger will be controlled when the sensor is read, since the trigger is part of the reading process					
		
			break;
		case CREATE_DATA: //Mode: SYSTEM_ERROR

		
			//Creates data for PC_USB
			if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
			{
				createDataFromQueueFor(ROVERCOMM_PC_USB, PC_USB_MSG_QUEUE);
				
				//skip auto data	
				
			}//end if
			
			
			//Creates data for MAIN (primary queue)
			if (main_pri_msg_queue != CMD_TAG_NO_MSG)
			{
			
				if(pri_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_COMM)//data is for COMM
				{
					createDataFromQueueFor(ROVERCOMM_COMM, PRIMARY_MSG_QUEUE);
				}//end if
				else if(pri_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_CMNC) //data is for CMNC
				{
					createDataFromQueueFor(ROVERCOMM_CMNC, PRIMARY_MSG_QUEUE);
				}//end else if
				else if(pri_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_MAIN) //data is for MAIN
				{
					createDataFromQueueFor(ROVERCOMM_MAIN, PRIMARY_MSG_QUEUE);
				}//end else if
				else if(pri_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_AUXI) //data is for AUXI
				{
					createDataFromQueueFor(ROVERCOMM_AUXI, PRIMARY_MSG_QUEUE);
				}//end else if
				else//invalid state, error out
				{
					_SERIAL_DEBUG_CHANNEL_.println(F("ErrUnkDest"));//error, unknown destination
				}//end else
								
			}//end if
			//Auto data code for Primary Queue			
			else if( auto_NAVI_to_COMM_data_cnt < sizeof(auto_NAVI_to_COMM_data_array) )//if there is auto data for COMM and it has not been all sent yet
				//if there is auto data for COMM and it has not been all sent yet
				//Note: Since the counter is a byte, it's lowest value is 0. And the array size can't be smaller than zero. So this can only be true if the array has data, i.e. it's size is greater than 0 and the counter is less than the size of the array. If the array is empty, the size would be 0 and the counter's lowest value would be 0, so it would be equal and not less than, so the if statement would be still false.
			{
				//since there is no custom data, then send the next auto data.
					//create message corresponding to the next auto data for COMM.

					//Assign the next auto message to the queue
					main_pri_msg_queue = auto_NAVI_to_COMM_data_array[auto_NAVI_to_COMM_data_cnt];

					pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_COMM;
					
					//Create the message
					createDataFromQueueFor(ROVERCOMM_COMM, PRIMARY_MSG_QUEUE);
					
					//Loop/Increment the auto data for the next iteration
					auto_NAVI_to_COMM_data_cnt++;

					//Note: Though auto data increments now, preparing for the next iteration, the queue data was already assigned above and is "latched" or "locked" in for this iteration. As the queue and not the auto data is referred for the rest of this loop iteration.

			}//end else if
			else if ( auto_NAVI_to_CMNC_data_cnt < sizeof(auto_NAVI_to_CMNC_data_array) )//if there is auto data for CMNC and it has not been all sent yet
				//Note: Since the counter is a byte, it's lowest value is 0. And the array size can't be smaller than zero. So this can only be true if the array has data, i.e. it's size is greater than 0 and the counter is less than the size of the array. If the array is empty, the size would be 0 and the counter's lowest value would be 0, so it would be equal and not less than, so the if statement would be still false.			
			{
					//since there is no custom data, then send the next auto data.
					//create message corresponding to the next auto data for CMNC.

					//Assign the next auto message to the queue
					main_pri_msg_queue = auto_NAVI_to_CMNC_data_array[auto_NAVI_to_CMNC_data_cnt];

					pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_CMNC;
					
					//Create the message
					createDataFromQueueFor(ROVERCOMM_CMNC, PRIMARY_MSG_QUEUE);
					
					//Loop/Increment the auto data for the next iteration
					auto_NAVI_to_CMNC_data_cnt++;

					//Note: Though auto data increments now, preparing for the next iteration, the queue data was already assigned above and is "latched" or "locked" in for this iteration. As the queue and not the auto data is referred for the rest of this loop iteration.

			}//end else if
			else if ( auto_NAVI_to_MAIN_data_cnt < sizeof(auto_NAVI_to_MAIN_data_array) )//if there is auto data for MAIN and it has not been all sent yet
				//Note: Since the counter is a byte, it's lowest value is 0. And the array size can't be smaller than zero. So this can only be true if the array has data, i.e. it's size is greater than 0 and the counter is less than the size of the array. If the array is empty, the size would be 0 and the counter's lowest value would be 0, so it would be equal and not less than, so the if statement would be still false.			
			{
					//since there is no custom data, then send the next auto data.
					//create message corresponding to the next auto data for CMNC.

					//Assign the next auto message to the queue
					main_pri_msg_queue = auto_NAVI_to_MAIN_data_array[auto_NAVI_to_MAIN_data_cnt];

					pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_CMNC;
					
					//Create the message
					createDataFromQueueFor(ROVERCOMM_CMNC, PRIMARY_MSG_QUEUE);
					
					//Loop/Increment the auto data for the next iteration
					auto_NAVI_to_MAIN_data_cnt++;

					//Note: Though auto data increments now, preparing for the next iteration, the queue data was already assigned above and is "latched" or "locked" in for this iteration. As the queue and not the auto data is referred for the rest of this loop iteration.

			}//end else if				
			else if ( auto_NAVI_to_AUXI_data_cnt < sizeof(auto_NAVI_to_AUXI_data_array) )//if there is auto data for AUXI and it has not been all sent yet
				//Note: Since the counter is a byte, it's lowest value is 0. And the array size can't be smaller than zero. So this can only be true if the array has data, i.e. it's size is greater than 0 and the counter is less than the size of the array. If the array is empty, the size would be 0 and the counter's lowest value would be 0, so it would be equal and not less than, so the if statement would be still false.			
			{
					//since there is no custom data, then send the next auto data.
					//create message corresponding to the next auto data for CMNC.

					//Assign the next auto message to the queue
					main_pri_msg_queue = auto_NAVI_to_AUXI_data_array[auto_NAVI_to_AUXI_data_cnt];

					pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_CMNC;
					
					//Create the message
					createDataFromQueueFor(ROVERCOMM_CMNC, PRIMARY_MSG_QUEUE);
					
					//Loop/Increment the auto data for the next iteration
					auto_NAVI_to_AUXI_data_cnt++;

					//Note: Though auto data increments now, preparing for the next iteration, the queue data was already assigned above and is "latched" or "locked" in for this iteration. As the queue and not the auto data is referred for the rest of this loop iteration.

			}//end else if						
			//else do nothing since there was no message and no auto data to send
					
			
			
		
			//Creates data for MAIN (secondary queue)
			if (main_sec_msg_queue != CMD_TAG_NO_MSG)
			{
			
				if(sec_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_COMM)//data is for COMM
				{
					createDataFromQueueFor(ROVERCOMM_COMM, SECONDARY_MSG_QUEUE);
				}//end if
				else if(sec_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_CMNC) //data is for CMNC
				{
					createDataFromQueueFor(ROVERCOMM_CMNC, SECONDARY_MSG_QUEUE);
				}//end else if
				else if(sec_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_MAIN) //data is for MAIN
				{
					createDataFromQueueFor(ROVERCOMM_MAIN, SECONDARY_MSG_QUEUE);
				}//end else if
				else if(sec_comm_cmnc_main_auxi_destination_selection == ROVERCOMM_AUXI) //data is for AUXI
				{
					createDataFromQueueFor(ROVERCOMM_AUXI, SECONDARY_MSG_QUEUE);
				}//end else if
				else//invalid state, error out
				{
					_SERIAL_DEBUG_CHANNEL_.println(F("ErrUnkDest"));//error, unknown destination
				}//end else
								
			}//end if
			//Auto data code for Secondary Queue			
			else if( auto_NAVI_to_COMM_data_cnt < sizeof(auto_NAVI_to_COMM_data_array) )//if there is auto data for COMM and it has not been all sent yet
				//if there is auto data for COMM and it has not been all sent yet
				//Note: Since the counter is a byte, it's lowest value is 0. And the array size can't be smaller than zero. So this can only be true if the array has data, i.e. it's size is greater than 0 and the counter is less than the size of the array. If the array is empty, the size would be 0 and the counter's lowest value would be 0, so it would be equal and not less than, so the if statement would be still false.
			{
				//since there is no custom data, then send the next auto data.
					//create message corresponding to the next auto data for COMM.

					//Assign the next auto message to the queue
					main_sec_msg_queue = auto_NAVI_to_COMM_data_array[auto_NAVI_to_COMM_data_cnt];

					sec_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_COMM;
					
					//Create the message
					createDataFromQueueFor(ROVERCOMM_COMM, SECONDARY_MSG_QUEUE);
					
					//Loop/Increment the auto data for the next iteration
					auto_NAVI_to_COMM_data_cnt++;

					//Note: Though auto data increments now, preparing for the next iteration, the queue data was already assigned above and is "latched" or "locked" in for this iteration. As the queue and not the auto data is referred for the rest of this loop iteration.

			}//end else if
			else if ( auto_NAVI_to_CMNC_data_cnt < sizeof(auto_NAVI_to_CMNC_data_array) )//if there is auto data for CMNC and it has not been all sent yet
				//Note: Since the counter is a byte, it's lowest value is 0. And the array size can't be smaller than zero. So this can only be true if the array has data, i.e. it's size is greater than 0 and the counter is less than the size of the array. If the array is empty, the size would be 0 and the counter's lowest value would be 0, so it would be equal and not less than, so the if statement would be still false.			
			{
					//since there is no custom data, then send the next auto data.
					//create message corresponding to the next auto data for CMNC.

					//Assign the next auto message to the queue
					main_sec_msg_queue = auto_NAVI_to_CMNC_data_array[auto_NAVI_to_CMNC_data_cnt];

					sec_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_CMNC;
					
					//Create the message
					createDataFromQueueFor(ROVERCOMM_CMNC, SECONDARY_MSG_QUEUE);
					
					//Loop/Increment the auto data for the next iteration
					auto_NAVI_to_CMNC_data_cnt++;

					//Note: Though auto data increments now, preparing for the next iteration, the queue data was already assigned above and is "latched" or "locked" in for this iteration. As the queue and not the auto data is referred for the rest of this loop iteration.

			}//end else if
			else if ( auto_NAVI_to_MAIN_data_cnt < sizeof(auto_NAVI_to_MAIN_data_array) )//if there is auto data for MAIN and it has not been all sent yet
				//Note: Since the counter is a byte, it's lowest value is 0. And the array size can't be smaller than zero. So this can only be true if the array has data, i.e. it's size is greater than 0 and the counter is less than the size of the array. If the array is empty, the size would be 0 and the counter's lowest value would be 0, so it would be equal and not less than, so the if statement would be still false.			
			{
					//since there is no custom data, then send the next auto data.
					//create message corresponding to the next auto data for CMNC.

					//Assign the next auto message to the queue
					main_sec_msg_queue = auto_NAVI_to_MAIN_data_array[auto_NAVI_to_MAIN_data_cnt];

					sec_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_CMNC;
					
					//Create the message
					createDataFromQueueFor(ROVERCOMM_CMNC, SECONDARY_MSG_QUEUE);
					
					//Loop/Increment the auto data for the next iteration
					auto_NAVI_to_MAIN_data_cnt++;

					//Note: Though auto data increments now, preparing for the next iteration, the queue data was already assigned above and is "latched" or "locked" in for this iteration. As the queue and not the auto data is referred for the rest of this loop iteration.

			}//end else if				
			else if ( auto_NAVI_to_AUXI_data_cnt < sizeof(auto_NAVI_to_AUXI_data_array) )//if there is auto data for AUXI and it has not been all sent yet
				//Note: Since the counter is a byte, it's lowest value is 0. And the array size can't be smaller than zero. So this can only be true if the array has data, i.e. it's size is greater than 0 and the counter is less than the size of the array. If the array is empty, the size would be 0 and the counter's lowest value would be 0, so it would be equal and not less than, so the if statement would be still false.			
			{
					//since there is no custom data, then send the next auto data.
					//create message corresponding to the next auto data for CMNC.

					//Assign the next auto message to the queue
					main_sec_msg_queue = auto_NAVI_to_AUXI_data_array[auto_NAVI_to_AUXI_data_cnt];

					sec_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_CMNC;
					
					//Create the message
					createDataFromQueueFor(ROVERCOMM_CMNC, SECONDARY_MSG_QUEUE);
					
					//Loop/Increment the auto data for the next iteration
					auto_NAVI_to_AUXI_data_cnt++;

					//Note: Though auto data increments now, preparing for the next iteration, the queue data was already assigned above and is "latched" or "locked" in for this iteration. As the queue and not the auto data is referred for the rest of this loop iteration.

			}//end else if						
			//else do nothing since there was no message and no auto data to send
								
			

					
			//Once all the counters are equal to or greater than the size of the arrays (or even if the array is empty with size 0), reset all the counters)
			if (
				auto_NAVI_to_COMM_data_cnt >= sizeof(auto_NAVI_to_COMM_data_array) &&
				auto_NAVI_to_CMNC_data_cnt >= sizeof(auto_NAVI_to_CMNC_data_array) &&
				auto_NAVI_to_MAIN_data_cnt >= sizeof(auto_NAVI_to_MAIN_data_array) &&
				auto_NAVI_to_AUXI_data_cnt >= sizeof(auto_NAVI_to_AUXI_data_array)
				)
			{
				auto_NAVI_to_CMNC_data_cnt = 0;
				auto_NAVI_to_COMM_data_cnt = 0;
				auto_NAVI_to_MAIN_data_cnt = 0;
				auto_NAVI_to_AUXI_data_cnt = 0;
			}//end if
		
		
			break;
		case TX_COMMUNICATIONS: //Mode: SYSTEM_ERROR

			//Note: There are no redirections for the NAVI Arduino since it is a node at the end of the network tree.
	
			//Interweave primary transmissions and the secondary transmission, to allow the receiving end have time to process each incoming data
	
			if(BooleanBitFlags::flagIsSet(flagSet_SystemStatus1, _BTFG_FIRST_TRANSMISSION_))//check to see if this is the first transmission
			{		
			
				//1. Sends data to PC_USB
				if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
				{
					txData(txMsgBuffer_PC_USB, ROVERCOMM_PC_USB);
				}//end if
				//2. Sends data to MAIN (primary queue)
				if (main_pri_msg_queue != CMD_TAG_NO_MSG)
				{
					txData(txMsgBuffer_Pri_MAIN, ROVERCOMM_MAIN);//Note: This just sends the data as created through the MAIN channel. Whether it goes to COMM, CMNC, MAIN, or AUXI that would be determined in the createDataFromQueueFor().
				}//end if
				//3. Check to see if there are any second messages to send
				if ( main_sec_msg_queue != CMD_TAG_NO_MSG )		
				{
					BooleanBitFlags::clearFlagBit(flagSet_SystemStatus1, _BTFG_FIRST_TRANSMISSION_);//clear the flag
					//reset the counter before use
					transmission_delay_cnt = 0;
					queuedState = TX_COMMUNICATIONS;//override the default state (usually would be RX_COMMUNICATIONS)
				}//end if
				else//there is no second transmission, move on
				{					
					//clears message queue(s)
					pc_usb_msg_queue = CMD_TAG_NO_MSG;
					main_pri_msg_queue = CMD_TAG_NO_MSG;
					main_sec_msg_queue = CMD_TAG_NO_MSG;
					pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;//default to MAIN
					sec_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;//default to MAIN			
					//reset the first transmission flag
					BooleanBitFlags::setFlagBit(flagSet_SystemStatus1, _BTFG_FIRST_TRANSMISSION_);						
				}//end else					
			}//end if			
			else//this is not the first transmission
			{
					
				if(transmission_delay_cnt >= CONCURRENT_TRANSMISSION_DELAY) //once the desired delay has been reached, continue with the code
				{								
			
				
					txData(txMsgBuffer_Sec_MAIN, ROVERCOMM_MAIN);//Note: This just sends the data as created through the MAIN channel. Whether it goes to COMM, CMNC, MAIN, or AUXI that would be determined in the createDataFromQueueFor().
				
					//clears message queue(s)
					pc_usb_msg_queue = CMD_TAG_NO_MSG;
					main_pri_msg_queue = CMD_TAG_NO_MSG;
					main_sec_msg_queue = CMD_TAG_NO_MSG;
					pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;//default to MAIN
					sec_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;//default to MAIN			
					//reset the first transmission flag
					BooleanBitFlags::setFlagBit(flagSet_SystemStatus1, _BTFG_FIRST_TRANSMISSION_);
							
				}//end if
				else//the desired delay has not been reached yet, so just increment the count
				{
					transmission_delay_cnt++;
					queuedState = TX_COMMUNICATIONS;//override the default state (usually would be RX_COMMUNICATIONS)
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

	_PRINT_MODE_(F("MODE: default"));
	_SERIAL_DEBUG_CHANNEL_.println(F("UnExpErr"));//unexpected error
	//No switch case needed for the states, all states do the same thing
	
	main_pri_msg_queue = CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS;//to be sent to MAIN (first), which will process it, then sent to COMM (next), which will process it, and then send a copy to CMNC
 	pc_usb_msg_queue = CMD_TAG_INVALID_STATE_OR_MODE_ERROR_STATUS;
	
	pri_comm_cmnc_main_auxi_destination_selection = ROVERCOMM_MAIN;
			
	queuedState = CONTROL_OUTPUTS;
	currentMode = SYSTEM_ERROR;//Set mode to SYSTEM_ERROR *begin*		

	error_origin = ROVERCOMM_NAVI;

	
	//Set motor controller signals to stop and center
	motor_turn_value = SET_GO_STRAIGHT;
	motor_speed_value = SET_STOP_SPEED;

	//Set gimbal controller middle and center
	gimbal_pan_value = SET_CENTER_PAN;
	gimbal_tilt_value = SET_MIDDLE_TILT;

	//Set buffer select to remote control selected = false so the rover is in control of the emergency stop (but the SYSTEM_ERROR state will allow commands to override this if desired, and set it to manual)
	BooleanBitFlags::clearFlagBit(flagSet_SystemControls1, _BTFG_REMOTE_CTRL_SELECTED_);//buffer_remote_ctrl_selected = false 
					
	drive_setting = AUTONOMOUS_DRIVE;//since it's at SYSTEM_ERROR and the rover should have control
		
	
		
	//Set Invalid State Error Flag
	//Note: The Invalid State Error Flag can only be cleared with a sw reset or hw reset
	BooleanBitFlags::setFlagBit(flagSet_Error1, _BTFG_INVALID_STATE_OR_MODE_ERROR_);

	//initialize/reset shared counter before use
	timeout_counter = 0;

	
}//end of runStateFunction_default

 //====End of: Mode Functions
 //============End of Function Definitions






void InterruptDispatch_wheelEncoder_FrontLeft() {
	wheelEncoder_FrontLeft->isrUpdate();
}//end of InterruptDispatch_wheelEncoder_FrontLeft()
void InterruptDispatch_wheelEncoder_FrontRight() {
	wheelEncoder_FrontRight->isrUpdate();
}//end of InterruptDispatch_wheelEncoder_FrontRight()
void InterruptDispatch_wheelEncoder_RearLeft() {
	wheelEncoder_RearLeft->isrUpdate();
}//end of InterruptDispatch_wheelEncoder_RearLeft()
void InterruptDispatch_wheelEncoder_RearRight() {
	wheelEncoder_RearRight->isrUpdate();
}//end of InterruptDispatch_wheelEncoder_RearRight()
void InterruptDispatch_WakeUpArduino() {
	//Have to keep the ISR short else the program won't work
	sleeperNAVI->isrUpdate();//update the awake flag to reflect current status
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
	roverDataForNAVI = NULL;	
	roverDataForPC_USB = NULL;
	roverDataForMAIN = NULL;
	
}//end of clearRoverDataPointer()

void setRoverDataPointer(RoverData * roverDataPointer, byte roverCommType)
{

	//This sets the roverDataPointer to the desired roverCommType.
	//Note: This function can be called more than once to set more than one roverDataPointer to the same data (i.e. if the same data needs to be shared in multiple places)
	if (roverCommType == ROVERCOMM_PC_USB)
	{
		roverDataForPC_USB = roverDataPointer;
	}//end if
	else if (roverCommType == ROVERCOMM_COMM || roverCommType == ROVERCOMM_CMNC || roverCommType == ROVERCOMM_MAIN || roverCommType == ROVERCOMM_AUXI)//COMM, CMNC, MAIN, and AUXI all go through MAIN
	{
		roverDataForMAIN = roverDataPointer;
	}//end else if
	else//the roverCommType should be for this local Arduino (i.e. ROVERCOMM_MAIN)
	{
		roverDataForNAVI = roverDataPointer;
	}//end else
}//end of setRoverDataPointer()



void processHeading(double newHeading)
{

	headingArray[headingDataCounter] = newHeading;//assign the new heading into the heading array
	headingDataCounter++;//increment the global counter
	
	if( headingDataCounter >= _BUBBLESORT_MEDIAN_ARRAY_SIZE_ )//once all the samples have been collected for the median
	{
	
		headingDataCounter = 0;//reset the global counter
		
		double avgHeading = BubbleSort::getMedian(headingArray[0], headingArray[1], headingArray[2], headingArray[3], headingArray[4], headingArray[5], headingArray[6]);
		
		if(avgHeading >= 0.0 && avgHeading <= 360.0)//check to see that the heading value is within valid range
		{
			roverNavigation->setHeadingDeg(avgHeading);//set it to the actual/official heading value
			
			#ifdef _PRINT_IMU_MEDIAN_COMPLETED_STATUS
				_SERIAL_DEBUG_CHANNEL_.println(F("IMU Median Completed"));
			#endif
				BooleanBitFlags::setFlagBit(flagSet_SystemStatus1, _BTFG_ALL_HEADING_DATA_GATHERED_);//Set the status flag
		
		}//end if
		
		else
		{
		
			//do nothing and keep the last set value as is
			BooleanBitFlags::clearFlagBit(flagSet_SystemStatus1, _BTFG_ALL_HEADING_DATA_GATHERED_);//Set the status flag
			
		}
		
		
		
	}//end if
	
}//end of processHeading()





void processGPS(double newLatitude, double newLongitude)//where the latitude and longitude are in decimal degrees
{

	latitudeArray[gpsDataCounter] = newLatitude;//assign the new latitude into the latitude array
	longitudeArray[gpsDataCounter] = newLongitude;//assign the new longitude into the longitude array
	gpsDataCounter++;//increment the counter
	
	if( gpsDataCounter >= _BUBBLESORT_MEDIAN_ARRAY_SIZE_ )//once all the samples have been collected for the median
	{
	
		gpsDataCounter = 0;//reset the global counter
		
		double avgLatitude = BubbleSort::getMedian(latitudeArray[0], latitudeArray[1], latitudeArray[2], latitudeArray[3], latitudeArray[4], latitudeArray[5], latitudeArray[6]);//take the median value
		
		double avgLongitude = BubbleSort::getMedian(longitudeArray[0], longitudeArray[1], longitudeArray[2], longitudeArray[3], longitudeArray[4], longitudeArray[5], longitudeArray[6]);//take the median
		
		//check to see if both lat and long are within valid range
		if(( avgLatitude >= 0.0 && avgLatitude <= 90.0) && (avgLongitude >= -180.0 && avgLongitude <= 180.0 ))
		{
			roverNavigation->setLatitudeDeg(avgLatitude , TYPE_ACTUAL);//set it to the actual/official latitude value
			roverNavigation->setLongitudeDeg(avgLongitude, TYPE_ACTUAL);//set it to the actual/official longitude value
			
			
			#ifdef _PRINT_GPS_MEDIAN_COMPLETED_STATUS
				_SERIAL_DEBUG_CHANNEL_.println(F("GPS Median Completed"));
			#endif
			
			BooleanBitFlags::setFlagBit(flagSet_SystemStatus1, _BTFG_ALL_GPS_DATA_GATHERED_);//Set the status flag
		
		}//end if
		else
		{
		
			//throw the whole lat/long pair away (i.e. do nothing with it) and just keep the previous value
			BooleanBitFlags::clearFlagBit(flagSet_SystemStatus1, _BTFG_ALL_GPS_DATA_GATHERED_);//Set the status flag
			
		}
	}//end if			
	
}//end of processGPS()



boolean rxGPSData(RoverGpsSensor * roverGps) {

	//Note: Make sure processRxGPSData() is called between (before, after, or in) successive rxGPSData() function calls, as it will clear the string and reset the index (required for the code to work properly)


	byte numberOfAttempts = 0;//counts the number of times attempting to wait for a valid gps data string
	byte gpsCharactersToReceiveBeforeTimeout;//counts the number of characters received while waiting for the start of the gps data (i.e. $) before timing out
	boolean foundStart = false;
	boolean validGpsData = false;
	byte counter;


	while (numberOfAttempts <= GPS_RX_DATA_ATTEMPTS)
	{

		//Check availability of serial data
		if (_GPS_SERIAL_.available())
		{
			//initialize the counter
			gpsCharactersToReceiveBeforeTimeout = 0;
			//Wait for the GPS start of data (i.e. $) else for a time out
			do
			{
				if ((char)_GPS_SERIAL_.read() == '$')//look for the start of the GPS data (do NOT include it in the gps data string if found)
				{
					foundStart = true;
					delay(1);
					break;//break out of the loop since the header was found
				}
				delay(1);
			} while (gpsCharactersToReceiveBeforeTimeout <= GPS_SENTENCE_LENGTH);




			//If time-out has NOT occurred, keep processing the GPS data
			if (foundStart)
			{
				//initialize the counter
				counter = 0;

				//Gather the rest of the GPS String (AFTER the $, so $ is not included)
				while (_GPS_SERIAL_.available() && _GPS_SERIAL_.peek() != '$' && counter <= GPS_SENTENCE_LENGTH)//while there is still data on the Serial RX Buffer, another sentence has not started, and the length is not over the max GPS sentence length
				{


					//Read one character of serial data at a time
					//Note: Must type cast the _PC_USB_SERIAL_.Read to a char since not saving it to a char type first					

					roverGps->appendToRxGPSData((char)_GPS_SERIAL_.read());//construct the string one char at a time
																	  //DEBUG: Add as needed
					counter++;
					delay(1);//add a small delay between each transmission to reduce noisy and garbage characters


				}//end while



				 //Process and validate GPS Data
				validGpsData = roverGps->processRxGPSData();


				//If the received gps data is valid, return validGpsData and exit out of this function (no more trial attempts needed)
				if (validGpsData)
				{
					return validGpsData;
				}
				//else the GPS data was invalid, so make another attempt to find valid GPS data


			}//end if
			 //else if time out has occurred, go to the next trial		

		}//end if
		 //else if there is no serial data available do nothing, go to the next trial

		 //Increment trial counter
		numberOfAttempts++;

	}//end while

	 //Reached the max attempts to receive valid GPS Data
	return validGpsData;//If the code has reached this point, this value will be false. No valid GPS data found, and max attempts to find it has been reached.

}//end rxGPSData
