	//RoverReset.h
#ifndef _ROVERRESET_H
#define _ROVERRESET_H

	#include <Arduino.h>

	class RoverReset {
		public:
			// virtual destructor is required if the object may
			// be deleted through a pointer to RoverReset
			virtual ~RoverReset();//destructor
			virtual void reset() = 0;//pure virtual function
		private:
			//nothing
	};



#endif 

//Reference
//http://stackoverflow.com/questions/11945993/equivalent-of-java-interfaces-in-c


/*

CLASS .H:
#include <RoverReset.h>

class ClassName : public virtual RoverReset {
public:
	
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
};



CLASS .CPP:

void ClassName::reset()
{
		//software reset
		<code here>
}



TEST CODE
	//Holds all custom objects created by this sketch
	RoverReset * resetArray[] = { &object1, &object2, <etc.> };


	void setup() {
		//resetting all objects
		for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
		{
			resetArray[i]->reset();
		}

		<etc.>
	}



	
*/