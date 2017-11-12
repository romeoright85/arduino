//RoverBitFlags.h
	
	//"Boolean" Bit Flags
	#ifdef _COMM_BIT_FLAGS_
	
	
		//---------------------------------------------------	
		//Status Flag(s)
		//---------------------------------------------------
		//Universal
		#define _BTFG_NONE_													0x00
		//Error: flagSet_Error
		#define _BTFG_INVALID_STATE_OR_MODE_ERROR_		0x01
		#define _BTFG_SYNC_ERROR_										0x02
		#define _BTFG_SECURE_LINK_ERROR_							0x04
		#define _BTFG_SW_RESET_ERROR_								0x08
		#define _BTFG_GENERIC_HEALTH_ERROR_						0x10
		#define _BTFG_SLEEPING_ERROR_									0x20
		//Message Controls: flagSet_MessageControl
		#define _BTFG_REDIRECT_TO_CMNC_								0x01
		#define _BTFG_REDIRECT_TO_MAIN_								0x02		
		#define _BTFG_DATA_WAS_FOR_COMM_CH1_					0x04
		#define _BTFG_DATA_WAS_FOR_COMM_CH2_				0x08
		//System Status: flagSet_SystemStatus
		#define _BTFG_MAIN_SYSTEM_READY_								0x01
		#define _BTFG_MAIN_SYSTEM_GO_								0x02
		#define _BTFG_COMMUNICATIONS_SECURE_						0x04
		#define _BTFG_FIRST_TRANSMISSION_								0x08
		#define _BTFG_PIR_MOTION_DETECTED_								0x10
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
		//Command Filter Options: Set 2: Used in commandFilterOptionsSet2_MAIN, and commandFilterOptionsSet1_CMNC
		#define _BTFG_COMMAND_ENABLE_OPTION_COMMSLEEPREQUEST_					0x01
		#define _BTFG_COMMAND_ENABLE_OPTION_ALLSLEEPREQUEST_						0x02
		#define _BTFG_COMMAND_ENABLE_OPTION_PIRSTATUS_									0x04
		#define _BTFG_COMMAND_ENABLE_OPTION_RXDERRORMESSAGES_					0x08
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
		//Message Controls: flagSet_MessageControl
		#define _BTFG_REDIRECT_TO_PC_USB_								0x01
		#define _BTFG_REDIRECT_TO_MAIN_									0x02		
		#define _BTFG_DATA_WAS_FOR_NAVI_CH1_					0x04
		#define _BTFG_DATA_WAS_FOR_NAVI_CH2_				0x08
		//---------------------------------------------------
		
		
		
		
	#endif
	
	#ifdef _AUXI_BIT_FLAGS_

	//---------------------------------------------------	
		//Status Flag(s)
		//---------------------------------------------------
		//Universal
		#define _BTFG_NONE_													0x00
		//Message Controls: flagSet_MessageControl
		#define _BTFG_REDIRECT_TO_PC_USB_								0x01
		#define _BTFG_REDIRECT_TO_MAIN_									0x02		
		#define _BTFG_DATA_WAS_FOR_AUXI_CH1_					0x04
		#define _BTFG_DATA_WAS_FOR_AUXI_CH2_				0x08
		//---------------------------------------------------
	
		
		
	#endif
	
	#ifdef _MAIN_BIT_FLAGS_
			//---------------------------------------------------	
		//Status Flag(s)
		//---------------------------------------------------
		//Universal
		#define _BTFG_NONE_													0x00
		//Message Controls: flagSet_MessageControl
		#define _BTFG_REDIRECT_TO_PC_USB_								0x01
		#define _BTFG_REDIRECT_TO_COMM_									0x02		
		#define _BTFG_REDIRECT_TO_NAVI_									0x04
		#define _BTFG_REDIRECT_TO_AUXI_								0x08	
		#define _BTFG_DATA_WAS_FOR_MAIN_CH1_					0x10
		#define _BTFG_DATA_WAS_FOR_MAIN_CH2_				0x20
		#define _BTFG_DATA_WAS_FOR_MAIN_CH3_				0x40
		#define _BTFG_DATA_WAS_FOR_MAIN_CH4_				0x80
		//---------------------------------------------------
	
	#endif
	