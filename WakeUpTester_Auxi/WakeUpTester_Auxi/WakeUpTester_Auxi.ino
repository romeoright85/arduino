//Used for AUXI - 2



//Note: Since all the Arduinos use this class, you have to define them in each of its .ino as there are shared naming conventions and will cause a conflict otherwise.


//uncomment below to use PC to simulate the COMM Arduino and be able to send sleep commands to AUXI
//#define _DEBUG_W_PC_INPUT
//Also see the debug flag _DEBUG_STAY_AWAKE in RoverSleeperServer.h

//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast

#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ Serial2
#else
	#define _SERIAL_DEBUG_CHANNEL_ Serial
#endif


/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/
			
//define Arduino 1: AUXI in order to use it's config pins
#ifndef _ARD_2_AUXI_H
	#define _ARD_2_AUXI_H		
#endif
	
/********************************************************************/

#include <RoverConfig.h>





//Note: Make sure to set the IDE to Mega.

#include <RoverSleeperServer.h>

char rxData;
void InterruptDispatch1();

//Controls the self wakeup of AUXI
RoverSleeperServer * sleeperAUXI = new RoverSleeperServer(AUXI_WAKEUP_CTRL_PIN, &InterruptDispatch1);//AUXI Wakeup Pin Control



RoverReset * resetArray[] = { 
	sleeperAUXI
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
	Serial2.begin(MAIN_BAUD_RATE);//Use to talk between MAIN and AUXI

}

void loop()
{


	//MAIN puts AUXI to Sleep or Wakes it up.
#ifdef _DEBUG_W_PC_INPUT
	if (Serial.available() > 0)//Check MAIN to AUXI serial bus
#else	
	if (Serial2.available() > 0)//Check MAIN to AUXI serial bus	
#endif
	{
		#ifdef _DEBUG_W_PC_INPUT
			rxData = Serial.read();//Get data from the MAIN to AUXI serial bus
		#else		
			rxData = Serial2.read();//Get data from the MAIN to AUXI serial bus
		#endif				
		
		if (rxData == 's')//AUXI sleep
		{
			goToSleepAUXI();

			//The AUXI will go to sleep here.

			wakeUpAUXI();

		}//end if
	}//end if

	if (sleeperAUXI->isAwake())
	{
		_SERIAL_DEBUG_CHANNEL_.println(F("AUXI is still awake..."));//output to PC for debug
	}
	delay(1000);




}




void InterruptDispatch1() {
	//Have to keep the ISR short else the program won't work
	sleeperAUXI->isrUpdate();//update the awake flag to reflect current status
}


void goToSleepAUXI() {
	//Pre sleep tasks
	_SERIAL_DEBUG_CHANNEL_.println(F("AUXI sleeping..."));//output to PC for debug
	delay(100);//add some delay to allow the serial print to finish before going to sleep

			   //Go to sleep
			   //Note: Make sure to end any Software Serial here
			   //No SW Serials used for AUXI
	sleeperAUXI->goToSleep();//will sleep and can be awoken by MAIN
}
void wakeUpAUXI() {
	//Wake Up
	sleeperAUXI->hasAwoken();
	//Note: Make sure to begin (again) any Software Serial here
	//No SW Serials used for AUXI

	//Post Wake Up tasks
	delay(100);// let everybody get up and running for a sec
	_SERIAL_DEBUG_CHANNEL_.println(F("AUXI Awoken!"));//output to PC for debug	
}