//Used for AUXI - 2

#include <LaserControl.h>


//Written for the AUXI
//Note: The timing isn't perfect but as long as the lasers are toggling on/off, that's all that matters.

//Global Variables


//uncomment to show debug comments
//#define _DEBUG_
//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast
#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ Serial2
#else
	#define _SERIAL_DEBUG_CHANNEL_ Serial
#endif


//counter delays
//using a counter to create delays while still allowing the loop() to run (i.e. for messages, etc.)
unsigned int outputMessageDelay = 0;
unsigned int laserControlDelay = 0;

boolean leftLaserOn = false;
boolean rightLaserOn = false;




LaserControl * leftSidelaser = new LaserControl(LEFT_LASER_CTRL_PIN);
LaserControl * rightSidelaser = new LaserControl(RIGHT_LASER_CTRL_PIN);

RoverReset * resetArray[] = {
	leftSidelaser,
	rightSidelaser
};

void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	Serial.begin(PC_USB_BAUD_RATE);
	Serial2.begin(MAIN_BAUD_RATE);	
}


void loop() {



	//Counter Delays
	//increment the counters
	outputMessageDelay++;
	laserControlDelay++;


	if(laserControlDelay >= 40000)
	{
		//turn off right laser

		rightSidelaser->laserEnable(LASER_OFF);
		laserControlDelay = 0;//reset counter
	}
	else if (laserControlDelay >= 30000)
	{
		
		//turn on right laser
		rightSidelaser->laserEnable(LASER_ON);
	}
	else if (laserControlDelay >= 20000)
	{
		
		//turn off left laser
		leftSidelaser->laserEnable(LASER_OFF);
	}
	else//laserControlDelay < 20000
	{
		
		//turn on left laser
		leftSidelaser->laserEnable(LASER_ON);		
	}
	
	

	if (outputMessageDelay >= 20000)
	{
		//Right Laser
		if (rightSidelaser->isLaserOn())//right laser is on
		{
			if (!rightLaserOn)//if the right laser was off and now just turned on
			{
				#ifdef _DEBUG_					
						_SERIAL_DEBUG_CHANNEL_.println(laserControlDelay);//DEBUG									
				#endif					
				_SERIAL_DEBUG_CHANNEL_.println(F("RIGHT LASER ON"));//print message on the first toggle
				_SERIAL_DEBUG_CHANNEL_.println();					
				rightLaserOn = true;//set status
			}
			else//the right laser had already been on
			{
				//do nothing
			}
		}
		else
		{
			if (rightLaserOn)//if the right laser was on and now just turned off
			{
				#ifdef _DEBUG_					
					_SERIAL_DEBUG_CHANNEL_.println(laserControlDelay);//DEBUG	
				#endif				
				_SERIAL_DEBUG_CHANNEL_.println(F("RIGHT LASER OFF"));
				_SERIAL_DEBUG_CHANNEL_.println();				
				rightLaserOn = false;//set status
			}
			else//the right laser had already been off
			{
				//do nothing
			}		
		}

		//Left Laser
		if (leftSidelaser->isLaserOn())//left laser is on
		{
			if (!leftLaserOn)//if the left laser was off and now just turned on
			{
				#ifdef _DEBUG_
					_SERIAL_DEBUG_CHANNEL_.println(laserControlDelay);//DEBUG
				#endif
				_SERIAL_DEBUG_CHANNEL_.println(F("LEFT LASER ON"));//print message on the first toggle
				_SERIAL_DEBUG_CHANNEL_.println();
				leftLaserOn = true;//set status
			}
			else//the left laser had already been on
			{
				//do nothing
			}
		}
		else
		{
			if (leftLaserOn)//if the left laser was on and now just turned off
			{
				#ifdef _DEBUG_
					_SERIAL_DEBUG_CHANNEL_.println(laserControlDelay);//DEBUG
				#endif
				_SERIAL_DEBUG_CHANNEL_.println(F("LEFT LASER OFF"));
				_SERIAL_DEBUG_CHANNEL_.println();
				leftLaserOn = false;//set status
			}
			else//the left laser had already been off
			{
				//do nothing
			}
		}
	}
}
