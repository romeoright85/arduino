//Used for MAIN - 3

//Note: The test cases varies for different Arduinos

//Note: Can send this (about max size) to test: "/-c4--*cmd2asdasdfasdfgsdfgsdfgsfdgd12321123123153452364564564^"


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
Debug data: /5c401*HelloCOMMtoMAIN
Also uncomment flag(s) in RoverComm.h to see the received string, etc.
*/


//Test case 3a:
/*
Send (i.e. with your keyboard and using a terminal window) over USB serial
/-c4--*hi
to test the command interface for this Arduino
*/

//Test case 3b:
/*
Send (i.e. with your keyboard and using a terminal window) over USB serial
/-c4--*bye
to test the command interface for this Arduino
*/





//Must define this before calling RoverConfig.h (either directly or through another header file)
#define _ARD_3_MAIN_H //define this flag to turn on MAIN definitions
#include <RoverData.h>
#include <RoverComm.h> //calls RoverConfig.h
#include <RoverCommand.h>
#include <SoftwareSerial.h>



//Global Variables
//RoverData pointers and RoverComms
//Ch1 is between MAIN and PC USB
RoverData * roverDataCh1_MAIN = new RoverData();
RoverComm * roverMain_Ch1 = new RoverComm(roverDataCh1_MAIN);
//Ch3 is between MAIN and COMM
RoverData * roverDataCh2_MAIN = new RoverData();
RoverComm * roverMain_Ch2 = new RoverComm(roverDataCh2_MAIN);
//Ch3 is between MAIN and NAVI
RoverData * roverDataCh3_MAIN = new RoverData();
RoverComm * roverMain_Ch3 = new RoverComm(roverDataCh3_MAIN);
//Ch4 is between MAIN and AUXI
RoverData * roverDataCh4_MAIN = new RoverData();
RoverComm * roverMain_Ch4 = new RoverComm(roverDataCh4_MAIN);



//Command Parser
RoverCommand * roverCommand = new RoverCommand();







//SW resettable variables
//flag for data for this Arduino
boolean dataWasForMAIN;
//flags for valid data ready
boolean ch1Valid;//for PC USB
boolean ch2Valid;//for COMM
boolean ch3Valid;//for NAVI
boolean ch4Valid;//for AUXI


RoverReset * resetArray[] = {
	roverDataCh1_MAIN,
	roverMain_Ch1,
	roverDataCh2_MAIN,
	roverMain_Ch2,
	roverDataCh3_MAIN,
	roverMain_Ch3,
	roverDataCh4_MAIN,
	roverMain_Ch4,
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
	dataWasForMAIN = false;
	ch1Valid = false;
	ch2Valid = false;
	ch3Valid = false;
	ch4Valid = false;


	//Setup the HW_UART
	Serial.begin(PC_USB_BAUD_RATE);
	Serial1.begin(COMM_BAUD_RATE);
	Serial2.begin(NAVI_BAUD_RATE);
	Serial3.begin(AUXI_BAUD_RATE);

	
}


