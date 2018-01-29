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

//WRITE ME LATER-SEE LEFT OFF HERE
	
	switch(this->_currentUniversalLEDMode)
	{
		case LED_ALL_OFF_MODE:
			//Do nothing that is recurring.
			break;
		case LED_ALL_ON_MODE:
			//Do nothing that is recurring.	
			break;
		case LED_STANDARD_DAY_TIME_MODE:
			//Do nothing that is recurring.			
			break;
		case LED_NIGHT_TIME_MODE:
			//Do nothing that is recurring.			
			break;
		case LED_HAZARD_MODE:
			//Note: This mode uses the delay counter.
			if (this->_counterPtr->countReached())
			{
				
				this->_counterPtr->counterReset();//reset the counter
					
				if( this->_patternIndexCounter == 0)
				{
					for(byte i = 0; i < this->_arrayOfInterestSize; i++)
					{
						this->discreteLEDControl( this->_LED_NAMES_For_HazardMode[ i ], LED_OFF );//turn off all the elements in the array
					}//end for
				}//end if
				else
				{
					for(byte i = 0; i < this->_arrayOfInterestSize; i++)
					{
						this->discreteLEDControl( this->_LED_NAMES_For_HazardMode[ i ], LED_ON );//turn off all the elements in the array
					}//end for
				}//end else
				//increment pattern index counter
				this->incrementPatternIndexCounter(BLINK_PATTERN_SIZE);
				
			}//end if
			//else do nothing, keep waiting until the count is reached. The counter is external and is incremented externally by its associated GlobalDelayTimer.
		
			break;
		case LED_DEMO_MODE:
			//Note: This mode uses the delay counter.
			if (this->_counterPtr->countReached())
			{
				
				this->_counterPtr->counterReset();//reset the counter
					
				if( this->_patternIndexCounter == 0)//for the first element in the array
				{
					this->discreteLEDControl( this->_LED_NAMES_For_DemoMode[ this->_arrayOfInterestSize - this->_patternIndexCounter ], LED_OFF );//the last element in the array (the last element = arraySize - currentIndex)
					
					this->discreteLEDControl( this->_LED_NAMES_For_DemoMode[ this->_patternIndexCounter ], LED_ON );//the current element in the array
				}//end if
				else//for all other elements
				{
					this->discreteLEDControl( this->_LED_NAMES_For_DemoMode[ this->_patternIndexCounter - 1 ], LED_OFF );//the previous element in the array
					this->discreteLEDControl( this->_LED_NAMES_For_DemoMode[ this->_patternIndexCounter ], LED_ON );//the current element in the array
				}//end else	
					
				//increment pattern index counter
				this->incrementPatternIndexCounter(this->_arrayOfInterestSize);
					
			}//end if
			//else do nothing, keep waiting until the count is reached. The counter is external and is incremented externally by its associated GlobalDelayTimer.
				
			break;
		case LED_ERROR_MODE:
			//Note: This mode uses the delay counter.
			if (this->_counterPtr->countReached())
			{
				
				this->_counterPtr->counterReset();//reset the counter
				
					
				if( this->_patternIndexCounter == 0)
				{
					for(byte i = 0; i < this->_arrayOfInterestSize; i++)
					{
						this->discreteLEDControl( this->_LED_NAMES_For_ErrorMode[ i ], LED_OFF );//turn off all the elements in the array
					}//end for
				}//end if
				else
				{
					for(byte i = 0; i < this->_arrayOfInterestSize; i++)
					{
						this->discreteLEDControl( this->_LED_NAMES_For_ErrorMode[ i ], LED_ON );//turn off all the elements in the array
					}//end for
				}//end else
				//increment pattern index counter
				this->incrementPatternIndexCounter(BLINK_PATTERN_SIZE);
				
			}//end if
			//else do nothing, keep waiting until the count is reached. The counter is external and is incremented externally by its associated GlobalDelayTimer.
			
			break;		
		case LED_STEALTH_MODE:
			//Make sure all LEDs turn off and continue to stay off as long as it's in stealth mode
			this->allOff();
			break;
		case LED_DEBUG_MODE:
			//Do nothing that is recurring.
			break;			
		default:
			//Do nothing that is recurring.
			break;
	}//end switch
	
	
