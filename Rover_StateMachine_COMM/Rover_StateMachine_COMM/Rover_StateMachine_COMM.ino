//Rover_StateMachine_COMM

//Configuration defines for #includes (must come before the #includes)
#define _ROVER_STATES_AND_MODES
#define _COMMAND_CREATION_DEFINITIONS
#define _ARD_4_COMM_H //Must define this before calling RoverConfig.h (either directly or through another header file), define this flag to turn on COMM definitions

//#includes
#include <RoverStatesAndModes.h>
#include <RoverCommandDefs.h>
#include <RoverConfig.h>
#include <SoftwareSerial.h>



//============Serial Debugging
//Used to output debugging messages only when the _DEBUG_COMM_BROADCAST flag is defined
//Uncomment the flag below in order to output debugging messages

//#define _DEBUG_COMM_BROADCAST

//Reference the "Where Left Off...txt" at: K:\Working Directory\DESIGN_PROJ\Design Projects\Robot\Workspaces\Arduino\2nd Gen Code\GitHub\arduino\Planning
#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_ //for COMM, either way it goes to the PC USB Serial
#else
	#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_
#endif
//============End of Serial Debugging





//============Global Declarations
//States
byte currentState = RUN_HOUSEKEEPING_TASKS;

//Modes
byte currentMode = POWER_ON_AND_HW_RESET;

//Message Queues
byte cmnc_msg_queue = CMD_TAG_NO_MSG; // (command tag, not boolean since use by CREATE_DATA to generate messages as well as TX_COMMUNICATIONS as a flag)
byte main_msg_queue = CMD_TAG_NO_MSG; // (command tag, not boolean since use by CREATE_DATA to generate messages as well as TX_COMMUNICATIONS as a flag)

//Flags - Error
boolean sync_error = false;
boolean secure_link_error = false;
boolean sw_reset_error = false;
boolean generic_health_error = false;
boolean sleeping_error = false;
//Flags - Message Controls
boolean redirectToCMNC = false;
boolean redirectToMAIN = false;
//Flags - Status
boolean main_system_ready = false;
boolean communications_secure = false;//(used to keep track is the communications link is already secure or not, and is useful for things like when going to sleep and waking back up and needing to synchronize again without needing to resecure the link)
boolean first_transmission = true;

//Counters
unsigned int timeout_counter = 0; //shared counter, used to detect timeout of MAIN responding back to COMM for any reason (i.e. system go or system ready responses), used to track how long COMM has been waiting for a COMM SW Request back from MAIN, after it sent a ALL_SW_RESET_REQUEST to MAIN (which MAIN might have missed, since it's sent only once), etc. Make sure to clear it out before use and only use it for one purpose at a time.
unsigned int transmission_delay_cnt = 0;//concurrent transmission delay counter


//Software Serial
SoftwareSerial _MAIN_SWSERIAL_(COMM_SW_UART_RX_PIN, COMM_SW_UART_TX_PIN);

//============End of Global Declarations





void setup() {


	//Serial Communications
	//Setup the HW_UART for communications between COMM and CMNC/PC USB
	_CMNC_SERIAL_.begin(CMNC_BAUD_RATE);
	//Setup the SW_UART for communications between COMM and MAIN
	_MAIN_SWSERIAL_.begin(MAIN_BAUD_RATE);

	

}//end of setup()


void loop() {
  
  
	  
  
  
  
  
  
  
}//end of loop()




//============Function Definitions


//============End of Function Definitions



