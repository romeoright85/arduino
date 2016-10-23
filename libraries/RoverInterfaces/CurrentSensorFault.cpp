#include <CurrentSensorFault.h>


CurrentSensorFault::CurrentSensorFault(byte currentSensor1_FaultPin, byte currentSensor2_FaultPin, byte currentSensor3_FaultPin, byte currentSensor4_FaultPin, byte currentSensor5_FaultPin, byte currentSensors_ResetPin)
{
	//Assign Pins
	//Current Fault Pins
	this->currentSensorFaultPins[0] = currentSensor1_FaultPin;
	this->currentSensorFaultPins[1] = currentSensor2_FaultPin;
	this->currentSensorFaultPins[2] = currentSensor3_FaultPin;
	this->currentSensorFaultPins[3] = currentSensor4_FaultPin;
	this->currentSensorFaultPins[4] = currentSensor5_FaultPin;
	//Reset Pin	
	this->currentSensors_ResetPin = currentSensors_ResetPin;
	
	//Setup pins
	pinMode(this->currentSensorFaultPins[0], INPUT);
	pinMode(this->currentSensorFaultPins[1], INPUT);
	pinMode(this->currentSensorFaultPins[2], INPUT);
	pinMode(this->currentSensorFaultPins[3], INPUT);
	pinMode(this->currentSensorFaultPins[4], INPUT);
	pinMode(this->currentSensors_ResetPin, OUTPUT);
		
	//Initialize
	this->reset();
}
CurrentSensorFault::~CurrentSensorFault()
{
	//do nothing
}
void CurrentSensorFault::reset()
{
	//Since delay() doesn't work in the global space and the constructor of this object may be called globally, then the resetCurrentSensors() shouldn't be called by the constructor (since you may want to create this object globally)
	this->clearFaultedCurrentSensors();
}
boolean CurrentSensorFault::anyFaulted()
{
	//initialize the flags before the loop
	boolean anyFaultedCurrentSensors = false;
	
	//Initialize/clear the faulted current sensor flags
	this->clearFaultedCurrentSensors();
	
	for (byte i = 0; i < 5; i++)
	{		
		//Read the current sensor fault pin (it is active low)
		if(!digitalRead(this->currentSensorFaultPins[i]))
		{
			this->faultedCurrentSensors[i] = true;
			anyFaultedCurrentSensors = true;
		}					
	}	
	return anyFaultedCurrentSensors;
}

boolean * CurrentSensorFault::getFaultedSensors()
{
	return this->faultedCurrentSensors;
}
void CurrentSensorFault::resetCurrentSensors()
{
	
	//Toggle the current reset pin
	//Initialize to turn Vcc on (active low)
	digitalWrite(this->currentSensors_ResetPin, LOW);
	delay(10);
	//Turn off Vcc (active low)
	digitalWrite(this->currentSensors_ResetPin, HIGH);
	delay(10);
	//Turn on Vcc again (active low)
	digitalWrite(this->currentSensors_ResetPin, LOW);
	
	//Clear the faulted current sensor flags
	this->clearFaultedCurrentSensors();
	
	
}
void CurrentSensorFault::clearFaultedCurrentSensors()
{
	//Clear the faulted current sensor flags
	for (byte i = 0; i < 5; i++)
	{
		this->faultedCurrentSensors[i] = false;
	}
}