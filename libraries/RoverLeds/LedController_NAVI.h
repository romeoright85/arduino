//LedController_NAVI.h
//Note: Can also reference DigitalLedTester.ino

#ifndef _LEDCONTROLLER_NAVI_H
#define _LEDCONTROLLER_NAVI_H

#ifndef _LED_STATE_BIT_FLAGS_
#define _LED_STATE_BIT_FLAGS_
#endif

#include <Arduino.h>
#include <RoverDebug.h>
#include <UnderglowLeds.h>
#include <SideSignalLight.h>
#include <BooleanBitFlags.h>
#include <RoverBitFlags.h>
#include <BeaconLightAssembly.h>
#include <HeadLightAssembly.h>
#include <TailLightAssembly.h>
#include <RoverReset.h>
#include <DelayCounter.h>




//============Debugging: Turn On All LEDs on Power On Reset
//Uncomment the flag below in order to turn on all LEDs at power on reset. (to see if all LEDs are function).
//#define _DEBUG_TURN_ON_ALL_LEDS_AT_POR_

//============End Debugging: Turn On All LEDs on Power On Reset



//============Debugging: Output Startup Mode Status
//Uncomment the flag below in order to print out the startup mode status
#define _DEBUG_OUTPUT_STARTUP_MODE_STATUS_

//============End Debugging: Output Startup Mode Status





