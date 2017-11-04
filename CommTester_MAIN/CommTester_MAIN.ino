	
	
//Used for MAIN - 4

//Note: The test cases varies for different Arduinos

//To test code, in RoverConfig uncomment _DEBUG_ALL_SERIALS_WITH_USB_SERIAL_

//Note: Can send this (about max size of the Rover Command Data) to test: "/6c4--*002abcdefghijklm^"


//Test cases for debugging

//Test case 1:
//#define _DEBUG_IMU_TEST_CASE_
/*
Uncomment the line above to test the IMU AHRS formatted data
Debug data: !ANG:1.23,4.56,78.90
Also uncomment the _DEBUG_OUTPUT_RXDATA_ in RoverComm.h to see the received string
*/


//Test case 2:
//#define _DEBUG_ROVER_TEST_CASE_
/*
Uncomment the line above to test the Rover formatted data
Debug data: /6c401*HelloPCUSBtoMAIN
Also uncomment flag(s) in RoverComm.h to see the received string, etc.
Note: You will get an "/3c400*004invlcmd" but that is expected and fine since "/6c401*HelloPCUSBtoMAIN" isn't a registered command. But this test the routing of the data is correct.
*/


//Test case 3a:
/*
Send (i.e. with your keyboard and using a terminal window) over USB serial
/6c4--*002hi
to test the command interface for this Arduino
*/

//Test case 3b:
/*
Send (i.e. with your keyboard and using a terminal window) over USB serial
/6c4--*003bye
to test the command interface for this Arduino

*/




//Test case 4a:
/*
Send (i.e. with your keyboard and using a terminal window) over USB serial
/6c501*FromPCUSBtoCOMM
to test the redirection interface for this Arduino
You can turn on this flag (_DEBUG_REDIRECTION_NOTICE) below to verify it's redirecting.
//Note: Since when the _DEBUG_ALL_SERIALS_WITH_USB_SERIAL_ is turned on, all channels are being simulated with PC_USB, there may be some blank data sent or a slight delay (or you might have to send it more than once), but that's okay. As long as it works.
*/




//Test case 4b:
/*
Send (i.e. with your keyboard and using a terminal window) over USB serial
/2c601*FromNAVItoPCUSB
to test the redirection interface for this Arduino
You can turn on this flag (_DEBUG_REDIRECTION_NOTICE) below to verify it's redirecting.
//Note: Since when the _DEBUG_ALL_SERIALS_WITH_USB_SERIAL_ is turned on, all channels are being simulated with PC_USB, there may be some blank data sent or a slight delay (or you might have to send it more than once), but that's okay. As long as it works.



//Test case 4c:
/*
Send (i.e. with your keyboard and using a terminal window) over USB serial
/5c501*FromCOMMtoCOMM
to test the redirection interface for this Arduino
You can turn on this flag (_DEBUG_REDIRECTION_NOTICE) below to verify it's redirecting.
//Note: Since when the _DEBUG_ALL_SERIALS_WITH_USB_SERIAL_ is turned on, all channels are being simulated with PC_USB, there may be some blank data sent or a slight delay (or you might have to send it more than once), but that's okay. As long as it works.
*/



//Configuration defines for #includes (must come before the #includes)
//Must define this before calling RoverConfig.h (either directly or through another header file)
#ifndef _COMMAND_CREATION_DEFINITIONS
#define _COMMAND_CREATION_DEFINITIONS //for RoverCommandDefs.h
#endif
#define _ARD_2_MAIN_H //define this flag to turn on MAIN definitions
#ifndef _MAIN_BIT_FLAGS_
#define _MAIN_BIT_FLAGS_ //For RoverBitFlags.h
#endif


//#includes
#include <RoverCommandDefs.h>
#include <RoverCommandCreator.h>
#include <RoverData.h>
#include <RoverComm.h> //calls RoverConfig.h
#include <RoverConfig.h>	
#include <avr/pgmspace.h> //To store certain variables in Flash
#include <BooleanBitFlags.h>	
#include <RoverBitFlags.h>	



//============Debugging: Serial Channel Selection
//Used to output debugging messages only when the _DEBUG_COMM_BROADCAST flag is defined
//Uncomment the flag below in order to output debugging messages
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast

//If it is decided CommBroadcast_MAIN isn't being loaded on MAIN, then instead of going to COMM, direct any MAIN, AUXI, or NAVI data out to the PC USB of MAIN
#ifdef _DEBUG_COMM_BROADCAST
	#define _SERIAL_DEBUG_CHANNEL_ _COMM_SERIAL_
#else
	#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_
#endif

//============End of Debugging: Serial Channel Selection

//============Debugging: Redirection
//Uncomment below to output a notice when a message is being redirected
//#define _DEBUG_REDIRECTION_NOTICE
//============End Debugging: Redirection

						  
//============Global Declarations




//Message Queues
byte pc_usb_msg_queue = CMD_TAG_NO_MSG;
byte comm_msg_queue = CMD_TAG_NO_MSG;
byte navi_msg_queue = CMD_TAG_NO_MSG;
byte auxi_msg_queue = CMD_TAG_NO_MSG;



//Message Char Array
char txMsgBuffer_PC_USB[UNIV_BUFFER_SIZE];//transmit buffer for PC_USB
char txMsgBuffer_COMM[UNIV_BUFFER_SIZE];//transmit buffer for COMM (CMNC)
char txMsgBuffer_NAVI[UNIV_BUFFER_SIZE];//transmit buffer for NAVI
char txMsgBuffer_AUXI[UNIV_BUFFER_SIZE];//transmit buffer for AUXI
char programMem2RAMBuffer[_MAX_PROGMEM_BUFF_STR_LEN_];//Buffer to use for Message Strings




													  //Fixed Message Strings (to store in flash)
