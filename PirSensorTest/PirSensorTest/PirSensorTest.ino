//Used for COMM - 4

#include <PirSensor.h>

void InterruptDispatch1();

//Global Variables
PirSensor * pirSensor = new PirSensor(PIR_PIN, &InterruptDispatch1);//Note: This is my custom function and not attachInterrupt (though it calls it)
volatile boolean motionDetected;


RoverReset * resetArray[] = { 
	pirSensor
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

}

// the loop function runs over and over again until power down or reset
void loop() {
	



	if (pirSensor->monitorMotion())
	{
		//motion detected, take action
		Serial.println("motion detected");
		
	}
	else
	{
		Serial.println("no motion");
	}
	pirSensor->reset();//reset the pir sensor once samples are processed
	delay(250);
	


}



void InterruptDispatch1() {
	pirSensor->isrUpdate();
}