/*
Notes on Usage:

Reference: "_LED_CONTROLLER_DEFINITIONS" in the RoverConfig.h file.


When you want to a Universal LED Mode (in general):
	
	Run setUniversalLEDMode(<<choose your mode>>) where
		the universal mode choices are listed in
		"_LED_CONTROLLER_DEFINITIONS" in the RoverConfig.h file.
		Then wait for the next iteration of runLedController() to
		run automatically in the background.



When you want set a Fog Light Mode:
	
	Run setFogLightMode(<<choose your fog mode here>>) where
		the fog mode choices are listed in
		"_LED_CONTROLLER_DEFINITIONS" in the RoverConfig.h file.
		It can be ran before or after setUniversalLEDMode().
	
	Run setUniversalLEDMode(<<choose your mode>>) as long as
		the mode is either LED_STANDARD_DAY_TIME_MODE, LED_NIGHT_TIME_MODE, LED_HAZARD_MODE is chosen.
		It can be ran before or after setFogLightMode().
		
	Then wait for the next iteration of runLedController() to
		run automatically in the background.

	
When you want set a Underglow Light Mode:

	Run setUnderglowLightMode(<<choose your underglow light mode here>>) where
		the Underglow Light mode choices are listed in
		"_LED_CONTROLLER_DEFINITIONS" in the RoverConfig.h file.
		It can be ran before or after setUniversalLEDMode().

	Run setUniversalLEDMode(<<choose your mode>>) as long as
		the mode is either LED_STANDARD_DAY_TIME_MODE, LED_NIGHT_TIME_MODE, LED_HAZARD_MODE is chosen.
		It can be ran before or after setUnderglowLightMode().
		
	Then wait for the next iteration of runLedController() to
		run automatically in the background.

When you want set a IR Beacon Light Mode:

	Run setIRBeaconLightMode(<<choose your IR Beacon mode here>>) where
		the IR Beacon mode choices are listed in
		"_LED_CONTROLLER_DEFINITIONS" in the RoverConfig.h file.
		It can be ran before or after setUniversalLEDMode().

	Run setUniversalLEDMode(<<choose your mode>>) as long as
		the mode is either LED_STANDARD_DAY_TIME_MODE, LED_NIGHT_TIME_MODE, LED_HAZARD_MODE is chosen.
		It can be ran before or after setIRBeaconLightMode().

	Then wait for the next iteration of runLedController() to
		run automatically in the background.


When you want set a Blue Beacon Light Mode:

	Run setBlueBeaconLightMode(<<choose your Blue Beacon mode here>>) where
		the Blue Beacon mode choices are listed in
		"_LED_CONTROLLER_DEFINITIONS" in the RoverConfig.h file.
		It can be ran before or after setUniversalLEDMode().

	Run setUniversalLEDMode(<<choose your mode>>) as long as
		the mode is either LED_STANDARD_DAY_TIME_MODE, LED_NIGHT_TIME_MODE, LED_HAZARD_MODE is chosen.
		It can be ran before or after setBlueBeaconLightMode().

	Then wait for the next iteration of runLedController() to
		run automatically in the background.

When you want set a Beacon Direction Mode:

	Run setBeaconDirection(<<choose your Beacon Direction here>>) where
		the Beacon Direction choices are listed in
		"_LED_CONTROLLER_DEFINITIONS" in the RoverConfig.h file.
		It can be ran before or after setUniversalLEDMode() and setBlueBeaconLightMode(), in any order.


	Run either setBlueBeaconLightMode(LED_IR_BEACON_DIRECTIONAL_MODE) and/or
		setBlueBeaconLightMode(LED_BLUE_BEACON_DIRECTIONAL_MODE). Note
		that in theory both can be ran as IR and Blue Beacon LEDs are independent of each other.
		It can be ran before or after setUniversalLEDMode() and setBeaconDirection(), in any order.

	Run setUniversalLEDMode(<<choose your mode>>) as long as
		the mode is either LED_STANDARD_DAY_TIME_MODE, LED_NIGHT_TIME_MODE, LED_HAZARD_MODE is chosen.
		It can be ran before or after setBeaconDirection() and setBlueBeaconLightMode(), in any order.

	Then wait for the next iteration of runLedController() to
		run automatically in the background.


When you want to set a Rover Motion:

	Run setRoverMotion(<<choose your rover motion here>>) where
		the rover motion choices are listed in
		"_LED_CONTROLLER_DEFINITIONS" in the RoverConfig.h file.
		It can be ran before or after setUniversalLEDMode().

	Run setUniversalLEDMode(<<choose your mode>>) as long as
		the mode is either LED_STANDARD_DAY_TIME_MODE or LED_NIGHT_TIME_MODE is chosen.
		It can be ran before or after setRoverMotion().

	Then wait for the next iteration of runLedController() to
		run automatically in the background.


When you want to set an Error Type then:

	Run setErrorType(<<choose your error type here>>) where
		the error type choices are listed in
		"_LED_CONTROLLER_DEFINITIONS" in the RoverConfig.h file.
		It needs to be ran before setUniversalLEDMode(LED_ERROR_MODE) as it
		tells what setUniversalLEDMode() to initialize the LEDs to.

	Run setUniversalLEDMode(LED_ERROR_MODE). It needs to run after
		setErrorType() as it initializes the LEDs based on the error type.

	Then wait for the next iteration of runLedController() to
		run automatically in the background.


When you want to set a userDiscreteLEDControl:

	Run setUniversalLEDMode(LED_DEBUG_MODE). It needs to run before
		userDiscreteLEDControl() as it gives permission for userDiscreteLEDControl() to execute.

	Run userDiscreteLEDControl(<<choose the LED name here>>,<<choose the LED state here>>) where
		the LED name choices are listed in
		"_LED_CONTROLLER_DEFINITIONS" in the RoverConfig.h file. And
		where the LED state is either LED_OFF or LED_ON.

	Then wait for the next iteration of runLedController() to
		run automatically in the background.

*/

/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/
//define Arduino 1: NAVI in order to use it's config pins
#ifndef _ARD_1_NAVI_H
	#define _ARD_1_NAVI_H
#endif

#ifndef _LED_CONTROLLER_DEFINITIONS
	#define _LED_CONTROLLER_DEFINITIONS
#endif

/********************************************************************/

#include <RoverConfig.h>



