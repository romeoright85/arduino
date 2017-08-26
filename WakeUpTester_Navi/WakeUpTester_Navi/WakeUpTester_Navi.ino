//Used for NAVI - 1

//Note: Since all the Arduinos use this class, you have to define them in each of it's .ino as there are shared naming conventions and will cause a conflict otherwise.



//uncomment below to use PC to simulate the COMM Arduino and be able to send sleep commands to NAVI
//#define _DEBUG_W_PC_INPUT
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast
	//Note: The COMM Broadcast only works if _DEBUG_W_PC_INPUT is commented out
	
#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ _MAIN_SERIAL_
#else
	#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_
#endif

//Also see the debug flag _DEBUG_STAY_AWAKE in RoverSleeperServer.h




/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/
			
//define Arduino 2: NAVI in order to use it's config pins
#ifndef _ARD_1_NAVI_H
	#define _ARD_1_NAVI_H		
#endif
	
/********************************************************************/

#include <RoverConfig.h>


//Note: Make sure to set the IDE to Mega.

#include <RoverSleeperServer.h>

char rxData;
void InterruptDispatch1();

//Controls the self wakeup of NAVI
RoverSleeperServer * sleeperNAVI = new RoverSleeperServer(NAVI_WAKEUP_CTRL_PIN, &InterruptDispatch1);//NAVI Wakeup Pin Control

//Holds all custom objects created by this sketch
RoverReset * resetArray[] = { 
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
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);//Used to talk to the computer, for debugging 
	_MAIN_SERIAL_.begin(MAIN_BAUD_RATE);//Use to talk between MAIN and NAVI

}

void loop()
{


	//MAIN puts NAVI to Sleep or Wakes it up.
#ifdef _DEBUG_W_PC_INPUT	
	if (_PC_USB_SERIAL_.available() > 0)//Check MAIN to NAVI serial bus
#else	
	if (_MAIN_SERIAL_.available() > 0)//Check MAIN to NAVI serial bus
#endif	
	{
	
	#ifdef _DEBUG_W_PC_INPUT
		rxData = _PC_USB_SERIAL_.read();//Get data from the MAIN to NAVI serial bus
	#else
		rxData = _MAIN_SERIAL_.read();//Get data from the MAIN to NAVI serial bus
	#endif
		
		if (rxData == 's')//NAVI sleep
		{
			goToSleepNAVI();

			//The NAVI will go to sleep here.

			wakeUpNAVI();

		}//end if
	}//end if

	if (sleeperNAVI->isAwake())
	{
		_SERIAL_DEBUG_CHANNEL_.println(F("NAVI is still awake..."));//output to PC for debug
	}
	delay(1000);




}




void InterruptDispatch1() {
	//Have to keep the ISR short else the program won't work
	sleeperNAVI->isrUpdate();//update the awake flag to reflect current status
}


void goToSleepNAVI() {
	//Pre sleep tasks
	_SERIAL_DEBUG_CHANNEL_.println(F("NAVI sleeping..."));//output to PC for debug
	delay(100);//add some delay to allow the serial print to finish before going to sleep

			   //Go to sleep
			   //Note: Make sure to end any Software Serial here
			   //No SW Serials used for NAVI
	sleeperNAVI->goToSleep();//will sleep and can be awoken by MAIN
}
void wakeUpNAVI() {
	//Wake Up
	sleeperNAVI->hasAwoken();
	//Note: Make sure to begin (again) any Software Serial here
	//No SW Serials used for NAVI

	//Post Wake Up tasks
	delay(100);// let everybody get up and running for a sec
	_SERIAL_DEBUG_CHANNEL_.println(F("NAVI Awoken!"));//output to PC for debug
	
}