//RoverBitFlags.h
	
	//"Boolean" Bit Flags
	#ifdef _COMM_BIT_FLAGS_
	
	
		//---------------------------------------------------	
		//Status Flag(s)
		//---------------------------------------------------
		//Universal
		#define _BTFG_NONE_													0x00
		//Error: flagSet_Error1
		#define _BTFG_INVALID_STATE_OR_MODE_ERROR_		0x01
		#define _BTFG_SYNC_ERROR_										0x02
		#define _BTFG_SECURE_LINK_ERROR_							0x04
		#define _BTFG_SW_RESET_ERROR_								0x08
		#define _BTFG_GENERIC_HEALTH_ERROR_						0x10
		#define _BTFG_SLEEPING_ERROR_									0x20
		#define _BTFG_GENERIC_SYSTEM_ERROR_							0x40
		//DEBUG//Error: flagSet_Error2//the variable has not yet been created
		//None Yet. Placeholder.
		//Message Controls: flagSet_MessageControl
		#define _BTFG_REDIRECT_TO_CMNC_								0x01
		#define _BTFG_REDIRECT_TO_MAIN_								0x02		
		#define _BTFG_DATA_WAS_FOR_COMM_CH1_					0x04
		#define _BTFG_DATA_WAS_FOR_COMM_CH2_				0x08
		//System Status: flagSet_SystemStatus1
		#define _BTFG_MAIN_SYSTEM_READY_								0x01
		#define _BTFG_MAIN_SYSTEM_GO_								0x02
		#define _BTFG_COMMUNICATIONS_SECURE_						0x04
		#define _BTFG_FIRST_TRANSMISSION_								0x08
		#define _BTFG_PIR_MOTION_DETECTED_								0x10
		//System Status: flagSet_SystemStatus2
		#define _BTFG_COMM_SLEEP_REQUESTED_							0x01
		#define _BTFG_COMM_SW_RESET_REQUESTED_							0x02		
		//---------------------------------------------------
		
		
		
		
		 //---------------------------------------------------	
		 //Command Filter Option Flag(s)
		 //---------------------------------------------------
		 //Command Filter Options: Set 1: Used in commandFilterOptionsSet1_MAIN and commandFilterOptionsSet1_CMNC
		#define _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_							0x01
		#define _BTFG_COMMAND_ENABLE_OPTION_HWRESETREQUEST_					0x02
		#define _BTFG_COMMAND_ENABLE_OPTION_COMMSWRESETREQUEST_				0x04
		#define _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_					0x08
		#define _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_				0x10
		#define _BTFG_COMMAND_ENABLE_OPTION_SYSTEMGO_									0x20
		#define _BTFG_COMMAND_ENABLE_OPTION_BREAKSECURELINK_						0x40
		#define _BTFG_COMMAND_ENABLE_OPTION_ESTABLISHSECURELINK_				0x80
		//Command Filter Options: Set 2: Used in commandFilterOptionsSet2_MAIN, and commandFilterOptionsSet2_CMNC
		#define _BTFG_COMMAND_ENABLE_OPTION_COMMSLEEPREQUEST_					0x01
		#define _BTFG_COMMAND_ENABLE_OPTION_ALLSLEEPREQUEST_						0x02
		#define _BTFG_COMMAND_ENABLE_OPTION_PIRSTATUS_									0x04
		#define _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_			0x08
		#define _BTFG_COMMAND_ENABLE_OPTION_HI_												0x10
		#define _BTFG_COMMAND_ENABLE_OPTION_BYE_										0x20
		#define _BTFG_COMMAND_ENABLE_OPTION_INVALID_										0x40		 		
		 //---------------------------------------------------
		 
		 
		
	#endif
	
	
	
	#ifdef _MAIN_BIT_FLAGS_
		//---------------------------------------------------	
		//Status Flag(s)
		//---------------------------------------------------
		//Universal
		#define _BTFG_NONE_													0x00
		//Error: flagSet_Error1
		#define _BTFG_INVALID_STATE_OR_MODE_ERROR_		0x01
		#define _BTFG_SYNC_ERROR_										0x02
		#define _BTFG_SW_RESET_ERROR_								0x04
		#define _BTFG_SLEEPING_ERROR_									0x08				
		#define _BTFG_GENERIC_HEALTH_ERROR_						0x01
		#define _BTFG_GENERIC_SYSTEM_ERROR_							0x02		
		//DEBUG//Error: flagSet_Error2//the variable has not yet been created
		//None Yet. Placeholder.
		//Message Controls: flagSet_MessageControl1
		#define _BTFG_REDIRECT_TO_PC_USB_								0x01
		#define _BTFG_REDIRECT_TO_COMM_									0x02		
		#define _BTFG_REDIRECT_TO_NAVI_									0x04
		#define _BTFG_REDIRECT_TO_AUXI_								0x08	
		#define _BTFG_DATA_WAS_FOR_MAIN_CH1_					0x10
		#define _BTFG_DATA_WAS_FOR_MAIN_CH2_				0x20
		#define _BTFG_DATA_WAS_FOR_MAIN_CH3_				0x40
		#define _BTFG_DATA_WAS_FOR_MAIN_CH4_				0x80
		//DEBUG//Message Controls: flagSet_MessageControl2//the variable has not yet been created
		//System Status: flagSet_SystemStatus1
		#define _BTFG_FIRST_TRANSMISSION_								0x01
		#define _BTFG_MTR_POWER_ON_																					0x02
		#define _BTFG_COMM_SYSTEM_READY_								0x04
		#define _BTFG_NAVI_SYSTEM_READY_								0x08
		#define _BTFG_AUXI_SYSTEM_READY_								0x10		
		#define _BTFG_ALL_SYSTEMS_GO_								0x20				
		//System Status: flagSet_SystemStatus2
		#define _BTFG_NAVI_ACKNOWLEDGEMENT_								0x01
		#define _BTFG_AUXI_ACKNOWLEDGEMENT_								0x02
		#define _BTFG_RUN_TASKS_ON_MAIN_NOW_								0x04	
		//System Control: flagSet_SystemControls1
		#define _BTFG_ENABLE_MTR_POWER_								0x01		
		#define _BTFG_MTR_PREV_STATE_								0x02
		
		 //---------------------------------------------------	
		 //Command Filter Option Flag(s)
		 //---------------------------------------------------
		//Command Filter Options: Set 1: Used in commandFilterOptionsSet1_PC_USB, commandFilterOptionsSet1_COMM, commandFilterOptionsSet1_NAVI, commandFilterOptionsSet1_AUXI
		#define _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_							0x01
		#define _BTFG_COMMAND_ENABLE_OPTION_COMMHWRESETREQUEST_					0x02
		#define _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_					0x04
		#define _BTFG_COMMAND_ENABLE_OPTION_SWRESETACKNOWLEDGMENT_					0x08
		#define _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_				0x10
		#define _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_			0x20
		#define _BTFG_COMMAND_ENABLE_OPTION_ALLSLEEPREQUEST_					0x40
		#define _BTFG_COMMAND_ENABLE_OPTION_SLEEPREQUESTACKNOWLEDGEMENT_					0x80
		//Command Filter Options: Set 2: Used in commandFilterOptionsSet2_PC_USB, commandFilterOptionsSet2_COMM, commandFilterOptionsSet2_NAVI, commandFilterOptionsSet2_AUXI
		#define _BTFG_COMMAND_ENABLE_OPTION_SETMOTORPOWERENABLE_									0x01
		#define _BTFG_COMMAND_ENABLE_OPTION_MOTORPOWERSTATUS_									0x02
		#define _BTFG_COMMAND_ENABLE_OPTION_MIDRIGHTENCODERSTATUS_									0x04
		#define _BTFG_COMMAND_ENABLE_OPTION_MIDLEFTENCODERSTATUS_									0x08		
		#define _BTFG_COMMAND_ENABLE_OPTION_HI_												0x10
		#define _BTFG_COMMAND_ENABLE_OPTION_BYE_										0x20
		#define _BTFG_COMMAND_ENABLE_OPTION_INVALID_										0x40		

		
		//---------------------------------------------------
	
	
	
	

	#endif
	
	
	
	
	#ifdef _NAVI_BIT_FLAGS_
				
	//---------------------------------------------------	
		//Status Flag(s)
		//---------------------------------------------------
		//Universal
		#define _BTFG_NONE_													0x00
		//Error: flagSet_Error1
		#define _BTFG_INVALID_STATE_OR_MODE_ERROR_		0x01
		#define _BTFG_SYNC_ERROR_										0x02
		#define _BTFG_SW_RESET_ERROR_								0x04
		#define _BTFG_SLEEPING_ERROR_									0x08				
		#define _BTFG_GENERIC_HEALTH_ERROR_						0x01
		#define _BTFG_GENERIC_SYSTEM_ERROR_							0x02		
		//DEBUG//Error: flagSet_Error2//the variable has not yet been created
		//Message Controls: flagSet_MessageControl1
		#define _BTFG_DATA_WAS_FOR_NAVI_CH1_					0x01
		#define _BTFG_DATA_WAS_FOR_NAVI_CH2_				0x02
		//System Status: flagSet_SystemStatus1
		#define _BTFG_FIRST_TRANSMISSION_								0x01
		#define _BTFG_MAIN_SYSTEM_READY_								0x02
		#define _BTFG_MAIN_SYSTEM_GO_								0x04
		#define _BTFG_GPS_DATA_READY_								0x08
		#define _BTFG_HEADING_DATA_READY_						0x10
		#define _BTFG_ALL_GPS_DATA_GATHERED_								0x20
		#define _BTFG_ALL_HEADING_DATA_GATHERED_								0x40
		//DEBUG//Error: flagSet_SystemStatus2//the variable has not yet been created
		
		//System Control: flagSet_SystemControls1
		#define _BTFG_MTR_POWER_IS_ON_										0x01//mtrPowerIsOn, used to store values passed in from MAIN
		#define _BTFG_REMOTE_CTRL_SELECTED_								0x02//replaces buffer_remote_ctrl_selected, default: false/clear
		#define _BTFG_PREV_REMOTE_CTRL_SELECTED_					0x04//replaces prev_buffer_remote_ctrl_selected
				
		
		





		
		
		//---------------------------------------------------
		
		 //---------------------------------------------------	
		 //Command Filter Option Flag(s)
		 //---------------------------------------------------
		 //Note: These flags were grouped best by function, but in the commandDirector, they are ordered by priority. So it may not correlate 1 to 1.
		 
		//Command Filter Options: Set 1: Used in commandFilterOptionsSet1_PC_USB, commandFilterOptionsSet1_MAIN

		#define _BTFG_COMMAND_ENABLE_OPTION_NAVISWRESETREQUEST_					0x01
		#define _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_				0x02
		#define _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_			0x04
		#define _BTFG_COMMAND_ENABLE_OPTION_SYSTEMGO_									0x08
		#define _BTFG_COMMAND_ENABLE_OPTION_MAINSYSTEMREADY_							0x10
		#define _BTFG_COMMAND_ENABLE_OPTION_NAVISLEEPREQUEST_					0x20
		
		//Command Filter Options: Set 2: Used in commandFilterOptionsSet2_PC_USB, commandFilterOptionsSet2_MAIN
		#define _BTFG_COMMAND_ENABLE_OPTION_GETDRIVESETTING_							0x01
		#define _BTFG_COMMAND_ENABLE_OPTION_SETDRIVESETTING_							0x02
		#define _BTFG_COMMAND_ENABLE_OPTION_SETMOTORPOWERSTATUS_							0x04
		#define _BTFG_COMMAND_ENABLE_OPTION_SETMIDRIGHTENCODERSTATUS_							0x08
		#define _BTFG_COMMAND_ENABLE_OPTION_SETMIDLEFTENCODERSTATUS_							0x10
		#define _BTFG_COMMAND_ENABLE_OPTION_SETHEADING_							0x20
		
		//Command Filter Options: Set 3: Used in commandFilterOptionsSet3_PC_USB, commandFilterOptionsSet3_MAIN
		#define _BTFG_COMMAND_ENABLE_OPTION_FRONTLEFTENCODERSTATUS_				0x01
		#define _BTFG_COMMAND_ENABLE_OPTION_FRONTRIGHTENCODERSTATUS_				0x02
		#define _BTFG_COMMAND_ENABLE_OPTION_MIDLEFTENCODERSTATUS_				0x04
		#define _BTFG_COMMAND_ENABLE_OPTION_MIDRIGHTENCODERSTATUS_				0x08
		#define _BTFG_COMMAND_ENABLE_OPTION_REARLEFTENCODERSTATUS_				0x10
		#define _BTFG_COMMAND_ENABLE_OPTION_REARRIGHTENCODERSTATUS_				0x20
		#define _BTFG_COMMAND_ENABLE_OPTION_RUNMOTORCALIBRATION_				0x40
		#define _BTFG_COMMAND_ENABLE_OPTION_RUNGIMBALDEMO_				0x80
		
		//Command Filter Options: Set 4: Used in commandFilterOptionsSet4_PC_USB, commandFilterOptionsSet4_MAIN
		#define _BTFG_COMMAND_ENABLE_OPTION_SETGIMBALPAN_							0x01
		#define _BTFG_COMMAND_ENABLE_OPTION_GETGIMBALPANSTATUS_							0x02
		#define _BTFG_COMMAND_ENABLE_OPTION_SETGIMBALTILT_							0x04
		#define _BTFG_COMMAND_ENABLE_OPTION_GETGIMBALTILTSTATUS_							0x08
		#define _BTFG_COMMAND_ENABLE_OPTION_SETMOTORSPEED_							0x10
		#define _BTFG_COMMAND_ENABLE_OPTION_GETMOTORSPEEDSTATUS_							0x20
		#define _BTFG_COMMAND_ENABLE_OPTION_SETMOTORTURN_							0x40
		#define _BTFG_COMMAND_ENABLE_OPTION_GETMOTORTURNSTATUS_							0x80

		//Command Filter Options: Set 5: Used in commandFilterOptionsSet5_PC_USB, commandFilterOptionsSet4_MAIN
			//Reserved for LED options. Not implement for now due to time savings.

		//Command Filter Options: Set 6: Used in commandFilterOptionsSet6_PC_USB, commandFilterOptionsSet5_MAIN
		#define _BTFG_COMMAND_ENABLE_OPTION_GETLATITUDE_							0x01
		#define _BTFG_COMMAND_ENABLE_OPTION_GETLONGITUDE_							0x02
		#define _BTFG_COMMAND_ENABLE_OPTION_GETGPSFIXQUALITY_							0x04
		#define _BTFG_COMMAND_ENABLE_OPTION_GETGPSSATELLITESTRACKED_							0x08
		#define _BTFG_COMMAND_ENABLE_OPTION_SETLATITUDEDESTINATION_							0x10
		#define _BTFG_COMMAND_ENABLE_OPTION_SETLONGITUDEDESTINATION_							0x20

		//Command Filter Options: Set 7: Used in commandFilterOptionsSet7_PC_USB, commandFilterOptionsSet7_MAIN
		#define _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCEFORWARDLEFT_							0x01
		#define _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCEFORWARDCENTER_							0x02
		#define _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCEFORWARDRIGHT_							0x04
		#define _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCESIDERIGHT_							0x08
		#define _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCESIDELEFT_							0x10
		#define _BTFG_COMMAND_ENABLE_OPTION_GETULTRASONICDISTANCEREARCENTER_							0x20

		//Command Filter Options: Set 8: Used in commandFilterOptionsSet8_PC_USB, commandFilterOptionsSet8_MAIN
		#define _BTFG_COMMAND_ENABLE_OPTION_GETIRDISTANCEFORWARDCENTERSTATUS_						0x01
		#define _BTFG_COMMAND_ENABLE_OPTION_GETIRDISTANCESIDERIGHTSTATUS_						0x02
		#define _BTFG_COMMAND_ENABLE_OPTION_GETIRDISTANCESIDELEFTSTATUS_						0x04
		#define _BTFG_COMMAND_ENABLE_OPTION_GETIRDISTANCEREARCENTERSTATUS_						0x08
		#define _BTFG_COMMAND_ENABLE_OPTION_HI_						0x10
		#define _BTFG_COMMAND_ENABLE_OPTION_BYE_						0x20
		#define _BTFG_COMMAND_ENABLE_OPTION_INVALID_						0x40


	
		//---------------------------------------------------
	
	
	
	
		
	#endif
	
	#ifdef _AUXI_BIT_FLAGS_

	//---------------------------------------------------	
		//Status Flag(s)
		//---------------------------------------------------
		//Universal
		#define _BTFG_NONE_													0x00
		//Error: flagSet_Error1
