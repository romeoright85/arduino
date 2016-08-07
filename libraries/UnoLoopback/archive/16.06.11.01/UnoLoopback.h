/*
  UnoLoopback.h - Library for setting up serial loopback on the UNO
  Created by Richard Nguyen
  Version (YY.MM.DD.Version): 16.06.11.01
*/


#ifndef UnoLoopback_h
#define UnoLoopback_h

	#include "Arduino.h"

	class UnoLoopback
	{
		public:
			UnoLoopback(int baudRate);//declare the constructor
			void startLoopback();//start serial
			void setBaud(int baudRate);
			int getBaud();
		private:
			int _baudRate;//use _ to denote variable is private per https://www.arduino.cc/en/Hacking/LibraryTutorial
	};//don't forget the semicolon after the class definiton http://stackoverflow.com/questions/5675208/expected-initializer-before-function-name


#endif
