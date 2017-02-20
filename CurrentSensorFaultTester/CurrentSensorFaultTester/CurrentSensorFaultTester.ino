//Used for AUXI - 2

#include <CurrentSensorFault.h>


//Global Variables

//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast


//All the current sensors share one fault reset pin
//7.2V 25A PreSwitch
CurrentSensorFault * currentSensorFault = new CurrentSensorFault(CURRENT_FAULT_1_7D2V_25A_PRESW_PIN, CURRENT_FAULT_2_3D3V_12D4A_SW_PIN, CURRENT_FAULT_3_MCTRLRCH1_12D5A_PIN, CURRENT_FAULT_4_MCTRLRCH2_12D5A_PIN, CURRENT_FAULT_5_7D2_12D5A_SW_PIN, CURRENT_SENSOR_RESET_PIN);


RoverReset * resetArray[] = {
	currentSensorFault
};


void setup() {
	
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	
	Serial.begin(PC_USB_BAUD_RATE);
	Serial.begin(MAIN_BAUD_RATE);
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
			#ifdef _DEBUG_COMM_BROADCAST
				Serial2.print(F("Current Sensor "));
				Serial2.print(i + 1);//Print the Current Sensor Number (do i + 1 since the index starts at 0 but the current sensors are from 1-5)
				Serial2.println(F(" At Fault"));
			#else
				Serial.print(F("Current Sensor "));
				Serial.print(i + 1);//Print the Current Sensor Number (do i + 1 since the index starts at 0 but the current sensors are from 1-5)
				Serial.println(F(" At Fault"));
			#endif		
			}
		}
		currentSensorFault->resetCurrentSensors();
	#ifdef _DEBUG_COMM_BROADCAST
		Serial2.println(F("Current Sensors Was Reset"));
	#else
		Serial.println(F("Current Sensors Was Reset"));
	#endif
	}
	else
	{
	#ifdef _DEBUG_COMM_BROADCAST
		Serial2.println(F("No Current Sensors Faulted"));
	#else
		Serial.println(F("No Current Sensors Faulted"));
	#endif	
	}


	for (unsigned int i = 0; i < 65000; i++)
	{
		//create a software delay
	}

	delay(1000);

}
