//This code is for any Arduino
//This is to test bitwise operations
//This is to use one byte to store 8 booleans to save memory


byte flagset;


#define _FLAG_BIT_NONE_	0x00
#define _FLAG_BIT_1_	0x01
#define _FLAG_BIT_2_	0x02
#define _FLAG_BIT_3_	0x04
#define _FLAG_BIT_4_	0x08
#define _FLAG_BIT_5_	0x10
#define _FLAG_BIT_6_	0x20
#define _FLAG_BIT_7_	0x40
#define _FLAG_BIT_8_	0x80

void setup()
{

	Serial.begin(9600);
	delay(1000);

}

void loop()
{


	resetFlag(flagset);
	Serial.println(F("Trial 1: Bit 0"));
	whichBit(flagset);
	Serial.println(F("Trial 2: Bit 1"));
	setFlagBit(flagset, _FLAG_BIT_1_);
	whichBit(flagset);
	Serial.println(F("Trial 3: Bit 1 and 2"));
	resetFlag(flagset);
	setFlagBit(flagset, _FLAG_BIT_1_);
	setFlagBit(flagset, _FLAG_BIT_2_);	
	whichBit(flagset);
	Serial.println(F("Trial 4: Bit 2"));
	clearFlagBit(flagset, _FLAG_BIT_1_);
	whichBit(flagset);
	Serial.println(F("Trial 5: Bit 1, 2, 3, 4, 8"));
	setFlagBit(flagset, _FLAG_BIT_1_);
	setFlagBit(flagset, _FLAG_BIT_2_);
	setFlagBit(flagset, _FLAG_BIT_3_);
	setFlagBit(flagset, _FLAG_BIT_4_);
	setFlagBit(flagset, _FLAG_BIT_8_);
	whichBit(flagset);
	Serial.println(F("Trial 6: Bit 6"));
	resetFlag(flagset);
	setFlagBit(flagset, _FLAG_BIT_6_);
	whichBit(flagset);


	while (1);//wait forever

}

void resetFlag(byte &flag)
{
	flag = 0x00;
}
void setFlagBit(byte &flag, byte flagBit)
{
	flag = flag | flagBit;
}
void clearFlagBit(byte &flag, byte flagBit)
{
	flag = flag & (~flagBit);
}
void whichBit(byte flag)
{
	if (!(flag | _FLAG_BIT_NONE_))
	{
		Serial.println(F("None"));
	}
	if (flag & _FLAG_BIT_1_)
	{
		Serial.println(F("1"));
	}
	if (flag & _FLAG_BIT_2_)
	{
		Serial.println(F("2"));
	}
	if (flag & _FLAG_BIT_3_)
	{
		Serial.println(F("3"));
	}
	if (flag & _FLAG_BIT_4_)
	{
		Serial.println(F("4"));
	}
	if (flag & _FLAG_BIT_5_)
	{
		Serial.println(F("5"));
	}
	if (flag & _FLAG_BIT_6_)
	{
		Serial.println(F("6"));
	}
	if (flag & _FLAG_BIT_7_)
	{
		Serial.println(F("7"));
	}
	if (flag & _FLAG_BIT_8_)
	{
		Serial.println(F("8"));
	}
}
