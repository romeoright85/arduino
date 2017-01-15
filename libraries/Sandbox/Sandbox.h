//Sandbox.h
#ifndef _SANDBOX_H
#define _SANDBOX_H

#include <Arduino.h>

class Sandbox {
public:
	Sandbox();//constructor
	~Sandbox();//destructor
	void write(char *, byte);
	char * read();
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	char * getLat();
	char * getLatUnit();
	char * getLon();
	char * getLonUnit();
	

	
	
private:
	//Non-SW Resettable
	//SW Resettable
	char _data[15];
	
	
	//Latitude: 3916.10N
	//Longitude : 7636.66W
	char _lat[10];
	char _latUnit[2];
	char _lon[10];
	char _lonUnit[2];
	
	char * _gpsFields[4];
	
};

#endif 