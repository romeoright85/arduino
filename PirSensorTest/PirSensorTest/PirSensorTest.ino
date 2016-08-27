#include <PirSensor.h>



void InterruptDispatch1();

//Global Variables
PirSensor pirSensor = PirSensor(PIR_PIN, &InterruptDispatch1);//Note: This is my custom function and not attachInterrupt (though it calls it)
volatile boolean motionDetected;


RoverReset * resetArray[] = { &pirSensor };


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
	
	motionDetected = pirSensor.monitorMotion();

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
	pirSensor.isrUpdate();
}