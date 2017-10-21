#include <TailLightAssembly.h>

TailLightAssembly::TailLightAssembly( byte redLed1Pin, byte redLed2Pin, byte redLed3Pin, byte redLed4Pin, byte redLed5Pin, byte whiteLedPin)
{
	this->_redLed1 = new DigitalLed(redLed1Pin);
	this->_redLed2 = new DigitalLed(redLed2Pin);
	this->_redLed3 = new DigitalLed(redLed3Pin);
	this->_redLed4 = new DigitalLed(redLed4Pin);	
	this->_redLed5 = new DigitalLed(redLed5Pin);
	this->_whiteLed = new DigitalLed(whiteLedPin);	
}
TailLightAssembly::~TailLightAssembly()
{
	//do nothing
}
void TailLightAssembly::reset()
{
}
void TailLightAssembly::turnOn(byte taillightLightType)
{

	switch (taillightLightType)
	{
		case RED1_TAILLIGHT:
			this->_redLed1->ledOn();
			break;
		case RED2_TAILLIGHT:
			this->_redLed2->ledOn();
			break;
		case RED3_TAILLIGHT:
			this->_redLed3->ledOn();
			break;
		case RED4_TAILLIGHT:
			this->_redLed4->ledOn();
			break;			
		case RED5_TAILLIGHT:
			this->_redLed5->ledOn();
			break;
		case WHITE_TAILLIGHT:
			this->_whiteLed->ledOn();
			break;		
		default:
			//do nothing. invalid value.
			break;
	}//end switch
}
void TailLightAssembly::turnOn(byte taillightLightType1, byte taillightLightType2)
{
	byte tailLightTypes[] = { taillightLightType1, taillightLightType2 };

	for (byte i = 0; i <  sizeof(tailLightTypes); i++)
	{
		this->turnOn(tailLightTypes[i]);//using delegation. Passing the tail light type.
	}
}
void TailLightAssembly::turnOn(byte taillightLightType1, byte taillightLightType2, byte taillightLightType3)
{
	byte tailLightTypes[] = { taillightLightType1, taillightLightType2, taillightLightType3 };

	for (byte i = 0; i <  sizeof(tailLightTypes); i++)
	{
		this->turnOn(tailLightTypes[i]);//using delegation. Passing the tail light type.
	}
}
void TailLightAssembly::turnOn(byte taillightLightType1, byte taillightLightType2, byte taillightLightType3, byte taillightLightType4)
{
	byte tailLightTypes[] = { taillightLightType1, taillightLightType2, taillightLightType3, taillightLightType4  };

	for (byte i = 0; i <  sizeof(tailLightTypes); i++)
	{
		this->turnOn(tailLightTypes[i]);//using delegation. Passing the tail light type.
	}
}
void TailLightAssembly::turnOn(byte taillightLightType1, byte taillightLightType2, byte taillightLightType3, byte taillightLightType4, byte taillightLightType5)
{
	byte tailLightTypes[] = { taillightLightType1, taillightLightType2, taillightLightType3, taillightLightType4, taillightLightType5  };

	for (byte i = 0; i <  sizeof(tailLightTypes); i++)
	{
		this->turnOn(tailLightTypes[i]);//using delegation. Passing the tail light type.
	}
}
void TailLightAssembly::turnOn(byte taillightLightType1, byte taillightLightType2, byte taillightLightType3, byte taillightLightType4, byte taillightLightType5, byte taillightLightType6)
{
	byte tailLightTypes[] = { taillightLightType1, taillightLightType2, taillightLightType3, taillightLightType4, taillightLightType5, taillightLightType6 };

	for (byte i = 0; i <  sizeof(tailLightTypes); i++)
	{
		this->turnOn(tailLightTypes[i]);//using delegation. Passing the tail light type.
	}
}
void TailLightAssembly::turnOff(byte taillightLightType)
{

	switch (taillightLightType)
	{
		case RED1_TAILLIGHT:
			this->_redLed1->ledOff();
			break;
		case RED2_TAILLIGHT:
			this->_redLed2->ledOff();
			break;
		case RED3_TAILLIGHT:
			this->_redLed3->ledOff();
			break;
		case RED4_TAILLIGHT:
			this->_redLed4->ledOff();
			break;			
		case RED5_TAILLIGHT:
			this->_redLed5->ledOff();
			break;
		case WHITE_TAILLIGHT:
			this->_whiteLed->ledOff();
			break;		
		default:
			//do nothing. invalid value.
			break;
	}//end switch
}
void TailLightAssembly::turnOff(byte taillightLightType1, byte taillightLightType2)
{
	byte tailLightTypes[] = { taillightLightType1, taillightLightType2 };

	for (byte i = 0; i <  sizeof(tailLightTypes); i++)
	{
		this->turnOff(tailLightTypes[i]);//using delegation. Passing the tail light type.
	}
}
void TailLightAssembly::turnOff(byte taillightLightType1, byte taillightLightType2, byte taillightLightType3)
{
	byte tailLightTypes[] = { taillightLightType1, taillightLightType2, taillightLightType3 };

	for (byte i = 0; i <  sizeof(tailLightTypes); i++)
	{
		this->turnOff(tailLightTypes[i]);//using delegation. Passing the tail light type.
	}
}
void TailLightAssembly::turnOff(byte taillightLightType1, byte taillightLightType2, byte taillightLightType3, byte taillightLightType4)
{
	byte tailLightTypes[] = { taillightLightType1, taillightLightType2, taillightLightType3, taillightLightType4  };

	for (byte i = 0; i <  sizeof(tailLightTypes); i++)
	{
		this->turnOff(tailLightTypes[i]);//using delegation. Passing the tail light type.
	}
}
void TailLightAssembly::turnOff(byte taillightLightType1, byte taillightLightType2, byte taillightLightType3, byte taillightLightType4, byte taillightLightType5)
{
	byte tailLightTypes[] = { taillightLightType1, taillightLightType2, taillightLightType3, taillightLightType4, taillightLightType5  };

	for (byte i = 0; i <  sizeof(tailLightTypes); i++)
	{
		this->turnOff(tailLightTypes[i]);//using delegation. Passing the tail light type.
	}
}
void TailLightAssembly::turnOff(byte taillightLightType1, byte taillightLightType2, byte taillightLightType3, byte taillightLightType4, byte taillightLightType5, byte taillightLightType6)
{
	byte tailLightTypes[] = { taillightLightType1, taillightLightType2, taillightLightType3, taillightLightType4, taillightLightType5, taillightLightType6 };

	for (byte i = 0; i <  sizeof(tailLightTypes); i++)
	{
		this->turnOff(tailLightTypes[i]);//using delegation. Passing the tail light type.
	}
}
boolean TailLightAssembly::isOn(byte taillightLightType)
{	
	switch (taillightLightType)
	{
		case RED1_TAILLIGHT:
			return this->_redLed1->isLedOn();
			break;
		case RED2_TAILLIGHT:
			return this->_redLed2->isLedOn();
			break;
		case RED3_TAILLIGHT:
			return this->_redLed3->isLedOn();
			break;
		case RED4_TAILLIGHT:
			return this->_redLed4->isLedOn();
			break;			
		case RED5_TAILLIGHT:
			return this->_redLed5->isLedOn();
			break;
		case WHITE_TAILLIGHT:
			return this->_whiteLed->isLedOn();
			break;
		default:
			//do nothing. invalid value.
			break;
	}//end switch				
}


