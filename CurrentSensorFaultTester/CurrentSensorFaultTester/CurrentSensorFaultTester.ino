//Used for AUXI - 2

#include <CurrentSensorFault.h>


//Global Variables

//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast

#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ Serial2
#else
	#define _SERIAL_DEBUG_CHANNEL_ Serial
#endif


//All the current sensors share one fault reset pin
//7.2V 25A PreSwitch
CurrentSensorFault * currentSensorFault = new CurrentSensorFault(CURRENT_FAULT_1_7D2V_25A_PRESW_PIN, CURRENT_FAULT_2_3D3V_12D5A_SW_PIN, CURRENT_FAULT_3_MCTRLRCH1_12D5A_PIN, CURRENT_FAULT_4_MCTRLRCH2_12D5A_PIN, CURRENT_FAULT_5_7D2_12D5A_SW_PIN, CURRENT_SENSOR_RESET_PIN);


RoverReset * resetArray[] = {
	currentSensorFault
};


void setup() {
	
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	_MAIN_SERIAL_.begin(MAIN_BAUD_RATE);//Use to talk between MAIN and AUXI
}


void loop() {
		
	boolean * faultedCurrentSensors;

	//If any of the current sensors has faulted, reset them all
	if (currentSensorFault->anyFaulted())
	{
		faultedCurrentSensors = currentSensorFault->getFaultedSensors();
		for (byte i = 0; i < 5; i++)
		{
			if (faultedCurrentSensors[i])
			{
				_SERIAL_DEBUG_CHANNEL_.print(F("Current Sensor "));
				_SERIAL_DEBUG_CHANNEL_.print(i + 1);//Print the Current Sensor Number (do i + 1 since the index starts at 0 but the current sensors are from 1-5)
				_SERIAL_DEBUG_CHANNEL_.println(F(" At Fault"));	
			}
		}
		currentSensorFault->resetCurrentSensors();
		_SERIAL_DEBUG_CHANNEL_.println(F("Current Sensors Was Reset"));
	}
	else
	{
		_SERIAL_DEBUG_CHANNEL_.println(F("No Current Sensors Faulted"));
	}


	for (unsigned int i = 0; i < 65000; i++)
	{
		//create a software delay
	}

	delay(1000);

}
