#include <LedController_NAVI.h>


LedController_NAVI::LedController_NAVI(DelayCounter * counterPtr)
{
	this->_counterPtr = counterPtr;//take the passed counter pointer in the constructor argument and save it to the object member counter pointer
	
	this->_underglowLight = new UnderglowLeds(UNDERGLOW_PIN);
	this->_leftSideSignal = new SideSignalLight(SIDE_LEFT_SIGNAL_PIN);
	this->_rightSideSignal = new SideSignalLight(SIDE_RIGHT_SIGNAL_PIN);
	this->_beaconLightAssy = new BeaconLightAssembly(FRONT_LEFT_BEACON_IR_PIN, BACK_LEFT_BEACON_IR_PIN, BACK_RIGHT_BEACON_IR_PIN, FRONT_RIGHT_BEACON_IR_PIN, LEFT_BEACON_BLUE_PIN, BACK_BEACON_BLUE_PIN, RIGHT_BEACON_BLUE_PIN, FRONT_BEACON_BLUE_PIN);
	this->_leftHeadLightAssy = new HeadLightAssembly(LEFT_HIGHBEAM_HEADLIGHT_PIN, LEFT_SIGNAL_HEADLIGHT_PIN, LEFT_FOG_HEADLIGHT_PIN);
	this->_rightHeadLightAssy = new HeadLightAssembly(RIGHT_HIGHBEAM_HEADLIGHT_PIN, RIGHT_SIGNAL_HEADLIGHT_PIN, RIGHT_FOG_HEADLIGHT_PIN); 
	this->_leftTailLightAssy = new TailLightAssembly(LEFT_RED_TAILLIGHT_1_PIN, LEFT_RED_TAILLIGHT_2_PIN, LEFT_RED_TAILLIGHT_3_PIN, LEFT_RED_TAILLIGHT_4_PIN, LEFT_RED_TAILLIGHT_5_PIN, LEFT_WHITE_TAILLIGHT_PIN);
	this->_rightTailLightAssy = new TailLightAssembly(RIGHT_RED_TAILLIGHT_1_PIN, RIGHT_RED_TAILLIGHT_2_PIN, RIGHT_RED_TAILLIGHT_3_PIN, RIGHT_RED_TAILLIGHT_4_PIN, RIGHT_RED_TAILLIGHT_5_PIN, RIGHT_WHITE_TAILLIGHT_PIN);
		
}
LedController_NAVI::~LedController_NAVI()
{
	//do nothing
}

void LedController_NAVI::runLedController()
{

//WRITE ME LATER
//STILL NEED TO ADD THE DELAY DURATION LOGIC HERE
//ALSO STILL NEED TO PICK THE DURATION DELAYS. Possibly use a counter to count multiples of the lowest common denominator of the durations.

	switch(this->_currentUniversalLEDMode)
	{
		case LED_ALL_OFF_MODE:
			for(byte i = 0; i < this->_arrayOfInterestSize; i++)
			{
				//Note: The _currentPatternIndex is not needed in this mode.
				discreteLEDControl( this->_ALL_LED_NAMES[ i ], LED_OFF );//turn off all the elements in the array
			}//end for
			break;
		case LED_ALL_ON_MODE:
			for(byte i = 0; i < this->_arrayOfInterestSize; i++)
			{
				//Note: The _currentPatternIndex is not needed in this mode.
				discreteLEDControl( this->_ALL_LED_NAMES[ i ], LED_ON );//turn off all the elements in the array
			}//end for
			break;
		case LED_STANDARD_DAY_TIME_MODE:
			//Do nothing that is recurring.
			break;
		case LED_NIGHT_TIME_MODE:
			//Do nothing that is recurring.
			break;
		case LED_HAZARD_MODE:
			if( this->_currentPatternIndex == 0)//for the first element in the array
			{
				discreteLEDControl( this->_LED_NAMES_For_HazardMode[ this->_arrayOfInterestSize - this->_currentPatternIndex ], LED_OFF );//the last element in the array (the last element = arraySize - currentIndex)
				
				discreteLEDControl( this->_LED_NAMES_For_HazardMode[ this->_currentPatternIndex ], LED_ON );//the current element in the array
			}//end if
			else//for all other elements
			{
				discreteLEDControl( this->_LED_NAMES_For_HazardMode[ this->_currentPatternIndex - 1 ], LED_OFF );//the previous element in the array
				discreteLEDControl( this->_LED_NAMES_For_HazardMode[ this->_currentPatternIndex ], LED_ON );//the current element in the array
			}//end else		
			break;
		case LED_DEMO_MODE:
			//WRITE ME LATER
			break;
		case LED_ERROR_MODE:
			//WRITE ME LATER
			break;		
		case LED_STEALTH_MODE:
			//WRITE ME LATER
			break;
		case LED_DEBUG_MODE:
			//WRITE ME LATER
			break;			
		default:
			//WRITE ME LATER
			break;
	}//end switch
	

	
	//increment counter for the next iteration
	this->_currentPatternIndex++;
	
	if( _currentPatternIndex >= this->_arrayOfInterestSize )
	{
		this->_currentPatternIndex = 0;//reset the counter once it has reached (or surpassed) the _arrayOfInterestSize
	}//end if

}