class LedController_NAVI : public virtual RoverReset {
public:
	LedController_NAVI(DelayCounter *, unsigned int, unsigned int);//constructor. (DelayCounter pointer, periods for short delay, periods for long delay)
	~LedController_NAVI();//destructor
	void runLedController();//runs the led controller with the desired light pattern(s). This function should be called in every iteration of the Arduino loop()
	void setUniversalLEDMode(byte);//(which Universal LED Modes) used for LED modes
	void setHazardLightsMode(byte);//(which Hazard Lights State)	
	void setFogLightMode(byte);//(which Fog Lights State)
	void setUnderglowLightMode(byte);//(which Underglow Light State)
	void setIRBeaconLightMode(byte);//(which IR Beacon State)
	void setBlueBeaconLightMode(byte);//(which Blue Beacon State)
	void setBeaconDirection(byte);//(which Beacon LED Direction) used in IR/blue beacon directional mode
	void setRoverMotion(byte);//(which Rover Motion) used for LED motions
	void setErrorType(byte);//(which LED Error Types) used for Error Mode
	void userDiscreteLEDControl(byte, byte);//(which led name, desired led state). This function should only be called when there is a received command (i.e. from CMNC) to control the LEDs. Ultimately this function just calls the private function discreteLEDControl() but after using some logic to ensure it's in the right mode (i.e. LED_DEBUG_MODE). The LED state is either LED_OFF or LED_ON.
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:
	//Non-SW Resettable
			
	
	void autoIncrementIndexCounter(byte &, byte);//(index counter, max index value to roll over and reset the counter)
	void resetIndexCounter(byte &);//(index counter) resets the pattern index counter
	void discreteLEDControl(byte, byte);//(which led name, desired led state). Use this to set the state of the LED. The state can be overwritten with a higher priority state by calling this function again. The LED won't change states until executeFinalLEDStates() is called. And executeFinalLEDStates() should be called after all states have been finalized.
	void runIRBeaconDirectionalControl(byte);//(LED Direction) controls the IR Beacon based on the given LED Direction
	void runBlueBeaconDirectionalControl(byte);//(LED Direction) controls the Blue Beacon based on the given LED Direction
	void executeFinalLEDStates();//controls the LEDs based on the finalized settings (after overriding priorities)
	unsigned int _periodsForLongDelay = 0;
	unsigned int _periodsForShortDelay = 0;
	
	byte _ALL_LED_NAMES[29] = {
		LED_NAME_FRONT_BLUE_BEACON,
		LED_NAME_FRONT_RIGHT_IR_BEACON,
		LED_NAME_RIGHT_BLUE_BEACON,
		LED_NAME_BACK_RIGHT_IR_BEACON,
		LED_NAME_BACK_BLUE_BEACON,
		LED_NAME_BACK_LEFT_IR_BEACON,
		LED_NAME_LEFT_BLUE_BEACON,			
		LED_NAME_FRONT_LEFT_IR_BEACON,
		LED_NAME_LEFT_SIDE_SIGNAL_LIGHT,		
		LED_NAME_LEFT_FOG_HEADLIGHT,
		LED_NAME_LEFT_SIGNAL_HEADLIGHT,
		LED_NAME_LEFT_HIGHBEAM_HEADLIGHT,
		LED_NAME_RIGHT_HIGHBEAM_HEADLIGHT,
		LED_NAME_RIGHT_SIGNAL_HEADLIGHT,
		LED_NAME_RIGHT_FOG_HEADLIGHT,		
		LED_NAME_RIGHT_SIDE_SIGNAL_LIGHT,			
		LED_NAME_RIGHT_WHITE_TAILLIGHT,
		LED_NAME_RIGHT_RED1_TAILLIGHT,
		LED_NAME_RIGHT_RED5_TAILLIGHT,
		LED_NAME_RIGHT_RED2_TAILLIGHT,			
		LED_NAME_RIGHT_RED4_TAILLIGHT,
		LED_NAME_RIGHT_RED3_TAILLIGHT,
		LED_NAME_LEFT_RED3_TAILLIGHT,
		LED_NAME_LEFT_RED4_TAILLIGHT,
		LED_NAME_LEFT_RED2_TAILLIGHT,
		LED_NAME_LEFT_RED5_TAILLIGHT,			
		LED_NAME_LEFT_RED1_TAILLIGHT,
		LED_NAME_LEFT_WHITE_TAILLIGHT,
		LED_NAME_UNDERGLOW_LIGHT	
	};//Holds the names of all the LEDs, used for LED_ALL_OFF_MODE, LED_ALL_ON_MODE, and LED_DEMO_MODE. The order of these names is for the demo mode.

	
	//Hazard Mode
	byte _LED_NAMES_For_HazardMode[10] = {
		LED_NAME_RIGHT_SIGNAL_HEADLIGHT,
		LED_NAME_LEFT_SIGNAL_HEADLIGHT,
		LED_NAME_RIGHT_SIDE_SIGNAL_LIGHT,
		LED_NAME_LEFT_SIDE_SIGNAL_LIGHT,
		LED_NAME_RIGHT_RED1_TAILLIGHT,
		LED_NAME_RIGHT_RED2_TAILLIGHT,
		LED_NAME_RIGHT_RED3_TAILLIGHT,
		LED_NAME_LEFT_RED1_TAILLIGHT,
		LED_NAME_LEFT_RED2_TAILLIGHT,
		LED_NAME_LEFT_RED3_TAILLIGHT
	};
	//Pattern: Turn on all of the LEDs in the array, wait for the duration of the desired delay, then turn them all off, wait for the duration of the desired delay, and repeat (off, on)
	//Use a 500ms delay for the pattern
	
	
	//Demo Mode
	byte * _LED_NAMES_For_DemoMode = _ALL_LED_NAMES;
	//Pattern: Turn off the previous LED and then turn on the current LED, wait for the duration of the desired delay, then repeat
	//Use a 500ms delay for the pattern
	
	

