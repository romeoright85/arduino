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
	LedController_NAVI();//constructor
	~LedController_NAVI();//destructor
	void allOn();//turns all LEDs on
	void allOff();//turns all LEDs off	
	
	
//WRITE ME LATER
brake();
leftTurn();
rightTurn();
nightLightsOn();
underglowOn();
fogOn();
reverse();
hazardBlink();
//ADD SOME TIMERS
	
	
	
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:
	//Non-SW Resettable
	//SW Resettable
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