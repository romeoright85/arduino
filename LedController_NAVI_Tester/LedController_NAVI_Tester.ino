//Used for NAVI - 1


#ifndef _LED_STATE_BIT_FLAGS_
#define _LED_STATE_BIT_FLAGS_ //For RoverBitFlags.h
#endif

#include <LedController_NAVI.h>
#include <RoverConfig.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>
#include <BooleanBitFlags.h>	
#include <RoverBitFlags.h>	

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

//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast
#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ _MAIN_SERIAL_ //When using COMM Broadcast, reroute the PC USB output to the channel to MAIN instead
#else
	#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_
#endif



//Global Variables


DelayCounter * ledControllerDelayCounter = new DelayCounter(DELAY_100_PERIODS);//initialize it to count to 100 periods (so 100 periods x 5ms = 500ms). This is only the initial/default delay. It may change in the code dynamically as needed.
GlobalDelayTimer * ledControllerTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, ledControllerDelayCounter);//arbitrarily chose 5ms resolution for the timer. Can change this later to something else if I want
LedController_NAVI * ledController_NAVI = new LedController_NAVI(ledControllerDelayCounter, DELAY_50_PERIODS, DELAY_100_PERIODS);//the short delay is 50 periods (50x5ms=250ms) and the long delay is 100 periods (100x5ms=500ms)



RoverReset * resetArray[] = {
	ledControllerDelayCounter,
	ledControllerTimer,
	ledController_NAVI
};


void setup() {

	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	_MAIN_SERIAL_.begin(MAIN_BAUD_RATE);	
	
	_PC_USB_SERIAL_.flush();//waits for any outgoing serial data to complete
	_MAIN_SERIAL_.flush();//waits for any outgoing serial data to complete
	delay(50);
	
	//Setting Up Timer Interrupt
	OCR0A = 0x7F;//Set the timer to interrupt somewhere in the middle of it's count, say 127 aka 7F in hex (since Timer0 is 8 bit and counts from 0 to 255)
	TIMSK0 |= _BV(OCIE0A);//Activating the Timer Interrupt by setting the Mask Register
	/*
	Reference:
	https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers
	http://forum.arduino.cc/index.php?topic=3240.0
	https://protostack.com.au/2010/09/timer-interrupts-on-an-atmega168/
	*/
	
}


SIGNAL(TIMER0_COMPA_vect)//Interrupt Service Routine
{
	//Tasks always running in the background, called by the timer about every 1 ms
	//This will allow the millis value to be checked every millisecond and not get missed.
	//Timer(s)
	ledControllerTimer->Running();//activate the timer
	
}

