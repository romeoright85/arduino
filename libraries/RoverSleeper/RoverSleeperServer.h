//RoverSleeperServer.h
#ifndef _ROVERSLEEPER_SERVER_H
#define _ROVERSLEEPER_SERVER_H

	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>

	
	//uncomment line below to test the interrupt function without sending the Arduino to sleep
	//#define _DEBUG_STAY_AWAKE
	//#define _DEBUG_PRINT_ISR_TRIGGERED
	
	
//Note: Allow about 8+ seconds for each Arduino to wake up and initialize from sleep.
	//So if you're waking up more than one Arduino serially by toggling the digital pin levels with a single parent ".ino" you have to take into account for the sum of all the 8+ seconds for each of the Arduinos.
	//Or you don't have to use delays and just send a low and keep it low for all the Arduinos. This is how it is currently implemented.
//Future Idea: You could send a low and poll for acknowledge of waking up if you real time closed loop feedback updates.

	
//Note: Since all the Arduinos use this class, you have to define them (i.e. #define _ARD_2_AUXI_H, #define _ARD_1_NAVI_H, #define _ARD_3_MAIN_H, or #define _ARD_4_COMM_H) in each of its .ino as there are shared naming conventions and will cause a conflict otherwise.

//The sleeper local is used to locally control the sleep and wakeup of itself
//The sleeper server is used to control the sleep and wakeup of itself, controlled remotely
//The sleeper client is used to remotely control the sleep and wakeup on a server


/*
	Note:
	Rising interrupts do work on the Mega, but when you use it for sleep it won't work.
	It seems that only level works for the interrupt waking up. Probably because
	when you use attackInterrupt(0) (aka int.0) it is actually int4, and according
	to the datasheet, int4 will only work on level mode to wake up in sleep mode.
*/

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