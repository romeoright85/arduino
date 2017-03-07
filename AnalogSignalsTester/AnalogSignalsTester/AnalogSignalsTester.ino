//Used for AUXI - 2

#include <RoverAnalogSignals.h> //calls MqGasSensor.h
#include <UpTime.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>


//Debug: uncomment the follow defines below in order to see the output (can choose as many or as little as you want
//#define _OUTPUT_MUX1_
//#define _OUTPUT_MUX2_
//#define _OUTPUT_MUX3_
#define _OUTPUT_MUX4_
#define _DEBUG_3SEC_WARM_UP_ //do a 3 second warmup instead of a 3 minute warmup for software debugging only

//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast

#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ Serial2
#else
	#define _SERIAL_DEBUG_CHANNEL_ Serial
#endif

//Global Variables


//Note the timers aren't very accurate due to delay caused by the loop() code, such as Serial.println(). But good enough for parallel processing.
DelayCounter * counterGasCal = new DelayCounter(DELAY_1_PERIODS);//initialize it to count to 1 periods
GlobalDelayTimer * timerGasCal = new GlobalDelayTimer(DELAY_TIMER_RES_1ms, counterGasCal);//set each period to be 5ms long (delay interval)
DelayCounter * counterGasRead = new DelayCounter(DELAY_1_PERIODS);//initialize it to count to 1 periods
GlobalDelayTimer * timerGasRead = new GlobalDelayTimer(DELAY_TIMER_RES_1ms, counterGasRead);//set each period to be 5ms long (delay interval)


UpTime * roverUptime = new UpTime();
MqGasSensor * mqGasSensor = new MqGasSensor(GAS_SENSOR_TYPE_MQ2, GAS_BEACONCCA_RIGHTPOINTING, RESISTOR_GAS_BEACONCCA_RIGHTPOINTING);
RoverAnalogSignals * analogSignals = new RoverAnalogSignals();

int val = 0;
double val_Dbl = 0;


RoverReset * resetArray[] = {	
	counterGasCal,
	timerGasCal,
	counterGasRead,
	timerGasRead,
	roverUptime,
	mqGasSensor,
	analogSignals	
};


void setup() {
	//put this before the reset since the reset might Serial Print in debug mode
	
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	
	Serial.begin(PC_USB_BAUD_RATE);
	Serial2.begin(MAIN_BAUD_RATE);
	delay(100);//allow some time for the serial port to begin

	_SERIAL_DEBUG_CHANNEL_.println(F("Gas Sensor Warming Up And Calibrating - Wait ~3:26"));

}


