//Note: The test cases varies for different Arduinos

//Note: Can send this (about max size) to test: "/-c3--*cmd2asdasdfasdfgsdfgsdfgsfdgd12321123123153452364564564^"


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
Debug data: /4c301*HelloMAINtoAUXI
Also uncomment flag(s) in RoverComm.h to see the received string, etc.
*/


//Test case 3a:
/*
Send (i.e. with your keyboard and using a terminal window) over USB serial
/-c3--*hi
to test the command interface for this Arduino
*/

//Test case 3b:
/*
Send (i.e. with your keyboard and using a terminal window) over USB serial
/-c3--*bye
to test the command interface for this Arduino
*/





//Must define this before calling RoverConfig.h (either directly or through another header file)
#define _ARD_2_AUXI_H //define this flag to turn on AUXI definitions
#include <RoverData.h>
#include <RoverComm.h> //calls RoverConfig.h
#include <RoverCommand.h>
#include <SoftwareSerial.h>



//Global Variables
//RoverData pointers and RoverComms
//Ch1 is between AUXI and PC USB
RoverData * roverDataCh1_AUXI = new RoverData();
RoverComm * roverAuxi_Ch1 = new RoverComm(roverDataCh1_AUXI);
//Ch3 is between AUXI and MAIN
RoverData * roverDataCh2_AUXI = new RoverData();
RoverComm * roverAuxi_Ch2 = new RoverComm(roverDataCh2_AUXI);



//Command Parser
RoverCommand * roverCommand = new RoverCommand();







//SW resettable variables
//flag for data for this Arduino
boolean dataWasForAUXI;
//flags for data ready
boolean dataReadyCh1;//for PC USB
boolean dataReadyCh2;//for MAIN



RoverReset * resetArray[] = {
	roverDataCh1_AUXI,
	roverAuxi_Ch1,
	roverDataCh2_AUXI,
	roverAuxi_Ch2,
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
	dataWasForAUXI = false;
	dataReadyCh1 = false;
	dataReadyCh2 = false;


	//Setup the HW_UART
	Serial.begin(PC_USB_BAUD_RATE);
	Serial2.begin(MAIN_BAUD_RATE);



}


