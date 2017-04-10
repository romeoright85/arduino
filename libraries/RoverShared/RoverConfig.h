//RoverConfig.h
//Note: Don't do a #ifndef as you want the user to do a #include <RoverConfig.h> with newly updated flags for each .h or .cpp class which will append to the current config like with cascading style sheets (CSS).
//For the flags in this RoverConfig.h, use #ifdef _SOME_FLAG_NAME in order to only "turn on"/enable that code if that flag name was defined then #include <RoverConfig.h> was called after
//The order of defining the flag then calling #include <RoverConfig.h> matters. You have to define the flags first, then call #include <RoverConfig.h>
	
	#include <RoverDebug.h>
	#include <RoverReset.h>
	
	
	//Serial Communications
	//Note: CMNC = Command and Control
	//Note: Make sure the baud rates match on both ends of the pair of devices in communication
	#define CMNC_BAUD_RATE	9600  //used for the COMM Arduino to go from the Arduino to the Xbee (same as PC_USB_BAUD_RATE but specific for COMM)
	#define PC_USB_BAUD_RATE	9600 //used for outputting from UNO, Mega Arduinos to the PC via USB
	#define MAIN_BAUD_RATE 115200
	#define COMM_BAUD_RATE 115200
	#define NAVI_BAUD_RATE 115200
	#define AUXI_BAUD_RATE 115200	
	#define GPS_BAUD_RATE 57600// The default GPS baud rate is 57600
	#define UNIV_BUFFER_SIZE 128//universal buffer size of characters and strings for input/output messages. This was made universal so different messages can be processed with the same function.
	
	//Arduino Types
	//Matching the Arduino numbering with the Microcontroller labels
	#define ARDUINO_NAVI		1
	#define ARDUINO_AUXI		2
	#define ARDUINO_MAIN	3
	#define ARDUINO_COMM	4
	

	
	//definition for MQ Gas Sensors
	#ifdef _MQ_GAS_SENSOR_DEFINITIONS
		#define GAS_SENSOR_TYPE_MQ2		2
		#define GAS_SENSOR_TYPE_MQ3		3
		#define GAS_SENSOR_TYPE_MQ4		4
		#define GAS_SENSOR_TYPE_MQ6		6
		#define GAS_SENSOR_TYPE_MQ7		7
		#define GAS_SENSOR_TYPE_MQ9		9
		
		#define GAS_SENSOR_CURVE_X			0
		#define GAS_SENSOR_CURVE_Y			1
		#define GAS_SENSOR_CURVE_SLOPE	2
		
		//Char Array Sizes		
		#define MQ_SENSOR_NAME_BUFFER_SIZE 50
		#define MQ_SENSOR_UNIT_BUFFER_SIZE 15

	#endif	

	//definition for Rover Data
	#ifdef _ROVERDATA
		//Char Array Sizes				
		#define ROVER_DATA_BUFFER_SIZE		120				
	#endif

	//definition for Character Buffer Array Sizes
	#ifdef _CHAR_BUFFER_ARRAY_SIZES
		//Char Array Sizes		
		#define BUFFER_SIZE_2		2
		#define BUFFER_SIZE_6		6
	#endif

	
	//definition for 
	#ifdef _ROVERHEALTHANDSTATUS_DEFINITONS
		//Hold States
		#define CURRENT_FAULT_HOLD	1
		
	#endif	
		
	//definition for CurrentSensorFault
	#ifdef _CURRENTSENSORFAULT_DEFINITIONS
		#define NUM_OF_CURRENT_SENSORS		5
	#endif	
		
	//definition for UpTime
	#ifdef _UPTIME_DEFINITIONS
		//value was arbitrarily chosen to be somewhat near the max value for millis() of 4,294,967,295 but not too close to the max to account for any loop delay
		#define UPTIME_ROLLOVER_UPPER_THRESHOLD 3000000000
		//value was arbitrarily chosen to be something small since roll over has occured, but big enough to account for any loop code delay
		#define UPTIME_ROLLOVER_LOWER_THRESHOLD 100000
	#endif	
	
	//definition for RoverGpsSensor
	#ifdef _GPS_SENSOR
		/*
			ex: GPGGA,011217.800,3916.1627,N,07636.6598,W,1,5,1.27,39.2,M,-33.6,M,,*59//DEBUG AND DELETE
			
			GPGGA = Sentence ID
			011217.800 = Data Fix Time
			3916.1627 - Latitude
			N = Latitude Direction
			07636.6598 = Longitude
			W = Longitude Direction
			1 = Fix Quality
			5 = Number Of Satellites
			1.27 = Horizontal Dilution
			39.2 = Altitude
			M = Unit of Altitude
			-33.6 =Height of geiod above WGS84 Ellipsoid
			M = Unit of Height
			 = Blank
			 = Blank
			*59 = Checksum
		*/
		
		
		//Char Array Sizes		
		#define GPS_DATA_CHAR_BUFFER_SIZE 100//should be equal or greater than GPS_SENTENCE_LENGTH
		//GPS Number of Attempts To Obtain A Valid Data String
		#define GPS_RX_DATA_ATTEMPTS 	5
		//GPS Number of Characters to receive while waiting for the start of the GPS data (i.e. $) before timing out
		#define GPS_SENTENCE_LENGTH 	75//should match the same size as ROVER_COMM_SENTENCE_LENGTH
		//GPS Header Types
		#define GPS_GPGGA_SENTENCE_ID			"GPGGA"		
		//GPS Data Index - GPGGA (holds the GPGGA GPS data)
		#define GPS_GPGGA_INDEX_OF_SENTENCE_ID											0
		#define GPS_GPGGA_INDEX_OF_DATA_FIX_TIME											1 
		#define GPS_GPGGA_INDEX_OF_LATITUDE													2
		#define GPS_GPGGA_INDEX_OF_LATITUDE_DIRECTION								3 //N (North) or S (South)
		#define GPS_GPGGA_INDEX_OF_LONGITUDE												4
		#define GPS_GPGGA_INDEX_OF_LONGITUDE_DIRECTION							5 //E (East) or W (West)
		#define GPS_GPGGA_INDEX_OF_FIX_QUALITY												6
		#define GPS_GPGGA_INDEX_OF_SATELLITES_TRACKED								7		
		//GPS GPGGA Number of Fields of reliable good data (as if you try to get all 14 max fields, it often gets corrupted near the end)
		#define GPS_GPGGA_FIELDS		8		
		//GPS Direction Types
		#define GPS_DIR_UNKOWN 0//Save 0 for invalid since when you convert a string to an integer, if it's not a valid conversion, the default output is 0
		#define GPS_DIR_NORTH				1//Save 0 for invalid since when you convert a string to an integer, if it's not a valid conversion, the default output is 0
		#define GPS_DIR_NORTHEAST		2
		#define GPS_DIR_EAST					3
		#define GPS_DIR_SOUTHEAST		4
		#define GPS_DIR_SOUTH				5
		#define GPS_DIR_SOUTHWEST		6
		#define GPS_DIR_WEST					7
		#define GPS_DIR_NORTHWEST		8
		//GPS Fix Quality Types	
		#define GPS_GPGGA_FQ_INVALID								0
		#define GPS_GPGGA_FQ_GPS_FIX								1
		#define GPS_GPGGA_DGPS											2
	#endif	
	
	
	//definition for BeaconLightAssembly
	//Beacon light types
	#ifdef _BEACON_LIGHT_TYPES
		#define FRONT_LEFT_IR_BEACON		0
		#define BACK_LEFT_IR_BEACON			1
		#define BACK_RIGHT_IR_BEACON		2
		#define FRONT_RIGHT_IR_BEACON		3
		#define LEFT_BLUE_BEACON				4
		#define BACK_BLUE_BEACON				5
		#define RIGHT_BLUE_BEACON				6
		#define FRONT_BLUE_BEACON			7
	#endif
	
	//definition for HeadLightAssembly
	//Headlight types
	#ifdef _HEADLIGHT_TYPES
		#define HIGHBEAM_HEADLIGHT		0
		#define SIGNAL_HEADLIGHT			1
		#define FOG_HEADLIGHT					2
	#endif
	
	//definition for TailLightAssembly
	//Taillight types
	#ifdef _TAILLIGHT_TYPES
		#define RED1_TAILLIGHT			0
		#define RED2_TAILLIGHT			1
		#define RED3_TAILLIGHT			2
		#define RED4_TAILLIGHT			3
		#define RED5_TAILLIGHT			4
		#define WHITE_TAILLIGHT			5	
	#endif
		
	//definitions for RoverComm 
	#ifdef _ROVERCOMM_DEFINITIONS
		//RoverCommTypes (which rover communication source/destination)
		#define ROVER_COMM_SENTENCE_LENGTH		75//should match the same size as GPS_SENTENCE_LENGTH
		#define ROVERCOMM_NONE 0 //Save 0 for invalid since when you convert a string to an integer, if it's not a valid conversion, the default output is 0		
		#define ROVERCOMM_CMNC 1
		#define ROVERCOMM_NAVI 2
		#define ROVERCOMM_AUXI 3
		#define ROVERCOMM_MAIN 4
		#define ROVERCOMM_COMM 5		
		#define ROVERCOMM_PC_USB 6		
	#endif
	
	//definition for DelayCounter Periods
	#ifdef _DELAYCOUNTERPERIODS
		#define DELAY_1_PERIODS 1
		#define DELAY_2_PERIODS 2
		#define DELAY_4_PERIODS 4
		#define DELAY_10_PERIODS 10		
		#define DELAY_80_PERIODS 80		
		#define DELAY_200_PERIODS 200
	#endif

	
	//definition for DelayTimer Resolutions
	#ifdef _DELAYTIMER_RESOLUTIONS
		#define DELAY_TIMER_RES_1ms 1
		#define DELAY_TIMER_RES_2ms 2
		#define DELAY_TIMER_RES_5ms 5
		#define DELAY_TIMER_RES_10ms 10
		#define DELAY_TIMER_RES_50ms 50
		#define DELAY_TIMER_RES_500ms 50
	#endif
		
	//definition for MotorPowerControl
	#ifdef _MOTORPOWERCONTROL_DEFINITIONS
		#define MTR_DISABLED 0
		#define MTR_ENABLED 1	
	#endif
	

	//definition for BufferSelect
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
	
	//definitions for ImuSensor
	#ifdef _IMU_DEFINITIONS

		
		// tested with Arduino Uno with ATmega328 and Arduino Duemilanove with ATMega168

		// accelerometer: 8 g sensitivity
		// 3.9 mg/digit; 1 g = 256
		#define GRAVITY 256  //this equivalent to 1G in the raw data coming from the accelerometer

		#define ToRad(x) ((x)*0.01745329252)  // *pi/180
		#define ToDeg(x) ((x)*57.2957795131)  // *180/pi

		// gyro: 2000 dps full scale
		// 70 mdps/digit; 1 dps = 0.07
		#define Gyro_Gain_X 0.07 //X axis Gyro gain
		#define Gyro_Gain_Y 0.07 //Y axis Gyro gain
		#define Gyro_Gain_Z 0.07 //Z axis Gyro gain
		#define Gyro_Scaled_X(x) ((x)*ToRad(Gyro_Gain_X)) //Return the scaled ADC raw data of the gyro in radians for second
		#define Gyro_Scaled_Y(x) ((x)*ToRad(Gyro_Gain_Y)) //Return the scaled ADC raw data of the gyro in radians for second
		#define Gyro_Scaled_Z(x) ((x)*ToRad(Gyro_Gain_Z)) //Return the scaled ADC raw data of the gyro in radians for second

		/*For debugging purposes*/
		//IMU_OUTPUTMODE=1 will print the corrected data,
		//IMU_OUTPUTMODE=0 will print uncorrected data of the gyros (with drift)
		#define OUTPUTMODE 1

		#define PRINT_DCM 0     //Will print the whole direction cosine matrix
		#define PRINT_ANALOGS 0 //Will print the analog raw data
		#define PRINT_EULER 1   //Will print the Euler angles Roll, Pitch and Yaw
				
		//==End Of Intergrated Code From Others
		

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
		//Ideal/theoretical value, before calibration adjusted
		//Note: These values should not change. These are  from manufacturing/RC signal specifications.
		#define MC_CENTER_POSITION_IDEAL		90		
		
		//Steering
		#define MC_MAX_RIGHT_POSITION_IDEAL		180		
		#define MC_CENTER_POSITION_IDEAL		90
		#define MC_MAX_LEFT_POSITION_IDEAL		0
		//Throttle		
		#define MC_MAX_FWD_THROTTLE_IDEAL 0
		#define MC_NO_THROTTLE_IDEAL	90
		#define MC_MAX_REV_THROTTLE_IDEAL 180 //use a bigger number is going reverse
	#endif	
	
	//definition for GimbalController
	#ifdef _GIMBALCONTROLLER_DEFINITIONS		
		//Ideal/theoretical value, before calibration adjusted
		//Note: These values should not change. These are  from manufacturing/RC signal specifications.
		
		//Pan
		#define GC_MAX_LEFT_POSITION_IDEAL		0
		#define GC_CENTER_POSITION_IDEAL			90
		#define GC_MAX_RIGHT_POSITION_IDEAL		180
		//Tilt		
		#define GC_MAX_DOWN_POSITION_IDEAL		0
		#define GC_MIDDLE_POSITION_IDEAL			90
		#define GC_MAX_UP_POSITION_IDEAL			180
		
	#endif	
	
	//Rover Current Sensor Models
	#ifdef _ROVERCURRENTSENSORMODELS
		//Leave 0 for the default case
		#define ACS711_12D5A	1
		#define ACS711_25A		2
	#endif		
		
	//Rover Analog Names
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
		#define MTR_FET_CTRL_PIN				13		
		#define MAIN_HW_UART3_TX_PIN		14
		#define MAIN_HW_UART3_RX_PIN	15
		#define MAIN_HW_UART2_TX_PIN		16
		#define MAIN_HW_UART2_RX_PIN	17
		#define MAIN_HW_UART1_TX_PIN		18
		#define MAIN_HW_UART1_RX_PIN	19
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
		#define CURRENT_FAULT_1_7D2V_25A_PRESW_PIN				12
		#define AUXI_HW_UART2_TX_PIN		16
		#define AUXI_HW_UART2_RX_PIN		17
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
		#define CURRENT_FAULT_2_3D3V_12D5A_SW_PIN				46
		#define CURRENT_FAULT_3_MCTRLRCH1_12D5A_PIN				47
		#define CURRENT_FAULT_4_MCTRLRCH2_12D5A_PIN				48
		#define CURRENT_FAULT_5_7D2_12D5A_SW_PIN				49
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
		#define GPS_DATA_TX_PIN						15 //The definition is not really used in the code, but the pin is for Serial3
		#define NAVI_HW_UART2_TX_PIN		16
		#define NAVI_HW_UART2_RX_PIN		17		
		#define ENCODER_A_FRONT_LEFT						18
		#define ENCODER_A_FRONT_RIGHT						19
		#define ENCODER_A_REAR_LEFT						20
		#define ENCODER_A_REAR_RIGHT						21
		#define SIDE_LEFT_SIGNAL_PIN				22
		#define SIDE_RIGHT_SIGNAL_PIN				24
		#define RIGHT_FOG_HEADLIGHT_PIN					26
		#define RIGHT_SIGNAL_HEADLIGHT_PIN				28
		#define UNDERGLOW_PIN						29
		#define RIGHT_HIGHBEAM_HEADLIGHT_PIN			30
		#define LEFT_RED_TAILLIGHT_1_PIN			31
		#define LEFT_HIGHBEAM_HEADLIGHT_PIN			32
		#define LEFT_RED_TAILLIGHT_2_PIN			33
		#define LEFT_SIGNAL_HEADLIGHT_PIN				34
		#define LEFT_RED_TAILLIGHT_3_PIN			35
		#define LEFT_FOG_HEADLIGHT_PIN					36
		#define LEFT_WHITE_TAILLIGHT_PIN				37
		#define FRONT_LEFT_BEACON_IR_PIN					38
		#define LEFT_RED_TAILLIGHT_5_PIN			39
		#define BACK_LEFT_BEACON_IR_PIN					40
		#define LEFT_RED_TAILLIGHT_4_PIN			41
		#define BACK_RIGHT_BEACON_IR_PIN					42
		#define RIGHT_RED_TAILLIGHT_3_PIN			43
		#define FRONT_RIGHT_BEACON_IR_PIN					44
		#define RIGHT_RED_TAILLIGHT_2_PIN			45
		#define LEFT_BEACON_BLUE_PIN				46
		#define RIGHT_RED_TAILLIGHT_1_PIN			47
		#define BACK_BEACON_BLUE_PIN				48
		#define RIGHT_RED_TAILLIGHT_4_PIN			49
		#define RIGHT_BEACON_BLUE_PIN				50
		#define RIGHT_RED_TAILLIGHT_5_PIN			51
		#define FRONT_BEACON_BLUE_PIN				52
		#define RIGHT_WHITE_TAILLIGHT_PIN				53
		#define SIDE_LEFT_IR_DIST_SENSOR_PIN		A0 //analog used as digital
		#define REAR_CENTER_IR_DIST_SENSOR_PIN		A1 //analog used as digital
		#define FORWARD_CENTER_IR_DIST_SENSOR_PIN	A2 //analog used as digital
		#define SIDE_RIGHT_IR_DIST_SENSOR_PIN		A3 //analog used as digital
		#define SIDE_LEFT_ULTSNC_TRIG_PIN			A4 //analog used as digital
		#define SIDE_LEFT_ULTSNC_ECHO_PIN			A5 //analog used as digital
		#define REAR_CENTER_ULTSNC_TRIG_PIN			A6 //analog used as digital
		#define REAR_CENTER_ULTSNC_ECHO_PIN			A7 //analog used as digital
		#define FORWARD_LEFT_ULTSNC_TRIG_PIN		A8 //analog used as digital
		#define FORWARD_LEFT_ULTSNC_ECHO_PIN		A9 //analog used as digital
		#define FORWARD_CENTER_ULTSNC_TRIG_PIN		A10 //analog used as digital
		#define FORWARD_CENTER_ULTSNC_ECHO_PIN		A11 //analog used as digital
		#define FORWARD_RIGHT_ULTSNC_TRIG_PIN		A12 //analog used as digital
		#define FORWARD_RIGHT_ULTSNC_ECHO_PIN		A13 //analog used as digital
		#define SIDE_RIGHT_ULTSNC_TRIG_PIN			A14 //analog used as digital
		#define SIDE_RIGHT_ULTSNC_ECHO_PIN			A15 //analog used as digital

	#endif


	//Used for	Distance Sensors (like ultrasonic and infrared sensors)
	#ifdef _DISTANCE_UNITS_MODES
		#define UNIT_CM	 0
		#define UNIT_M	 1
		#define UNIT_IN  2
		#define UNIT_FT	 3
	#endif	

	//definitions for Ultrasonic Sensor
	#ifdef _ULTRASONIC_SENSOR_DEFINITIONS	
		#define ULTRASONIC_SENSOR_TIMEOUT 30000		
		#define ULTRASONIC_SENSOR_SAMPLE_TIMES	5 //the number times to sample and average the ultrasonic data
		#define ULTRASONIC_SENSOR_NO_OBJECT_SAMPLES	3 //the number of times no objects detect threshold before declaring no objects detected. Should be <= ULTRASONIC_SENSOR_SAMPLE_TIMES.
	#endif
	
	
	
//definitions for Infrared Sensor
	#ifdef _INFRARED_SENSOR_DEFINITIONS	
		#define INFRARED_SENSOR_SAMPLE_TIMES	5 //the number times to sample and average the IR sensor data		
	#endif
	
		
	
	

	
