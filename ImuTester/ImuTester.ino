//Used for AUXI - 2


//Note: Make sure you run the calibration code:
//K:\Working Directory\DESIGN_PROJ\Design Projects\Robot\Workspaces\Arduino\2nd Gen Code\GitHub\arduino\libraries\RoverShared\IMU_Calibration


#include <ImuSensor.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>
#include <StopWatch.h>


//Uncomment to customize output
#define _DEBUG_OUTPUT_HEADING_
//#define _DEBUG_OUTPUT_ROLL_
//#define _DEBUG_OUTPUT_PITCH_
//#define _DEBUG_OUTPUT_YAW_
//#define _DEBUG_OUTPUT_AHRS_

//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast
//Note: You also have to uncomment _DEBUG_COMM_BROADCAST in ImuSensor.cpp

#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ _MAIN_SERIAL_ //When using COMM Broadcast, reroute the PC USB output to the channel to MAIN instead
#else
	#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_
#endif



DelayCounter * counter50Hz = new DelayCounter(DELAY_4_PERIODS);//initialize it to count to 4 periods
DelayCounter * counter10Hz = new DelayCounter(DELAY_2_PERIODS);//initialize it to count to 2 periods
GlobalDelayTimer * timer50Hz = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, counter50Hz);//set each period to be 5ms long (delay interval)
GlobalDelayTimer * timer10Hz = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, counter10Hz);//set each period to be 5ms long (delay interval)
StopWatch * stopWatch = new StopWatch();


RoverReset * resetArray[] = { counter50Hz, counter10Hz, timer50Hz, timer10Hz, stopWatch };






void setup()
{
	Serial.begin(PC_USB_BAUD_RATE);
	Serial2.begin(MAIN_BAUD_RATE);
	
	Imu_Init();	
		
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
		
	stopWatch->startStopWatch();//start/reset the stop watch
	delay(20);

	//Setting Up Timer Interrupt
	OCR0A = 0x7F;//Set the timer to interrupt somewhere in the middle of it's count, say 127 aka 7F in hex (since Timer0 is 8 bit and counts from 0 to 255)
	TIMSK0 |= _BV(OCIE0A);//Activating the Timer Interrupt by setting the Mask Register
	/*
	Reference:
	https://learn.adafruit.com/multi-tasking-the-arduino-part-2/timers
	http://forum.arduino.cc/index.php?topic=3240.0
	https://protostack.com.au/2010/09/timer-interrupts-on-an-atmega168/
	*/
	
}



SIGNAL(TIMER0_COMPA_vect)//Interrupt Service Routine
{
	//Tasks always running in the background, called by the timer about every 1 ms
	//This will allow the millis value to be checked every millisecond and not get missed.
	//Timer(s)
	timer50Hz->Running();//activate the timer
	timer10Hz->Running();//activate the timer
}




void loop() //Main Loop
{

	
	if (counter50Hz->countReached())  // Main loop runs at 50Hz
	{		
		counter50Hz->counterReset();

		stopWatch->recordStartTime();		
		stopWatch->startStopWatch();//start/reset the stop watch
				
		if (stopWatch->timeElapsedAfterRecordedTime())
		{
			
			G_Dt = (stopWatch->getElapsedTime()) / 1000.0;    // Real time of loop run. We use this on the DCM algorithm (gyro integration time)
			if (G_Dt > 0.2)
			{								
				G_Dt = 0; // ignore integration times over 200 ms
			}			
		}
		else
		{			
			G_Dt = 0;
		}


		// *** DCM algorithm
		// Data adquisition
		Read_Gyro();   // This read gyro data
		Read_Accel();     // Read I2C accelerometer

		if (counter10Hz->countReached())  // Read compass data at 10Hz...
		{
			counter10Hz->counterReset();
			Read_Compass();    // Read I2C magnetometer
			Compass_Heading(); // Calculate magnetic heading
		}

		// Calculations
		Imu_Calculations();

	#ifdef _DEBUG_OUTPUT_HEADING_
			_SERIAL_DEBUG_CHANNEL_.print(F("Heading: "));
			_SERIAL_DEBUG_CHANNEL_.println(getCorrectedHeading());
	#endif
	#ifdef _DEBUG_OUTPUT_ROLL_
			_SERIAL_DEBUG_CHANNEL_.print(F("Roll: "));
			_SERIAL_DEBUG_CHANNEL_.println(getRoll());
	#endif
	#ifdef _DEBUG_OUTPUT_PITCH_
			_SERIAL_DEBUG_CHANNEL_.print(F("Pitch: "));
			_SERIAL_DEBUG_CHANNEL_.println(getPitch());
	#endif
	#ifdef _DEBUG_OUTPUT_YAW_
			_SERIAL_DEBUG_CHANNEL_.print(F("Yaw: "));
			_SERIAL_DEBUG_CHANNEL_.println(getYaw());
	#endif
	#ifdef _DEBUG_OUTPUT_AHRS_
			printInAHRSFormat();
	#endif
	


	}

	delay(50);

}

/*

Sample IMU AHRS Data

!ANG:0.27,1.56,16.47
!ANG:0.24,1.57,16.46
!ANG:0.26,1.56,16.46
!ANG:0.38,1.61,16.47
!ANG:0.38,1.63,16.46
!ANG:0.42,1.63,16.47
!ANG:0.45,1.61,16.47
!ANG:0.41,1.61,16.47


*/