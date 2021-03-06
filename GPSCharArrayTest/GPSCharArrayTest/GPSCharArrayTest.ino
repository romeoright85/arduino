#include <CharArray.h>
#include <RoverConfig.h>


// the setup function runs once when you press reset or power the board
void setup() {
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);

}

// the loop function runs over and over again until power down or reset
void loop() {
			
	char gpsData[] = "GPGGA,142103.400,3916.2242,N,07636.6542,W,1,3,3.90,183.6,M,-33.6,M,,*6B";
	char outputCharArray[75];
	byte arraySize = sizeof(gpsData);

	int startIndex = 0;
	int endIndex = 0;
	byte test = 1;

	_PC_USB_SERIAL_.println(gpsData);

	endIndex = CharArray::indexOf(gpsData, arraySize, ',');
	_PC_USB_SERIAL_.print(F("endIndex: "));
	_PC_USB_SERIAL_.println(endIndex);

	if (endIndex >= 0)
	{
		 CharArray::substring(gpsData, arraySize, startIndex, endIndex, outputCharArray);		 
		 _PC_USB_SERIAL_.println(outputCharArray);
		 CharArray::substring(gpsData, arraySize, startIndex +7, outputCharArray);//where 7 was chosen aribitrarily just to get a different result than the one above to test the no start index specified function
		 _PC_USB_SERIAL_.println(outputCharArray);
		 CharArray::substring(gpsData, arraySize, startIndex + 2, gpsData);//where 7 was chosen aribitrarily just to get a different result than the one above to test the no start index specified function
		 _PC_USB_SERIAL_.println(gpsData);
	}
	


	

	_PC_USB_SERIAL_.println("bye");
	
	while (1);//end the program
}
