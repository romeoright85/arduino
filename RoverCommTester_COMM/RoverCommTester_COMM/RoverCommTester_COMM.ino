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
boolean dataWasForCOMM = false;
RoverReset * resetArray[] = { roverDataCh1_COMM, roverComm_Ch1, roverDataCh2_COMM, roverComm_Ch2, roverCommand };//for pointers, pass them directly, for objects pass the address



void setup() {
	//resetting all objects in this sketch
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		if (!resetArray[i] == NULL)//if the object isn't null
		{
			resetArray[i]->reset();//reset the object	
		}

	}


	//Setup the HW_UART
	Serial.begin(CMNC_BAUD_RATE);

	//Setup the SW_UART
	swSerialMAIN.begin(MAIN_BAUD_RATE);
}


void loop() {
	

	//1. receive all data first

		//1a. receive data from CMNC (the PC)
		rxData(roverComm_Ch1);

		//1b. receive data from MAIN
		rxData(roverComm_Ch2);

	//2. process data	
	
		//2a. process received data from CMNC (the PC)
		roverComm_Ch1->validateData();//validate, parse the data

		//2b. process received data from MAIN
		roverComm_Ch2->validateData();

		if(roverComm_Ch1->isDataValid())
		{
						
			//3. then transmit the data if it was meant for CMNC (the PC) or MAIN
			dataDirector(roverDataCh1_COMM);//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action
			
			//4. Take any actions if the data was meant for this unit, COMM
			if (dataWasForCOMM)
			{
				dataWasForCOMM = false;//reset the flag
				//send the RoverData to the roverCommand's parser to get the command
				roverCommand->parseCommand(roverDataCh1_COMM->getData());
				commandDirector(roverCommand->getCommand());
			}
		}
		
		
		if (roverComm_Ch2->isDataValid())
		{

			//3. then transmit the data if it was meant for CMNC (the PC) or MAIN
			dataDirector(roverDataCh2_COMM);//if the data is valid, send it to the dataDirector where it will be routed to the corresponding action

											//4. Take any actions if the data was meant for this unit, COMM
			if (dataWasForCOMM)
			{
				dataWasForCOMM = false;//reset the flag
									   //send the RoverData to the roverCommand's parser to get the command
				roverCommand->parseCommand(roverDataCh2_COMM->getData());
				commandDirector(roverCommand->getCommand());
			}
		}
		
	delay(1000);//add some delay in between cycles

}


void rxData(RoverComm * roverComm) {
	if (Serial.available() > 1)
	{
		while (Serial.available() > 0)//while there is data on the Serial RX Buffer
		{
			//Read one character of serial data at a time
			//Note: Must type cast the Serial.Read to a char since not saving it to a char type first
			roverComm->appendToRxData((char)swSerialMAIN.read());//construct the string one char at a time
			//DEBUG: Add as needed//delay(1);//add a 1 us delay between each transmission
		}//end while
	}//end if
}

void dataDirector(RoverData * roverData)
{
	byte roverCommType = roverData->getCommType();

	if (roverCommType == ROVERCOMM_COMM)
	{
		//if the data is for this unit, CMNC
		dataWasForCOMM = true;//set the flag that the data was for this unit, COMM
	}//end if
	else if (roverCommType == ROVERCOMM_CMNC)
	{
		//if the data is for CMNC data, transmit the data out from COMM to CMNC
		txData(roverData->getData(), ROVERCOMM_CMNC);
	}//end else if
	else if(roverCommType == ROVERCOMM_NAVI || roverCommType == ROVERCOMM_AUXI || roverCommType == ROVERCOMM_MAIN)
	{
		//if the data is for either NAVI, AUXI, or MAIN, transmit the data out from COMM to MAIN since COMM only can talk to MAIN and not NAVI or AUXI (and MAIN will process it accordingly or reroute it if needed)
		txData(roverData->getData(), ROVERCOMM_MAIN);
	}//end else if
	else//the command type is ROVERCOMM_NONE
	{
		//invalid RoverComm Type, so do nothing
	}//end else		
}

void txData(String txData, byte roverCommType)
{
	if (roverCommType == ROVERCOMM_CMNC)
	{
		//transmit the data to CMNC
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

void commandDirector(String roverCommand)
{
	if (roverCommand.equals("cmd0"))
	{
		Serial.println("CMD 0");
	}
	else if (roverCommand.equals("cmd1"))
	{
		Serial.println("CMD 1");
	}
	else
	{
		//do nothing, invalid command
	}	
}
