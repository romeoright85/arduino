#include <RoverState.h>
#include <PowerOnResetState.h>
#include <ShutdownState.h>
#include <ObstacleDetectedState.h>
#include <DoSomething.h>



//Global Variables




RoverState * roverCurrentState;
RoverState * powerOnResetState = new PowerOnResetState();
DoSomething * doSomething = new DoSomething();
RoverState * obstacleDetectedState = new ObstacleDetectedState(doSomething);
RoverState * shutdownState = new ShutdownState();



RoverReset * resetArray[] = {
	
};
RoverState * roverStates[3];




void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}

	Serial.begin(PC_USB_BAUD_RATE);


	//Note: Make sure to update the size of the roverStates array.
	//Assign/Register all states in the roverStates Array
	roverStates[POWER_ON_RESET_STATE] = powerOnResetState;
	roverStates[OBSTACLE_DETECTED_STATE] = obstacleDetectedState;
	roverStates[SHUTDOWN_STATE] = shutdownState;
	

	roverCurrentState = roverStates[POWER_ON_RESET_STATE];//assign the current state
}


void loop() {
	Serial.println(F("Loop"));
	roverCurrentState->process();
	roverCurrentState = roverCurrentState->nextState(roverStates);
	delay(100);
}
