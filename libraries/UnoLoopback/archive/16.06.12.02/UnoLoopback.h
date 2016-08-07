/*
  UnoLoopback.h - Library for setting up serial loopback on the UNO
  Created by Richard Nguyen
  Version (YY.MM.DD.Version): 16.06.12.02
*/


#ifndef UnoLoopback_h
#define UnoLoopback_h


	#include "Arduino.h"

	class UnoLoopback
	{
		public:
			UnoLoopback(int baudRate);//declare the constructor
			void startComms();//start serial
			void startLoopback();//start loopback
			void setBaud(int baudRate);
			int getBaud();			
		private:
			int _baudRate;//use _ to denote variable is private per https://www.arduino.cc/en/Hacking/LibraryTutorial
			String _content;
			int _index = 0;
	};//don't forget the semicolon after the class definiton http://stackoverflow.com/questions/5675208/expected-initializer-before-function-name


#endif
