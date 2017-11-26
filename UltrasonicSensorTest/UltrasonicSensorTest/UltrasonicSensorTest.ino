//Used for NAVI - 1

#include <UltrasonicSensor.h>

//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast
#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ _MAIN_SERIAL_ //When using COMM Broadcast, reroute the PC USB output to the channel to MAIN instead
#else
	#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_
#endif


//Global Variables
UltrasonicSensor * uSon_FwdLeft = new UltrasonicSensor(FORWARD_LEFT_ULTSNC_TRIG_PIN, FORWARD_LEFT_ULTSNC_ECHO_PIN);
UltrasonicSensor * uSon_FwdCenter = new UltrasonicSensor(FORWARD_CENTER_ULTSNC_TRIG_PIN, FORWARD_CENTER_ULTSNC_ECHO_PIN);
UltrasonicSensor * uSon_FwdRight = new UltrasonicSensor(FORWARD_RIGHT_ULTSNC_TRIG_PIN, FORWARD_RIGHT_ULTSNC_ECHO_PIN);
UltrasonicSensor * uSon_SideRight = new UltrasonicSensor(SIDE_RIGHT_ULTSNC_TRIG_PIN, SIDE_RIGHT_ULTSNC_ECHO_PIN);
UltrasonicSensor * uSon_RearCenter = new UltrasonicSensor(REAR_CENTER_ULTSNC_TRIG_PIN, REAR_CENTER_ULTSNC_ECHO_PIN);
UltrasonicSensor * uSon_SideLeft = new UltrasonicSensor(SIDE_LEFT_ULTSNC_TRIG_PIN, SIDE_LEFT_ULTSNC_ECHO_PIN);


int distanceMeasured;

//Alternate the ultrasonics to prevent interference
UltrasonicSensor * uSonSensors[6] =
{
	uSon_FwdLeft,
	uSon_SideRight,
	uSon_FwdCenter,
	uSon_RearCenter,
	uSon_FwdRight,
	uSon_SideLeft
};



RoverReset * resetArray[] = { 
	uSon_FwdLeft, 
	uSon_FwdCenter, 
	uSon_FwdRight, 
	uSon_SideRight,
	uSon_RearCenter, 
	uSon_SideLeft
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

}

void loop()
{

		
	for (byte i = 0; i <= 5; i++)
	{
		for (byte j = 0; j < 4; j++)
		{
			distanceMeasured = uSonSensors[i]->getDistance(UNIT_CM);
			
			switch (i)
			{
				case 0:
					_SERIAL_DEBUG_CHANNEL_.print("uSon_FwdLeft: ");
					break;
				case 1:
					_SERIAL_DEBUG_CHANNEL_.print("uSon_SideRight: ");
					break;
				case 2:
					_SERIAL_DEBUG_CHANNEL_.print("uSon_FwdCenter: ");
					break;
				case 3:
					_SERIAL_DEBUG_CHANNEL_.print("uSon_RearCenter: ");
					break;
				case 4:
					_SERIAL_DEBUG_CHANNEL_.print("uSon_FwdRight: ");
					break;
				case 5:
					_SERIAL_DEBUG_CHANNEL_.print("uSon_SideLeft: ");
					break;
			}//end switch
			 //if objects are detected...
			if (distanceMeasured >= 0)
			{
				_SERIAL_DEBUG_CHANNEL_.print(distanceMeasured);
				_SERIAL_DEBUG_CHANNEL_.println(" cm");
			}//end if
			else//no objects detected...
			{
				_SERIAL_DEBUG_CHANNEL_.println(F("No Object Detected"));
			}//end else
			delay(1000);
		}//end for
	}//end for
	
		
}//end loop

