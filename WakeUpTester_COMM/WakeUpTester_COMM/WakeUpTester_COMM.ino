//Used for COMM - 4

//Note: Make sure to set the IDE to UNO.

#include <SoftwareSerial.h>
#include <RoverSleeperServer.h>
#include <RoverSleeperClient.h>


/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/
			
//define Arduino 4: COMM in order to use it's config pins
#ifndef _ARD_4_COMM_H
#define _ARD_4_COMM_H		
#endif
	
/********************************************************************/


#include <RoverConfig.h>

char rxData;
void InterruptDispatch1();


/*
Connections:
COMM Pin to MAIN Pin (signal)
4  -> 2 (MAIN_WAKEUP_CTRL_PIN)
12 -> 18 (COMM RX to MAIN TX)
13 -> 19(COMM TX to MAIN RX)
Uno Loopback Connections
2 (COMM) to 0 (COMM) using a 220ohm resistor. No connection to the Mega since it's self wakeup (COMM_WAKEUP_CTRL_PIN)
Commands:
On the UART from the PC to COMM send:
s = sleep the MAIN
w = wake up the MAIN
a = sleep both the COMM and the MAIN
u = to sleep the COMM
Send any one or more character(s) through UART/Xbee to generate a low/rising/or falling signal
(depending on the attach interrupt mode) to wakeup the arduino. If the 'a' sleep all was sent
to make it sleep, any UART Rx will wake up both the COMM and MAIN at the same time. But if the
'u' was sent to make it sleep, any UART Rx will wake up the COMM only.
*/



//Used to communicate between COMM and MAIN
SoftwareSerial comm2MainSerial(COMM_SW_UART_RX_PIN, COMM_SW_UART_TX_PIN); // RX, TX, Note declare this in global and not setup() else it won't work

//Controls the self wakeup of COMM
RoverSleeperServer * sleeperCOMM = new RoverSleeperServer(COMM_WAKEUP_CTRL_PIN, &InterruptDispatch1);//COMM Wakeup Pin Control
RoverSleeperClient * sleeperMAIN = new RoverSleeperClient(MAIN_WAKEUP_CTRL_PIN);



//Holds all custom objects created by this sketch
RoverReset * resetArray[] = { 
	sleeperCOMM,
	sleeperMAIN
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
	Serial.begin(PC_USB_BAUD_RATE);//Used to talk to the computer    
	comm2MainSerial.begin(MAIN_BAUD_RATE);//Use to talk between COMM and MAIN


}

void loop()
{


	//The Computer puts COMM to Sleep or Wakes it up. It can also puts MAIN, AUXI, and NAVI to sleep  (by using COMM to command the sleep) as well.
	if (Serial.available() > 0)
	{


		rxData = Serial.read();//Get data from the computer
		if (rxData == 's')//Sleep all Megas
		{
			goToSleepMegas();
		}//end if
		else if (rxData == 'w')//Wake up all Megas
		{
			wakeUpMegas();
		}//end else if
		else if (rxData == 'u')//COMM sleep (any UART/Xbee character will generate a low/rising/or falling signal (depending on the attach interrupt mode)
		{
			goToSleepCOMM();

			//The COMM will go to sleep here. Then it will resume below once it's awoken by pressing any key.

			wakeUpCOMM();

		}//end else if
		else if (rxData == 'a')//Uno and Mega sleep (any UART/Xbee character will generate a low/rising/or falling signal (depending on the attach interrupt mode)
		{
			//Put the Megas to sleep (remotely)
			goToSleepMegas();

			//Then put the COMM to sleep (locally)
			goToSleepCOMM();


			//Wake up the COMM (locally)
			wakeUpCOMM();

			//Wake up the Megas (remotely)
			wakeUpMegas();

		}//end else if 



	}//end if

	if (sleeperCOMM->isAwake())
	{
		Serial.println(F("COMM is still awake..."));
	}
	delay(1000);




}




void InterruptDispatch1() {
	//Have to keep the ISR short else the program won't work
	sleeperCOMM->isrUpdate();//update the awake flag to reflect current status
}


void goToSleepCOMM() {
	//Pre sleep tasks
	Serial.println(F("COMM sleeping..."));
	delay(100);//add some delay to allow the serial print to finish before going to sleep

			   //Go to sleep
			   //Note: Make sure to end any Software Serial here
	comm2MainSerial.end();// IMPORTANT! You have to stop the software serial function before sleep, or it won't sleep!
	sleeperCOMM->goToSleep();//will sleep and wakeup the COMM

}
void wakeUpCOMM() {
	//Wake Up
	sleeperCOMM->hasAwoken();
	//Note: Make sure to begin (again) any Software Serial here
	comm2MainSerial.begin(MAIN_BAUD_RATE);//Turn on SW Serial again

										  //Post Wake Up tasks
	delay(100);// let everybody get up and running for a sec
	Serial.println(F("COMM Awoken!"));
}


void goToSleepMegas() {
	//Pre sleep tasks
	Serial.println(F("Megas Sleeping..."));

	//Go to sleep
	//Note: Don't forget to call this before sending the command, else the status won't be up to date
	sleeperMAIN->goToSleep();//update awake flag status
							//Send command over software serial to shutdown the MAIN, AUXI, and NAVI
	comm2MainSerial.println('s');//send 's' to the MAIN

}
void wakeUpMegas() {

	if (!sleeperMAIN->isAwake())
	{
		//Wake Up
		sleeperMAIN->wakeUp();//Creates a rising edge on the interrupt pin to wake up MAIN, which then wakes up all others

							 //Post Wake Up tasks
		Serial.println(F("Megas Awoken!"));
	}
	else
	{
		Serial.println(F("Megas already awoken."));
	}

}