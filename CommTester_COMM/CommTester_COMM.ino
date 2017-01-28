//Used for COMM - 4

//NOTE: txData() in the RoverCommTester will output any data sent to the COMM with the destination CMNC back out to the CMNC. So if you want to test a loopback, send from CMNC with the destination CMNC to get a loopback

//Note: The test cases varies for different Arduinos

//Note: Can send this (about max size) to test: "/-c5--*cmd2asdasdfasdfgsdfgsdfgsfdgd12321123123153452364564564^"


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
Debug data: /3c101*HelloMAINtoCMNC
Also uncomment flag(s) in RoverComm.h to see the received string, etc.
*/


//Test case 3a:
/*
	Send (i.e. with your keyboard and using a terminal window) over USB serial
		/-c5--*hi
	to test the command interface for this Arduino
*/

//Test case 3b:
/*
	Send (i.e. with your keyboard and using a terminal window) over USB serial
		/-c5--*bye
	to test the command interface for this Arduino
*/





//Must define this before calling RoverConfig.h (either directly or through another header file)
#define _ARD_4_COMM_H //define this flag to turn on COMM definitions
#include <RoverData.h>
#include <RoverComm.h> //calls RoverConfig.h
#include <RoverCommand.h>
#include <SoftwareSerial.h>



//Global Variables
//RoverData pointers and RoverComms
//Ch1 is between CMNC and COMM
RoverData * roverDataCh1_COMM = new RoverData();
RoverComm * roverComm_Ch1 = new RoverComm(roverDataCh1_COMM);
//Ch2 is between COMM and MAIN
RoverData * roverDataCh2_COMM = new RoverData();
RoverComm * roverComm_Ch2 = new RoverComm(roverDataCh2_COMM);
//Command Parser
RoverCommand * roverCommand = new RoverCommand();


//{ SW_UART Declarations
	//{ MAIN SW_UART
		SoftwareSerial swSerialMAIN(COMM_SW_UART_RX_PIN, COMM_SW_UART_TX_PIN); // RX, TX, Note declare this in global and not setup() else it won't work
	//} End of MAIN SW_UART
//} End of SW_UART Declarations






//SW resettable variables
//flag for data for this Arduino
boolean dataWasForCOMM;
//flags for valid data ready
boolean ch1Valid;//for PC USB/CNMC
boolean ch2Valid;//for MAIN

RoverReset * resetArray[] = {
	roverDataCh1_COMM,
	roverComm_Ch1,
	roverDataCh2_COMM,
	roverComm_Ch2,
	roverCommand
};//for pointers, pass them directly, for objects pass the address



void setup() {
	//resetting all objects in this sketch
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		if (!resetArray[i] == NULL)//if the object isn't null
		{
			resetArray[i]->reset();//reset the object	
		}
	}
	//Reset flags
	dataWasForCOMM = false;
	ch1Valid = false;
	ch2Valid = false;


	//Setup the HW_UART
	Serial.begin(CMNC_BAUD_RATE);

	//Setup the SW_UART
	swSerialMAIN.begin(MAIN_BAUD_RATE);
}


