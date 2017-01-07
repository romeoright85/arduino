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
	digitalWrite(this->_wakeUpPin,HIGH);//reset the controlling pin to the server interrupt to high to allow it to sleep
	this->_awake = false;//update the awake flag to reflect current status
	//The actuallly sleep is done by sending it a command over serial, which is processed and the server goes to sleep at that time
}
boolean RoverSleeperClient::isAwake()
{
	return this->_awake;
}
void RoverSleeperClient::wakeUp()
{
  //Toggle the wakeup pin to create a LOW level for the interrupt
  digitalWrite(this->_wakeUpPin,LOW);//set the controlling pin to the server interrupt to low to wake it up
  this->_awake = true;//update the awake flag to reflect current status
}
void RoverSleeperClient::reset()
{
	//this will awake any servers the client is connected to
	this->wakeUp();
}

