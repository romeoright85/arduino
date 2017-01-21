//CharArray.h
#ifndef _CHARARRAY_H
#define _CHARARRAY_H

#include <Arduino.h>

//Note: Use a :: (and not . or ->) to call the static method, i.e. CharArray::substring();


class CharArray {
	public:
		CharArray();//constructor
		~CharArray();//destructor
		static byte indexOf(char *, byte, char, byte);//Index Of - With start index provided (charArray, array size, char to find, start index), where array size is typically: sizeof(charArray) / sizeof(charArray[0])
		static byte indexOf(char *, byte, char);//Index Of - With no start index provided (charArray, array size, char to find), where array size is typically: sizeof(charArray) / sizeof(charArray[0])
		static char * substring(char * , byte, byte );//Substring - With no start index provided (charArray, startIndex, endIndex)
		static char * substring(char * , byte );//Substring - With no start index provided (charArray, endIndex)
				
	private:
	
};

#endif 