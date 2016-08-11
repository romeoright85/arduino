#include <PirSensor.h>
#include <RoverPinConfig.h>



void InterruptDispatch1();

//Global Variables
PirSensor pirSensor001 = PirSensor(PIR_PIN, INTRPT_1, &InterruptDispatch1);


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);

}

// the loop function runs over and over again until power down or reset
void loop() {
	String test;

	volatile boolean motionDetected;

	delay(1000);//allow enough delay so after it finishes uploading, the terminal window can be opened



				//test interrupt
	while (1)
	{
		motionDetected = pirSensor001.readSensor();
		if (motionDetected)
		{
			Serial.println("motion detected");
		}
		else
		{
			Serial.println("no motion");
			delay(900);
		}
		delay(100);
	}
}



void InterruptDispatch1() {
	pirSensor001.isrUpdate();
}