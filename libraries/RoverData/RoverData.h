//RoverData.h
//use to hold the data in an encapsulated object
#ifndef _ROVERDATA_H
#define _ROVERDATA_H
#define _ROVERCOMMTYPES 
	
	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>
	#include <String.h>
	#include <RoverConfig.h>
	

	class RoverData : public virtual RoverReset {
	public:
		RoverData();//constructor
		~RoverData();//destructor
		
		byte getCommType();//returns the RoverComm Type
		void setCommType(byte);//set the RoverComm type
		
		void setData(String);//save the data string
		void clearData();//clear the stored data
		String getData();//retrieve the data string
		
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)		
	private:		
		String _dataString;//holds the data string
		byte _roverCommType;
	};

	

	
#endif 