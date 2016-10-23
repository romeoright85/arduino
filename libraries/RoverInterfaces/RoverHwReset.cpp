#include <RoverHwReset.h>


RoverHwReset::RoverHwReset(byte hwResetPin)
{
	
	
	//Assign pins
	this->_hwResetPin = hwResetPin;
	
		
	//Setup pins
	pinMode(this->_hwResetPin, OUTPUT);		
	
	//Initialize
	this->reset();//nothing really happens. Just keeping the template format going.
	
}
RoverHwReset::~RoverHwReset()
{
	//do nothing
}

void RoverHwReset::reset()
{
	//do nothing, only do a hw reset when a command is sent to do so. Not on power on startup.
}

void RoverHwReset::performHwReset()
{
	//Note: For Arduino the HW Reset pin is active low		
	
	//Toggle the hardware reset pin
	//Initialize state, DISABLE the HW reset (active low)
	digitalWrite(this->_hwResetPin, HIGH);
	delay(10);
	//ENABLE the HW reset (active low)
	digitalWrite(this->_hwResetPin, LOW);
	delay(10);
	//DISABLE the HW reset (active low)
	digitalWrite(this->_hwResetPin, HIGH);
	Serial.println(F("Arduino Reset"));	

}