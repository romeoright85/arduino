#include <RoverAnalogSignals.h>

RoverAnalogSignals::RoverAnalogSignals()
{
		
	//Define the amux names below before passing it to the AnalogMuxSensor objects
	
	//AMUX 1
	this->_amux1AnalogNames[0] = VOLTAGE_7D2_RAW;
	this->_amux1AnalogNames[1] = CURRENT_7D2_PRESW25A;
	this->_amux1AnalogNames[2] = CURRENT_7D2_SW12D5A;
	this->_amux1AnalogNames[3] = PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING;
	this->_amux1AnalogNames[4] = PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING;
	this->_amux1AnalogNames[5] = TEMPSENSOR_BEACONCCA_CENTERSIDE;
	this->_amux1AnalogNames[6] = TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET;
	this->_amux1AnalogNames[7] = UNUSED_CH;

	//AMUX 2
	this->_amux2AnalogNames[0] = VOLTAGE_5_ANALOGCCA;
	this->_amux2AnalogNames[1] = CURRENT_3D3_SW12D5A;
	this->_amux2AnalogNames[2] = PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING;
	this->_amux2AnalogNames[3] = PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING;
	this->_amux2AnalogNames[4] = PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING;
	this->_amux2AnalogNames[5] = TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR;
	this->_amux2AnalogNames[6] = TEMPSENSOR_DIGITALCCA_MIDDLESIDE;
	this->_amux2AnalogNames[7] = UNUSED_CH;	

	//AMUX 3
	this->_amux3AnalogNames[0] = VOLTAGE_3D3_SW;
	this->_amux3AnalogNames[1] = CURRENT_MOTORCTRLR_CH1_12D5A;
	this->_amux3AnalogNames[2] = PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING;
	this->_amux3AnalogNames[3] = PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK;
	this->_amux3AnalogNames[4] = PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING;
	this->_amux3AnalogNames[5] = TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK;
	this->_amux3AnalogNames[6] = UNUSED_CH;
	this->_amux3AnalogNames[7] = UNUSED_CH;	

	//AMUX 4
	this->_amux4AnalogNames[0] = GAS_BEACONCCA_RIGHTPOINTING;
	this->_amux4AnalogNames[1] = CURRENT_MOTORCTRLR_CH2_12D5A;
	this->_amux4AnalogNames[2] = PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING;
	this->_amux4AnalogNames[3] = PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK;
	this->_amux4AnalogNames[4] = PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING;
	this->_amux4AnalogNames[5] = TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE;
	this->_amux4AnalogNames[6] = UNUSED_CH;
	this->_amux4AnalogNames[7] = UNUSED_CH;	

	//AMUX 5
	this->_amux5AnalogNames[0] = UNUSED_CH;
	this->_amux5AnalogNames[1] = UNUSED_CH;
	this->_amux5AnalogNames[2] = UNUSED_CH;
	this->_amux5AnalogNames[3] = UNUSED_CH;
	this->_amux5AnalogNames[4] = UNUSED_CH;
	this->_amux5AnalogNames[5] = UNUSED_CH;
	this->_amux5AnalogNames[6] = UNUSED_CH;
	this->_amux5AnalogNames[7] = UNUSED_CH;	

	//AMUX 6
	this->_amux6AnalogNames[0] = UNUSED_CH;
	this->_amux6AnalogNames[1] = UNUSED_CH;
	this->_amux6AnalogNames[2] = UNUSED_CH;
	this->_amux6AnalogNames[3] = UNUSED_CH;
	this->_amux6AnalogNames[4] = UNUSED_CH;
	this->_amux6AnalogNames[5] = UNUSED_CH;
	this->_amux6AnalogNames[6] = UNUSED_CH;
	this->_amux6AnalogNames[7] = UNUSED_CH;	
			
	//AMUX 7
	this->_amux7AnalogNames[0] = UNUSED_CH;
	this->_amux7AnalogNames[1] = UNUSED_CH;
	this->_amux7AnalogNames[2] = UNUSED_CH;
	this->_amux7AnalogNames[3] = UNUSED_CH;
	this->_amux7AnalogNames[4] = UNUSED_CH;
	this->_amux7AnalogNames[5] = UNUSED_CH;
	this->_amux7AnalogNames[6] = UNUSED_CH;
	this->_amux7AnalogNames[7] = UNUSED_CH;	
				
	//AMUX 8
	this->_amux8AnalogNames[0] = UNUSED_CH;
	this->_amux8AnalogNames[1] = UNUSED_CH;
	this->_amux8AnalogNames[2] = UNUSED_CH;
	this->_amux8AnalogNames[3] = UNUSED_CH;
	this->_amux8AnalogNames[4] = UNUSED_CH;
	this->_amux8AnalogNames[5] = UNUSED_CH;
	this->_amux8AnalogNames[6] = UNUSED_CH;
	this->_amux8AnalogNames[7] = UNUSED_CH;

	
	
	//create AnalogMuxSensor objects and assign them to the private _amux pointers
	this->_amux1 = new AnalogMuxSensor(AMUX1_SEL_0_PIN, AMUX1_SEL_1_PIN, AMUX1_SEL_2_PIN, OPAMP_1_OUT_PIN, this->_amux1AnalogNames);
	this->_amux2 = new AnalogMuxSensor(AMUX2_SEL_0_PIN, AMUX2_SEL_1_PIN, AMUX2_SEL_2_PIN, OPAMP_2_OUT_PIN, this->_amux2AnalogNames);//DEBUG, change the _amux1AnalogNames later
	this->_amux3 = new AnalogMuxSensor(AMUX3_SEL_0_PIN, AMUX3_SEL_1_PIN, AMUX3_SEL_2_PIN, OPAMP_3_OUT_PIN, this->_amux3AnalogNames);//DEBUG, change the _amux1AnalogNames later
	this->_amux4 = new AnalogMuxSensor(AMUX4_SEL_0_PIN, AMUX4_SEL_1_PIN, AMUX4_SEL_2_PIN, OPAMP_4_OUT_PIN, this->_amux4AnalogNames);//DEBUG, change the _amux1AnalogNames later
	this->_amux5 = new AnalogMuxSensor(AMUX5_SEL_0_PIN, AMUX5_SEL_1_PIN, AMUX5_SEL_2_PIN, OPAMP_5_OUT_PIN, this->_amux5AnalogNames);//DEBUG, change the _amux1AnalogNames later
	this->_amux6 = new AnalogMuxSensor(AMUX6_SEL_0_PIN, AMUX6_SEL_1_PIN, AMUX6_SEL_2_PIN, OPAMP_6_OUT_PIN, this->_amux6AnalogNames);//DEBUG, change the _amux1AnalogNames later
	this->_amux7 = new AnalogMuxSensor(AMUX7_SEL_0_PIN, AMUX7_SEL_1_PIN, AMUX7_SEL_2_PIN, OPAMP_7_OUT_PIN, this->_amux7AnalogNames);//DEBUG, change the _amux1AnalogNames later
	this->_amux8 = new AnalogMuxSensor(AMUX8_SEL_0_PIN, AMUX8_SEL_1_PIN, AMUX8_SEL_2_PIN, OPAMP_8_OUT_PIN, this->_amux8AnalogNames);//DEBUG, change the _amux1AnalogNames later
	
	//initialize the muxArray's pointers with the AnalogMuxSensor objects
	this->_muxArray[0] = this->_amux1;
	this->_muxArray[1] = this->_amux2;
	this->_muxArray[2] = this->_amux3;
	this->_muxArray[3] = this->_amux4;
	this->_muxArray[4] = this->_amux5;
	this->_muxArray[5] = this->_amux6;
	this->_muxArray[6] = this->_amux7;
	this->_muxArray[7] = this->_amux8;	

	//initialize the _resetArray's pointers with the AnalogMuxSensor objects
	this->_resetArray[0] = this->_amux1;
	this->_resetArray[1] = this->_amux2;
	this->_resetArray[2] = this->_amux3;
	this->_resetArray[3] = this->_amux4;
	this->_resetArray[4] = this->_amux5;
	this->_resetArray[5] = this->_amux6;
	this->_resetArray[6] = this->_amux7;
	this->_resetArray[7] = this->_amux8;	

}