void loop() {


	//Background running tasks
	roverUptime->run();//active the uptime monitor
	timerGasRead->Running();//activate the 50mS timer
	timerGasCal->Running();//activate the 500mS timer
	

	//wait for warm up of the MQ gas sensor, the calibrate once
	if (!analogSignals->gasSensorIsCalibrated())
	{
		#ifdef _DEBUG_3SEC_WARM_UP_
			//Wait for a >= 3 minute second warm up
			//Note: Calibration takes about 20 secs (due to the parallel processing code)
			analogSignals->calibrateGasSensor(mqGasSensor, roverUptime->getSeconds(), counterGasCal);//DEBUG, speed it up to 3 seconds. But the code will think the seconds are minutes as the function is expecting minutes as the input
		#else
			//Wait for a >= 3 minute warm up
			//Note: Calibration takes a few seconds, measured at about 26 seconds to begin	
			analogSignals->calibrateGasSensor(mqGasSensor, roverUptime->getMinutes());
		#endif
	
	}


	_SERIAL_DEBUG_CHANNEL_.println(F("--START--"));
	_SERIAL_DEBUG_CHANNEL_.println("");



#ifdef _OUTPUT_MUX1_
	//AMUX 1
	_SERIAL_DEBUG_CHANNEL_.println(F("==AMUX1=="));
	

	//Ch 0		
	val = analogSignals->getRawADCValueOf(VOLTAGE_7D2_RAW);
	_SERIAL_DEBUG_CHANNEL_.print(F("VOLTAGE_7D2_RAW: "));
	_SERIAL_DEBUG_CHANNEL_.println(val);
	val_Dbl = analogSignals->getVoltageValueOf(VOLTAGE_7D2_RAW);
	_SERIAL_DEBUG_CHANNEL_.print(F("VOLTAGE_7D2_ACTUAL: "));
	_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);



	//Ch 1
	val = analogSignals->getRawADCValueOf(CURRENT_7D2_PRESW25A);
	_SERIAL_DEBUG_CHANNEL_.print(F("CURRENT_7D2_PRESW25A_RAW: "));
	_SERIAL_DEBUG_CHANNEL_.println(val);
	val_Dbl = analogSignals->getCurrentValueOf(CURRENT_7D2_PRESW25A, ACS711_25A);
	_SERIAL_DEBUG_CHANNEL_.print(F("CURRENT_7D2_PRESW25A_ACTUAL: "));
	_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);




	//Ch 2	
	val = analogSignals->getRawADCValueOf(CURRENT_7D2_SW12D5A);
	_SERIAL_DEBUG_CHANNEL_.print(F("CURRENT_7D2_SW12D5A_RAW: "));
	_SERIAL_DEBUG_CHANNEL_.println(val);
	val_Dbl = analogSignals->getCurrentValueOf(CURRENT_7D2_SW12D5A, ACS711_12D5A);
	_SERIAL_DEBUG_CHANNEL_.print(F("CURRENT_7D2_SW12D5A_ACTUAL: "));
	_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);


	//Ch 3
	val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING);
	_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING_RAW: "));
	_SERIAL_DEBUG_CHANNEL_.println(val);
	val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING);
	_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING_ACTUAL: "));
	_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);



	//Ch 4
	val = analogSignals->getRawADCValueOf(PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING);
	_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING_RAW: "));
	_SERIAL_DEBUG_CHANNEL_.println(val);
	val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING, RESISTOR_PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING);
	_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING_ACTUAL: "));
	_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);


	//Ch 5
	val = analogSignals->getRawADCValueOf(TEMPSENSOR_BEACONCCA_CENTERSIDE);
	_SERIAL_DEBUG_CHANNEL_.print(F("TEMPSENSOR_BEACONCCA_CENTERSIDE_RAW: "));
	_SERIAL_DEBUG_CHANNEL_.println(val);
	val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_BEACONCCA_CENTERSIDE, RESISTOR_TEMPSENSOR_BEACONCCA_CENTERSIDE);
	_SERIAL_DEBUG_CHANNEL_.print(F("TEMPSENSOR_BEACONCCA_CENTERSIDE_ACTUAL: "));
	_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);



	//Ch 6
	val = analogSignals->getRawADCValueOf(TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET);
	_SERIAL_DEBUG_CHANNEL_.print(F("TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET_RAW: "));
	_SERIAL_DEBUG_CHANNEL_.println(val);
	val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET, RESISTOR_TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET);
	_SERIAL_DEBUG_CHANNEL_.print(F("TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET_ACTUAL: "));
	_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);




	//delay(1000);
	_SERIAL_DEBUG_CHANNEL_.println("");


#ifdef _OUTPUT_MUX2_
	//AMUX 2
	_SERIAL_DEBUG_CHANNEL_.println(F("==AMUX2=="));
	

	//Ch 0
	val = analogSignals->getRawADCValueOf(VOLTAGE_5_ANALOGCCA);
	_SERIAL_DEBUG_CHANNEL_.print(F("VOLTAGE_5_ANALOGCCA_RAW: "));
	_SERIAL_DEBUG_CHANNEL_.println(val);
	val_Dbl = analogSignals->getVoltageValueOf(VOLTAGE_5_ANALOGCCA);
	_SERIAL_DEBUG_CHANNEL_.print(F("VOLTAGE_5_ANALOGCCA_ACTUAL: "));
	_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);
