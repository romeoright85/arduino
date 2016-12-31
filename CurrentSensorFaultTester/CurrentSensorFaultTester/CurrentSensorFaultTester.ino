//Used for AUXI - 2

#include <CurrentSensorFault.h>


//Global Variables


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
	
	Serial.begin(9600);
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
				Serial.print(F("Current Sensor "));
				Serial.print(i + 1);//Print the Current Sensor Number (do i + 1 since the index starts at 0 but the current sensors are from 1-5)
				Serial.println(F(" At Fault"));
			}
		}
		currentSensorFault->resetCurrentSensors();
		Serial.println(F("Current Sensors Was Reset"));
	}
	else
	{
		Serial.println(F("No Current Sensors Faulted"));
	}


	for (unsigned int i = 0; i < 65000; i++)
	{
		//create a software delay
	}

	delay(1000);

}
