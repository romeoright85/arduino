#include <GimbalController.h>


GimbalController::GimbalController(byte panPin, byte tiltPin)
{
	this->_panPin = panPin;
	this->_tiltPin = tiltPin;
	
	Servo panControl;
	Servo tiltControl;
	
	panControl.attach(this->_panPin);
	tiltControl.attach(this->_tiltPin);
}
GimbalController::~GimbalController()
{
	//do nothing
}
void GimbalController::reset()
{
}

