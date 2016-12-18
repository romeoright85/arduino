/* This Script is the bare bones needed to Keep a Uptime counter that will survive the 50 day timer rollover
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

//************************** Just Some basic Definitions used for the Up Time LOgger ************//
long Day = 0;
int Hour = 0;
int Minute = 0;
int Second = 0;
int HighMillis = 0;
int Rollover = 0;


//************** Setup routine - Runs once at power up **************************//
void setup() {
	Serial.begin(9600); // starting Serial Com's

};

//****** Main Loop - Put your Code Here ********************//
void loop() {

	uptime(); //Runs the uptime script located below the main loop and reenters the main loop
	print_Uptime();
	delay(10000);
};



//************************ Uptime Code - Makes a count of the total up time since last start ****************//

void uptime() {
	//** Making Note of an expected rollover *****//   
	if (millis() >= 3000000000) {
		HighMillis = 1;

	}
	//** Making note of actual rollover **//
	if (millis() <= 100000 && HighMillis == 1) {
		Rollover++;
		HighMillis = 0;
	}

	long secsUp = millis() / 1000;

	Second = secsUp % 60;

	Minute = (secsUp / 60) % 60;

	Hour = (secsUp / (60 * 60)) % 24;

	Day = (Rollover * 50) + (secsUp / (60 * 60 * 24));  //First portion takes care of a rollover [around 50 days]

};

//******************* Prints the uptime to serial window **********************//
void print_Uptime() {

	Serial.print(F("Uptime: ")); // The "F" Portion saves your SRam Space
	Serial.print(Day);
	Serial.print(F("  Days  "));
	Serial.print(Hour);
	Serial.print(F("  Hours  "));
	Serial.print(Minute);
	Serial.print(F("  Minutes  "));
	Serial.print(Second);
	Serial.println(F("  Seconds"));
};