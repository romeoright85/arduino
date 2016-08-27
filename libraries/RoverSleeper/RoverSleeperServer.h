//RoverSleeperServer.h
#ifndef _ROVERSLEEPER_SERVER_H
#define _ROVERSLEEPER_SERVER_H

	#include <Arduino.h>
	#include <RoverReset.h>
	
	/*******************************************************************
	Configure (define) flags before calling #include <RoverConfig.h>
	/********************************************************************/
	
	//Since all the Arduinos use this class, define/activate them all
		
	//define Arduino 1: AUXI in order to use it's config pins
	#ifndef _ARD_2_AUXI_H
		#define _ARD_2_AUXI_H		
	#endif
		
	//define Arduino 2: NAVI in order to use it's config pins
	#ifndef _ARD_1_NAVI_H
		#define _ARD_1_NAVI_H		
	#endif
		
	//define Arduino 3: MAIN in order to use it's config pins
	#ifndef _ARD_3_MAIN_H
		#define _ARD_3_MAIN_H		
	#endif
		
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
	
	class RoverSleeperServer : public virtual RoverReset {
	public:
		RoverSleeperServer(byte, voidFuncPtr);//constructor. Used for self wakeup/sleeping. (wakeup control pin, interrupt_service_routine)
		~RoverSleeperServer();//destructor
		void hasAwoken();//interrupt service routine (ISR)
		void goToSleep();
		void isrUpdate();//updates the awake variable when the interrupt service routine (ISR) is called. (can't do much else because the isr has to happen fast or the program will not work)
		boolean isAwake();
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	private:
		byte wakeUpPin;
		byte interruptChannel;
		voidFuncPtr interruptDispatch;
		boolean awake;		
	};







#endif 