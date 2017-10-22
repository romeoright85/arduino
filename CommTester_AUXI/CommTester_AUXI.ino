//Used for AUXI - 2

//Note: The test cases varies for different Arduinos

//To test code, in RoverConfig uncomment _DEBUG_ALL_SERIALS_WITH_USB_SERIAL_

//Note: Can send this (about max size of the Rover Command Data) to test: "/6c3--*002abcdefghijklm^"


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
Debug data: /6c301*HelloMAINtoAUXI
Also uncomment flag(s) in RoverComm.h to see the received string, etc.
Note: You will get an "/3c400*004invlcmd" but that is expected and fine since "/6c301*HelloMAINtoAUXI" isn't a registered command. But this test the routing of the data is correct.
*/


//Test case 3a:
/*
Send (i.e. with your keyboard and using a terminal window) over USB serial
/6c3--*002hi
to test the command interface for this Arduino
*/

//Test case 3b:
/*
Send (i.e. with your keyboard and using a terminal window) over USB serial
/6c3--*003bye
to test the command interface for this Arduino
*/



//Configuration defines for #includes (must come before the #includes)
//Must define this before calling RoverConfig.h (either directly or through another header file)
#ifndef _COMMAND_CREATION_DEFINITIONS
#define _COMMAND_CREATION_DEFINITIONS //for RoverCommandDefs.h
#endif
#define _ARD_2_AUXI_H //define this flag to turn on AUXI definitions
#ifndef _AUXI_BIT_FLAGS_
#define _AUXI_BIT_FLAGS_ //For RoverBitFlags.h
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

#ifdef _DEBUG_COMM_BROADCAST
#define _SERIAL_DEBUG_CHANNEL_ _MAIN_SERIAL_
#else
#define _SERIAL_DEBUG_CHANNEL_ _PC_USB_SERIAL_
#endif
//============End of Debugging: Serial Channel Selection


//============Global Declarations




//Message Queues
byte pc_usb_msg_queue = CMD_TAG_NO_MSG;
byte main_msg_queue = CMD_TAG_NO_MSG;



//Message Char Array
char txMsgBufferShared[UNIV_BUFFER_SIZE];//transmit buffer shared between MAIN and CMNC
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
byte ch2Status = DATA_STATUS_NOT_READY;//for MAIN



//Rover Data and COMMs
//RoverData pointers and RoverComms
//Ch1 is between AUXI to PC_USB
RoverData * roverDataCh1_COMM = new RoverData();
RoverComm * roverComm_Ch1 = new RoverComm(roverDataCh1_COMM);
//Ch2 is between AUXI to MAIN
RoverData * roverDataCh2_COMM = new RoverData();
RoverComm * roverComm_Ch2 = new RoverComm(roverDataCh2_COMM);
//Command Parsers
//Rover Data Pointers for use with either internal processing or outgoing messages
RoverData * roverDataForAUXI;//pointer used access the RoverData which has the command data outgoing to COMM
RoverData * roverDataForPC_USB;//pointer used access the RoverData which has the command data outgoing to CMNC
RoverData * roverDataForMAIN;//pointer used access the RoverData which has the command data outgoing to MAIN

							 //Flag(s) - Message Controls
byte flagSet_MessageControl = _BTFG_NONE_;

