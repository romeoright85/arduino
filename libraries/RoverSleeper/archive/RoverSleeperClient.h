//RoverSleeperClient.h
#ifndef _ROVERSLEEPER_CLIENT_H
#define _ROVERSLEEPER_CLIENT_H

	#include <Arduino.h>

//The sleeper local is used to locally control the sleep and wakeup of itself
//The sleeper server is used to control the sleep and wakeup of itself, controlled remotely
//The sleeper client is used to remotely control the sleep and wakeup on a server

	
	class RoverSleeperClient {
	public:
		RoverSleeperClient(RoverSerial, RoverCommand );//constructor. (RoverSerial Object in order to send the remote wakeup and sleep commands, character array aka string that holds the command to sleep the server)
		~RoverSleeperClient();//destructor
		void wakeup();
		void goToSleep();
	};







#endif 