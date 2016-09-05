//Note: If you write a reset, make sure you delete the object roverData_COMM pointer is pointing to before hand else you might get memory leaks

//Must define this before calling RoverConfig.h (either directly or through another header file)
#define _ARD_4_COMM_H //define this flag to turn on COMM definitions
#include <RoverData.h>
#include <RoverComm.h> //calls RoverConfig.h
#include <SoftwareSerial.h>





//Global Variables
RoverData * roverData_COMM;//RoverData pointer
RoverComm roverComm = RoverComm(ROVERCOMM_CMNC, roverData_COMM);
RoverReset * resetArray[] = { &roverComm };

//{ SW_UART Declarations
//{ MAIN SW_UART
SoftwareSerial swSerialMAIN(COMM_SW_UART_RX_PIN, COMM_SW_UART_TX_PIN); // RX, TX, Note declare this in global and not setup() else it won't work
																	   //} End of MAIN SW_UART
																	   //} End of SW_UART Declarations





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
	String dataForCOMM;//data destined for this unit (i.e. no reroute)

	//1. receive all data first

	//1a. receive data from CMNC (the PC)
	rxData_CMNC_2_COMM();

	//1b. receive data from MAIN
	rxData_MAIN_2_COMM();

	//2. process data
	roverComm.processReceivedData();
	//2a. process received data from CMNC (the PC)
	
		//2b. process received data from MAIN

		//3. Take any actions if the data was meant for the COMM
	//WRITE LATER: do whatever the command is asking you to

		delete roverData_COMM;//delete the object the pointer is pointing to after you're done with it
		roverData_COMM = NULL;//set the pointer to NULL after the object is deleted (not required but good practice)

		//4. then transmit all data

		//4a. transmit data to MAIN
		txData_COMM_2_MAIN();

	//4. transmit data to CMNC (the PC)
	txData_COMM_2_CMNC();

	delay(1000);//add some delay in between cycles

}


void rxData_CMNC_2_COMM() {
	if (Serial.available() > 1)
	{
		while (Serial.available() > 0)//while there is data on the Serial RX Buffer
		{
			//Read one character of serial data at a time
			//Note: Must type cast the Serial.Read to a char since not saving it to a char type first
			roverComm.appendToRxData((char)swSerialMAIN.read(), ROVERCOMM_COMM);//construct the string one char at a time
																				//DEBUG: Add as needed//delay(1);//add a 1 us delay between each transmission
		}//end while
	}//end if
}
void rxData_MAIN_2_COMM() {

}
void txData_COMM_2_MAIN() {

}
void txData_COMM_2_CMNC() {

}