//DataType.h
#ifndef _DATATYPE_H
#define _DATATYPE_H

#include <Arduino.h>


class DataType {
public:
	DataType();//constructor
	~DataType();//destructor
	
	//Note: You may need to use delayMicroseconds(1) with your code after calling this class if it some reason it's acting up and not functioning correctly.
	static char byteToHex(byte);//converts bytes with range from 0 to 15 to the corresponding hexadecimal character	
	static char byteToChar(byte);//converts bytes with range from 0 to 9 to a character array in the corresponding decimal format (from 0 to 9)
	static byte byteToChars(byte, char *, byte);//(byte num value, output char array, array size) converts bytes with range from 0 to 255 to a character array in the corresponding decimal format (from 0 to 255). The output is passed by reference. Returns 1 (true) for success and 0 (false) for error. Typically the output char array should be size 4 since the byte converted value can have up to three characters long and 1 null terminator
	
	static byte charsToByte(char *);//(input char array) returns byte (with range 0 to 255)
	static byte charToByte(char);//(input char) returns byte (with range 0 to 9)
	
	
	
private:
	//Non-SW Resettable
	//SW Resettable
};

#endif 