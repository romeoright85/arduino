#include <DataType.h>
//Written to test the charsToByte functionality in DataType.h


#include <RoverConfig.h>


//Global Variables



void setup() {

	Serial.begin(PC_USB_BAUD_RATE);

}


void loop() {
	byte tempByte;	

	//test case 1
	char testCharArray1[] = "123";
	tempByte = DataType::charsToByte(testCharArray1);
	tempByte = tempByte + 1;
	Serial.println(tempByte);//should be 124


	//test case 2
	char testCharArray2[] = "256";
	tempByte = DataType::charsToByte(testCharArray2);
	Serial.println(tempByte);//should be 0, since the value is greater than 255 after it's converted

	 //test case 3
	char testCharArray3[] = "-1";
	tempByte = DataType::charsToByte(testCharArray3);
	Serial.println(tempByte);//should be 0, since the value is less than0 after it's converted

	 //test case 4
	char testCharArray4[] = "0";
	tempByte = DataType::charsToByte(testCharArray4);
	Serial.println(tempByte);//should be 0


	//test case 5
	char testCharArray5[] = "255";
	tempByte = DataType::charsToByte(testCharArray5);
	Serial.println(tempByte);//should be 255



	//test case 6
	char testCharArray6[] = "255";
	tempByte = DataType::charsToByte(testCharArray6);
	tempByte = tempByte + 10;
	Serial.println(tempByte);//should be 9, since when the byte overflows it wraps back around. It won't go to zero since the data was added after the conversion.


	



	while (1);
}
