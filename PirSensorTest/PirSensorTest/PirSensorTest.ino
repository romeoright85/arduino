//Used for COMM - 4

#include <PirSensor.h>

void InterruptDispatch1();

//Global Variables
PirSensor pirSensor = PirSensor(PIR_PIN, &InterruptDispatch1);//Note: This is my custom function and not attachInterrupt (though it calls it)
volatile boolean motionDetected;


RoverReset * resetArray[] = { &pirSensor };


void setup() {
	//resetting all objects in this sketch
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		if (!resetArray[i] == NULL)//if the object isn't null
		{
			resetArray[i]->reset();//reset the object	
		}

	}
	Serial.begin(9600);

}

// the loop function runs over and over again until power down or reset
void loop() {
	
	motionDetected = pirSensor.monitorMotion();

	if (motionDetected)
	{
		//motion detected, take action
		Serial.println("motion detected");
		pirSensor.reset();//reset the pir sensor once action is taken
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