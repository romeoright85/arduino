//Note: Make sure to set the IDE to Mega.

#include <RoverSleeperServer.h>
#include <RoverSleeperClient.h>

char rxData;
void InterruptDispatch1();

//Controls the self wakeup of MAIN
RoverSleeperServer sleeperMAIN(MAIN_WAKEUP_CTRL_PIN, &InterruptDispatch1);//MAIN Wakeup Pin Control
RoverSleeperClient sleeperAUXI(AUXI_WAKEUP_CTRL_PIN);
RoverSleeperClient sleeperNAVI(NAVI_WAKEUP_CTRL_PIN);



//Holds all custom objects created by this sketch

RoverReset * resetArray[] = { &sleeperMAIN , &sleeperAUXI, &sleeperNAVI };


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}

	Serial.begin(PC_USB_BAUD_RATE);//Used to talk to the computer, for debugging 
	Serial1.begin(COMM_BAUD_RATE);//Use to talk between COMM and MAIN
	Serial2.begin(NAVI_BAUD_RATE);//Use to talk between MAIN and NAVI
	Serial3.begin(AUXI_BAUD_RATE);//Use to talk between MAIN and AUXI
	
}

void loop()
{


	//COMM puts MAIN to Sleep or Wakes it up. When MAIN goes to sleep it also sends a command for AUXI and NAVI to sleep as well.
	if (Serial1.available() > 0)//Check COMM to MAIN serial bus
	{
		
		rxData = Serial1.read();//Get data from the COMM to MAIN serial bus
		if (rxData == 's')//AUXI, NAVI, MAIN sleep
		{
			goToSleepAUXI();
			//The AUXI will go to sleep here.

			goToSleepNAVI();
			//The NAVI will go to sleep here.

			goToSleepMAIN();
			//The MAIN will go to sleep here. Then it will resume below once it's awoken.

			wakeUpMAIN();

			wakeUpNAVI();

			wakeUpAUXI();

		}//end if
	}//end if

	if (sleeperMAIN.isAwake())
	{
		Serial.println(F("MAIN is still awake..."));//output to PC for debug
	}
	delay(1000);




}




void InterruptDispatch1() {
	//Have to keep the ISR short else the program won't work
	sleeperMAIN.isrUpdate();//update the awake flag to reflect current status
}


void goToSleepMAIN() {
	//Pre sleep tasks
	Serial.println(F("MAIN sleeping..."));//output to PC for debug
	delay(100);//add some delay to allow the serial print to finish before going to sleep

	//Go to sleep
	//Note: Make sure to end any Software Serial here
	//No SW Serials used for MAIN
	sleeperMAIN.goToSleep();//will sleep and wakeup the MAIN
}
void wakeUpMAIN() {
	//Wake Up
	sleeperMAIN.hasAwoken();
	//Note: Make sure to begin (again) any Software Serial here
	//No SW Serials used for MAIN

	//Post Wake Up tasks
	delay(100);// let everybody get up and running for a sec
	Serial.println(F("MAIN Awoken!"));//output to PC for debug
}


void goToSleepNAVI() {
	//Pre sleep tasks
	Serial.println(F("NAVI Sleeping..."));//output to PC for debug

	//Go to sleep
	//Note: Don't forget to call this before sending the command, else the status won't be up to date
	sleeperNAVI.goToSleep();//update awake flag status
	//Send command over software serial to shutdown the NAVI
	Serial2.println('s');//send 's' to the NAVI over NAVI's dedicated serial bus

}
void wakeUpNAVI() {

	if (!sleeperNAVI.isAwake())
	{
		//Wake Up
		sleeperNAVI.wakeUp();//Creates a rising edge on the interrupt pin to wake up NAVI

		//Post Wake Up tasks
		Serial.println(F("NAVI Awoken!"));//output to PC for debug
	}
	else
	{
		Serial.println(F("NAVI already awoken."));//output to PC for debug
	}

}


void goToSleepAUXI() {
	//Pre sleep tasks
	Serial.println(F("AUXI Sleeping..."));//output to PC for debug

	//Go to sleep
	//Note: Don't forget to call this before sending the command, else the status won't be up to date
	sleeperAUXI.goToSleep();//update awake flag status
	//Send command over software serial to shutdown the AUXI
	Serial3.println('s');//send 's' to the AUXI over AUXI's dedicated serial bus

}
void wakeUpAUXI() {

	if (!sleeperAUXI.isAwake())
	{
		//Wake Up
		sleeperAUXI.wakeUp();//Creates a rising edge on the interrupt pin to wake up AUXI

		//Post Wake Up tasks
		Serial.println(F("AUXI Awoken!"));//output to PC for debug
	}
	else
	{
		Serial.println(F("AUXI already awoken."));//output to PC for debug
	}

}