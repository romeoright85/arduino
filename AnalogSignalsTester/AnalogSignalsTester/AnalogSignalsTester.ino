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

#ifdef _DEBUG_COMM_BROADCAST
	Serial2.println(F("Gas Sensor Warming Up And Calibrating - Wait ~3:26"));
#else
	Serial.println(F("Gas Sensor Warming Up And Calibrating - Wait ~3:26"));
#endif
	

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

#ifdef _DEBUG_COMM_BROADCAST
	Serial2.println(F("--START--"));
	Serial2.println("");
#else
	Serial.println(F("--START--"));
	Serial.println("");
#endif


#ifdef _OUTPUT_MUX1_
		//AMUX 1
	#ifdef _DEBUG_COMM_BROADCAST
		Serial2.println(F("==AMUX1=="));
	#else
		Serial.println(F("==AMUX1=="));
	#endif
		

		//Ch 0		
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(VOLTAGE_7D2_RAW);
		Serial2.print(F("VOLTAGE_7D2_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getVoltageValueOf(VOLTAGE_7D2_RAW);
		Serial2.print(F("VOLTAGE_7D2_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(VOLTAGE_7D2_RAW);
		Serial.print(F("VOLTAGE_7D2_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getVoltageValueOf(VOLTAGE_7D2_RAW);
		Serial.print(F("VOLTAGE_7D2_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif


		//Ch 1
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(CURRENT_7D2_PRESW25A);
		Serial2.print(F("CURRENT_7D2_PRESW25A_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getCurrentValueOf(CURRENT_7D2_PRESW25A, ACS711_25A);
		Serial2.print(F("CURRENT_7D2_PRESW25A_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(CURRENT_7D2_PRESW25A);
		Serial.print(F("CURRENT_7D2_PRESW25A_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getCurrentValueOf(CURRENT_7D2_PRESW25A, ACS711_25A);
		Serial.print(F("CURRENT_7D2_PRESW25A_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif



		//Ch 2
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(CURRENT_7D2_SW12D5A);
		Serial2.print(F("CURRENT_7D2_SW12D5A_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getCurrentValueOf(CURRENT_7D2_SW12D5A, ACS711_12D5A);
		Serial2.print(F("CURRENT_7D2_SW12D5A_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(CURRENT_7D2_SW12D5A);
		Serial.print(F("CURRENT_7D2_SW12D5A_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getCurrentValueOf(CURRENT_7D2_SW12D5A, ACS711_12D5A);
		Serial.print(F("CURRENT_7D2_SW12D5A_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif


		//Ch 3
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING);
		Serial2.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING);
		Serial2.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_LEFTPOINTING_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif

	
		//Ch 4
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING);
		Serial2.print(F("PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING, RESISTOR_PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING);
		Serial2.print(F("PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING);
		Serial.print(F("PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING, RESISTOR_PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING);
		Serial.print(F("PHOTOSENSOR_GPSCCA_REARSIDE_UPWARDPOINTING_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif

	
		//Ch 5
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(TEMPSENSOR_BEACONCCA_CENTERSIDE);
		Serial2.print(F("TEMPSENSOR_BEACONCCA_CENTERSIDE_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_BEACONCCA_CENTERSIDE, RESISTOR_TEMPSENSOR_BEACONCCA_CENTERSIDE);
		Serial2.print(F("TEMPSENSOR_BEACONCCA_CENTERSIDE_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(TEMPSENSOR_BEACONCCA_CENTERSIDE);
		Serial.print(F("TEMPSENSOR_BEACONCCA_CENTERSIDE_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_BEACONCCA_CENTERSIDE, RESISTOR_TEMPSENSOR_BEACONCCA_CENTERSIDE);
		Serial.print(F("TEMPSENSOR_BEACONCCA_CENTERSIDE_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif

	
		//Ch 6
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET);
		Serial2.print(F("TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET, RESISTOR_TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET);
		Serial2.print(F("TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET);
		Serial.print(F("TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET, RESISTOR_TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET);
		Serial.print(F("TEMPSENSOR_POWERCCA_CENTERSIDE_MTRMOSFET_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif



		//delay(1000);
	#ifdef _DEBUG_COMM_BROADCAST
		Serial2.println("");
	#else
		Serial.println("");
	#endif
	
#endif

#ifdef _OUTPUT_MUX2_
	//AMUX 2
	#ifdef _DEBUG_COMM_BROADCAST
		Serial2.println(F("==AMUX2=="));
	#else
		Serial.println(F("==AMUX2=="));
	#endif
	

	//Ch 0
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(VOLTAGE_5_ANALOGCCA);
		Serial2.print(F("VOLTAGE_5_ANALOGCCA_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getVoltageValueOf(VOLTAGE_5_ANALOGCCA);
		Serial2.print(F("VOLTAGE_5_ANALOGCCA_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(VOLTAGE_5_ANALOGCCA);
		Serial.print(F("VOLTAGE_5_ANALOGCCA_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getVoltageValueOf(VOLTAGE_5_ANALOGCCA);
		Serial.print(F("VOLTAGE_5_ANALOGCCA_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif


	//Ch 1
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(CURRENT_3D3_SW12D5A);
		Serial2.print(F("CURRENT_3D3_SW12D5A_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getCurrentValueOf(CURRENT_3D3_SW12D5A, ACS711_12D5A);
		Serial2.print(F("CURRENT_3D3_SW12D5A_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(CURRENT_3D3_SW12D5A);
		Serial.print(F("CURRENT_3D3_SW12D5A_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getCurrentValueOf(CURRENT_3D3_SW12D5A, ACS711_12D5A);
		Serial.print(F("CURRENT_3D3_SW12D5A_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif


	//Ch 2
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING);
		Serial2.print(F("PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING);
		Serial2.print(F("PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_CENTERSIDE_UPWARDPOINTING_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif


	//Ch 3
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING);
		Serial2.print(F("PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING);
		Serial2.print(F("PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_REARSIDE_REARPOINTING_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif



	//Ch 4
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING);
		Serial2.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING);
		Serial2.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_LEFTSIDE_UPWARDPOINTING_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif


	//Ch 5
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR);
		Serial2.print(F("TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR, RESISTOR_TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR);
		Serial2.print(F("TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR);
		Serial.print(F("TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR, RESISTOR_TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR);
		Serial.print(F("TEMPSENSOR_CURRENTCCA_CENTERSIDE_POWERRESISTOR_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif


	//Ch 6
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(TEMPSENSOR_DIGITALCCA_MIDDLESIDE);
		Serial2.print(F("TEMPSENSOR_DIGITALCCA_MIDDLESIDE_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_DIGITALCCA_MIDDLESIDE, RESISTOR_TEMPSENSOR_DIGITALCCA_MIDDLESIDE);
		Serial2.print(F("TEMPSENSOR_DIGITALCCA_MIDDLESIDE_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(TEMPSENSOR_DIGITALCCA_MIDDLESIDE);
		Serial.print(F("TEMPSENSOR_DIGITALCCA_MIDDLESIDE_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_DIGITALCCA_MIDDLESIDE, RESISTOR_TEMPSENSOR_DIGITALCCA_MIDDLESIDE);
		Serial.print(F("TEMPSENSOR_DIGITALCCA_MIDDLESIDE_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif


	//delay(1000);
	#ifdef _DEBUG_COMM_BROADCAST
		Serial2.println("");
	#else
		Serial.println("");
	#endif
	

#endif

#ifdef _OUTPUT_MUX3_
	//AMUX 3
	#ifdef _DEBUG_COMM_BROADCAST
		Serial2.println(F("==AMUX3=="));
	#else
		Serial.println(F("==AMUX3=="));
	#endif
	

	//Ch 0
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(VOLTAGE_3D3_SW);
		Serial2.print(F("VOLTAGE_3D3_SW_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getVoltageValueOf(VOLTAGE_3D3_SW);
		Serial2.print(F("VOLTAGE_3D3_SW_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(VOLTAGE_3D3_SW);
		Serial.print(F("VOLTAGE_3D3_SW_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getVoltageValueOf(VOLTAGE_3D3_SW);
		Serial.print(F("VOLTAGE_3D3_SW_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif


	//Ch 1
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(CURRENT_MOTORCTRLR_CH1_12D5A);
		Serial2.print(F("CURRENT_MOTORCTRLR_CH1_12D5A_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getCurrentValueOf(CURRENT_MOTORCTRLR_CH1_12D5A, ACS711_12D5A);
		Serial2.print(F("CURRENT_MOTORCTRLR_CH1_12D5A_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(CURRENT_MOTORCTRLR_CH1_12D5A);
		Serial.print(F("CURRENT_MOTORCTRLR_CH1_12D5A_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getCurrentValueOf(CURRENT_MOTORCTRLR_CH1_12D5A, ACS711_12D5A);
		Serial.print(F("CURRENT_MOTORCTRLR_CH1_12D5A_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif


	//Ch 2
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING);
		Serial2.print(F("PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING);
		Serial2.print(F("PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_FRONTSIDE_FORWARDPOINTING_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif


	//Ch 3
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK);
		Serial2.print(F("PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK, RESISTOR_PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK);
		Serial2.print(F("PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK);
		Serial.print(F("PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK, RESISTOR_PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK);
		Serial.print(F("PHOTOSENSOR_CURRENTCCA_CENTERSIDE_UPWARDPOINTING_MIDDLEDECK_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif



	//Ch 4
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING);
		Serial2.print(F("PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING, RESISTOR_PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING);
		Serial2.print(F("PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING);
		Serial.print(F("PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING, RESISTOR_PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING);
		Serial.print(F("PHOTOSENSOR_POWERCCA_LEFTSIDE_LEFTPOINTING_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif


	//Ch 5
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK);
		Serial2.print(F("TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK, RESISTOR_TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK);
		Serial2.print(F("TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK);
		Serial.print(F("TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK, RESISTOR_TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK);
		Serial.print(F("TEMPSENSOR_GPSCCA_REARSIDE_UPPERDECK_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif


	
	//delay(1000);
	#ifdef _DEBUG_COMM_BROADCAST
		Serial2.println("");
	#else
		Serial.println("");
	#endif

#endif

#ifdef _OUTPUT_MUX4_
	//AMUX 4
	#ifdef _DEBUG_COMM_BROADCAST
		Serial2.println(F("==AMUX4=="));
	#else
		Serial.println(F("==AMUX4=="));
	#endif
		

		//Ch 0
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(GAS_BEACONCCA_RIGHTPOINTING);
		Serial2.print(F("GAS_BEACONCCA_RIGHTPOINTING_RAW: "));
		Serial2.println(val);

		//only output the MQ gas sensor actual values once the MQ sensor has warmed up for at least 3 minutes and is calibrated
		if (analogSignals->gasSensorIsCalibrated())
		{
			//Note: Calibration takes about 6 secs (due to the parallel processing code)
			analogSignals->readGasSensor(mqGasSensor, counterGasRead);



			//only output the MQ gas sensor gas values once the MQ sensor read is complete
			if (analogSignals->gasSensorDoneReading())
			{
				val = analogSignals->getGasValueOf(mqGasSensor);
				Serial2.print(F("GAS_BEACONCCA_RIGHTPOINTING_ACTUAL (new): "));
				Serial2.print(val);
				Serial2.print(F(" "));//add a space
				Serial2.println(analogSignals->getMqGasSensorUnit(mqGasSensor));
			}
			else
			{
				val = analogSignals->getGasValueOf(mqGasSensor);
				Serial2.print(F("GAS_BEACONCCA_RIGHTPOINTING_ACTUAL (old): "));
				Serial2.print(val);
				Serial2.print(F(" "));//add a space
				Serial2.println(analogSignals->getMqGasSensorUnit(mqGasSensor));
			}

		}
		else
		{
			Serial2.print(F("GAS_BEACONCCA_RIGHTPOINTING_ACTUAL: "));
			Serial2.println(F("Still Initializing..."));
		}
	#else
		val = analogSignals->getRawADCValueOf(GAS_BEACONCCA_RIGHTPOINTING);
		Serial.print(F("GAS_BEACONCCA_RIGHTPOINTING_RAW: "));
		Serial.println(val);

		//only output the MQ gas sensor actual values once the MQ sensor has warmed up for at least 3 minutes and is calibrated
		if (analogSignals->gasSensorIsCalibrated())
		{
			//Note: Calibration takes about 6 secs (due to the parallel processing code)
			analogSignals->readGasSensor(mqGasSensor, counterGasRead);



			//only output the MQ gas sensor gas values once the MQ sensor read is complete
			if (analogSignals->gasSensorDoneReading())
			{
				val = analogSignals->getGasValueOf(mqGasSensor);
				Serial.print(F("GAS_BEACONCCA_RIGHTPOINTING_ACTUAL (new): "));
				Serial.print(val);
				Serial.print(F(" "));//add a space
				Serial.println(analogSignals->getMqGasSensorUnit(mqGasSensor));
			}
			else
			{
				val = analogSignals->getGasValueOf(mqGasSensor);
				Serial.print(F("GAS_BEACONCCA_RIGHTPOINTING_ACTUAL (old): "));
				Serial.print(val);
				Serial.print(F(" "));//add a space
				Serial.println(analogSignals->getMqGasSensorUnit(mqGasSensor));
			}

		}
		else
		{
			Serial.print(F("GAS_BEACONCCA_RIGHTPOINTING_ACTUAL: "));
			Serial.println(F("Still Initializing..."));
		}
	#endif

		

		//Ch 1
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(CURRENT_MOTORCTRLR_CH2_12D5A);
		Serial2.print(F("CURRENT_MOTORCTRLR_CH2_12D5A_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getCurrentValueOf(CURRENT_MOTORCTRLR_CH2_12D5A, ACS711_12D5A);
		Serial2.print(F("CURRENT_MOTORCTRLR_CH2_12D5A_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(CURRENT_MOTORCTRLR_CH2_12D5A);
		Serial.print(F("CURRENT_MOTORCTRLR_CH2_12D5A_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getCurrentValueOf(CURRENT_MOTORCTRLR_CH2_12D5A, ACS711_12D5A);
		Serial.print(F("CURRENT_MOTORCTRLR_CH2_12D5A_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif



		//Ch 2
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING);
		Serial2.print(F("PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING);
		Serial2.print(F("PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING, RESISTOR_PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING);
		Serial.print(F("PHOTOSENSOR_BEACONCCA_RIGHTSIDE_RIGHTPOINTING_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif


		//Ch 3
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK);
		Serial2.print(F("PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK, RESISTOR_PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK);
		Serial2.print(F("PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK);
		Serial.print(F("PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK, RESISTOR_PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK);
		Serial.print(F("PHOTOSENSOR_CURRENTCCA_FRONTUPWARDPOINTING_MIDDLEDECK_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif

	
		//Ch 4
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING);
		Serial2.print(F("PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING, RESISTOR_PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING);
		Serial2.print(F("PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING);
		Serial.print(F("PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getLightValueOf(PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING, RESISTOR_PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING);
		Serial.print(F("PHOTOSENSOR_DIGITALCCA_LEFTSIDE_UPWARDPOINTING_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif


		//Ch 5
	#ifdef _DEBUG_COMM_BROADCAST
		val = analogSignals->getRawADCValueOf(TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE);
		Serial2.print(F("TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE_RAW: "));
		Serial2.println(val);
		val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE, RESISTOR_TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE);
		Serial2.print(F("TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE_ACTUAL: "));
		Serial2.println(val_Dbl);
	#else
		val = analogSignals->getRawADCValueOf(TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE);
		Serial.print(F("TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE_RAW: "));
		Serial.println(val);
		val_Dbl = analogSignals->getTempValueOf(TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE, RESISTOR_TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE);
		Serial.print(F("TEMPSENSOR_POWERCCA_FRONTSIDE_CHARGER_SOLAR_OR_GATE_ACTUAL: "));
		Serial.println(val_Dbl);
	#endif



		
	#ifdef _DEBUG_COMM_BROADCAST
		Serial2.println("");		
	#else
		Serial.println("");		
	#endif	
		//delay(1000);
#endif	


		
	#ifdef _DEBUG_COMM_BROADCAST		
		Serial2.println(F("--END--"));
		//print blank lines for spacing
		Serial2.println("");
		Serial2.println("");
	#else		
		Serial.println(F("--END--"));
		//print blank lines for spacing
		Serial.println("");
		Serial.println("");		
	#endif

		//delay(4000);


	


}


