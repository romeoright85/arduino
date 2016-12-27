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
	//resetting all muxes and gas sensor
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
unsigned int RoverAnalogSignals::getRawADCValueOf(byte analogSignalName)
{
	
	AnalogMuxSensor * analogMux;
	
	analogMux = findMuxBySignalName(analogSignalName);
	
	//using delegation and calling AnalogMuxSensor's method
	return analogMux->getRawADCValueOf(analogSignalName);
}
double RoverAnalogSignals::getVoltageValueOf(byte analogSignalName)
{
	
	AnalogMuxSensor * analogMux;
	
	analogMux = findMuxBySignalName(analogSignalName);
	
	//using delegation and calling AnalogMuxSensor's method
	return analogMux->getVoltageValueOf(analogSignalName);
}
double RoverAnalogSignals::getCurrentValueOf(byte analogSignalName, byte currentSensorModel)
{
	
	//Vcc for the ACS current sensors are switched Vcc (standard ~5V)
	long measuredVcc = this->readVcc();
	
	double outputVoltage;
	//Get the voltage value of the analog mux channel
	outputVoltage = this->getVoltageValueOf(analogSignalName);
	
	//Convert voltage to current	
	switch(currentSensorModel)
	{
		case ACS711_12D5A:
			//Original Equation: VOUT = (0.11 V/A * i + 1.65 V) * Vcc / 3.3 V
			//Derived Equation: i = ((VOUT*3.3/Vcc)-1.65)/0.11
			return ( ( outputVoltage * 3.3 / measuredVcc ) - 1.65 ) / 0.11;
		break;
		case ACS711_25A:
			//Original Equation: VOUT = (0.055 V/A * i + 1.65 V) * Vcc / 3.3 V
			//Derived Equation: i = ((VOUT*3.3/Vcc)-1.65)/0.055
			return ( ( outputVoltage * 3.3 / measuredVcc ) - 1.65 ) / 0.055;
		break;
		default: //when the model isn't recognized
			return 9999;
		break;
	}	
}
double RoverAnalogSignals::getLightValueOf(byte analogSignalName, double fixedResistorValue)
{

	long measuredVcc = this->readVcc();
	
	double outputVoltage;
	double resistanceInOhms;
	//Get the voltage value of the analog mux channel
	outputVoltage = this->getVoltageValueOf(analogSignalName);
	//Convert voltage output of resistor divider to measured resistance
	resistanceInOhms = this->calculateResistance(measuredVcc, outputVoltage, fixedResistorValue);
	//Convert resistance to lux
	return 500 / ( resistanceInOhms / 1000 );
}
double RoverAnalogSignals::getTempValueOf(byte analogSignalName, double fixedResistorValue)
{
	
	long measuredVcc = this->readVcc();
	
	double outputVoltage;
	double resistanceInOhms;
	//Get the voltage value of the analog mux channel
	outputVoltage = this->getVoltageValueOf(analogSignalName);
	//Convert voltage output of resistor divider to measured resistance
	resistanceInOhms = this->calculateResistance(measuredVcc, outputVoltage, fixedResistorValue);
	//Convert resistance to temperature
	return 1 / ( 1 / TEMP_CONSTANT_T0 + 1 / TEMP_CONSTANT_B * log( resistanceInOhms / TEMP_CONSTANT_R0 ) );	
}
int RoverAnalogSignals::getGasValueOf(MqGasSensor * mqGasSensor)
{
	
	/*
		Reference: http://sandboxelectronics.com/?p=165
		Based on the MqGasSensor object's mqGasSensorDataCurve data (which is based on sensor type),
		by using the slope and a point of the line. The x(logarithmic value of ppm) 
		of the line could be derived if y(rs_ro_ratio) is provided. As it is a 
		logarithmic coordinate, power of 10 is used to convert the result to non-logarithmic 
		 value.
		 
		 This function calculates and returns the ppm (parts per million) of the target gas.
	*/	

	//calculate and set (in mqGasSensor) the Rs/R0 ratio
	this->calculateGasSensorRsRoRatio(mqGasSensor);

	return (
		pow(10, (
					(
						(
							log(mqGasSensor->getRsRoRatio()) - mqGasSensor->mqGasSensorDataCurve[1]
						) / mqGasSensor->mqGasSensorDataCurve[2]						
					) + mqGasSensor->mqGasSensorDataCurve[0]
				)
		)
	);
	
}	


double RoverAnalogSignals::calculateResistance(long measuredVcc, double outputVoltage, double fixedResistorValue)
{
	//Convert voltage to resistance
	//Original Equation: Vo = Vin * Rl / ( Rf + Rl )
	//Derived Equation: Rl = Vo * Rf / ( Vin + Vo )
	//Note: Vcc is Vin in this case.
	//returns resistance in ohms
	
	return outputVoltage * fixedResistorValue / ( measuredVcc + outputVoltage );		
}


double RoverAnalogSignals::calculateGasSensorResistance(MqGasSensor * mqGasSensor)
{
	

	/*
	Notes from http://sandboxelectronics.com/?p=165
	The sensor and the load resistor forms a voltage divider.
	Given the voltage across the load resistor and its resistance,
	the resistance of the sensor could be derived.
	*/
	
	long measuredVcc = this->readVcc();
	
	double outputVoltage;
	double resistanceInOhms;
	//Get the voltage value of the analog mux channel
	outputVoltage = this->getVoltageValueOf(mqGasSensor->getAnalogSignalName());
		
	//Convert voltage output of resistor divider to measured resistance
	resistanceInOhms = this->calculateResistance(measuredVcc, outputVoltage, mqGasSensor->getFixedResistorValue());
	
	return resistanceInOhms;
	
}

void RoverAnalogSignals::calculateGasSensorRsRoRatio(MqGasSensor * mqGasSensor)
{
	//Reference: http://sandboxelectronics.com/?p=165
	//Rs divided by R0	
	mqGasSensor->setRsRoRatio( this->readGasSensor(mqGasSensor) / mqGasSensor->getR0() );
	
}

double RoverAnalogSignals::readGasSensor(MqGasSensor * mqGasSensor)
{
	//initialize variables	
	float mqGasSensorRs = 0;//Note: the term mqGasSensorRs = Sensing Resistance is from the MQ datasheet
	  	   
	for (byte i=0; i<GAS_SENSOR_READ_SAMPLE_TIMES; i++) {
		mqGasSensorRs += this->calculateGasSensorResistance(mqGasSensor);
		delay(GAS_SENSOR_READ_SAMPLE_INTERVAL);
	}

	mqGasSensorRs = mqGasSensorRs/GAS_SENSOR_READ_SAMPLE_TIMES;

	return mqGasSensorRs;
}

void RoverAnalogSignals::calibrateGasSensor(MqGasSensor * mqGasSensor)
{

	//Code based on: http://sandboxelectronics.com/?p=165

	float val=0;

	//take multiple samples
	for (byte i=0; i<GAS_SENSOR_CALIBARAION_SAMPLE_TIMES; i++)
	{
		//accumulate sensor resistance measurements (to be averaged later on)
		val += this->calculateGasSensorResistance(mqGasSensor);
		//delay between measurements
		delay(GAS_SENSOR_CALIBRATION_SAMPLE_INTERVAL);
	}
	
	//calculate the average value
	val = val/GAS_SENSOR_CALIBARAION_SAMPLE_TIMES;

	//divided by _mqGasSensorR0CleanAirFactor yields the Ro according to the chart in the datasheet 
	val = val/(mqGasSensor->getR0CleanAirFactor());                                                        

	//Assign the calculated value of R0 to the variable R0
	mqGasSensor->setR0(val);
	
}