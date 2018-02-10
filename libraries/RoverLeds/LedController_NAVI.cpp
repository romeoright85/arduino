#include <LedController_NAVI.h>


LedController_NAVI::LedController_NAVI(DelayCounter * counterPtr, unsigned int periodsForShortDelay, unsigned int periodsForLongDelay)
{
	this->_counterPtr = counterPtr;//take the passed counter pointer in the constructor argument and save it to the object member counter pointer
	
	this->_periodsForShortDelay = periodsForShortDelay;
	this->_periodsForLongDelay = periodsForLongDelay;
	
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

	//Note: Also see setUniversalLEDMode() and setRoverMotion(), where the LED states are initialized.





		
	switch(this->_currentUniversalLEDMode)
	{
		case LED_ALL_OFF_MODE:
			//Turn Off all LEDs			
			for(byte i = 0; i < sizeof(this->_ALL_LED_NAMES) / sizeof(this->_ALL_LED_NAMES[0]) ; i++)
			{
				this->discreteLEDControl( this->_ALL_LED_NAMES[ i ], LED_OFF );//turn off all the elements in the array
			}//end for

			break;
		case LED_ALL_ON_MODE:
			//Turn On all LEDs
			for(byte i = 0; i < sizeof(this->_ALL_LED_NAMES) / sizeof(this->_ALL_LED_NAMES[0]) ; i++)
			{
				this->discreteLEDControl( this->_ALL_LED_NAMES[ i ], LED_ON );//turn on all the elements in the array
			}//end for
			break;
		case LED_STANDARD_DAY_TIME_MODE:
			//Do nothing that is recurring.			
			break;
		case LED_NIGHT_TIME_MODE:
			//Do nothing that is recurring.			
			break;
/*OLD CODE
		case LED_HAZARD_MODE:
			//Note: This mode uses the delay counter.
			if (this->_counterPtr->countReached())
			{
				
				this->_counterPtr->counterReset();//reset the counter
					
				if( this->_roverMotionPatternIndexCounter == 0)
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
				//auto-increment pattern index counter. (it will reset the counter automatically once it rolls over)
				this->autoIncrementIndexCounter(this->_roverMotionPatternIndexCounter, BLINK_PATTERN_SIZE);
			}//end if
			//else do nothing, keep waiting until the count is reached. The counter is external and is incremented externally by its associated GlobalDelayTimer.
		
			break;
*/			
		case LED_DEMO_MODE:
			//Note: This mode uses the delay counter.
			if (this->_counterPtr->countReached())
			{
				
				this->_counterPtr->counterReset();//reset the counter
					
				if( this->_universalLEDModePatternIndexCounter == 0)//for the first element in the array
				{
					this->discreteLEDControl( this->_LED_NAMES_For_DemoMode[ this->_arrayOfInterestSize - this->_universalLEDModePatternIndexCounter ], LED_OFF );//the last element in the array (the last element = arraySize - currentIndex)
					
					this->discreteLEDControl( this->_LED_NAMES_For_DemoMode[ this->_universalLEDModePatternIndexCounter ], LED_ON );//the current element in the array
				}//end if
				else//for all other elements
				{
					this->discreteLEDControl( this->_LED_NAMES_For_DemoMode[ this->_universalLEDModePatternIndexCounter - 1 ], LED_OFF );//the previous element in the array
					this->discreteLEDControl( this->_LED_NAMES_For_DemoMode[ this->_universalLEDModePatternIndexCounter ], LED_ON );//the current element in the array
				}//end else	
					
				//auto-increment pattern index counter. (it will reset the counter automatically once it rolls over)
				this->autoIncrementIndexCounter(this->_universalLEDModePatternIndexCounter, this->_arrayOfInterestSize);//the rollover value/size of the pattern is the number of LEDs in the array (as it turns on one at a time)
					
			}//end if
			//else do nothing, keep waiting until the count is reached. The counter is external and is incremented externally by its associated GlobalDelayTimer.
				
			break;
		case LED_ERROR_MODE:
			//Note: This mode uses the delay counter.
			if (this->_counterPtr->countReached())
			{
				
				this->_counterPtr->counterReset();//reset the counter

				//Depending on which error type, blink certain LEDs and light on (solid) other LEDs
				
				//Blink Code
				if( this->_universalLEDModePatternIndexCounter == 0)
				{
					for(byte i = 0; i < this->_arrayOfInterestSize; i++)
					{
						this->discreteLEDControl( this->_arrayOfInterest[ i ], LED_OFF );//turn off all the elements in the array
					}//end for
				}//end if
				else
				{
					for(byte i = 0; i < this->_arrayOfInterestSize; i++)
					{
						this->discreteLEDControl( this->_arrayOfInterest[ i ], LED_ON );//turn off all the elements in the array
					}//end for
				}//end else
				//auto-increment pattern index counter. (it will reset the counter automatically once it rolls over)
				this->autoIncrementIndexCounter(this->_universalLEDModePatternIndexCounter, BLINK_PATTERN_SIZE);
					
				//On Solid Code
				switch(this->_currentErrorState)
				{
					case LED_ERROR_TYPE_NONE:
						//Do nothing that is recurring.
						break;
					case LED_ERROR_TYPE_GENERIC_HEALTH:
						this->discreteLEDControl( LED_NAME_LEFT_RED1_TAILLIGHT, LED_ON );//turn on this LED
						this->discreteLEDControl( LED_NAME_RIGHT_RED1_TAILLIGHT, LED_ON );//turn on this LED
						break;
					case LED_ERROR_TYPE_GENERIC_SYSTEM:
						this->discreteLEDControl( LED_NAME_LEFT_RED2_TAILLIGHT, LED_ON );//turn on this LED
						this->discreteLEDControl( LED_NAME_RIGHT_RED2_TAILLIGHT, LED_ON );//turn on this LED
						break;
					case LED_ERROR_TYPE_SW_RESET:
						this->discreteLEDControl( LED_NAME_LEFT_RED3_TAILLIGHT, LED_ON );//turn on this LED
					this->discreteLEDControl( LED_NAME_RIGHT_RED3_TAILLIGHT, LED_ON );//turn on this LED
						break;
					case LED_ERROR_TYPE_SYNC:
						this->discreteLEDControl( LED_NAME_LEFT_RED4_TAILLIGHT, LED_ON );//turn on this LED
						this->discreteLEDControl( LED_NAME_RIGHT_RED4_TAILLIGHT, LED_ON );//turn on this LED
						break;
					case LED_ERROR_TYPE_INVALID_STATE_OR_MODE:
						this->discreteLEDControl( LED_NAME_LEFT_RED5_TAILLIGHT, LED_ON );//turn on this LED
						this->discreteLEDControl( LED_NAME_RIGHT_RED5_TAILLIGHT, LED_ON );//turn on this LED
						break;
					case LED_ERROR_TYPE_UNDEFINED:
						this->discreteLEDControl( LED_NAME_LEFT_RED1_TAILLIGHT, LED_ON );//turn on this LED
						this->discreteLEDControl( LED_NAME_RIGHT_RED1_TAILLIGHT, LED_ON );//turn on this LED
						this->discreteLEDControl( LED_NAME_LEFT_RED3_TAILLIGHT, LED_ON );//turn on this LED
						this->discreteLEDControl( LED_NAME_RIGHT_RED3_TAILLIGHT, LED_ON );//turn on this LED
						break;			
					default:
						//Do nothing else since it's an invalid state.
						break;				
				}//end switch
				
			}//end if
			//else do nothing, keep waiting until the count is reached. The counter is external and is incremented externally by its associated GlobalDelayTimer.
			
			break;		
		case LED_STEALTH_MODE:
			//Make sure all LEDs turn off and continue to stay off as long as it's in stealth mode
			//Turn Off all LEDs
			for(byte i = 0; i < sizeof(this->_ALL_LED_NAMES) / sizeof(this->_ALL_LED_NAMES[0]) ; i++)
			{
				this->discreteLEDControl( this->_ALL_LED_NAMES[ i ], LED_OFF );//turn off all the elements in the array
			}//end for
			break;
		case LED_DEBUG_MODE:
			//Do nothing that is recurring.
			break;			
		default:
			//Do nothing that is recurring.
			break;
	}//end switch
	
	
	
	
	//Hazard Lights Override (if applicable)
	if( this->_currentUniversalLEDMode == LED_STANDARD_DAY_TIME_MODE || this->_currentUniversalLEDMode == LED_NIGHT_TIME_MODE )//For these modes, allow Hazard Lights to override the LED controls (i.e. blink headlight's signal lights, side signal lights, and some tail lights)
	{
		switch(this->_currentHazardLightsState)
		{
			case LED_HAZARDS_OFF:
				//Do nothing that is recurring.
				break;		
			case LED_HAZARDS_ON:
							
					//Note: This mode uses the delay counter.
					if (this->_counterPtr->countReached())
					{
						
						this->_counterPtr->counterReset();//reset the counter
						

						switch(this->_hazardLightsPatternIndexCounter)
						{
							case 0:
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_HazardMode) / sizeof(this->_LED_NAMES_For_HazardMode[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_HazardMode[ i ], LED_OFF );//turn off all the elements in the array
								}//end for
								break;
							case 1:
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_HazardMode) / sizeof(this->_LED_NAMES_For_MotionBrake[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_HazardMode[ i ], LED_ON );//turn off all the elements in the array
								}//end for								
								break;
							default:
								//do nothing
								break;								
						}//end switch

						//auto-increment pattern index counter. (it will reset the counter automatically once it rolls over)
						this->autoIncrementIndexCounter(this->_hazardLightsPatternIndexCounter, BLINK_PATTERN_SIZE);						
						
					}//end if
					//else do nothing, keep waiting until the count is reached. The counter is external and is incremented externally by its associated GlobalDelayTimer.	
				break;
			case LED_HAZARDS_NEUTRAL:
				//Do nothing that is recurring.
				break;								
			default:
				//do nothing since it's an invalid state
				break;
				
		}//end switch
		
	}//end if
	
	
	//Rover Motion Override (if applicable)
	if(
		( this->_currentUniversalLEDMode == LED_STANDARD_DAY_TIME_MODE || this->_currentUniversalLEDMode == LED_NIGHT_TIME_MODE ) &&
		this->_currentHazardLightsState != LED_HAZARDS_ON
	)//For these modes, allow Rover Motion to override the LED controls (i.e. turn signal lights, brake lights, etc. on the headlight, side signal, and tail lights)

	{

		switch(this->_currentRoverMotion)
		{
		
			case LED_MOTION_STANDARD:
				//Do nothing that is recurring.
				break;
			case LED_MOTION_TURN_LEFT:
							
					//Note: This mode uses the delay counter.
					if (this->_counterPtr->countReached())
					{
						
						this->_counterPtr->counterReset();//reset the counter
						

						switch(this->_roverMotionPatternIndexCounter)
						{
							case 0:
								//Left Turn Headlight - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnLeft_Headlight) / sizeof(this->_LED_NAMES_For_MotionTurnLeft_Headlight[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnLeft_Headlight[ i ], LED_OFF );//turn off all the elements in the array
								}//end for			
								
								//Right Turn Headlight - Turn Off
								//Do Nothing
								//Note: The right headlight's signal should already be turned off by setRoverMotion()'s initialization
								
								//Left Side Signal Light - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnLeft_SideSignalLights) / sizeof(this->_LED_NAMES_For_MotionTurnLeft_SideSignalLights[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnLeft_SideSignalLights[ i ], LED_OFF );//turn off all the elements in the array
								}//end for	
								
								//Right Side Signal Light - Turn Off
								//Do Nothing
								//Note: The right side signal light should already be turned off by setRoverMotion()'s initialization
								
								//Left Tail Light
								//Part 1 - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part1) / sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part1[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part1[ i ], LED_OFF );//turn off all the elements in the array
								}//end for
								//Part 2 - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part2) / sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part2[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part2[ i ], LED_OFF );//turn off all the elements in the array
								}//end for								
								//Part 3 - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part3) / sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part3[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part3[ i ], LED_OFF );//turn off all the elements in the array
								}//end for								
								
								//Right Tail Light - Turn Off
								//Do Nothing
								//Note: The right tail light's signal should already be turned off by setRoverMotion()'s initialization. (though it can be overriden with code from above)

								break;
							case 1:
								//Left Turn Headlight - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnLeft_Headlight) / sizeof(this->_LED_NAMES_For_MotionTurnLeft_Headlight[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnLeft_Headlight[ i ], LED_OFF );//turn off all the elements in the array
								}//end for			
								
								//Right Turn Headlight - Turn Off
								//Do Nothing
								//Note: The right headlight's signal should already be turned off by setRoverMotion()'s initialization
								
								//Left Side Signal Light - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnLeft_SideSignalLights) / sizeof(this->_LED_NAMES_For_MotionTurnLeft_SideSignalLights[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnLeft_SideSignalLights[ i ], LED_OFF );//turn off all the elements in the array
								}//end for	
								
								//Right Side Signal Light - Turn Off
								//Do Nothing
								//Note: The right side signal light should already be turned off by setRoverMotion()'s initialization
								
								//Left Tail Light
								//Part 1 - Turn On
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part1) / sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part1[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part1[ i ], LED_ON );//turn on all the elements in the array
								}//end for
								//Part 2 - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part2) / sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part2[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part2[ i ], LED_OFF );//turn off all the elements in the array
								}//end for								
								//Part 3 - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part3) / sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part3[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part3[ i ], LED_OFF );//turn off all the elements in the array
								}//end for								
								
								//Right Tail Light - Turn Off
								//Do Nothing
								//Note: The right tail light's signal should already be turned off by setRoverMotion()'s initialization. (though it can be overriden with code from above)
							
								break;
							case 2:
								//Left Turn Headlight - Turn On
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnLeft_Headlight) / sizeof(this->_LED_NAMES_For_MotionTurnLeft_Headlight[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnLeft_Headlight[ i ], LED_ON );//turn on all the elements in the array
								}//end for			
								
								//Right Turn Headlight - Turn Off
								//Do Nothing
								//Note: The right headlight's signal should already be turned off by setRoverMotion()'s initialization
								
								//Left Side Signal Light - Turn On
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnLeft_SideSignalLights) / sizeof(this->_LED_NAMES_For_MotionTurnLeft_SideSignalLights[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnLeft_SideSignalLights[ i ], LED_ON );//turn on all the elements in the array
								}//end for	
								
								//Right Side Signal Light - Turn Off
								//Do Nothing
								//Note: The right side signal light should already be turned off by setRoverMotion()'s initialization
								
								//Left Tail Light
								//Part 1 - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part1) / sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part1[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part1[ i ], LED_OFF );//turn off all the elements in the array
								}//end for
								//Part 2 - Turn On
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part2) / sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part2[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part2[ i ], LED_ON );//turn on all the elements in the array
								}//end for								
								//Part 3 - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part3) / sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part3[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part3[ i ], LED_OFF );//turn off all the elements in the array
								}//end for								
								
								//Right Tail Light - Turn Off
								//Do Nothing
								//Note: The right tail light's signal should already be turned off by setRoverMotion()'s initialization. (though it can be overriden with code from above)
								
								break;	
							case 3:
								//Left Turn Headlight - Turn On
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnLeft_Headlight) / sizeof(this->_LED_NAMES_For_MotionTurnLeft_Headlight[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnLeft_Headlight[ i ], LED_ON );//turn on all the elements in the array
								}//end for			
								
								//Right Turn Headlight - Turn Off
								//Do Nothing
								//Note: The right headlight's signal should already be turned off by setRoverMotion()'s initialization
								
								//Left Side Signal Light - Turn On
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnLeft_SideSignalLights) / sizeof(this->_LED_NAMES_For_MotionTurnLeft_SideSignalLights[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnLeft_SideSignalLights[ i ], LED_ON );//turn on all the elements in the array
								}//end for	
								
								//Right Side Signal Light - Turn Off
								//Do Nothing
								//Note: The right side signal light should already be turned off by setRoverMotion()'s initialization
								
								//Left Tail Light
								//Part 1 - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part1) / sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part1[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part1[ i ], LED_OFF );//turn off all the elements in the array
								}//end for
								//Part 2 - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part2) / sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part2[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part2[ i ], LED_OFF );//turn off all the elements in the array
								}//end for								
								//Part 3 - Turn On
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part3) / sizeof(this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part3[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnLeft_LeftTaillight_Part3[ i ], LED_ON );//turn on all the elements in the array
								}//end for								
								
								//Right Tail Light - Turn Off
								//Do Nothing
								//Note: The right tail light's signal should already be turned off by setRoverMotion()'s initialization. (though it can be overriden with code from above)
								
								break;
							default:
								//do nothing
								break;
						}//end switch
	
						//auto-increment pattern index counter. (it will reset the counter automatically once it rolls over)
						this->autoIncrementIndexCounter(this->_roverMotionPatternIndexCounter, TURN_SIGNAL_PATTERN_SIZE);

				
					}//end if
					//else do nothing, keep waiting until the count is reached. The counter is external and is incremented externally by its associated GlobalDelayTimer.					
					
					break;
			case LED_MOTION_TURN_RIGHT:

					//Note: This mode uses the delay counter.
					if (this->_counterPtr->countReached())
					{
						
						this->_counterPtr->counterReset();//reset the counter
							
	
						switch(this->_roverMotionPatternIndexCounter)
						{
							case 0:
								//Left Turn Headlight - Turn Off
								//Do Nothing
								//Note: The left headlight's signal should already be turned off by setRoverMotion()'s initialization
																
								//Right Turn Headlight - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnRight_Headlight) / sizeof(this->_LED_NAMES_For_MotionTurnRight_Headlight[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnRight_Headlight[ i ], LED_OFF );//turn off all the elements in the array
								}//end for			
								
								
								//Left Side Signal Light - Turn Off
								//Do Nothing
								//Note: The left side signal light should already be turned off by setRoverMotion()'s initialization
								
								//Right Side Signal Light - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnRight_SideSignalLights) / sizeof(this->_LED_NAMES_For_MotionTurnRight_SideSignalLights[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnRight_SideSignalLights[ i ], LED_OFF );//turn off all the elements in the array
								}//end for	
								
								
								//Left Tail Light - Turn Off
								//Do Nothing
								//Note: The left tail light's signal should already be turned off by setRoverMotion()'s initialization. (though it can be overriden with code from above)
								
								//Right Tail Light - Turn Off
								//Part 1 - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part1) / sizeof(this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part1[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part1[ i ], LED_OFF );//turn off all the elements in the array
								}//end for
								//Part 2 - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part2) / sizeof(this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part2[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part2[ i ], LED_OFF );//turn off all the elements in the array
								}//end for								
								//Part 3 - Turn Off
								for(byte i = 0; i < sizeof(_LED_NAMES_For_MotionTurnRight_RightTaillight_Part3) / sizeof(this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part3[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part3[ i ], LED_OFF );//turn off all the elements in the array
								}//end for								

								break;
							case 1:
								//Left Turn Headlight - Turn Off
								//Do Nothing
								//Note: The left headlight's signal should already be turned off by setRoverMotion()'s initialization
																
								//Right Turn Headlight - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnRight_Headlight) / sizeof(this->_LED_NAMES_For_MotionTurnRight_Headlight[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnRight_Headlight[ i ], LED_OFF );//turn off all the elements in the array
								}//end for			
								
								
								//Left Side Signal Light - Turn Off
								//Do Nothing
								//Note: The left side signal light should already be turned off by setRoverMotion()'s initialization
								
								//Right Side Signal Light - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnRight_SideSignalLights) / sizeof(this->_LED_NAMES_For_MotionTurnRight_SideSignalLights[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnRight_SideSignalLights[ i ], LED_OFF );//turn off all the elements in the array
								}//end for	
								
								
								//Left Tail Light - Turn Off
								//Do Nothing
								//Note: The left tail light's signal should already be turned off by setRoverMotion()'s initialization. (though it can be overriden with code from above)
								
								//Right Tail Light
								//Part 1 - Turn On
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part1) / sizeof(this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part1[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part1[ i ], LED_ON );//turn on all the elements in the array
								}//end for
								//Part 2 - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part2) / sizeof(this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part2[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part2[ i ], LED_OFF );//turn off all the elements in the array
								}//end for								
								//Part 3 - Turn Off
								for(byte i = 0; i < sizeof(_LED_NAMES_For_MotionTurnRight_RightTaillight_Part3) / sizeof(this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part3[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part3[ i ], LED_OFF );//turn off all the elements in the array
								}//end for							
								
								break;
							case 2:
								//Left Turn Headlight - Turn Off
								//Do Nothing
								//Note: The left headlight's signal should already be turned off by setRoverMotion()'s initialization
																
								//Right Turn Headlight - Turn On
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnRight_Headlight) / sizeof(this->_LED_NAMES_For_MotionTurnRight_Headlight[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnRight_Headlight[ i ], LED_ON );//turn on all the elements in the array
								}//end for			
								
								
								//Left Side Signal Light - Turn Off
								//Do Nothing
								//Note: The left side signal light should already be turned off by setRoverMotion()'s initialization
								
								//Right Side Signal Light - Turn On
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnRight_SideSignalLights) / sizeof(this->_LED_NAMES_For_MotionTurnRight_SideSignalLights[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnRight_SideSignalLights[ i ], LED_ON );//turn on all the elements in the array
								}//end for	
								
								
								//Left Tail Light - Turn Off
								//Do Nothing
								//Note: The left tail light's signal should already be turned off by setRoverMotion()'s initialization. (though it can be overriden with code from above)
								
								//Right Tail Light
								//Part 1 - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part1) / sizeof(this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part1[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part1[ i ], LED_OFF );//turn off all the elements in the array
								}//end for
								//Part 2 - Turn On
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part2) / sizeof(this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part2[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part2[ i ], LED_ON );//turn on all the elements in the array
								}//end for								
								//Part 3 - Turn Off
								for(byte i = 0; i < sizeof(_LED_NAMES_For_MotionTurnRight_RightTaillight_Part3) / sizeof(this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part3[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part3[ i ], LED_OFF );//turn off all the elements in the array
								}//end for							
								
								break;	
							case 3:

								//Left Turn Headlight - Turn Off
								//Do Nothing
								//Note: The left headlight's signal should already be turned off by setRoverMotion()'s initialization
																
								//Right Turn Headlight - Turn On
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnRight_Headlight) / sizeof(this->_LED_NAMES_For_MotionTurnRight_Headlight[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnRight_Headlight[ i ], LED_ON );//turn on all the elements in the array
								}//end for			
								
								
								//Left Side Signal Light - Turn Off
								//Do Nothing
								//Note: The left side signal light should already be turned off by setRoverMotion()'s initialization
								
								//Right Side Signal Light - Turn On
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnRight_SideSignalLights) / sizeof(this->_LED_NAMES_For_MotionTurnRight_SideSignalLights[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnRight_SideSignalLights[ i ], LED_ON );//turn on all the elements in the array
								}//end for	
								
								
								//Left Tail Light - Turn Off
								//Do Nothing
								//Note: The left tail light's signal should already be turned off by setRoverMotion()'s initialization. (though it can be overriden with code from above)
								
								//Right Tail Light
								//Part 1 - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part1) / sizeof(this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part1[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part1[ i ], LED_OFF );//turn off all the elements in the array
								}//end for
								//Part 2 - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part2) / sizeof(this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part2[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part2[ i ], LED_OFF );//turn off all the elements in the array
								}//end for								
								//Part 3 - Turn On
								for(byte i = 0; i < sizeof(_LED_NAMES_For_MotionTurnRight_RightTaillight_Part3) / sizeof(this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part3[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionTurnRight_RightTaillight_Part3[ i ], LED_ON );//turn on all the elements in the array
								}//end for							
								
								break;
							default:
								//do nothing
								break;
						}//end switch
	
	
						//auto-increment pattern index counter. (it will reset the counter automatically once it rolls over)
						this->autoIncrementIndexCounter(this->_roverMotionPatternIndexCounter, TURN_SIGNAL_PATTERN_SIZE);
						
					}//end if
					//else do nothing, keep waiting until the count is reached. The counter is external and is incremented externally by its associated GlobalDelayTimer.					
					
					
					break;
			case LED_MOTION_BRAKE:

					//Note: This mode uses the delay counter.
					if (this->_counterPtr->countReached())
					{
						
						this->_counterPtr->counterReset();//reset the counter
						
						switch(this->_roverMotionPatternIndexCounter)
						{
							case 0:
								//Right and Left Tail lights - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionBrake) / sizeof(this->_LED_NAMES_For_MotionBrake[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionBrake[ i ], LED_OFF );//turn off all the elements in the array
								}//end for
								break;
							case 1:
								//Right and Left Tail lights - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionBrake) / sizeof(this->_LED_NAMES_For_MotionBrake[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionBrake[ i ], LED_OFF );//turn off all the elements in the array
								}//end for								
								break;
							case 2:
								//Right and Left Tail lights - Turn On
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionBrake) / sizeof(this->_LED_NAMES_For_MotionBrake[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionBrake[ i ], LED_ON );//turn on all the elements in the array
								}//end for								
								break;	
							case 3:
								//Right and Left Tail lights - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionBrake) / sizeof(this->_LED_NAMES_For_MotionBrake[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionBrake[ i ], LED_OFF );//turn off all the elements in the array
								}//end for
								break;
							case 4:
								//Right and Left Tail lights - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionBrake) / sizeof(this->_LED_NAMES_For_MotionBrake[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionBrake[ i ], LED_OFF );//turn off all the elements in the array
								}//end for
								break;
							case 5:
								//Right and Left Tail lights - Turn On
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionBrake) / sizeof(this->_LED_NAMES_For_MotionBrake[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionBrake[ i ], LED_ON );//turn on all the elements in the array
								}//end for	
								break;
							case 6:
								//Right and Left Tail lights - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionBrake) / sizeof(this->_LED_NAMES_For_MotionBrake[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionBrake[ i ], LED_OFF );//turn off all the elements in the array
								}//end for
								break;
							case 7:
								//Right and Left Tail lights - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionBrake) / sizeof(this->_LED_NAMES_For_MotionBrake[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionBrake[ i ], LED_OFF );//turn off all the elements in the array
								}//end for
								break;
							case 8:
								//Right and Left Tail lights - Turn Off
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionBrake) / sizeof(this->_LED_NAMES_For_MotionBrake[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionBrake[ i ], LED_OFF );//turn off all the elements in the array
								}//end for
								break;
							case 9:
								//Right and Left Tail lights - Turn On
								for(byte i = 0; i < sizeof(this->_LED_NAMES_For_MotionBrake) / sizeof(this->_LED_NAMES_For_MotionBrake[0]) ; i++)
								{
									this->discreteLEDControl( this->_LED_NAMES_For_MotionBrake[ i ], LED_ON );//turn on all the elements in the array
								}//end for
								break;
							default:
								//do nothing
								break;
						}//end switch
	
						if(this->_roverMotionPatternIndexCounter < 9) //Keep incrementing the pattern counter unless it's the state where the tail light should hold it's value, then don't increment it anymore. As you don't want it to reset. 
						//Since _roverMotionPatternIndexCounter is independent of other index counters like _universalLEDModePatternIndexCounter, _blueBeaconLEDsPatternIndexCounter, _irBeaconLEDsPatternIndexCounter, etc. other LEDs can still have it's own display patterns still going even though the brake light is held on
						{
						
							//auto-increment pattern index counter. (it will reset the counter automatically once it rolls over)
							this->autoIncrementIndexCounter(this->_roverMotionPatternIndexCounter, BRAKE_PATTERN_SIZE);
							
						}//end if
						
					}//end if
					//else do nothing, keep waiting until the count is reached. The counter is external and is incremented externally by its associated GlobalDelayTimer.	
					
					break;
			case LED_MOTION_REVERSE:
					//Turn on the reverse lights when reversing
					this->discreteLEDControl(LED_NAME_RIGHT_WHITE_TAILLIGHT, LED_ON);
					this->discreteLEDControl(LED_NAME_LEFT_WHITE_TAILLIGHT, LED_ON);
					break;
			default:
				//do nothing since it's an invalid state
				break;
		}//end switch
	}//end if
	

	//Fog Light Override (if applicable)
	if( this->_currentUniversalLEDMode == LED_STANDARD_DAY_TIME_MODE || this->_currentUniversalLEDMode == LED_NIGHT_TIME_MODE )//For these modes, allow current Fog Light State to override the LED controls
	{
		switch(this->_currentFogLightState)
		{
			case LED_FOG_OFF:
					this->discreteLEDControl(LED_NAME_LEFT_FOG_HEADLIGHT, LED_OFF);
					this->discreteLEDControl(LED_NAME_RIGHT_FOG_HEADLIGHT, LED_OFF);
				break;
			case LED_FOG_ON:
					this->discreteLEDControl(LED_NAME_LEFT_FOG_HEADLIGHT, LED_ON);
					this->discreteLEDControl(LED_NAME_RIGHT_FOG_HEADLIGHT, LED_ON);
				break;
			case LED_FOG_NEUTRAL:
				//Do nothing recurring.
				break;
			default:
				break;				
		}//end switch
	}//end if
	
	//Underglow Light Override (if applicable)
	if( this->_currentUniversalLEDMode == LED_STANDARD_DAY_TIME_MODE || this->_currentUniversalLEDMode == LED_NIGHT_TIME_MODE )//For these modes, allow current Underglow Light State to override the LED controls
	{
		switch(this->_currentUnderglowState)
		{
			case LED_UNDERGLOW_OFF:
				this->discreteLEDControl(LED_NAME_UNDERGLOW_LIGHT, LED_OFF);					
				break;
			case LED_UNDERGLOW_ON:
				this->discreteLEDControl(LED_NAME_UNDERGLOW_LIGHT, LED_ON);					
				break;
			case LED_UNDERGLOW_NEUTRAL:
				//Do nothing recurring.
				break;
			default:
				//Do nothing recurring.
				break;				
		}//end switch
	}//end if	
	
	//IR Beacon Light Override (if applicable)
	if( this->_currentUniversalLEDMode == LED_STANDARD_DAY_TIME_MODE || this->_currentUniversalLEDMode == LED_NIGHT_TIME_MODE )//For these modes, allow current IR Beacon State to override the LED controls
	{
		switch(this->_currentUnderglowState)
		{
			case LED_IR_BEACON_ALL_OFF:
				for(byte i = 0; i < sizeof(this->_LED_NAMES_For_IRBeaconLEDs) / sizeof(this->_LED_NAMES_For_IRBeaconLEDs[0]) ; i++)
				{
					this->discreteLEDControl( this->_LED_NAMES_For_IRBeaconLEDs[ i ], LED_OFF );//turn off all the elements in the array
				}//end for				
				break;
			case LED_IR_BEACON_ALL_ON:
				for(byte i = 0; i < sizeof(this->_LED_NAMES_For_IRBeaconLEDs) / sizeof(this->_LED_NAMES_For_IRBeaconLEDs[0]) ; i++)
				{
					this->discreteLEDControl( this->_LED_NAMES_For_IRBeaconLEDs[ i ], LED_ON );//turn on all the elements in the array
				}//end for	
				break;	
			case LED_IR_BEACON_DIRECTIONAL_MODE:
				this->runIRBeaconDirectionalControl(this->_currentBeaconLEDDirection);
				break;
			case LED_IR_BEACON_ALL_NEUTRAL:
				//Do nothing recurring.
				break;					
			default:
				//Do nothing recurring.
				break;							
		}//end switch
	}//end if	
	
	//Blue Beacon Light Override (if applicable)
	if( this->_currentUniversalLEDMode == LED_STANDARD_DAY_TIME_MODE || this->_currentUniversalLEDMode == LED_NIGHT_TIME_MODE )//For these modes, allow current Blue Beacon State to override the LED controls
	{
		switch(this->_currentBlueBeaconState)
		{
			case LED_BLUE_BEACON_ALL_OFF:
				for(byte i = 0; i < sizeof(this->_LED_NAMES_For_BlueBeaconLEDs) / sizeof(this->_LED_NAMES_For_BlueBeaconLEDs[0]) ; i++)
				{
					this->discreteLEDControl( this->_LED_NAMES_For_BlueBeaconLEDs[ i ], LED_OFF );//turn off all the elements in the array
				}//end for	
				break;		
			case LED_BLUE_BEACON_ALL_ON:
				for(byte i = 0; i < sizeof(this->_LED_NAMES_For_BlueBeaconLEDs) / sizeof(this->_LED_NAMES_For_BlueBeaconLEDs[0]) ; i++)
				{
					this->discreteLEDControl( this->_LED_NAMES_For_BlueBeaconLEDs[ i ], LED_ON );//turn on all the elements in the array
				}//end for	
				break;				
			case LED_BLUE_BEACON_DIRECTIONAL_MODE:
				this->runBlueBeaconDirectionalControl(this->_currentBeaconLEDDirection);
				break;
			case LED_BLUE_BEACON_ALL_NEUTRAL:
				//Do nothing recurring.
				break;					
			default:
				//Do nothing recurring.			
				break;				
		}//end switch
	}//end if
		
	//Run the finalized LED States (this function is also ran by setUniversalLEDMode() to control the LEDs initially)
	executeFinalLEDStates();//controls the LEDs based on the finalized settings (after overriding priorities)
	
	
}//end runLedController()
void LedController_NAVI::setUniversalLEDMode(byte desiredMode)
{
	
	//Change delay duration and then reset the counter
	//Note: The setUniversalLEDMode() default delay is 500ms.
	this->_counterPtr->setStopValue(this->_periodsForLongDelay);
	//reset the delay counter
	this->_counterPtr->counterReset();
	//initialize the current pattern index for universal LED Modes
	this->resetIndexCounter(this->_universalLEDModePatternIndexCounter);	
		
	//initialize/reset/turn off all LEDs before setting the Universal LED Mode
	for(byte i = 0; i < sizeof(this->_ALL_LED_NAMES) / sizeof(this->_ALL_LED_NAMES[0]) ; i++)
	{
		this->discreteLEDControl( this->_ALL_LED_NAMES[ i ], LED_OFF );//turn off all the elements in the array
	}//end for

	//Assign the _arrayOfInterestSize
	switch(desiredMode)
	{
		case LED_ALL_OFF_MODE:
			//Assign desired mode to the current universal LED mode since it's one of the valid cases
			this->_currentUniversalLEDMode = desiredMode;	
	
			//No other initialization needs to be done. By default all LEDs are initially turned off in the code for this function, above.
			break;
		case LED_ALL_ON_MODE:
			//Assign desired mode to the current universal LED mode since it's one of the valid cases
			this->_currentUniversalLEDMode = desiredMode;	

			//Set the overriding initialization LED states
			//Turn on all LEDs
			for(byte i = 0; i < sizeof(this->_ALL_LED_NAMES) / sizeof(this->_ALL_LED_NAMES[0]) ; i++)
			{
				this->discreteLEDControl( this->_ALL_LED_NAMES[ i ], LED_ON );//turn on all the elements in the array
			}//end for
			break;
		case LED_STANDARD_DAY_TIME_MODE:
			//Assign desired mode to the current universal LED mode since it's one of the valid cases
			this->_currentUniversalLEDMode = desiredMode;	

			
			//No other initialization needs to be done. By default all LEDs are initially turned off in the code for this function, above.			
			break;
		case LED_NIGHT_TIME_MODE:		
			//Set the overriding initialization LED states
			//Turn on the High Beams of the Headlights
			this->discreteLEDControl( LED_NAME_LEFT_HIGHBEAM_HEADLIGHT, LED_ON );
			this->discreteLEDControl( LED_NAME_RIGHT_HIGHBEAM_HEADLIGHT, LED_ON );
			//Turn on LEDs 2, 4, 5 on the left tail lights
			this->discreteLEDControl( LED_NAME_LEFT_RED2_TAILLIGHT, LED_ON );
			this->discreteLEDControl( LED_NAME_LEFT_RED4_TAILLIGHT, LED_ON );
			this->discreteLEDControl( LED_NAME_LEFT_RED5_TAILLIGHT, LED_ON );
			//Turn on LEDs 2, 4, 5 on the right tail lights
			this->discreteLEDControl( LED_NAME_RIGHT_RED2_TAILLIGHT, LED_ON );
			this->discreteLEDControl( LED_NAME_RIGHT_RED4_TAILLIGHT, LED_ON );
			this->discreteLEDControl( LED_NAME_RIGHT_RED5_TAILLIGHT, LED_ON );			
			
			break;
/*OLD CODE

		case LED_HAZARD_MODE:		
			//Assign desired mode to the current universal LED mode since it's one of the valid cases
			this->_currentUniversalLEDMode = desiredMode;	

			
			//No other initialization needs to be done. By default all LEDs are initially turned off in the code for this function, above.
			
			this->_arrayOfInterestSize = sizeof(this->_LED_NAMES_For_HazardMode) / sizeof(this->_LED_NAMES_For_HazardMode[0]);
			
			//Set Custom Delay (if required)
			//This mode uses a 500ms delay. And that's the default delay for setUniversalLEDMode().
			
			break;
*/			
		case LED_DEMO_MODE:
			//Assign desired mode to the current universal LED mode since it's one of the valid cases
			this->_currentUniversalLEDMode = desiredMode;
			
			//No other initialization needs to be done. By default all LEDs are initially turned off in the code for this function, above.
			
			this->_arrayOfInterestSize = sizeof(this->_LED_NAMES_For_DemoMode) / sizeof(this->_LED_NAMES_For_DemoMode[0]);
			
			//Set Custom Delay (if required)
			//This mode uses a 500ms delay. And that's the default delay for setUniversalLEDMode().
			
			break;
		case LED_ERROR_MODE:
			//Assign desired mode to the current universal LED mode since it's one of the valid cases
			this->_currentUniversalLEDMode = desiredMode;	
			
			switch(this->_currentErrorState)
			{
				case LED_ERROR_TYPE_NONE:
					//No other initialization needs to be done. By default all LEDs are initially turned off in the code for this function, above.
					break;
				case LED_ERROR_TYPE_GENERIC_HEALTH:
					//Assign the array of interest that contains the array of LED(s) that should blink
					this->_arrayOfInterest = _LED_NAMES_For_Error_Type_Generic_Health;
					//Assign the array of interest's size
					this->_arrayOfInterestSize = sizeof(this->_arrayOfInterest) / sizeof(this->_arrayOfInterest[0]);
					//Initialize any other LEDs that should be on (solid)
					this->discreteLEDControl( LED_NAME_LEFT_RED1_TAILLIGHT, LED_ON );//turn on this LED
					this->discreteLEDControl( LED_NAME_RIGHT_RED1_TAILLIGHT, LED_ON );//turn on this LED
					//Set Custom Delay (if required)
					//This mode uses a 500ms delay. And that's the default delay for setUniversalLEDMode().	
					break;
				case LED_ERROR_TYPE_GENERIC_SYSTEM:
					//Assign the array of interest that contains the array of LED(s) that should blink
					this->_arrayOfInterest = _LED_NAMES_For_Error_Type_Generic_System;
					//Assign the array of interest's size
					this->_arrayOfInterestSize = sizeof(this->_arrayOfInterest) / sizeof(this->_arrayOfInterest[0]);
					//Initialize any other LEDs that should be on (solid)
					this->discreteLEDControl( LED_NAME_LEFT_RED2_TAILLIGHT, LED_ON );//turn on this LED
					this->discreteLEDControl( LED_NAME_RIGHT_RED2_TAILLIGHT, LED_ON );//turn on this LED
					//Set Custom Delay (if required)
					//This mode uses a 500ms delay. And that's the default delay for setUniversalLEDMode().	
					break;
				case LED_ERROR_TYPE_SW_RESET:
					//Assign the array of interest that contains the array of LED(s) that should blink
					this->_arrayOfInterest = _LED_NAMES_For_Error_Type_SW_Reset;
					//Assign the array of interest's size
					this->_arrayOfInterestSize = sizeof(this->_arrayOfInterest) / sizeof(this->_arrayOfInterest[0]);
					//Initialize any other LEDs that should be on (solid)
					this->discreteLEDControl( LED_NAME_LEFT_RED3_TAILLIGHT, LED_ON );//turn on this LED
					this->discreteLEDControl( LED_NAME_RIGHT_RED3_TAILLIGHT, LED_ON );//turn on this LED
					//Set Custom Delay (if required)
					//This mode uses a 500ms delay. And that's the default delay for setUniversalLEDMode().	
					break;
				case LED_ERROR_TYPE_SYNC:
					//Assign the array of interest that contains the array of LED(s) that should blink
					this->_arrayOfInterest = _LED_NAMES_For_Error_Type_Sync;
					//Assign the array of interest's size
					this->_arrayOfInterestSize = sizeof(this->_arrayOfInterest) / sizeof(this->_arrayOfInterest[0]);
					//Initialize any other LEDs that should be on (solid)
					this->discreteLEDControl( LED_NAME_LEFT_RED4_TAILLIGHT, LED_ON );//turn on this LED
					this->discreteLEDControl( LED_NAME_RIGHT_RED4_TAILLIGHT, LED_ON );//turn on this LED
					//Set Custom Delay (if required)
					//This mode uses a 500ms delay. And that's the default delay for setUniversalLEDMode().	
					break;
				case LED_ERROR_TYPE_INVALID_STATE_OR_MODE:
					//Assign the array of interest that contains the array of LED(s) that should blink
					this->_arrayOfInterest = _LED_NAMES_For_Error_Type_Invalid_State_Or_Mode;
					//Assign the array of interest's size
					this->_arrayOfInterestSize = sizeof(this->_arrayOfInterest) / sizeof(this->_arrayOfInterest[0]);
					//Initialize any other LEDs that should be on (solid)
					this->discreteLEDControl( LED_NAME_LEFT_RED5_TAILLIGHT, LED_ON );//turn on this LED
					this->discreteLEDControl( LED_NAME_RIGHT_RED5_TAILLIGHT, LED_ON );//turn on this LED
					//Set Custom Delay (if required)
					//This mode uses a 500ms delay. And that's the default delay for setUniversalLEDMode().	
					break;
				case LED_ERROR_TYPE_UNDEFINED:
					//Assign the array of interest that contains the array of LED(s) that should blink
					this->_arrayOfInterest = _LED_NAMES_For_Error_Type_Undefined;
					//Assign the array of interest's size
					this->_arrayOfInterestSize = sizeof(this->_arrayOfInterest) / sizeof(this->_arrayOfInterest[0]);
					//Initialize any other LEDs that should be on (solid)
					this->discreteLEDControl( LED_NAME_LEFT_RED1_TAILLIGHT, LED_ON );//turn on this LED
					this->discreteLEDControl( LED_NAME_RIGHT_RED1_TAILLIGHT, LED_ON );//turn on this LED
					this->discreteLEDControl( LED_NAME_LEFT_RED3_TAILLIGHT, LED_ON );//turn on this LED
					this->discreteLEDControl( LED_NAME_RIGHT_RED3_TAILLIGHT, LED_ON );//turn on this LED
					//Set Custom Delay (if required)
					//This mode uses a 500ms delay. And that's the default delay for setUniversalLEDMode().	
					break;			
				default:
					//Do nothing else since it's an invalid state.	
					break;				
			}//end switch
			
			break;		
		case LED_STEALTH_MODE:
			//Assign desired mode to the current universal LED mode since it's one of the valid cases
			this->_currentUniversalLEDMode = desiredMode;	
			
			//No other initialization needs to be done. By default all LEDs are initially turned off in the code for this function, above.
			break;
		case LED_DEBUG_MODE:
			//Assign desired mode to the current universal LED mode since it's one of the valid cases
			this->_currentUniversalLEDMode = desiredMode;	

			//No other initialization needs to be done. By default all LEDs are initially turned off in the code for this function, above.
			
			//In LED_DEBUG_MODE, userDiscreteLEDControl() is allowed to run where the user can control the LEDs.
			break;			
		default:
			//No other initialization needs to be done. By default all LEDs are initially turned off in the code for this function, above.
			
			this->_currentUniversalLEDMode = LED_ALL_OFF_MODE;//set the current universal LED mode to the default LED_ALL_OFF_MODE
			
			//Do nothing else since it's an invalid state
			break;
	}//end switch
	
	
	//Run the finalized LED States to set the initial LED controls (this function is also ran by runLedController() to control the LEDs recurringly)
	//Note: This is needed to be done here because for non-recurring LED states, nothing will be set again in runLedController() because runLedController() assumes it will be set here by setUniversalLEDMode()
	executeFinalLEDStates();//controls the LEDs based on the finalized settings (after overriding priorities)
	
}
void LedController_NAVI::setHazardLightsMode(byte desiredHazardLightsState)
{
	
	
	/*
	Note:
		It is implied that setUniversalLEDMode() is called first and sets the modes. It also initializes the LED states and executes the LEDs controls.
		Then, if needed, setHazardLightsMode() is called and sets the hazard lights. (which will only be active if the mode that was set allowed it.)
		Then runLedController() is ran recurringly, and determines (based on mode) if the rover motion's LED states will override the current LED state.		
		
	Note:
		Always make sure runLedController() is called after setHazardLightsMode() is called so:
		1) The LED state can be overridden by runLedController() if there is a higher priority
					
		2) Then runLedController() can call executeFinalLEDStates() which controls the LEDs based on the finalized states
		
	*/
	
	
	//Change delay duration and then reset the counter
	//Note: The roverMotion() default is 250ms.
	this->_counterPtr->setStopValue(this->_periodsForLongDelay);
	//reset the delay counter
	this->_counterPtr->counterReset();
	//initialize the current pattern index for  rover motion	
	this->resetIndexCounter(this->_hazardLightsPatternIndexCounter);	
		
	
	//Reset the states for certain LED types before changing states. In the switch case for the states, the LEDs state will be set if needed
	//Note these states aren't executed at the end by executeFinalLEDStates(), so the LEDs won't flicker if the states are changing/overridden.
	//Head lights (signal)
	this->discreteLEDControl(LED_NAME_RIGHT_SIGNAL_HEADLIGHT, LED_OFF);
	this->discreteLEDControl(LED_NAME_LEFT_SIGNAL_HEADLIGHT, LED_OFF);
	//Side signal lights
	this->discreteLEDControl(LED_NAME_RIGHT_SIDE_SIGNAL_LIGHT, LED_OFF);
	this->discreteLEDControl(LED_NAME_LEFT_SIDE_SIGNAL_LIGHT, LED_OFF);
	//Tail lights (right)
	this->discreteLEDControl(LED_NAME_RIGHT_RED1_TAILLIGHT, LED_OFF);
	this->discreteLEDControl(LED_NAME_RIGHT_RED2_TAILLIGHT, LED_OFF);
	this->discreteLEDControl(LED_NAME_RIGHT_RED3_TAILLIGHT, LED_OFF);	
	//Tail lights (left)
	this->discreteLEDControl(LED_NAME_LEFT_RED1_TAILLIGHT, LED_OFF);
	this->discreteLEDControl(LED_NAME_LEFT_RED2_TAILLIGHT, LED_OFF);
	this->discreteLEDControl(LED_NAME_LEFT_RED3_TAILLIGHT, LED_OFF);	
	
	
	
	
	
	//Assign the hazard lights state if it's one of the valid modes
	switch(desiredHazardLightsState)
	{
		case LED_HAZARDS_OFF:
			//Initialize the LEDs to this motion's state
			//It already turned off all the motion LEDs. Nothing else is needed.
			
			//Note: You don't want to turn on any LEDs at this state since the mode has not been verified as a Rover Motion friendly mode yet. LEDs will instead be turned on in the runLedController() function once the current mode has been verified as a Rover Motion friendly state.
			
			//Assign desired rover motion to the current rover motion since it's one of the valid cases		
			this->_currentHazardLightsState = desiredHazardLightsState;
			break;
		case LED_HAZARDS_ON:
			//Initialize the LEDs to this motion's state
			//It already turned off all the motion LEDs. Nothing else is needed.
			
			//Note: You don't want to turn on any LEDs at this state since the mode has not been verified as a Rover Motion friendly mode yet. LEDs will instead be turned on in the runLedController() function once the current mode has been verified as a Rover Motion friendly state.
			
			//Assign desired rover motion to the current rover motion since it's one of the valid cases		
			this->_currentHazardLightsState = desiredHazardLightsState;
			break;
		case LED_HAZARDS_NEUTRAL:
			//Initialize the LEDs to this motion's state
			//It already turned off all the motion LEDs. Nothing else is needed.
			
			//Note: You don't want to turn on any LEDs at this state since the mode has not been verified as a Rover Motion friendly mode yet. LEDs will instead be turned on in the runLedController() function once the current mode has been verified as a Rover Motion friendly state.
			
			//Assign desired rover motion to the current rover motion since it's one of the valid cases		
			this->_currentHazardLightsState = desiredHazardLightsState;
			break;
		default:
			//else do nothing since it's an invalid mode
			break;
	}//end switch
}
void LedController_NAVI::setFogLightMode(byte fogLightsState)
{
	//Assign the fog light state if it's one of the valid modes
	switch(fogLightsState)
	{
		case LED_FOG_OFF:
			this->_currentFogLightState = LED_FOG_OFF;
			break;
		case LED_FOG_ON:
			this->_currentFogLightState = LED_FOG_ON;
			break;
		case LED_FOG_NEUTRAL:
			this->_currentFogLightState = LED_FOG_NEUTRAL;
			break;
		default:
			//else do nothing since it's an invalid mode
			break;
	}//end switch
}
void LedController_NAVI::setUnderglowLightMode(byte underglowLightState)
{
	//Assign the underglow light mode if it's one of the valid modes
	switch(underglowLightState)
	{
		case LED_UNDERGLOW_OFF:
			this->_currentUnderglowState = LED_UNDERGLOW_OFF;
			break;
		case LED_UNDERGLOW_ON:
			this->_currentUnderglowState = LED_UNDERGLOW_ON;
			break;
		case LED_UNDERGLOW_NEUTRAL:
			this->_currentUnderglowState = LED_UNDERGLOW_NEUTRAL;
			break;
		default:
			//else do nothing since it's an invalid mode
			break;
	}//end switch
}
void LedController_NAVI::setIRBeaconLightMode(byte irBeaconLightState)
{
	//Assign the IR Beacon light mode if it's one of the valid modes
	switch(irBeaconLightState)
	{
		case LED_IR_BEACON_ALL_OFF:
			this->_currentIRBeaconState = LED_IR_BEACON_ALL_OFF;
			break;
		case LED_IR_BEACON_ALL_ON:
			this->_currentIRBeaconState = LED_IR_BEACON_ALL_ON;
			break;
		case LED_IR_BEACON_DIRECTIONAL_MODE:
			this->_currentIRBeaconState = LED_IR_BEACON_DIRECTIONAL_MODE;
			break;
		case LED_IR_BEACON_ALL_NEUTRAL:
			this->_currentIRBeaconState = LED_IR_BEACON_ALL_NEUTRAL;
			break;			
		default:
			//else do nothing since it's an invalid mode
			break;
	}//end switch
}
void LedController_NAVI::setBlueBeaconLightMode(byte blueBeaconLightState)
{
	//Assign the Blue Beacon light mode if it's one of the valid modes
	switch(blueBeaconLightState)
	{
		case LED_BLUE_BEACON_ALL_OFF:
			this->_currentIRBeaconState = LED_BLUE_BEACON_ALL_OFF;
			break;
		case LED_BLUE_BEACON_ALL_ON:
			this->_currentIRBeaconState = LED_BLUE_BEACON_ALL_ON;
			break;
		case LED_BLUE_BEACON_DIRECTIONAL_MODE:
			this->_currentIRBeaconState = LED_BLUE_BEACON_DIRECTIONAL_MODE;
			break;
		case LED_BLUE_BEACON_ALL_NEUTRAL:
			this->_currentIRBeaconState = LED_BLUE_BEACON_ALL_NEUTRAL;
			break;			
		default:
			//else do nothing since it's an invalid mode
			break;
	}//end switch
}
void LedController_NAVI::setBeaconDirection(byte beaconLedDirection)
{
	//Assign the Beacon Direction if it's one of the valid modes
	switch(beaconLedDirection)
	{
		case LED_DIRECTION_NONE:
			this->_currentBeaconLEDDirection = LED_DIRECTION_NONE;
			break;
		case LED_DIRECTION_FRONT:
			this->_currentBeaconLEDDirection = LED_DIRECTION_FRONT;
			break;
		case LED_DIRECTION_FRONT_RIGHT:
			this->_currentBeaconLEDDirection = LED_DIRECTION_FRONT_RIGHT;
			break;
		case LED_DIRECTION_RIGHT:
			this->_currentBeaconLEDDirection = LED_DIRECTION_RIGHT;
			break;			
		case LED_DIRECTION_REAR_RIGHT:
			this->_currentBeaconLEDDirection = LED_DIRECTION_REAR_RIGHT;
			break;			
		case LED_DIRECTION_REAR:
			this->_currentBeaconLEDDirection = LED_DIRECTION_REAR;
			break;			
		case LED_DIRECTION_REAR_LEFT:
			this->_currentBeaconLEDDirection = LED_DIRECTION_REAR_LEFT;
			break;			
		case LED_DIRECTION_LEFT:
			this->_currentBeaconLEDDirection = LED_DIRECTION_LEFT;
			break;			
		case LED_DIRECTION_FRONT_LEFT:
			this->_currentBeaconLEDDirection = LED_DIRECTION_FRONT_LEFT;
			break;						
		default:
			//else do nothing since it's an invalid mode
			break;
	}//end switch
}
void LedController_NAVI::setRoverMotion(byte desiredRoverMotion)
{
	
	/*
	Note:
		It is implied that setUniversalLEDMode() is called first and sets the modes. It also initializes the LED states and executes the LEDs controls.
		Then, if needed, setRoverMotion() is called and sets the motion. (which will only be active if the mode that was set allowed it.)
		Then runLedController() is ran recurringly, and determines (based on mode) if the rover motion's LED states will override the current LED state.		
		
	Note:
		Always make sure runLedController() is called after setRoverMotion() is called so:
		1) The LED state can be overridden by runLedController() if there is a higher priority
			i.e.
			setRoverMotion() will clear all the tail lights states for LED_MOTION_STANDARD. 
			
			And when runLedController() is ran, it will set the tail light states if needed for LED_NIGHT_TIME_MODE, LED_DEMO_MODE, LED_ERROR_MODE, LED_HAZARDS_OFF, etc.
			
			Then at //Rover Motion Overrides (if applicable)
				For LED_MOTION_STANDARD, nothing is needed to be done. So it will keep it's state it it wasn't overrided by the other modes.
			
		2) Then runLedController() can call executeFinalLEDStates() which controls the LEDs based on the finalized states
	*/
	
	
	//Change delay duration and then reset the counter
	//Note: The roverMotion() default is 250ms.
	this->_counterPtr->setStopValue(this->_periodsForShortDelay);
	//reset the delay counter
	this->_counterPtr->counterReset();
	//initialize the current pattern index for  rover motion	
	this->resetIndexCounter(this->_roverMotionPatternIndexCounter);	
		
	
	//Reset the states for certain LED types before changing states. In the switch case for the states, the LEDs state will be set if needed
	//Note these states aren't executed at the end by executeFinalLEDStates(), so the LEDs won't flicker if the states are changing/overridden.
	//Head lights (signal)
	this->discreteLEDControl(LED_NAME_RIGHT_SIGNAL_HEADLIGHT, LED_OFF);
	this->discreteLEDControl(LED_NAME_LEFT_SIGNAL_HEADLIGHT, LED_OFF);
	//Side signal lights
	this->discreteLEDControl(LED_NAME_RIGHT_SIDE_SIGNAL_LIGHT, LED_OFF);
	this->discreteLEDControl(LED_NAME_LEFT_SIDE_SIGNAL_LIGHT, LED_OFF);
	//Tail lights (right)
	this->discreteLEDControl(LED_NAME_RIGHT_RED1_TAILLIGHT, LED_OFF);
	this->discreteLEDControl(LED_NAME_RIGHT_RED2_TAILLIGHT, LED_OFF);
	this->discreteLEDControl(LED_NAME_RIGHT_RED3_TAILLIGHT, LED_OFF);
	this->discreteLEDControl(LED_NAME_RIGHT_RED4_TAILLIGHT, LED_OFF);
	this->discreteLEDControl(LED_NAME_RIGHT_RED5_TAILLIGHT, LED_OFF);
	//Tail lights (left)
	this->discreteLEDControl(LED_NAME_LEFT_RED1_TAILLIGHT, LED_OFF);
	this->discreteLEDControl(LED_NAME_LEFT_RED2_TAILLIGHT, LED_OFF);
	this->discreteLEDControl(LED_NAME_LEFT_RED3_TAILLIGHT, LED_OFF);
	this->discreteLEDControl(LED_NAME_LEFT_RED4_TAILLIGHT, LED_OFF);
	this->discreteLEDControl(LED_NAME_LEFT_RED5_TAILLIGHT, LED_OFF);
	//Reverse Lights
	this->discreteLEDControl(LED_NAME_RIGHT_WHITE_TAILLIGHT, LED_OFF);
	this->discreteLEDControl(LED_NAME_LEFT_WHITE_TAILLIGHT, LED_OFF);
		

	switch(desiredRoverMotion)
	{
		case LED_MOTION_STANDARD:
			//Initialize the LEDs to this motion's state
			//It already turned off all the motion LEDs. Nothing else is needed.
			
			//Note: You don't want to turn on any LEDs at this state since the mode has not been verified as a Rover Motion friendly mode yet. LEDs will instead be turned on in the runLedController() function once the current mode has been verified as a Rover Motion friendly state.
			
			//Assign desired rover motion to the current rover motion since it's one of the valid cases
			this->_currentRoverMotion = desiredRoverMotion;			
			break;
		case LED_MOTION_TURN_LEFT:
			//Initialize the LEDs to this motion's state
			//It already turned off all the motion LEDs. Nothing else is needed.
			
			//Note: You don't want to turn on any LEDs at this state since the mode has not been verified as a Rover Motion friendly mode yet. LEDs will instead be turned on in the runLedController() function once the current mode has been verified as a Rover Motion friendly state.
			
			//Assign desired rover motion to the current rover motion since it's one of the valid cases
			this->_currentRoverMotion = desiredRoverMotion;
			
			//Set Custom Delay (if required)
			//This mode uses a 250ms delay. And that's the default delay for setUniversalLEDMode().
			
			//Note: Array of Interest is not used since there is more than one array of interest and I don't want to create three global variables (to save space). It will just be explicitly called out in each for loop.
			break;
		case LED_MOTION_TURN_RIGHT:
			//Initialize the LEDs to this motion's state
			//It already turned off all the motion LEDs. Nothing else is needed.
			
			//Note: You don't want to turn on any LEDs at this state since the mode has not been verified as a Rover Motion friendly mode yet. LEDs will instead be turned on in the runLedController() function once the current mode has been verified as a Rover Motion friendly state.
			
			//Assign desired rover motion to the current rover motion since it's one of the valid cases
			this->_currentRoverMotion = desiredRoverMotion;
			
			//Set Custom Delay (if required)
			//This mode uses a 250ms delay. And that's the default delay for setUniversalLEDMode().
			
			//Note: Array of Interest is not used since there is more than one array of interest and I don't want to create three global variables (to save space). It will just be explicitly called out in each for loop.				
			
			break;
		case LED_MOTION_BRAKE:
			//Initialize the LEDs to this motion's state
			//It already turned off all the motion LEDs. Nothing else is needed.
			
			//Note: You don't want to turn on any LEDs at this state since the mode has not been verified as a Rover Motion friendly mode yet. LEDs will instead be turned on in the runLedController() function once the current mode has been verified as a Rover Motion friendly state.
			
			//Assign desired rover motion to the current rover motion since it's one of the valid cases
			this->_currentRoverMotion = desiredRoverMotion;			

			//Set Custom Delay (if required)
			//This mode uses a 250ms delay. And that's the default delay for setUniversalLEDMode().
			
			//Note: Array of Interest is not used since there is more than one array of interest and I don't want to create three global variables (to save space). It will just be explicitly called out in each for loop.	
			
			break;
		case LED_MOTION_REVERSE:
			//Initialize the LEDs to this motion's state
			//It already turned off all the motion LEDs. Nothing else is needed.
			
			//Note: You don't want to turn on any LEDs at this state since the mode has not been verified as a Rover Motion friendly mode yet. LEDs will instead be turned on in the runLedController() function once the current mode has been verified as a Rover Motion friendly state.
			
			//Assign desired rover motion to the current rover motion since it's one of the valid cases
			this->_currentRoverMotion = desiredRoverMotion;
			
			break;
		default:
			//Initialize the LEDs to this motion's state
			//It already turned off all the motion LEDs. Nothing else is needed.
			
			//Note: You don't want to turn on any LEDs at this state since the mode has not been verified as a Rover Motion friendly mode yet. LEDs will instead be turned on in the runLedController() function once the current mode has been verified as a Rover Motion friendly state.
			
			this->_currentRoverMotion = LED_MOTION_STANDARD;//set the current rover motion to the default LED_MOTION_STANDARD
			
			//Do nothing else since it's an invalid state		
			break;
	}//end switch

	
	//Note: Do not run executeFinalLEDStates() here. The LEDs will execute in runLedController() after the modes has been check to make sure they're valid ones for RoverMotion.
	//Though you can check the modes here, if you do, and it's not set yet, then this function won't run. But you want to allow this function to "preset" the rover motion before the allowed modes are set. So that's why you don't want to check the modes here yet.	
	
}
void LedController_NAVI::setErrorType(byte errorType)
{
	
	/*

	Note:
		It is implied that setErrorType() is called first and sets the error type. Then setUniversalLEDMode() is called and sets the mode and initializes the LED states and executes the LEDs controls.
		Then runLedController() is ran recurringly, and determines (based on mode and error type) and controls the LEDs recurringly.

	*/
	
	

	//Assign the Error Type if it's one of the valid modes
	switch(errorType)
	{
		case LED_ERROR_TYPE_NONE:
			this->_currentErrorState = errorType;
			break;
		case LED_ERROR_TYPE_GENERIC_HEALTH:
			this->_currentErrorState = errorType;
			break;
		case LED_ERROR_TYPE_GENERIC_SYSTEM:
			this->_currentErrorState = errorType;			
			break;
		case LED_ERROR_TYPE_SW_RESET:
			this->_currentErrorState = errorType;			
			break;
		case LED_ERROR_TYPE_SYNC:
			this->_currentErrorState = errorType;			
			break;
		case LED_ERROR_TYPE_INVALID_STATE_OR_MODE:
			this->_currentErrorState = errorType;			
			break;
		case LED_ERROR_TYPE_UNDEFINED:
			this->_currentErrorState = errorType;			
			break;			
		default:
			//Do nothing else since it's an invalid state		
			break;				
	}//end switch
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
	
	
	#ifdef _DEBUG_TURN_ON_ALL_LEDS_AT_POR_
		this->_currentUniversalLEDMode = LED_ALL_ON_MODE;
	#else
		this->_currentUniversalLEDMode = LED_ALL_OFF_MODE;
	#endif
	
	this->_currentRoverMotion = LED_MOTION_STANDARD;
	this->_currentErrorState = LED_ERROR_TYPE_NONE;
	this->_currentHazardLightsState = LED_HAZARDS_OFF;
	this->_currentFogLightState = LED_FOG_OFF;
	this->_currentUnderglowState = LED_UNDERGLOW_OFF;
	this->_currentIRBeaconState = LED_IR_BEACON_ALL_OFF;
	this->_currentBlueBeaconState = LED_BLUE_BEACON_ALL_OFF;
	this->_currentBeaconLEDDirection = LED_DIRECTION_NONE;
	this->_arrayOfInterest = NULL;
	this->_arrayOfInterestSize = 0;
	this->_universalLEDModePatternIndexCounter = 0;
	this->_hazardLightsPatternIndexCounter = 0;
	this->_roverMotionPatternIndexCounter = 0;
	this->_blueBeaconLEDsPatternIndexCounter = 0;
	this->_irBeaconLEDsPatternIndexCounter = 0;
	
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


void LedController_NAVI::autoIncrementIndexCounter(byte &indexCounter, byte rollOverValue)
{
	//increment counter for the next iteration
	indexCounter++;

	if( indexCounter >=  rollOverValue )//Note: It resets when it's >= to this roll over value. But the index does start counting at 0.
	{
		this->resetIndexCounter(indexCounter);//reset the counter once it has reached (or surpassed) the roll over value
	}//end if	
}

void LedController_NAVI::resetIndexCounter(byte &indexCounter)
{
	indexCounter = 0;
}
void LedController_NAVI::discreteLEDControl(byte ledName, byte desiredLedState)
{
	
	//Note: Boolean Bit Flags are used to hold the state of each of the LEDs. This is so that the states can be set and overridden with a high priority setting. And then once everything has been determined, the LED Controller will execute the changes all at once. (else if bit flags weren't used, the LEDs may flash as they are changing states from being overridden from something of a higher priority.
	

	byte * correspondingLEDFlagSet;//pointer to point to the corresponding LED Flag Set
	byte correspondingLEDFlagOfInterest;//holds the corresponding LED Flag of Interest


	//Assign the correspondingLEDFlagOfInterest and pass the address of the flag set to the correspondingLEDFlagSet pointer
	switch(ledName)
	{
		case LED_NAME_FRONT_LEFT_IR_BEACON:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_FRONT_LEFT_IR_BEACON;
			correspondingLEDFlagSet= &this->_ledStateFlagSet1;
			break;
		case LED_NAME_BACK_LEFT_IR_BEACON:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_BACK_LEFT_IR_BEACON;
			correspondingLEDFlagSet= &this->_ledStateFlagSet1;
			break;
		case LED_NAME_BACK_RIGHT_IR_BEACON:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_BACK_RIGHT_IR_BEACON;
			correspondingLEDFlagSet= &this->_ledStateFlagSet1;
			break;
		case LED_NAME_FRONT_RIGHT_IR_BEACON:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_FRONT_RIGHT_IR_BEACON;
			correspondingLEDFlagSet= &this->_ledStateFlagSet1;
			break;
		case LED_NAME_LEFT_BLUE_BEACON:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_LEFT_BLUE_BEACON;
			correspondingLEDFlagSet= &this->_ledStateFlagSet1;
			break;
		case LED_NAME_BACK_BLUE_BEACON:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_BACK_BLUE_BEACON;
			correspondingLEDFlagSet= &this->_ledStateFlagSet1;
			break;
		case LED_NAME_RIGHT_BLUE_BEACON:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_RIGHT_BLUE_BEACON;
			correspondingLEDFlagSet= &this->_ledStateFlagSet1;
			break;
		case LED_NAME_FRONT_BLUE_BEACON:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_FRONT_BLUE_BEACON;
			correspondingLEDFlagSet= &this->_ledStateFlagSet1;
			break;
		case LED_NAME_RIGHT_HIGHBEAM_HEADLIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_RIGHT_HIGHBEAM_HEADLIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet2;
			break;
		case LED_NAME_RIGHT_SIGNAL_HEADLIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_RIGHT_SIGNAL_HEADLIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet2;
			break;
		case LED_NAME_RIGHT_FOG_HEADLIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_RIGHT_FOG_HEADLIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet2;
			break;
		case LED_NAME_LEFT_HIGHBEAM_HEADLIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_LEFT_HIGHBEAM_HEADLIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet2;
			break;
		case LED_NAME_LEFT_SIGNAL_HEADLIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_LEFT_SIGNAL_HEADLIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet2;
			break;
		case LED_NAME_LEFT_FOG_HEADLIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_LEFT_FOG_HEADLIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet2;
			break;
		case LED_NAME_RIGHT_RED1_TAILLIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_RIGHT_RED1_TAILLIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet3;
			break;
		case LED_NAME_RIGHT_RED2_TAILLIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_RIGHT_RED2_TAILLIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet3;
			break;
		case LED_NAME_RIGHT_RED3_TAILLIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_RIGHT_RED3_TAILLIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet3;
			break;
		case LED_NAME_RIGHT_RED4_TAILLIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_RIGHT_RED4_TAILLIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet3;
			break;
		case LED_NAME_RIGHT_RED5_TAILLIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_RIGHT_RED5_TAILLIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet3;
			break;
		case LED_NAME_RIGHT_WHITE_TAILLIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_RIGHT_WHITE_TAILLIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet3;
			break;
		case LED_NAME_LEFT_RED1_TAILLIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_LEFT_RED1_TAILLIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet4;
			break;
		case LED_NAME_LEFT_RED2_TAILLIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_LEFT_RED2_TAILLIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet4;
			break;
		case LED_NAME_LEFT_RED3_TAILLIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_LEFT_RED3_TAILLIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet3;
			break;
		case LED_NAME_LEFT_RED4_TAILLIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_LEFT_RED4_TAILLIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet3;
			break;
		case LED_NAME_LEFT_RED5_TAILLIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_LEFT_RED5_TAILLIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet4;
			break;
		case LED_NAME_LEFT_WHITE_TAILLIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_LEFT_WHITE_TAILLIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet4;
			break;
		case LED_NAME_UNDERGLOW_LIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_UNDERGLOW_LIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet4;
			break;
		case LED_NAME_RIGHT_SIDE_SIGNAL_LIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_RIGHT_SIDE_SIGNAL_LIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet2;
			break;
		case LED_NAME_LEFT_SIDE_SIGNAL_LIGHT:
			correspondingLEDFlagOfInterest= _BTFG_LED_STATE_LEFT_SIDE_SIGNAL_LIGHT;
			correspondingLEDFlagSet= &this->_ledStateFlagSet2;
			break;
		default:
			//do nothing
			break;
	}//end switch
		

	if(desiredLedState == LED_ON)
	{
		BooleanBitFlags::setFlagBit(*correspondingLEDFlagSet, correspondingLEDFlagOfInterest);//dereference the pointer in order to pass the address the pointer is pointing to, which is the address of the corresponding LED Flag Set (correspondingLEDFlagSet)
	}//end if
	else if (desiredLedState == LED_OFF)
	{
		BooleanBitFlags::clearFlagBit(*correspondingLEDFlagSet, correspondingLEDFlagOfInterest);//dereference the pointer in order to pass the address the pointer is pointing to, which is the address of the corresponding LED Flag Set (correspondingLEDFlagSet)
	}//end else
	//else do nothing, as it's an invalid input

		
		
}//end of discreteLEDControl()
void LedController_NAVI::runIRBeaconDirectionalControl(byte ledDirection)
{

//For IR Beacon LEDs:
//For Front, Right, Back, Left, just light up the two LEDs associated with that direction
//For Front Right, Back Right, Back Left, Front Left, light up the one LED associated with that direction


	switch(this->_currentBeaconLEDDirection)
	{
		case LED_DIRECTION_NONE:
			//Turn Off All IR Beacon LEDS
			this->discreteLEDControl(LED_NAME_FRONT_RIGHT_IR_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_BACK_RIGHT_IR_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_BACK_LEFT_IR_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_FRONT_LEFT_IR_BEACON, LED_OFF);
			break;
		case LED_DIRECTION_FRONT:
			//Turn On the LED(s) for this Corresponding Direction
			this->discreteLEDControl(LED_NAME_FRONT_RIGHT_IR_BEACON, LED_ON);
			this->discreteLEDControl(LED_NAME_FRONT_LEFT_IR_BEACON, LED_ON);
			//Turn Off All Other IR Beacon LEDS
			this->discreteLEDControl(LED_NAME_BACK_RIGHT_IR_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_BACK_LEFT_IR_BEACON, LED_OFF);
			break;
		case LED_DIRECTION_FRONT_RIGHT:
			//Turn On the LED(s) for this Corresponding Direction
			this->discreteLEDControl(LED_NAME_FRONT_RIGHT_IR_BEACON, LED_ON);			
			//Turn Off All Other IR Beacon LEDS			
			this->discreteLEDControl(LED_NAME_BACK_RIGHT_IR_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_BACK_LEFT_IR_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_FRONT_LEFT_IR_BEACON, LED_OFF);
			break;
		case LED_DIRECTION_RIGHT:
			//Turn On the LED(s) for this Corresponding Direction
			this->discreteLEDControl(LED_NAME_FRONT_RIGHT_IR_BEACON, LED_ON);
			this->discreteLEDControl(LED_NAME_BACK_RIGHT_IR_BEACON, LED_ON);
			//Turn Off All Other IR Beacon LEDS						
			this->discreteLEDControl(LED_NAME_BACK_LEFT_IR_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_FRONT_LEFT_IR_BEACON, LED_OFF);
			break;
		case LED_DIRECTION_REAR_RIGHT:
			//Turn On the LED(s) for this Corresponding Direction
			this->discreteLEDControl(LED_NAME_BACK_RIGHT_IR_BEACON, LED_ON);
			//Turn Off All Other IR Beacon LEDS
			this->discreteLEDControl(LED_NAME_FRONT_RIGHT_IR_BEACON, LED_OFF);			
			this->discreteLEDControl(LED_NAME_BACK_LEFT_IR_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_FRONT_LEFT_IR_BEACON, LED_OFF);		
			break;
		case LED_DIRECTION_REAR:
			//Turn On the LED(s) for this Corresponding Direction
			this->discreteLEDControl(LED_NAME_BACK_RIGHT_IR_BEACON, LED_ON);
			this->discreteLEDControl(LED_NAME_BACK_LEFT_IR_BEACON, LED_ON);
			//Turn Off All Other IR Beacon LEDS
			this->discreteLEDControl(LED_NAME_FRONT_RIGHT_IR_BEACON, LED_OFF);			
			this->discreteLEDControl(LED_NAME_FRONT_LEFT_IR_BEACON, LED_OFF);			
			break;
		case LED_DIRECTION_REAR_LEFT:
			//Turn On the LED(s) for this Corresponding Direction
			this->discreteLEDControl(LED_NAME_BACK_LEFT_IR_BEACON, LED_ON);
			//Turn Off All Other IR Beacon LEDS
			this->discreteLEDControl(LED_NAME_FRONT_RIGHT_IR_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_BACK_RIGHT_IR_BEACON, LED_OFF);			
			this->discreteLEDControl(LED_NAME_FRONT_LEFT_IR_BEACON, LED_OFF);				
			break;
		case LED_DIRECTION_LEFT:
			//Turn On the LED(s) for this Corresponding Direction
			this->discreteLEDControl(LED_NAME_BACK_LEFT_IR_BEACON, LED_ON);
			this->discreteLEDControl(LED_NAME_FRONT_LEFT_IR_BEACON, LED_ON);			
			//Turn Off All Other IR Beacon LEDS
			this->discreteLEDControl(LED_NAME_FRONT_RIGHT_IR_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_BACK_RIGHT_IR_BEACON, LED_OFF);			
			break;
		case LED_DIRECTION_FRONT_LEFT:
			//Turn On the LED(s) for this Corresponding Direction
			this->discreteLEDControl(LED_NAME_FRONT_LEFT_IR_BEACON, LED_ON);
			//Turn Off All Other IR Beacon LEDS
			this->discreteLEDControl(LED_NAME_FRONT_RIGHT_IR_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_BACK_RIGHT_IR_BEACON, LED_OFF);
			this->discreteLEDControl(LED_NAME_BACK_LEFT_IR_BEACON, LED_OFF);
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
	//Front Blue Beacon
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet1, _BTFG_LED_STATE_FRONT_BLUE_BEACON) )
	{
		this->_beaconLightAssy->turnOn(FRONT_BLUE_BEACON);
	}//end if
	else
	{
		this->_beaconLightAssy->turnOff(FRONT_BLUE_BEACON);
	}//end else
		
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

	//Back Left IR Beacon
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
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet2, _BTFG_LED_STATE_LEFT_SIDE_SIGNAL_LIGHT) )
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
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet3, _BTFG_LED_STATE_RIGHT_WHITE_TAILLIGHT) )
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
	if( BooleanBitFlags::flagIsSet(this->_ledStateFlagSet4, _BTFG_LED_STATE_LEFT_RED2_TAILLIGHT) )
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