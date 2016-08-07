/*
  UnoLoopback.cpp - Library for setting up serial loopback on the UNO
  Created by Richard Nguyen
  Version (YY.MM.DD.Version): 16.06.11.02
*/

#include "Arduino.h"
#include "UnoLoopback.h"


//Class Constructor
UnoLoopback::UnoLoopback( int baudRate)
{
	_baudRate = baudRate;
		
}

void UnoLoopback::startComms()
{
	
	
	Serial.end();//end any current communication
	Serial.begin( _baudRate);
	
	
	
}//end of startComms()
void UnoLoopback::startLoopback()
{
	delay(100);//add delay so the buffer can be filled up a bit
	if(Serial.available() > 0)
	{
		while(Serial.available() > 0)
		{
			
			this->_content.concat((char)Serial.read());

		}
		delay(1);
		Serial.print(_content);//no need to println. let the terminal send a linefeed
		_content = "";//clear buffer
	}
	

	
	
}//end of startLoopback()
void UnoLoopback::setBaud(int baudRate)
{
	_baudRate = baudRate;
}//end of setBaud()

int UnoLoopback::getBaud()//don't put a semicolon here
{
	return _baudRate;
}//end of getBaud()