	//IR Beacon LEDs
	byte _LED_NAMES_For_IRBeaconLEDs[4] = {
		LED_NAME_FRONT_RIGHT_IR_BEACON,
		LED_NAME_BACK_RIGHT_IR_BEACON,
		LED_NAME_BACK_LEFT_IR_BEACON,
		LED_NAME_FRONT_LEFT_IR_BEACON		
	};
	
	//Blue Beacon LEDs
	byte _LED_NAMES_For_BlueBeaconLEDs[4] = {
		LED_NAME_FRONT_BLUE_BEACON,
		LED_NAME_RIGHT_BLUE_BEACON,
		LED_NAME_BACK_BLUE_BEACON,
		LED_NAME_LEFT_BLUE_BEACON		
	};
	
	
	//Error Mode Arrays (for blinking)
	//Note: For now they all blink the headlights high beams, the reverse tail lights, and underglow lights. And the different taillights will be solid and change based on error type.
	byte _LED_NAMES_For_Error_Type_Generic_Health[5] = {
		LED_NAME_LEFT_HIGHBEAM_HEADLIGHT,
		LED_NAME_RIGHT_HIGHBEAM_HEADLIGHT,
		LED_NAME_RIGHT_WHITE_TAILLIGHT,
		LED_NAME_LEFT_WHITE_TAILLIGHT,
		LED_NAME_UNDERGLOW_LIGHT
	};
	byte _LED_NAMES_For_Error_Type_Generic_System[5] = {
		LED_NAME_LEFT_HIGHBEAM_HEADLIGHT,
		LED_NAME_RIGHT_HIGHBEAM_HEADLIGHT,
		LED_NAME_RIGHT_WHITE_TAILLIGHT,
		LED_NAME_LEFT_WHITE_TAILLIGHT,
		LED_NAME_UNDERGLOW_LIGHT
	};
	byte _LED_NAMES_For_Error_Type_SW_Reset[5] = {
		LED_NAME_LEFT_HIGHBEAM_HEADLIGHT,
		LED_NAME_RIGHT_HIGHBEAM_HEADLIGHT,
		LED_NAME_RIGHT_WHITE_TAILLIGHT,
		LED_NAME_LEFT_WHITE_TAILLIGHT
		,LED_NAME_UNDERGLOW_LIGHT
	};
	byte _LED_NAMES_For_Error_Type_Sync[5] = {
		LED_NAME_LEFT_HIGHBEAM_HEADLIGHT,
		LED_NAME_RIGHT_HIGHBEAM_HEADLIGHT,
		LED_NAME_RIGHT_WHITE_TAILLIGHT,
		LED_NAME_LEFT_WHITE_TAILLIGHT
		,LED_NAME_UNDERGLOW_LIGHT
	};
	byte _LED_NAMES_For_Error_Type_Invalid_State_Or_Mode[5] = {
		LED_NAME_LEFT_HIGHBEAM_HEADLIGHT,
		LED_NAME_RIGHT_HIGHBEAM_HEADLIGHT,
		LED_NAME_RIGHT_WHITE_TAILLIGHT,
		LED_NAME_LEFT_WHITE_TAILLIGHT,
		LED_NAME_UNDERGLOW_LIGHT
	};
	byte _LED_NAMES_For_Error_Type_Undefined[5] = {
		LED_NAME_LEFT_HIGHBEAM_HEADLIGHT,
		LED_NAME_RIGHT_HIGHBEAM_HEADLIGHT,
		LED_NAME_RIGHT_WHITE_TAILLIGHT,
		LED_NAME_LEFT_WHITE_TAILLIGHT,
		LED_NAME_UNDERGLOW_LIGHT
	};

	
	//Motion Left Turn
	byte _LED_NAMES_For_MotionTurnLeft_Headlight[1] = {
			LED_NAME_LEFT_SIGNAL_HEADLIGHT
	};
	//Pattern: Turn off all of the LEDs in the array, wait for the duration of the desired delay, stay off, wait for the duration of the desired delay, then turn them all on, wait for the duration of the desired delay, stay on, wait for the duration of the desired delay and repeat (off, off, off, off, on, on, on, on).
	//Note: This off-off then on-on pattern is so it can use the same 125ms delay used for tail lights, instead of having it's own 500ms delay.
	//Use a 125ms delay for the pattern
	
	
	byte _LED_NAMES_For_MotionTurnLeft_SideSignalLights[1] = {
			LED_NAME_LEFT_SIDE_SIGNAL_LIGHT
	};
	//Pattern: Turn off all of the LEDs in the array, wait for the duration of the desired delay, stay off, wait for the duration of the desired delay, then turn them all on, wait for the duration of the desired delay, stay on, wait for the duration of the desired delay and repeat (off, off, off, off, on, on, on, on).
	//Note: This off-off then on-on pattern is so it can use the same 125ms delay used for tail lights, instead of having it's own 500ms delay.
	//Use a 125ms delay for the pattern
	
	
	byte _LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part1[1] = {
			LED_NAME_LEFT_RED3_TAILLIGHT
	};
	//Pattern: Turn off all of the LEDs in the array, wait for the duration of the desired delay, then turn them all on, wait for x2 the duration of the desired delay, and repeat (off, on, off, off, off, on, off, off: repeat)
	//Use a 125ms delay for the pattern
	
	
	byte _LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part2[2] = {
			LED_NAME_LEFT_RED4_TAILLIGHT,
			LED_NAME_LEFT_RED2_TAILLIGHT
	};
	//Pattern: Turn off all of the LEDs in the array, wait for x2 the duration of the desired delay, then turn them all on, wait for x1 the duration of the desired delay, and repeat (off, off, on, off, off, off, on, off: repeat)
	//Use a 125ms delay for the pattern
	
	
	byte _LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part3[2] = {
			LED_NAME_LEFT_RED5_TAILLIGHT,			
			LED_NAME_LEFT_RED1_TAILLIGHT
	};		
	//Pattern: Turn off all of the LEDs in the array, wait for x3 the duration of the desired delay, then turn them all on, and repeat (off, off, off, on, off, off, off, on: repeat)
	//Use a 125ms delay for the pattern
		
		
	//Motion Right Turn
	byte _LED_NAMES_For_MotionTurnRight_Headlight[1] = {
			LED_NAME_RIGHT_SIGNAL_HEADLIGHT
	};
	//Pattern: Turn off all of the LEDs in the array, wait for the duration of the desired delay, stay off, wait for the duration of the desired delay, then turn them all on, wait for the duration of the desired delay, stay on, wait for the duration of the desired delay and repeat (off, off, off, off, on, on, on, on).
	//Note: This off-off then on-on pattern is so it can use the same 125ms delay used for tail lights, instead of having it's own 500ms delay.
	//Use a 125ms delay for the pattern
	
	
	
