#include <BooleanBitFlags.h>


BooleanBitFlags::BooleanBitFlags()
{
}
BooleanBitFlags::~BooleanBitFlags()
{
	//do nothing
}
void BooleanBitFlags::reset()
{
	//do nothing
}
void BooleanBitFlags::resetFlag(byte &flag)
{
	flag = 0x00;
}
void BooleanBitFlags::setFlagBit(byte &flag, byte flagOfInterest)
{
	flag = flag | flagOfInterest;
}
void BooleanBitFlags::clearFlagBit(byte &flag, byte flagOfInterest)
{
	flag = flag & (~flagOfInterest);
}
boolean BooleanBitFlags::flagIsSet(byte &flag, byte flagOfInterest)
{
	if (flag & flagOfInterest)
	{
		return true;
	}//endif
	else
	{
		return false;
	}//end else
}