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

		#define IMU_M_X_MIN -1000
		#define IMU_M_Y_MIN -1000
		#define IMU_M_Z_MIN -1000
		#define IMU_M_X_MAX +1000
		#define IMU_M_Y_MAX +1000
		#define IMU_M_Z_MAX +1000

		#define IMU_Kp_ROLLPITCH 0.02
		#define IMU_Ki_ROLLPITCH 0.00002
		#define IMU_Kp_YAW 1.2
		#define IMU_Ki_YAW 0.00002
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
			
	

	
