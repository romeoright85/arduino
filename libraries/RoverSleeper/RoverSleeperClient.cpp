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
}
boolean RoverSleeperClient::isAwake()
{
	return this->_awake;
}
void RoverSleeperClient::wakeUp()
{
  //Toggle the wakeup pin to create a rising edge for the interrupt
  digitalWrite(this->_wakeUpPin,HIGH);//make sure it starts high
  delay(100);
  digitalWrite(this->_wakeUpPin,LOW);//make a low level
  delay(100);
  digitalWrite(this->_wakeUpPin,HIGH);//reset back to high
  this->_awake = true;//update the awake flag to reflect current status
}
void RoverSleeperClient::reset()
{
	//this will awake any servers the client is connected to
	this->wakeUp();
}

