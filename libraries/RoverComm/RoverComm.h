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
		The format is /OcDLL*tttdddd... (Note: The d's can range from none to up to _MAX_ROVER_COMMAND_DATA_LEN_ - 1, i.e. 15-1=14. Minus 1 due to null character. So hence dddd....)
		The /, c, and * are format identifiers. For commands the headers are as such: /-c---*----
		The O shows the origin where the message came from (Origin ID): See definitions below.
		The D shows the destination Arduino it's going to (Destination ID): See definitions below.
		Definitions:
			0=NONE, 1=CMNC (external), 2=NAVI (internal), 3=AUXI (internal), 4=MAIN (internal), 5=COMM (internal)
		The LL shows command priority level it should be in the lookup table
		The ttt are the rover command tag to represent which command it is.
		The d's (none to _MAX_ROVER_COMMAND_DATA_LEN_ - 1, i.e. 15-1 = 14. Minus 1 due to null character.) are the letters that designate the command data, if any.
		
		
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
		/3c101*002HelloMAINtoCMNC
		
*/	


#ifndef _ROVERCOMM_H
#define _ROVERCOMM_H
#define _ROVERCOMM_DEFINITIONS
#define _ROVERDATA
#define _CHAR_BUFFER_ARRAY_SIZES

	
	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>	
	#include <RoverConfig.h>
	#include <RoverData.h>
	#include <CharArray.h>
	#include <DataType.h>
	
	
	//uncomment the debug flag below to print the received data string
	//#define _DEBUG_OUTPUT_RXDATA_
	
	//uncomment the debug flag below to see the stages in the code that is processed
	//#define _DEBUG_RX_STAGES_
	
	//uncomment the debug flag below to see the extracted substrings
	//#define _DEBUG_SHOW_EXTRACTED_SUBSTRINGS_
	
	//uncomment the debug flag below to see other data as required
	//#define _DEBUG_OUTPUT_COMMAND_ORIGIN_
	//#define _DEBUG_OUTPUT_COMMAND_DESTINATION_
	
	
	class RoverComm : public virtual RoverReset {
	public:
		RoverComm(RoverData *);//constructor (RoverData Pointer)
		~RoverComm();//destructor				
		void appendToRxData(char);//append a char to the _rxDataString		
		void setRxData(char *, byte);//(charArray, array size) set the _rxDataString with provided string. Mainly used for debugging.
		char * getRxData();//returns _rxDataString
		void clearRxData();//clear the stored data in _rxDataString		
		int getRxDataLength();//returns the length of the corresponding string		
		boolean parseAndValidateData();//parse and validate the data to see if the data is not empty, is in the correct format, and has a valid RoverComm type. Returns true if the data is valid, else returns false.
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
	private:
		
		//SW Resetted
			char _rxDataString[ROVER_DATA_BUFFER_SIZE];
			byte _rxDataStringCharacterIndex;//tracks how many characters was received for array indexing
		//Not SW Resetted
			RoverData * _rxRoverDataPointer;
			boolean validateThenSetOriginRoverCommType(char *);//(Rover Comm Type in the original form of a char array). Sets the origin Rover Comm Type.
			boolean validateThenSetDestinationRoverCommType(char *);//(Rover Comm Type in the original form of a char array). Sets the destination Rover Comm Type.			
			
	};

#endif 