RoverAnalogSignals::~RoverAnalogSignals()
{
	//do nothing
}
void RoverAnalogSignals::reset()
{
	//resetting all muxes
	for (byte i = 0; i < sizeof(this->_resetArray) / sizeof(this->_resetArray[0]); i++)
	{
		this->_resetArray[i]->reset();
	}
}
AnalogMuxSensor * RoverAnalogSignals::findMuxBySignalName(byte analogSignalName)
{	
	
	for (byte i = 0; i < sizeof(this->_muxArray) / sizeof(this->_muxArray[0]); i++)//search through all the muxes contained in RoverAnalogSignals
	{

		if(this->_muxArray[i]->hasAnalogName(analogSignalName))//if the current mux has the Analog Signal Name
		{
			
			#ifdef _DEBUG_MODE_ON
				Serial.flush();
				Serial.print(F("MUX: "));
				Serial.println(i+1);//i+1 since the array starts at 0 but the mux numbering starts at 1
			#endif
			
			return this->_muxArray[i];//return that mux object
		}
	}
	return NULL;//else return no object if there is no mux with that Analog Signal Name
}
int RoverAnalogSignals::getRawADCValueOf(byte analogSignalName)
{
	
	AnalogMuxSensor * analogMux;
	
	analogMux = findMuxBySignalName(analogSignalName);
	
	//using delegation and calling AnalogMuxSensor's method
	return analogMux->getRawADCValueOf(analogSignalName);
}


