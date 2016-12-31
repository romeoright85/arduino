//Used for AUXI - 2

#include <ImuSensor.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>
#include <StopWatch.h>


DelayCounter * counter50Hz = new DelayCounter(DELAY_4_PERIODS);//initialize it to count to 4 periods
DelayCounter * counter10Hz = new DelayCounter(DELAY_2_PERIODS);//initialize it to count to 2 periods
GlobalDelayTimer * timer50Hz = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, counter50Hz);//set each period to be 5ms long (delay interval)
GlobalDelayTimer * timer10Hz = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, counter10Hz);//set each period to be 5ms long (delay interval)
StopWatch * stopWatch = new StopWatch();


RoverReset * resetArray[] = { counter50Hz, counter10Hz, timer50Hz, timer10Hz, stopWatch };






void setup()
{
	Serial.begin(PC_USB_BAUD_RATE);
	
	Imu_Init();	
		
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
		
	stopWatch->startStopWatch();//start/reset the stop watch
	delay(20);
	
}

void loop() //Main Loop
{
	timer50Hz->Running();//activate the timer
	timer10Hz->Running();//activate the timer
	
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
		
		

		
		Serial.print(F("Heading: "));
		Serial.println(getHeading());
		Serial.print(F("Roll: "));
		Serial.println(getRoll());
		Serial.print(F("Pitch: "));
		Serial.println(getPitch());
		Serial.print(F("Yaw: "));
		Serial.println(getYaw());
		


		printInAHRSFormat();
		
	}

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