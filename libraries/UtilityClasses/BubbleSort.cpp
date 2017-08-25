#include <BubbleSort.h>


BubbleSort::BubbleSort()
{
}
BubbleSort::~BubbleSort()
{
	//do nothing
}
void BubbleSort::reset()
{
}
double BubbleSort::getMedian(double val1, double val2, double val3, double val4, double val5, double val6, double val7)
{
	double array[7] = {val1, val2, val3, val4, val5, val6, val7};
	double temp;
	boolean wasSwapped;//flag to keep track if anythhing was swapped, if so, the loop should be ran again to see if that element needs to keep moving to it's final position
	
	//"Optimizing bubble sort"
	//Reference:
	//https://en.wikipedia.org/wiki/Bubble_sort
	
	do{//keep repeating the swap loop until no elements have moved. because if an element has moved (swapped) with one element, it means it was greater than it's adjacent element, and also means it could be greater than it's new adjacent element as well
		wasSwapped = false;
		for(byte i = 1; i < 7; i++)
		{
				//sort descending (the lower element is larger]
				if( array[i] > array[i-1])//swap when
				{
					temp = array[i];
					array[i] = array[i-1];
					array[i-1] = temp;
					wasSwapped = true;
				}//end if
				
		}//end for
	}while(wasSwapped);	
	
	#ifdef _DEBUG_PRINT_BUBBLESORT_ARRAY_HORIZONTAL
		Serial.println(F("The sorted array: "));
		Serial.print(F("( "));
		for(byte i = 0; i < 7; i++)
		{
			Serial.print(array[i],4);
			if(i != 6)//print a comma after each element except for the last
			{
				Serial.print(F(", "));
			}//end if
		}//end for
		Serial.println(F(" )"));
		Serial.println();
	#endif
		
	#ifdef _DEBUG_PRINT_BUBBLESORT_ARRAY_VERTICAL
		Serial.println(F("The sorted array: "));
		
		for(byte i = 0; i < 7; i++)
		{
			Serial.println(array[i],4);
		
		}//end for
		Serial.println();
	#endif
	
	
	return array[3];//return the median value
	
}
