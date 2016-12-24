//RoverData.h
//use to hold the data in an encapsulated object


/*
		
		Note: RoverComm, RoverData, and RoverCommand classes are used together.
		
		==IMU AHRS Data Format==
		!ANG:Y.XX,Y.XX,Y.XX
			Where Y can be 1 or more digits.
		i.e.
		
		!ANG:0.27,1.56,16.47
		!ANG:0.24,1.57,16.46
		!ANG:0.26,1.56,16.46
		!ANG:0.38,1.61,16.47
		!ANG:0.38,1.63,16.46
		!ANG:0.42,1.63,16.47
		!ANG:0.45,1.61,16.47
		!ANG:0.41,1.61,16.47



		==Rover Data Format==
		The format is /OcDLL*CCCC... (Note: There could be more than four C's so hence CCCC...)
		The /, c, and * are format identifiers. For commands the headers are as such: /-c---*----
		The O shows the origin where the message came from (Origin ID): See definitions below.
		The D shows the destination Arduino it's going to (Destination ID): See definitions below.
		Definitions:
			0=NONE, 1=CMNC (external), 2=NAVI (internal), 3=AUXI (internal), 4=MAIN (internal), 5=COMM (internal)
		The LL shows command priority level it should be in the lookup table
		The C's (four or more) are the letters that designate the command. The length of the letters will be determined by the lookup's priority and destination
		
		
		(where - are don't cares and ... means it can vary in length)
		Any messages for
			CMNC: 
				/-c1--*----.... 
			NAVI:
				/-c2--*----.... 
			AUXI:
				/-c3--*----.... 
			MAIN:
				/-c4--*----.... 				
			COMM:
				/-c5--*----.... 
				
				
	Example:
		/3c101*HelloMAINtoCMNC
		
*/	


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
		
		void setData(String);//save the data string in _dataString
		void clearData();//clear the stored data in _dataString
		String getData();//retrieve the data string
		
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)		
	private:		
		String _dataString;//holds the data string
		byte _roverCommType;
	};

	

	
#endif 