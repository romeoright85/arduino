//RoverComm.h


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


#ifndef _ROVERCOMM_H
#define _ROVERCOMM_H
#define _ROVERCOMMTYPES
	
	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>
	#include <String.h>
	#include <RoverConfig.h>
	#include <RoverData.h>
	
	
	//uncomment the debug flag below to print the received data string
	#define _DEBUG_OUTPUT_RXDATA_
	
	//uncomment the debug flag below to see other data as required
	#define _DEBUG_OUTPUT_CMDTYPE_
	

	class RoverComm : public virtual RoverReset {
	public:
		RoverComm(RoverData *);//constructor (RoverData Pointer)
		~RoverComm();//destructor
		void appendToRxData(char);//append a char to the _rxDataString
		void setRxData(String);//(set this data to _rxDataString) set the _rxDataString with provided string. Mainly used for debugging
		byte getDestinationCommType();//returns the RoverData's destination RoverComm Type
		boolean isDataValid();//returns the validity state of the data
		void validateData();//validate the data to see if the data is not empty, is in the correct format, and has a valid RoverComm type
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	private:
		
		//SW Resetted
			String _rxDataString = "";
			byte _destinationCommType = ROVERCOMM_NONE;//holds the RoverComm Type where the data is meant to go to
			boolean _dataIsValid;//returns true if the data is not empty, is in the correct format, and has a valid RoverComm type	
		//Not SW Resetted
			RoverData * _rxRoverDataPointer;
	};

#endif 