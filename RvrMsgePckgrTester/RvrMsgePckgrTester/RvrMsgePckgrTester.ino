//RvrMsgePckgrTester = RoverMessagePackager, but the name was too long so it had to be shortened


#define _WHEEL_ENCODER_DEFINITIONS


#include <RoverMessagePackager.h>
#include <RoverConfig.h>


//Global Variables

RoverMessagePackager * roverMessagePackager = new RoverMessagePackager();


//Data Format: xyyyzzzz (where x is the direction, y is the speed, and z is the footage/distance in feet.
	//Note: Speed is in inches per second.





//Test Data Set 1 - Data with whole number shorters
byte testDirection1 = MOTOR_STOPPED;//aka 0
int testSpeed1 = 12;
int testFootage1 = 987;
char testPackArray1[_MAX_ROVER_COMMAND_DATA_LEN_];
byte testPackArray1Size;
//The output should be Packed Data 1: 0012987

//Test Data Set 2 - Data as whole numbers only, within length
byte testDirection2 = MOTOR_FORWARD;//aka 1
int testSpeed2 = 123;
int testFootage2 = 9876;
char testPackArray2[_MAX_ROVER_COMMAND_DATA_LEN_];
byte testPackArray2Size;
//Packed Data 2: 11239876

//Test Data Set 3 - Data as whole numbers only, over the length
byte testDirection3 = MOTOR_REVERSE;//aka 2
int testSpeed3 = 12345;
int testFootage3 = 97654;
char testPackArray3[_MAX_ROVER_COMMAND_DATA_LEN_];
byte testPackArray3Size;
//Packed Data 3: 29999999

//Test Data Set 4 - Unpacking
char testUnpackArray[] = "12345678";//direction should be 1, speed should be 234, footage should be 5678
byte unpackedDirection;
int unpackedSpeed;
int unpackedFootage;
/*
	Direction: 1
	Speed: 234
	Footage: 5678
*/


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
	_PC_USB_SERIAL_.flush();//waits for any outgoing serial data to complete
	delay(50);
}


void loop() {

	
	
	_PC_USB_SERIAL_.print(F("Packed Data 1: ")); 
	RoverMessagePackager::packEncoderStatus(testDirection1, testSpeed1, testFootage1, testPackArray1, testPackArray1Size);
	_PC_USB_SERIAL_.println(testPackArray1);
	
	
	_PC_USB_SERIAL_.print(F("Packed Data 2: "));
	RoverMessagePackager::packEncoderStatus(testDirection2, testSpeed2, testFootage2, testPackArray2, testPackArray2Size);
	_PC_USB_SERIAL_.println(testPackArray2);
	
	
	_PC_USB_SERIAL_.print(F("Packed Data 3: "));
	RoverMessagePackager::packEncoderStatus(testDirection3, testSpeed3, testFootage3, testPackArray3, testPackArray3Size);
	_PC_USB_SERIAL_.println(testPackArray3);	
	
	RoverMessagePackager::unpackEncoderStatus(testUnpackArray, sizeof(testUnpackArray), unpackedDirection, unpackedSpeed, unpackedFootage);
	_PC_USB_SERIAL_.print(F("Direction: "));
	_PC_USB_SERIAL_.println(unpackedDirection);
	_PC_USB_SERIAL_.print(F("Speed: "));
	_PC_USB_SERIAL_.println(unpackedSpeed);
	_PC_USB_SERIAL_.print(F("Footage: "));
	_PC_USB_SERIAL_.println(unpackedFootage);
	

	while (1);
}//end loop()