const static char msg_strg_0[] PROGMEM = "nodata";//getMsgString(0)
const static char msg_strg_1[] PROGMEM = "invlcmd";//getMsgString(1)
												   //Note: Make sure to update  the msg_str_table[] array

												   //Table of Fixed Commaned Strings (array of strings stored in flash)
const char* const msg_str_table[] PROGMEM = {
	msg_strg_0,
	msg_strg_1
};



//Flag(s) - Rover Data Channels Status
byte ch1Status = DATA_STATUS_NOT_READY;//for PC_USB
byte ch2Status = DATA_STATUS_NOT_READY;//for COMM
byte ch3Status = DATA_STATUS_NOT_READY;//for NAVI
byte ch4Status = DATA_STATUS_NOT_READY;//for AUXI


//Rover Data and COMMs
//Ch1 is between MAIN and PC USB
RoverData * roverDataCh1_COMM = new RoverData();
RoverComm * roverComm_Ch1 = new RoverComm(roverDataCh1_COMM);
//Ch3 is between MAIN and COMM
RoverData * roverDataCh2_COMM = new RoverData();
RoverComm * roverComm_Ch2 = new RoverComm(roverDataCh2_COMM);
//Ch3 is between MAIN and NAVI
RoverData * roverDataCh3_COMM = new RoverData();
RoverComm * roverComm_Ch3 = new RoverComm(roverDataCh3_COMM);
//Ch4 is between MAIN and AUXI
RoverData * roverDataCh4_COMM = new RoverData();
RoverComm * roverComm_Ch4 = new RoverComm(roverDataCh4_COMM);





//Command Parsers
//Rover Data Pointers for use with either internal processing or outgoing messages
RoverData * roverDataForMAIN;//pointer used access the RoverData which has the command data incoming to MAIN
RoverData * roverDataForPC_USB;//pointer used access the RoverData which has the command data outgoing to PC_USB
RoverData * roverDataForCOMM;//pointer used access the RoverData which has the command data outgoing to COMM
RoverData * roverDataForNAVI;//pointer used access the RoverData which has the command data outgoing to NAVI
RoverData * roverDataForAUXI;//pointer used access the RoverData which has the command data outgoing to AUXI



							 //Flag(s) - Message Controls
byte flagSet_MessageControl = _BTFG_NONE_;

//Note: Make sure to add any new objects created to this array
RoverReset * resetArray[] = {
	roverDataCh1_COMM,
	roverComm_Ch1,
	roverDataCh2_COMM,
	roverComm_Ch2,
	roverDataCh3_COMM,
	roverComm_Ch3,
	roverDataCh4_COMM,
	roverComm_Ch4
};//for pointers, pass them directly, for objects pass the address



//=====End of: Non-SW Resettable Variables


//=====End of: SW Resettable Variables

//============End of Global Declarations



void setup() {


	//resetting all objects in this sketch
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		if (!resetArray[i] == NULL)//if the object isn't null
		{
			resetArray[i]->reset();//reset the object	
		}
	}


	//Serial Communications
	//Setup the HW_UARTs
	_PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
	_COMM_SERIAL_.begin(COMM_BAUD_RATE);
	_NAVI_SERIAL_.begin(NAVI_BAUD_RATE);
	_AUXI_SERIAL_.begin(AUXI_BAUD_RATE);

	
	

}//end of setup()






