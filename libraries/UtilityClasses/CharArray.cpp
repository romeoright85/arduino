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


void CharArray::substring(char * inputCharArray, byte arraySize, byte startIndex, byte endIndex, char * outputCharArray)
{
	
	//Note: arraySize not used, but kept, in order to do function overloading
	
	char tempCharArray[arraySize];
		
	byte j = 0;	
	byte tempIndex = 0;
	
	//do a swap if the start and end indices are in the wrong order
	if(endIndex < startIndex)
	{
		tempIndex = endIndex;
		endIndex = startIndex;
		startIndex = tempIndex;
	}
		
	
	//make a copy of the input array, just in case it is also used as the output array, this allows it to be read and write to at the same time
	strncpy(tempCharArray, inputCharArray, arraySize);
	
	
	
	for(byte i = startIndex; i < endIndex; i++)
	{
		outputCharArray[j] = tempCharArray[i];
		j++;
	}
	outputCharArray[j] = '\0';
	return;
}
void CharArray::substring(char * inputCharArray, byte arraySize, byte startIndex, char * outputCharArray)
{
	
	char tempCharArray[arraySize];
		
		
	byte j = 0;	
	byte endIndex = arraySize;
	byte tempIndex = 0;
	
	//do a swap if the start and end indices are in the wrong order
	if(endIndex < startIndex)
	{
		tempIndex = endIndex;
		endIndex = startIndex;
		startIndex = tempIndex;
	}
		
		
	//make a copy of the input array, just in case it is also used as the output array, this allows it to be read and write to at the same time
	strncpy(tempCharArray, inputCharArray, arraySize);
		

	for(byte i = startIndex; i <endIndex; i++)
	{
		outputCharArray[j] = tempCharArray[i];
		j++;
	}
	outputCharArray[j] = '\0';
	return;	
}
int CharArray::stringSize(char * charArray, byte arraySize)
{
	
	for(int i = 0; i < arraySize; i++)
	{
		if(charArray[i] == '\0')
		{
			i++;//add one more for the null character
			return i;
		}
	}
	return -1;//if not found
}	



void CharArray::LTrim(char * charArray)
{
	//Reference: http://stackoverflow.com/questions/11401609/is-memmove-necessary-for-trim-function-in-c
  char *ptr;
  int len;

  for (ptr = charArray; *ptr && isspace((int)*ptr); ++ptr);

  len = strlen(ptr);
  memmove(charArray, ptr, len + 1);

}

void CharArray::RTrim(char* charArray)
{
	//Reference: http://stackoverflow.com/questions/25345598/c-implementation-to-trim-char-array-of-leading-trailing-white-space-not-workin
	int i = strlen(charArray);
	while (' ' == charArray[--i]) charArray[i] = 0;	
}

void CharArray::Trim(char* charArray)
{	
	//Reference: http://stackoverflow.com/questions/25345598/c-implementation-to-trim-char-array-of-leading-trailing-white-space-not-workin
	LTrim(charArray);
	RTrim(charArray);
	//return charArray;
}
