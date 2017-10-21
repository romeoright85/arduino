

/*
References:
Character array
http://www.cplusplus.com/doc/tutorial/ntcs/


*/


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	
}

// the loop function runs over and over again until power down or reset
void loop() {
	char test1[] = "Hello World";//size 12 (which includes the null terminatng character)

	char * output;
	byte index = 0;





	output = substringFindIndex(test1, 4, 'l', sizeof(test1));//array, start index, array size
	Serial.println(output);
	output = substringFindIndex(test1, 3, 'l', sizeof(test1));//array, start index, array size
	Serial.println(output);
	//No start index provided
	output = substringFindIndex(test1, 'l', sizeof(test1));//array, start index, array size
	Serial.println(output);



	while (1);//end the program
}

//With no start index provided
char * substringFindIndex(char * array, char charToFind, byte arraySize)
{
	delay(1);//required else the function delegation won't work right for some reason
	substringFindIndex(array, 0, charToFind, arraySize);
}

//With start index provided
char * substringFindIndex(char * array, byte startIndex,  char charToFind, byte arraySize)
{
	
	char * temp;
	byte size;

	for (byte i = startIndex; i <= arraySize; i++)
	{
		
		if (array[i] == charToFind)
		{
		
			size = arraySize - i;
			temp = (char*)realloc(temp, size * sizeof(char));//copy over from the original array to the new array based on the remaing characters after the index
			memcpy(temp, array + i, size);//start from after the index
			return temp;
					

		}
	}
	return NULL;
















}