void loop() {



	//1. Receives data

	//1a. receive and process data from PC_USB
	//rxData() from PC_USB
	//Reset status flag
	ch1Status = DATA_STATUS_NOT_READY;
	//Clear all Rx'ed data before getting new data				
	roverComm_Ch1->clearRxData();
	//Receive data
	ch1Status = rxData(roverComm_Ch1, ROVERCOMM_PC_USB);
	//Parse and validate data	
	if (ch1Status == DATA_STATUS_READY)
	{
		//If the data is valid, set the status as such
		if (roverComm_Ch1->parseAndValidateData())
		{
			ch1Status = DATA_STATUS_VALID;//if data is valid once it's validated, set the flag
		}//end if
		 //Else the data is invalid, so set the status as such
		else
		{
			ch1Status = DATA_STATUS_INVALID;
		}//end else
	}//end if
	 //Else, since the data isn't ready, leave the status as DATA_STATUS_NOT_READY



	 //1b. receive and process data from COMM
	 //rxData() from COMM
	 //Reset status flag
	ch2Status = DATA_STATUS_NOT_READY;
	//Clear all Rx'ed data before getting new data				
	roverComm_Ch2->clearRxData();
	//Receive data
	ch2Status = rxData(roverComm_Ch2, ROVERCOMM_COMM);
	//Parse and validate data
	if (ch2Status == DATA_STATUS_READY)
	{
		//If the data is valid, set the status as such
		if (roverComm_Ch2->parseAndValidateData())
		{
			ch2Status = DATA_STATUS_VALID;//if data is valid once it's validated, set the flag
		}//end if
		 //Else the data is invalid, so set the status as such
		else
		{
			ch2Status = DATA_STATUS_INVALID;
		}//end else
	}//end if
	 //Else, since the data isn't ready, leave the status as DATA_STATUS_NOT_READY


 //1c. receive and process data from NAVI
	 //rxData() from NAVI
	 //Reset status flag
	ch3Status = DATA_STATUS_NOT_READY;
	//Clear all Rx'ed data before getting new data				
	roverComm_Ch3->clearRxData();
	//Receive data
	ch3Status = rxData(roverComm_Ch3, ROVERCOMM_NAVI);
	//Parse and validate data
	if (ch3Status == DATA_STATUS_READY)
	{
		//If the data is valid, set the status as such
		if (roverComm_Ch3->parseAndValidateData())
		{
			ch3Status = DATA_STATUS_VALID;//if data is valid once it's validated, set the flag
		}//end if
		 //Else the data is invalid, so set the status as such
		else
		{
			ch3Status = DATA_STATUS_INVALID;
		}//end else
	}//end if
	 //Else, since the data isn't ready, leave the status as DATA_STATUS_NOT_READY	 
	 
	 
	 
	 //1d. receive and process data from AUXI
	 //rxData() from AUXI
	 //Reset status flag
	ch4Status = DATA_STATUS_NOT_READY;
	//Clear all Rx'ed data before getting new data				
	roverComm_Ch4->clearRxData();
	//Receive data
	ch4Status = rxData(roverComm_Ch4, ROVERCOMM_AUXI);
	//Parse and validate data
	if (ch4Status == DATA_STATUS_READY)
	{
		//If the data is valid, set the status as such
		if (roverComm_Ch4->parseAndValidateData())
		{
			ch4Status = DATA_STATUS_VALID;//if data is valid once it's validated, set the flag
		}//end if
		 //Else the data is invalid, so set the status as such
		else
		{
			ch4Status = DATA_STATUS_INVALID;
		}//end else
	}//end if
	 //Else, since the data isn't ready, leave the status as DATA_STATUS_NOT_READY 
	 
	 
	 
	 
	 

	 //Note: The debug code below varies for different Arduinos
	 //DEBUG Code: Data Injection (from AUXI to MAIN)	
#ifdef _DEBUG_IMU_TEST_CASE_
	roverComm_Ch1->setRxData("!ANG:1.23,4.56,78.90", sizeof("!ANG:1.23,4.56,78.90"));
	//If the data is valid as well as parses it, set the status as such
	if (roverComm_Ch1->parseAndValidateData())
	{
		ch1Status = DATA_STATUS_VALID;//if data is valid once it's validated, set the flag
	}//end if
	 //Else the data is invalid, so set the status as such
	else
	{
		ch1Status = DATA_STATUS_INVALID;
	}//end else
#endif
#ifdef _DEBUG_ROVER_TEST_CASE_		
	roverComm_Ch1->setRxData("/6c401*HelloPCUSBtoMAIN", sizeof("/6c401*HelloPCUSBtoMAIN"));
	//If the data is valid as well as parses it, set the status as such
	if (roverComm_Ch1->parseAndValidateData())
	{
		ch1Status = DATA_STATUS_VALID;//if data is valid once it's validated, set the flag
	}//end if
	 //Else the data is invalid, so set the status as such
	else
	{
		ch1Status = DATA_STATUS_INVALID;
	}//end else
#endif

	//Clear redirect flags before processing the data with dataDirector (a bit redundant since it will be cleared later, but better safe than sorry)
	BooleanBitFlags::clearFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_PC_USB_);
	BooleanBitFlags::clearFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_COMM_);	
	BooleanBitFlags::clearFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_NAVI_);
	BooleanBitFlags::clearFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_AUXI_);

	 //2. Processes data


	//2a. Processes data from PC_USB
	if (ch1Status == DATA_STATUS_VALID)
	{

		//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
		dataDirector(roverDataCh1_COMM, DATA_REDIRECT_ENABLED, flagSet_MessageControl, _BTFG_DATA_WAS_FOR_MAIN_CH1_);
		//Note: this is a local .ino function
		if (BooleanBitFlags::flagIsSet(flagSet_MessageControl, _BTFG_DATA_WAS_FOR_MAIN_CH1_))//If there was data from the PC_USB (Ch1), and it was for MAIN
		{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
			commandDirector(roverDataCh1_COMM);
		}//end if	
	}//end if
	//else the data was invalid or not ready, so do nothing



	 //2b. Processes data from COMM
	if (ch2Status == DATA_STATUS_VALID)
	{

		//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
		dataDirector(roverDataCh2_COMM, DATA_REDIRECT_ENABLED, flagSet_MessageControl, _BTFG_DATA_WAS_FOR_MAIN_CH2_);
		//Note: this is a local .ino function
		if (BooleanBitFlags::flagIsSet(flagSet_MessageControl, _BTFG_DATA_WAS_FOR_MAIN_CH2_))//If there was data from the COMM (Ch2), and it was for MAIN
		{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
			commandDirector(roverDataCh2_COMM);
		}//end if	
	}//end if
	//else the data was invalid or not ready, so do nothing


	//2c. Processes data from NAVI
	if (ch3Status == DATA_STATUS_VALID)
	{

		//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
		dataDirector(roverDataCh3_COMM, DATA_REDIRECT_ENABLED, flagSet_MessageControl, _BTFG_DATA_WAS_FOR_MAIN_CH3_);
		//Note: this is a local .ino function
		if (BooleanBitFlags::flagIsSet(flagSet_MessageControl, _BTFG_DATA_WAS_FOR_MAIN_CH3_))//If there was data from the NAVI (Ch3), and it was for MAIN
		{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
			commandDirector(roverDataCh3_COMM);
		}//end if	
	}//end if
	 //else the data was invalid or not ready, so do nothing


	 
	//2d. Processes data from AUXI
	if (ch4Status == DATA_STATUS_VALID)
	{

		//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
		dataDirector(roverDataCh4_COMM, DATA_REDIRECT_ENABLED, flagSet_MessageControl, _BTFG_DATA_WAS_FOR_MAIN_CH4_);
		//Note: this is a local .ino function
		if (BooleanBitFlags::flagIsSet(flagSet_MessageControl, _BTFG_DATA_WAS_FOR_MAIN_CH4_))//If there was data from the AUXI (Ch4), and it was for MAIN
		{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
			commandDirector(roverDataCh4_COMM);
		}//end if	
	}//end if
	//else the data was invalid or not ready, so do nothing	 

	 //3. Creates and sends data, reroutes data, and/or executes the command

	//Creates data for PC_USB and sends it to PC_USB
	if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
	{
		createDataFromQueueFor(ROVERCOMM_PC_USB);
		txData(txMsgBuffer_PC_USB, ROVERCOMM_PC_USB);
	}//end if


	//Creates data for COMM and sends it to COMM
	if (comm_msg_queue != CMD_TAG_NO_MSG)
	{
		createDataFromQueueFor(ROVERCOMM_COMM);
		txData(txMsgBuffer_COMM, ROVERCOMM_COMM);
	}//end if


	//Creates data for NAVI and sends it to NAVI
	if (navi_msg_queue != CMD_TAG_NO_MSG)
	{
		createDataFromQueueFor(ROVERCOMM_NAVI);
		txData(txMsgBuffer_NAVI, ROVERCOMM_NAVI);
	}//end if



	//Creates data for AUXI and sends it to AUXI
	if (auxi_msg_queue != CMD_TAG_NO_MSG)
	{
		createDataFromQueueFor(ROVERCOMM_AUXI);
		txData(txMsgBuffer_AUXI, ROVERCOMM_AUXI);
	}//end if
	
	
		

	 //Redirects data
	redirectData(roverComm_Ch1);//to PC_USB
	redirectData(roverComm_Ch2);//to COMM
	redirectData(roverComm_Ch3);//to NAVI
	redirectData(roverComm_Ch4);//to AUXI



	//4. Clears variables for future use

	//clears message queue(s) and redirect flags			
	pc_usb_msg_queue = CMD_TAG_NO_MSG;
	comm_msg_queue = CMD_TAG_NO_MSG;
	navi_msg_queue = CMD_TAG_NO_MSG;
	auxi_msg_queue = CMD_TAG_NO_MSG;


	BooleanBitFlags::clearFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_PC_USB_);
	BooleanBitFlags::clearFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_COMM_);	
	BooleanBitFlags::clearFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_NAVI_);
	BooleanBitFlags::clearFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_AUXI_);





}//end of loop()