	byte _LED_NAMES_For_MotionTurnRight_SideSignalLights[1] = {
			LED_NAME_RIGHT_SIDE_SIGNAL_LIGHT
	};
	//Pattern: Turn off all of the LEDs in the array, wait for the duration of the desired delay, stay off, wait for the duration of the desired delay, then turn them all on, wait for the duration of the desired delay, stay on, wait for the duration of the desired delay and repeat (off, off, off, off, on, on, on, on).
	//Note: This off-off then on-on pattern is so it can use the same 125ms delay used for tail lights, instead of having it's own 500ms delay.
	//Use a 125ms delay for the pattern
	
	
	byte _LED_NAMES_For_MotionTurnRight_RightTaillight_Part1[1] = {
			LED_NAME_RIGHT_RED3_TAILLIGHT
	};
	//Pattern: Turn off all of the LEDs in the array, wait for the duration of the desired delay, then turn them all on, wait for x2 the duration of the desired delay, and repeat (off, on, off, off, off, on, off, off: repeat)
	//Use a 250ms delay for the pattern
	
	
	byte _LED_NAMES_For_MotionTurnRight_RightTaillight_Part2[2] = {
			LED_NAME_RIGHT_RED4_TAILLIGHT,
			LED_NAME_RIGHT_RED2_TAILLIGHT
	};
	//Pattern: Turn off all of the LEDs in the array, wait for x2 the duration of the desired delay, then turn them all on, wait for x1 the duration of the desired delay, and repeat (off, off, on, off, off, off, on, off: repeat)
	//Use a 125ms delay for the pattern
	
	
	byte _LED_NAMES_For_MotionTurnRight_RightTaillight_Part3[2] = {
			LED_NAME_RIGHT_RED5_TAILLIGHT,			
			LED_NAME_RIGHT_RED1_TAILLIGHT
	};		
	//Pattern: Turn off all of the LEDs in the array, wait for x3 the duration of the desired delay, then turn them all on, and repeat (off, off, off, on, off, off, off, on: repeat)
	//Use a 125ms delay for the pattern
	
	
	//Motion Brake
	byte _LED_NAMES_For_MotionBrake[10] = {
		LED_NAME_RIGHT_RED1_TAILLIGHT,
		LED_NAME_RIGHT_RED5_TAILLIGHT,
		LED_NAME_RIGHT_RED2_TAILLIGHT,
		LED_NAME_RIGHT_RED4_TAILLIGHT,
		LED_NAME_RIGHT_RED3_TAILLIGHT,
		LED_NAME_LEFT_RED3_TAILLIGHT,
		LED_NAME_LEFT_RED4_TAILLIGHT,
		LED_NAME_LEFT_RED2_TAILLIGHT,
		LED_NAME_LEFT_RED5_TAILLIGHT,
		LED_NAME_LEFT_RED1_TAILLIGHT
	};
	
