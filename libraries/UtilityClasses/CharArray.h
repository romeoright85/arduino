//CharArray.h
#ifndef _CHARARRAY_H
#define _CHARARRAY_H

#include <Arduino.h>

//Note: Use a :: (and not . or ->) to call the static method, i.e. CharArray::substring();


//Uncomment to see debug output
//#define _DEBUG_PROBE_INDEXOF_


class CharArray {
	public:
		CharArray();//constructor
		~CharArray();//destructor
		static int indexOf(char *, byte, char, byte);//Index Of - With start index provided (charArray, array size, char to find, start index), where array size is typically: sizeof(charArray) / sizeof(charArray[0])
		static int indexOf(char *, byte, char);//Index Of - With no start index provided (charArray, array size, char to find), where array size is typically: sizeof(charArray) / sizeof(charArray[0])
				
				
		//Note: When using char array substrings, make sure the buffer size is 1 more bigger than the characters as you need room for the null terminating character
		static void substring(char *, byte, byte, byte, char *);//With End Index (input char array, string size, start index, end index, output char array). Note you should use stringSize() for the string size as it's not just the array size but the size to the null termination character. Note: Start index can be as small as 0. The end index is not inclusive. So for example start 0 and end 2 means it grabs elements 0 and 1, and stops at element 2 and does not include it.
		static void substring(char *, byte, byte, char *);//With No End Index, goes to the end of the array or to the terminating character (input char array, string size, start index, output char array). Note you should use stringSize() for the string size as it's not just the array size but the size to the null termination character. Note: Start index can be as small as 0.
		
		static void LTrim(char *);//(char array) trim white spaces on the left
		static void RTrim(char *);//(char array) trim white spaces on the right.
		static void Trim(char *);//(char array) trim white spaces on both sides
		
		
		static int stringSize(char *, byte );//(charArray, array size) finds the number of characters until it reaches the first null character. The count includes the null character in the count. Note: To get the array size, use "sizeof(array)/sizeof(array[0])" where the array is your array name.
		
	private:
	
};

#endif 