byte rxData(RoverComm * roverComm, byte roverCommType) {


	byte counter;
	byte dataStatus = DATA_STATUS_NOT_READY;

	//Note: Make sure parseAndValidateData() is called between (before, after, or in) successive rxData() function calls, as it will clear the string and reset the index (required for the code to work properly)
	if (roverCommType == ROVERCOMM_PC_USB)
	{

		if (_PC_USB_SERIAL_.available() > 1)
		{

			//initialize the counter
			counter = 0;

			while (_PC_USB_SERIAL_.available() > 0 && counter <= ROVER_COMM_SENTENCE_LENGTH)//while there is data on the Serial RX Buffer and the length is not over the max GPS sentence length
			{
				//Read one character of serial data at a time
				//Note: Must type cast the _PC_USB_SERIAL_.Read to a char since not saving it to a char type first
				roverComm->appendToRxData((char)_PC_USB_SERIAL_.read());//construct the string one char at a time
				counter++;
				delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
			}//end while

			dataStatus = DATA_STATUS_READY;
		}//end if
		else
		{
			dataStatus = DATA_STATUS_NOT_READY;
		}//end else
	}//end if
	else if (roverCommType == ROVERCOMM_COMM)
	{


		if (_COMM_SERIAL_.available() > 1)
		{


			//initialize the counter
			counter = 0;

			while (_COMM_SERIAL_.available() > 0 && counter <= ROVER_COMM_SENTENCE_LENGTH)//while there is data on the Serial RX Buffer and the length is not over the max GPS sentence length
			{
				//Read one character of serial data at a time
				//Note: Must type cast the Serial.Read to a char since not saving it to a char type first
				roverComm->appendToRxData((char)_COMM_SERIAL_.read());//construct the string one char at a time
				counter++;
				delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
			}//end while
			dataStatus = DATA_STATUS_READY;
		}//end if
		else
		{
			dataStatus = false;
		}//end DATA_STATUS_NOT_READY
	}//end else if
	else if (roverCommType == ROVERCOMM_NAVI)
	{


		if (_NAVI_SERIAL_.available() > 1)
		{


			//initialize the counter
			counter = 0;

			while (_NAVI_SERIAL_.available() > 0 && counter <= ROVER_COMM_SENTENCE_LENGTH)//while there is data on the Serial RX Buffer and the length is not over the max GPS sentence length
			{
				//Read one character of serial data at a time
				//Note: Must type cast the Serial.Read to a char since not saving it to a char type first
				roverComm->appendToRxData((char)_NAVI_SERIAL_.read());//construct the string one char at a time
				counter++;
				delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
			}//end while
			dataStatus = DATA_STATUS_READY;
		}//end if
		else
		{
			dataStatus = false;
		}//end DATA_STATUS_NOT_READY
	}//end else if
	else if (roverCommType == ROVERCOMM_AUXI)
	{


		if (_AUXI_SERIAL_.available() > 1)
		{


			//initialize the counter
			counter = 0;

			while (_AUXI_SERIAL_.available() > 0 && counter <= ROVER_COMM_SENTENCE_LENGTH)//while there is data on the Serial RX Buffer and the length is not over the max GPS sentence length
			{
				//Read one character of serial data at a time
				//Note: Must type cast the Serial.Read to a char since not saving it to a char type first
				roverComm->appendToRxData((char)_AUXI_SERIAL_.read());//construct the string one char at a time
				counter++;
				delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
			}//end while
			dataStatus = DATA_STATUS_READY;
		}//end if
		else
		{
			dataStatus = false;
		}//end DATA_STATUS_NOT_READY
	}//end else if
	else
	{
		//invalid RoverComm Type, so do nothing
		dataStatus = DATA_STATUS_NOT_READY;
	}//end else


	return dataStatus;

}//end of rxData()



