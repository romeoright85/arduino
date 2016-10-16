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
		
	
	
	
	

	