f


	//Ch 1
	val = analogSignals->getRawADCValueOf(CURRENT_3D3_SW12D5A);
	_SERIAL_DEBUG_CHANNEL_.print(F("CURRENT_3D3_SW12D5A_RAW: "));
	_SERIAL_DEBUG_CHANNEL_.println(val);
	val_Dbl = analogSignals->getCurrentValueOf(CURRENT_3D3_SW12D5A, ACS711_12D5A);
	_SERIAL_DEBUG_CHANNEL_.print(F("CURRENT_3D3_SW12D5A_ACTUAL: "));
	_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);



	//Ch 2
	val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING);
	_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING_RAW: "));
	_SERIAL_DEBUG_CHANNEL_.println(val);
	val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING);
	_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING_ACTUAL: "));
	_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);


	//Ch 3
	val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING);
	_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING_RAW: "));
	_SERIAL_DEBUG_CHANNEL_.println(val);
	val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING);
	_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING_ACTUAL: "));
	_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);



	//Ch 4
	val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING);
	_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING_RAW: "));
	_SERIAL_DEBUG_CHANNEL_.println(val);
	val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING);
	_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING_ACTUAL: "));
	_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);


	//Ch 5
	val = analogSignals->getRawADCValueOf(TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR);
	_SERIAL_DEBUG_CHANNEL_.print(F("TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR_RAW: "));
	_SERIAL_DEBUG_CHANNEL_.println(val);
	val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR, RESISTOR_TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR);
	_SERIAL_DEBUG_CHANNEL_.print(F("TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR_ACTUAL: "));
	_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);


	//Ch 6
	val = analogSignals->getRawADCValueOf(TEMPSENSOR_DIGITALCCA_MIDDLESIDE);
	_SERIAL_DEBUG_CHANNEL_.print(F("TEMPSENSOR_DIGITALCCA_MIDDLESIDE_RAW: "));
	_SERIAL_DEBUG_CHANNEL_.println(val);
	val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_DIGITALCCA_MIDDLESIDE, RESISTOR_TEMPSENSOR_DIGITALCCA_MIDDLESIDE);
	_SERIAL_DEBUG_CHANNEL_.print(F("TEMPSENSOR_DIGITALCCA_MIDDLESIDE_ACTUAL: "));
	_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);


	//delay(1000);
	_SERIAL_DEBUG_CHANNEL_.println("");
	

#endif

#ifdef _OUTPUT_MUX3_
	//AMUX 3
	_SERIAL_DEBUG_CHANNEL_.println(F("==AMUX3=="));
	

	//Ch 0
	val = analogSignals->getRawADCValueOf(VOLTAGE_3D3_SW);
	_SERIAL_DEBUG_CHANNEL_.print(F("VOLTAGE_3D3_SW_RAW: "));
	_SERIAL_DEBUG_CHANNEL_.println(val);
	val_Dbl = analogSignals->getVoltageValueOf(VOLTAGE_3D3_SW);
	_SERIAL_DEBUG_CHANNEL_.print(F("VOLTAGE_3D3_SW_ACTUAL: "));
	_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);


	//Ch 1
	val = analogSignals->getRawADCValueOf(CURRENT_MOTORCTRLR_CH1_12D5A);
	_SERIAL_DEBUG_CHANNEL_.print(F("CURRENT_MOTORCTRLR_CH1_12D5A_RAW: "));
	_SERIAL_DEBUG_CHANNEL_.println(val);
	val_Dbl = analogSignals->getCurrentValueOf(CURRENT_MOTORCTRLR_CH1_12D5A, ACS711_12D5A);
	_SERIAL_DEBUG_CHANNEL_.print(F("CURRENT_MOTORCTRLR_CH1_12D5A_ACTUAL: "));
	_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);
	

	//Ch 2
	val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING);
	_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING_RAW: "));
	_SERIAL_DEBUG_CHANNEL_.println(val);
	val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING);
	_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING_ACTUAL: "));
	_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);


	//Ch 3
	val = analogSignals->getRawADCValueOf(PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK);
	_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK_RAW: "));
	_SERIAL_DEBUG_CHANNEL_.println(val);
	val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK, RESISTOR_PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK);
	_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK_ACTUAL: "));
	_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);



	//Ch 4
	val = analogSignals->getRawADCValueOf(PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING);
	_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING_RAW: "));
	_SERIAL_DEBUG_CHANNEL_.println(val);
	val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING, RESISTOR_PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING);
	_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING_ACTUAL: "));
	_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);


	//Ch 5
	val = analogSignals->getRawADCValueOf(TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK);
	_SERIAL_DEBUG_CHANNEL_.print(F("TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK_RAW: "));
	_SERIAL_DEBUG_CHANNEL_.println(val);
	val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK, RESISTOR_TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK);
	_SERIAL_DEBUG_CHANNEL_.print(F("TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK_ACTUAL: "));
	_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);

	
	//delay(1000);
	_SERIAL_DEBUG_CHANNEL_.println("");
	

#endif

