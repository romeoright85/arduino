//Used for any Arduino. To see if sizeof(charArray) vs sizeof(charArray)/sizeof(charArray[0]) matters
//Result: Either one yields the same thing for regular variables (non pointers) but for objects you have to divide by the element. And for char pointers, you have to pass the length in directly. You can't get the size of a char pointer.
//Reference: https://stackoverflow.com/questions/399003/is-the-sizeofsome-pointer-always-equal-to-four
//Size of (object) pointers are always two bytes.
//Reference: https://stackoverflow.com/questions/15774534/c-how-to-get-the-length-of-a-pointer-array
//"If the char * is 0 - terminated, you can use strlen. (but strlen doesn't count the \0 so you have to add 1). Otherwise, there is no way to determine that information."
//Reference: https://stackoverflow.com/questions/21022644/how-to-get-the-real-and-total-length-of-char-char-array


#include <RoverConfig.h>
#include <RoverData.h>

//Global Variables

RoverData * roverData1 = new RoverData();
RoverData * roverData2 = new RoverData();
RoverData * roverData3 = new RoverData();


void setup() {

	Serial.begin(PC_USB_BAUD_RATE);

}


void loop() {
	char testString[] = "Hello World";//The result is 12 since it includes a null string terminator /0
	Serial.print("sizeof(testString): ");
	Serial.println(sizeof(testString));
	Serial.print("sizeof(testString)/sizeof(testString[0]): ");
	Serial.println(sizeof(testString)/sizeof(testString[0]));
	

	char * charArrayPointer = testString;//The result is 2 since it's a char pointer and all pointers are size 2. Even when you divide by [0] you can't get the size.
	Serial.print("sizeof(charArrayPointer): ");
	Serial.println(sizeof(charArrayPointer));
	Serial.print("sizeof(charArrayPointer)/sizeof(charArrayPointer[0]): ");
	Serial.println(sizeof(charArrayPointer) / sizeof(charArrayPointer[0]));
	Serial.print("strlen(charArrayPointer)+1: ");
	Serial.println(strlen(charArrayPointer)+1);//since strlen doesn't count the \0 you have to add 1




	byte testByteArray[] = { 1,2,3,4,5 };//The result is 5
	Serial.print("sizeof(testByteArray): ");
	Serial.println(sizeof(testByteArray));
	Serial.print("sizeof(testByteArray)/sizeof(testByteArray[0]): ");
	Serial.println(sizeof(testByteArray) / sizeof(testByteArray[0]));

	RoverData * testObjectArray[] = { //The result should be 3 but it gets 2 bytes per an object, so if you don't divide, you will get 6
		roverData1,
		roverData2,
		roverData3

	};


	Serial.print("sizeof(testObjectArray): ");
	Serial.println(sizeof(testObjectArray));
	Serial.print("sizeof(testObjectArray)/sizeof(testObjectArray[0]): ");
	Serial.println(sizeof(testObjectArray) / sizeof(testObjectArray[0]));

	while (1);
}


/*
sizeof(testString): 12
sizeof(testString)/sizeof(testString[0]: 12
sizeof(testByteArray): 5
sizeof(testByteArray)/sizeof(testByteArray[0]: 5
sizeof(testObjectArray): 6
sizeof(testObjectArray)/sizeof(testObjectArray[0]: 3
*/