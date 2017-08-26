
#ifdef _ROVER_STATES_AND_MODES
	//State Definitions
	//Reference: K:\Working Directory\DESIGN_PROJ\Design Projects\Robot\Workspaces\Arduino\2nd Gen Code\GitHub\arduino\Pseudocode
	#define UNDEFINED_STATE									0
	#define RUN_HOUSEKEEPING_TASKS					1
	#define RX_COMMUNICATIONS							2
	#define DATA_VALIDATION									3
	#define DATA_FILTER											4
	#define READ_INPUTS											5
	#define SYSTEM_HEALTH										6
	#define PROCESS_DATA										7
	#define PLAN_ROUTE											8
	#define OBJECT_AVOIDANCE								9
	#define CONTROL_OUTPUTS								10
	#define CREATE_DATA											11
	#define TX_COMMUNICATIONS								12

	//Mode Definitions
	//Reference: K:\Working Directory\DESIGN_PROJ\Design Projects\Robot\Workspaces\Arduino\2nd Gen Code\GitHub\arduino\Pseudocode
	#define UNDEFINED_MODE									0
	#define POWER_ON_AND_HW_RESET					1
	#define INITIALIZATION										2
	#define SYNCHRONIZATION								3
	#define SECURING_LINK									4
	#define NORMAL_OPERATIONS							5
	#define HW_RESETTING										6
	#define SYSTEM_SLEEPING									7
	#define SYSTEM_WAKING									8
	#define SW_RESETTING										9
	#define SYSTEM_ERROR										10
	
#endif