//RoverSleeperClient.h
#ifndef _ROVERSLEEPER_CLIENT_H
#define _ROVERSLEEPER_CLIENT_H

	#include <Arduino.h>

//The sleeper local is used to locally control the sleep and wakeup of itself
//The sleeper server is used to control the sleep and wakeup of itself, controlled remotely
//The sleeper client is used to remotely control the sleep and wakeup on a server

	
	class RoverSleeperClient {
	public:
		RoverSleeperClient(byte);//constructor. (wakeup pin)
		~RoverSleeperClient();//destructor
		void goToSleep();//To go to sleep, just send the command the Sleeper Server is expecting. This function just updates the flag variable
		void wakeUp();
		boolean isAwake();
	private:
		byte wakeUpPin;
		boolean awake;
	};







#endif 