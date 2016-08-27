#include <SignalLightAssembly.h>

#include <Arduino.h>

SignalLightAssembly::SignalLightAssembly(byte frontRightPin, byte frontLeftPin, byte sideRightPin, byte sideLeftPin)
{
	this->_frontRightSignal = new DigitalLed(frontRightPin);
	this->_frontLeftSignal = new DigitalLed(frontLeftPin);
	this->_sideRightSignal = new DigitalLed(sideRightPin);
	this->_sideLeftSignal = new DigitalLed(sideLeftPin);
	//initialize them as off
	this->_frontRightSignal->ledOff();
	this->_frontLeftSignal->ledOff();
	this->_sideRightSignal->ledOff();
	this->_sideLeftSignal->ledOff();
}
SignalLightAssembly::~SignalLightAssembly()
{
	//do nothing
}

//overloaded turn on functions
void SignalLightAssembly::turnOn(byte signalLightType)
{

	switch (signalLightType)
	{
	case FRONT_RIGHT_SIGNAL_PIN:
		this->_frontRightSignal->ledOn();
		break;
	case FRONT_LEFT_SIGNAL_PIN:
		this->_frontLeftSignal->ledOn();
		break;
	case SIDE_RIGHT_SIGNAL_PIN:
		this->_sideRightSignal->ledOn();
		break;
	case SIDE_LEFT_SIGNAL_PIN:
		this->_sideLeftSignal->ledOn();
		break;
	default:
		//do nothing. invalid value.
		break;
	}//end switch
}
void SignalLightAssembly::turnOn(byte signalLightType1, byte signalLightType2)
{
	byte signalLightTypes[] = { signalLightType1, signalLightType2 };

	for (byte i = 0; i <= 1; i++)
	{
		this->turnOn(signalLightTypes[i]);//using delegation. Passing the signal light type.
	}
}
void SignalLightAssembly::turnOn(byte signalLightType1, byte signalLightType2, byte signalLightType3)
{
	byte signalLightTypes[] = { signalLightType1, signalLightType2, signalLightType3 };

	for (byte i = 0; i <= 2; i++)
	{
		this->turnOn(signalLightTypes[i]);//using delegation. Passing the signal light type.
	}
}
void SignalLightAssembly::turnOn(byte signalLightType1, byte signalLightType2, byte signalLightType3, byte signalLightType4)
{
	byte signalLightTypes[] = { signalLightType1, signalLightType2, signalLightType3, signalLightType4 };

	for (byte i = 0; i <= 3; i++)
	{
		this->turnOn(signalLightTypes[i]);//using delegation. Passing the signal light type.
	}
}


//overloaded turn off functions
void SignalLightAssembly::turnOff(byte signalLightType)
{
	switch (signalLightType)
	{
	case FRONT_RIGHT_SIGNAL_PIN:
		this->_frontRightSignal->ledOff();
		break;
	case FRONT_LEFT_SIGNAL_PIN:
		this->_frontLeftSignal->ledOff();
		break;
	case SIDE_RIGHT_SIGNAL_PIN:
		this->_sideRightSignal->ledOff();
		break;
	case SIDE_LEFT_SIGNAL_PIN:
		this->_sideLeftSignal->ledOff();
		break;
	default:
		//do nothing. invalid value.
		break;
	}//end switch
}
void SignalLightAssembly::turnOff(byte signalLightType1, byte signalLightType2)
{
	byte signalLightTypes[] = { signalLightType1, signalLightType2 };

	for (byte i = 0; i <= 1; i++)
	{
		this->turnOff(signalLightTypes[i]);//using delegation. Passing the signal light type.
	}
}
void SignalLightAssembly::turnOff(byte signalLightType1, byte signalLightType2, byte signalLightType3)
{
	byte signalLightTypes[] = { signalLightType1, signalLightType2, signalLightType3 };

	for (byte i = 0; i <= 2; i++)
	{
		this->turnOff(signalLightTypes[i]);//using delegation. Passing the signal light type.
	}
}
void SignalLightAssembly::turnOff(byte signalLightType1, byte signalLightType2, byte signalLightType3, byte signalLightType4)
{
	byte signalLightTypes[] = { signalLightType1, signalLightType2, signalLightType3, signalLightType4 };

	for (byte i = 0; i <= 3; i++)
	{
		this->turnOff(signalLightTypes[i]);//using delegation. Passing the signal light type.
	}
}

boolean SignalLightAssembly::isOn(byte signalLightType)
{
	switch (signalLightType)
	{
	case FRONT_RIGHT_SIGNAL_PIN:
		return this->_frontRightSignal->isLedOn();
		break;
	case FRONT_LEFT_SIGNAL_PIN:
		return this->_frontLeftSignal->isLedOn();
		break;
	case SIDE_RIGHT_SIGNAL_PIN:
		return this->_sideRightSignal->isLedOn();
		break;
	case SIDE_LEFT_SIGNAL_PIN:
		return this->_sideLeftSignal->isLedOn();
		break;
	default:
		//do nothing. invalid value.
		break;
	}//end switch


}

void SignalLightAssembly::reset()
{
	//software reset
	turnOff(FRONT_RIGHT_SIGNAL_PIN, FRONT_LEFT_SIGNAL_PIN, SIDE_RIGHT_SIGNAL_PIN, SIDE_LEFT_SIGNAL_PIN);
	
}