#include <RoverConfig.h>

/*
References:
Character array
http://www.cplusplus.com/doc/tutorial/ntcs/


*/


// the setup function runs once when you press reset or power the board
void setup() {
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	
}

// the loop function runs over and over again until power down or reset
void loop() {



	//NOTE FOR SOME REASON IF YOU DO char test1[] = "Hello World!!!!"; it won't upload
	char test1[] = "Hello World!!";//size includes the null terminatng character

	char * output;
	
	byte index = 0;


	_PC_USB_SERIAL_.println(test1);


	index = indexOf(test1, 4, 'l', sizeof(test1)/ sizeof(test1[0]));//array, start index, array size
	_PC_USB_SERIAL_.println(index);
	output = subCharArray(test1, index, sizeof(test1) / sizeof(test1[0]) - index);
	_PC_USB_SERIAL_.println(output);
	output = subCharArray(test1, index, 10, sizeof(test1) / sizeof(test1[0]) - index);//end index is 5
	_PC_USB_SERIAL_.println(output);



	index = indexOf(test1, 'l', sizeof(test1) / sizeof(test1[0]));//array, start index, array size
	_PC_USB_SERIAL_.println(index);

	output = subCharArray(test1, index, sizeof(test1) / sizeof(test1[0]) - index);
	_PC_USB_SERIAL_.println(output);

	_PC_USB_SERIAL_.println("ok");

	output = subCharArray(test1, index, 5, sizeof(test1) / sizeof(test1[0]) - index);//end index is 5
	_PC_USB_SERIAL_.println(output);
	output = subCharArray(test1, index, 6, sizeof(test1) / sizeof(test1[0]) - index);//end index is 5
	_PC_USB_SERIAL_.println(output);
	output = subCharArray(test1, index, 7, sizeof(test1) / sizeof(test1[0]) - index);//end index is 5
	_PC_USB_SERIAL_.println(output);
	output = subCharArray(test1, index, 8, sizeof(test1) / sizeof(test1[0]) - index);//end index is 5
	_PC_USB_SERIAL_.println(output);


	_PC_USB_SERIAL_.println("bye");
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
byte indexOf(char * array, byte startIndex,  char charToFind, byte arraySize)
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


//With no end index provided
char * subCharArray(char * array, byte startIndex, byte arraySize)
{
	
	
	byte size = arraySize * sizeof(char);
	char * temp;	
	temp = (char*)malloc(size);
	strncpy(temp, array + startIndex, size);//start from after the index
	return temp;

}

char * subCharArray(char * array, byte startIndex, byte endIndex, byte arraySize)
{
	//byte size = ( endIndex- startIndex) * sizeof(char);
	char * temp;
	temp = (char*)malloc(2* sizeof(char));
	
	strncpy(temp, array, 2);
	return temp;

}



/*
//With end index provided
char * subCharArray(char * array, byte startIndex, byte endIndex, byte arraySize)
{

	//Note: arraySize not used, but kept for function overloading
	if (endIndex > startIndex)
	{
		byte size = (endIndex - startIndex) * sizeof(char);//add 1 for the null charachter	

		char * temp;
		temp = (char*)malloc(size);
		byte i = startIndex;
		for (byte j = 0; j < size-1; j++)
		{
			temp[j] = array[i];
			i++;
		}
		delay(1);
		temp[size] = NULL;//null character (don't forget this or the code will keep on printing the rest of the string
		return temp;
	}
	else
	{
		//invalid, since the end index has to be greater than the start
		return NULL;
	}
}
*/