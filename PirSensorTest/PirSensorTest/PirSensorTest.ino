#include <PirSensor.h>



void InterruptDispatch1();

//Global Variables
PirSensor pirSensor001 = PirSensor(PIR_PIN, &InterruptDispatch1);//Note: This is my custom function and not attachInterrupt (though it calls it)
volatile boolean motionDetected;

																 // the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);

}

// the loop function runs over and over again until power down or reset
void loop() {
	
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



void InterruptDispatch1() {
	pirSensor001.isrUpdate();
}