void dataDirector(RoverData * roverData, byte redirectOption, byte &flagSet, byte flagOfInterest)
{
	//Note: This function varies for different Arduinos


	BooleanBitFlags::clearFlagBit(flagSet, flagOfInterest);//initialize flag to false

	byte roverCommType = roverData->getDestinationCommType();//get the roverComm Destination

	if (roverCommType == ROVERCOMM_MAIN)
	{
		//if the data is for this unit, MAIN
		BooleanBitFlags::setFlagBit(flagSet, flagOfInterest);//set the status such that the data was for this unit, MAIN
		//process it back in the main loop (to prevent software stack from being too deep)
	}//end if
	 //else check to see if the data was for other cases
	else if (redirectOption == DATA_REDIRECT_ENABLED)
	{
		if (roverCommType == ROVERCOMM_PC_USB)
		{
			//if the data is for PC_USB, transmit the data out from MAIN to PC_USB
			//Set redirect to PC_USB flag to true			
			BooleanBitFlags::setFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_PC_USB_);
		}//end else if		
		else if (roverCommType == ROVERCOMM_COMM || roverCommType == ROVERCOMM_CMNC)
		{
			//if the data is for either COMM or CMNC, transmit the data out from MAIN to COMM since MAIN only can talk to COMM and not CMNC (and COMM will process it accordingly or reroute it if needed)
			//Set redirect to COMM flag to true			
			BooleanBitFlags::setFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_COMM_);
		}//end else if
		else if (roverCommType == ROVERCOMM_NAVI)
		{
			//if the data is for NAVI, transmit the data out to NAVI
			//Set redirect to NAVI flag to true			
			BooleanBitFlags::setFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_NAVI_);
		}//end else if		
		else if (roverCommType == ROVERCOMM_AUXI)
		{
			//if the data is for AUXI, transmit the data out to AUXI
			//Set redirect to AUXI flag to true			
			BooleanBitFlags::setFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_AUXI_);
		}//end else if		
		
		 //else the command type is ROVERCOMM_
	}//end if
	 //else the data was not for this local unit, and redirect was disabled, so do nothing

	return;
}//end of dataDirector()




