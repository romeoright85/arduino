#include <MotorController.h>
MotorController::MotorController( byte steeringPin, byte throttlePin)
{
	
	//Set the pins
	this->_steeringPin = steeringPin;
	this->_throttlePin = throttlePin;	

	//Create "servo" signal objects	
	this->_steeringControl = new Servo();
	this->_throttleControl = new Servo();	
	
	//set the pins
	this->_steeringControl->attach(this->_steeringPin);
	this->_throttleControl->attach(this->_throttlePin);	
	
	//Initialize
	this->reset();
	
}
MotorController::~MotorController()
{
	//do nothing
}
void MotorController::reset()
{	
	//At HW or SW Reset, the values will be set to MC_CENTER_POSITION_AFTER_POR and MC_NO_THROTTLE_AFTER_POR as defined in RoverConfig.h
	this->calibrateSteering(MC_CENTER_POSITION_AFTER_POR);
	this->calibrateThrottle(MC_NO_THROTTLE_AFTER_POR);
}
void MotorController::setSteering(int steeringAmount)
{
	//Add the calibration offset amount (could be a positive or negative offset) to the desired amount to get the adjusted amount
	steeringAmount = steeringAmount + this->_steeringCalibrationOffset;
	
	//Adjust the amount to boundary limitations	
	this->_steeringAmount = boundToServoLimits(steeringAmount);
	
	//Execute with the final adjusted amount
	this->_steeringControl->write(this->_steeringAmount);	
	
}
void MotorController::setThrottle(int throttleAmount)
{


	//Add the calibration offset amount (could be a positive or negative offset) to the desired amount to get the adjusted amount
	throttleAmount = throttleAmount + this->_throttleCalibrationOffset;
		
	//Adjust the amount to boundary limitations	
	this->_throttleAmount = boundToServoLimits(throttleAmount);
		
	//Execute with the final adjusted amount
	this->_throttleControl->write(this->_throttleAmount);		

}
int MotorController::getSteeringSet()
{
	
	return this->_steeringAmount;//can be values between SRVO_MIN_RANGE to SRVO_MAX_RANGE
	
}
int MotorController::getThrottleSet()
{
	
	return this->_throttleAmount;
		
}
void MotorController::calibrateSteering(int steeringActualAmount)
{
	
	//Example 1: If the ideal is 90 for center but the actual center is 92 then 92 - 90 = 2, which is the _steeringCalibrationOffset 
	//Example 2: If the ideal is 90 for center but the actual center is 87 then 87 - 90 = -3, which is the _steeringCalibrationOffset 
	this->_steeringCalibrationOffset = steeringActualAmount - MC_CENTER_POSITION_IDEAL;
	
}
void MotorController::calibrateThrottle(int throttleActualAmount)
{
	
	//Example 1: If the ideal is 90 for stop but the actual stop is 92 then 92 - 90 = 2, which is the _throttleCalibrationOffset 
	//Example 2: If the ideal is 90 for stop but the actual stop is 87 then 87 - 90 = -3, which is the _throttleCalibrationOffset 
	this->_throttleCalibrationOffset = throttleActualAmount - MC_NO_THROTTLE_IDEAL;
	
}
void MotorController::calibrationSetAsCenter()
{	
	this->calibrateSteering(this->getSteeringSet());//get the current amount set and use it as the calibration amount
}
void MotorController::calibrationSetAsStop()
{
	this->calibrateThrottle(this->getThrottleSet());//get the current amount set and use it as the calibration amount
}



int MotorController::boundToServoLimits(int amount)
{
	//Adjust the amount to boundary limitations
	if(amount>=SRVO_MAX_RANGE)
	{
		return SRVO_MAX_RANGE;
	}		
	else	if(amount<=SRVO_MIN_RANGE)
	{
		return SRVO_MIN_RANGE;
	}
	else
	{
		return amount;
	}
}