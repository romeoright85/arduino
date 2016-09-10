#include <RoverAnalogSignals.h>

RoverAnalogSignals::RoverAnalogSignals()
{
		
	//Define the amux names below before passing it to the AnalogMuxSensor objects
	this->_amux1AnalogNames[0] = VOLTAGE_7D2_RAW;
	this->_amux1AnalogNames[1] = VOLTAGE_7D2_PRESW25A;
	this->_amux1AnalogNames[2] = VOLTAGE_7D2_SW12D5A;
	this->_amux1AnalogNames[3] = PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING;
	this->_amux1AnalogNames[4] = PHOTOSENSOR_BEACONCCA_REARSIDE_UPWARDPOINTING;
	this->_amux1AnalogNames[5] = TEMPSENSOR_BEACONCCA_CENTERSIDE;
	this->_amux1AnalogNames[6] = TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET;
	this->_amux1AnalogNames[7] = UNUSED_CH;

//DEBUG, type up the other names later using the AMUX Spreadsheet	at K:\Working Directory\DESIGN_PROJ\Design Projects\Robot\My Notes\Pinout Lists
	this->_amux2AnalogNames[0] = UNUSED_CH;
	this->_amux2AnalogNames[1] = UNUSED_CH;
	this->_amux2AnalogNames[2] = UNUSED_CH;
	this->_amux2AnalogNames[3] = UNUSED_CH;
	this->_amux2AnalogNames[4] = UNUSED_CH;
	this->_amux2AnalogNames[5] = UNUSED_CH;
	this->_amux2AnalogNames[6] = UNUSED_CH;
	this->_amux2AnalogNames[7] = UNUSED_CH;	

	this->_amux3AnalogNames[0] = UNUSED_CH;
	this->_amux3AnalogNames[1] = UNUSED_CH;
	this->_amux3AnalogNames[2] = UNUSED_CH;
	this->_amux3AnalogNames[3] = UNUSED_CH;
	this->_amux3AnalogNames[4] = UNUSED_CH;
	this->_amux3AnalogNames[5] = UNUSED_CH;
	this->_amux3AnalogNames[6] = UNUSED_CH;
	this->_amux3AnalogNames[7] = UNUSED_CH;	

	this->_amux4AnalogNames[0] = UNUSED_CH;
	this->_amux4AnalogNames[1] = UNUSED_CH;
	this->_amux4AnalogNames[2] = UNUSED_CH;
	this->_amux4AnalogNames[3] = UNUSED_CH;
	this->_amux4AnalogNames[4] = UNUSED_CH;
	this->_amux4AnalogNames[5] = UNUSED_CH;
	this->_amux4AnalogNames[6] = UNUSED_CH;
	this->_amux4AnalogNames[7] = UNUSED_CH;	

	this->_amux5AnalogNames[0] = UNUSED_CH;
	this->_amux5AnalogNames[1] = UNUSED_CH;
	this->_amux5AnalogNames[2] = UNUSED_CH;
	this->_amux5AnalogNames[3] = UNUSED_CH;
	this->_amux5AnalogNames[4] = UNUSED_CH;
	this->_amux5AnalogNames[5] = UNUSED_CH;
	this->_amux5AnalogNames[6] = UNUSED_CH;
	this->_amux5AnalogNames[7] = UNUSED_CH;	

	this->_amux6AnalogNames[0] = UNUSED_CH;
	this->_amux6AnalogNames[1] = UNUSED_CH;
	this->_amux6AnalogNames[2] = UNUSED_CH;
	this->_amux6AnalogNames[3] = UNUSED_CH;
	this->_amux6AnalogNames[4] = UNUSED_CH;
	this->_amux6AnalogNames[5] = UNUSED_CH;
	this->_amux6AnalogNames[6] = UNUSED_CH;
	this->_amux6AnalogNames[7] = UNUSED_CH;	
			
	this->_amux7AnalogNames[0] = UNUSED_CH;
	this->_amux7AnalogNames[1] = UNUSED_CH;
	this->_amux7AnalogNames[2] = UNUSED_CH;
	this->_amux7AnalogNames[3] = UNUSED_CH;
	this->_amux7AnalogNames[4] = UNUSED_CH;
	this->_amux7AnalogNames[5] = UNUSED_CH;
	this->_amux7AnalogNames[6] = UNUSED_CH;
	this->_amux7AnalogNames[7] = UNUSED_CH;	
							
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

	
}

RoverAnalogSignals::~RoverAnalogSignals()
{
	//do nothing
}
void RoverAnalogSignals::reset()
{
	//resetting all muxes
	for (byte i = 0; i < sizeof(this->_muxArray) / sizeof(this->_muxArray[0]); i++)
	{
		this->_muxArray[i]->reset();
	}
}
AnalogMuxSensor * RoverAnalogSignals::getMuxWith(byte analogSignalName)
{	
	
	for (byte i = 0; i < sizeof(this->_muxArray) / sizeof(this->_muxArray[0]); i++)//search through all the muxes contained in RoverAnalogSignals
	{

		if(this->_muxArray[i]->hasAnalogName(analogSignalName))//if the current mux has the Analog Signal Name
		{
			
			#ifdef _DEBUG_MODE_ON
				Serial.print("MUX: ");
				Serial.println(i+1);//i+1 since the array starts at 0 but the mux numbering starts at 1
			#endif
			
			return this->_muxArray[i];//return that mux object
		}
	}
	return NULL;//else return no object if there is no mux with that Analog Signal Name
}




