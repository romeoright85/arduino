//RoverConfig.h
//Note: Don't do a #ifndef as you want the user to do a #include <RoverConfig.h> with newly updated flags for each .h or .cpp class which will append to the current config like with cascading style sheets (CSS).
//For the flags in this RoverConfig.h, use #ifdef _SOME_FLAG_NAME in order to only "turn on"/enable that code if that flag name was defined then #include <RoverConfig.h> was called after
//The order of defining the flag then calling #include <RoverConfig.h> matters. You have to define the flags first, then call #include <RoverConfig.h>
		
	//Pinouts for Arduino 4: COMM (UNO)
	#ifdef _ARD_4_COMM_H

		#define UNO_WAKEUP_CTRL_PIN_0			0
		#define UNO_WAKEUP_CTRL_PIN_2			2
		#define PIR_PIN							3		
		#define MAIN_WAKEUP_CTRL_PIN			4
		#define MAIN_HW_RESET_CTRL_PIN			8
		#define HEART_LED_PIN					9
		#define AUXI_HW_RESET_CTRL_PIN			10
		#define NAVI_HW_RESET_CTRL_PIN			11
		#define SW_UART_RX_PIN					12
		#define SW_UART_TX_PIN					13

	#endif

	//Pinouts for Arduino 3: MAIN (MEGA)
	#ifdef _ARD_3_MAIN_H

		#define COMM_WAKEUP_CTRL_PIN			2
		#define NAVI_WAKEUP_CTRL_PIN			4
		#define AUXI_WAKEUP_CTRL_PIN			5
		#define COMM_HW_RESET_CTRL_PIN			12
		#define MTR_FET_CTRL_PIN				12
		#define ENCODER_5_PIN					20
		#define ENCODER_7_PIN					21
		#define MTR_ENABLE_STATUS				22
		#define ENCODER_6_PIN					23
		#define ENCODER_8_PIN					24

	#endif

	//Pinouts for Arduino 2: AUXI (MEGA)
	#ifdef _ARD_2_AUXI_H

		#define LEFT_LASER_CTRL_PIN				4
		#define RIGHT_LASER_CTRL_PIN			5
		#define CURRENT_SENSOR_RESET_PIN		11
		#define CURRENT_FAULT_1_PIN				12
		#define IMU_SDA_PIN						20
		#define IMU_SCL_PIN						21
		#define CURRENT_FAULT_2_PIN				46
		#define CURRENT_FAULT_3_PIN				47
		#define CURRENT_FAULT_4_PIN				48
		#define CURRENT_FAULT_5_PIN				49
		#define OP_AMP_1						0
		#define OP_AMP_2						1
		#define OP_AMP_3						2
		#define OP_AMP_4						3
		#define OP_AMP_5						4
		#define OP_AMP_6						5
		#define OP_AMP_7						6
		#define OP_AMP_8						7
	#endif


	//Pinouts for Arduino 1: NAVI (MEGA)
	#ifdef _ARD_1_NAVI_H

		#define NAVI_WAKEUP_CTRL_PIN				2
		#define ENCODER_2_PIN						3
		#define ENCODER_4_PIN						4
		#define ENCODER_10_PIN						5
		#define ENCODER_12_PIN						6
		#define MTR_RC_CTRL_STEERING_PIN			7
		#define MTR_RC_CTRL_ACCELERATION_PIN		8
		#define SERVO_PAN_PIN						9
		#define SERVO_TILT_PIN						10
		#define BUFFER_SELECT_PIN					11
		#define GPS_DATA_PIN						15
		#define ENCODER_1_PIN						18
		#define ENCODER_3_PIN						19
		#define ENCODER_9_PIN						20
		#define ENCODER_11_PIN						21
		#define SIDE_LEFT_SIGNAL_PIN				22
		#define SIDE_RIGHT_SIGNAL_PIN				24
		#define FRONT_RIGHT_FOG_PIN					26
		#define FRONT_RIGHT_SIGNAL_PIN				28
		#define UNDERGLOW_PIN						29
		#define FRONT_RIGHT_HEADLIGHT_PIN			30
		#define BACK_LEFT_TAILLIGHT_1_PIN			31
		#define FRONT_LEFT_HEADLIGHT_PIN			32
		#define BACK_LEFT_TAILLIGHT_2_PIN			33
		#define FRONT_LEFT_SIGNAL_PIN				34
		#define BACK_LEFT_TAILLIGHT_3_PIN			35
		#define FRONT_LEFT_FOG_PIN					36
		#define BACK_LEFT_REVERSE_PIN				37
		#define TOP_BEACON_IR_4_PIN					38
		#define BACK_LEFT_TAILLIGHT_5_PIN			39
		#define TOP_BEACON_IR_3_PIN					40
		#define BACK_LEFT_TAILLIGHT_4_PIN			41
		#define TOP_BEACON_IR_2_PIN					42
		#define BACK_LEFT_TAILLIGHT_3_PIN			43
		#define TOP_BEACON_IR_1_PIN					44
		#define BACK_LEFT_TAILLIGHT_2_PIN			45
		#define TOP_BEACON_BLUE_1_PIN				46
		#define BACK_RIGHT_TAILLIGHT_1_PIN			47
		#define TOP_BEACON_BLUE_3_PIN				48
		#define BACK_RIGHT_TAILLIGHT_4_PIN			49
		#define TOP_BEACON_BLUE_2_PIN				50
		#define BACK_RIGHT_TAILLIGHT_5_PIN			51
		#define TOP_BEACON_BLUE_1_PIN				52
		#define BACK_RIGHT_REVERSE_PIN				53
		#define SIDE_LEFT_IR_DIST_SENSOR_PIN		0
		#define REAR_CENTER_IR_DIST_SENSOR_PIN		1
		#define FORWARD_CENTER_IR_DIST_SENSOR_PIN	2
		#define SIDE_RIGHT_IR_DIST_SENSOR_PIN		3
		#define SIDE_LEFT_ULTSNC_TRIG_PIN			4
		#define SIDE_LEFT_ULTSNC_ECHO_PIN			5
		#define REAR_CENTER_ULTSNC_TRIG_PIN			6
		#define REAR_CENTER_ULTSNC_ECHO_PIN			7
		#define FORWARD_LEFT_ULTSNC_TRIG_PIN		8
		#define FORWARD_LEFT_ULTSNC_ECHO_PIN		9
		#define FORWARD_CENTER_ULTSNC_TRIG_PIN		10
		#define FORWARD_CENTER_ULTSNC_ECHO_PIN		11
		#define FORWARD_RIGHT_ULTSNC_TRIG_PIN		12
		#define FORWARD_RIGHT_ULTSNC_ECHO_PIN		13
		#define SIDE_RIGHT_ULTSNC_TRIG_PIN			14
		#define SIDE_RIGHT_ULTSNC_ECHO_PIN			15

	#endif


	//Used for	 distance sensors like ultrasonic or infrared sensors
	#ifdef _DISTANCE_UNITS_MODES
		#define UNIT_CM	 0
		#define UNIT_M	 1
		#define UNIT_IN  2
		#define UNIT_FT	 3
	#endif	