void loop() {


	//reset flags
	dataReadyCh1 = false;
	dataReadyCh2 = false;



	//1. receive all data first

	//1a. receive data from PC USB
	roverDataCh1_AUXI->clearData();//clear data before getting new data
	dataReadyCh1 = rxData(roverAuxi_Ch1, ROVERCOMM_PC_USB);

	//1b. receive data from MAIN
	roverDataCh2_AUXI->clearData();//clear data before getting new data
	dataReadyCh2 = rxData(roverAuxi_Ch2, MAIN_BAUD_RATE);



	//Note: The debug code below varies for different Arduinos
	//DEBUG Code: Data Injection (from MAIN to AUXI)	
	#ifdef _DEBUG_IMU_TEST_CASE_
		roverAuxi_Ch1->setRxData("!ANG:1.23,4.56,78.90");
		dataReadyCh1 = true;
	#endif
	#ifdef _DEBUG_ROVER_TEST_CASE_		
		roverAuxi_Ch1->setRxData("/4c301*HelloMAINtoAUXI");
		dataReadyCh1 = true;
	#endif


	//2. process data	

	//2a. process received data from PC USB
	if (dataReadyCh1)
	{
		roverAuxi_Ch1->validateData();
	}

	//2b. process received data from MAIN
	if (dataReadyCh2)
	{
		roverAuxi_Ch2->validateData();
	}




	//3a. For data from PC USB, transmit the data to it's proper destination if it was meant for another Arduino
	//		or take any actions if the data was meant for this unit, AUXI
	if (roverAuxi_Ch1->isDataValid() && dataReadyCh1)
	{


		//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
		dataDirector(roverDataCh1_AUXI);//Note: this is a local .ino function


		//if the data was for this unit
		if (dataWasForAUXI)
		{

			//send the RoverData to the roverCommand's parser to get the command
			roverCommand->parseCommand(roverDataCh1_AUXI->getData());
			commandDirector(roverCommand->getCommand());
		}
	}
	else
	{
		//The data was invalid, so do nothing			
	}


	//3b. For data from MAIN, transmit the data to it's proper destination if it was meant for another Arduino
	//		or take any actions if the data was meant for this unit, AUXI
	if (roverAuxi_Ch2->isDataValid() && dataReadyCh2)
	{


		//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
		dataDirector(roverDataCh2_AUXI);//Note: this is a local .ino function


		//if the data was for this unit
		if (dataWasForAUXI)
		{

			//send the RoverData to the roverCommand's parser to get the command
			roverCommand->parseCommand(roverDataCh2_AUXI->getData());
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
	if (roverCommType == ROVERCOMM_PC_USB)
	{

		if (Serial.available() > 1)
		{
			while (Serial.available() > 0)//while there is data on the Serial RX Buffer
			{
				//Read one character of serial data at a time
				//Note: Must type cast the Serial.Read to a char since not saving it to a char type first
				roverComm->appendToRxData((char)Serial.read());//construct the string one char at a time
//DEBUG: Add as needed//delay(1);//add a 1 us delay between each transmission
			}//end while
			return true;
		}//end if
		else
		{
			return false;
		}//end else
	}//end if
	else if (roverCommType == ROVERCOMM_MAIN)
	{

		if (Serial2.available() > 1)
		{
			while (Serial2.available() > 0)//while there is data on the Serial RX Buffer
			{
				//Read one character of serial data at a time
				//Note: Must type cast the Serial.Read to a char since not saving it to a char type first
				roverComm->appendToRxData((char)Serial2.read());//construct the string one char at a time
//DEBUG: Add as needed//delay(1);//add a 1 us delay between each transmission
			}//end while
			return true;
		}//end if
		else
		{
			return false;
		}//end else
	}//end if	
	else
	{
		//invalid RoverComm Type, so do nothing
	}//end else





}

void dataDirector(RoverData * roverData)
{
	//Note: This function varies for different Arduinos

	byte roverCommType = roverData->getCommType();

	dataWasForAUXI = false;//reset the flag

	if (roverCommType == ROVERCOMM_AUXI)
	{
		//if the data is for this unit, AUXI
		dataWasForAUXI = true;//set the flag that the data was for this unit, AUXI
		//process it back in the main loop (to prevent software stack from being too deep)
		return;
	}//end if
	else if (roverCommType == ROVERCOMM_PC_USB)
	{
		//if the data is for the PC USB, transmit the data out from AUXI to PC USB
		txData(roverData->getData(), ROVERCOMM_PC_USB);
	}//end else if
	else if (roverCommType == ROVERCOMM_MAIN)
	{
		//if the data is for MAIN, transmit the data out from AUXI to MAIN
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

	if (roverCommType == ROVERCOMM_AUXI || roverCommType == ROVERCOMM_PC_USB)
	{
		//transmit the data through the USB of this Arduino (i.e. for debug)
		Serial.println(txData);
	}//end if
	else if (roverCommType == ROVERCOMM_MAIN)
	{
		//transmit the data to COMM
		Serial2.println(txData);

	}//end if	
	else
	{
		//do nothing
	}//end else
}

void commandDirector(String roverCommand)
{
	//Note: This function varies for different Arduinos

	//This checks to see if the roverCommand matches any of the known values. Else it's an invalid command
	if (roverCommand.equals("hi"))
	{
		txData(F("Valid Cmd! =)"), ROVERCOMM_AUXI);
		txData(F("Rx'd:"), ROVERCOMM_AUXI);
		txData(roverCommand, ROVERCOMM_AUXI);
	}
	else if (roverCommand.equals("bye"))
	{
		txData(F("Valid Cmd! =)"), ROVERCOMM_AUXI);
		txData(F("Rx'd:"), ROVERCOMM_AUXI);
		txData(roverCommand, ROVERCOMM_AUXI);
	}
	else
	{
		txData(F("Invalid Cmd! =("), ROVERCOMM_AUXI);
		txData(F("Rx'd:"), ROVERCOMM_AUXI);
		txData(roverCommand, ROVERCOMM_AUXI);



	}
}

