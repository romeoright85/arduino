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
#define _COMMAND_CREATION_DEFINITIONS	
	
	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>	
	#include <RoverConfig.h>
	#include <CharArray.h>	
	#include<RoverCommandDefs.h>
	

	class RoverData : public virtual RoverReset {
	public:
		RoverData();//constructor
		~RoverData();//destructor
		
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		
		void setOriginCommType(byte);//(origin Rover Comm Type)set the origin RoverComm type
		byte getOriginCommType();//returns the origin RoverComm Type		
		void clearOriginCommType();//clears the origin RoverComm type
		
		void setDestinationCommType(byte);//(destination Rover Comm Type)set the destination RoverComm type		
		byte getDestinationCommType();//returns the destination RoverComm Type		
		void clearDestinationCommType();//clears the destination RoverComm type
		
		void setCommandData(char *, byte);//(command data char array, array size) save the data string in _commandData
		char * getCommandData();//retrieves the _commandData
		byte getCommandDataLength();//returns the _commandData length
		void clearCommandData();//clears the stored data in _commandData
		
		void setCommandTag(byte);//(rover command tag) set the rover command tag
		byte getCommandTag();//returns the rover command tag	
		void clearCommandTag();//clears the rover command tag (i.e. to 0: CMD_TAG_NO_MSG)		
		
		void setIMUData(char *, byte);//(IMU data char array, array size) save the _imuDataString
		void clearIMUData();//clear the stored data in _imuDataString
		char * getIMUData();//retrieve the _imuDataString
		byte getIMUDataLength();//retrieve the _imuDataString length
		
		
	private:		
		byte _roverOriginCommType;
		byte _roverDestinationCommType;
		char _commandData[_MAX_ROVER_COMMAND_DATA_LEN_];//holds the rover's command data string
		byte _commandTag;
		char _imuDataString[ROVER_IMU_DATA_BUFFER_SIZE];//holds the IMU data string		
	};	
	
#endif