//RoverComm.h
#ifndef _ROVERCOMM_H
#define _ROVERCOMM_H
	
	#include <Arduino.h>
	#include <RoverReset.h>
	#include <String.h>
	#include <RoverConfig.h>//this defines a lot of the values used (i.e. RoverComm Types and RoverComm Data Directions)
	#include <RoverData.h>

	class RoverComm : public virtual RoverReset {
	public:
		RoverComm(byte, RoverData *);//constructor (RoverComm Type, this unit's RoverData Pointer)
		~RoverComm();//destructor
		void appendToRxData(char, byte);//append a char to the rxDataString for the corresponding overComm Types
		String getTxData(byte);//returns the Tx data of the corresponding RoverComm type (roverComm Types). Can also be used to get the data destined for this unit (i.e. no reroute)
		String getRxData(byte);//returns the Tx data of the corresponding RoverComm type (roverComm Types)
		void processReceivedData();
		byte getThisUnitsCommType();//returns this unit's RoverComm Type
		
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	private:
		//Note: By creating a string for every communications type, it takes up more memory but allows the RoverComm class to be more adaptable across different Arduinos
		//SW Resetted
			//received data strings
			String _rxDataString_CMNC = "";
			String _rxDataString_NAVI = "";
			String _rxDataString_AUXI = "";
			String _rxDataString_MAIN = "";
			String _rxDataString_COMM = "";
			//transmit data strings
			String _txDataString_CMNC = "";
			String _txDataString_NAVI = "";
			String _txDataString_AUXI = "";
			String _txDataString_MAIN = "";
			String _txDataString_COMM = "";	
			RoverData * _thisUnit_RoverDataPointer;//this unit's RoverData pointer. Used to point to the rover data that was meant for this unit.
		//Not SW Resetted
			byte _thisUnit_CommType;//this unit's RoverComm Type
		
		//Private Functions
		String dataSelector(byte, byte);//sets up string for the corresponding overComm Types (overComm Types, RoverComm Data Direction)
		boolean dataFormatValidator(String);//returns true if the data format is correct, else it returns false
		
		
		
	};

#endif 