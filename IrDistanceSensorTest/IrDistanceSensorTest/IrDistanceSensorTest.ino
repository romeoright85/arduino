#include <IrDistanceSensor.h>


//Global Variables
IrDistanceSensor irDistanceSideLeft = IrDistanceSensor(SIDE_LEFT_IR_DIST_SENSOR_PIN);
IrDistanceSensor irDistanceSideRight = IrDistanceSensor(SIDE_RIGHT_IR_DIST_SENSOR_PIN);
IrDistanceSensor irDistanceRearCenter = IrDistanceSensor(REAR_CENTER_IR_DIST_SENSOR_PIN);
IrDistanceSensor irDistanceForwardCenter = IrDistanceSensor(FORWARD_CENTER_IR_DIST_SENSOR_PIN);

int distanceMeasured;

IrDistanceSensor * irDistanceSensors[4] =
{
	&irDistanceSideLeft,
	&irDistanceSideRight,
	&irDistanceRearCenter,
	&irDistanceForwardCenter
};



RoverReset * resetArray[] = { &irDistanceSideLeft , &irDistanceSideRight, &irDistanceRearCenter, &irDistanceForwardCenter };



void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}

	Serial.begin(9600);
}

// the loop function runs over and over again until power down or reset
void loop() {


	for (byte i = 0; i <= 3; i++)
	{
		switch (i)
		{
		case 0:
			Serial.print("irDistanceSideLeft: ");
			break;
		case 1:
			Serial.print("irDistanceSideRight: ");
			break;
		case 2:
			Serial.print("irDistanceRearCenter: ");
			break;
		case 3:
			Serial.print("irDistanceForwardCenter: ");
			break;
		}//end switch
		distanceMeasured = irDistanceSensors[i]->getDistance(UNIT_CM);
		Serial.print(distanceMeasured);
		Serial.println(" cm");
		delay(1000);
	}//end for
}
