#include <RoverConfig.h>
#define _COMMAND_CREATION_DEFINITIONS
#include <RoverCommandDefs.h>

//Global Variables


byte auto_test_data_array[] = {
	CMD_TAG_MTR_PWR_STATUS,
	CMD_TAG_ENC_STATUS_MID_LEFT,
	CMD_TAG_ENC_STATUS_MID_RIGHT
};// add more as needed	





byte auto_test_data_cnt = 0; //data counter, can just be byte instead of unsigned int since there aren't that many elements

void setup() {


	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	_PC_USB_SERIAL_.flush();//waits for any outgoing serial data to complete
	delay(50);

}


void loop() {
	
	
	_PC_USB_SERIAL_.println(F("====="));


	_PC_USB_SERIAL_.print(F("Size: "));
	_PC_USB_SERIAL_.println(sizeof(auto_test_data_array));


	delay(100);

	
	_PC_USB_SERIAL_.print(F("Data: "));
	_PC_USB_SERIAL_.println(auto_test_data_array[auto_test_data_cnt]);
	
	auto_test_data_cnt++;

	if (auto_test_data_cnt >= sizeof(auto_test_data_array))
	{
		auto_test_data_cnt = 0;
	}//end if
	
	_PC_USB_SERIAL_.print(F("Cnt: "));
	_PC_USB_SERIAL_.println(auto_test_data_cnt);
	delay(500);
}
