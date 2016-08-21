//RoverSleeperServer.h
#ifndef _ROVERSLEEPER_SERVER_H
#define _ROVERSLEEPER_SERVER_H

	#include <Arduino.h>

//The sleeper local is used to locally control the sleep and wakeup of itself
//The sleeper server is used to control the sleep and wakeup of itself, controlled remotely
//The sleeper client is used to remotely control the sleep and wakeup on a server

	
	class RoverSleeperServer {
	public:
		RoverSleeperServer(RoverSerial *, byte);//constructor. (RoverSerial object pointer to establish communications with the client, wakeup control pin). Use for remote wakeup/sleeping.
		~RoverSleeperServer();//destructor
		void wakingUp();
		void goingToSleep();
	private:
		char[] sleepCommand;//holds the command to check in order to sleep (a specially formatted string)
		char[] wakeupCommand;//holds the command to check in order to sleep (a specially formatted string)
	};







#endif 