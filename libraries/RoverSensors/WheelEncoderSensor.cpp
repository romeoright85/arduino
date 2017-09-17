#include <WheelEncoderSensor.h>


WheelEncoderSensor::WheelEncoderSensor(byte pinEncoderA, byte pinEncoderB, byte motorSide, voidFuncPtr interruptDispatch, DelayCounter * counterPtr)
{		
		//Assign values
		this->_pinEncoderA = pinEncoderA;
		this->_pinEncoderB = pinEncoderB;
		this->_motorSide = motorSide;
		this->_counterPtr = counterPtr;//take the passed counter pointer in the constructor argument and save it to the object member counter pointer				
				
				
		pinMode(this->_pinEncoderA, INPUT);
		pinMode(this->_pinEncoderB, INPUT);
		
		//Setup the interrupt for Channel A
		byte interruptChannel = digitalPinToInterrupt(_pinEncoderA); //calling an arduino function
		attachInterrupt(interruptChannel, interruptDispatch, RISING); //calling an arduino function, attachInterrupt()
		
		//Initialize variables
		this->_counterPtr->reset();
		this->_motorDirection = MOTOR_STOPPED;
		this->_inchesTraveledWithinLastSecond = 0;
		this->_totalInchesTraveled = 0;
		this->_mtrSpeed = 0;	
		this->_encoderAEdgeCount = 0;
		this->_encoderBLevel = LOW;
		this->_chAIsLeadingChB = false;
		
		
}
WheelEncoderSensor::~WheelEncoderSensor()
{
	//do nothing
}

void WheelEncoderSensor::reset()
{
	

	//reset variables
	this->_counterPtr->reset();
	this->_motorDirection = MOTOR_STOPPED;
	this->_inchesTraveledWithinLastSecond = 0;
	this->_totalInchesTraveled = 0;
	this->_mtrSpeed = 0;	
	this->_encoderAEdgeCount = 0;
	this->_encoderBLevel = LOW;
	this->_chAIsLeadingChB = false;
}

void WheelEncoderSensor::sensorOnline()
{
	//This function is to calculation the motor/wheel encoder parameters like speed, distance, and direction
	//this function is called with every pass in the loop(). But calculations are only performed after the counter/timer counts to 1 second. This is to free up the Arduino to do other tasks.
	//The edge counter is still counting in the background using interrupts. Just the calculations are only performed once a second.
	//Motors are slow, and there is only 12 edges per a revolution, so a 1Hz refresh rate is okay.
	
	

	#ifdef _DEBUG_SIMULATED_ENCODER_COUNT_
		this->_encoderAEdgeCount=this->_encoderAEdgeCount+random(0,100);
	#endif

	if (this->_counterPtr->countReached())//waits for the delay to finish counting to 1 second (determined the by delay periods * delayInterval/resolution)
	{
		//calculate the motor's speed, distance, and direction
		if(this->_encoderAEdgeCount==0)//if the edge count is still at zero (from the last reset), the motor is stopped
		{
			//Determine motor direction
			this->_motorDirection = MOTOR_STOPPED;
			
			//since the edge counts is 0, both _inchesTraveledWithinLastSecond and _mtrSpeed are 0.  And _totalInchesTraveled has not changed.
			//distance traveled since the last second
			this->_inchesTraveledWithinLastSecond = 0;

			//calculate the motor speed in inches per second
			this->_mtrSpeed = 0;
			
			//calculate total inches traveled
			this->_totalInchesTraveled = this->_totalInchesTraveled;//no change
		}
		else//the motors are moving
		{
				//Determine motor direction
				if(this->_chAIsLeadingChB)
				{
					if(this->_motorSide == LEFT_MOUNTED)//and when the motor is on the left side and _chAIsLeadingChB == true, the motor is going forward
					{
						this->_motorDirection = MOTOR_FORWARD;			
					}		
					else//this->_motorSide == RIGHT_MOUNTED
					//the motor is going in reverse
					{
						this->_motorDirection = MOTOR_REVERSE;
					}
				}
				else//this->_chAIsLeadingChB == false
				{
					if(this->_motorSide == LEFT_MOUNTED)//and when the motor is on the left side and _chAIsLeadingChB == false, the motor is going in reverse
					{
						this->_motorDirection = MOTOR_REVERSE;			
					}		
					else//this->_motorSide == RIGHT_MOUNTED
					//the motor is going forward
					{
						this->_motorDirection = MOTOR_FORWARD;
					}
				}
				
				//distance traveled since the last second
				this->_inchesTraveledWithinLastSecond = ( (this->_encoderAEdgeCount) / SINGLE_SIDED_EDGES_PER_REVOLUTION) * INCHES_PER_REVOLUTION;//the number of edges divided by 12 edges per a wheel revolution * 15 inches per a revolution equals the distance traveled in inches

				//calculate the motor speed in inches per second
				this->_mtrSpeed = this->_inchesTraveledWithinLastSecond;// inches/1 second (but since this function is already set to refresh every second so no need to divide)
				
				//calculate total inches traveled
				this->_totalInchesTraveled = this->_totalInchesTraveled + this->_inchesTraveledWithinLastSecond;//add to the inches accumulator
				
		}

		this->_encoderAEdgeCount = 0;//reset the current edge count		
		this->_counterPtr->counterReset();//reset the counter to start the count over again			
		
	}//end if for count reached

	
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
	return this->_inchesTraveledWithinLastSecond / 12;
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