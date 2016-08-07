/*
  UnoLoopback.cpp - Library for setting up serial loopback on the UNO
  Created by Richard Nguyen
  Version (YY.MM.DD.Version): 16.06.11.01
*/

#include "Arduino.h"
#include "UnoLoopback.h"

//Class Constructor
UnoLoopback::UnoLoopback( int baudRate)
{
	_baudRate = baudRate;
		
}

void UnoLoopback::startLoopback()
{
	Serial.end();//end any current communication
	Serial.begin(_baudRate);
}//end of startLoopback()

void UnoLoopback::setBaud(int baudRate)
{
	_baudRate = baudRate;
}//end of setBaud()

int UnoLoopback::getBaud()//don't put a semicolon here
{
	return _baudRate;
}//end of getBaud()