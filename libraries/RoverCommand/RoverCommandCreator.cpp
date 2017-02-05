#include <RoverCommandCreator.h>


RoverCommandCreator::RoverCommandCreator()
{
}
RoverCommandCreator::~RoverCommandCreator()
{
	//do nothing
}
void RoverCommandCreator::reset()
{
}
char * RoverCommandCreator::createCmd(byte origin, byte destination, byte priorityLevel, char * commandString)
{

		
	char inputCharArray[ROVER_COMM_SENTENCE_LENGTH] = "";	
	byte charIndex;
	
	
	
	//Start at index 0
	charIndex = 0;		
	//Add the command format identifier '/'
	inputCharArray[charIndex] = '/';	
	charIndex++;		
	//Add the origin	
	inputCharArray[charIndex] = DataType::byteToHex(origin);			
	charIndex++;
	//Add the command format identifier 'c'
	inputCharArray[charIndex] = 'c';	
	charIndex++;
	//Add the destination	
	inputCharArray[charIndex] = DataType::byteToHex(destination);		
	delayMicroseconds(1);//for some reason the code needs a delay here to work properly. Use delayMicroseconds since it's faster than delay (which is in milliseconds)
	charIndex++;
	
	
	WHERE LEFT OFF
	
	USE byteToChars to convert priority level to a string, then finish the command
	
	
	
	
	
	//Add the null terminating character (just in case if there isn't already one)
	inputCharArray[charIndex] = '\0';	
	
	//Serial.println(inputCharArray);
	
	//return "";//DEBUG
	
	return inputCharArray;//DEBUG

	
}
char * RoverCommandCreator::createCmd(byte origin, byte destination, byte priorityLevel, char * commandTag, char * commandString)
{
	
	//Using delegation and function overloading
	
	char inputCharArray[ROVER_COMM_SENTENCE_LENGTH] = "";
		
	//Concantenate Strings
	strcat(inputCharArray, commandTag);
	strcat(inputCharArray, commandString);
	//Add the null terminating character (just in case if there isn't already one)
	strcat(inputCharArray, '\0');
	
	
	return createCmd(origin, destination, priorityLevel, inputCharArray);//DEBUG	
	
	
}