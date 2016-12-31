//Used for NAVI - 1

#include <RoverConfig.h>
#include <WheelEncoderSensor.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>
#include <BufferSelect.h>
#include <MotorPowerControl.h>
#include <MotorController.h>
#include <GimbalController.h>
#include <RoverCalibration.h>

//Global Variables


//counter delays
//using a counter to create delays while still allowing the loop() to run (i.e. for messages, etc.)
unsigned int outputMessageDelay = 0;
unsigned int modesToggleDelay = 0;


//A counter use to increment through the different modes
byte modesTester = 0;

MotorPowerControl * roverMtrPowerCtrl = new MotorPowerControl(MTR_FET_CTRL_PIN, MTR_ENABLE_STATUS);

BufferSelect * roverBuffer = new BufferSelect(BUFFER_SELECT_PIN);

//The WheelEncoder will wait for 1sec (1000 periods * 1mS) between each wheel encoder calculation
DelayCounter * frontLeftSyncCounter = new DelayCounter(DELAY_200_PERIODS);//initialize it to count to 1 periods x 1ms delay timer resolution = 1ms before the count has reached flag goes true
GlobalDelayTimer * frontLeftSyncTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, frontLeftSyncCounter);//everytime the delay interval (resolution) is reached, it will increment the delay counter. The standard resolution used for the Rover has been 5mS so it's not too small where it has to increment the counter often, but not to big where it won't work for many different classes without being too slow or fast

DelayCounter * frontRightSyncCounter = new DelayCounter(DELAY_200_PERIODS);//initialize it to count to 1 periods x 1ms delay timer resolution = 1ms before the count has reached flag goes true
GlobalDelayTimer * frontRightSyncTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, frontRightSyncCounter);//everytime the delay interval (resolution) is reached, it will increment the delay counter. The standard resolution used for the Rover has been 5mS so it's not too small where it has to increment the counter often, but not to big where it won't work for many different classes without being too slow or fast

DelayCounter * rearLeftSyncCounter = new DelayCounter(DELAY_200_PERIODS);//initialize it to count to 1 periods x 1ms delay timer resolution = 1ms before the count has reached flag goes true
GlobalDelayTimer * rearLeftSyncTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, rearLeftSyncCounter);//everytime the delay interval (resolution) is reached, it will increment the delay counter. The standard resolution used for the Rover has been 5mS so it's not too small where it has to increment the counter often, but not to big where it won't work for many different classes without being too slow or fast

DelayCounter * rearRightSyncCounter = new DelayCounter(DELAY_200_PERIODS);//initialize it to count to 1 periods x 1ms delay timer resolution = 1ms before the count has reached flag goes true
GlobalDelayTimer * rearRightSyncTimer = new GlobalDelayTimer(DELAY_TIMER_RES_5ms, rearRightSyncCounter);//everytime the delay interval (resolution) is reached, it will increment the delay counter. The standard resolution used for the Rover has been 5mS so it's not too small where it has to increment the counter often, but not to big where it won't work for many different classes without being too slow or fast


void printMcAndGcOutputs();//print motor controller and gimbal controller outputs

void InterruptDispatch_wheelEncoder_FrontLeft();
void InterruptDispatch_wheelEncoder_FrontRight();
void InterruptDispatch_wheelEncoder_RearLeft();
void InterruptDispatch_wheelEncoder_RearRight();

//Note: Remember to update all fields of the constructor. All the fields are unique to/distinct for each motor. You can't share the counter, because it gets reset for each one. And each timer get's only one counter, so you need a timer for each one as well.
WheelEncoderSensor * wheelEncoder_FrontLeft = new WheelEncoderSensor(ENCODER_A_FRONT_LEFT, ENCODER_B_FRONT_LEFT, LEFT_MOUNTED, &InterruptDispatch_wheelEncoder_FrontLeft, frontLeftSyncCounter);
WheelEncoderSensor * wheelEncoder_FrontRight = new WheelEncoderSensor(ENCODER_A_FRONT_RIGHT, ENCODER_B_FRONT_RIGHT, RIGHT_MOUNTED, &InterruptDispatch_wheelEncoder_FrontRight, frontRightSyncCounter);
WheelEncoderSensor * wheelEncoder_RearLeft = new WheelEncoderSensor(ENCODER_A_REAR_LEFT, ENCODER_B_REAR_LEFT, LEFT_MOUNTED, &InterruptDispatch_wheelEncoder_RearLeft, rearLeftSyncCounter);
WheelEncoderSensor * wheelEncoder_RearRight = new WheelEncoderSensor(ENCODER_A_REAR_RIGHT, ENCODER_B_REAR_RIGHT, RIGHT_MOUNTED, &InterruptDispatch_wheelEncoder_RearRight, rearRightSyncCounter);