//LEFT OFF HERE	
//WRITE ME LATER	
	if()//For these modes, allow Rover Motion to override the LED controls
	{
		switch(this->_currentRoverMotion)
		{
		}//end switch
	}//end if
	if()//For these modes, allow current Fog Light State to override the LED controls
	{
		switch(this->)
		{
		}//end switch
	}//end if
	if()//For these modes, allow current Underglow Light State to override the LED controls
	{
		switch(this->)
		{
		}//end switch
	}//end if	
	if()//For these modes, allow current IR Beacon State to override the LED controls
	{
		switch(this->)
		{
			case:
				break;
				
			case LED_IR_BEACON_DIRECTIONAL_MODE:
				this->runIRBeaconDirectionalControl(this->_currentBeaconLEDDirection);
				break;
			default:
				break;							
		}//end switch
	}//end if	
	if()//For these modes, allow current Blue Beacon State to override the LED controls
	{
		switch(this->_currentBlueBeaconState)
		{
			case:
				break;
				
			case LED_BLUE_BEACON_DIRECTIONAL_MODE:
				this->runBlueBeaconDirectionalControl(this->_currentBeaconLEDDirection);
				break;
			default:
				break;				
		}//end switch
	}//end if
	
	
	
//WRITE A FUNCTION TO EXECUTE THE STATE OF ALL THE LEDS ONCE THEIR STATES HAVE BEEN DETERMINED (based on priority and overriding)
//TEMPLATE//executeFinalLEDStates();//controls the LEDs based on the finalized settings (after overriding priorities)

}//end runLedController()



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
	this->resetPatternIndexCounter();
	//set the desired mode as the current mode
	this->_currentUniversalLEDMode = desiredMode;
	//turn off all LEDs for the initial state
	this->allOff();
	
	//assign the _arrayOfInterestSize
	switch(desiredMode)
	{
		case LED_ALL_OFF_MODE:
			//Nothing else needs to be done. By default all LEDs are initially turned off when this function is called.
			break;
		case LED_ALL_ON_MODE:
			//Turn on all LEDs
			this->allOn();
			break;
		case LED_STANDARD_DAY_TIME_MODE:
			//Do nothing else that is recurring. All LEDs are already turned off for the initial state.
			break;
		case LED_NIGHT_TIME_MODE:
			//Turn on the High Beams of the Headlights
			this->_leftHeadLightAssy->turnOn(HIGHBEAM_HEADLIGHT);
			this->_rightHeadLightAssy->turnOn(HIGHBEAM_HEADLIGHT);			
			//Turn on LEDs 2, 4, 5 on the left tail lights
			this->_leftTailLightAssy = new TailLightAssembly( LEFT_RED_TAILLIGHT_2_PIN,  LEFT_RED_TAILLIGHT_4_PIN, LEFT_RED_TAILLIGHT_5_PIN);
			//Turn on LEDs 2, 4, 5 on the right tail lights
			this->_rightTailLightAssy = new TailLightAssembly( RIGHT_RED_TAILLIGHT_2_PIN,  RIGHT_RED_TAILLIGHT_4_PIN, RIGHT_RED_TAILLIGHT_5_PIN );			
			break;
		case LED_HAZARD_MODE:
			this->_arrayOfInterestSize = sizeof(this->_LED_NAMES_For_HazardMode) / sizeof(this->_LED_NAMES_For_HazardMode[0]);
			
			this->_counterPtr->setStopValue(DELAY_100_PERIODS);//set the counter stop value for this mode since it uses a specific delay.
			//This mode uses a 500ms delay. And since the delay timer resolution is 5ms, then use 100 periods to get to 500ms.
			
			break;
		case LED_DEMO_MODE:
			this->_arrayOfInterestSize = sizeof(this->_LED_NAMES_For_DemoMode) / sizeof(this->_LED_NAMES_For_DemoMode[0]);
			
			this->_counterPtr->setStopValue(DELAY_100_PERIODS);//set the counter stop value for this mode since it uses a specific delay.
			//This mode uses a 500ms delay. And since the delay timer resolution is 5ms, then use 100 periods to get to 500ms.	

			break;
		case LED_ERROR_MODE:
			this->_arrayOfInterestSize = sizeof(this->_LED_NAMES_For_ErrorMode) / sizeof(this->_LED_NAMES_For_ErrorMode[0]);
			
			this->_counterPtr->setStopValue(DELAY_100_PERIODS);//set the counter stop value for this mode since it uses a specific delay.
			//This mode uses a 500ms delay. And since the delay timer resolution is 5ms, then use 100 periods to get to 500ms.
			
			break;		
		case LED_STEALTH_MODE:
			//Nothing else needs to be done. By default all LEDs are initially turned off when this function is called.
			break;
		case LED_DEBUG_MODE:
			//Nothing else needs to be done. By default all LEDs are initially turned off when this function is called.
			break;			
		default:
			//Nothing else needs to be done. By default all LEDs are initially turned off when this function is called.
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




//NEED TO THINK ABOUT LOGIC FOR:
//LEFT TURN (which has a pattern across multiple arrays),
//RIGHT TURN(which has a pattern across multiple arrays),
//AND BRAKING (which has different delay values)








}
void LedController_NAVI::setErrorType(byte errorType)
{
//WRITE ME LATER
}
void LedController_NAVI::setDebugType(byte debugType)
{
//WRITE ME LATER
}
void LedController_NAVI::roverDiscreteLEDControl(byte ledName, byte desiredLedState)
{

	//Check to see if the mode is in LED_ERROR_MODE, else don't do anything.
	if(this->_currentUniversalLEDMode ==LED_ERROR_MODE)
	{
			this->discreteLEDControl(ledName, desiredLedState);
	}//end if
	//else don't do anything
}

