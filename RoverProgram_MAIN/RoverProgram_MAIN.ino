//Used for MAIN - 3
#include <RoverCaptain.h>


//Global Variables
void InterruptDispatch_sleeperMAIN();
void InterruptDispatch_wheelEncoder_MidLeft();
void InterruptDispatch_wheelEncoder_MidRight();
RoverCaptain * roverCaptain = new RoverCaptain(&InterruptDispatch_sleeperMAIN, &InterruptDispatch_wheelEncoder_MidLeft, &InterruptDispatch_wheelEncoder_MidRight);

void setup() {


	//Setup the HW_UART for communications between MAIN and COMM, MAIN and AUXI, MAIN and NAVI, and MAIN and PC USB
	Serial.begin(PC_USB_BAUD_RATE);
	Serial1.begin(COMM_BAUD_RATE);
	Serial2.begin(NAVI_BAUD_RATE);
	Serial3.begin(AUXI_BAUD_RATE);
	//Note: Can't do a reset here since objects aren't created yet until in the loop() code of the state machine.
}


void loop() {
	roverCaptain->run();
	delay(500);//DEBUG
}




void InterruptDispatch_sleeperMAIN() {
	//Have to keep the ISR short else the program won't work
	roverCaptain->isrUpdate_sleeperMAIN();//update the awake flag of the sleeperMAIN to reflect current status
}
void InterruptDispatch_wheelEncoder_MidLeft() {
	//Have to keep the ISR short else the program won't work
	roverCaptain->isrUpdate_wheelEncoder_MidLeft();
}

void InterruptDispatch_wheelEncoder_MidRight() {
	//Have to keep the ISR short else the program won't work
	roverCaptain->isrUpdate_wheelEncoder_MidRight();
}




