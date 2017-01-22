#include <CharArray.h>


CharArray::CharArray()
{
	//do nothing
}
CharArray::~CharArray()
{
	//do nothing
}
//Index Of - With start index provided
int CharArray::indexOf(char * array, byte arraySize, char charToFind, byte startIndex)
{
	
	#ifdef _DEBUG_PROBE_INDEXOF_
		Serial.print(F("IndexOf: "));//DEBUG
		Serial.println(array);//DEBUG
		Serial.print(F("Array Size: "));//DEBUG
		Serial.println(arraySize);//DEBUG
		Serial.print(F("charToFind: "));//DEBUG
		Serial.println(charToFind);//DEBUG
	#endif
	

	for (byte i = startIndex; i <= arraySize; i++)
	{

		if (array[i] == charToFind)
		{

			return i;

		}
	}
	return -1;
}
//Index Of - With no start index provided
int CharArray::indexOf(char * array, byte arraySize, char charToFind)
{
	//add delay else the function delegation doesn't work properly
	delay(1);	
	return indexOf(array, arraySize, charToFind, 0 );
}





//Substring - With no start index provided
char * CharArray::substring(char * charArray, byte startIndex, byte endIndex)
{
	
	byte tempIndex;
	byte size;
	char * tempCharArray;
	
	//startIndex should be smaller (before) the endIndex. Else swap the numbers if the user input them in wrong
	if(startIndex > endIndex)
	{		
		tempIndex = endIndex;
		endIndex = startIndex;
		startIndex = tempIndex;
	}
	
	size = endIndex - startIndex;
	tempCharArray = (char*)malloc(size * sizeof(char));
	strncpy(tempCharArray, charArray + startIndex, size * sizeof(char));
	tempCharArray[size * sizeof(char)] = 0;
	return tempCharArray;
}
//Substring - With no start index provided
char * CharArray::substring(char * charArray, byte endIndex)
{
	
	byte size;
	char * tempCharArray;
	
	size = endIndex;
	tempCharArray = (char*)malloc(size * sizeof(char));
	strncpy(tempCharArray, charArray, size * sizeof(char));
	tempCharArray[size * sizeof(char)] = 0;
	return tempCharArray;

}










int CharArray::stringSize(char * charArray, byte arraySize)
{
	
	for(int i = 0; i < arraySize; i++)
	{
		if(charArray[i] == '\0')
		{
			return i;
		}
	}
	return -1;//if not found
}	

