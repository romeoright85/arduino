//RoverCaptain.h
#ifndef _ROVERCAPTAIN_H
#define _ROVERCAPTAIN_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>



#include <DoSomething.h>


/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/
//define Arduino 3: MAIN in order to use it's config pins
#ifndef _ARD_3_MAIN_H
	#define _ARD_3_MAIN_H
#endif



/********************************************************************/

#include <RoverConfig.h>

class RoverCaptain : public virtual RoverReset {
public:
	RoverCaptain();//constructor
	~RoverCaptain();//destructor
	void run();
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		
private:
	//Non-SW Resettable
	static const byte _numOfObjects = 0;
	//SW Resettable	
	RoverReset * resetArray[_numOfObjects] = {		
	};

	
	enum class State {
	};

	State _state;
	
	
};

#endif 