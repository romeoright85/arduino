#include <RoverMessagePackager.h>


RoverMessagePackager::RoverMessagePackager()
{
}
RoverMessagePackager::~RoverMessagePackager()
{
	//do nothing
}
void packEncoderStatus(byte mtrDirection, int speed, int footage, char * outputCharArray, &byte arraySize)
{
	char tempCharArray[_MAX_ROVER_COMMAND_DATA_LEN_] = "";	

//WRITE ME LATER	
	//use DataType's byteToChar or byteToChars	
	//use sprintf to convert int to char array
	//https://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1043808026&id=1043284385
		
	arraySize = sizeof(tempCharArray);//save the output char array size
	strncpy(outputCharArray, tempCharArray, arraySize);//copy the temp char array to the output char array
	
	
}//end of packEncoderStatus()
void unpackEncoderStatus(char * inputCharArray, byte inputCharArraySize, &byte mtrDirection, &int speed, &int footage)
{
	
	char tempCharArray[_MAX_ROVER_COMMAND_DATA_LEN_] = "";	
	
//WRITE ME LATER	

	//since it's fixed length, use CharArray::substring to get the byte, speed, and footage char arrays. Refer to RoverGpsSensor.cpp	
	//use atoi to go from array to int
	//use DataType's charToByte or charToBytes
	
	
	strncpy(tempCharArray, inputCharArray, inputCharArraySize);//copy the input string to the temp array, tempCharArray
	
	
}//end of unpackEncoderStatus()
void RoverMessagePackager::reset()
{
}

