//RoverComm.h
#ifndef _ROVERCOMM_H
#define _ROVERCOMM_H
#define _ROVERCOMMTYPES
	
	#include <Arduino.h>
	#include <RoverReset.h>
	#include <String.h>
	#include <RoverConfig.h>
	#include <RoverData.h>

	class RoverComm : public virtual RoverReset {
	public:
		RoverComm(RoverData *);//constructor (RoverData Pointer)
		~RoverComm();//destructor
		void appendToRxData(char);//append a char to the rxDataString
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