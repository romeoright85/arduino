#include <RoverSleeperClient.h>


//The server is used to control the sleep and wakeup of itself
//The client is used to remotely control the sleep and wakeup on a server

RoverSleeperClient::RoverSleeperClient(byte wakeUpPin)
{
	this->wakeUpPin = wakeUpPin;
	this->awake = true;//initialize variable
}
RoverSleeperClient::~RoverSleeperClient()
{
	//do nothing
}
void RoverSleeperClient::goToSleep()
{
	this->awake = false;//update the awake flag to reflect current status
}
boolean RoverSleeperClient::isAwake()
{
	return this->awake;
}
void RoverSleeperClient::wakeUp()
{
  //Toggle the wakeup pin to create a rising edge for the interrupt
  digitalWrite(this->wakeUpPin,HIGH);//make sure it starts high
  delay(100);
  digitalWrite(this->wakeUpPin,LOW);//make a low level
  delay(100);
  digitalWrite(this->wakeUpPin,HIGH);//reset back to high
  this->awake = true;//update the awake flag to reflect current status
}