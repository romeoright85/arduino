#include <RoverSleeperClient.h>

//The server is used to control the sleep and wakeup of itself
//The client is used to remotely control the sleep and wakeup on a server

RoverSleeperClient::RoverSleeperClient(byte wakeUpPin)
{
	this->_wakeUpPin = wakeUpPin;
	this->_awake = true;//initialize variable
}
RoverSleeperClient::~RoverSleeperClient()
{
	//do nothing
}
void RoverSleeperClient::goToSleep()
{
	this->_awake = false;//update the awake flag to reflect current status
	//The actuallly sleep is done by sending it a command over serial, which is processed and the server goes to sleep at that time
}
boolean RoverSleeperClient::isAwake()
{
	return this->_awake;
}
void RoverSleeperClient::wakeUp()
{
	//Note: The servers should be able to go to sleep at any time (on its's own), so the default pin should be high so it can be ready to go low at anytime to wake it up again)
	//Toggle the wakeup pin to create a LOW level for the interrupt
	digitalWrite(this->_wakeUpPin,LOW);//set the controlling pin to the server interrupt to low to wake it up
	this->_awake = true;//update the awake flag to reflect current status
	delay(20);//wait for 20ms
	digitalWrite(this->_wakeUpPin,HIGH);//resets the controlling pin to the server interrupt to high to allow it to sleep
  
}
void RoverSleeperClient::reset()
{
	//this will awake any servers the client is connected to
	this->wakeUp();
}