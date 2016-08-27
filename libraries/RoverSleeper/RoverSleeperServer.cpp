#include <RoverSleeperServer.h>



RoverSleeperServer::RoverSleeperServer(byte wakeUpPin, voidFuncPtr interruptDispatch)
{
	this->wakeUpPin = wakeUpPin;
	this->interruptDispatch = interruptDispatch;
	this->interruptChannel = digitalPinToInterrupt(this->wakeUpPin); //calling an Arduino function
	pinMode(this->wakeUpPin, INPUT);
	this->awake = true;//initialize variable
}
RoverSleeperServer::~RoverSleeperServer()
{
	//do nothing
}

void RoverSleeperServer::goToSleep()
{
   
   
   //NOTE: Make sure to stop any software serials before calling this function or it won't go to sleep.
   
   
   //attach the interrupt on the wakeUpPin, call the  interruptDispatch, and do it when the pin rises from 5V to 0V  
	attachInterrupt(this->interruptChannel, this->interruptDispatch, RISING); //calling an Arduino function attachInterrupt()
   
   
   this->awake = false;//update the awake flag to reflect current status
   
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
   
   SMCR = B00000101;//Sleep mode control register, Power Down mode and Enable Sleep
   __asm__  __volatile__("sleep");// In line assembler to execute the sleep function
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
	if(awake)//awake flag will be updated by isrUpdate() 
	{
		SMCR = B00000100;// turn off bit 0 to disable the ability to sleep
		detachInterrupt(this->interruptChannel);//turn off the interrupt, so the program doesn't go crazy when awake
	}
	return;	
}

void RoverSleeperServer::isrUpdate()
{
	this->awake = true;//update the awake flag to reflect current status
	return;	
}

boolean RoverSleeperServer::isAwake()
{
	return this->awake;
}
void RoverSleeperServer::reset()
{
	//software reset
	
	
	this->interruptChannel = digitalPinToInterrupt(this->wakeUpPin); //calling an Arduino function
	pinMode(this->wakeUpPin, INPUT);
	
	//it is assumed the rover is awake since if it isn't, it couldn't sw reset anyways	
	this->awake = true;//initialize variable
	this->hasAwoken();
}












