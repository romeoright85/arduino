//RoverCalibration.h
//Note: Don't do a #ifndef as you want the user to do a #include <RoverCalibration.h> with newly updated flags for each .h or .cpp class which will append to the current config like with cascading style sheets (CSS).
//For the flags in this RoverConfig.h, use #ifdef _SOME_FLAG_NAME in order to only "turn on"/enable that code if that flag name was defined then #include <RoverCalibration.h> was called after
//The order of defining the flag then calling #include <RoverCalibration.h> matters. You have to define the flags first, then call #include <RoverCalibration.h>
	

	//definition for MotorController
	#ifdef _MOTORCONTROLLER_CALIBRATIONS
		//Power On Reset Values
		//Note: These values need to be calibration then the values updated here
		#define MC_CENTER_POSITION_AFTER_POR		90		
		#define MC_NO_THROTTLE_AFTER_POR		90				
	#endif	
	
	//definition for GimbalController
	#ifdef _GIMBALCONTROLLER_CALIBRATIONS
		//Power On Reset Values
		//Note: These values need to be calibration then the values updated here
		#define GC_CENTER_POSITION_AFTER_POR		90		//for pan
		#define GC_MIDDLE_POSITION_AFTER_POR		90		//for tilt
	#endif	

	
	
	//definition for MQ Gas Sensors
	#ifdef _MQ_GAS_SENSOR_CALIBRATIONS

		//MQ-2 (Flammable Gas & Smoke Sensor) Curve Values (from the datasheet)
		#define MQ2_X_PT				2.3  //DEBUG, get values later. For now was from http://sandboxelectronics.com/?p=165
		#define MQ2_Y_PT					0.53 //DEBUG, get values later. For now was from http://sandboxelectronics.com/?p=165
		#define MQ2_SLOPE				-0.44 //DEBUG, get values later. For now was from http://sandboxelectronics.com/?p=165
		#define MQ2_RO_CLEAN_AIR_FACTOR			9.83 //DEBUG, get values later. For now was from http://sandboxelectronics.com/?p=165
		
		//MQ-3 (Alcohol Gas Sensor) Curve Values (from the datasheet)
		#define MQ3_X_PT				1.1  //DEBUG, get values later. For now create random fake values.
		#define MQ3_Y_PT					0.22 //DEBUG, get values later. For now create random fake values.
		#define MQ3_SLOPE				-0.33 //DEBUG, get values later. For now create random fake values.
		#define MQ3_RO_CLEAN_AIR_FACTOR			9.87 //DEBUG, get values later. For now create random fake values.
	
		//MQ-4 (Methane Gas Sensor) Curve Values (from the datasheet)
		#define MQ4_X_PT				1.1  //DEBUG, get values later. For now create random fake values.
		#define MQ4_Y_PT					0.22 //DEBUG, get values later. For now create random fake values.
		#define MQ4_SLOPE				-0.33 //DEBUG, get values later. For now create random fake values.
		#define MQ4_RO_CLEAN_AIR_FACTOR			9.87 //DEBUG, get values later. For now create random fake values.
		
		//MQ-6 (LPG / Isobutane / Propane Gas Sensor)
		#define MQ6_X_PT				2.3  //DEBUG, get values later. For now was from http://sandboxelectronics.com/?p=165
		#define MQ6_Y_PT					0.21 //DEBUG, get values later. For now was from http://sandboxelectronics.com/?p=165
		#define MQ6_SLOPE				-0.47 //DEBUG, get values later. For now was from http://sandboxelectronics.com/?p=165
		#define MQ6_RO_CLEAN_AIR_FACTOR			9.83 //DEBUG, get values later. For now was from http://sandboxelectronics.com/?p=165

		//MQ-7 (Carbon Monoxide Gas Sensor)
		#define MQ7_X_PT				2.3  //DEBUG, get values later. For now was from http://sandboxelectronics.com/?p=165
		#define MQ7_Y_PT					0.72 //DEBUG, get values later. For now was from http://sandboxelectronics.com/?p=165
		#define MQ7_SLOPE				-0.34 //DEBUG, get values later. For now was from http://sandboxelectronics.com/?p=165
		#define MQ7_RO_CLEAN_AIR_FACTOR			9.83 //DEBUG, get values later. For now was from http://sandboxelectronics.com/?p=165

		//MQ-9 (Carbon Monoxide & Flammable Gas Sensor)
		#define MQ9_X_PT				1.1  //DEBUG, get values later. For now create random fake values.
		#define MQ9_Y_PT					0.22 //DEBUG, get values later. For now create random fake values.
		#define MQ9_SLOPE				-0.33 //DEBUG, get values later. For now create random fake values.
		#define MQ9_RO_CLEAN_AIR_FACTOR			9.87 //DEBUG, get values later. For now create random fake values.
		
		//Also see "RESISTOR_GAS_BEACONCCA_RIGHTPOINTING"
		
	#endif
	
	
	
	#ifdef _SERVOSIGNAL_CALIBRATIONS
		//Servo Limits
		//Got these values from trial and error. The servos don't do well after 175 or before 5 degrees
		#define SRVO_MAX_RANGE 175
		#define SRVO_MIN_RANGE 5
	#endif	
		
	//definitions for ImuSensor
	#ifdef _IMU_CALIBRATIONS

		//==Start Of Intergrated Code From Others
		// LSM303/LIS3MDL magnetometer calibration constants; use the Calibrate example from
		// the Pololu LSM303 or LIS3MDL library to find the right values for your board

		#define M_X_MIN -1000
		#define M_Y_MIN -1000
		#define M_Z_MIN -1000
		#define M_X_MAX +1000
		#define M_Y_MAX +1000
		#define M_Z_MAX +1000

		#define Kp_ROLLPITCH 0.02
		#define Ki_ROLLPITCH 0.00002
		#define Kp_YAW 1.2
		#define Ki_YAW 0.00002
		//==End Of Intergrated Code From Others
		
	#endif
	
		
		
	
	#ifdef _TEMP_CONSTANTS
		#define	TEMP_CONSTANT_T0	298.15
		#define	TEMP_CONSTANT_B	4050
		#define	TEMP_CONSTANT_R0	10000
	#endif	
			
		
	#ifdef _FIXED_RESISTORS
		
		#define RESISTOR_PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING											10000
		#define RESISTOR_PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING											10000
		#define RESISTOR_TEMPSENSOR_BEACONCCA_CENTERSIDE																10000
		#define RESISTOR_TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET												10000
		#define RESISTOR_PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING									10000
		#define RESISTOR_PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING											10000
		#define RESISTOR_PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING										10000
		#define RESISTOR_TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR									10000
		#define RESISTOR_TEMPSENSOR_DIGITALCCA_MIDDLESIDE																10000
		#define RESISTOR_PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING									10000
		#define RESISTOR_PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK			10000
		#define RESISTOR_PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING												10000
		#define RESISTOR_TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK														10000
		#define RESISTOR_GAS_BEACONCCA_RIGHTPOINTING																		20000 //I did not record down the value used, so this is just a guess for now
		#define RESISTOR_PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING										10000
		#define RESISTOR_PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK						10000
		#define RESISTOR_PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING										10000
		#define RESISTOR_TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE							10000
		
	#endif	
			
	

	
