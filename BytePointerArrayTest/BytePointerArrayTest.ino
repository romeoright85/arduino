#include <RoverConfig.h>

byte testFlagSet1 = 0xF0;
byte testFlagSet2 = 0xF0;
byte testFlagSet3 = 0xF0;


byte systemFlagSet1 = 0xF0;
byte systemFlagSet2 = 0xF0;
byte systemFlagSet3 = 0xF0;

#define TEST_FLAGS	0
#define SYSTEM_FLAGS	1

#define ARRAY_SIZE 3

void setup() {
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	delay(1000);
	_PC_USB_SERIAL_.println("Arduino Starting Up");
}


void loop() {


	_PC_USB_SERIAL_.println("testFlagSet1, Initial, 0xF0");
	_PC_USB_SERIAL_.println(testFlagSet1, HEX);



	_PC_USB_SERIAL_.println("testFlagSet1, No Change, 0xF0");
	setAllFlagsTo(true, SYSTEM_FLAGS);
	_PC_USB_SERIAL_.println(testFlagSet1, HEX);



	_PC_USB_SERIAL_.println("testFlagSet1, All True, 0xFF");
	setAllFlagsTo(true, TEST_FLAGS);
	_PC_USB_SERIAL_.println(testFlagSet1, HEX);


	_PC_USB_SERIAL_.println("testFlagSet1, All Fals, 0x00");
	setAllFlagsTo(false, TEST_FLAGS);
	_PC_USB_SERIAL_.println(testFlagSet1, HEX);

	while (1);
}

void setAllFlagsTo(boolean choice, byte flagSet)
{
	byte * flagSetArray[ARRAY_SIZE] = { 0 };
	switch (flagSet)
	{
	case TEST_FLAGS:
		flagSetArray[0] = &testFlagSet1;
		flagSetArray[1] = &testFlagSet2;
		flagSetArray[2] = &testFlagSet3;
		break;
	case SYSTEM_FLAGS:
		flagSetArray[0] = &systemFlagSet1;
		flagSetArray[1] = &systemFlagSet2;
		flagSetArray[2] = &systemFlagSet3;
		break;
	default:
		break;
	}
	arraySet(choice, flagSetArray, ARRAY_SIZE);
}

void arraySet(boolean choice, byte * bytePointerArray[], byte arraySize)
{

		for (byte i = 0; i < arraySize; i++)
		{
			byteSet(choice, *bytePointerArray[i]);
		}//end for	
}

void byteSet(boolean choice, byte &byteOfInterest)
{
	if (choice)
	{
		byteOfInterest = 0xFF;//set all bits in the byte to 1
	}
	else
	{
		byteOfInterest = 0x00;//clear all bits in the byte to 0
	}
}