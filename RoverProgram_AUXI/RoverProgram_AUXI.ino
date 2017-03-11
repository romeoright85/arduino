//Used for AUXI - 3


#include <RoverHealthAndStatus.h>


//Global Variables

void InterruptDispatch_sleeperAUXI();
RoverHealthAndStatus * roverHealthAndStatus = new RoverHealthAndStatus(&InterruptDispatch_sleeperAUXI);


void setup() {

	
	Serial.begin(PC_USB_BAUD_RATE);	
	Serial2.begin(MAIN_BAUD_RATE);//Use to talk between MAIN and AUXI	
	//Note: Can't do a reset here since objects aren't created yet until in the loop() code of the state machine.
	
}


void loop() {
	
	roverHealthAndStatus->run();
	delay(500);//DEBUG
}

void InterruptDispatch_sleeperAUXI() {
	//Have to keep the ISR short else the program won't work
	roverHealthAndStatus->isrUpdate_sleeperAUXI();//update the awake flag of the sleeperAUXI to reflect current status
}