void LedController_NAVI::allOn()
{
	//Turn on All LEDs
	this->_underglowLight->turnOn();
	this->_leftSideSignal->turnOn();
	this->_rightSideSignal->turnOn();
	this->_beaconLightAssy->turnOn(FRONT_LEFT_IR_BEACON, BACK_LEFT_IR_BEACON, BACK_RIGHT_IR_BEACON, FRONT_RIGHT_IR_BEACON, LEFT_BLUE_BEACON, BACK_BLUE_BEACON, RIGHT_BLUE_BEACON, FRONT_BLUE_BEACON);
	this->_leftHeadLightAssy->turnOn(HIGHBEAM_HEADLIGHT, SIGNAL_HEADLIGHT, FOG_HEADLIGHT);
	this->_rightHeadLightAssy->turnOn(HIGHBEAM_HEADLIGHT, SIGNAL_HEADLIGHT, FOG_HEADLIGHT);
	this->_leftTailLightAssy->turnOn(RED1_TAILLIGHT, RED2_TAILLIGHT, RED3_TAILLIGHT, RED4_TAILLIGHT, RED5_TAILLIGHT, WHITE_TAILLIGHT);	
	this->_rightTailLightAssy->turnOn(RED1_TAILLIGHT, RED2_TAILLIGHT, RED3_TAILLIGHT, RED4_TAILLIGHT, RED5_TAILLIGHT, WHITE_TAILLIGHT);	
	
}
void LedController_NAVI::allOff()
{
	//Note: Reset could also have been used as well. But to make the code more clear to understand and read, the off command was used explicitly.
	
	//Turn off All LEDs
	this->_underglowLight->turnOff();
	this->_leftSideSignal->turnOff();
	this->_rightSideSignal->turnOff();
	this->_beaconLightAssy->turnOff(FRONT_LEFT_IR_BEACON, BACK_LEFT_IR_BEACON, BACK_RIGHT_IR_BEACON, FRONT_RIGHT_IR_BEACON, LEFT_BLUE_BEACON, BACK_BLUE_BEACON, RIGHT_BLUE_BEACON, FRONT_BLUE_BEACON);
	this->_leftHeadLightAssy->turnOff(HIGHBEAM_HEADLIGHT, SIGNAL_HEADLIGHT, FOG_HEADLIGHT);
	this->_rightHeadLightAssy->turnOff(HIGHBEAM_HEADLIGHT, SIGNAL_HEADLIGHT, FOG_HEADLIGHT);
	this->_leftTailLightAssy->turnOff(RED1_TAILLIGHT, RED2_TAILLIGHT, RED3_TAILLIGHT, RED4_TAILLIGHT, RED5_TAILLIGHT, WHITE_TAILLIGHT);	
	this->_rightTailLightAssy->turnOff(RED1_TAILLIGHT, RED2_TAILLIGHT, RED3_TAILLIGHT, RED4_TAILLIGHT, RED5_TAILLIGHT, WHITE_TAILLIGHT);	
	
}

void LedController_NAVI::setUniversalLEDMode(byte desiredMode)
{

	//initialize the current pattern index
	this->_currentPatternIndex = 0;
	//set the desired mode as the current mode
	this->_currentUniversalLEDMode = desiredMode;
	//turn off all LEDs for the initial state
	this->allOff();
	
	//assign the _arrayOfInterestSize
	switch(desiredMode)
	{
		case LED_ALL_OFF_MODE:
			this->_arrayOfInterestSize = sizeof(this->_ALL_LED_NAMES) / sizeof(this->_ALL_LED_NAMES[0]);
			break;
		case LED_ALL_ON_MODE:
			this->_arrayOfInterestSize = sizeof(this->_ALL_LED_NAMES) / sizeof(this->_ALL_LED_NAMES[0]);
			break;
		case LED_STANDARD_DAY_TIME_MODE:
			//Do nothing else that is recurring. All LEDs are already turned off for the initial state.
			break;
		case LED_NIGHT_TIME_MODE:
//WRITE ME LATER		
			break;
		case LED_HAZARD_MODE:
			this->_arrayOfInterestSize = sizeof(this->_LED_NAMES_For_HazardMode) / sizeof(this->_LED_NAMES_For_HazardMode[0]);
			break;
		case LED_DEMO_MODE:
//WRITE ME LATER		
			break;
		case LED_ERROR_MODE:
//WRITE ME LATER		
			break;		
		case LED_STEALTH_MODE:
//WRITE ME LATER		
			break;
		case LED_DEBUG_MODE:
//WRITE ME LATER		
			break;			
		default:
//WRITE ME LATER
			break;
	}//end switch
	
}
void LedController_NAVI::setFogLightControl(byte fogLightsState)
{
//WRITE ME LATER
}
void LedController_NAVI::setUnderglowLightControl(byte underglowLightState)
{
//WRITE ME LATER
}
void LedController_NAVI::setIRBeaconLightControl(byte irBeaconLightState)
{
//WRITE ME LATER
}
void LedController_NAVI::setBlueBeaconLightControl(byte blueBeaconLightState)
{
//WRITE ME LATER
}
void LedController_NAVI::setBeaconDirection(byte beaconLedDirection)
{
//WRITE ME LATER
}
void LedController_NAVI::setRoverMotion(byte roverMotion)
{
//WRITE ME LATER
}
void LedController_NAVI::setErrorType(byte errorType)
{
//WRITE ME LATER
}
void LedController_NAVI::setDebugType(byte debugType)
{
//WRITE ME LATER
}
void LedController_NAVI::discreteLEDControl(byte ledName, byte desiredLedState)
{
//WRITE ME LATER
}

void LedController_NAVI::reset()
{
	//Turn off All LEDs
	this->_underglowLight->reset();
	this->_leftSideSignal->reset();
	this->_rightSideSignal->reset();
	this->_beaconLightAssy->reset();
	this->_leftHeadLightAssy->reset();
	this->_rightHeadLightAssy->reset();
	this->_leftTailLightAssy->reset();
	this->_rightTailLightAssy->reset();
}