void LedController_NAVI::userDiscreteLEDControl(byte ledName, byte desiredLedState)
{

	//Check to see if the mode is in LED_DEBUG_MODE, else don't do anything.
	if(this->_currentUniversalLEDMode ==LED_DEBUG_MODE)
	{
			this->discreteLEDControl(ledName, desiredLedState);
	}//end if
	//else don't do anything
}

void LedController_NAVI::reset()
{
	
	this->_currentUniversalLEDMode = LED_ALL_OFF_MODE;
	this->_currentRoverMotion = LED_MOTION_STANDARD;
	this->_currentIRBeaconState = LED_IR_BEACON_ALL_NEUTRAL;
	this->_currentBlueBeaconState = LED_BLUE_BEACON_ALL_NEUTRAL;
	this->_currentBeaconLEDDirection = LED_DIRECTION_NONE;
	this->_arrayOfInterestSize = 0;
	this->_patternIndexCounter = 0;	
	this->_ledStateFlagSet1 = _BTFG_LED_STATE_ALL_OFF_;
	this->_ledStateFlagSet2 = _BTFG_LED_STATE_ALL_OFF_;
	this->_ledStateFlagSet3 = _BTFG_LED_STATE_ALL_OFF_;
	this->_ledStateFlagSet4 = _BTFG_LED_STATE_ALL_OFF_;
	
	
	//resetting all objects in this class
	for (byte i = 0; i < sizeof(this->_resetArray) / sizeof(this->_resetArray[0]); i++)
	{
		if (!this->_resetArray[i] == NULL)//if the object isn't null
		{
			this->_resetArray[i]->reset();//reset the object	
		}//end if
	}//end for

}


void LedController_NAVI::incrementPatternIndexCounter(byte rollOverValue)
{
	//increment counter for the next iteration
	this->_patternIndexCounter++;

	if( _patternIndexCounter >=  rollOverValue )//Note: It resets when it's >= to this roll over value. But the index does start counting at 0.
	{
		this->resetPatternIndexCounter();//reset the counter once it has reached (or surpassed) the roll over value
	}//end if	
}

