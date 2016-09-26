#include <WheelEncoderSensor.h>


WheelEncoderSensor::WheelEncoderSensor(byte pinEncoderA, byte pinEncoderB, byte motorSide, voidFuncPtr interruptDispatch)
{		
		//Assign values
		this->_pinEncoderA = pinEncoderA;
		this->_pinEncoderB = pinEncoderB;
		this->_motorSide = motorSide;
				
		pinMode(this->_pinEncoderA, INPUT);
		pinMode(this->_pinEncoderB, INPUT);
		
		//Setup the interrupt for Channel A
		byte interruptChannel = digitalPinToInterrupt(_pinEncoderA); //calling an arduino function
		attachInterrupt(interruptChannel, interruptDispatch, RISING); //calling an arduino function, attachInterrupt()
		
		//Initialize variables
		this->_motorDirection = MOTOR_STOPPED;
		this->_encoderAEdgeCount = 0;
		this->_mtrSpeed = 0;
		this->_encoderBLevel = LOW;
		this->_inchesTraveled = 0;
		
		
}
WheelEncoderSensor::~WheelEncoderSensor()
{
	//do nothing
}
void WheelEncoderSensor::reset()
{
	//reset variables
	this->_motorDirection = MOTOR_STOPPED;
	this->_encoderAEdgeCount = 0;
	this->_mtrSpeed = 0;
	this->_encoderBLevel = LOW;
	this->_inchesTraveled = 0;
		
}
void WheelEncoderSensor::calculateMotorParameters()
{
	unsigned long timeElapsed;//milliseconds elapsed
	
//LEFT OFF HERE	
//WRITE ME	
//calculate time elapsed and save it to timeElapsed
//need to maybe use delay timers and delay counters to automatically call calculateMotorParameters()
	//add delay timers and delay counters to the .ino file
	
	if(this->_prevEncoderAEdgeCount==this->_encoderAEdgeCount)//if the edge count has not changed, the motor is stopped
	{
		//Determine motor direction
		this->_motorDirection = MOTOR_STOPPED;
	}
	else
	{
			//Determine motor direction
			if(this->_chAIsLeadingChB)
			{
				if(this->_motorSide == RIGHT_MOUNTED_MOTOR)//and when the motor is on the right side and _chAIsLeadingChB == true, the motor is going forward
				{
					this->_motorDirection = MOTOR_FORWARD;			
				}		
				else//this->_motorSide == LEFT_MOUNTED_MOTOR
				//the motor is going in reverse
				{
					this->_motorDirection = MOTOR_REVERSE;
				}
			}
			else//this->_chAIsLeadingChB == false
			{
				if(this->_motorSide == RIGHT_MOUNTED_MOTOR)//and when the motor is on the right side and _chAIsLeadingChB == false, the motor is going in reverse
				{
					this->_motorDirection = MOTOR_REVERSE;			
				}		
				else//this->_motorSide == LEFT_MOUNTED_MOTOR
				//the motor is going forward
				{
					this->_motorDirection = MOTOR_FORWARD;
				}
			}
	}


	
	//distance traveled in inches
	this->_inchesTraveled = ((this->_encoderAEdgeCount - this->_prevEncoderAEdgeCount) / SINGLE_SIDED_EDGES_PER_REVOLUTION) * INCHES_PER_REVOLUTION;//the number of edges (the delta between last and current number of edges) divided by 12 edges per a wheel revolution * 15 inches per a revolution is the distance traveled in inches

	//calculate the motor speed	
	this->_mtrSpeed = this->_inchesTraveled/(timeElapsed/1000);// inches/seconds = inches / (msec/1000)	
		
	//set up the variables for the next time it's called
	this->_prevEncoderAEdgeCount=this->_encoderAEdgeCount;//set the previous count to the current count
	this->_encoderAEdgeCount = 0;//reset the current edge count
	
	
}
byte WheelEncoderSensor::getDirection()
{
	return this->_motorDirection;
}
int WheelEncoderSensor::getSpeed()
{
	return this->_mtrSpeed;
}
int WheelEncoderSensor::getFootage()
{	
	return this->_inchesTraveled / 12;
}
void WheelEncoderSensor::isrUpdate()//this will be called by an interruptDispatch
{
	//the isrUpdate() will be called when there is a rising edge on this->_pinEncoderA
	this->_encoderBLevel = digitalRead(this->_pinEncoderB);
	
	if(_encoderBLevel == LOW)//if _pinEncoderA has a rising edge and _pinEncoderB is LOW, channel A is leading channel B
	{
		_chAIsLeadingChB = true;
	}
	else//channel B is leading channel A
	{
		_chAIsLeadingChB = false;
	}
	this->_encoderAEdgeCount++;
}