double RoverAnalogSignals::getADCValueOf_As(byte analogSignalName, byte conversionType, double fixedResistorValue)
{
	
	int rawADCValue;
	double voltage;
	double resistanceValue;
	 rawADCValue = this->getRawADCValueOf(analogSignalName);
	
	switch(conversionType)
	{
		case VOLTAGE_VALUE: //fixedResistorValue not needed, so you can pass it the constant NO_RESISTOR
			//Convert rawADC to voltage
			return getMeasuredVoltage(rawADCValue);			
			break;
		case CURRENT_VALUE:
			//Convert rawADC to voltage
			voltage = getMeasuredVoltage(rawADCValue);
			//Convert voltage to current
//DEBUG, write me later			
			return voltage;//DEBUG
			break;
		case TEMP_VALUE:
			//Convert rawADC to voltage
			voltage = getMeasuredVoltage(rawADCValue);
			//Convert voltage output of resistor divider to measured resistance
			resistanceValue = getMeasuredResistance(voltage, fixedResistorValue);
			//Convert resistance to temperature
			return 1/(1/TEMP_CONSTANT_T0+1/TEMP_CONSTANT_B*log(resistanceValue/TEMP_CONSTANT_R0));			
			break;
		case GAS_VALUE:			
			//Convert rawADC to voltage
			voltage = getMeasuredVoltage(rawADCValue);
			//????
//DEBUG, write me later		
			return rawADCValue*10;//DEBUG
			break;	
		case PHOTO_VALUE:
			//Convert rawADC to voltage
			voltage = getMeasuredVoltage(rawADCValue);
			//Convert voltage output of resistor divider to measured resistance
			resistanceValue = getMeasuredResistance(voltage, fixedResistorValue);
			//Convert resistance to lux
//DEBUG, write me later					
			return rawADCValue*10;//DEBUG
			break;				
		default: //No conversion.
			return rawADCValue*10;//DEBUG
			break;
	}	
}





double RoverAnalogSignals::getMeasuredVoltage(int rawADCValue)
{
	//Convert rawADC to voltage
//DEBUG, write me later
	return rawADCValue;//DEBUG
}

double RoverAnalogSignals::getMeasuredResistance(double voltage, double fixedResistorValue)
{
	//Convert voltage to resistance
//DEBUG, write me later	
	return voltage;//DEBUG
}