//TEMPLATE//		#define _BTFG_INVALID_STATE_OR_MODE_ERROR_		0x01
//TEMPLATE//		#define _BTFG_SYNC_ERROR_										0x02
//TEMPLATE//		#define _BTFG_SW_RESET_ERROR_								0x04
//TEMPLATE//		#define _BTFG_SLEEPING_ERROR_									0x08				
//TEMPLATE//		#define _BTFG_GENERIC_HEALTH_ERROR_						0x01
//TEMPLATE//		#define _BTFG_GENERIC_SYSTEM_ERROR_							0x02		
		//DEBUG//Error: flagSet_Error2//the variable has not yet been created		
		//Message Controls: flagSet_MessageControl
		#define _BTFG_REDIRECT_TO_PC_USB_								0x01
		#define _BTFG_REDIRECT_TO_MAIN_									0x02		
		#define _BTFG_DATA_WAS_FOR_AUXI_CH1_					0x04
		#define _BTFG_DATA_WAS_FOR_AUXI_CH2_				0x08
		//---------------------------------------------------
	
				 //---------------------------------------------------	
		 //Command Filter Option Flag(s)
		 //---------------------------------------------------
		//Command Filter Options: Set 1: Used in commandFilterOptionsSet1_PC_USB, commandFilterOptionsSet1_MAIN
