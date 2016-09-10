#include <AnalogMuxSensor.h>

AnalogMuxSensor::AnalogMuxSensor(byte amuxSel0Pin, byte amuxSel1Pin, byte amuxSel2Pin, byte opampOutPin, byte analogNames[] )
{
		
			//store the object variables
			this->_AMUX_SEL_0_PIN = amuxSel0Pin;
			this->_AMUX_SEL_1_PIN = amuxSel1Pin;
			this->_AMUX_SEL_2_PIN = amuxSel2Pin;
			this->_OPAMP_OUT_PIN = opampOutPin;

			memcpy(this->_analogNames, analogNames, sizeof(this->_analogNames)/sizeof(this->_analogNames[0]));
	
			//configure the pins
			pinMode(this->_AMUX_SEL_0_PIN, OUTPUT);
			pinMode(this->_AMUX_SEL_1_PIN, OUTPUT);
			pinMode(this->_AMUX_SEL_2_PIN, OUTPUT);
			
			//initialize to channel 0
			digitalWrite(this->_AMUX_SEL_0_PIN, LOW);
			digitalWrite(this->_AMUX_SEL_1_PIN, LOW);
			digitalWrite(this->_AMUX_SEL_2_PIN, LOW);
			
}
AnalogMuxSensor::~AnalogMuxSensor()
{
	//do nothing
}

void AnalogMuxSensor::reset()
{

	//software reset
	//initialize to channel 0
	digitalWrite(this->_AMUX_SEL_0_PIN, LOW);
	digitalWrite(this->_AMUX_SEL_1_PIN, LOW);
	digitalWrite(this->_AMUX_SEL_2_PIN, LOW);
}


int AnalogMuxSensor::readAmuxChannel(byte aMuxChannel)
{
	#ifdef _DEBUG_MODE_ON
		Serial.print("CH: ");
		Serial.println(aMuxChannel);
	#endif
	
	switch(aMuxChannel)
	{
		case AMUX_CH_1:
				digitalWrite(this->_AMUX_SEL_0_PIN, LOW);
				digitalWrite(this->_AMUX_SEL_1_PIN, LOW);
				digitalWrite(this->_AMUX_SEL_2_PIN, LOW);
		break;
		case AMUX_CH_2:
				digitalWrite(this->_AMUX_SEL_0_PIN, HIGH);
				digitalWrite(this->_AMUX_SEL_1_PIN, LOW);
				digitalWrite(this->_AMUX_SEL_2_PIN, LOW);
		break;
		case AMUX_CH_3:
				digitalWrite(this->_AMUX_SEL_0_PIN, LOW);
				digitalWrite(this->_AMUX_SEL_1_PIN, HIGH);
				digitalWrite(this->_AMUX_SEL_2_PIN, LOW);
		break;
		case AMUX_CH_4:
				digitalWrite(this->_AMUX_SEL_0_PIN, HIGH);
				digitalWrite(this->_AMUX_SEL_1_PIN, HIGH);
				digitalWrite(this->_AMUX_SEL_2_PIN, LOW);
		break;
		case AMUX_CH_5:
				digitalWrite(this->_AMUX_SEL_0_PIN, LOW);
				digitalWrite(this->_AMUX_SEL_1_PIN, LOW);
				digitalWrite(this->_AMUX_SEL_2_PIN, HIGH);
		break;
		case AMUX_CH_6:
				digitalWrite(this->_AMUX_SEL_0_PIN, HIGH);
				digitalWrite(this->_AMUX_SEL_1_PIN, LOW);
				digitalWrite(this->_AMUX_SEL_2_PIN, HIGH);
		break;
		case AMUX_CH_7:
				digitalWrite(this->_AMUX_SEL_0_PIN, LOW);
				digitalWrite(this->_AMUX_SEL_1_PIN, HIGH);
				digitalWrite(this->_AMUX_SEL_2_PIN, HIGH);
		break;
		case AMUX_CH_8:
				digitalWrite(this->_AMUX_SEL_0_PIN, HIGH);
				digitalWrite(this->_AMUX_SEL_1_PIN, HIGH);
				digitalWrite(this->_AMUX_SEL_2_PIN, HIGH);
		break;
		default:
			//undefined channel - default to Channel 1
			digitalWrite(this->_AMUX_SEL_0_PIN, LOW);
			digitalWrite(this->_AMUX_SEL_1_PIN, LOW);
			digitalWrite(this->_AMUX_SEL_2_PIN, LOW);
	}
	delay(1);//allow enough time to switch to the desired AMUX channel
	return analogRead(this->_OPAMP_OUT_PIN);		
}
int AnalogMuxSensor::getRawADCValueOf(byte analogSignalName)
{
	for(byte i = 0; i< sizeof( this->_analogNames)/sizeof(_analogNames[0]); i++)
	{
		if(this->_analogNames[i] == analogSignalName)
		{
			return this->readAmuxChannel(i+1);//use i+1 since the index is from 0 to 7, but the channels are label 1 to 8
		}
	}
	return 32767;//else invalid Analog Signal Name, so return the max int value of 32,767 to error out
}
boolean AnalogMuxSensor::hasAnalogName(byte analogSignalName)
{
	for(byte i = 0; i< sizeof( this->_analogNames)/sizeof(_analogNames[0]); i++)
	{
	if(this->_analogNames[i] == analogSignalName)
		{
			return true;
		}
	}
	return false;//return false if the Analog Signal Name was not found
}
