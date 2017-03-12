#include <TemplateClassPractice.h>


//Global Variables
template <typename T> T getMin(T a, T b);

TemplateClassPractice<int> * intTemplate;
TemplateClassPractice<double> * doubleTemplate;

template<class T> class foobar;



void setup() {

	Serial.begin(PC_USB_BAUD_RATE);

}


void loop() {


	//int template
	intTemplate = new TemplateClassPractice<int>(1, 2);
	Serial.println(F("Get Max of 1 and 2:"));
	Serial.println(intTemplate->getMax());
	delete intTemplate;


	doubleTemplate = new TemplateClassPractice<double>(4.0, 3.0);
	Serial.println(F("Get Max of 4 and 3:"));
	Serial.println(doubleTemplate->getMax());	
	delete doubleTemplate;
	
	Serial.println(F("Get Min of 1 and 4:"));
	Serial.println(getMin<int>(1, 4));


	Serial.println(F("Get Min of 3 and 2:"));
	Serial.println(getMin<double>(3.0, 2.0));



	while (1);
}

template <typename T> T getMin(T a, T b) {
	return (a<b ? a : b);
}