//TEMPLATE//				#define _BTFG_COMMAND_ENABLE_OPTION_SYSTEMREADY_							0x01
//TEMPLATE//				#define _BTFG_COMMAND_ENABLE_OPTION_ALLSWRESETREQUEST_					0x04
//TEMPLATE//				#define _BTFG_COMMAND_ENABLE_OPTION_SWRESETACKNOWLEDGMENT_					0x08
//TEMPLATE//				#define _BTFG_COMMAND_ENABLE_OPTION_GENERICHEALTHERROR_				0x10
//TEMPLATE//				#define _BTFG_COMMAND_ENABLE_OPTION_GENERICSYSTEMERROR_			0x20
//TEMPLATE//				#define _BTFG_COMMAND_ENABLE_OPTION_SLEEPREQUESTACKNOWLEDGEMENT_					0x80
		//Command Filter Options: Set 2: Used in commandFilterOptionsSet2_PC_USB, commandFilterOptionsSet2_MAIN
//TEMPLATE//				#define _BTFG_COMMAND_ENABLE_OPTION_HI_												0x10
//TEMPLATE//				#define _BTFG_COMMAND_ENABLE_OPTION_BYE_										0x20
//TEMPLATE//				#define _BTFG_COMMAND_ENABLE_OPTION_INVALID_										0x40		
		//System Status: flagSet_SystemStatus1
