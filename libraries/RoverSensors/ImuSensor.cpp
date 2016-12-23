#include <ImuSensor.h>


/*
References:
http://www.pololu.com/
http://code.google.com/p/sf9domahrs/
http://code.google.com/p/ardu-imu/

*/

//==Start Of Intergrated Code From Others


	
ImuSensor::ImuSensor()
{
	
	//initialize variables
	this->reset();
	
}
ImuSensor::~ImuSensor()
{
	//do nothing
}		
void ImuSensor::reset() //This function just reinitializes all the variables (and not the hardware)
{
				
		
}
void ImuSensor::init()
{
	
	
	
		

}
void ImuSensor::readSensor()
{

}
float ImuSensor::getRoll()
{
	return 0;//DEBUG
}
float ImuSensor::getPitch()
{
	return 0;//DEBUG
}
float ImuSensor::getYaw()
{
	return 0;//DEBUG
}
float ImuSensor::getHeading()
{
	return 0;//DEBUG
	
}
void ImuSensor::printForAHRS()
{
	
}
