//Used for AUXI - 2

//Note: Make sure to set the IDE to Mega.

#include <RoverSleeperServer.h>

char rxData;
void InterruptDispatch1();

//Controls the self wakeup of AUXI
RoverSleeperServer sleeperAUXI(AUXI_WAKEUP_CTRL_PIN, &InterruptDispatch1);//AUXI Wakeup Pin Control



RoverReset * resetArray[] = { &sleeperAUXI };


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
	Serial2.begin(AUXI_BAUD_RATE);//Use to talk between MAIN and AUXI

}

void loop()
{


	//MAIN puts AUXI to Sleep or Wakes it up.
	if (Serial2.available() > 0)//Check MAIN to AUXI serial bus
	{

		rxData = Serial2.read();//Get data from the MAIN to AUXI serial bus
		if (rxData == 's')//AUXI sleep
		{
			goToSleepAUXI();

			//The AUXI will go to sleep here.

			wakeUpAUXI();

		}//end if
	}//end if

	if (sleeperAUXI.isAwake())
	{
		Serial.println(F("AUXI is still awake..."));//output to PC for debug
	}
	delay(1000);




}




void InterruptDispatch1() {
	//Have to keep the ISR short else the program won't work
	sleeperAUXI.isrUpdate();//update the awake flag to reflect current status
}


void goToSleepAUXI() {
	//Pre sleep tasks
	Serial.println(F("AUXI sleeping..."));//output to PC for debug
	delay(100);//add some delay to allow the serial print to finish before going to sleep

			   //Go to sleep
			   //Note: Make sure to end any Software Serial here
			   //No SW Serials used for AUXI
	sleeperAUXI.goToSleep();//will sleep and wakeup the MAIN
}
void wakeUpAUXI() {
	//Wake Up
	sleeperAUXI.hasAwoken();
	//Note: Make sure to begin (again) any Software Serial here
	//No SW Serials used for AUXI

	//Post Wake Up tasks
	delay(100);// let everybody get up and running for a sec
	Serial.println(F("AUXI Awoken!"));//output to PC for debug
}