void commandDirector(RoverData * roverDataPointer)
{

	//Note: This function varies for different Arduinos
	//Categorize all commands/data from all sources.					
	//Sort based on priority.
	//Allow for all non-conflicting commands to run.
	//Then only run the highest priority functions for MAIN last, so it will overwrite anything else, right before state transition.




	byte originRoverCommType;//holds the received data's origin
	byte destinationRoverCommType;//holds the received data's destination
	byte commandTag;//holds received data's commandtag


	//Get the received data's origin and destination
	originRoverCommType = roverDataPointer->getOriginCommType();
	destinationRoverCommType = roverDataPointer->getDestinationCommType();

	//Get the command tag from the Rover Data Object
	commandTag = roverDataPointer->getCommandTag();


	//Setting the roverDataPointer in order to route where the rover command data will be routed to
	//Clears/resets all data pointers before setting them.
	clearRoverDataPointers();
	//Sets the default such that the rover command data goes to the destination of the command. If needed, this can be overwritten by the command tag if/else statements
	setRoverDataPointer(roverDataPointer, destinationRoverCommType);
	//Note: The roverDataPointer should be going to MAIN (else it would have been redirected already with dataDirector).
	//However, it can be overwritten in the if/else conditions below based on the command tag for special cases like when it redirects itself to the original sender (i.e. when the command is a request for data/status)


	//Run highest priority functions here. //this will override any lower priority messages


	if (commandTag == CMD_TAG_DEBUG_HI_TEST_MSG)
	{

		//Based on which Arduino sent the command, that same Arduino will get a response
		if (originRoverCommType == ROVERCOMM_PC_USB)
		{
			pc_usb_msg_queue = CMD_TAG_DEBUG_HI_TEST_MSG;
		}//end if
		else if (originRoverCommType == ROVERCOMM_COMM || originRoverCommType == ROVERCOMM_CMNC)
		{
			comm_msg_queue = CMD_TAG_DEBUG_HI_TEST_MSG;
		}//end else if		
		else if (originRoverCommType == ROVERCOMM_NAVI)
		{
			navi_msg_queue = CMD_TAG_DEBUG_HI_TEST_MSG;
		}//end else if		
		else if (originRoverCommType == ROVERCOMM_AUXI)
		{
			auxi_msg_queue = CMD_TAG_DEBUG_HI_TEST_MSG;
		}//end else if		

		

		 //Clears/resets all data pointers before setting them.
		clearRoverDataPointers();
		//Sets the roverDataPointer to the origin
		setRoverDataPointer(roverDataPointer, originRoverCommType);//override the default and send the response back to the requestor


	}//end if
	 //Bye Command - DEBUG
	else if (commandTag == CMD_TAG_DEBUG_BYE_TEST_MSG)
	{

		//Based on which Arduino sent the command, that same Arduino will get a response
		if (originRoverCommType == ROVERCOMM_PC_USB)
		{
			pc_usb_msg_queue = CMD_TAG_DEBUG_BYE_TEST_MSG;
		}//end if
		else if (originRoverCommType == ROVERCOMM_COMM || originRoverCommType == ROVERCOMM_CMNC)
		{
			comm_msg_queue = CMD_TAG_DEBUG_BYE_TEST_MSG;
		}//end else if		
		else if (originRoverCommType == ROVERCOMM_NAVI)
		{
			navi_msg_queue = CMD_TAG_DEBUG_BYE_TEST_MSG;
		}//end else if		
		else if (originRoverCommType == ROVERCOMM_AUXI)
		{
			auxi_msg_queue = CMD_TAG_DEBUG_BYE_TEST_MSG;
		}//end else if		

		 //Clears/resets all data pointers before setting them.
		clearRoverDataPointers();
		//Sets the roverDataPointer to the origin
		setRoverDataPointer(roverDataPointer, originRoverCommType);//override the default and send the response back to the requestor

	}//end else if
	 //Invalid - DEBUG
	else
	{

		//Based on which Arduino sent the command, that same Arduino will get a response
		if (originRoverCommType == ROVERCOMM_PC_USB)
		{
			pc_usb_msg_queue = CMD_TAG_INVALID_CMD;
		}//end if
		else if (originRoverCommType == ROVERCOMM_COMM || originRoverCommType == ROVERCOMM_CMNC)
		{
			comm_msg_queue = CMD_TAG_INVALID_CMD;
		}//end else if		
		else if (originRoverCommType == ROVERCOMM_NAVI)
		{
			navi_msg_queue = CMD_TAG_INVALID_CMD;
		}//end else if		
		else if (originRoverCommType == ROVERCOMM_AUXI)
		{
			auxi_msg_queue = CMD_TAG_INVALID_CMD;
		}//end else if		
	
		//Clears/resets all data pointers before setting them.
		clearRoverDataPointers();
		//Sets the roverDataPointer to the origin
		setRoverDataPointer(roverDataPointer, originRoverCommType);//override the default and send the response back to the requestor

	}//end else if
	 //else output nothing	





	return;
}//end of commandDirector()






void clearRoverDataPointers()
{
	//Clears/resets all data pointers
	roverDataForMAIN = NULL;
	roverDataForPC_USB = NULL;
	roverDataForCOMM = NULL;
	roverDataForNAVI = NULL;
	roverDataForAUXI = NULL;
	
}//end of clearRoverDataPointer()

void setRoverDataPointer(RoverData * roverDataPointer, byte roverCommType)
{
	//This sets the roverDataPointer to the desired roverCommType.
	//Note: This function can be called more than once to set more than one roverDataPointer to the same data (i.e. if the same data needs to be shared in multiple places)
	if (roverCommType == ROVERCOMM_PC_USB)
	{
		roverDataForPC_USB = roverDataPointer;
	}//end if
	else if (roverCommType == ROVERCOMM_COMM || roverCommType == ROVERCOMM_CMNC)
	{
		roverDataForCOMM = roverDataPointer;
	}//end else if
	else if (roverCommType == ROVERCOMM_NAVI)
	{
		roverDataForNAVI = roverDataPointer;
	}//end else if	
	else if (roverCommType == ROVERCOMM_AUXI)
	{
		roverDataForAUXI = roverDataPointer;
	}//end else if		
	else//the roverCommType should be for this local Arduino (i.e. ROVERCOMM_MAIN)
	{
		roverDataForMAIN = roverDataPointer;
	}//end else	
	
}//end of setRoverDataPointer()


