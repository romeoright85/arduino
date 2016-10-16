//RoverConfig.h
//Note: Don't do a #ifndef as you want the user to do a #include <RoverConfig.h> with newly updated flags for each .h or .cpp class which will append to the current config like with cascading style sheets (CSS).
//For the flags in this RoverConfig.h, use #ifdef _SOME_FLAG_NAME in order to only "turn on"/enable that code if that flag name was defined then #include <RoverConfig.h> was called after
//The order of defining the flag then calling #include <RoverConfig.h> matters. You have to define the flags first, then call #include <RoverConfig.h>
	
	#include <RoverDebug.h>
	#include <RoverReset.h>
	
	
	//Serial Communications
	//Note: CMNC = Command and Control
	#define CMNC_BAUD_RATE	9600  //used for the COMM Arduino to go from the Arduino to the Xbee (same as PC_USB_BAUD_RATE but specific for COMM)
	#define PC_USB_BAUD_RATE	9600 //used for outputting from UNO, Mega Arduinos to the PC via USB
	#define MAIN_BAUD_RATE 9600
	#define AUXI_BAUD_RATE 115200
	#define NAVI_BAUD_RATE 115200
	#define UNIV_BUFFER_SIZE 128//universal buffer size of characters and strings for input/output messages. This was made universal so different messages can be processed with the same function.
		
	//definition for RoverComm (which rover communication source/destination)
	#ifdef _ROVERCOMMTYPES
		//RoverCommTypes
		#define ROVERCOMM_NONE 0 //Save 0 for invalid since when you convert a string to an integer, if it's not a valid conversion, the default output is 0
		#define ROVERCOMM_CMNC 1
		#define ROVERCOMM_NAVI 2
		#define ROVERCOMM_AUXI 3
		#define ROVERCOMM_MAIN 4
		#define ROVERCOMM_COMM 5
	#endif
	
	//definition for DelayCounter Periods
	#ifdef _DELAYCOUNTERPERIODS
		#define DELAY_1_PERIODS 1
		#define DELAY_10_PERIODS 10
		#define DELAY_80_PERIODS 80
		#define DELAY_200_PERIODS 200
	#endif


	//definition for DelayTimer Resolutions
	#ifdef _DELAYTIMER_RESOLUTIONS
		#define DELAY_TIMER_RES_1ms 1
		#define DELAY_TIMER_RES_5ms 5
	#endif
		
	//definition for MotorPowerControl
	#ifdef _MOTORPOWERCONTROL
		#define MTR_OFF 0
		#define MTR_ON 1	
	#endif
	

	//definition for MotorPowerControl
	#ifdef _BUFFERSELECT_MODES
		#define MANUAL_DRIVE 0
		#define AUTO_DRIVE 1
	#endif
	
	
	//definition for LaserControl
	#ifdef _LASERCONTROL_MODES
		#define LASER_OFF 0
		#define LASER_ON 1
	#endif
	
	
	
	//definition for AnalogMuxSensor Channels
	#ifdef _ROVERAMUXCHANNELS
		//Save 0 for invalid since when you convert a string to an integer, if it's not a valid conversion, the default output is 0
		#define AMUX_UNDEF 0 //undefined channel
		#define AMUX_CH_1 1
		#define AMUX_CH_2 2
		#define AMUX_CH_3 3
		#define AMUX_CH_4 4
		#define AMUX_CH_5 5
		#define AMUX_CH_6 6
		#define AMUX_CH_7 7
		#define AMUX_CH_8 8
	#endif
	
	//definition for ImuSensor (use with data arrays that go from element [0] to element [2]
	#ifdef _IMUDATATYPES
		//IMU Data Types
		#define X_DATA 0
		#define Y_DATA 1
		#define Z_DATA 2		
	#endif	
	
	
	
	//definition for WheelEncoderSensor
	#ifdef _WHEEL_ENCODER_DEFINITIONS
		//Motor Mounting Side
		#define RIGHT_MOUNTED		0
		#define LEFT_MOUNTED		1
		//Motor Directions
		#define MOTOR_STOPPED		0
		#define MOTOR_FORWARD		1
		#define MOTOR_REVERSE		2
		#define SINGLE_SIDED_EDGES_PER_REVOLUTION 12
		#define INCHES_PER_REVOLUTION 15		
	#endif	
	

	//definition for MotorController
	#ifdef _MOTORCONTROLLER_DEFINITIONS
		//Power On Reset Values
		//Note: These values need to be calibration then the values updated here
		#define MC_CENTER_POSITION_AFTER_POR		90		
		#define MC_NO_THROTTLE_AFTER_POR		90		
		//Ideal/theoretical value, before calibration adjusted
		//Note: These values should not change. These are  from manufacturing/RC signal specifications.
		#define MC_CENTER_POSITION_IDEAL		90		
		#define MC_NO_THROTTLE_IDEAL	90
		//Servo Limits
		//Got these values from trial and error. The servos don't do well after 175 or before 5 degrees
		#define SRVO_MAX_RANGE 175
		#define SRVO_MIN_RANGE 5
	#endif	
	
	
	
	
	//definition for Rover Analog Names
	#ifdef _ROVERANALOGNAMES
		
		//General Use
		//Save 0 for invalid since when you convert a string to an integer, if it's not a valid conversion, the default output is 0
		#define UNUSED_CH 0 //unused channel
		
		//Amux 1
		#define VOLTAGE_7D2_RAW 1
		#define CURRENT_7D2_PRESW25A 2
		#define CURRENT_7D2_SW12D5A 3
		#define PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING		4
		#define PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING	5
		#define TEMPSENSOR_BEACONCCA_CENTERSIDE		6
		#define TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET		7
		
		//Amux 2
		#define VOLTAGE_5_ANALOGCCA 8
		#define CURRENT_3D3_SW12D5A 9
		#define PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING 10
		#define PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING 11
		#define PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING 12
		#define TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR 13
		#define TEMPSENSOR_DIGITALCCA_MIDDLESIDE 14
		
		//Amux 3
		#define VOLTAGE_3D3_SW 15
		#define CURRENT_MOTORCTRLR_CH1_12D5A 16
		#define PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING 17
		#define PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK 18
		#define PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING 19
		#define TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK 20
		
		//Amux 4
		#define GAS_BEACONCCA_RIGHTPOINTING 21
		#define CURRENT_MOTORCTRLR_CH2_12D5A 22
		#define PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING 23
		#define PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK 24
		#define PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING 25
		#define TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE 26
		
		//Amux 5-8
		//Not used

	#endif
	
		
	
	
		
	//Pinouts for Arduino 4: COMM (UNO)
	#ifdef _ARD_4_COMM_H

		#define COMM_WAKEUP_SOURCE_PIN			0
		#define COMM_WAKEUP_CTRL_PIN	2
		#define PIR_PIN							3		
		#define MAIN_WAKEUP_CTRL_PIN			4
		#define MAIN_HW_RESET_CTRL_PIN			8
		#define HEART_LED_PIN					9
		#define AUXI_HW_RESET_CTRL_PIN			10
		#define NAVI_HW_RESET_CTRL_PIN			11
		#define COMM_SW_UART_RX_PIN					12
		#define COMM_SW_UART_TX_PIN					13

	#endif

	//Pinouts for Arduino 3: MAIN (MEGA)
	#ifdef _ARD_3_MAIN_H

		#define MAIN_WAKEUP_CTRL_PIN			2
		#define NAVI_WAKEUP_CTRL_PIN			4
		#define AUXI_WAKEUP_CTRL_PIN			5
		#define COMM_HW_RESET_CTRL_PIN			12
		#define MTR_FET_CTRL_PIN				12
		#define ENCODER_A_MID_LEFT					20
		#define ENCODER_A_MID_RIGHT					21
		#define MTR_ENABLE_STATUS				22
		#define ENCODER_B_MID_LEFT					23
		#define ENCODER_B_MID_RIGHT					24

	#endif

	//Pinouts for Arduino 2: AUXI (MEGA)
	#ifdef _ARD_2_AUXI_H

	
		#define AUXI_WAKEUP_CTRL_PIN			2
		#define LEFT_LASER_CTRL_PIN				4
		#define RIGHT_LASER_CTRL_PIN			5
		#define CURRENT_SENSOR_RESET_PIN		11
		#define CURRENT_FAULT_1_PIN				12
		#define IMU_SDA_PIN						20
		#define IMU_SCL_PIN						21
		#define AMUX1_SEL_0_PIN				22
		#define AMUX1_SEL_1_PIN				23
		#define AMUX1_SEL_2_PIN				24
		#define AMUX2_SEL_0_PIN				25
		#define AMUX2_SEL_1_PIN				26
		#define AMUX2_SEL_2_PIN				27
		#define AMUX3_SEL_0_PIN				28
		#define AMUX3_SEL_1_PIN				29
		#define AMUX3_SEL_2_PIN				30
		#define AMUX4_SEL_0_PIN				31
		#define AMUX4_SEL_1_PIN				32
		#define AMUX4_SEL_2_PIN				33
		#define AMUX5_SEL_0_PIN				34
		#define AMUX5_SEL_1_PIN				35
		#define AMUX5_SEL_2_PIN				36
		#define AMUX6_SEL_0_PIN				37
		#define AMUX6_SEL_1_PIN				38
		#define AMUX6_SEL_2_PIN				39
		#define AMUX7_SEL_0_PIN				40
		#define AMUX7_SEL_1_PIN				41
		#define AMUX7_SEL_2_PIN				42
		#define AMUX8_SEL_0_PIN				43
		#define AMUX8_SEL_1_PIN				44
		#define AMUX8_SEL_2_PIN				45
		#define CURRENT_FAULT_2_PIN				46
		#define CURRENT_FAULT_3_PIN				47
		#define CURRENT_FAULT_4_PIN				48
		#define CURRENT_FAULT_5_PIN				49
		#define OPAMP_1_OUT_PIN					0
		#define OPAMP_2_OUT_PIN					1
		#define OPAMP_3_OUT_PIN					2
		#define OPAMP_4_OUT_PIN					3
		#define OPAMP_5_OUT_PIN					4
		#define OPAMP_6_OUT_PIN					5
		#define OPAMP_7_OUT_PIN					6
		#define OPAMP_8_OUT_PIN					7
	#endif


	//Pinouts for Arduino 1: NAVI (MEGA)
	#ifdef _ARD_1_NAVI_H

		#define NAVI_WAKEUP_CTRL_PIN				2
		#define ENCODER_B_FRONT_LEFT					3
		#define ENCODER_B_FRONT_RIGHT						4
		#define ENCODER_B_REAR_LEFT						5
		#define ENCODER_B_REAR_RIGHT						6
		#define MTR_RC_CTRL_STEERING_PIN			7
		#define MTR_RC_CTRL_THROTTLE_PIN		8
		#define SERVO_PAN_PIN						9
		#define SERVO_TILT_PIN						10
		#define BUFFER_SELECT_PIN					11
		#define GPS_DATA_PIN						15
		#define ENCODER_A_FRONT_LEFT						18
		#define ENCODER_A_FRONT_RIGHT						19
		#define ENCODER_A_REAR_LEFT						20
		#define ENCODER_A_REAR_RIGHT						21
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

	
	
	
	

	
