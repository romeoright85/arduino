#include <RoverNavigation.h>


RoverNavigation::RoverNavigation()
{
}
RoverNavigation::~RoverNavigation()
{
	//do nothing
}
void RoverNavigation::reset()
{
	this->_desiredLatitudeDeg = 0.0;
	this->_desiredLongitudeDeg = 0.0;
	this->_actualLatitudeDeg = 0.0;
	this->_actualLongitudeDeg = 0.0;
}
void RoverNavigation::setDesiredLatitudeDeg(double degreesLatitude)
{
	this->_desiredLatitudeDeg = degreesLatitude;
}
void RoverNavigation::setDesiredLongitudeDeg(double degreesLongitude)
{
	this->_desiredLongitudeDeg = degreesLongitude;
}
void RoverNavigation::setActualLatitudeDeg(double degreesLatitude)
{
	this->_actualLatitudeDeg = degreesLatitude;
}
void RoverNavigation::setActualLongitudeDeg(double degreesLongitude)
{
	this->_actualLongitudeDeg = degreesLongitude;
}
double RoverNavigation::getDesiredLatitudeDeg()
{
	return this->_desiredLatitudeDeg;
}
double RoverNavigation::getDesiredLongitudeDeg()
{
	return this->_desiredLongitudeDeg;
}
double RoverNavigation::getActualLatitudeDeg()
{
	return this->_actualLatitudeDeg;
}
double RoverNavigation::getActualLongitudeDeg()
{
	return this->_actualLongitudeDeg;
}
double RoverNavigation::calculateDistance( double desired_latitudeDeg, double desired_longitudeDeg, double actual_latitudeDeg, double actual_longitudeDeg, byte unitType)
{
  
  
  //lat 1 - desired latitude  
  double desired_latitudeRad;
  
  //lat 2 - actual latitude
  double actual_latitudeRad;  
  
  //long 1 - desired longitude
  
  
  //long 2 - actual longitude 
    
  double delta_latitudeRad;
  double delta_longitudeRad;
  
  double varA;
  double varC;
  double distance;
  
  
  desired_latitudeRad = (desired_latitudeDeg * M_PI) / 180;
  
  actual_latitudeRad = (actual_latitudeDeg * M_PI) / 180;
  
  delta_latitudeRad = actual_latitudeRad - desired_latitudeRad;
  
  delta_longitudeRad = ((actual_longitudeDeg - desired_longitudeDeg) * M_PI) / 180;
  
  varA = sin(delta_latitudeRad/2) * sin(delta_latitudeRad/2) + cos(desired_latitudeRad) * cos(actual_latitudeRad) * sin(delta_longitudeRad/2) * sin(delta_longitudeRad/2);
  
  varC = 2 * atan2( sqrt(varA), sqrt(1-varA) );
  
  
  if(unitType == UNIT_M)
  {
	  distance = EARTHS_RADIUS_M * varC;//in m
  }
  else if(unitType == UNIT_KM)
  {
	  distance = EARTHS_RADIUS_KM * varC;//in km
  }
  else//error unknown state
  {
	  
	  distance = 0.0;
  }
  
  return distance;
  

}







float RoverNavigation::getRelativeBearing(float headingOfRover, double desired_latitudeDeg, double desired_longitudeDeg, double actual_latitudeDeg, double actual_longitudeDeg)
{

//FINISH WRITING ME!!


	float relativeBearing = 0.0;

	return relativeBearing;//returns the relative bearing of the rover to the destination
}
int RoverNavigation::getCalculatedMotorThrottle()
{
//FINISH WRITING ME!!	
	int throttle = MC_NO_THROTTLE_IDEAL;
	
	//ideal stop is 90
	return throttle;//TEMP DEBUG VALUE
}
int RoverNavigation::getCalculatedMotorSteering()
{
//FINISH WRITING ME!!	
	int steering = MC_CENTER_POSITION_IDEAL;
	
	//ideal center is 90
	return steering;//TEMP DEBUG VALUE
}
