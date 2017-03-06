//Used for AUXI - 3


#include <RoverHeathAndStatus.h>


//Global Variables

void InterruptDispatch_sleeperAUXI();
RoverHeathAndStatus * roverHeathAndStatus = new RoverHeathAndStatus(&InterruptDispatch_sleeperAUXI);


void setup() {

	
	Serial.begin(PC_USB_BAUD_RATE);	
	Serial2.begin(MAIN_BAUD_RATE);//Use to talk between MAIN and AUXI	
	//Note: Can't do a reset here since objects aren't created yet until in the loop() code of the state machine.
	
}


void loop() {
	
	roverHeathAndStatus->run();
	delay(500);//DEBUG
}

void InterruptDispatch_sleeperAUXI() {
	//Have to keep the ISR short else the program won't work
	roverHeathAndStatus->isrUpdate_sleeperAUXI();//update the awake flag of the sleeperAUXI to reflect current status
}
