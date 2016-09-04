//RoverData.h
#ifndef _ROVERDATA_H
#define _ROVERDATA_H
	
	#include <Arduino.h>
	#include <RoverReset.h>
	#include <String.h>
	#include <RoverConfig.h>//this defines a lot of the values used (i.e. RoverComm Types and RoverComm Data Directions)
	

	class RoverData : public virtual RoverReset {
	public:
		RoverData();//constructor
		~RoverData();//destructor
		void setData(String);//sets the string of the RoverData object
		boolean validData();//returns true if the string isn't empty and has the correct format
		byte getCommType();//returns the RoverComm Type after extracting it from the data string
		
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)		
	private:		
		String _dataString;//holds the data string
	};

#endif 