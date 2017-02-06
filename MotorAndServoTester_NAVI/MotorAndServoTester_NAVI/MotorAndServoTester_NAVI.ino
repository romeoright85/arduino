//Used for NAVI - 1

//Uncomment below to debug
//#define _DEBUG_START_IN_MANUAL_MODE

#include <RoverConfig.h>
#include <WheelEncoderSensor.h>
#include <GlobalDelayTimer.h>
#include <DelayCounter.h>
#include <BufferSelect.h>
#include <MotorController.h>
#include <GimbalController.h>
#include <RoverCalibration.h>

//Global Variables

#define SET_LEFT_TURN		45
#define SET_GO_STRAIGHT		90
#define SET_RIGHT_TURN		135	

#define SET_REV_HIGH_SPEED	180
#define SET_REV_LOW_SPEED	135
#define SET_STOP_SPEED		90
#define SET_FWD_LOW_SPEED	45
#define SET_FWD_HIGH_SPEED	0

#define SET_LEFT_PAN		45
#define SET_CENTER_PAN		90
#define SET_RIGHT_PAN		135

#define SET_DOWN_TILT		45
#define SET_MIDDLE_TILT		90
#define SET_UP_TILT			135

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


//void printMcAndGcOutputs();//print motor controller and gimbal controller outputs

void InterruptDispatch_wheelEncoder_FrontLeft();
void InterruptDispatch_wheelEncoder_FrontRight();
void InterruptDispatch_wheelEncoder_RearLeft();
void InterruptDispatch_wheelEncoder_RearRight();

//Note: Remember to update all fields of the constructor. All the fields are unique to/distinct for each motor. You can't share the counter, because it gets reset for each one. And each timer get's only one counter, so you need a timer for each one as well.
WheelEncoderSensor * wheelEncoder_FrontLeft = new WheelEncoderSensor(ENCODER_A_FRONT_LEFT, ENCODER_B_FRONT_LEFT, LEFT_MOUNTED, &InterruptDispatch_wheelEncoder_FrontLeft, frontLeftSyncCounter);
WheelEncoderSensor * wheelEncoder_FrontRight = new WheelEncoderSensor(ENCODER_A_FRONT_RIGHT, ENCODER_B_FRONT_RIGHT, RIGHT_MOUNTED, &InterruptDispatch_wheelEncoder_FrontRight, frontRightSyncCounter);
WheelEncoderSensor * wheelEncoder_RearLeft = new WheelEncoderSensor(ENCODER_A_REAR_LEFT, ENCODER_B_REAR_LEFT, LEFT_MOUNTED, &InterruptDispatch_wheelEncoder_RearLeft, rearLeftSyncCounter);
WheelEncoderSensor * wheelEncoder_RearRight = new WheelEncoderSensor(ENCODER_A_REAR_RIGHT, ENCODER_B_REAR_RIGHT, RIGHT_MOUNTED, &InterruptDispatch_wheelEncoder_RearRight, rearRightSyncCounter);




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
	
};