void loop() {


	//Reset flags
	ch1Valid = false;
	ch2Valid = false;
	

	//1. Receive and process data

	//1a. receive data and process data from CMNC (the PC)
	roverDataCh1_COMM->clearData();//clear data before getting new data
	ch1Valid = rxData(roverComm_Ch1, ROVERCOMM_CMNC);
		
	//1b. receive data and process data from MAIN
	roverDataCh2_COMM->clearData();//clear data before getting new data
	ch2Valid = rxData(roverComm_Ch2, ROVERCOMM_MAIN);//Note: this is a local .ino function


	//Note: The debug code below varies for different Arduinos
	//DEBUG Code: Data Injection (from MAIN to CMNC)	
	#ifdef _DEBUG_IMU_TEST_CASE_
		roverComm_Ch2->setRxData("!ANG:1.23,4.56,78.90", sizeof("!ANG:1.23,4.56,78.90"));
		ch2Valid = true;
	#endif
	#ifdef _DEBUG_ROVER_TEST_CASE_
		roverComm_Ch2->setRxData("/3c101*HelloMAINtoCMNC", sizeof("/3c101*HelloMAINtoCMNC");
		ch2Valid = true;
	#endif
			

	//2. Transmit data and/or execute command
	
	//2a. For data from MAIN, transmit the data to it's proper destination if it was meant for another Arduino
	//		or take any actions if the data was meant for this unit, COMM
	if (ch1Valid)
	{

		
		//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
		dataDirector(roverDataCh1_COMM);//Note: this is a local .ino function
		

		//if the data was for this unit
		if (dataWasForCOMM)
		{
			
			//send the RoverData to the roverCommand's parser to get the command
			roverCommand->parseCommand(roverDataCh1_COMM->getData(), roverDataCh1_COMM->getDataLength());
			commandDirector(roverCommand->getCommand());
		}
	}
	else
	{
		//The data was invalid, so do nothing			
	}

	//2b. For data from CMNC, transmit the data to it's proper destination if it was meant for another Arduino
	//		or take any actions if the data was meant for this unit, COMM
	if (ch2Valid)
	{

		
		//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
		dataDirector(roverDataCh2_COMM);//Note: this is a local .ino function

		//4. Take any actions if the data was meant for this unit, COMM
		if (dataWasForCOMM)
		{
			
			//send the RoverData to the roverCommand's parser to get the command
			roverCommand->parseCommand(roverDataCh2_COMM->getData(), roverDataCh2_COMM->getDataLength());
			commandDirector(roverCommand->getCommand());

		}
	}
	else
	{
		//The data was invalid, so do nothing
	}

	delay(1000);//add some delay in between cycles


}//end loop


boolean rxData(RoverComm * roverComm, byte roverCommType) {

	byte counter;
	boolean dataReady = false;
	boolean validData = false;

	if (roverCommType == ROVERCOMM_CMNC)
	{

		if (Serial.available() > 1)
		{
			//initialize the counter
			counter = 0;

			while (Serial.available() > 0 && counter <= ROVER_COMM_SENTENCE_LENGTH)//while there is data on the Serial RX Buffer and the length is not over the max GPS sentence length
			{
				//Read one character of serial data at a time
				//Note: Must type cast the Serial.Read to a char since not saving it to a char type first
				roverComm->appendToRxData((char)Serial.read());//construct the string one char at a time
				counter++;
				delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
			}//end while
			dataReady = true;
		}//end if
		else
		{
			dataReady = false;
		}//end else
	}//end if
	else if (roverCommType == ROVERCOMM_MAIN)
	{
		if (swSerialMAIN.available() > 1)
		{
			//initialize the counter
			counter = 0;

			while (swSerialMAIN.available() > 0 && counter <= ROVER_COMM_SENTENCE_LENGTH)//while there is data on the Serial RX Buffer and the length is not over the max GPS sentence length
			{
				//Read one character of serial data at a time
				//Note: Must type cast the Serial.Read to a char since not saving it to a char type first
				roverComm->appendToRxData((char)swSerialMAIN.read());//construct the string one char at a time
				counter++;
				delay(1);//add a small delay between each transmission to reduce noisy and garbage characters
			}//end while
			dataReady = true;
		}//end if
		else
		{
			dataReady = false;
		}//end else
	}//end else if
	else
	{
		//invalid RoverComm Type, so do nothing
		dataReady = false;
	}//end else

	 //Process data received data
	if (dataReady)
	{
		validData = roverComm->validateData();
	}
	else
	{
		validData = false;
	}

	return validData;



}

void dataDirector(RoverData * roverData)
{
	//Note: This function varies for different Arduinos

	byte roverCommType = roverData->getCommType();

	dataWasForCOMM = false;//reset the flag

	if (roverCommType == ROVERCOMM_COMM)
	{
		//if the data is for this unit, CMNC
		dataWasForCOMM = true;//set the flag that the data was for this unit, COMM
		//process it back in the main loop (to prevent software stack from being too deep)
		return;
	}//end if		
	else if (roverCommType == ROVERCOMM_CMNC)
	{
		//if the data is for CMNC, transmit the data out from COMM to CMNC
		txData(roverData->getData(), ROVERCOMM_CMNC);		
	}//end else if
	else if (roverCommType == ROVERCOMM_NAVI || roverCommType == ROVERCOMM_AUXI || roverCommType == ROVERCOMM_MAIN)
	{
		//if the data is for either NAVI, AUXI, or MAIN, transmit the data out from COMM to MAIN since COMM only can talk to MAIN and not NAVI or AUXI (and MAIN will process it accordingly or reroute it if needed)
		txData(roverData->getData(), ROVERCOMM_MAIN);
	}//end else if
	else//the command type is ROVERCOMM_NONE
	{
		//invalid RoverComm Type, so do nothing
	}//end else		
		
	return;
}

void txData(String txData, byte roverCommType)
{
	//Note: This function varies for different Arduinos

	if (roverCommType == ROVERCOMM_CMNC)
	{
		//transmit the data to CMNC or through the USB of this Arduino (i.e. for debug) [in this case, it means the same thing]
		Serial.println(txData);
	}//end if
	else if (roverCommType == ROVERCOMM_MAIN)
	{
		//transmit the data to MAIN
		swSerialMAIN.println(txData);
	}//end else if
	else
	{
		//do nothing
	}//end else
}

void commandDirector(char * roverCommand)
{
	//Note: This function varies for different Arduinos

	//This checks to see if the roverCommand matches any of the known values. Else it's an invalid command
	if (strcmp(roverCommand, "hi") == 0)
	{
		txData("Valid Cmd! =)", ROVERCOMM_CMNC);
		txData("Rx'd:", ROVERCOMM_CMNC);
		txData(roverCommand, ROVERCOMM_CMNC);
	}
	else if (strcmp(roverCommand, "bye") == 0)
	{
		txData("Valid Cmd! =)", ROVERCOMM_CMNC);
		txData("Rx'd:", ROVERCOMM_CMNC);
		txData(roverCommand, ROVERCOMM_CMNC);
	}
	else
	{
		txData("Invalid Cmd! =(", ROVERCOMM_CMNC);
		txData("Rx'd:", ROVERCOMM_CMNC);
		txData(roverCommand, ROVERCOMM_CMNC);
	}
}