	/*
		Pattern:
		Basic Pattern Concept: Flash, Flash, Pause, Solid on
		
		
		Turn off all of the LEDs in the array
		Wait for x2 the duration of the desired delay (i.e. 2x125= 250 ms)
		Turn on all of the LEDs in the array
		Wait for the duration of the desired delay (i.e. 125 ms)
		Turn off all of the LEDs in the array
		Wait for x2 the duration of the desired delay (i.e. 2x125= 250 ms)
		Turn on all of the LEDs in the array
		Wait for the duration of the desired delay (i.e. 125 ms)	
		Turn off all of the LEDs in the array
		Wait for x2 the duration of the desired delay (i.e. 2x125= 250 ms)
		Turn on all of the LEDs in the array
		Hold it on indefinitely until the mode is changed to something else
			
		(off, off, on, off, off, on, off, off, on-hold)
		
	*/
	//Use a 125ms delay for the pattern
		

	//SW Resettable
	
	byte _currentUniversalLEDMode = LED_ALL_OFF_MODE;//It holds the current universal LED Mode. The default (for the LedController_NAVI class) is LED_ALL_OFF_MODE.
	byte _currentRoverMotion = LED_MOTION_STANDARD;//holds the current Rover Motion
	byte _currentErrorState = LED_ERROR_TYPE_NONE;//holds the current error state
	byte _currentHazardLightsState = LED_HAZARDS_OFF;//holds the current hazard lights state
	byte _currentFogLightState = LED_FOG_OFF;//holds the current fog light state
	byte _currentUnderglowState = LED_UNDERGLOW_OFF;//holds the current underglow state	
	byte _currentIRBeaconState = LED_IR_BEACON_ALL_OFF;//holds the current IR Beacon State
	byte _currentBlueBeaconState = LED_BLUE_BEACON_ALL_OFF;//holds the current Blue Beacon State
	byte _currentBeaconLEDDirection = LED_DIRECTION_NONE;//holds the current Beacon LED Direction (shared between IR Beacons and Blue Beacons)
	byte * _arrayOfInterest = NULL;//shared variable, used to point to the current array of interest
	byte _arrayOfInterestSize = 0;//shared variable, used to hold the current array of interest's size
	//Note: Keep separate pattern index counters just in case one set of LEDs holds a pattern (like with braking) while others still should be incrementing
	byte _universalLEDModePatternIndexCounter = 0;//used to hold the pattern index counter for the universal LED modes
	byte _hazardLightsPatternIndexCounter = 0;//used to hold the pattern index counter for the hazard lights
	byte _roverMotionPatternIndexCounter = 0;//used to hold the pattern index counter for the rover motion
	byte _blueBeaconLEDsPatternIndexCounter = 0;//used to hold the pattern index counter for the blue beacon LEDs
	byte _irBeaconLEDsPatternIndexCounter = 0;//used to hold the pattern index counter for the IR Beacon LEDs
	
	
	
