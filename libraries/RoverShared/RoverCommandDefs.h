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
		#define CMD_TAG_ENC_SET_STATUS_MID_LEFT     46
		#define CMD_TAG_ENC_SET_STATUS_MID_RIGHT     47
		#define CMD_TAG_ENC_STATUS_FRT_LEFT     48
		#define CMD_TAG_ENC_STATUS_FRT_RIGHT     49
		#define CMD_TAG_ENC_STATUS_MID_LEFT     50
		#define CMD_TAG_ENC_STATUS_MID_RIGHT     51
		#define CMD_TAG_ENC_STATUS_REAR_LEFT     52
		#define CMD_TAG_ENC_STATUS_REAR_RIGHT     53
		#define CMD_TAG_SET_HEADING     54
		#define CMD_TAG_SET_ROLL     55
		#define CMD_TAG_SET_PITCH     56
		#define CMD_TAG_SET_YAW     57
		#define CMD_TAG_HEADING_STATUS     58
		#define CMD_TAG_ROLL_STATUS     59
		#define CMD_TAG_PITCH_STATUS     60
		#define CMD_TAG_YAW_STATUS     61
		#define CMD_TAG_VOLTAGE_7D2_ACTUAL_STATUS     62
		#define CMD_TAG_VOLTAGE_7D2_ACTUAL_ERROR     63
		#define CMD_TAG_CURRENT_7D2_PRESW25A_ACTUAL_STATUS     64
		#define CMD_TAG_CURRENT_7D2_PRESW25A_ACTUAL_ERROR     65
		#define CMD_TAG_CURRENT_7D2_SW12D5A_ACTUAL_STATUS     66
		#define CMD_TAG_CURRENT_7D2_SW12D5A_ACTUAL_ERROR     67
		#define CMD_TAG_PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING_ACTUAL_STATUS     68
		#define CMD_TAG_PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING_ACTUAL_ERROR     69
		#define CMD_TAG_PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING_ACTUAL_STATUS     70
		#define CMD_TAG_PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING_ACTUAL_ERROR     71
		#define CMD_TAG_TEMPSENSOR_BEACONCCA_CENTERSIDE_ACTUAL_STATUS     72
		#define CMD_TAG_TEMPSENSOR_BEACONCCA_CENTERSIDE_ACTUAL_ERROR     73
		#define CMD_TAG_TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET_ACTUAL_STATUS     74
		#define CMD_TAG_TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET_ACTUAL_ERROR     75
		#define CMD_TAG_VOLTAGE_5_ANALOGCCA_ACTUAL_STATUS     76
		#define CMD_TAG_VOLTAGE_5_ANALOGCCA_ACTUAL_ERROR     77
		#define CMD_TAG_CURRENT_3D3_SW12D5A_ACTUAL_STATUS     78
		#define CMD_TAG_CURRENT_3D3_SW12D5A_ACTUAL_ERROR     79
		#define CMD_TAG_PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING_ACTUAL_STATUS     80
		#define CMD_TAG_PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING_ACTUAL_ERROR     81
		#define CMD_TAG_PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING_ACTUAL_STATUS     82
		#define CMD_TAG_PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING_ACTUAL_ERROR     83
		#define CMD_TAG_PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING_ACTUAL_STATUS     84
		#define CMD_TAG_PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING_ACTUAL_ERROR     85
		#define CMD_TAG_TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR_ACTUAL_STATUS     86
		#define CMD_TAG_TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR_ACTUAL_ERROR     87
		#define CMD_TAG_TEMPSENSOR_DIGITALCCA_MIDDLESIDE_ACTUAL_STATUS     88
		#define CMD_TAG_TEMPSENSOR_DIGITALCCA_MIDDLESIDE_ACTUAL_ERROR     89
		#define CMD_TAG_VOLTAGE_3D3_SW_ACTUAL_STATUS     90
		#define CMD_TAG_VOLTAGE_3D3_SW_ACTUAL_ERROR     91
		#define CMD_TAG_CURRENT_MOTORCTRLR_CH1_12D5A_ACTUAL_STATUS     92
		#define CMD_TAG_CURRENT_MOTORCTRLR_CH1_12D5A_ACTUAL_ERROR     93
		#define CMD_TAG_PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING_ACTUAL_STATUS     94
		#define CMD_TAG_PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING_ACTUAL_ERROR     95
		#define CMD_TAG_PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK_ACTUAL_STATUS     96
		#define CMD_TAG_PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK_ACTUAL_ERROR     97
		#define CMD_TAG_PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING_ACTUAL_STATUS     98
		#define CMD_TAG_PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING_ACTUAL_ERROR     99
		#define CMD_TAG_TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK_ACTUAL_STATUS     100
		#define CMD_TAG_TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK_ACTUAL_ERROR     101
		#define CMD_TAG_GAS_BEACONCCA_RIGHTPOINTING_ACTUAL_STATUS     102
		#define CMD_TAG_GAS_BEACONCCA_RIGHTPOINTING_ACTUAL_ERROR     103
		#define CMD_TAG_CURRENT_MOTORCTRLR_CH2_12D5A_ACTUAL_STATUS     104
		#define CMD_TAG_CURRENT_MOTORCTRLR_CH2_12D5A_ACTUAL_ERROR     105
		#define CMD_TAG_PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING_ACTUAL_STATUS     106
		#define CMD_TAG_PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING_ACTUAL_ERROR     107
		#define CMD_TAG_PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK_ACTUAL_STATUS     108
		#define CMD_TAG_PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK_ACTUAL_ERROR     109
		#define CMD_TAG_PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING_ACTUAL_STATUS     110
		#define CMD_TAG_PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING_ACTUAL_ERROR     111
		#define CMD_TAG_TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE_ACTUAL_STATUS     112
		#define CMD_TAG_TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE_ACTUAL_ERROR     113
		#define CMD_TAG_GENERIC_HEALTH_STATUS_ERROR     114
		#define CMD_TAG_IR_DISTANCE_FWD_CTR_STATUS     115
		#define CMD_TAG_IR_DISTANCE_SIDE_RT_STATUS     116
		#define CMD_TAG_IR_DISTANCE_SIDE_LT_STATUS     117
		#define CMD_TAG_IR_DISTANCE_REAR_CTR_STATUS     118
		#define CMD_TAG_CURRENT_FAULT_1_7D2V_25A_PRESW_STATUS     119
		#define CMD_TAG_CURRENT_FAULT_1_7D2V_25A_PRESW_ERROR     120
		#define CMD_TAG_CURRENT_FAULT_2_3D3V_12D5A_SW_STATUS     121
		#define CMD_TAG_CURRENT_FAULT_2_3D3V_12D5A_SW_ERROR     122
		#define CMD_TAG_CURRENT_FAULT_3_MCTRLRCH1_12D5A_STATUS     123
		#define CMD_TAG_CURRENT_FAULT_3_MCTRLRCH1_12D5A_ERROR     124
		#define CMD_TAG_CURRENT_FAULT_4_MCTRLRCH2_12D5A_STATUS     125
		#define CMD_TAG_CURRENT_FAULT_4_MCTRLRCH2_12D5A_ERROR     126
		#define CMD_TAG_CURRENT_FAULT_5_7D2_12D5A_SW_STATUS     127
		#define CMD_TAG_CURRENT_FAULT_5_7D2_12D5A_SW_ERROR     128
		#define CMD_TAG_SET_LEFT_LASER_ENABLE     129
		#define CMD_TAG_ENABLING_LEFT_LASER     130
		#define CMD_TAG_DISABLING_LEFT_LASER     131
		#define CMD_TAG_LEFT_LASER_STATUS     132
		#define CMD_TAG_SET_RIGHT_LASER_ENABLE     133
		#define CMD_TAG_ENABLING_RIGHT_LASER     134
		#define CMD_TAG_DISABLING_RIGHT_LASER     135
		#define CMD_TAG_RIGHT_LASER_STATUS     136
		#define CMD_TAG_SET_PAN_VALUE     137
		#define CMD_TAG_GIMBAL_PAN_STATUS     138
		#define CMD_TAG_SET_TILT_VALUE     139
		#define CMD_TAG_GIMBAL_TILT_STATUS     140
		#define CMD_TAG_SET_MOTOR_SPEED     141
		#define CMD_TAG_MOTOR_SPEED_STATUS     142
		#define CMD_TAG_SET_MOTOR_TURN     143
		#define CMD_TAG_MOTOR_TURN_STATUS     144
		#define CMD_TAG_SET_DRIVE_SETTING     145
		#define CMD_TAG_DRIVE_SETTING_STATUS     146
		#define CMD_TAG_LATITUDE_STATUS     147
		#define CMD_TAG_LONGITUDE_STATUS     148
		#define CMD_TAG_GPS_FIX_QUALITY_STATUS     149
		#define CMD_TAG_GPS_SATELLITES_STATUS     150
		#define CMD_TAG_SET_LATITUDE_DEST     151
		#define CMD_TAG_SET_LONGITUDE_DEST     152
		#define CMD_TAG_ULTSNC_DISTANCE_FWD_LT_STATUS     153
		#define CMD_TAG_ULTSNC_DISTANCE_FWD_CTR_STATUS     154
		#define CMD_TAG_ULTSNC_DISTANCE_FWD_RT_STATUS     155
		#define CMD_TAG_ULTSNC_DISTANCE_SIDE_RT_STATUS     156
		#define CMD_TAG_ULTSNC_DISTANCE_SIDE_LT_STATUS     157
		#define CMD_TAG_ULTSNC_DISTANCE_REAR_CTR_STATUS     158
		#define CMD_TAG_INVALID_STATE_OR_MODE_ERROR_STATUS     159
		#define CMD_TAG_CALIBRATE_MOTOR_CONTROLLER     160
		#define CMD_TAG_RUN_GIMBAL_DEMO     161

	#endif	
