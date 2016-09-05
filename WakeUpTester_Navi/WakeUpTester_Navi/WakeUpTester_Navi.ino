//Note: Make sure to set the IDE to Mega.

#include <RoverSleeperServer.h>

char rxData;
void InterruptDispatch1();

//Controls the self wakeup of NAVI
RoverSleeperServer sleeperNAVI(NAVI_WAKEUP_CTRL_PIN, &InterruptDispatch1);//NAVI Wakeup Pin Control

//Holds all custom objects created by this sketch
RoverReset * resetArray[] = { &sleeperNAVI };


void setup() {
	//resetting all objects in this sketch
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		if (!resetArray[i] == NULL)//if the object isn't null
		{
			resetArray[i]->reset();//reset the object	
		}

	}
	Serial.begin(PC_USB_BAUD_RATE);//Used to talk to the computer, for debugging 
	Serial2.begin(NAVI_BAUD_RATE);//Use to talk between MAIN and NAVI

}

void loop()
{


	//MAIN puts NAVI to Sleep or Wakes it up.
	if (Serial2.available() > 0)//Check MAIN to NAVI serial bus
	{

		rxData = Serial2.read();//Get data from the MAIN to NAVI serial bus
		if (rxData == 's')//NAVI sleep
		{
			goToSleepNAVI();

			//The NAVI will go to sleep here.

			wakeUpNAVI();

		}//end if
	}//end if

	if (sleeperNAVI.isAwake())
	{
		Serial.println(F("NAVI is still awake..."));//output to PC for debug
	}
	delay(1000);




}




void InterruptDispatch1() {
	//Have to keep the ISR short else the program won't work
	sleeperNAVI.isrUpdate();//update the awake flag to reflect current status
}


void goToSleepNAVI() {
	//Pre sleep tasks
	Serial.println(F("NAVI sleeping..."));//output to PC for debug
	delay(100);//add some delay to allow the serial print to finish before going to sleep

			   //Go to sleep
			   //Note: Make sure to end any Software Serial here
			   //No SW Serials used for NAVI
	sleeperNAVI.goToSleep();//will sleep and wakeup the MAIN
}
void wakeUpNAVI() {
	//Wake Up
	sleeperNAVI.hasAwoken();
	//Note: Make sure to begin (again) any Software Serial here
	//No SW Serials used for NAVI

	//Post Wake Up tasks
	delay(100);// let everybody get up and running for a sec
	Serial.println(F("NAVI Awoken!"));//output to PC for debug
}