//TEMPLATE//				#define _BTFG_FIRST_TRANSMISSION_								0x01
		//System Control: flagSet_SystemControls1

		
		//---------------------------------------------------
	
		
	#endif
	

	#ifdef _LED_STATE_BIT_FLAGS_
	
		//---------------------------------------------------	
		//LED State Flag(s)
		//---------------------------------------------------
		//Universal
		#define _BTFG_LED_STATE_ALL_OFF_											0x00
		#define _BTFG_LED_STATE_ALL_ON_												0xFF
		//LED State Flag: Set 1: Used in _ledStateFlagSet1
		#define _BTFG_LED_STATE_FRONT_BLUE_BEACON							0x01
		#define _BTFG_LED_STATE_FRONT_RIGHT_IR_BEACON					0x02
		#define _BTFG_LED_STATE_RIGHT_BLUE_BEACON							0x04
		#define _BTFG_LED_STATE_BACK_RIGHT_IR_BEACON					0x08
		#define _BTFG_LED_STATE_BACK_BLUE_BEACON							0x10
		#define _BTFG_LED_STATE_BACK_LEFT_IR_BEACON						0x20
		#define _BTFG_LED_STATE_LEFT_BLUE_BEACON							0x40
		#define _BTFG_LED_STATE_FRONT_LEFT_IR_BEACON					0x80		
		//LED State Flag: Set 2: Used in _ledStateFlagSet2
		#define _BTFG_LED_STATE_LEFT_SIDE_SIGNAL_LIGHT					0x01
		#define _BTFG_LED_STATE_LEFT_HIGHBEAM_HEADLIGHT				0x02
		#define _BTFG_LED_STATE_LEFT_SIGNAL_HEADLIGHT					0x04
		#define _BTFG_LED_STATE_LEFT_FOG_HEADLIGHT						0x08
		#define _BTFG_LED_STATE_RIGHT_FOG_HEADLIGHT						0x10
		#define _BTFG_LED_STATE_RIGHT_SIGNAL_HEADLIGHT					0x20
		#define _BTFG_LED_STATE_RIGHT_HIGHBEAM_HEADLIGHT			0x40
		#define _BTFG_LED_STATE_RIGHT_SIDE_SIGNAL_LIGHT				0x80
		//LED State Flag: Set 3: Used in _ledStateFlagSet3
		#define _BTFG_LED_STATE_RIGHT_WHITE_TAILLIGHT					0x01
		#define _BTFG_LED_STATE_RIGHT_RED1_TAILLIGHT						0x02
		#define _BTFG_LED_STATE_RIGHT_RED5_TAILLIGHT						0x04
		#define _BTFG_LED_STATE_RIGHT_RED2_TAILLIGHT						0x08
		#define _BTFG_LED_STATE_RIGHT_RED4_TAILLIGHT						0x10
		#define _BTFG_LED_STATE_RIGHT_RED3_TAILLIGHT						0x20
		#define _BTFG_LED_STATE_LEFT_RED3_TAILLIGHT						0x40
		#define _BTFG_LED_STATE_LEFT_RED4_TAILLIGHT						0x80
		//LED State Flag: Set 4: Used in _ledStateFlagSet4
		#define _BTFG_LED_STATE_LEFT_RED2_TAILLIGHT						0x01
		#define _BTFG_LED_STATE_LEFT_RED5_TAILLIGHT						0x02
		#define _BTFG_LED_STATE_LEFT_RED1_TAILLIGHT						0x04
		#define _BTFG_LED_STATE_LEFT_WHITE_TAILLIGHT						0x08
		#define _BTFG_LED_STATE_UNDERGLOW_LIGHT							0x10
		
		
//WRITE ME LATER
//ADD MORE LATER
	#endif
	