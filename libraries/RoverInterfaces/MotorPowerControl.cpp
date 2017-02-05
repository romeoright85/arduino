#include <MotorPowerControl.h>


MotorPowerControl::MotorPowerControl(byte motorMosfetPin, byte motorEnableStatusPin)
{
	
	//Assign variables
	this->_motorMosfetPin = motorMosfetPin;
	this->_motorEnableStatusPin = motorEnableStatusPin;
	
	//Setup pins
	pinMode(this->_motorMosfetPin, OUTPUT);
	pinMode(this->_motorEnableStatusPin, INPUT);
	
	//Initialize
	this->reset();	
	
}
MotorPowerControl::~MotorPowerControl()
{
	//do nothing
}
void MotorPowerControl::reset()
{
	this->setMotorPower(MTR_DISABLED);
}
void MotorPowerControl::setMotorPower(byte motorEnable)
{
	if(motorEnable==MTR_ENABLED)
	{
		digitalWrite(this->_motorMosfetPin, HIGH);
	}
	else//motorEnable==MTR_DISABLED
	{
		digitalWrite(this->_motorMosfetPin, LOW);
	}
}
boolean MotorPowerControl::motorIsOn()
{
	
	byte isMotorOn;
	isMotorOn = digitalRead(this->_motorEnableStatusPin);
	if(isMotorOn==HIGH)
	{
		return true;
	}
	else//isMotorOn==LOW
	{
		return false;
	}
}




