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

/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/
//define Arduino 1: NAVI in order to use it's config pins
#ifndef _ARD_1_NAVI_H
	#define _ARD_1_NAVI_H
#endif

/********************************************************************/

#include <RoverConfig.h>



class LedController_NAVI : public virtual RoverReset {
public:
	LedController_NAVI(DelayCounter *);//constructor. (DelayCounter pointer)
	~LedController_NAVI();//destructor
	void setUniversalLEDMode(byte);//used for LED modes
	void setFogLightControl();
	void setUnderglowLightControl();
	void setIRBeaconLightControl();
	void setBlueBeaconLightControl();
	void setBeaconDirection(byte);//used in IR/blue beacon directional mode
	void setRoverMotion(byte);//used for LED motions
	void setErrorType(byte);//used for Error Mode
	void setDebugType(byte);//used for Debug Mode
	

	




	

//ADD SOME TIMERS
	
	
	
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:
	//Non-SW Resettable
	byte _ledPatternArray_HazardMode[] = { };
	byte _ledPatternArray_DemoMode[] = { };
	byte _ledPatternArray_MotionTurnLeft[] = { };
	byte _ledPatternArray_MotionTurnRight[] = { };
	byte _ledPatternArray_MotionBrake[] = { };
	
	//SW Resettable
	byte _ledPatternIndex = 0;//index of the led pattern array
	UnderglowLeds * _underglowLight;
	SideSignalLight* _leftSideSignal;
	SideSignalLight *_rightSideSignal;
	BeaconLightAssembly *_beaconLightAssy;
	HeadLightAssembly * _leftHeadLightAssy;
	HeadLightAssembly * _rightHeadLightAssy; 
	TailLightAssembly * _leftTailLightAssy;
	TailLightAssembly * _rightTailLightAssy;	
	
	DelayCounter * _counterPtr;//delay counter pointer
	//TEMPLATE//unsigned int _periodsForShortDelay;//holds the number of periods for the short delay
	//TEMPLATE//unsigned int _periodsForLongDelay;//holds the number of periods for the long delay
	
};

#endif 