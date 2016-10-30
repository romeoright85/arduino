#include <BeaconLightAssembly.h>


BeaconLightAssembly::BeaconLightAssembly( byte frontLeftIRPin, byte backLeftIRPin, byte backRightIRPin, byte frontRightIRPin, byte leftBluePin, byte backBluePin, byte rightBluePin, byte frontBluePin )
{
	
	
	this->_frontLeftBeaconIR = new DigitalLed(frontLeftIRPin);
	this->_backLeftBeaconIR = new DigitalLed(backLeftIRPin);
	this->_backRightBeaconIR = new DigitalLed(backRightIRPin);
	this->_frontRightBeaconIR = new DigitalLed(frontRightIRPin);
	
	this->_leftBeaconBlue = new DigitalLed(leftBluePin);
	this->_backBeaconBlue = new DigitalLed(backBluePin);
	this->_rightBeaconBlue = new DigitalLed(rightBluePin);
	this->_frontBeaconBlue = new DigitalLed(frontBluePin);
	
	
	//initialize them as off
	this->reset();
	
	
}
BeaconLightAssembly::~BeaconLightAssembly()
{
	//do nothing
}
void BeaconLightAssembly::reset()
{
		
	this->turnOff(FRONT_LEFT_IR_BEACON, BACK_LEFT_IR_BEACON, BACK_RIGHT_IR_BEACON, FRONT_RIGHT_IR_BEACON, LEFT_BLUE_BEACON, BACK_BLUE_BEACON, RIGHT_BLUE_BEACON, FRONT_BLUE_BEACON);	
	
}
void BeaconLightAssembly::turnOn(byte beaconLightType)
{

	switch (beaconLightType)
	{
		case FRONT_LEFT_IR_BEACON:
			this->_frontLeftBeaconIR->ledOn();
			break;
		case BACK_LEFT_IR_BEACON:
			this->_backLeftBeaconIR->ledOn();
			break;
		case BACK_RIGHT_IR_BEACON:
			this->_backRightBeaconIR->ledOn();
			break;
		case FRONT_RIGHT_IR_BEACON:
			this->_frontRightBeaconIR->ledOn();
			break;			
		case LEFT_BLUE_BEACON:
			this->_leftBeaconBlue->ledOn();
			break;
		case BACK_BLUE_BEACON:
			this->_backBeaconBlue->ledOn();
			break;
		case RIGHT_BLUE_BEACON:
			this->_rightBeaconBlue->ledOn();
			break;
		case FRONT_BLUE_BEACON:
			this->_frontBeaconBlue->ledOn();
			break;
		default:
			//do nothing. invalid value.
			break;
	}//end switch
}
void BeaconLightAssembly::turnOn(byte beaconLightType1, byte beaconLightType2)
{
	byte beaconLightTypes[] = { beaconLightType1, beaconLightType2 };

	for (byte i = 0; i <  sizeof(beaconLightTypes)/sizeof(beaconLightTypes[0]); i++)
	{
		this->turnOn(beaconLightTypes[i]);//using delegation. Passing the beacon light type.
	}
}
void BeaconLightAssembly::turnOn(byte beaconLightType1, byte beaconLightType2, byte beaconLightType3)
{
	byte beaconLightTypes[] = { beaconLightType1, beaconLightType2, beaconLightType3 };

	for (byte i = 0; i <  sizeof(beaconLightTypes)/sizeof(beaconLightTypes[0]); i++)
	{
		this->turnOn(beaconLightTypes[i]);//using delegation. Passing the beacon light type.
	}
}
void BeaconLightAssembly::turnOn(byte beaconLightType1, byte beaconLightType2, byte beaconLightType3, byte beaconLightType4)
{
	byte beaconLightTypes[] = { beaconLightType1, beaconLightType2, beaconLightType3, beaconLightType4 };

	for (byte i = 0; i <  sizeof(beaconLightTypes)/sizeof(beaconLightTypes[0]); i++)
	{
		this->turnOn(beaconLightTypes[i]);//using delegation. Passing the beacon light type.
	}
}
void BeaconLightAssembly::turnOn(byte beaconLightType1, byte beaconLightType2, byte beaconLightType3, byte beaconLightType4, byte beaconLightType5)
{
	byte beaconLightTypes[] = { beaconLightType1, beaconLightType2, beaconLightType3, beaconLightType4, beaconLightType5 };

	for (byte i = 0; i <  sizeof(beaconLightTypes)/sizeof(beaconLightTypes[0]); i++)
	{
		this->turnOn(beaconLightTypes[i]);//using delegation. Passing the beacon light type.
	}
}
void BeaconLightAssembly::turnOn(byte beaconLightType1, byte beaconLightType2, byte beaconLightType3, byte beaconLightType4, byte beaconLightType5, byte beaconLightType6)
{
	byte beaconLightTypes[] = { beaconLightType1, beaconLightType2, beaconLightType3, beaconLightType4, beaconLightType5, beaconLightType6 };

	for (byte i = 0; i <  sizeof(beaconLightTypes)/sizeof(beaconLightTypes[0]); i++)
	{
		this->turnOn(beaconLightTypes[i]);//using delegation. Passing the beacon light type.
	}
}
void BeaconLightAssembly::turnOn(byte beaconLightType1, byte beaconLightType2, byte beaconLightType3, byte beaconLightType4, byte beaconLightType5, byte beaconLightType6, byte beaconLightType7)
{
	byte beaconLightTypes[] = { beaconLightType1, beaconLightType2, beaconLightType3, beaconLightType4, beaconLightType5, beaconLightType6, beaconLightType7 };

	for (byte i = 0; i <  sizeof(beaconLightTypes)/sizeof(beaconLightTypes[0]); i++)
	{
		this->turnOn(beaconLightTypes[i]);//using delegation. Passing the beacon light type.
	}
}
void BeaconLightAssembly::turnOn(byte beaconLightType1, byte beaconLightType2, byte beaconLightType3, byte beaconLightType4, byte beaconLightType5, byte beaconLightType6, byte beaconLightType7, byte beaconLightType8)
{
	byte beaconLightTypes[] = { beaconLightType1, beaconLightType2, beaconLightType3, beaconLightType4, beaconLightType5, beaconLightType6, beaconLightType7, beaconLightType8 };

	for (byte i = 0; i <  sizeof(beaconLightTypes)/sizeof(beaconLightTypes[0]); i++)
	{
		this->turnOn(beaconLightTypes[i]);//using delegation. Passing the beacon light type.
	}
}
void BeaconLightAssembly::turnOff(byte beaconLightType)
{

	switch (beaconLightType)
	{
		case FRONT_LEFT_IR_BEACON:
			this->_frontLeftBeaconIR->ledOff();
			break;
		case BACK_LEFT_IR_BEACON:
			this->_backLeftBeaconIR->ledOff();
			break;
		case BACK_RIGHT_IR_BEACON:
			this->_backRightBeaconIR->ledOff();
			break;
		case FRONT_RIGHT_IR_BEACON:
			this->_frontRightBeaconIR->ledOff();
			break;			
		case LEFT_BLUE_BEACON:
			this->_leftBeaconBlue->ledOff();
			break;
		case BACK_BLUE_BEACON:
			this->_backBeaconBlue->ledOff();
			break;
		case RIGHT_BLUE_BEACON:
			this->_rightBeaconBlue->ledOff();
			break;
		case FRONT_BLUE_BEACON:
			this->_frontBeaconBlue->ledOff();
			break;
		default:
			//do nothing. invalid value.
			break;
	}//end switch
}
void BeaconLightAssembly::turnOff(byte beaconLightType1, byte beaconLightType2)
{
	byte beaconLightTypes[] = { beaconLightType1, beaconLightType2 };

	for (byte i = 0; i <  sizeof(beaconLightTypes)/sizeof(beaconLightTypes[0]); i++)
	{
		this->turnOff(beaconLightTypes[i]);//using delegation. Passing the beacon light type.
	}
}
void BeaconLightAssembly::turnOff(byte beaconLightType1, byte beaconLightType2, byte beaconLightType3)
{
	byte beaconLightTypes[] = { beaconLightType1, beaconLightType2, beaconLightType3 };

	for (byte i = 0; i <  sizeof(beaconLightTypes)/sizeof(beaconLightTypes[0]); i++)
	{
		this->turnOff(beaconLightTypes[i]);//using delegation. Passing the beacon light type.
	}
}
void BeaconLightAssembly::turnOff(byte beaconLightType1, byte beaconLightType2, byte beaconLightType3, byte beaconLightType4)
{
	byte beaconLightTypes[] = { beaconLightType1, beaconLightType2, beaconLightType3, beaconLightType4 };

	for (byte i = 0; i <  sizeof(beaconLightTypes)/sizeof(beaconLightTypes[0]); i++)
	{
		this->turnOff(beaconLightTypes[i]);//using delegation. Passing the beacon light type.
	}
}
void BeaconLightAssembly::turnOff(byte beaconLightType1, byte beaconLightType2, byte beaconLightType3, byte beaconLightType4, byte beaconLightType5)
{
	byte beaconLightTypes[] = { beaconLightType1, beaconLightType2, beaconLightType3, beaconLightType4, beaconLightType5 };

	for (byte i = 0; i <  sizeof(beaconLightTypes)/sizeof(beaconLightTypes[0]); i++)
	{
		this->turnOff(beaconLightTypes[i]);//using delegation. Passing the beacon light type.
	}
}
void BeaconLightAssembly::turnOff(byte beaconLightType1, byte beaconLightType2, byte beaconLightType3, byte beaconLightType4, byte beaconLightType5, byte beaconLightType6)
{
	byte beaconLightTypes[] = { beaconLightType1, beaconLightType2, beaconLightType3, beaconLightType4, beaconLightType5, beaconLightType6 };

	for (byte i = 0; i <  sizeof(beaconLightTypes)/sizeof(beaconLightTypes[0]); i++)
	{
		this->turnOff(beaconLightTypes[i]);//using delegation. Passing the beacon light type.
	}
}
void BeaconLightAssembly::turnOff(byte beaconLightType1, byte beaconLightType2, byte beaconLightType3, byte beaconLightType4, byte beaconLightType5, byte beaconLightType6, byte beaconLightType7)
{
	byte beaconLightTypes[] = { beaconLightType1, beaconLightType2, beaconLightType3, beaconLightType4, beaconLightType5, beaconLightType6, beaconLightType7 };

	for (byte i = 0; i <  sizeof(beaconLightTypes)/sizeof(beaconLightTypes[0]); i++)
	{
		this->turnOff(beaconLightTypes[i]);//using delegation. Passing the beacon light type.
	}
}
void BeaconLightAssembly::turnOff(byte beaconLightType1, byte beaconLightType2, byte beaconLightType3, byte beaconLightType4, byte beaconLightType5, byte beaconLightType6, byte beaconLightType7, byte beaconLightType8)
{
	byte beaconLightTypes[] = { beaconLightType1, beaconLightType2, beaconLightType3, beaconLightType4, beaconLightType5, beaconLightType6, beaconLightType7, beaconLightType8 };

	for (byte i = 0; i <  sizeof(beaconLightTypes)/sizeof(beaconLightTypes[0]); i++)
	{
		this->turnOff(beaconLightTypes[i]);//using delegation. Passing the beacon light type.
	}
}



boolean BeaconLightAssembly::isOn(byte beaconLightType)
{	
	switch (beaconLightType)
	{
		case FRONT_LEFT_IR_BEACON:
			return this->_frontLeftBeaconIR->isLedOn();
			break;
		case BACK_LEFT_IR_BEACON:
			return this->_backLeftBeaconIR->isLedOn();
			break;
		case BACK_RIGHT_IR_BEACON:
			return this->_backRightBeaconIR->isLedOn();
			break;
		case FRONT_RIGHT_IR_BEACON:
			return this->_frontRightBeaconIR->isLedOn();
			break;			
		case LEFT_BLUE_BEACON:
			return this->_leftBeaconBlue->isLedOn();
			break;
		case BACK_BLUE_BEACON:
			return this->_backBeaconBlue->isLedOn();
			break;
		case RIGHT_BLUE_BEACON:
			return this->_rightBeaconBlue->isLedOn();
			break;
		case FRONT_BLUE_BEACON:
			return this->_frontBeaconBlue->isLedOn();
			break;
		default:
			//do nothing. invalid value.
			break;
	}//end switch				
}