	//LED State Bit Flags, used to hold the on or off state of all the LEDs
	//Reference: RoverBitFlags.h
	//Set all the LEDs to default all off
	byte _ledStateFlagSet1 = _BTFG_LED_STATE_ALL_OFF_;
	byte _ledStateFlagSet2 = _BTFG_LED_STATE_ALL_OFF_;
	byte _ledStateFlagSet3 = _BTFG_LED_STATE_ALL_OFF_;
	byte _ledStateFlagSet4 = _BTFG_LED_STATE_ALL_OFF_;
	
	
	
	//Class Objects Pointers
	//Delay Counter Pointer
	DelayCounter * _counterPtr;
	//LED Objects
	UnderglowLeds * _underglowLight;
	SideSignalLight* _leftSideSignal;
	SideSignalLight *_rightSideSignal;
	BeaconLightAssembly *_beaconLightAssy;
	HeadLightAssembly * _leftHeadLightAssy;
	HeadLightAssembly * _rightHeadLightAssy; 
	TailLightAssembly * _leftTailLightAssy;
	TailLightAssembly * _rightTailLightAssy;	
	
	
	RoverReset * _resetArray[9] = {	
		this->_counterPtr,
		this->_underglowLight,
		this->_leftSideSignal,
		this->_rightSideSignal,
		this->_beaconLightAssy,
		this->_leftHeadLightAssy,
		this->_rightHeadLightAssy,
		this->_leftTailLightAssy,
		this->_rightTailLightAssy
	};
	
	
	
	
};

#endif