void loop() {
	

	
	ledController_NAVI->runLedController();
	

	char rxData;
	

	if (_SERIAL_DEBUG_CHANNEL_.available() > 0)
	{
		rxData = (char)_SERIAL_DEBUG_CHANNEL_.read();//Get data from COMM or PC USB

		delay(1);

		switch (rxData)
		{
			case 'a':
				_SERIAL_DEBUG_CHANNEL_.println(F("UM: All Off"));//UM = Universal Mode
				ledController_NAVI->setUniversalLEDMode(LED_ALL_OFF_MODE);
				break;
			case 'b':
				_SERIAL_DEBUG_CHANNEL_.println(F("UM: All On"));//UM = Universal Mode
				ledController_NAVI->setUniversalLEDMode(LED_ALL_ON_MODE);
				break;
			case 'c':
				_SERIAL_DEBUG_CHANNEL_.println(F("UM: Std Day"));//UM = Universal Mode
				ledController_NAVI->setUniversalLEDMode(LED_STANDARD_DAY_TIME_MODE);
				break;
			case 'd':
				_SERIAL_DEBUG_CHANNEL_.println(F("UM: Night"));//UM = Universal Mode
				ledController_NAVI->setUniversalLEDMode(LED_NIGHT_TIME_MODE);
				break;
			case 'e':
				_SERIAL_DEBUG_CHANNEL_.println(F("UM: Hazard"));//UM = Universal Mode
				ledController_NAVI->setUniversalLEDMode(LED_HAZARD_MODE);
				break;
			case 'f':
				_SERIAL_DEBUG_CHANNEL_.println(F("UM: Demo"));//UM = Universal Mode
				ledController_NAVI->setUniversalLEDMode(LED_DEMO_MODE);
				break;
			case 'g':
				_SERIAL_DEBUG_CHANNEL_.println(F("UM: Error"));//UM = Universal Mode
				ledController_NAVI->setUniversalLEDMode(LED_ERROR_MODE);
				break;
			case 'h':
				_SERIAL_DEBUG_CHANNEL_.println(F("UM: Stealth"));//UM = Universal Mode
				ledController_NAVI->setUniversalLEDMode(LED_STEALTH_MODE);
				break;
			case 'i':
				_SERIAL_DEBUG_CHANNEL_.println(F("UM: Debug"));//UM = Universal Mode
				ledController_NAVI->setUniversalLEDMode(LED_DEBUG_MODE);
				break;
			case 'j':
				_SERIAL_DEBUG_CHANNEL_.println(F("FS: Off"));//FG = Fog State
				ledController_NAVI->setFogLightMode(LED_FOG_OFF);
				break;
			case 'k':
				_SERIAL_DEBUG_CHANNEL_.println(F("FS: On"));//FG = Fog State
				ledController_NAVI->setFogLightMode(LED_FOG_ON);
				break;
			case 'l':
				_SERIAL_DEBUG_CHANNEL_.println(F("FS: Neutral"));//FG = Fog State
				ledController_NAVI->setFogLightMode(LED_FOG_NEUTRAL);
				break;
			case 'm':
				_SERIAL_DEBUG_CHANNEL_.println(F("UG: Off"));//UG = Underglow
				ledController_NAVI->setUnderglowLightMode(LED_UNDERGLOW_OFF);
				break;
			case 'n':
				_SERIAL_DEBUG_CHANNEL_.println(F("UG: On"));//UG = Underglow
				ledController_NAVI->setUniversalLEDMode(LED_UNDERGLOW_ON);
				break;
			case 'o':
				_SERIAL_DEBUG_CHANNEL_.println(F("UG: Neutral"));//UG = Underglow
				ledController_NAVI->setUnderglowLightMode(LED_UNDERGLOW_NEUTRAL);
				break;
			case 'p':
				_SERIAL_DEBUG_CHANNEL_.println(F("IR: All Off"));//IR = IR Beacon
				ledController_NAVI->setIRBeaconLightMode(LED_IR_BEACON_ALL_OFF);
				break;
			case 'q':
				_SERIAL_DEBUG_CHANNEL_.println(F("IR: All On"));//IR = IR Beacon
				ledController_NAVI->setIRBeaconLightMode(LED_IR_BEACON_ALL_ON);
				break;
			case 'r':
				_SERIAL_DEBUG_CHANNEL_.println(F("IR: Drctnl"));//IR = IR Beacon
				ledController_NAVI->setIRBeaconLightMode(LED_IR_BEACON_DIRECTIONAL_MODE);
				break;
			case 's':
				_SERIAL_DEBUG_CHANNEL_.println(F("IR: Neutral"));//IR = IR Beacon
				ledController_NAVI->setIRBeaconLightMode(LED_IR_BEACON_ALL_NEUTRAL);
				break;
			case 't':
				_SERIAL_DEBUG_CHANNEL_.println(F("BL: All Off"));//BL = Blue Beacon
				ledController_NAVI->setBlueBeaconLightMode(LED_BLUE_BEACON_ALL_OFF);
				break;
			case 'u':
				_SERIAL_DEBUG_CHANNEL_.println(F("BL: All On"));//BL = Blue Beacon
				ledController_NAVI->setBlueBeaconLightMode(LED_BLUE_BEACON_ALL_ON);
				break;
			case 'v':
				_SERIAL_DEBUG_CHANNEL_.println(F("BL: Drctnl"));//BL = Blue Beacon
				ledController_NAVI->setBlueBeaconLightMode(LED_BLUE_BEACON_DIRECTIONAL_MODE);
				break;
			case 'w':
				_SERIAL_DEBUG_CHANNEL_.println(F("BL: Neutral"));//BL = Blue Beacon
				ledController_NAVI->setBlueBeaconLightMode(LED_BLUE_BEACON_ALL_NEUTRAL);
				break;
			case 'x':
				_SERIAL_DEBUG_CHANNEL_.println(F("DN: None"));//DN = Direction
				ledController_NAVI->setBeaconDirection(LED_DIRECTION_NONE);
				break;
			case 'y':
				_SERIAL_DEBUG_CHANNEL_.println(F("DN: Front"));//DN = Direction
				ledController_NAVI->setBeaconDirection(LED_DIRECTION_FRONT);
				break;
			case 'z':
				_SERIAL_DEBUG_CHANNEL_.println(F("DN: Front Right"));//DN = Direction
				ledController_NAVI->setBeaconDirection(LED_DIRECTION_FRONT_RIGHT);
				break;
			case 'A':
				_SERIAL_DEBUG_CHANNEL_.println(F("DN: Right"));//DN = Direction
				ledController_NAVI->setBeaconDirection(LED_DIRECTION_RIGHT);
				break;
			case 'B':
				_SERIAL_DEBUG_CHANNEL_.println(F("DN: Rear Right"));//DN = Direction
				ledController_NAVI->setBeaconDirection(LED_DIRECTION_REAR_RIGHT);
				break;
			case 'C':
				_SERIAL_DEBUG_CHANNEL_.println(F("DN: Rear"));//DN = Direction
				ledController_NAVI->setBeaconDirection(LED_DIRECTION_REAR);
				break;
			case 'D':
				_SERIAL_DEBUG_CHANNEL_.println(F("DN: Rear Left"));//DN = Direction
				ledController_NAVI->setBeaconDirection(LED_DIRECTION_REAR_LEFT);
				break;
			case 'E':
				_SERIAL_DEBUG_CHANNEL_.println(F("DN: Left"));//DN = Direction
				ledController_NAVI->setBeaconDirection(LED_DIRECTION_LEFT);
				break;
			case 'F':
				_SERIAL_DEBUG_CHANNEL_.println(F("DN: Front Left"));//DN = Direction
				ledController_NAVI->setBeaconDirection(LED_DIRECTION_FRONT_LEFT);
				break;
			case 'G':
				_SERIAL_DEBUG_CHANNEL_.println(F("RM: Std"));//RM = Rover Motion
				ledController_NAVI->setRoverMotion(LED_MOTION_STANDARD);
				break;
			case 'H':
				_SERIAL_DEBUG_CHANNEL_.println(F("RM: Trn Left"));//RM = Rover Motion
				ledController_NAVI->setRoverMotion(LED_MOTION_TURN_LEFT);
				break;
			case 'I':
				_SERIAL_DEBUG_CHANNEL_.println(F("RM: Trn Right"));//RM = Rover Motion
				ledController_NAVI->setRoverMotion(LED_MOTION_TURN_RIGHT);
				break;
			case 'J':
				_SERIAL_DEBUG_CHANNEL_.println(F("RM: Brake"));//RM = Rover Motion
				ledController_NAVI->setRoverMotion(LED_MOTION_BRAKE);
				break;
			case 'K':
				_SERIAL_DEBUG_CHANNEL_.println(F("RM: Reverse"));//RM = Rover Motion
				ledController_NAVI->setRoverMotion(LED_MOTION_REVERSE);
				break;
			case 'L':
				_SERIAL_DEBUG_CHANNEL_.println(F("ET: None"));//ET = Error Type
				ledController_NAVI->setRoverMotion(LED_ERROR_TYPE_NONE);
				break;
			case 'M':
				_SERIAL_DEBUG_CHANNEL_.println(F("ET: Gen Health"));//ET = Error Type
				ledController_NAVI->setRoverMotion(LED_ERROR_TYPE_GENERIC_HEALTH);
				break;
			case 'N':
				_SERIAL_DEBUG_CHANNEL_.println(F("ET: Gen Sys"));//ET = Error Type
				ledController_NAVI->setRoverMotion(LED_ERROR_TYPE_GENERIC_SYSTEM);
				break;
			case 'O':
				_SERIAL_DEBUG_CHANNEL_.println(F("ET: SW Rst"));//ET = Error Type
				ledController_NAVI->setRoverMotion(LED_ERROR_TYPE_SW_RESET);
				break;
			case 'P':
				_SERIAL_DEBUG_CHANNEL_.println(F("ET: Sync"));//ET = Error Type
				ledController_NAVI->setRoverMotion(LED_ERROR_TYPE_SYNC);
				break;
			case 'Q':
				_SERIAL_DEBUG_CHANNEL_.println(F("ET: Invd Ste/Mde"));//ET = Error Type
				ledController_NAVI->setRoverMotion(LED_ERROR_TYPE_INVALID_STATE_OR_MODE);
				break;
			case 'R':
				_SERIAL_DEBUG_CHANNEL_.println(F("ET: Undfnd"));//ET = Error Type
				ledController_NAVI->setRoverMotion(LED_ERROR_TYPE_UNDEFINED);
				break;
			default:
				_SERIAL_DEBUG_CHANNEL_.println(F("INVALID OPTION"));
				break;
		}//end switch
	}//end if
	

	


}