void setup() {
	//resetting all objects
	for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
	{
		resetArray[i]->reset();
	}
	Serial.begin(9600);

	//Instantiate the gimbal servos and motor controller
	gimbalSetPins(SERVO_PAN_PIN, SERVO_TILT_PIN);
	motorControllerSetPins(MTR_RC_CTRL_STEERING_PIN, MTR_RC_CTRL_THROTTLE_PIN);

	//Reset the gimbal and motor controller
	gimbalReset();	
	motorControllerReset();
	

	#ifdef _DEBUG_START_IN_MANUAL_MODE //good for testing if the motor controller mode needs to be reprogrammed
		Serial.println(F("SWITCHING TO MANUAL DRIVE"));//DEBUG
		roverBuffer->driverMode(MANUAL_DRIVE);//DEBUG
	#else //default is auto mode
		Serial.println(F("SWITCHING TO AUTO DRIVE"));
		roverBuffer->driverMode(AUTO_DRIVE);
	#endif
	

	//Run motor controller calibration
	motorControllerPowerOnCalibration(roverBuffer);//calibrate if buffer select is in auto mode, else do nothing
	
	delay(1000);

	//Run Gimbal Functional Demo
	gimbalFunctionalDemo();
	
	
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
	

	char rxData;

	if (Serial.available() > 0)
	{
		rxData = Serial.read();//Get data from the computer
		delay(1);

		switch (rxData)
		{
			case '1'://Reset
				Serial.println(F("RESET"));
				motorControllerSetSteering(SET_GO_STRAIGHT);
				motorControllerSetThrottle(SET_STOP_SPEED);
				gimbalSetPan(SET_CENTER_PAN);
				gimbalSetTilt(SET_MIDDLE_TILT);
				break;
			case '2'://Set to manual drive
				Serial.println(F("SWITCHING TO MANUAL DRIVE"));
				roverBuffer->driverMode(MANUAL_DRIVE);			
				break;
			case '3'://Set to auto drive
				Serial.println(F("SWITCHING TO AUTO DRIVE"));
				roverBuffer->driverMode(AUTO_DRIVE);
				break;		
			case 'd'://steer right			
				Serial.println(F("STEER RIGHT"));
				motorControllerSetSteering(SET_RIGHT_TURN);
				motorControllerSetThrottle(SET_FWD_LOW_SPEED);			
				break;
			case 'w'://go forward straight
				Serial.println(F("FORWARD STRAIGHT"));
				motorControllerSetSteering(SET_GO_STRAIGHT);
				motorControllerSetThrottle(SET_FWD_HIGH_SPEED);
				break;
			case 's'://stop motors
				Serial.println(F("STOP MOTORS"));
				motorControllerSetSteering(SET_GO_STRAIGHT);
				motorControllerSetThrottle(SET_STOP_SPEED);
				break;
			case 'x'://go backwards straight
				Serial.println(F("BACKWARDS STRAIGHT"));
				motorControllerSetSteering(SET_GO_STRAIGHT);
				motorControllerSetThrottle(SET_REV_HIGH_SPEED);
				break;
			case 'a'://steer left				 
				Serial.println(F("STEER LEFT"));
				motorControllerSetSteering(SET_LEFT_TURN);
				motorControllerSetThrottle(SET_FWD_LOW_SPEED);			
				break;
			case 'k'://pan left				 
				Serial.println(F("PAN LEFT"));
				gimbalSetPan(SET_LEFT_PAN);
				break;			
			case 'l'://pan center
				Serial.println(F("PAN CENTER"));
				gimbalSetPan(SET_CENTER_PAN);			
				break;
			case ';'://pan right			
				Serial.println(F("PAN RIGHT"));
				gimbalSetPan(SET_RIGHT_PAN);
				break;
			case 'u'://tilt up
				Serial.println(F("TILT UP"));
				gimbalSetTilt(SET_UP_TILT);
				break;
			case 'j'://tilt middle
				Serial.println(F("TILT MIDDLE"));
				gimbalSetTilt(SET_MIDDLE_TILT);
				break;
			case 'm'://tilt down
				Serial.println(F("TILT DOWN"));
				gimbalSetTilt(SET_DOWN_TILT);
				break;			
			default:
				break;
		}//end switch
	}//end if

	printMcAndGcOutputs();
	delay(500);

	
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


	delay(500);

}//end loop()





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
	Serial.println(motorControllerGetSteeringSet());
	Serial.print(F("Throttle: "));
	Serial.println(motorControllerGetThrottleSet());
	Serial.print(F("Pan: "));
	Serial.println(gimbalGetPanSet());
	Serial.print(F("Tilt: "));
	Serial.println(gimbalGetTiltSet());

}


void getDriveMode()//based on the buffer select
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
}