//Note: Make sure to add any new objects created to this array
RoverReset * resetArray[] = {
	roverDataCh1_COMM,
	roverComm_Ch1,
	roverDataCh2_COMM,
	roverComm_Ch2
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
	_MAIN_SERIAL_.begin(MAIN_BAUD_RATE);



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



	 //1b. receive and process data from MAIN
	 //rxData() from MAIN
	 //Reset status flag
	ch2Status = DATA_STATUS_NOT_READY;
	//Clear all Rx'ed data before getting new data				
	roverComm_Ch2->clearRxData();
	//Receive data
	ch2Status = rxData(roverComm_Ch2, ROVERCOMM_AUXI);
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



	 //Note: The debug code below varies for different Arduinos
	 //DEBUG Code: Data Injection (from MAIN to AUXI)	
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
	roverComm_Ch1->setRxData("/4c301*HelloMAINtoAUXI", sizeof("/4c301*HelloMAINtoAUXI"));
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



	 //2. Processes data


	 //2a. Processes data from PC_USB
	if (ch1Status == DATA_STATUS_VALID)
	{


		//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
		dataDirector(roverDataCh1_COMM, DATA_REDIRECT_ENABLED, flagSet_MessageControl, _BTFG_DATA_WAS_FOR_AUXI_CH1_);
		//Note: this is a local .ino function
		if (BooleanBitFlags::flagIsSet(flagSet_MessageControl, _BTFG_DATA_WAS_FOR_AUXI_CH1_))//If there was data from the PC_USB (Ch1), and it was for AUXI
		{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
			commandDirector(roverDataCh1_COMM);
		}//end if	
	}//end if
	 //else the data was invalid or not ready, so do nothing


	 //2b. Processes data from MAIN
	if (ch2Status == DATA_STATUS_VALID)
	{

		//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
		dataDirector(roverDataCh2_COMM, DATA_REDIRECT_ENABLED, flagSet_MessageControl, _BTFG_DATA_WAS_FOR_AUXI_CH2_);
		//Note: this is a local .ino function
		if (BooleanBitFlags::flagIsSet(flagSet_MessageControl, _BTFG_DATA_WAS_FOR_AUXI_CH2_))//If there was data from the PC_USB (Ch1), and it was for AUXI
		{
			//Run the command director to process the allowed commands (i.e. sets flags, prepares message queues, changes modes/states, etc.)			
			commandDirector(roverDataCh2_COMM);
		}//end if	
	}//end if
	 //else the data was invalid or not ready, so do nothing






	 //3. Creates and sends data, reroutes data, and/or executes the command




	 //Creates data for PC_USB and sends it to PC_USB
	if (pc_usb_msg_queue != CMD_TAG_NO_MSG)
	{
		createDataFromQueueFor(ROVERCOMM_PC_USB);
		txData(txMsgBufferShared, ROVERCOMM_PC_USB);
	}//end if


	 //Creates data for MAIN and sends it to MAIN
	if (main_msg_queue != CMD_TAG_NO_MSG)
	{
		createDataFromQueueFor(ROVERCOMM_MAIN);
		txData(txMsgBufferShared, ROVERCOMM_MAIN);
	}//end if


	 //Redirects all data
	redirectData();



	//4. Clears variables for future use

	//clears message queue(s) and redirect flags		
	pc_usb_msg_queue = CMD_TAG_NO_MSG;
	main_msg_queue = CMD_TAG_NO_MSG;
	BooleanBitFlags::clearFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_PC_USB_);
	BooleanBitFlags::clearFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_MAIN_);







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
	else if (roverCommType == ROVERCOMM_MAIN)
	{


		if (_MAIN_SERIAL_.available() > 1)
		{


			//initialize the counter
			counter = 0;

			while (_MAIN_SERIAL_.available() > 0 && counter <= ROVER_COMM_SENTENCE_LENGTH)//while there is data on the Serial RX Buffer and the length is not over the max GPS sentence length
			{
				//Read one character of serial data at a time
				//Note: Must type cast the Serial.Read to a char since not saving it to a char type first
				roverComm->appendToRxData((char)_MAIN_SERIAL_.read());//construct the string one char at a time
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

	if (roverCommType == ROVERCOMM_AUXI)
	{
		//if the data is for this unit, AUXI
		BooleanBitFlags::setFlagBit(flagSet, flagOfInterest);//set the status such that the data was for this unit, AUXI
															 //process it back in the main loop (to prevent software stack from being too deep)
	}//end if
	 //else check to see if the data was for other cases
	else if (redirectOption == DATA_REDIRECT_ENABLED)
	{
		if (roverCommType == ROVERCOMM_PC_USB)
		{
			//if the data is for PC_USB, transmit the data out from AUXI to PC_USB
			//Set redirect to PC_USB flag to true			
			BooleanBitFlags::setFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_PC_USB_);
		}//end else if		
		else if (roverCommType == ROVERCOMM_NAVI || roverCommType == ROVERCOMM_COMM || roverCommType == ROVERCOMM_MAIN || roverCommType == ROVERCOMM_CMNC)
		{
			//if the data is for either NAVI, COMM, or MAIN, transmit the data out from AUXI to MAIN since AUXI only can talk to MAIN and not NAVI or COMM (and MAIN will process it accordingly or reroute it if needed)
			//Set redirect to MAIN flag to true			
			BooleanBitFlags::setFlagBit(flagSet_MessageControl, _BTFG_REDIRECT_TO_MAIN_);
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
	//Then only run the highest priority functions for AUXI last, so it will overwrite anything else, right before state transition.




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
	//Note: The roverDataPointer should be going to AUXI (else it would have been redirected already with dataDirector).
	//However, it can be overwritten in the if/else conditions below based on the command tag for special cases like when it redirects itself to the original sender (i.e. when the command is a request for data/status)


	//Run highest priority functions here. //this will override any lower priority messages







	if (commandTag == CMD_TAG_DEBUG_HI_TEST_MSG)
	{


		//Based on which Arduino sent the command, that same Arduino will get a response
		if (originRoverCommType == ROVERCOMM_PC_USB)
		{
			pc_usb_msg_queue = CMD_TAG_DEBUG_HI_TEST_MSG;
		}//end if
		else if (originRoverCommType == ROVERCOMM_NAVI || originRoverCommType == ROVERCOMM_COMM || originRoverCommType == ROVERCOMM_MAIN || originRoverCommType == ROVERCOMM_CMNC)
		{
			main_msg_queue = CMD_TAG_DEBUG_HI_TEST_MSG;
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
		else if (originRoverCommType == ROVERCOMM_NAVI || originRoverCommType == ROVERCOMM_COMM || originRoverCommType == ROVERCOMM_MAIN || originRoverCommType == ROVERCOMM_CMNC)
		{
			main_msg_queue = CMD_TAG_DEBUG_BYE_TEST_MSG;
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
		else if (originRoverCommType == ROVERCOMM_NAVI || originRoverCommType == ROVERCOMM_COMM || originRoverCommType == ROVERCOMM_MAIN || originRoverCommType == ROVERCOMM_CMNC)
		{
			main_msg_queue = CMD_TAG_INVALID_CMD;
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
	roverDataForAUXI = NULL;
	roverDataForPC_USB = NULL;
	roverDataForMAIN = NULL;
}//end of clearRoverDataPointer()

void setRoverDataPointer(RoverData * roverDataPointer, byte roverCommType)
{
	//This sets the roverDataPointer to the desired roverCommType.
	//Note: This function can be called more than once to set more than one roverDataPointer to the same data (i.e. if the same data needs to be shared in multiple places)
	if (roverCommType == ROVERCOMM_PC_USB)
	{
		roverDataForPC_USB = roverDataPointer;
	}//end if
	else if (roverCommType == ROVERCOMM_NAVI || roverCommType == ROVERCOMM_COMM || roverCommType == ROVERCOMM_MAIN || roverCommType == ROVERCOMM_CMNC)
	{
		roverDataForMAIN = roverDataPointer;
	}//end else if
	else//the roverCommType should be for this local Arduino (i.e. ROVERCOMM_AUXI)
	{
		roverDataForAUXI = roverDataPointer;
	}//end else
}//end of setRoverDataPointer()


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
	else if (roverCommDestination == ROVERCOMM_MAIN)
	{
		queueOfInterest = main_msg_queue;
		if (roverDataForMAIN != NULL)//make sure the roverDataPointer is not NULL
		{
			commandDataOfInterest = roverDataForMAIN->getCommandData();
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
		sprintf(txMsgBufferShared, RoverCommandCreator::createCmd(ROVERCOMM_AUXI, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_DEBUG_HI_TEST_MSG, commandDataOfInterest));
		break;
	case CMD_TAG_DEBUG_BYE_TEST_MSG:
		//Use the Rover Command Creator to add the headers to the data string (origin, destination, priority level, command tag number, the message string)
		sprintf(txMsgBufferShared, RoverCommandCreator::createCmd(ROVERCOMM_AUXI, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_DEBUG_BYE_TEST_MSG, commandDataOfInterest));
		break;
	case CMD_TAG_INVALID_CMD:
		//Use the Rover Command Creator to add the headers to the data string (origin, destination, priority level, command tag number, the message string)			
		sprintf(txMsgBufferShared, RoverCommandCreator::createCmd(ROVERCOMM_AUXI, roverCommDestination, CMD_PRI_LVL_0, CMD_TAG_INVALID_CMD, getMsgString(1)));
		break;

	default:
		//do nothing
		break;
	}//end switch


}//end of createDataFromQueueFor()





void txData(char * txData, byte roverCommType)
{
	//Note: This function varies for different Arduinos

	if (roverCommType == ROVERCOMM_PC_USB)
	{
		//transmit the data to PC_USB
		_PC_USB_SERIAL_.println(txData);
	}//end if
	else if (roverCommType == ROVERCOMM_MAIN)
	{
		//transmit the data to MAIN
		_MAIN_SERIAL_.println(txData);
	}//end else if
	else
	{
		//do nothing
	}//end else
}//end of txData()







void redirectData()
{



	/*
	Note:
	When redirectData() is called it will process and send data for both MAIN and then PC_USB. redirectData() only has to be called once and it will redirect both data.
	For program efficiency, instead of sending all redirect messages, it sends only one per channel.
	*/

	byte roverCommType;


	//1. Data from MAIN being redirected to PC_USB
	roverCommType = roverDataCh2_COMM->getDestinationCommType();//get the destination comm type for roverDataCh2_COMM

																//Redirection from MAIN to PC_USB
	if (BooleanBitFlags::flagIsSet(flagSet_MessageControl, _BTFG_REDIRECT_TO_PC_USB_))
	{

		//Priority of the redirect is given by the order of the if/else statement.  All other redirect messages going to the same destination will get dropped/lost.
		//Priority 1: From MAIN (MAIN, COMM, or NAVI) to PC_USB
		if (roverCommType == ROVERCOMM_PC_USB)
		{
			//if the data is for PC_USB, transmit the data out to PC_USB
			txData(roverComm_Ch2->getRxData(), ROVERCOMM_PC_USB);
		}//end if
		 //Priority 2: No other cases
		 //else (place holder)
		 //Note: For the AUXI there is only one other channel, so it always gets the priority
	}//end if	

	 //2. Data from PC_USB being redirected to MAIN
	roverCommType = roverDataCh1_COMM->getDestinationCommType();//get the destination comm type for roverDataCh1_COMM

																//Redirection from PC_USB to MAIN, COMM, or NAVI
	if (BooleanBitFlags::flagIsSet(flagSet_MessageControl, _BTFG_REDIRECT_TO_MAIN_))//Checks to see if redirection is allowed to MAIN, AUXI, or NAVI
	{
		//Priority of the redirect is given by the order of the if/else statement.  All other redirect messages going to the same destination will get dropped/lost.
		//Priority 1: From PC_USB to MAIN, COMM, or NAVI
		if (roverCommType == ROVERCOMM_NAVI || roverCommType == ROVERCOMM_COMM || roverCommType == ROVERCOMM_MAIN || roverCommType == ROVERCOMM_CMNC)
		{
			//if the data is for MAIN, COMM, or NAVI, transmit the data out to MAIN
			txData(roverComm_Ch1->getRxData(), ROVERCOMM_MAIN);
		}//end if
		 //Priority 2: No other cases
		 //else (place holder)
		 //Note: For the AUXI there is only one other channel, so it always gets the priority

	}//end if	


	 //else do nothing

}//End of redirectData()




char * getMsgString(byte arrayIndex) {
	memset(programMem2RAMBuffer, 0, sizeof(programMem2RAMBuffer));//clear char array buffer
	return strcpy_P(programMem2RAMBuffer, (char*)pgm_read_word(&(msg_str_table[arrayIndex])));//copy the fixed string from flash into the char buffer
}//end of getMsgString()

