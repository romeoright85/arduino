#include <SoftwareSerial.h>
#include <RoverSleeperLocal.h>

char rxData;
void InterruptDispatch1();


/*
Connections:
Uno Pin to Mega Pin (signal)
3  -> 2 (MEGA_WAKEUP_CTRL)
12 -> 18 (UNO RX to Mega TX)
13 -> 19(UNO TX to Mega RX)
Uno Loopback Connections
2 (UNO) to 0 (UNO) using a 220ohm resistor. No connection to the Mega since it's self wakeup (UNO_WAKEUP_CTRL)
Commands:
On the COM from the PC to UNO send:
s = sleep the Mega
w = wake up the Mega
a = sleep both the UNO and the Mega
u = to sleep the Uno
Send any one or more character(s) through UART/Xbee to generate a low/rising/or falling signal
(depending on the attach interrupt mode) to wakeup the arduino. If the 'a' sleep all was sent
to make it sleep, any UART Rx will wake up both the UNO and Mega at the same time. But if the
'u' was sent to make it sleep, any UART Rx will wake up the UNO only.
*/









//Controls the self wakeup of COMM
RoverSleeperLocal sleeperCOMM(COMM_WAKEUP_CTRL_PIN, &InterruptDispatch1);//COMM Wakeup Pin Control

void setup()
{ 
	Serial.begin(PC_USB_BAUD_RATE);//Used to talk to the computer    
	


}

void loop()
{


	//The Computer puts MAIN to Sleep or Wakes it up. It can also put COMM to sleep  (by using MAIN to command the sleep) as well.
	if (Serial.available() > 0)
	{
		rxData = Serial.read();//Get data from the computer
		if (rxData == 'u')//COMM sleep (any UART/Xbee character will generate a low/rising/or falling signal (depending on the attach interrupt mode)
		{
			Serial.println(F("COMM sleeping..."));
			delay(25);//add some delay to allow the serial print to finish before going to sleep
			//Go to Sleep Mode
			//Note: Make sure to end any Software Serial here
			sleeperCOMM.goToSleep();//will sleep and wakeup the COMM
			//The program will go to sleep and then resume below once it's awoken
			sleeperCOMM.hasAwoken();
			//Note: Make sure to begin (again) any Software Serial here
			delay(1000);// let everybody get up and running for a sec
			Serial.println(F("Uno awaken!"));



		}//end else if		
	}//end if


	Serial.println(F("COMM is still awake..."));

//Serial.println((int)&InterruptDispatch1);//debug
	delay(1000);


}




void InterruptDispatch1() {
	sleeperCOMM.isrUpdate();
}