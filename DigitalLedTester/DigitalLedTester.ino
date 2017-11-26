//Used for NAVI - 1

//This is for an Arduino MEGA

#include <UnderglowLeds.h>
#include <SideSignalLight.h>
#include <BeaconLightAssembly.h>
#include <HeadLightAssembly.h>
#include <TailLightAssembly.h>

//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast

#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ _MAIN_SERIAL_ //When using COMM Broadcast, reroute the PC USB output to the channel to MAIN instead
#else
	#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_
#endif

//Global Variables


//counter delays
//using a counter to create delays while still allowing the loop() to run (i.e. for messages, etc.)
unsigned long modesToggleDelay = 0;


//A counter use to increment through the different modes
byte modesTester = 0;


UnderglowLeds * underglowLight = new UnderglowLeds(UNDERGLOW_PIN);
SideSignalLight * leftSideSignal = new SideSignalLight(SIDE_LEFT_SIGNAL_PIN);
SideSignalLight * rightSideSignal = new SideSignalLight(SIDE_RIGHT_SIGNAL_PIN);
BeaconLightAssembly * beaconLightAssy = new BeaconLightAssembly(FRONT_LEFT_BEACON_IR_PIN, BACK_LEFT_BEACON_IR_PIN, BACK_RIGHT_BEACON_IR_PIN, FRONT_RIGHT_BEACON_IR_PIN, LEFT_BEACON_BLUE_PIN, BACK_BEACON_BLUE_PIN, RIGHT_BEACON_BLUE_PIN, FRONT_BEACON_BLUE_PIN);
HeadLightAssembly * leftHeadLightAssy = new HeadLightAssembly(LEFT_HIGHBEAM_HEADLIGHT_PIN, LEFT_SIGNAL_HEADLIGHT_PIN, LEFT_FOG_HEADLIGHT_PIN);
HeadLightAssembly * rightHeadLightAssy = new HeadLightAssembly(RIGHT_HIGHBEAM_HEADLIGHT_PIN, RIGHT_SIGNAL_HEADLIGHT_PIN, RIGHT_FOG_HEADLIGHT_PIN); 
TailLightAssembly * leftTailLightAssy = new TailLightAssembly(LEFT_RED_TAILLIGHT_1_PIN, LEFT_RED_TAILLIGHT_2_PIN, LEFT_RED_TAILLIGHT_3_PIN, LEFT_RED_TAILLIGHT_4_PIN, LEFT_RED_TAILLIGHT_5_PIN, LEFT_WHITE_TAILLIGHT_PIN);
TailLightAssembly * rightTailLightAssy = new TailLightAssembly(RIGHT_RED_TAILLIGHT_1_PIN, RIGHT_RED_TAILLIGHT_2_PIN, RIGHT_RED_TAILLIGHT_3_PIN, RIGHT_RED_TAILLIGHT_4_PIN, RIGHT_RED_TAILLIGHT_5_PIN, RIGHT_WHITE_TAILLIGHT_PIN);


//Holds all objects created by this sketch
RoverReset * resetArray[] = {
		underglowLight,		
		leftSideSignal,
		rightSideSignal,
		beaconLightAssy,
		leftHeadLightAssy,
		rightHeadLightAssy,
		leftTailLightAssy,
		rightTailLightAssy
};





void setup() {
	//resetting all objects in this sketch
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		if (!resetArray[i] == NULL)//if the object isn't null
		{
			resetArray[i]->reset();//reset the object	
		}

	}

	Serial.begin(PC_USB_BAUD_RATE);
	Serial2.begin(MAIN_BAUD_RATE);
	delay(15);//add a little delay so the serial port has time to start up
	_SERIAL_DEBUG_CHANNEL_.println("Test running");
	
}


void loop() {


	//Counter Delays
	//increment the counters
	modesToggleDelay++;
	

	//Motor Power Control
	if (modesToggleDelay >= 80000)//about once every second
	{

		if (modesTester==1)//if in on mode
		{
			//Turn all lights on
			_SERIAL_DEBUG_CHANNEL_.println("tick");			
			underglowLight->turnOn();
			leftSideSignal->turnOn();
			rightSideSignal->turnOn();
			beaconLightAssy->turnOn(FRONT_LEFT_IR_BEACON, BACK_LEFT_IR_BEACON, BACK_RIGHT_IR_BEACON, FRONT_RIGHT_IR_BEACON, LEFT_BLUE_BEACON, BACK_BLUE_BEACON, RIGHT_BLUE_BEACON, FRONT_BLUE_BEACON);
			leftHeadLightAssy->turnOn(HIGHBEAM_HEADLIGHT, SIGNAL_HEADLIGHT, FOG_HEADLIGHT);
			rightHeadLightAssy->turnOn(HIGHBEAM_HEADLIGHT, SIGNAL_HEADLIGHT, FOG_HEADLIGHT);
			leftTailLightAssy->turnOn(RED1_TAILLIGHT, RED2_TAILLIGHT, RED3_TAILLIGHT, RED4_TAILLIGHT, RED5_TAILLIGHT, WHITE_TAILLIGHT);
			rightTailLightAssy->turnOn(RED1_TAILLIGHT, RED2_TAILLIGHT, RED3_TAILLIGHT, RED4_TAILLIGHT, RED5_TAILLIGHT, WHITE_TAILLIGHT);
			modesTester = 0;//set to the off mode
		}
		else//if in off mode
		{
			//Turn all lights off
			_SERIAL_DEBUG_CHANNEL_.println("tock");
			underglowLight->turnOff();
			leftSideSignal->turnOff();
			rightSideSignal->turnOff();
			beaconLightAssy->turnOff(FRONT_LEFT_IR_BEACON, BACK_LEFT_IR_BEACON, BACK_RIGHT_IR_BEACON, FRONT_RIGHT_IR_BEACON, LEFT_BLUE_BEACON, BACK_BLUE_BEACON, RIGHT_BLUE_BEACON, FRONT_BLUE_BEACON);
			leftHeadLightAssy->turnOff(HIGHBEAM_HEADLIGHT, SIGNAL_HEADLIGHT, FOG_HEADLIGHT);
			rightHeadLightAssy->turnOff(HIGHBEAM_HEADLIGHT, SIGNAL_HEADLIGHT, FOG_HEADLIGHT);
			leftTailLightAssy->turnOff(RED1_TAILLIGHT, RED2_TAILLIGHT, RED3_TAILLIGHT, RED4_TAILLIGHT, RED5_TAILLIGHT, WHITE_TAILLIGHT);
			rightTailLightAssy->turnOff(RED1_TAILLIGHT, RED2_TAILLIGHT, RED3_TAILLIGHT, RED4_TAILLIGHT, RED5_TAILLIGHT, WHITE_TAILLIGHT);
			modesTester = 1;//set to the on mode
		}

		modesToggleDelay = 0;//reset the counter


	}//end if

}
