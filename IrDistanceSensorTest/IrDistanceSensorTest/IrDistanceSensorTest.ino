//Used for NAVI - 1

#include <IrDistanceSensor.h>


//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast


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

	Serial.begin(PC_USB_BAUD_RATE);
	Serial.begin(MAIN_BAUD_RATE);	
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

			#ifdef _DEBUG_COMM_BROADCAST
				case 0:
					Serial2.print("irDistanceForwardCenter: ");
					break;
				case 1:
					Serial2.print("irDistanceSideRight: ");
					break;
				case 2:
					Serial2.print("irDistanceRearCenter: ");
					break;
				case 3:
					Serial2.print("irDistanceSideLeft: ");
					break;
				}//end switch			
				Serial2.print(distanceMeasured);
				Serial2.println(" cm");
				delay(750);
			}
			Serial2.println();
			#else
				case 0:
					Serial.print("irDistanceForwardCenter: ");
					break;
				case 1:
					Serial.print("irDistanceSideRight: ");
					break;
				case 2:
					Serial.print("irDistanceRearCenter: ");
					break;
				case 3:
					Serial.print("irDistanceSideLeft: ");
					break;
				}//end switch			
				Serial.print(distanceMeasured);
				Serial.println(" cm");
				delay(750);
			}
			Serial.println();
		#endif


		delay(1000);
	}//end for
}
