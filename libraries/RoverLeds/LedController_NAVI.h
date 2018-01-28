//LedController_NAVI.h
//Note: Can also reference DigitalLedTester.ino

#ifndef _LEDCONTROLLER_NAVI_H
#define _LEDCONTROLLER_NAVI_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <UnderglowLeds.h>
#include <SideSignalLight.h>
#include <BeaconLightAssembly.h>
#include <HeadLightAssembly.h>
#include <TailLightAssembly.h>
#include <RoverReset.h>
#include <DelayCounter.h>


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
	LedController_NAVI(DelayCounter *);//constructor. (DelayCounter pointer)
	~LedController_NAVI();//destructor
	void runLedController();//runs the led controller with the desired light pattern(s). This function should be called in every interation of the Arduino loop()
	void allOn();//turn on all LEDs
	void allOff();//turn off all LEDs
	void setUniversalLEDMode(byte);//(which Universal LED Modes) used for LED modes
	void setFogLightControl(byte);//(which Fog Lights State)
	void setUnderglowLightControl(byte);//(which Underglow Light State)
	void setIRBeaconLightControl(byte);//(which IR Beacon State)
	void setBlueBeaconLightControl(byte);//(which Blue Beacon State)
	void setBeaconDirection(byte);//(which Beacon LED Direction) used in IR/blue beacon directional mode
	void setRoverMotion(byte);//(which Rover Motion) used for LED motions
	void setErrorType(byte);//(which LED Error Types) used for Error Mode
	void setDebugType(byte);//(which LED Debug Types) used for Debug Mode
	void discreteLEDControl(byte, byte);//(which led name, desired led state)
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:
	//Non-SW Resettable
			
	
	
		
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
		LED_NAME_LEFT_HIGHBEAM_HEADLIGHT,
		LED_NAME_LEFT_SIGNAL_HEADLIGHT,
		LED_NAME_LEFT_FOG_HEADLIGHT,
		LED_NAME_RIGHT_FOG_HEADLIGHT,			
		LED_NAME_RIGHT_SIGNAL_HEADLIGHT,			
		LED_NAME_RIGHT_HIGHBEAM_HEADLIGHT,
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
	};//Holds the names of all the LEDs

	
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
	//Pattern: Turn on all of the LEDs in the array, wait for the duration of the desired delay, then turn them all off, and repeat
	//Use a 500ms delay for the pattern
	
	
	//Demo Mode
	byte _LED_NAMES_For_DemoMode[29] = {
		LED_NAME_FRONT_BLUE_BEACON,
		LED_NAME_FRONT_RIGHT_IR_BEACON,
		LED_NAME_RIGHT_BLUE_BEACON,
		LED_NAME_BACK_RIGHT_IR_BEACON,
		LED_NAME_BACK_BLUE_BEACON,
		LED_NAME_BACK_LEFT_IR_BEACON,
		LED_NAME_LEFT_BLUE_BEACON,			
		LED_NAME_FRONT_LEFT_IR_BEACON,
		LED_NAME_LEFT_SIDE_SIGNAL_LIGHT,
		LED_NAME_LEFT_HIGHBEAM_HEADLIGHT,
		LED_NAME_LEFT_SIGNAL_HEADLIGHT,
		LED_NAME_LEFT_FOG_HEADLIGHT,
		LED_NAME_RIGHT_FOG_HEADLIGHT,			
		LED_NAME_RIGHT_SIGNAL_HEADLIGHT,			
		LED_NAME_RIGHT_HIGHBEAM_HEADLIGHT,
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
	};
	//Pattern: Turn off the previous LED and then turn on the current LED, wait for the duration of the desired delay, then repeat
	//Use a 500ms delay for the pattern
	
	
	//Motion Left Turn
	byte _LED_NAMES_For_MotionTurnLeft_Headlight[1] = {
			LED_NAME_LEFT_SIGNAL_HEADLIGHT
	};
	//Pattern: Turn on all of the LEDs in the array, wait for the duration of the desired delay, then turn them all off, and repeat
	//Use a 500ms delay for the pattern
	byte _LED_NAMES_For_MotionTurnLeft_SideSignalLights[1] = {
			LED_NAME_LEFT_SIDE_SIGNAL_LIGHT
	};
	//Pattern: Turn on all of the LEDs in the array, wait for the duration of the desired delay, then turn them all off, and repeat
	//Use a 500ms delay for the pattern
	byte _LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part1[1] = {
			LED_NAME_LEFT_RED3_TAILLIGHT
	};
	//Pattern: Turn on all of the LEDs in the array, wait for the duration of the desired delay, then turn them all off, wait for x2 the duration of the desired delay, and repeat
	//Use a 500ms delay for the pattern
	byte _LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part2[2] = {
			LED_NAME_LEFT_RED4_TAILLIGHT,
			LED_NAME_LEFT_RED2_TAILLIGHT
	};
	//Pattern: Turn off all of the LEDs in the array, wait for the duration of the desired delay, then turn them all on, wait for the duration of the desired delay, and repeat
	//Use a 500ms delay for the pattern
	byte _LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part3[2] = {
			LED_NAME_LEFT_RED5_TAILLIGHT,			
			LED_NAME_LEFT_RED1_TAILLIGHT
	};		
	//Pattern: Turn off all of the LEDs in the array, wait for x2 the duration of the desired delay, then turn them all on, wait for the duration of the desired delay, and repeat
	//Use a 500ms delay for the pattern
		
		
	//Motion Right Turn
	byte _LED_NAMES_For_MotionTurnRight_Headlight[1] = {
			LED_NAME_RIGHT_SIGNAL_HEADLIGHT
	};
	//Pattern: Turn on all of the LEDs in the array, wait for the duration of the desired delay, then turn them all off, and repeat
	//Use a 500ms delay for the pattern
	byte _LED_NAMES_For_MotionTurnRight_SideSignalLights[1] = {
			LED_NAME_RIGHT_SIDE_SIGNAL_LIGHT
	};
	//Pattern: Turn on all of the LEDs in the array, wait for the duration of the desired delay, then turn them all off, and repeat
	//Use a 500ms delay for the pattern
	byte _LED_NAMES_For_MotionTurnLeft_RightTaillight_Part1[1] = {
			LED_NAME_RIGHT_RED3_TAILLIGHT
	};
	//Pattern: Turn on all of the LEDs in the array, wait for the duration of the desired delay, then turn them all off, wait for x2 the duration of the desired delay, and repeat
	//Use a 500ms delay for the pattern
	byte _LED_NAMES_For_MotionTurnLeft_RightTaillight_Part2[2] = {
			LED_NAME_RIGHT_RED4_TAILLIGHT,
			LED_NAME_RIGHT_RED2_TAILLIGHT
	};
	//Pattern: Turn off all of the LEDs in the array, wait for the duration of the desired delay, then turn them all on, wait for the duration of the desired delay, and repeat
	//Use a 500ms delay for the pattern
	byte _LED_NAMES_For_MotionTurnLeft_RightTaillight_Part3[2] = {
			LED_NAME_RIGHT_RED5_TAILLIGHT,			
			LED_NAME_RIGHT_RED1_TAILLIGHT
	};		
	//Pattern: Turn off all of the LEDs in the array, wait for x2 the duration of the desired delay, then turn them all on, wait for the duration of the desired delay, and repeat
	//Use a 500ms delay for the pattern
	
	
	
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
	//Pattern: Turn on all of the LEDs in the array, wait for the duration of the desired delay, then turn them all off, wait for the duration of the desired delay, turn on all of the LEDs in the array, wait for the duration of the desired delay, then turn them all off, wait for the duration of the desired delay, turn on all of the LEDs in the array and hold indefinitely until the mode is changed to something else
	//Use a 250ms delay for the pattern	
		

	//SW Resettable
	DelayCounter * _counterPtr;//delay counter pointer
	
	byte _currentUniversalLEDMode = LED_ALL_OFF_MODE;//holds the current universal LED Mode
	byte _arrayOfInterestSize = 0;//shared variable, used to hold the current array of interest's size
	byte _currentPatternIndex = 0;//shared variable, used to hold the current pattern index

	UnderglowLeds * _underglowLight;
	SideSignalLight* _leftSideSignal;
	SideSignalLight *_rightSideSignal;
	BeaconLightAssembly *_beaconLightAssy;
	HeadLightAssembly * _leftHeadLightAssy;
	HeadLightAssembly * _rightHeadLightAssy; 
	TailLightAssembly * _leftTailLightAssy;
	TailLightAssembly * _rightTailLightAssy;	
	
	
};

#endif 