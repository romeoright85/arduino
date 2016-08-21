#include <SoftwareSerial.h>
#include <RoverSleeperLocal.h>
#include <RoverSleeperClient.h>

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
RoverSleeperLocal sleeperCOMM(COMM_WAKEUP_CTRL_PIN, &InterruptDispatch1);//COMM Wakeup Pin Control
RoverSleeperClient sleeperMAIN(MAIN_WAKEUP_CTRL_PIN);



void setup()
{ 
	Serial.begin(PC_USB_BAUD_RATE);//Used to talk to the computer    
	comm2MainSerial.begin(COMM_BAUD_RATE);//Use to talk between COMM and MAIN


}

void loop()
{


	//The Computer puts MAIN to Sleep or Wakes it up. It can also put COMM to sleep  (by using MAIN to command the sleep) as well.
	if (Serial.available() > 0)
	{
		
		
		rxData = Serial.read();//Get data from the computer
		if (rxData == 's')//MAIN sleep
		{
			goToSleepMAIN();
		}//end if
		else if (rxData == 'w')//MAIN wakeup
		{
			wakeUpMAIN();
		}//end else if
		else if (rxData == 'u')//COMM sleep (any UART/Xbee character will generate a low/rising/or falling signal (depending on the attach interrupt mode)
		{
			goToSleepCOMM();

			//The program will go to sleep and then resume below once it's awoken

			wakeUpCOMM();
			
		}//end else if
		else if (rxData == 'a')//Uno and Mega sleep (any UART/Xbee character will generate a low/rising/or falling signal (depending on the attach interrupt mode)
		{
			//Put the MAIN to sleep (remotely)
			goToSleepMAIN();

			//Then put the COMM to sleep (locally)
			goToSleepCOMM();


			//Wake up the COMM (locally)
			wakeUpCOMM();

			//Wake up the MAIN (remotely)
			wakeUpMAIN();

		}//end else if 

		
	
	}//end if

	if (sleeperCOMM.isAwake())
	{
		Serial.println(F("COMM is still awake..."));
	}
	delay(1000);




}




void InterruptDispatch1() {
	//Have to keep the ISR short else the program won't work
	sleeperCOMM.isrUpdate();//update the awake flag to reflect current status
}


void goToSleepCOMM() {
	//Pre sleep tasks
	Serial.println(F("COMM sleeping..."));
	delay(100);//add some delay to allow the serial print to finish before going to sleep

	//Go to sleep
	//Note: Make sure to end any Software Serial here
	comm2MainSerial.end();// IMPORTANT! You have to stop the software serial function before sleep, or it won't sleep!
	sleeperCOMM.goToSleep();//will sleep and wakeup the COMM

}
void wakeUpCOMM() {
	//Wake Up
	sleeperCOMM.hasAwoken();
	//Note: Make sure to begin (again) any Software Serial here
	comm2MainSerial.begin(COMM_BAUD_RATE);//Turn on SW Serial again

	//Post Wake Up tasks
	delay(100);// let everybody get up and running for a sec
	Serial.println(F("COMM Awoken!"));
}


void goToSleepMAIN() {
	//Pre sleep tasks
	Serial.println(F("MAIN Sleeping..."));

	//Go to sleep
	//Note: Don't forget to call this before sending the command, else the status won't be up to date
	sleeperMAIN.goToSleep();//update awake flag status
	//Send command over software serial to shutdown the MAIN
	comm2MainSerial.println('s');//send 's' to the MAIN

}
void wakeUpMAIN() {
	
	if (!sleeperMAIN.isAwake())
	{
		//Wake Up
		sleeperMAIN.wakeUp();//Creates a rising edge on the interrupt pin to wake up MAIN

		//Post Wake Up tasks
		Serial.println(F("MAIN Awoken!"));
	}
	else
	{
		Serial.println(F("MAIN already awoken."));
	}

}