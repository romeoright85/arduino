//Used for AUXI - 2
//Used for NAVI - 1
//Used for COMM - 4
//Used for MAIN - 3


#include <BubbleSort.h>


//Global Variables




void setup() {


	Serial.begin(PC_USB_BAUD_RATE);

}


void loop() {
	double median;
	delay(100);
	//Example test case
	median = BubbleSort::getMedian(49.5168, 48.5164, 57.5156, 47.5136, 50.5166, 46.5196, 51.5116);//49.5168 should be the median
	Serial.print(F("The median is: "));
	Serial.println(median, 4);
	while (1);
}
