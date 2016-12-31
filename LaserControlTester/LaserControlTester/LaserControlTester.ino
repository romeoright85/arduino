//Used for AUXI - 2

#include <LaserControl.h>

//Written for the AUXI
//Note: The timing isn't perfect but as long as the lasers are toggling on/off, that's all that matters.

//Global Variables


//uncomment to show debug comments
//#define _DEBUG_

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
	Serial.begin(9600);
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
					Serial.println(laserControlDelay);//DEBUG
				#endif
				
				Serial.println(F("RIGHT LASER ON"));//print message on the first toggle
				Serial.println();
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
					Serial.println(laserControlDelay);//DEBUG
				#endif

				Serial.println(F("RIGHT LASER OFF"));
				Serial.println();
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
					Serial.println(laserControlDelay);//DEBUG
				#endif
				Serial.println(F("LEFT LASER ON"));//print message on the first toggle
				Serial.println();
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
					Serial.println(laserControlDelay);//DEBUG
				#endif
				Serial.println(F("LEFT LASER OFF"));
				Serial.println();
				leftLaserOn = false;//set status
			}
			else//the left laser had already been off
			{
				//do nothing
			}
		}
	}



	



}
