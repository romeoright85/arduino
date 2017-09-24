//This is test cosd. It can be used on any Arduino.
//This tests the BooleanBitFlags class which uses one 8-bit byte to hold 8 boolean states to save memory (instead of using eight 8-bit booleans)


#include <BooleanBitFlags.h>
#include <RoverConfig.h>


#define _FLAG_BIT_NONE_	0x00
#define _FLAG_BIT_1_	0x01
#define _FLAG_BIT_2_	0x02
#define _FLAG_BIT_3_	0x04
#define _FLAG_BIT_4_	0x08
#define _FLAG_BIT_5_	0x10
#define _FLAG_BIT_6_	0x20
#define _FLAG_BIT_7_	0x40
#define _FLAG_BIT_8_	0x80


//Global Variables
byte flagSet1;

RoverReset * resetArray[] = {
	
};


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}

	Serial.begin(PC_USB_BAUD_RATE);
	delay(1000);
}


void loop() {
	BooleanBitFlags::resetFlag(flagSet1);

	BooleanBitFlags::setFlagBit(flagSet1, _FLAG_BIT_1_);


	Serial.println(F("Trial 1: Set Bit 1"));
	if (BooleanBitFlags::flagIsSet(flagSet1, _FLAG_BIT_1_))
	{
		Serial.println(F("Bit 1 is set."));
	}
	else
	{
		Serial.println(F("Bit 1 is cleared."));
	}


	Serial.println(F("Trial 2: Clear Bit 1"));
	BooleanBitFlags::clearFlagBit(flagSet1, _FLAG_BIT_1_);

	if (BooleanBitFlags::flagIsSet(flagSet1, _FLAG_BIT_1_))
	{
		Serial.println(F("Bit 1 is set."));
	}
	else
	{
		Serial.println(F("Bit 1 is cleared."));
	}
	BooleanBitFlags::resetFlag(flagSet1);
	Serial.println(F("Trial 3: Set Bit 3"));
	BooleanBitFlags::setFlagBit(flagSet1, _FLAG_BIT_3_);
	if (BooleanBitFlags::flagIsSet(flagSet1, _FLAG_BIT_3_))
	{
		Serial.println(F("Bit 3 is set."));
	}
	else
	{
		Serial.println(F("Bit 3 is cleared."));
	}

	Serial.println(F("Trial 4: Reset, then Set Bit 4"));
	BooleanBitFlags::resetFlag(flagSet1);	
	if (BooleanBitFlags::flagIsSet(flagSet1, _FLAG_BIT_3_))
	{
		Serial.println(F("Bit 3 is set."));
	}
	else
	{
		Serial.println(F("Bit 3 is cleared."));
	}
	BooleanBitFlags::setFlagBit(flagSet1, _FLAG_BIT_4_);
	if (BooleanBitFlags::flagIsSet(flagSet1, _FLAG_BIT_4_))
	{
		Serial.println(F("Bit 4 is set."));
	}
	else
	{
		Serial.println(F("Bit 4 is cleared."));
	}






	while (1);
	
}
