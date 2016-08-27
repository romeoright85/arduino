#include <FoglightAssembly.h>

#include <Arduino.h>



FoglightAssembly::FoglightAssembly(byte rightLedPin, byte leftLedPin)
{
	this->rightFogLight = new DigitalLed(rightLedPin);
	this->leftFogLight = new DigitalLed(leftLedPin);
	//initialize them as off
	rightFogLight->ledOff();
	leftFogLight->ledOff();
}
FoglightAssembly::~FoglightAssembly()
{
	//do nothing
}

//overloaded turn on functions
void FoglightAssembly::turnOn(byte foglightType)
{	
	switch (foglightType)
	{
		case RIGHT_FOG:
			rightFogLight->ledOn();
		break;
		case LEFT_FOG:
			leftFogLight->ledOn();
		break;
		default:
			//do nothing. invalid value.
		break;
	}//end switch
}
void FoglightAssembly::turnOn(byte foglightType1, byte foglightType2)
{
	
	byte fogLightTypes[] = { foglightType1, foglightType2 };
	for (byte i = 0; i <= 1; i++)
	{
		this->turnOn(fogLightTypes[i]);//using delegation. Passing the fog light type.
	}
	
}
//overloaded turn off functions
void FoglightAssembly::turnOff(byte foglightType)
{
	switch (foglightType)
	{
	case RIGHT_FOG:
		rightFogLight->ledOff();
		break;
	case LEFT_FOG:
		leftFogLight->ledOff();
		break;
	default:
		//do nothing. invalid value.
		break;
	}//end switch
}
void FoglightAssembly::turnOff(byte foglightType1, byte foglightType2)
{
	byte fogLightTypes[2] = { foglightType1, foglightType2 };
	for (byte i = 0; i <= 1; i++)
	{
		this->turnOff(fogLightTypes[i]);//using delegation. Passing the foglight type.
	}

}
boolean FoglightAssembly::isOn(byte foglightType)
{
	switch (foglightType)
	{
		case RIGHT_FOG:
			rightFogLight->isLedOn();
			break;
		case LEFT_FOG:
			leftFogLight->isLedOn();
			break;
		default:
			//do nothing. invalid value.
			break;
	}//end switch
}
void FoglightAssembly::reset()
{
	//software reset
	this->turnOff(RIGHT_FOG, LEFT_FOG);
	
}

