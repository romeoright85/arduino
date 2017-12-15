//RoverCommandDefs.h
//Note: For some get and set statuses (when coming from and going to different arduinos), the command tags are shared so the list can remain compact. Else everything would require a tag for set and get and the list would be twice as long. As long as the get and set are in different ardunios, it can be shared. i.e. Get motor status is taken (get) from MAIN and saved (set) by NAVI.
	
	//Priority Levels
	#ifdef _COMMAND_CREATION_DEFINITIONS
		//Priority Levels
		#define CMD_PRI_LVL_0	0
		#define CMD_PRI_LVL_1	1
		#define CMD_PRI_LVL_2	2
		#define CMD_PRI_LVL_3	3		
		//Command Tags - Message Definitions
		//Reference: K:\Working Directory\DESIGN_PROJ\Design Projects\Robot\My Notes\Command Creator	
		#define CMD_TAG_NO_MSG     0
		#define CMD_TAG_DEBUG_OUTPUT_RXD_CMD     1
		#define CMD_TAG_DEBUG_HI_TEST_MSG     2
		#define CMD_TAG_DEBUG_BYE_TEST_MSG     3
		#define CMD_TAG_INVALID_CMD     4
		#define CMD_TAG_SYSTEM_READY_STATUS     5
		#define CMD_TAG_SYSTEM_GO_STATUS     6
		#define CMD_TAG_HW_IS_RESETTING     7
		#define CMD_TAG_COMM_HW_RESET_REQUEST     8
		#define CMD_TAG_MAIN_HW_RESET_REQUEST     9
		#define CMD_TAG_AUXI_HW_RESET_REQUEST     10
		#define CMD_TAG_NAVI_HW_RESET_REQUEST     11
		#define CMD_TAG_ALL_HW_RESET_REQUEST     12
		#define CMD_TAG_SW_IS_RESETTING_ACK     13
		#define CMD_TAG_COMM_SW_RESET_REQUEST     14
		#define CMD_TAG_MAIN_SW_RESET_REQUEST     15
		#define CMD_TAG_AUXI_SW_RESET_REQUEST     16
		#define CMD_TAG_NAVI_SW_RESET_REQUEST     17
		#define CMD_TAG_ALL_SW_RESET_REQUEST     18
		#define CMD_TAG_SW_RESET_ERROR_STATUS     19
		#define CMD_TAG_ESTABLISH_SECURE_LINK     20
		#define CMD_TAG_BREAK_SECURE_LINK     21
		#define CMD_TAG_SECURE_LINK_REQUEST     22
		#define CMD_TAG_PIR_STATUS     23
		#define CMD_TAG_SYSTEM_HOLD_REQUEST     24
		#define CMD_TAG_SYSTEM_STANDBY_REQUEST     25
		#define CMD_TAG_SYSTEM_IS_SLEEPING_ACK     26
		#define CMD_TAG_COMM_SLEEP_REQUEST     27
		#define CMD_TAG_MAIN_SLEEP_REQUEST     28
		#define CMD_TAG_AUXI_SLEEP_REQUEST     29
		#define CMD_TAG_NAVI_SLEEP_REQUEST     30
		#define CMD_TAG_ALL_SLEEP_REQUEST     31
		#define CMD_TAG_SLEEP_ERROR_STATUS     32
		#define CMD_TAG_COMM_WAKE_REQUEST     33
		#define CMD_TAG_MAIN_WAKE_REQUEST     34
		#define CMD_TAG_AUXI_WAKE_REQUEST     35
		#define CMD_TAG_NAVI_WAKE_REQUEST     36
		#define CMD_TAG_ALL_WAKE_REQUEST     37
		#define CMD_TAG_SYSTEM_IS_WAKING     38
		#define CMD_TAG_SYNC_ERROR_STATUS     39
		#define CMD_TAG_SECURE_LINK_ERROR_STATUS     40
		#define CMD_TAG_GENERIC_SYSTEM_ERROR_STATUS     41
		#define CMD_TAG_SET_MOTOR_POWER_ENABLE     42
		#define CMD_TAG_ENABLING_MTR_PWR     43
		#define CMD_TAG_DISABLING_MTR_PWR     44
		#define CMD_TAG_MTR_PWR_STATUS     45
		#define CMD_TAG_GET_GIMBAL_PAN_STATUS     163
		#define CMD_TAG_GIMBAL_PAN_STATUS     164
		#define CMD_TAG_GET_GIMBAL_TILT_STATUS     165
		#define CMD_TAG_GIMBAL_TILT_STATUS     166
		#define CMD_TAG_LATITUDE_REQUEST     167
		#define CMD_TAG_LONGITUDE_REQUEST     168
		#define CMD_TAG_LATITUDE_STATUS     169
		#define CMD_TAG_LONGITUDE_STATUS     170
		#define CMD_TAG_SET_LATITUDE_DEST     171
		#define CMD_TAG_SET_LONGITUDE_DEST     172
		#define CMD_TAG_ULTSNC_DISTANCE_FWD_LT_STATUS     173
		#define CMD_TAG_ULTSNC_DISTANCE_FWD_CTR_STATUS     174
		#define CMD_TAG_ULTSNC_DISTANCE_FWD_RT_STATUS     175
		#define CMD_TAG_ULTSNC_DISTANCE_SIDE_RT_STATUS     176
		#define CMD_TAG_ULTSNC_DISTANCE_SIDE_LT_STATUS     177
		#define CMD_TAG_ULTSNC_DISTANCE_REAR_CTR_STATUS     178
		#define CMD_TAG_GET_ULTSNC_DISTANCE_FWD_LT     179
		#define CMD_TAG_GET_ULTSNC_DISTANCE_FWD_CTR     180
		#define CMD_TAG_GET_ULTSNC_DISTANCE_FWD_RT     181
		#define CMD_TAG_GET_ULTSNC_DISTANCE_SIDE_RT     182
		#define CMD_TAG_GET_ULTSNC_DISTANCE_SIDE_LT     183
		#define CMD_TAG_GET_ULTSNC_DISTANCE_REAR_CTR     184
		#define CMD_TAG_INVALID_STATE_ERROR_STATUS     185		
	#endif	