MotorController * roverMotorController = new MotorController(MTR_RC_CTRL_STEERING_PIN, MTR_RC_CTRL_THROTTLE_PIN);
GimbalController * roverGimbalController = new GimbalController(SERVO_PAN_PIN, SERVO_TILT_PIN);




RoverReset * resetArray[] = {
	frontLeftSyncCounter,
	frontLeftSyncTimer,
	frontRightSyncCounter,
	frontRightSyncTimer,
	rearLeftSyncCounter,
	rearLeftSyncTimer,
	rearRightSyncCounter,
	rearRightSyncTimer,
	wheelEncoder_FrontLeft,
	wheelEncoder_FrontRight,
	wheelEncoder_RearLeft,
	wheelEncoder_RearRight,
	roverBuffer,
	roverMotorController,
	roverGimbalController,
	roverMtrPowerCtrl
};


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	Serial.begin(9600);
}


void loop() {

	//Tasks always running in the background with every loop() cycle
	//Timers
	frontLeftSyncTimer->Running();
	frontRightSyncTimer->Running();
	rearLeftSyncTimer->Running();
	rearRightSyncTimer->Running();
	//Wheel Encoders
	wheelEncoder_FrontLeft->sensorOnline();
	wheelEncoder_FrontRight->sensorOnline();
	wheelEncoder_RearLeft->sensorOnline();
	wheelEncoder_RearRight->sensorOnline();
	//Counter Delays
	//increment the counters
	outputMessageDelay++;
	modesToggleDelay++;


	//Motor Power Control
	if (modesToggleDelay >= 40000)//about once every second
	{


		//Detect drive mode
		if (roverBuffer->inAutoMode())
		{
			Serial.println(F("IN AUTO DRIVE"));
		}
		else
		{
			Serial.println(F("IN MANUAL DRIVE"));
		}
		

		switch (modesTester)
		{

			case 0:
				Serial.println(F("TURN MTR ON"));
				roverMtrPowerCtrl->setMotorPower(MTR_ON);
				//Set to auto drive
				Serial.println(F("SWITCHING TO AUTO DRIVE"));
				roverBuffer->driverMode(AUTO_DRIVE);
				break;
			case 1:
				//Set to stop/center uncalibrated values: 90
				roverMotorController->setSteering(90);
				roverMotorController->setThrottle(90);
				roverGimbalController->setPan(90);
				roverGimbalController->setTilt(90);
				//Print out the currently set values
				printMcAndGcOutputs();

				//Set next state
				modesTester++;
				break;
			case 2:
				//Set to arbitrary values: 75
				roverMotorController->setSteering(75);
				roverMotorController->setThrottle(75);

				//Print out the currently set values
				printMcAndGcOutputs();

				//Set next state
				modesTester++;
				break;
			case 3:
				//Set to arbitrary values: 100
				roverMotorController->setSteering(100);
				roverMotorController->setThrottle(100);

				//Print out the currently set values
				printMcAndGcOutputs();
				
				//Set next state
				modesTester++;
				break;
			case 4:
				//Set to arbitrary out of range values: 200
				roverMotorController->setSteering(200);
				roverMotorController->setThrottle(200);

				//Print out the currently set values
				printMcAndGcOutputs();

				//Set next state				
				modesTester++;
				break;
			case 5:
				//Set to arbitrary out of range values: -100
				roverMotorController->setSteering(-100);
				roverMotorController->setThrottle(-100);

				//Print out the currently set values
				printMcAndGcOutputs();

				//Set next state
				modesTester++;
				break;
			case 6:
				//Set to auto drive
				Serial.println(F("SWITCHING TO MANUAL DRIVE"));
				roverBuffer->driverMode(MANUAL_DRIVE);				
				//Set next state
				modesTester++;
				break;
			case 7:
				//Set to auto drive
				Serial.println(F("SWITCHING TO MANUAL DRIVE"));
				roverBuffer->driverMode(MANUAL_DRIVE);
				//Set next state
				modesTester++;
				Serial.println(F("TURN MTR ON"));
				roverMtrPowerCtrl->setMotorPower(MTR_OFF);
				break;
			default:
				//Set initial state, when it gets an undefined state or when modesTester++ has went past the max defined states
				modesTester = 0;
				break;
		}//end switch 
		
		modesToggleDelay = 0;//reset the counter

	}//end if



	if (outputMessageDelay >= 40000)//about once a second
	{



		//Print Buffer Select Status
		Serial.println(F("=BUFFER STATUS="));
		if (roverBuffer->inAutoMode())//currently in auto mode
		{
			Serial.println(F("AUTO MODE"));
		}
		else//currently in manual mode
		{

			Serial.println(F("MANUAL MODE"));
		}
		Serial.println();




		//Wheel Encoder Control and Status
		//========Front Left Motor===========
		byte direction_FrontLeft = wheelEncoder_FrontLeft->getDirection();
		Serial.println(F("=FRONT LEFT MTR="));
		Serial.print(F("Dir: "));
		if (direction_FrontLeft == MOTOR_FORWARD)//forward, reverse, stopped
		{
			Serial.println(F("Fwd"));
		}
		else if (direction_FrontLeft == MOTOR_REVERSE)
		{
			Serial.println(F("Rev"));
		}
		else//MOTOR_STOPPED
		{
			Serial.println(F("Stopped"));
		}
		Serial.print(F("Dist: "));//in inches
		Serial.println(wheelEncoder_FrontLeft->getFootage());//distance traveled in feet
		Serial.print(F("Spd: "));//in inches per second
		Serial.println(wheelEncoder_FrontLeft->getSpeed());//in inches per second


														   //========Front Right Motor===========
		byte direction_FrontRight = wheelEncoder_FrontRight->getDirection();
		Serial.println(F("=FRONT RIGHT MTR="));
		Serial.print(F("Dir: "));
		if (direction_FrontRight == MOTOR_FORWARD)//forward, reverse, stopped
		{
			Serial.println(F("Fwd"));
		}
		else if (direction_FrontRight == MOTOR_REVERSE)
		{
			Serial.println(F("Rev"));
		}
		else//MOTOR_STOPPED
		{
			Serial.println(F("Stopped"));
		}
		Serial.print(F("Dist: "));//in inches
		Serial.println(wheelEncoder_FrontRight->getFootage());//distance traveled in feet
		Serial.print(F("Spd: "));//in inches per second
		Serial.println(wheelEncoder_FrontRight->getSpeed());//in inches per second


															//========Rear Left Motor===========
		byte direction_RearLeft = wheelEncoder_RearLeft->getDirection();
		Serial.println(F("=REAR LEFT MTR="));
		Serial.print(F("Dir: "));
		if (direction_RearLeft == MOTOR_FORWARD)//forward, reverse, stopped
		{
			Serial.println(F("Fwd"));
		}
		else if (direction_RearLeft == MOTOR_REVERSE)
		{
			Serial.println(F("Rev"));
		}
		else//MOTOR_STOPPED
		{
			Serial.println(F("Stopped"));
		}
		Serial.print(F("Dist: "));//in inches
		Serial.println(wheelEncoder_RearLeft->getFootage());//distance traveled in feet
		Serial.print(F("Spd: "));//in inches per second
		Serial.println(wheelEncoder_RearLeft->getSpeed());//in inches per second

														  //========Rear Right Motor===========
		byte direction_RearRight = wheelEncoder_RearRight->getDirection();
		Serial.println(F("=REAR RIGHT MTR="));
		Serial.print(F("Dir: "));
		if (direction_RearRight == MOTOR_FORWARD)//forward, reverse, stopped
		{
			Serial.println(F("Fwd"));
		}
		else if (direction_RearRight == MOTOR_REVERSE)
		{
			Serial.println(F("Rev"));
		}
		else//MOTOR_STOPPED
		{
			Serial.println(F("Stopped"));
		}
		Serial.print(F("Dist: "));//in inches
		Serial.println(wheelEncoder_RearRight->getFootage());//distance traveled in feet
		Serial.print(F("Spd: "));//in inches per second
		Serial.println(wheelEncoder_RearRight->getSpeed());//in inches per second




		Serial.println();




		outputMessageDelay = 0;//reset the counter
	}





}





void InterruptDispatch_wheelEncoder_FrontLeft() {
	wheelEncoder_FrontLeft->isrUpdate();
}
void InterruptDispatch_wheelEncoder_FrontRight() {
	wheelEncoder_FrontRight->isrUpdate();
}
void InterruptDispatch_wheelEncoder_RearLeft() {
	wheelEncoder_RearLeft->isrUpdate();
}
void InterruptDispatch_wheelEncoder_RearRight() {
	wheelEncoder_RearRight->isrUpdate();
}


void printMcAndGcOutputs() {

	Serial.print(F("Steering: "));
	Serial.println(roverMotorController->getSteeringSet());
	Serial.print(F("Throttle: "));
	Serial.println(roverMotorController->getThrottleSet());
	Serial.print(F("Pan: "));
	Serial.println(roverGimbalController->getPanSet());
	Serial.print(F("Tilt: "));
	Serial.println(roverGimbalController->getTiltSet());

}