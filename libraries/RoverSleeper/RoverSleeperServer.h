//RoverSleeperServer.h
#ifndef _ROVERSLEEPER_SERVER_H
#define _ROVERSLEEPER_SERVER_H

	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>

	
//Note: Since all the Arduinos use this class, you have to define them (i.e. #define _ARD_2_AUXI_H, #define _ARD_1_NAVI_H, #define _ARD_3_MAIN_H, or #define _ARD_4_COMM_H) in each of its .ino as there are shared naming conventions and will cause a conflict otherwise.

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
		byte _wakeUpPin;
		byte _interruptChannel;
		voidFuncPtr _interruptDispatch;
		boolean _awake;		
	};







#endif 