void LedController_NAVI::resetPatternIndexCounter()
{
	this->_patternIndexCounter = 0;
}
void LedController_NAVI::discreteLEDControl(byte ledName, byte desiredLedState)
{
	
	//Note: Boolean Bit Flags are used to hold the state of each of the LEDs. This is so that the states can be set and overridden with a high priority setting. And then once everything has been determined, the LED Controller will execute the changes all at once. (else if bit flags weren't used, the LEDs may flash as they are changing states from being overridden from something of a higher priority.
	

	byte correspondingLEDFlagSet;//holds the corresponding LED Flag Set
	byte correspondingLEDFlagOfInterest;//holds the corresponding LED Flag of Interest
	
//WRITE ME LATER	


	switch(ledName)
	{
		case LED_NAME_FRONT_LEFT_IR_BEACON:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_FRONT_LEFT_IR_BEACON;
			correspondingLEDFlagSet= this->_ledStateFlagSet1;
			break;
		case LED_NAME_BACK_LEFT_IR_BEACON:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_BACK_RIGHT_IR_BEACON:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_FRONT_RIGHT_IR_BEACON:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_LEFT_BLUE_BEACON:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_BACK_BLUE_BEACON:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_RIGHT_BLUE_BEACON:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_FRONT_BLUE_BEACON:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_RIGHT_HIGHBEAM_HEADLIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_RIGHT_SIGNAL_HEADLIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_RIGHT_FOG_HEADLIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_LEFT_HIGHBEAM_HEADLIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_LEFT_SIGNAL_HEADLIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_LEFT_FOG_HEADLIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_RIGHT_RED1_TAILLIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_RIGHT_RED2_TAILLIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_RIGHT_RED3_TAILLIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER	
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_RIGHT_RED4_TAILLIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_RIGHT_RED5_TAILLIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_RIGHT_WHITE_TAILLIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_LEFT_RED1_TAILLIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_LEFT_RED2_TAILLIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_LEFT_RED3_TAILLIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_LEFT_RED4_TAILLIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_LEFT_RED5_TAILLIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_LEFT_WHITE_TAILLIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_UNDERGLOW_LIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_RIGHT_SIDE_SIGNAL_LIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		case LED_NAME_LEFT_SIDE_SIGNAL_LIGHT:
			//correspondingLEDFlagOfInterest= ???;//WRITE ME LATER
			//correspondingLEDFlagSet= ???;//WRITE ME LATER
			break;
		default:
			//do nothing
			break;
	}//end switch
		

	if(desiredLedState == LED_ON)
	{
		BooleanBitFlags::setFlagBit(correspondingLEDFlagSet, correspondingLEDFlagOfInterest);
	}//end if
	else if (desiredLedState == LED_OFF)
	{
		BooleanBitFlags::clearFlagBit(correspondingLEDFlagSet, correspondingLEDFlagOfInterest);
	}//end else
	//else do nothing, as it's an invalid input

		
		
}//end of discreteLEDControl()
void LedController_NAVI::runIRBeaconDirectionalControl(byte ledDirection)
{

//For IR Beacon LEDs:
//For Front, Right, Back, Left, just light up the two LEDs associated with that direction
//For Front Right, Back Right, Back Left, Front Left, light up the one LED associated with that direction


//WRITE ME LATER
	switch(this->_currentBeaconLEDDirection)
	{
		case LED_DIRECTION_NONE:
			break;
		case LED_DIRECTION_FRONT:
			break;
		case LED_DIRECTION_FRONT_RIGHT:
			break;
		case LED_DIRECTION_RIGHT:
			break;
		case LED_DIRECTION_REAR_RIGHT:
			break;
		case LED_DIRECTION_REAR:
			break;
		case LED_DIRECTION_REAR_LEFT:
			break;
		case LED_DIRECTION_LEFT:
			break;
		case LED_DIRECTION_FRONT_LEFT:
			break;		
		default:
			break;
	}//end switch

}//end of runIRBeaconDirectionalControl()
void LedController_NAVI::runBlueBeaconDirectionalControl(byte ledDirection)
{

//For Blue Beacon LEDs:
//For Front, Right, Back, Left, just light up the one LED associated with that direction
//For Front Right, Back Right, Back Left, Front Left, light up the two LEDs associated with that direction


	switch(this->_currentBeaconLEDDirection)
	{
		case LED_DIRECTION_NONE:
			//Turn Off All Blue Beacon LEDS
			this->discreteLEDControl(LED_NAME_LEFT_BLUE_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_BACK_BLUE_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_RIGHT_BLUE_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_FRONT_BLUE_BEACON, LED_OFF);
			break;
		case LED_DIRECTION_FRONT:
			//Turn On the LED(s) for this Corresponding Direction
			this->discreteLEDControl(LED_NAME_FRONT_BLUE_BEACON, LED_ON);
			//Turn Off All Other Blue Beacon LEDS
			this->discreteLEDControl(LED_NAME_LEFT_BLUE_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_BACK_BLUE_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_RIGHT_BLUE_BEACON, LED_OFF);			
			break;
		case LED_DIRECTION_FRONT_RIGHT:
			//Turn On the LED(s) for this Corresponding Direction
			this->discreteLEDControl(LED_NAME_FRONT_BLUE_BEACON, LED_ON);
			this->discreteLEDControl(LED_NAME_RIGHT_BLUE_BEACON, LED_ON);
			//Turn Off All Other Blue Beacon LEDS
			this->discreteLEDControl(LED_NAME_LEFT_BLUE_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_BACK_BLUE_BEACON, LED_OFF);
			break;
		case LED_DIRECTION_RIGHT:
			//Turn On the LED(s) for this Corresponding Direction
			this->discreteLEDControl(LED_NAME_RIGHT_BLUE_BEACON, LED_ON);
			//Turn Off All Other Blue Beacon LEDS
			this->discreteLEDControl(LED_NAME_LEFT_BLUE_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_BACK_BLUE_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_FRONT_BLUE_BEACON, LED_OFF);
			break;
		case LED_DIRECTION_REAR_RIGHT:
			//Turn On the LED(s) for this Corresponding Direction
			this->discreteLEDControl(LED_NAME_BACK_BLUE_BEACON, LED_ON);
			this->discreteLEDControl(LED_NAME_RIGHT_BLUE_BEACON, LED_ON);
			//Turn Off All Other Blue Beacon LEDS
			this->discreteLEDControl(LED_NAME_LEFT_BLUE_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_FRONT_BLUE_BEACON, LED_OFF);
			break;
		case LED_DIRECTION_REAR:
			//Turn On the LED(s) for this Corresponding Direction
			this->discreteLEDControl(LED_NAME_BACK_BLUE_BEACON, LED_ON);
			//Turn Off All Other Blue Beacon LEDS
			this->discreteLEDControl(LED_NAME_LEFT_BLUE_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_RIGHT_BLUE_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_FRONT_BLUE_BEACON, LED_OFF);
			break;
		case LED_DIRECTION_REAR_LEFT:
			//Turn On the LED(s) for this Corresponding Direction
			this->discreteLEDControl(LED_NAME_BACK_BLUE_BEACON, LED_ON);		
			this->discreteLEDControl(LED_NAME_LEFT_BLUE_BEACON, LED_ON);		
			//Turn Off All Other Blue Beacon LEDS
			this->discreteLEDControl(LED_NAME_RIGHT_BLUE_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_FRONT_BLUE_BEACON, LED_OFF);		
			break;
		case LED_DIRECTION_LEFT:
			//Turn On the LED(s) for this Corresponding Direction
			this->discreteLEDControl(LED_NAME_LEFT_BLUE_BEACON, LED_ON);	
			//Turn Off All Other Blue Beacon LEDS
			this->discreteLEDControl(LED_NAME_BACK_BLUE_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_RIGHT_BLUE_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_FRONT_BLUE_BEACON, LED_OFF);		
			break;
		case LED_DIRECTION_FRONT_LEFT:
			//Turn On the LED(s) for this Corresponding Direction
			this->discreteLEDControl(LED_NAME_LEFT_BLUE_BEACON, LED_ON);	
			this->discreteLEDControl(LED_NAME_FRONT_BLUE_BEACON, LED_ON);				
			//Turn Off All Other Blue Beacon LEDS
			this->discreteLEDControl(LED_NAME_BACK_BLUE_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_RIGHT_BLUE_BEACON, LED_OFF);
			break;		
		default:
			break;
	}//end switch


}//end of runBlueBeaconDirectionalControl()
void LedController_NAVI::executeFinalLEDStates()
{
		
	//Front Right IR Beacon
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet1, _BTFG_LED_STATE_FRONT_RIGHT_IR_BEACON) )
	{
		this->_beaconLightAssy->turnOn(FRONT_RIGHT_IR_BEACON);
	}//end if
	else
	{
		this->_beaconLightAssy->turnOff(FRONT_RIGHT_IR_BEACON);
	}//end else
	
	//Right Blue Beacon
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet1, _BTFG_LED_STATE_RIGHT_BLUE_BEACON) )
	{
		this->_beaconLightAssy->turnOn(RIGHT_BLUE_BEACON);
	}//end if
	else
	{
		this->_beaconLightAssy->turnOff(RIGHT_BLUE_BEACON);
	}//end else
	
	//Back Right IR Beacon
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet1, _BTFG_LED_STATE_BACK_RIGHT_IR_BEACON) )
	{
		this->_beaconLightAssy->turnOn(BACK_RIGHT_IR_BEACON);
	}//end if
	else
	{
		this->_beaconLightAssy->turnOff(BACK_RIGHT_IR_BEACON);
	}//end else

	//Back Blue Beacon
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet1, _BTFG_LED_STATE_BACK_BLUE_BEACON) )
	{
		this->_beaconLightAssy->turnOn(BACK_BLUE_BEACON);
	}//end if
	else
	{
		this->_beaconLightAssy->turnOff(BACK_BLUE_BEACON);
	}//end else

	//Back Blue Beacon
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet1, _BTFG_LED_STATE_BACK_LEFT_IR_BEACON) )
	{
		this->_beaconLightAssy->turnOn(BACK_LEFT_IR_BEACON);
	}//end if
	else
	{
		this->_beaconLightAssy->turnOff(BACK_LEFT_IR_BEACON);
	}//end else		
	
	//Left Blue Beacon
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet1, _BTFG_LED_STATE_LEFT_BLUE_BEACON) )
	{
		this->_beaconLightAssy->turnOn(LEFT_BLUE_BEACON);
	}//end if
	else
	{
		this->_beaconLightAssy->turnOff(LEFT_BLUE_BEACON);
	}//end else		

	//Front Left IR Beacon
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet1, _BTFG_LED_STATE_FRONT_LEFT_IR_BEACON) )
	{
		this->_beaconLightAssy->turnOn(FRONT_LEFT_IR_BEACON);
	}//end if
	else
	{
		this->_beaconLightAssy->turnOff(FRONT_LEFT_IR_BEACON);
	}//end else			
		
		
	//Left Side Signal Light
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet1, _BTFG_LED_STATE_LEFT_SIDE_SIGNAL_LIGHT) )
	{
		this->_leftSideSignal->turnOn();
	}//end if
	else
	{
		this->_leftSideSignal->turnOff();
	}//end else			
				
		
	//Left High Beam Headlight
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet2, _BTFG_LED_STATE_LEFT_HIGHBEAM_HEADLIGHT) )
	{
		this->_leftHeadLightAssy->turnOn(HIGHBEAM_HEADLIGHT);
	}//end if
	else
	{
		this->_leftHeadLightAssy->turnOff(HIGHBEAM_HEADLIGHT);
	}//end else				
		
		
	//Left Signal Headlight
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet2, _BTFG_LED_STATE_LEFT_SIGNAL_HEADLIGHT) )
	{
		this->_leftHeadLightAssy->turnOn(SIGNAL_HEADLIGHT);
	}//end if
	else
	{
		this->_leftHeadLightAssy->turnOff(SIGNAL_HEADLIGHT);
	}//end else				
		
	//Left Fog Headlight
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet2, _BTFG_LED_STATE_LEFT_FOG_HEADLIGHT) )
	{
		this->_leftHeadLightAssy->turnOn(FOG_HEADLIGHT);
	}//end if
	else
	{
		this->_leftHeadLightAssy->turnOff(FOG_HEADLIGHT);
	}//end else		
		
	//Right Fog Headlight
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet2, _BTFG_LED_STATE_RIGHT_FOG_HEADLIGHT) )
	{
		this->_rightHeadLightAssy->turnOn(FOG_HEADLIGHT);
	}//end if
	else
	{
		this->_rightHeadLightAssy->turnOff(FOG_HEADLIGHT);
	}//end else			
		
	//Right Signal Headlight
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet2, _BTFG_LED_STATE_RIGHT_SIGNAL_HEADLIGHT) )
	{
		this->_rightHeadLightAssy->turnOn(SIGNAL_HEADLIGHT);
	}//end if
	else
	{
		this->_rightHeadLightAssy->turnOff(SIGNAL_HEADLIGHT);
	}//end else			
		
	//Right High Beam Headlight
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet2, _BTFG_LED_STATE_RIGHT_HIGHBEAM_HEADLIGHT) )
	{
		this->_rightHeadLightAssy->turnOn(HIGHBEAM_HEADLIGHT);
	}//end if
	else
	{
		this->_rightHeadLightAssy->turnOff(HIGHBEAM_HEADLIGHT);
	}//end else				
				
	//Right Side Signal Light
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet2, _BTFG_LED_STATE_RIGHT_SIDE_SIGNAL_LIGHT) )
	{
		this->_rightSideSignal->turnOn();
	}//end if
	else
	{
		this->_rightSideSignal->turnOff();
	}//end else			
						
	//Right White Tail Light
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet2, _BTFG_LED_STATE_RIGHT_WHITE_TAILLIGHT) )
	{
		this->_rightTailLightAssy->turnOn(WHITE_TAILLIGHT);	
	
	}//end if
	else
	{
		this->_rightTailLightAssy->turnOff(WHITE_TAILLIGHT);	
	}//end else			
								
	//Right Red 1 Tail Light
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet3, _BTFG_LED_STATE_RIGHT_RED1_TAILLIGHT) )
	{
		this->_rightTailLightAssy->turnOn(RED1_TAILLIGHT);	
	
	}//end if
	else
	{
		this->_rightTailLightAssy->turnOff(RED1_TAILLIGHT);	
	}//end else			
									
	//Right Red 5 Tail Light
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet3, _BTFG_LED_STATE_RIGHT_RED5_TAILLIGHT) )
	{
		this->_rightTailLightAssy->turnOn(RED5_TAILLIGHT);	
	
	}//end if
	else
	{
		this->_rightTailLightAssy->turnOff(RED5_TAILLIGHT);	
	}//end else					
		
	//Right Red 2 Tail Light
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet3, _BTFG_LED_STATE_RIGHT_RED2_TAILLIGHT) )
	{
		this->_rightTailLightAssy->turnOn(RED2_TAILLIGHT);	
	
	}//end if
	else
	{
		this->_rightTailLightAssy->turnOff(RED2_TAILLIGHT);	
	}//end else				
		
	//Right Red 4 Tail Light
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet3, _BTFG_LED_STATE_RIGHT_RED4_TAILLIGHT) )
	{
		this->_rightTailLightAssy->turnOn(RED4_TAILLIGHT);	
	
	}//end if
	else
	{
		this->_rightTailLightAssy->turnOff(RED4_TAILLIGHT);	
	}//end else			

	//Right Red 3 Tail Light
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet3, _BTFG_LED_STATE_RIGHT_RED3_TAILLIGHT) )
	{
		this->_rightTailLightAssy->turnOn(RED3_TAILLIGHT);	
	
	}//end if
	else
	{
		this->_rightTailLightAssy->turnOff(RED3_TAILLIGHT);	
	}//end else		
		
	//Left Red 3 Tail Light
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet3, _BTFG_LED_STATE_LEFT_RED3_TAILLIGHT) )
	{
		this->_leftTailLightAssy->turnOn(RED3_TAILLIGHT);	
	
	}//end if
	else
	{
		this->_leftTailLightAssy->turnOff(RED3_TAILLIGHT);	
	}//end else	
		
	//Left Red 4 Tail Light
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet3, _BTFG_LED_STATE_LEFT_RED4_TAILLIGHT) )
	{
		this->_leftTailLightAssy->turnOn(RED4_TAILLIGHT);	
	
	}//end if
	else
	{
		this->_leftTailLightAssy->turnOff(RED4_TAILLIGHT);	
	}//end else	
		
	//Left Red 2 Tail Light
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet3, _BTFG_LED_STATE_LEFT_RED2_TAILLIGHT) )
	{
		this->_leftTailLightAssy->turnOn(RED2_TAILLIGHT);	
	
	}//end if
	else
	{
		this->_leftTailLightAssy->turnOff(RED2_TAILLIGHT);	
	}//end else		
	
	//Left Red 5 Tail Light
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet4, _BTFG_LED_STATE_LEFT_RED5_TAILLIGHT) )
	{
		this->_leftTailLightAssy->turnOn(RED5_TAILLIGHT);	
	}//end if
	else
	{
		this->_leftTailLightAssy->turnOff(RED5_TAILLIGHT);	
	}//end else
		
	//Left Red 1 Tail Light
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet4, _BTFG_LED_STATE_LEFT_RED1_TAILLIGHT) )
	{
		this->_leftTailLightAssy->turnOn(RED1_TAILLIGHT);	
	}//end if
	else
	{
		this->_leftTailLightAssy->turnOff(RED1_TAILLIGHT);	
	}//end else
		
	//Left White Tail Light
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet4, _BTFG_LED_STATE_LEFT_WHITE_TAILLIGHT) )
	{
		this->_leftTailLightAssy->turnOn(WHITE_TAILLIGHT);	
	}//end if
	else
	{
		this->_leftTailLightAssy->turnOff(WHITE_TAILLIGHT);	
	}//end else		

	//Underglow Light
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet4, _BTFG_LED_STATE_UNDERGLOW_LIGHT) )
	{
		this->_underglowLight->turnOn();	
	}//end if
	else
	{
		this->_underglowLight->turnOff();
	}//end else
	
}