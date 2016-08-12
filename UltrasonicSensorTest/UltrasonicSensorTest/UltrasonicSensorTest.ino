#include <UltrasonicSensor.h>

//Global Variables


UltrasonicSensor uSon_FwdLeft = UltrasonicSensor(FORWARD_LEFT_ULTSNC_TRIG_PIN, FORWARD_LEFT_ULTSNC_ECHO_PIN);
UltrasonicSensor uSon_FwdCenter = UltrasonicSensor(FORWARD_CENTER_ULTSNC_TRIG_PIN, FORWARD_CENTER_ULTSNC_ECHO_PIN);
UltrasonicSensor uSon_FwdRight = UltrasonicSensor(FORWARD_RIGHT_ULTSNC_TRIG_PIN, FORWARD_RIGHT_ULTSNC_ECHO_PIN);
UltrasonicSensor uSon_SideRight = UltrasonicSensor(SIDE_RIGHT_ULTSNC_TRIG_PIN, SIDE_RIGHT_ULTSNC_ECHO_PIN);
UltrasonicSensor uSon_RearCenter = UltrasonicSensor(REAR_CENTER_ULTSNC_TRIG_PIN, REAR_CENTER_ULTSNC_ECHO_PIN);
UltrasonicSensor uSon_SideLeft = UltrasonicSensor(SIDE_LEFT_ULTSNC_TRIG_PIN, SIDE_LEFT_ULTSNC_ECHO_PIN);


int distanceOfUSon;

UltrasonicSensor uSonSensorArray[6] =
{
	uSon_FwdLeft,
	uSon_FwdCenter,
	uSon_FwdRight,
	uSon_SideRight,
	uSon_RearCenter,
	uSon_SideLeft
};


void setup()
{

	Serial.begin(9600);

}

void loop()
{


		
	for (byte i = 0; i <= 5; i++)
	{
		switch (i)
		{
			case 0:
				Serial.print("uSon_FwdLeft: ");
				break;
			case 1:
				Serial.print("uSon_FwdCenter: ");
				break;
			case 2:
				Serial.print("uSon_FwdRight: ");
				break;
			case 3:
				Serial.print("uSon_SideRight: ");
				break;
			case 4:
				Serial.print("uSon_RearCenter: ");
				break;
			case 5:
				Serial.print("uSon_SideLeft: ");
				break;
		}
		distanceOfUSon = uSonSensorArray[i].readSensor(UNIT_CM);
		Serial.print(distanceOfUSon);
		Serial.println(" cm");
		delay(1000);
	}//end for
	
		
}
