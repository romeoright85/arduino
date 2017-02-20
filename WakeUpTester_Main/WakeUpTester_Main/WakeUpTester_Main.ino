//Used for MAIN - 3

//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast
//Note: Should be used with _DEBUG_W_PC_INPUT commented out

//Note: Since all the Arduinos use this class, you have to define them in each of its .ino as there are shared naming conventions and will cause a conflict otherwise.

//Uncomment below to use PC to simulate the COMM Arduino and be able to send sleep commands to MAIN
//#define _DEBUG_W_PC_INPUT
//Also see the debug flag _DEBUG_STAY_AWAKE in RoverSleeperServer.h


/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/
				
//define Arduino 3: MAIN in order to use it's config pins
#ifndef _ARD_3_MAIN_H
	#define _ARD_3_MAIN_H		
#endif
	

/********************************************************************/

#include <RoverConfig.h>





//Note: Make sure to set the IDE to Mega.

#include <RoverSleeperServer.h>
#include <RoverSleeperClient.h>

char rxData;
void InterruptDispatch1();

//Controls the self wakeup of MAIN
RoverSleeperServer * sleeperMAIN = new RoverSleeperServer(MAIN_WAKEUP_CTRL_PIN, &InterruptDispatch1);//MAIN Wakeup Pin Control
RoverSleeperClient * sleeperAUXI = new RoverSleeperClient(AUXI_WAKEUP_CTRL_PIN);
RoverSleeperClient * sleeperNAVI = new RoverSleeperClient(NAVI_WAKEUP_CTRL_PIN);




//Holds all custom objects created by this sketch

RoverReset * resetArray[] = { 
	sleeperMAIN, 
	sleeperAUXI, 
	sleeperNAVI
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

	Serial.begin(PC_USB_BAUD_RATE);//Used to talk to the computer, for debugging 
	Serial1.begin(MAIN_BAUD_RATE);//Use to talk between COMM and MAIN
	Serial2.begin(NAVI_BAUD_RATE);//Use to talk between MAIN and NAVI
	Serial3.begin(AUXI_BAUD_RATE);//Use to talk between MAIN and AUXI
	
}

void loop()
{


	//COMM puts MAIN to Sleep or Wakes it up. When MAIN goes to sleep it also sends a command for AUXI and NAVI to sleep as well.
#ifdef _DEBUG_W_PC_INPUT
	if (Serial.available() > 0)//Check COMM to MAIN serial bus
#else
	if (Serial1.available() > 0)//Check COMM to MAIN serial bus
#endif
	{
		#ifdef _DEBUG_W_PC_INPUT
			rxData = Serial.read();//Get data from the PC to MAIN serial bus
		#else
			rxData = Serial1.read();//Get data from the COMM to MAIN serial bus
		#endif
		
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
		#ifdef _DEBUG_COMM_BROADCAST
			Serial1.println(F("All Megas Now Awake"));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
		#else
			Serial.println(F("All Megas Now Awake"));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
		#endif

		
		}//end if
	}//end if

	if (sleeperMAIN->isAwake())
	{
#ifdef _DEBUG_COMM_BROADCAST
		Serial1.println(F("MAIN is still awake..."));//output to PC for debug
#else
		Serial.println(F("MAIN is still awake..."));//output to PC for debug
#endif		
	}
	delay(1000);




}




void InterruptDispatch1() {
	//Have to keep the ISR short else the program won't work
	sleeperMAIN->isrUpdate();//update the awake flag to reflect current status
}


void goToSleepMAIN() {
	//Pre sleep tasks
#ifdef _DEBUG_COMM_BROADCAST
	Serial1.println(F("MAIN Sleeping..."));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
#else
	Serial.println(F("MAIN Sleeping..."));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
#endif	
	delay(100);//add some delay to allow the serial print to finish before going to sleep

	//Go to sleep
	//Note: Make sure to end any Software Serial here
	//No SW Serials used for MAIN
	sleeperMAIN->goToSleep();//will sleep and wakeup the MAIN
//sleeperMAIN->goToSleep(&InterruptDispatch1);//DEBUG
	
}
void wakeUpMAIN() {
	//Wake Up
	sleeperMAIN->hasAwoken();
	//Note: Make sure to begin (again) any Software Serial here
	//No SW Serials used for MAIN

	//Post Wake Up tasks
	delay(100);// let everybody get up and running for a sec
#ifdef _DEBUG_COMM_BROADCAST
	Serial1.println(F("MAIN Awoken!"));//output to PC for debug
#else
	Serial.println(F("MAIN Awoken!"));//output to PC for debug
#endif	
	
}


void goToSleepNAVI() {
	//Pre sleep tasks	
#ifdef _DEBUG_COMM_BROADCAST
	Serial1.println(F("NAVI Sleeping..."));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
#else
	Serial.println(F("NAVI Sleeping..."));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
#endif
	//Go to sleep
	//Note: Don't forget to call this before sending the command, else the status won't be up to date
	sleeperNAVI->goToSleep();//update awake flag status
	//Send command over software serial to shutdown the NAVI
	Serial2.println('s');//send 's' to the NAVI over NAVI's dedicated serial bus

}
void wakeUpNAVI() {

	if (!sleeperNAVI->isAwake())
	{
		//Wake Up
		sleeperNAVI->wakeUp();//Creates a rising edge on the interrupt pin to wake up NAVI

		//Post Wake Up tasks
#ifdef _DEBUG_COMM_BROADCAST
		Serial1.println(F("NAVI Awoken!"));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
#else
		Serial.println(F("NAVI Awoken!"));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
#endif		
	}
	else
	{
#ifdef _DEBUG_COMM_BROADCAST
		Serial1.println(F("NAVI already awoken."));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
#else
		Serial.println(F("NAVI already awoken."));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
#endif		
	}

}


void goToSleepAUXI() {
	//Pre sleep tasks
#ifdef _DEBUG_COMM_BROADCAST
	Serial1.println(F("AUXI Sleeping..."));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
#else
	Serial.println(F("AUXI Sleeping..."));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
#endif
	//Go to sleep
	//Note: Don't forget to call this before sending the command, else the status won't be up to date
	sleeperAUXI->goToSleep();//update awake flag status
	//Send command over software serial to shutdown the AUXI
	Serial3.println('s');//send 's' to the AUXI over AUXI's dedicated serial bus

}
void wakeUpAUXI() {

	if (!sleeperAUXI->isAwake())
	{
		//Wake Up
		sleeperAUXI->wakeUp();//Creates a rising edge on the interrupt pin to wake up AUXI

		//Post Wake Up tasks
#ifdef _DEBUG_COMM_BROADCAST
		Serial1.println(F("AUXI Awoken!"));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
#else
		Serial.println(F("AUXI Awoken!"));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
#endif		
	}
	else
	{
#ifdef _DEBUG_COMM_BROADCAST
		Serial1.println(F("AUXI already awoken."));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
#else
		Serial.println(F("AUXI already awoken."));//output to PC for debug, this is actually open loop feedback. In reality, it may still be sleeping.
#endif		
	}

}