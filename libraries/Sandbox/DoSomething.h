//DoSomething.h
#ifndef _DOSOMETHING_H
#define _DOSOMETHING_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverReset.h>

#include <RoverConfig.h>

class DoSomething : public virtual RoverReset {
public:
	DoSomething();//constructor
	~DoSomething();//destructor
	void helloWorld();
	void goodbyeWorld();
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:
	//Non-SW Resettable
	static byte objectCount;
	byte objectID;
	//SW Resettable
};

#endif 