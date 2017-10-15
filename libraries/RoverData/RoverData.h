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


#ifndef _ROVERDATA_H
#define _ROVERDATA_H
#define _ROVERCOMM_DEFINITIONS 
#define _ROVERDATA

	
	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>	
	#include <RoverConfig.h>
	#include <CharArray.h>
	

	class RoverData : public virtual RoverReset {
	public:
		RoverData();//constructor
		~RoverData();//destructor
		
		void setOriginCommType(byte);//set the origin RoverComm type
		byte getOriginCommType();//returns the origin RoverComm Type		
		void clearOriginCommType();//clear the origin RoverComm type
		
		void setDestinationCommType(byte);//set the destination RoverComm type		
		byte getDestinationCommType();//returns the destination RoverComm Type		
		void clearDestinationCommType();//clear the destination RoverComm type
		
		void setCommandData(char *, byte);//(charArray, array size) save the data string in _commandData
		char * getCommandData();//retrieves the _commandData
		byte getCommandDataLength();//retrieve the _commandData length
		void clearCommandData();//clear the stored data in _commandData
		
		void setCommandTag(byte);//set the rover command tag
		byte getCommandTag();//returns the rover command tag	
		void clearCommandTag();//clears the rover command tag (i.e. to 0: CMD_TAG_NO_MSG)		
		
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)		
	private:		
		byte _roverOriginCommType;
		byte _roverDestinationCommType;
		char _commandData[_MAX_ROVER_COMMAND_DATA_LEN_];//holds the rover's command data string
		byte _commandTag;
		
	};	
	
#endif 



/*
//#DELETE ME

OLD CODE
	class RoverData : public virtual RoverReset {
	public:
		RoverData();//constructor
		~RoverData();//destructor
		
		byte getCommType();//returns the destination RoverComm Type
		void setCommType(byte);//set the destination RoverComm type
		
		void setData(char *, byte);//save the data string in _dataString (charArray, array size)		
		void clearData();//clear the stored data in _dataString
		char * getData();//retrieve the _dataString
		byte getDataLength();//retrieve the _dataString length
		
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)		
	private:		
		char _dataString[ROVER_DATA_BUFFER_SIZE];//holds the data string
		byte _roverCommType;
	};

	
*/