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
				
		static void substring(char *, byte, byte, byte, char *);//With End Index (input char array, array size, start index, end index, output char array)
		static void substring(char *, byte, byte, char *);//With No End Index, goes to the end of the array or to the terminating character (input char array, array size, start index, output char array)
		
		static void LTrim(char *);//(char array) trim white spaces on the left
		static void RTrim(char *);//(char array) trim white spaces on the right.
		static void Trim(char *);//(char array) trim white spaces on both sides
		
		
		static int stringSize(char *, byte );//(charArray, array size) finds the number of characters until it reaches the first null character. The count includes the null character in the count.
		
	private:
	
};

#endif 