void createDataFromQueueFor(byte roverCommDestination)
{
	//Note: The origin of the messsage will change every time it passes through an Arduino (i.e. using the RoverCommandProcessor::createCmd() with a Rover Comm Type passed to it). It shows the last originating Arduino that handled the data. If the true origin is required, that should be placed in the command data where it's not altered.

	byte queueOfInterest;
	char * commandDataOfInterest;//holds the rover's command data string
	char createdCommand[ROVER_COMM_SENTENCE_LENGTH];//holds the pointer to the created command
	//Based on the destination roverCommType of interest, set which queue and rover data the outgoing message should be based on
	if (roverCommDestination == ROVERCOMM_PC_USB)
	{
		queueOfInterest = pc_usb_msg_queue;
		if (roverDataForPC_USB != NULL)//make sure the roverDataPointer is not NULL
		{
			commandDataOfInterest = roverDataForPC_USB->getCommandData();
		}//end if
		else
		{
			commandDataOfInterest = "";//else if it's NULL, set the data to nothing
		}//end else		
	}//end if
	else if (roverCommDestination == ROVERCOMM_COMM)
	{
		queueOfInterest = comm_msg_queue;
		if (roverDataForCOMM != NULL)//make sure the roverDataPointer is not NULL
		{
			commandDataOfInterest = roverDataForCOMM->getCommandData();
		}//end if
		else
		{
			commandDataOfInterest = "";//else if it's NULL, set the data to nothing
		}//end else
	}//end else if
	else if (roverCommDestination == ROVERCOMM_NAVI)
	{
		queueOfInterest = navi_msg_queue;
		if (roverDataForNAVI != NULL)//make sure the roverDataPointer is not NULL
		{
			commandDataOfInterest = roverDataForNAVI->getCommandData();
		}//end if
		else
		{
			commandDataOfInterest = "";//else if it's NULL, set the data to nothing
		}//end else
	}//end else if
	else if (roverCommDestination == ROVERCOMM_AUXI)
	{
		queueOfInterest = auxi_msg_queue;
		if (roverDataForAUXI != NULL)//make sure the roverDataPointer is not NULL
		{
			commandDataOfInterest = roverDataForAUXI->getCommandData();
		}//end if
		else
		{
			commandDataOfInterest = "";//else if it's NULL, set the data to nothing
		}//end else
	}//end else if
	 //else
	 //do nothing

	
	
	//Use the Rover Command Creator to add the headers to the data string (origin, destination, priority level, command tag number, the message string)
	switch (queueOfInterest)
	{


		case CMD_TAG_DEBUG_HI_TEST_MSG:
			//Use the Rover Command Creator to add the headers to the data string (origin, destination, priority level, command tag number, the message string)
			RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_DEBUG_HI_TEST_MSG, commandDataOfInterest, createdCommand);			
			break;
		case CMD_TAG_DEBUG_BYE_TEST_MSG:
			//Use the Rover Command Creator to add the headers to the data string (origin, destination, priority level, command tag number, the message string)
			RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_DEBUG_BYE_TEST_MSG, commandDataOfInterest, createdCommand);
			break;
		case CMD_TAG_INVALID_CMD:
			//Use the Rover Command Creator to add the headers to the data string (origin, destination, priority level, command tag number, the message string)			
			RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_INVALID_CMD, getMsgString(1), createdCommand);			
			break;
		default:
			//do nothing
			break;
	}//end switch
	
	
	if (roverCommDestination == ROVERCOMM_PC_USB)
	{
		sprintf(txMsgBuffer_PC_USB, createdCommand);
	}//end if
	else if (roverCommDestination == ROVERCOMM_COMM || roverCommDestination == ROVERCOMM_CMNC)
	{
		sprintf(txMsgBuffer_COMM, createdCommand);
	}//end else if
	else if (roverCommDestination == ROVERCOMM_NAVI)
	{
		sprintf(txMsgBuffer_NAVI, createdCommand);
	}//end else if	
	else if (roverCommDestination == ROVERCOMM_AUXI)
	{
		sprintf(txMsgBuffer_AUXI, createdCommand);
	}//end else if		
	 //else

}//end of createDataFromQueueFor()


/*
void createDataFromQueueFor(byte roverCommDestination)
{


	//Note: The origin of the messsage will change every time it passes through an Arduino (i.e. using the RoverCommandProcessor::createCmd() with a Rover Comm Type passed to it). It shows the last originating Arduino that handled the data. If the true origin is required, that should be placed in the command data where it's not altered.

	byte queueOfInterest;
	char * commandDataOfInterest;//holds the rover's command data string

	//Based on the destination roverCommType of interest, set which queue and rover data the outgoing message should be based on
	if (roverCommDestination == ROVERCOMM_PC_USB)
	{
		queueOfInterest = pc_usb_msg_queue;
		if (roverDataForPC_USB != NULL)//make sure the roverDataPointer is not NULL
		{
			commandDataOfInterest = roverDataForPC_USB->getCommandData();
		}//end if
		else
		{
			commandDataOfInterest = "";//else if it's NULL, set the data to nothing
		}//end else		
	}//end if
	else if (roverCommDestination == ROVERCOMM_COMM)
	{
		queueOfInterest = comm_msg_queue;
		if (roverDataForCOMM != NULL)//make sure the roverDataPointer is not NULL
		{
			commandDataOfInterest = roverDataForCOMM->getCommandData();
		}//end if
		else
		{
			commandDataOfInterest = "";//else if it's NULL, set the data to nothing
		}//end else
	}//end else if
	else if (roverCommDestination == ROVERCOMM_NAVI)
	{
		queueOfInterest = navi_msg_queue;
		if (roverDataForNAVI != NULL)//make sure the roverDataPointer is not NULL
		{
			commandDataOfInterest = roverDataForNAVI->getCommandData();
		}//end if
		else
		{
			commandDataOfInterest = "";//else if it's NULL, set the data to nothing
		}//end else
	}//end else if
	else if (roverCommDestination == ROVERCOMM_AUXI)
	{
		queueOfInterest = auxi_msg_queue;
		if (roverDataForAUXI != NULL)//make sure the roverDataPointer is not NULL
		{
			commandDataOfInterest = roverDataForAUXI->getCommandData();
		}//end if
		else
		{
			commandDataOfInterest = "";//else if it's NULL, set the data to nothing
		}//end else
	}//end else if
	 //else
	 //do nothing


	switch (queueOfInterest)
	{


	case CMD_TAG_DEBUG_HI_TEST_MSG:
		//Use the Rover Command Creator to add the headers to the data string (origin, destination, priority level, command tag number, the message string)
		sprintf(txMsgBufferShared, RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_DEBUG_HI_TEST_MSG, commandDataOfInterest));
		sprintf(txMsgBufferShared, RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_DEBUG_HI_TEST_MSG, commandDataOfInterest));
		break;
	case CMD_TAG_DEBUG_BYE_TEST_MSG:
		//Use the Rover Command Creator to add the headers to the data string (origin, destination, priority level, command tag number, the message string)
		sprintf(txMsgBufferShared, RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_DEBUG_BYE_TEST_MSG, commandDataOfInterest));
		sprintf(txMsgBufferShared, RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_DEBUG_BYE_TEST_MSG, commandDataOfInterest));
		break;
	case CMD_TAG_INVALID_CMD:
		//Use the Rover Command Creator to add the headers to the data string (origin, destination, priority level, command tag number, the message string)			
		sprintf(txMsgBufferShared, RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_INVALID_CMD, getMsgString(1)));
		sprintf(txMsgBufferShared, RoverCommandCreator::createCmd(ROVERCOMM_MAIN, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_INVALID_CMD, getMsgString(1)));
		break;

	default:
		//do nothing
		break;
	}//end switch


}//end of createDataFromQueueFor()


*/