void loop() {


	//reset flags
	ch1Valid = false;
	ch2Valid = false;
	ch3Valid = false;
	ch4Valid = false;



	//1. Receive and process data

	//1a. Receive data and process data from PC USB
	roverDataCh1_MAIN->clearData();//clear data before getting new data
	ch1Valid = rxData(roverMain_Ch1, ROVERCOMM_PC_USB);

	//1b. receive data and process data from COMM
	roverDataCh2_MAIN->clearData();//clear data before getting new data
	ch2Valid = rxData(roverMain_Ch2, ROVERCOMM_COMM);

	//1c. receive data and process data from NAVI
	roverDataCh3_MAIN->clearData();//clear data before getting new data
	ch3Valid = rxData(roverMain_Ch3, ROVERCOMM_NAVI);//Note: this is a local .ino function

	//1d. receive data and process data from AUXI
	roverDataCh4_MAIN->clearData();//clear data before getting new data
	ch4Valid = rxData(roverMain_Ch4, ROVERCOMM_AUXI);//Note: this is a local .ino function


	//Note: The debug code below varies for different Arduinos
	//DEBUG Code: Data Injection (from COMM to MAIN)	
	#ifdef _DEBUG_IMU_TEST_CASE_
		roverMain_Ch1->setRxData("!ANG:1.23,4.56,78.90", sizeof("!ANG:1.23,4.56,78.90"));
		ch1Valid = true;
	#endif
	#ifdef _DEBUG_ROVER_TEST_CASE_		
		roverMain_Ch1->setRxData("/5c401*HelloCOMMtoMAIN", sizeof("/5c401*HelloCOMMtoMAIN");
		ch1Valid = true;
	#endif



	//2. Transmit data and/or execute command

	//2a. For data from PC USB, transmit the data to it's proper destination if it was meant for another Arduino
	//		or take any actions if the data was meant for this unit, MAIN
	if (ch1Valid)
	{


		//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
		dataDirector(roverDataCh1_MAIN);//Note: this is a local .ino function


		//if the data was for this unit
		if (dataWasForMAIN)
		{

			//send the RoverData to the roverCommand's parser to get the command
			roverCommand->parseCommand(roverDataCh1_MAIN->getData(), roverDataCh1_MAIN->getDataLength());
			commandDirector(roverCommand->getCommand());
		}
	}
	else
	{
		//The data was invalid, so do nothing			
	}


	//2b. For data from COMM, transmit the data to it's proper destination if it was meant for another Arduino
	//		or take any actions if the data was meant for this unit, MAIN
	if (ch2Valid)
	{


		//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
		dataDirector(roverDataCh2_MAIN);//Note: this is a local .ino function


		//if the data was for this unit
		if (dataWasForMAIN)
		{

			//send the RoverData to the roverCommand's parser to get the command
			roverCommand->parseCommand(roverDataCh2_MAIN->getData(), roverDataCh2_MAIN->getDataLength());
			commandDirector(roverCommand->getCommand());
		}
	}
	else
	{
		//The data was invalid, so do nothing			
	}

	//2c. For data from NAVI, transmit the data to it's proper destination if it was meant for another Arduino
	//		or take any actions if the data was meant for this unit, MAIN
	if (ch3Valid)
	{

		//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
		dataDirector(roverDataCh3_MAIN);//Note: this is a local .ino function

		//4. Take any actions if the data was meant for this unit, MAIN
		if (dataWasForMAIN)
		{

			//send the RoverData to the roverCommand's parser to get the command
			roverCommand->parseCommand(roverDataCh3_MAIN->getData(), roverDataCh3_MAIN->getDataLength());
			commandDirector(roverCommand->getCommand());

		}
	}
	else
	{
		//The data was invalid, so do nothing
	}

	//2d. For data from NAVI, transmit the data to it's proper destination if it was meant for another Arduino
	//		or take any actions if the data was meant for this unit, MAIN
	if (ch4Valid)
	{

		//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
		dataDirector(roverDataCh4_MAIN);//Note: this is a local .ino function

		//4. Take any actions if the data was meant for this unit, MAIN
		if (dataWasForMAIN)
		{

			//send the RoverData to the roverCommand's parser to get the command
			roverCommand->parseCommand(roverDataCh4_MAIN->getData(), roverDataCh4_MAIN->getDataLength());
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



	if (roverCommType == ROVERCOMM_PC_USB)
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
	else if (roverCommType == ROVERCOMM_COMM)
	{

		if (Serial1.available() > 1)
		{
			//initialize the counter
			counter = 0;

			while (Serial1.available() > 0 && counter <= ROVER_COMM_SENTENCE_LENGTH)//while there is data on the Serial RX Buffer and the length is not over the max GPS sentence length
			{
				//Read one character of serial data at a time
				//Note: Must type cast the Serial.Read to a char since not saving it to a char type first
				roverComm->appendToRxData((char)Serial1.read());//construct the string one char at a time
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
	else if (roverCommType == ROVERCOMM_NAVI)
	{
		//initialize the counter
		counter = 0;

		if (Serial2.available() > 1)
		{
			while (Serial2.available() > 0 && counter <= ROVER_COMM_SENTENCE_LENGTH)//while there is data on the Serial RX Buffer and the length is not over the max GPS sentence length
			{
				//Read one character of serial data at a time
				//Note: Must type cast the Serial.Read to a char since not saving it to a char type first
				roverComm->appendToRxData((char)Serial2.read());//construct the string one char at a time
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
	else if (roverCommType == ROVERCOMM_AUXI)
	{
		if (Serial3.available() > 1)
		{
			//initialize the counter
			counter = 0;

			while (Serial3.available() > 0 && counter <= ROVER_COMM_SENTENCE_LENGTH)//while there is data on the Serial RX Buffer and the length is not over the max GPS sentence length
			{
				//Read one character of serial data at a time
				//Note: Must type cast the Serial.Read to a char since not saving it to a char type first
				roverComm->appendToRxData((char)Serial3.read());//construct the string one char at a time
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

	dataWasForMAIN = false;//reset the flag

	if (roverCommType == ROVERCOMM_MAIN)
	{
		//if the data is for this unit, MAIN
		dataWasForMAIN = true;//set the flag that the data was for this unit, MAIN
		//process it back in the main loop (to prevent software stack from being too deep)
		return;
	}//end if
	else if (roverCommType == ROVERCOMM_PC_USB)
	{
		//if the data is for the PC USB, transmit the data out from MAIN to PC USB
		txData(roverData->getData(), ROVERCOMM_PC_USB);
	}//end else if
	else if (roverCommType == ROVERCOMM_COMM)
	{
		//if the data is for COMM, transmit the data out from MAIN to COMM
		txData(roverData->getData(), ROVERCOMM_COMM);
	}//end else if
	else if (roverCommType == ROVERCOMM_NAVI)
	{
		//if the data is for CMNC, transmit the data out from MAIN to NAVI
		txData(roverData->getData(), ROVERCOMM_NAVI);
	}//end else if
	else if (roverCommType == ROVERCOMM_AUXI)
	{
		//if the data is for CMNC, transmit the data out from MAIN to AUXI
		txData(roverData->getData(), ROVERCOMM_AUXI);
	}//end else if
	else//the command type is ROVERCOMM_NONE
	{
		//invalid RoverComm Type, so do nothing
	}//end else		

	return;
}

void txData(char * txData, byte roverCommType)
{
	//Note: This function varies for different Arduinos

	if (roverCommType == ROVERCOMM_MAIN || roverCommType == ROVERCOMM_PC_USB)
	{
		//transmit the data through the USB of this Arduino (i.e. for debug)
		Serial.println(txData);
	}//end if
	else if (roverCommType == ROVERCOMM_COMM)
	{
		//transmit the data to COMM
		Serial1.println(txData);
		
	}//end if
	else if (roverCommType == ROVERCOMM_NAVI)
	{
		//transmit the data to NAVI
		Serial2.println(txData);
	}//end if
	else if (roverCommType == ROVERCOMM_AUXI)
	{
		//transmit the data to AUXI
		Serial3.println(txData);
	}//end if
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
		txData("Valid Cmd! =)", ROVERCOMM_MAIN);
		txData("Rx'd:", ROVERCOMM_MAIN);
		txData(roverCommand, ROVERCOMM_MAIN);
	}
	else if (strcmp(roverCommand, "bye") == 0)
	{
		txData("Valid Cmd! =)", ROVERCOMM_MAIN);
		txData("Rx'd:", ROVERCOMM_MAIN);
		txData(roverCommand, ROVERCOMM_MAIN);
	}
	else
	{
		txData("Invalid Cmd! =(", ROVERCOMM_MAIN);
		txData("Rx'd:", ROVERCOMM_MAIN);
		txData(roverCommand, ROVERCOMM_MAIN);
	}
}

