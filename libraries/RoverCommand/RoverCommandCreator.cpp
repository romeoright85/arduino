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
}//end of reset()
char * RoverCommandCreator::createCmd(byte origin, byte destination, byte priorityLevel, char * commandString)
{

	//Note: The origin of the messsage will change every time it passes through an Arduino (i.e. using the createCmd with ROVERCOMM_COMM passed to it). It shows the last originating Arduino that handled the data. If the true origin is required, that should be placed in the command data where it's not altered.
	
	char inputCharArray[ROVER_COMM_SENTENCE_LENGTH] = "";	
	char priorityLevelCharArray[4] = "";//size for since it's three characters and 1 null terminator
	byte charIndex;
	
	//The format is /OcDLL*tttdddd... (Note: The d's can range from none to up to _MAX_ROVER_COMMAND_DATA_LEN_ - 1, i.e. 15-1=14. Minus 1 due to null character. So hence dddd....)
	
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
	//Convert priorityLevel from byte to a char array, where priorityLevel has a range of 00 to 99
	if(DataType::byteToChars(priorityLevel, priorityLevelCharArray, sizeof(priorityLevelCharArray)))
	{
		//if byteToChars() was successful, shift the array to the left and get rid of the hundreds place (since priorityLevel is only two digit)
		priorityLevelCharArray[0] = priorityLevelCharArray[1];
		priorityLevelCharArray[1] = priorityLevelCharArray[2];
		priorityLevelCharArray[2] = priorityLevelCharArray[3];	//this should be the null character
		priorityLevelCharArray[3] = '\0';//add another null since this element won't be used
	}
	else
	{
		priorityLevelCharArray[0] = '9';//default value, error
		priorityLevelCharArray[1] = '9';//default value, error
		priorityLevelCharArray[2] = '\0';//null terminating character
		priorityLevelCharArray[3] = '\0';//add another null since this element won't be used
	}
	
	//Concantenate Strings
	strcat(inputCharArray, priorityLevelCharArray);
	//Add the command format identifier '*'
	strcat(inputCharArray, "*");	
	//Adding the commandString (should have commandTag appended already if commandTag is being used for this command)
	strcat(inputCharArray, commandString);
	//Add the null terminating character (just in case if there isn't already one)
	strcat(inputCharArray, '\0');
		
	return inputCharArray;//DEBUG
	
}//end of createCmd() without commandTag
char * RoverCommandCreator::createCmd(byte origin, byte destination, byte priorityLevel, byte commandTag, char * commandString)
{
	
	//Using delegation and function overloading
	
	char inputCharArray[ROVER_COMM_SENTENCE_LENGTH] = "";
		
	//Concantenate Strings		
	//Adding the command tag
	strcat(inputCharArray, RoverCommandCreator::byteToCharArrayWithLeadingZeros(commandTag));
	//Adding the commandString
	strcat(inputCharArray, commandString);
	//Add the null terminating character (just in case if there isn't already one)
	strcat(inputCharArray, '\0');
	
	
	return createCmd(origin, destination, priorityLevel, inputCharArray);//DEBUG	
	
	
}//end of createCmd() with commandTag
char * RoverCommandCreator::byteToCharArrayWithLeadingZeros(byte input)
{
	
	char tempCharArray[4];//for 3 digit character but string null character
	
	
	//add leadings zeros as required
	if(input > 99)
	{
		//no leading zeros required
		sprintf(tempCharArray, "%u\0", input);	
	}
	else if(input > 9)
	{
		//one leading zero required
		sprintf(tempCharArray, "0%u\0", input);	
	}
	else
	{
		//two leading zeros required
		sprintf(tempCharArray, "00%u\0", input);	
	}
	
return tempCharArray;
	
}//end of byteToCharArrayWithLeadingZeros()


	