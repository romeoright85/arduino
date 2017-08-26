//Used for NAVI - 1

#include <IrDistanceSensor.h>


//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast
#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ _MAIN_SERIAL_
#else
	#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_
#endif

//Global Variables
IrDistanceSensor * irDistanceForwardCenter = new  IrDistanceSensor(FORWARD_CENTER_IR_DIST_SENSOR_PIN);
IrDistanceSensor * irDistanceSideRight = new  IrDistanceSensor(SIDE_RIGHT_IR_DIST_SENSOR_PIN);
IrDistanceSensor * irDistanceRearCenter = new  IrDistanceSensor(REAR_CENTER_IR_DIST_SENSOR_PIN);
IrDistanceSensor * irDistanceSideLeft = new IrDistanceSensor(SIDE_LEFT_IR_DIST_SENSOR_PIN);

int distanceMeasured;

IrDistanceSensor * irDistanceSensors[4] =
{
	irDistanceForwardCenter,
	irDistanceSideRight,
	irDistanceRearCenter,
	irDistanceSideLeft	
};



RoverReset * resetArray[] = { 
	irDistanceForwardCenter,
	irDistanceSideRight,
	irDistanceRearCenter, 
	irDistanceSideLeft
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

	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	_MAIN_SERIAL_.begin(MAIN_BAUD_RATE);	
}

// the loop function runs over and over again until power down or reset
void loop() {


	for (byte i = 0; i <= 3; i++)
	{
		for (byte j = 0; j < 5; j++)
		{
			
			distanceMeasured = irDistanceSensors[i]->getDistance(UNIT_CM);

			switch (i)
			{
				case 0:
					_SERIAL_DEBUG_CHANNEL_.print("irDistanceForwardCenter: ");
					break;
				case 1:
					_SERIAL_DEBUG_CHANNEL_.print("irDistanceSideRight: ");
					break;
				case 2:
					_SERIAL_DEBUG_CHANNEL_.print("irDistanceRearCenter: ");
					break;
				case 3:
					_SERIAL_DEBUG_CHANNEL_.print("irDistanceSideLeft: ");
					break;
				}//end switch			
				_SERIAL_DEBUG_CHANNEL_.print(distanceMeasured);
				_SERIAL_DEBUG_CHANNEL_.println(" cm");
				delay(750);
			}
			_SERIAL_DEBUG_CHANNEL_.println();
		


		delay(1000);
	}//end for
}
