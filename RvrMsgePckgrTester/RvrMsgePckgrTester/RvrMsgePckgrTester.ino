//RvrMsgePckgrTester = RoverMessagePackager, but the name was too long so it had to be shortened


#define _WHEEL_ENCODER_DEFINITIONS


#include <RoverMessagePackager.h>
#include <RoverConfig.h>


//Global Variables

RoverMessagePackager * roverMessagePackager = new RoverMessagePackager();


//Data Format: xyy.yyyzzz.zzz (where x is the direction, y is the speed, and z is the footage/distance in feet.
	//Note: Speed is in inches per second.

//Test Data Set 1 - Data shorter
byte testDirection1 = MOTOR_STOPPED;
int testSpeed1 = 12.3;
int testFootage1 976.5;

//Test Data Set 2 - Data within length
byte testDirection2 = MOTOR_FORWARD;
int testSpeed2 = 12.345;
int testFootage2 976.543

//Test Data Set 3 - Data longer
byte testDirection3 = MOTOR_REVERSE;
int testSpeed3 = 12.3456789;
int testFootage3 976.543210;



RoverReset * resetArray[] = {
	roverMessagePackager
};


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}

	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);

}


void loop() {

}
