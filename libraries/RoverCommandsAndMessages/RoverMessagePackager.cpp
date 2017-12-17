#include <RoverMessagePackager.h>


RoverMessagePackager::RoverMessagePackager()
{
}
RoverMessagePackager::~RoverMessagePackager()
{
	//do nothing
}
void RoverMessagePackager::packEncoderStatus(byte mtrDirection, int speed, int footage, char * outputCharArray, byte &arraySize)
{
	
	//Note: The data per this design will be fixed predetermined lengths, i.e. xyyyzzzz (where x is the direction, y is the speed, and z is the footage/distance in feet.
		
	char tempArray[_MAX_ROVER_COMMAND_DATA_LEN_] = "";	
	
	//Data range bounding
	if(speed > 999)
	{
		speed = 999;//limit the speed  to a max range of 999
	}
	if(footage > 9999)
	{
		footage = 9999;//limit the footage to a max range of 9999
	}

	
	//Start by filling the output char array with the Motor Direction
	sprintf(tempArray, "%c", DataType::byteToChar(mtrDirection));
	//Concatenating Speed to the output char array
	sprintf(tempArray, "%s%03u", tempArray, speed);
	//Concatenating Footage to the output char array
	sprintf(tempArray, "%s%03u", tempArray, footage);	
	arraySize = sizeof(tempArray);//save the output char array size
	strncpy(outputCharArray, tempArray, arraySize);//copy the temp char array to the output char array
	
	
}//end of packEncoderStatus()
void RoverMessagePackager::unpackEncoderStatus(char * inputCharArray, byte inputCharArraySize, byte &mtrDirection, int &speed, int &footage)
{

	//Note: The data per this design will be fixed predetermined lengths, i.e. xyyyzzzz (where x is the direction, y is the speed, and z is the footage/distance in feet.
		
	//Note: Need char length + 1 since the terminating char /0 is added on with CharArray::substring()
	char mtrDirectionCharArray[BUFFER_SIZE_2];
	char speedCharArray[BUFFER_SIZE_4];
	char footageCharArray[BUFFER_SIZE_5];

	CharArray::substring(inputCharArray, inputCharArraySize, 0, 1, mtrDirectionCharArray);	
	CharArray::substring(inputCharArray, inputCharArraySize, 1, 4, speedCharArray);	
	CharArray::substring(inputCharArray, inputCharArraySize, 4, 8, footageCharArray);	
	
	//Convert Char Array to Byte
	mtrDirection = DataType::charsToByte(mtrDirectionCharArray);
	//Convert Char Array to Integer
	speed = atoi(speedCharArray);
	//Convert Char Array to Integer
	footage = atoi(footageCharArray);	
}//end of unpackEncoderStatus()
