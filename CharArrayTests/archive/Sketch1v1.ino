

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
	char test2[] = "Good night world!";
	char * output;
	byte index = 0;

	byte size = sizeof(test1) / sizeof(test1[0]);//size 12
	Serial.println(size);
	index = substringFindIndex(test1, 4, 'l', sizeof(test1)/ sizeof(test1[0]));
	Serial.println(index);
	size = size - index;
	Serial.println(size);
	
	output = (char*)realloc(output, size * sizeof(char));
	memcpy(output, test1 + index, size);

	Serial.println(output);

	//index = substringFindIndex(test2, 'n', (unsigned)strlen(test2));
	//Serial.println(index);
	
	/*

	// Read each command pair 
	char* command = strtok(test1, " ");
	Serial.println(command);
	while (command != 0)
	{
		command = strtok(NULL, " ");
		Serial.println(command);	
	}

	*/







	//Serial.println("Bye");
	while (1);//end the program
}

//With no start index provided
byte substringFindIndex(char * array, char charToFind, byte arraySize)
{
//	Serial.println("hi2");//DEBUG
	delay(1);//a delay is needed, else for some reason it won't work
	substringFindIndex(array, 0, charToFind, arraySize);	
}

//With start index provided
byte substringFindIndex(char * array, byte startIndex,  char charToFind, byte arraySize)
{
	//Serial.println("hi1");//DEBUG
	//Serial.println(startIndex);//DEBUG
	//Serial.println(charToFind);//DEBUG
	//Serial.println(arraySize);//DEBUG
	
	for (byte i = startIndex; i <= arraySize; i++)
	{
		//Serial.println(array[i]);//DEBUG
		//Serial.println("hi2");//DEBUG
		if (array[i] == charToFind)
		{
			return i;
		}
	}
	return -1;
}
