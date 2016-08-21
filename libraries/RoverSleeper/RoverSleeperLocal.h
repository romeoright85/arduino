//RoverSleeperLocal.h
#ifndef _ROVERSLEEPER_LOCAL_H
#define _ROVERSLEEPER_LOCAL_H

	#include <Arduino.h>

	/*******************************************************************
	Configure (define) flags before calling #include <RoverConfig.h>
	/********************************************************************/
	//define Arduino 4: COMM in order to use it's config pins
	#ifndef _ARD_4_COMM_H
		#define _ARD_4_COMM_H		
	#endif
	
	/********************************************************************/

	#include <RoverConfig.h>

//The sleeper local is used to locally control the sleep and wakeup of itself
//The sleeper server is used to control the sleep and wakeup of itself, controlled remotely
//The sleeper client is used to remotely control the sleep and wakeup on a server

	typedef void (*voidFuncPtr)(void);//defining the type voidFuncPtr that is a function pointer that takes no arguments and returns void. It is used later on for the interrupt service routine.
	
	class RoverSleeperLocal {
	public:
		RoverSleeperLocal(byte, voidFuncPtr);//constructor. Used for self wakeup/sleeping. (wakeup control pin, interrupt_service_routine)
		~RoverSleeperLocal();//destructor
		void hasAwoken();//interrupt service routine (ISR)
		void goToSleep();
		void isrUpdate();//updates the awake variable when the interrupt service routine (ISR) is called. (can't do much else because the isr has to happen fast or the program will not work)
		boolean isAwake();
	private:
		byte wakeUpPin;
		byte interruptChannel;
		voidFuncPtr interruptDispatch;
		boolean awake;
		
	};







#endif 