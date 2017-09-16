//Used for AUXI - 2
//Used for the Gas Sensor, etc.

#include <UpTime.h>


//Global Variables

UpTime * roverUptime = new UpTime();

RoverReset * resetArray[] = {
	roverUptime
};


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}

	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);

	
	
	//Setting Up Timer Interrupt
	OCR0A = 0x7F;//Set the timer to interrupt somewhere in the middle of it's count, say 127 aka 7F in hex (since Timer0 is 8 bit and counts from 0 to 255)
	TIMSK0 |= _BV(OCIE0A);//Activating the Timer Interrupt by setting the Mask Register
	/*
	Reference:
	https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers
	http://forum.arduino.cc/index.php?topic=3240.0
	https://protostack.com.au/2010/09/timer-interrupts-on-an-atmega168/
	*/
	
	
}


SIGNAL(TIMER0_COMPA_vect)//Interrupt Service Routine
{
	//Uptime Monitor
	roverUptime->run();//active the uptime monitor
}

void loop() {
	roverUptime->run();

	roverUptime->printUptime();

	delay(random(500, 5000));//delay a randon number between 0.5 a second to 5 seconds in order to test the code by seeing time variability
}



