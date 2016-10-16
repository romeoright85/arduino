#include <GimbalController.h>

GimbalController::GimbalController( byte panPin, byte tiltPin)
{
	
	//Set the pins
	this->_panPin = panPin;
	this->_tiltPin = tiltPin;	

	//Create "servo" signal objects	
	this->_panControl = new Servo();
	this->_tiltControl = new Servo();	
	
	//set the pins
	this->_panControl->attach(this->_panPin);
	this->_tiltControl->attach(this->_tiltPin);	
	
	//Initialize
	this->reset();	
}
GimbalController::~GimbalController()
{
	//do nothing
}
void GimbalController::reset()
{	
	//At HW or SW Reset, the values will be set to GC_CENTER_POSITION_AFTER_POR and GC_MIDDLE_POSITION_AFTER_POR as defined in RoverCalibration.h
	this->calibratePan(GC_CENTER_POSITION_AFTER_POR);
	this->calibrateTilt(GC_MIDDLE_POSITION_AFTER_POR);
}
void GimbalController::setPan(int panAmount)
{
	//Add the calibration offset amount (could be a positive or negative offset) to the desired amount to get the adjusted amount
	panAmount = panAmount + this->_panCalibrationOffset;
	
	//Adjust the amount to boundary limitations	
	this->_panAmount = boundToServoLimits(panAmount);
	
	//Execute with the final adjusted amount
	this->_panControl->write(this->_panAmount);	
	
}
void GimbalController::setTilt(int tiltAmount)
{

	//Add the calibration offset amount (could be a positive or negative offset) to the desired amount to get the adjusted amount
	tiltAmount = tiltAmount + this->_tiltCalibrationOffset;
		
	//Adjust the amount to boundary limitations	
	this->_tiltAmount = boundToServoLimits(tiltAmount);
		
	//Execute with the final adjusted amount
	this->_tiltControl->write(this->_tiltAmount);		

}
int GimbalController::getPanSet()
{
	
	return this->_panAmount;//can be values between SRVO_MIN_RANGE to SRVO_MAX_RANGE
	
}
int GimbalController::getTiltSet()
{
	
	return this->_tiltAmount;//can be values between SRVO_MIN_RANGE to SRVO_MAX_RANGE
		
}



void GimbalController::calibratePan(int panActualAmount)
{
	
	//Example 1: If the ideal is 90 for center but the actual center is 92 then 92 - 90 = 2, which is the _panCalibrationOffset 
	//Example 2: If the ideal is 90 for center but the actual center is 87 then 87 - 90 = -3, which is the _panCalibrationOffset 
	this->_panCalibrationOffset = panActualAmount - GC_CENTER_POSITION_IDEAL;
	
}
void GimbalController::calibrateTilt(int tiltActualAmount)
{
	
	//Example 1: If the ideal is 90 for stop but the actual stop is 92 then 92 - 90 = 2, which is the _tiltCalibrationOffset 
	//Example 2: If the ideal is 90 for stop but the actual stop is 87 then 87 - 90 = -3, which is the _tiltCalibrationOffset 
	this->_tiltCalibrationOffset = tiltActualAmount - GC_MIDDLE_POSITION_IDEAL;
	
}
void GimbalController::calibrationSetAsCenter()
{	
	this->calibratePan(this->getPanSet());//get the current amount set and use it as the calibration amount
}
void GimbalController::calibrationSetAsMiddle()
{
	this->calibrateTilt(this->getTiltSet());//get the current amount set and use it as the calibration amount
}
int GimbalController::boundToServoLimits(int amount)
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
