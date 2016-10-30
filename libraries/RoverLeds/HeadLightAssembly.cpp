#include <HeadLightAssembly.h>


HeadLightAssembly::HeadLightAssembly(byte highBeamPin, byte signalPin, byte fogPin)
{
	
	this->_highBeam = new DigitalLed(highBeamPin);
	this->_signal = new DigitalLed(signalPin);
	this->_fog = new DigitalLed(fogPin);
		
	//initialize them as off
	this->reset();		
	
}
HeadLightAssembly::~HeadLightAssembly()
{
	//do nothing
}
void HeadLightAssembly::reset()
{
	//software reset
	this->turnOff(HIGHBEAM_HEADLIGHT, SIGNAL_HEADLIGHT, FOG_HEADLIGHT);
}






//overloaded turn on functions
void HeadLightAssembly::turnOn(byte headLightType)
{

	switch (headLightType)
	{
	case HIGHBEAM_HEADLIGHT:
		this->_highBeam->ledOn();
		break;
	case SIGNAL_HEADLIGHT:
		this->_signal->ledOn();
		break;
	case FOG_HEADLIGHT:
		this->_fog->ledOn();
		break;	
	default:
		//do nothing. invalid value.
		break;
	}//end switch
}
void HeadLightAssembly::turnOn(byte headLightType1, byte headLightType2)
{
	byte headLightTypes[] = { headLightType1, headLightType2 };

	for (byte i = 0; i <  sizeof( headLightTypes)/sizeof(headLightTypes[0]); i++)
	{
		this->turnOn(headLightTypes[i]);//using delegation. Passing the headlight type.
	}
}
void HeadLightAssembly::turnOn(byte headLightType1, byte headLightType2, byte headLightType3)
{
	byte headLightTypes[] = { headLightType1, headLightType2, headLightType3 };

	for (byte i = 0; i <= 2; i++)
	{
		this->turnOn(headLightTypes[i]);//using delegation. Passing the headlight type.
	}
}




//overloaded turn on functions
void HeadLightAssembly::turnOff(byte headLightType)
{

	switch (headLightType)
	{
	case HIGHBEAM_HEADLIGHT:
		this->_highBeam->ledOff();
		break;
	case SIGNAL_HEADLIGHT:
		this->_signal->ledOff();
		break;
	case FOG_HEADLIGHT:
		this->_fog->ledOff();
		break;	
	default:
		//do nothing. invalid value.
		break;
	}//end switch
}
void HeadLightAssembly::turnOff(byte headLightType1, byte headLightType2)
{
	byte headLightTypes[] = { headLightType1, headLightType2 };

	for (byte i = 0; i <  sizeof( headLightTypes)/sizeof(headLightTypes[0]); i++)
	{
		this->turnOff(headLightTypes[i]);//using delegation. Passing the headlight type.
	}
}
void HeadLightAssembly::turnOff(byte headLightType1, byte headLightType2, byte headLightType3)
{
	byte headLightTypes[] = { headLightType1, headLightType2, headLightType3 };

	for (byte i = 0; i <= 2; i++)
	{
		this->turnOff(headLightTypes[i]);//using delegation. Passing the headlight type.
	}
}
boolean HeadLightAssembly::isOn(byte headLightType)
{
	switch (headLightType)
	{
	case HIGHBEAM_HEADLIGHT:
		return this->_highBeam->isLedOn();
		break;
	case SIGNAL_HEADLIGHT:
		return this->_signal->isLedOn();
		break;
	case FOG_HEADLIGHT:
		return this->_fog->isLedOn();
		break;
	default:
		//do nothing. invalid value.
		break;
	}//end switch
}