#ifdef _OUTPUT_MUX4_
	//AMUX 4
	_SERIAL_DEBUG_CHANNEL_.println(F("==AMUX4=="));

		//Ch 0
	
		val = analogSignals->getRawADCValueOf(GAS_BEACONCCA_RIGHTPOINTING);
		_SERIAL_DEBUG_CHANNEL_.print(F("GAS_BEACONCCA_RIGHTPOINTING_RAW: "));
		_SERIAL_DEBUG_CHANNEL_.println(val);

		//only output the MQ gas sensor actual values once the MQ sensor has warmed up for at least 3 minutes and is calibrated
		if (analogSignals->gasSensorIsCalibrated())
		{
			//Note: Calibration takes about 6 secs (due to the parallel processing code)
			analogSignals->readGasSensor(mqGasSensor, counterGasRead);



			//only output the MQ gas sensor gas values once the MQ sensor read is complete
			if (analogSignals->gasSensorDoneReading())
			{
				val = analogSignals->getGasValueOf(mqGasSensor);
				_SERIAL_DEBUG_CHANNEL_.print(F("GAS_BEACONCCA_RIGHTPOINTING_ACTUAL (new): "));
				_SERIAL_DEBUG_CHANNEL_.print(val);
				_SERIAL_DEBUG_CHANNEL_.print(F(" "));//add a space
				_SERIAL_DEBUG_CHANNEL_.println(analogSignals->getMqGasSensorUnit(mqGasSensor));
			}
			else
			{
				val = analogSignals->getGasValueOf(mqGasSensor);
				_SERIAL_DEBUG_CHANNEL_.print(F("GAS_BEACONCCA_RIGHTPOINTING_ACTUAL (old): "));
				_SERIAL_DEBUG_CHANNEL_.print(val);
				_SERIAL_DEBUG_CHANNEL_.print(F(" "));//add a space
				_SERIAL_DEBUG_CHANNEL_.println(analogSignals->getMqGasSensorUnit(mqGasSensor));
			}

		}
		else
		{
			_SERIAL_DEBUG_CHANNEL_.print(F("GAS_BEACONCCA_RIGHTPOINTING_ACTUAL: "));
			_SERIAL_DEBUG_CHANNEL_.println(F("Still Initializing..."));
		}
	

		

		//Ch 1
		val = analogSignals->getRawADCValueOf(CURRENT_MOTORCTRLR_CH2_12D5A);
		_SERIAL_DEBUG_CHANNEL_.print(F("CURRENT_MOTORCTRLR_CH2_12D5A_RAW: "));
		_SERIAL_DEBUG_CHANNEL_.println(val);
		val_Dbl = analogSignals->getCurrentValueOf(CURRENT_MOTORCTRLR_CH2_12D5A, ACS711_12D5A);
		_SERIAL_DEBUG_CHANNEL_.print(F("CURRENT_MOTORCTRLR_CH2_12D5A_ACTUAL: "));
		_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);



		//Ch 2
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING);
		_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING_RAW: "));
		_SERIAL_DEBUG_CHANNEL_.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING);
		_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING_ACTUAL: "));
		_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);



		//Ch 3
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK);
		_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK_RAW: "));
		_SERIAL_DEBUG_CHANNEL_.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK, RESISTOR_PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK);
		_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK_ACTUAL: "));
		_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);


	
		//Ch 4
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING);
		_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING_RAW: "));
		_SERIAL_DEBUG_CHANNEL_.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING, RESISTOR_PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING);
		_SERIAL_DEBUG_CHANNEL_.print(F("PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING_ACTUAL: "));
		_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);


		//Ch 5
		val = analogSignals->getRawADCValueOf(TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE);
		_SERIAL_DEBUG_CHANNEL_.print(F("TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE_RAW: "));
		_SERIAL_DEBUG_CHANNEL_.println(val);
		val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE, RESISTOR_TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE);
		_SERIAL_DEBUG_CHANNEL_.print(F("TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE_ACTUAL: "));
		_SERIAL_DEBUG_CHANNEL_.println(val_Dbl);




		

		_SERIAL_DEBUG_CHANNEL_.println("");		
		//delay(1000);
#endif	


		
		_SERIAL_DEBUG_CHANNEL_.println(F("--END--"));
		//print blank lines for spacing
		_SERIAL_DEBUG_CHANNEL_.println("");
		_SERIAL_DEBUG_CHANNEL_.println("");


		//delay(4000);


	


}


