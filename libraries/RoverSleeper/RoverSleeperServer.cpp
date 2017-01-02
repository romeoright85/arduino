#include <RoverSleeperServer.h>



RoverSleeperServer::RoverSleeperServer(byte wakeUpPin, voidFuncPtr interruptDispatch)
{
	this->_wakeUpPin = wakeUpPin;
	this->_interruptDispatch = interruptDispatch;
	this->_interruptChannel = digitalPinToInterrupt(this->_wakeUpPin); //calling an Arduino function
	pinMode(this->_wakeUpPin, INPUT);
	this->_awake = true;//initialize variable
}
RoverSleeperServer::~RoverSleeperServer()
{
	//do nothing
}

void RoverSleeperServer::goToSleep()
{
   
   
   //NOTE: Make sure to stop any software serials before calling this function or it won't go to sleep.
   


   //attach the interrupt on the wakeUpPin, call the  interruptDispatch, and do it when the pin goes low
/*
	Note:
	Rising interrupts do work on the Mega, but when you use it for sleep it won't work.
	It seems that only level works for the interrupt waking up. Probably because
	when you use attackInterrupt(0) (aka int.0) it is actually int4, and according
	to the datasheet, int4 will only work on level mode to wake up in sleep mode.
*/
	attachInterrupt(this->_interruptChannel, this->_interruptDispatch, LOW); //calling an Arduino function attachInterrupt()

   this->_awake = false;//update the awake flag to reflect current status


  /*
    See 9.11.1 SMCR – Sleep Mode Control Register of pdf below:
    http://www.atmel.com/Images/doc8161.pdf
     
    Bit 7: Read Only, Set to 0
    Bit 6: Read Only, Set to 0
    Bit 5: Read Only, Set to 0
    Bit 4: Read Only, Set to 0
    Bit 3: SM2: Sleep Mode Select Bit 2, Set to 0 (for power-down mode per Table 9-2)
    Bit 2: SM1: Sleep Mode Select Bit 1, Set to 1 (for power-down mode per Table 9-2)
    Bit 1: SM0: Sleep Mode Select Bit 0, Set to 0 (for power-down mode per Table 9-2)
    Bit 0: SE: Sleep Enable, Set to 1 (to make the MCU enter sleep mode when the SLEEP instruction (using the in line assembler) is executed
    SMCR = B00000101
   
  */
	#ifdef _DEBUG_STAY_AWAKE
		Serial.println(F("Debug Sleep"));//DEBUG
		//Note: In _DEBUG_STAY_AWAKE mode, the Arduino never actually sleeps. It will call the hasAwoken() function on it's own after the delay below.
		delay(10000);//DEBUG, allow some time to test the interrupts.
	#else
		SMCR = B00000101;//Sleep mode control register, Power Down mode and Enable Sleep
		__asm__  __volatile__("sleep");// In line assembler to execute the sleep function
   	#endif
   //once wakeUpPin receives the right signal level or edge, the interrupt will call interruptDispatch, then the program will resume here after waking up

  /*
    See 9.11.1 SMCR – Sleep Mode Control Register of pdf below:
    http://www.atmel.com/Images/doc8161.pdf
     
    Bit 7: Read Only, Set to 0
    Bit 6: Read Only, Set to 0
    Bit 5: Read Only, Set to 0
    Bit 4: Read Only, Set to 0
    Bit 3: SM2: Sleep Mode Select Bit 2, Set to 0 (for power-down mode per Table 9-2)
    Bit 2: SM1: Sleep Mode Select Bit 1, Set to 1 (for power-down mode per Table 9-2)
    Bit 1: SM0: Sleep Mode Select Bit 0, Set to 0 (for power-down mode per Table 9-2)
    Bit 0: SE: Sleep Enable, Set to 0 (clear this bit after waking up)
    SMCR = B00000100
   
  */  	
   
   
   //NOTE: Make sure to start any software serials right after this function to have that capability again
   
	return;
	
	
}


void RoverSleeperServer::hasAwoken()
{	
	#ifdef _DEBUG_STAY_AWAKE
		Serial.println(F("Debug Wake"));
		this->_awake = true;//update the awake flag to reflect current status
	#endif
	
	
	if(this->_awake)//awake flag will be updated by isrUpdate() 
	{
		SMCR = B00000100;// turn off bit 0 to disable the ability to sleep
		detachInterrupt(this->_interruptChannel);//turn off the interrupt, so the program doesn't go crazy when awake
	}	
   	
	
	return;	
}

void RoverSleeperServer::isrUpdate()
{
	#ifdef _DEBUG_STAY_AWAKE
		Serial.println(F("Debug ISR Update"));	
	#else
		this->_awake = true;//update the awake flag to reflect current status
   	#endif

	
	return;	
}

boolean RoverSleeperServer::isAwake()
{
	return this->_awake;
}
void RoverSleeperServer::reset()
{
	//software reset
	
	
	this->_interruptChannel = digitalPinToInterrupt(this->_wakeUpPin); //calling an Arduino function
	pinMode(this->_wakeUpPin, INPUT);
	
	//it is assumed the rover is awake since if it isn't, it couldn't sw reset anyways	
	this->_awake = true;//initialize variable
	this->hasAwoken();
}












