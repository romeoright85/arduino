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
byte CharArray::indexOf(char * array, byte arraySize, char charToFind, byte startIndex)
{


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
byte CharArray::indexOf(char * array, byte arraySize, char charToFind)
{
	//add delay else the function delegation doesn't work properly
	delay(1);
	return indexOf(array, 0, charToFind, arraySize);
}
//Substring - With no start index provided
char * CharArray::substring(char * charArray, byte startIndex, byte endIndex)
{
	byte size = endIndex - startIndex;
	char * temp;
	temp = (char*)malloc(size * sizeof(char));
	strncpy(temp, charArray + startIndex, size * sizeof(char));
	temp[size * sizeof(char)] = 0;
	return temp;
}
//Substring - With no start index provided
char * CharArray::substring(char * charArray, byte endIndex)
{
	byte size = endIndex;
	char * temp;
	temp = (char*)malloc(size * sizeof(char));
	strncpy(temp, charArray, size * sizeof(char));
	temp[size * sizeof(char)] = 0;
	return temp;

}