void txData(char * txData, byte roverCommType)
{
	//Note: This function varies for different Arduinos

	if (roverCommType == ROVERCOMM_PC_USB)
	{
		//transmit the data to PC_USB
		_PC_USB_SERIAL_.println(txData);
	}//end if
	else if (roverCommType == ROVERCOMM_COMM)
	{
		//transmit the data to COMM
		_COMM_SERIAL_.println(txData);
	}//end else if
	else if (roverCommType == ROVERCOMM_NAVI)
	{
		//transmit the data to NAVI
		_NAVI_SERIAL_.println(txData);
	}//end else if
	else if (roverCommType == ROVERCOMM_AUXI)
	{
		//transmit the data to AUXI
		_AUXI_SERIAL_.println(txData);
	}//end else if
	else
	{
		//do nothing
	}//end else
}//end of txData()







void redirectData(RoverComm * roverComm)
{



	/*
	Note:
	For program efficiency, instead of sending all redirect messages, it sends only one per channel.
	This is because between each message transmission, there needs to be a delay (since the receiving code is designed only to receive so many messages at once.
	*/

	RoverData * roverData;
	byte roverCommType;

	
	//Get the roverData object from the RoverComm Object
	roverData = roverComm->getRoverDataObject();

	//Get destination from either AUXI's or PC_USB's Rover Data
	roverCommType = roverData->getDestinationCommType();//get the destination comm type for the roverData
	
	
	//If the destination is from: 1) AUXI (or COMM, CMNC, NAVI) to PC_USB or 2) PC_USB to PC_USB (loopback)
	if (roverCommType == ROVERCOMM_PC_USB)
	{
		//And if redirection to PC_USB is allowed
		if (BooleanBitFlags::flagIsSet(flagSet_MessageControl, _BTFG_REDIRECT_TO_PC_USB_))
		{
			#ifdef _DEBUG_REDIRECTION_NOTICE
				Serial.println(F("Redirect2PC_USB"));
			#endif
			//Then transmit the data out to PC_USB
			txData(roverComm->getRxData(), ROVERCOMM_PC_USB);
		}//end if		 
	}//end if	
	//Else if the destination is from: 1) AUXI or NAVI to COMM or CMNC or 2) COMM or CMNC to COMM or CMNC (loopback)
	else if (roverCommType == ROVERCOMM_COMM || roverCommType == ROVERCOMM_CMNC)
	{
		//And if redirection to COMM or CMNC is allowed
		if (BooleanBitFlags::flagIsSet(flagSet_MessageControl, _BTFG_REDIRECT_TO_COMM_))//Checks to see if redirection is allowed to AUXI, MAIN, or NAVI
		{
			#ifdef _DEBUG_REDIRECTION_NOTICE
				Serial.println(F("Redirect2COMM"));
			#endif
			//Then transmit the data out to AUXI
			txData(roverComm->getRxData(), ROVERCOMM_COMM);
		}//end if		 
	}//end if		
	//Else if the destination is from: 1) AUXI, CMNC, or COMM to NAVI or 2) NAVI to NAVI (loopback)
	else if (roverCommType == ROVERCOMM_NAVI)
	{
		//And if redirection to NAVI is allowed
		if (BooleanBitFlags::flagIsSet(flagSet_MessageControl, _BTFG_REDIRECT_TO_NAVI_))//Checks to see if redirection is allowed to AUXI, MAIN, or NAVI
		{
			#ifdef _DEBUG_REDIRECTION_NOTICE
				Serial.println(F("Redirect2NAVI"));
			#endif
			//Then transmit the data out to AUXI
			txData(roverComm->getRxData(), ROVERCOMM_NAVI);
		}//end if		 
	}//end if	
	//Else if the destination is from: 1) NAVI, CMNC, or COMM to AUXI or 2) AUXI to AUXI (loopback)
	else if (roverCommType == ROVERCOMM_AUXI)
	{
		//And if redirection to AUXI is allowed
		if (BooleanBitFlags::flagIsSet(flagSet_MessageControl, _BTFG_REDIRECT_TO_AUXI_))//Checks to see if redirection is allowed to AUXI, MAIN, or NAVI
		{
			#ifdef _DEBUG_REDIRECTION_NOTICE
				Serial.println(F("Redirect2AUXI"));
			#endif
			//Then transmit the data out to AUXI
			txData(roverComm->getRxData(), ROVERCOMM_AUXI);
		}//end if		 
	}//end if	
	
}//End of redirectData()




char * getMsgString(byte arrayIndex) {
	memset(programMem2RAMBuffer, 0, sizeof(programMem2RAMBuffer));//clear char array buffer
	return strcpy_P(programMem2RAMBuffer, (char*)pgm_read_word(&(msg_str_table[arrayIndex])));//copy the fixed string from flash into the char buffer
}//end of getMsgString()

