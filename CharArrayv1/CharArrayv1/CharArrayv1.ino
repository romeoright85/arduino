

/*
References:
Character array
http://www.cplusplus.com/doc/tutorial/ntcs/


*/


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(PC_USB_BAUD_RATE);

}

// the loop function runs over and over again until power down or reset
void loop() {



	//NOTE FOR SOME REASON IF YOU DO char test1[] = "Hello World!!!!"; it won't upload
	char test1[] = "Hello World. How are you?!!";//size includes the null terminatng character

	char * output;

	byte index = 0;


	Serial.println(test1);


	index = indexOf(test1, 1, 'a', sizeof(test1) / sizeof(test1[0]));//array, start index, array size
	Serial.println(index);
	output = subCharArray(test1, index, index+2);
	Serial.println(output);
	Serial.println("bye");
	free(output);
	while (1);//end the program
}

//With no start index provided
byte indexOf(char * array, char charToFind, byte arraySize)
{
	//add delay else the function delegation doesn't work properly
	delay(1);
	return indexOf(array, 0, charToFind, arraySize);
}

//With start index provided
byte indexOf(char * array, byte startIndex, char charToFind, byte arraySize)
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




char * subCharArray(char * array, byte startIndex, byte endIndex)
{
	byte size = endIndex - startIndex;
	char * temp;
	temp = (char*)malloc(size * sizeof(char));
	strncpy(temp, array + startIndex, (size-1)* sizeof(char));
	temp[size * sizeof(char)] = 0;
	return temp;

}


