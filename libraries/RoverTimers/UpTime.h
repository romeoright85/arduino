//UpTime.h
//Used for the Gas Sensor, etc.

/*
Millis outputs an unsigned long
The range is:
0 to 4,294,967,295
So detect when the millis is near it's upper range (arbitrarily chosen to be say: 3000000000) and flag it for an upcoming rollover
once the rollover has occured, the number will be low again
*/


	


/*
Script based on:

https://hackaday.io/project/7008-fly-wars-a-hackers-solution-to-world-hunger/log/25043-updated-uptime-counter
https://hackaday.io/project/7008-fly-wars-a-hackers-solution-to-world-hunger/log/24201-just-a-few-useful-arduino-hacks-sram-uptime


This Script is the bare bones needed to Keep a Uptime counter that will survive the 50 day timer rollover
This will not give a uptime of great accuracy over long periods, but it will let you see if your arduino has reset
if you want better accuracy, pull the Unix time from the IOT, External RTC or GPS module
Also Reconnecting the serial com's will reset the arduino. So this is mainly useful for a LCD screen

Michael Ratcliffe  Mike@MichaelRatcliffe.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see .


*/

/*

--------------------
Example Use:
--------------------
#include <UpTime.h>


UpTime * upTimeMonitor = new UpTime();


Place the output compare interrupt setup code in the setup function:
	setup(){
		//Setting Up Timer Interrupt
		OCR0A = 0x7F;//Set the timer to interrupt somewhere in the middle of it's count, say 127 aka 7F in hex (since Timer0 is 8 bit and counts from 0 to 255)
		TIMSK0 |= _BV(OCIE0A);//Activating the Timer Interrupt by setting the Mask Register	
	}


Then create a interrupt service routine:
	SIGNAL(TIMER0_COMPA_vect)//Interrupt Service Routine
	{
		//Uptime Monitor
		upTimeMonitor->run();//active the uptime monitor
	}
	
	
Then in the loop (either directly or by some other function, class method, etc.)

Example for loop() use:
	Serial.println(roverUptime->getSeconds());
	
	
	
--------------------

*/


#ifndef _UPTIME_H
#define _UPTIME_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>

/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/

//define Arduino 2: AUXI in order to use it's config pins
#ifndef _ARD_2_AUXI_H
	#define _ARD_2_AUXI_H
#endif

/********************************************************************/

#define _UPTIME_DEFINITIONS

#include <RoverConfig.h>

class UpTime : public virtual RoverReset {
public:
	UpTime();//constructor
	~UpTime();//destructor
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)	
	void forcedReset();//force resets the clock. Else don't reset the clock with SW resets as you still want to monitor how long the rover has been online
	unsigned long getDays();
	byte getHours();//in 24 hour format
	byte getMinutes();
	byte getSeconds();
	void run();//keeps the clock running in the background (i.e. calculations). This is required to run in the background in order to monitor any roll overs.
	void printUptime();//Prints to the USB for debugging in an easily read format
	
private:
	//Non-SW Resettable
	//For uptime you don't want these variables to reset when you reset all other things with software. Instead have a manual reset option.
	unsigned long _upTimeInSeconds;	
	byte _numberOfRollOvers;//number of rollovers counter. Each rollover is about 50 days, since 4,294,967,295 milliseconds is 49.71026961805556 days.
	boolean rolloverOccuringSoon;//is true when millis is near it's max value of 4,294,967,295. (Defined by UPTIME_ROLLOVER_UPPER_THRESHOLD in RoverConfig.h)
	//SW Resettable

};

#endif 