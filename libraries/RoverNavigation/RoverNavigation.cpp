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
	//in degrees
	this->_desiredLatitudeDeg = 0.0;
	this->_desiredLongitudeDeg = 0.0;
	this->_actualLatitudeDeg = 0.0;
	this->_actualLongitudeDeg = 0.0;
	//in radians
	this->_desiredLatitudeRad = 0.0;
	this->_desiredLongitudeRad = 0.0;
	this->_actualLatitudeRad = 0.0;
	this->_actualLongitudeRad = 0.0;
	
}
void RoverNavigation::setDesiredLatitudeDeg(double degreesLatitude)
{
	//stores the desired latitude in degrees
	this->_desiredLatitudeDeg = degreesLatitude;
	//stores the desired latitude in radians
	this->_desiredLatitudeRad = this->degToRad(this->_desiredLatitudeDeg);	
}
void RoverNavigation::setDesiredLongitudeDeg(double degreesLongitude)
{	
	//stores the desired longitude in degrees
	this->_desiredLongitudeDeg = degreesLongitude;
	//stores the desired longitude in radians
	this->_desiredLongitudeRad = this->degToRad(this->_desiredLongitudeDeg);
}
void RoverNavigation::setActualLatitudeDeg(double degreesLatitude)
{
	//stores the actual latitude in degrees
	this->_actualLatitudeDeg = degreesLatitude;
	//stores the actual latitude in radians
	this->_actualLatitudeRad = this->degToRad(this->_actualLatitudeDeg);
}
void RoverNavigation::setActualLongitudeDeg(double degreesLongitude)
{
	//stores the actual longitude in degrees
	this->_actualLongitudeDeg = degreesLongitude;
	//stores the actual longitude in radians
	this->_actualLongitudeRad = this->degToRad(this->_actualLongitudeDeg);
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
double RoverNavigation::getDesiredLatitudeRad()
{
	return this->_desiredLatitudeRad;
}
double RoverNavigation::getDesiredLongitudeRad()
{
	return this->_desiredLongitudeRad;
}
double RoverNavigation::getActualLatitudeRad()
{
	return this->_actualLatitudeRad;
}
double RoverNavigation::getActualLongitudeRad()
{
	return this->_actualLongitudeRad;
}
double RoverNavigation::calculateDistance( byte unitType)
{
  
	//Reference:
	//http://www.movable-type.co.uk/scripts/latlong.html
	//See: "Distance"
	//where	φ is latitude, λ is longitude

	//Per the formula, let the definitions be:
		//lat 1 - actual latitude
		//lat 2 - desired latitude  
		//long 1 - actual longitude 
		//long 2 - desired longitude
	
    
	
  double deltaLatitudeRad;
  double deltaLongitudeRad;
  
  double varA;
  double varC;
  double distance;
  
    
  deltaLatitudeRad = this->_desiredLatitudeRad -  this->_actualLatitudeRad;
  deltaLongitudeRad = this->_desiredLongitudeRad - this->_actualLongitudeRad;
  varA = sin(deltaLatitudeRad/2) * sin(deltaLatitudeRad/2) + cos(this->_actualLatitudeRad) * cos(this->_desiredLatitudeRad) * sin(deltaLongitudeRad/2) * sin(deltaLongitudeRad/2);
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

double RoverNavigation::degToRad(double degrees)
{
	return (degrees * M_PI) / 180;//returns radians
}


 double RoverNavigation::radToDeg(double radians)
{
	return (radians * 180) / M_PI;//returns degrees
}

  

  
  
  
  
  
  
  

float RoverNavigation::getTrueBearing()
{
		
	//Reference:
	//http://www.movable-type.co.uk/scripts/latlong.html
	//See: "Distance"
	//where	φ is latitude, λ is longitude
	
	//Per the formula, let the definitions be:
		//lat 1 - actual latitude
		//lat 2 - desired latitude  
		//long 1 - actual longitude 
		//long 2 - desired longitude
		

			
	double x = 0;
	double y = 0;
	double bearingRad = 0;
	double bearingDegrees = 0;
		
	y = sin(this->_desiredLongitudeRad - this->_actualLongitudeRad) * cos(this->_desiredLatitudeRad);
	x = cos(this->_actualLatitudeRad)*sin(this->_desiredLatitudeRad) - sin(this->_actualLatitudeRad)*cos(this->_desiredLatitudeRad)*cos(this->_desiredLongitudeRad-this->_actualLongitudeRad);
	bearingRad = atan2(y,x);
	bearingDegrees = fmod((this->radToDeg(bearingRad) + 360), 360);
	
	return bearingDegrees;
	
}



float RoverNavigation::getRelativeBearing(float, float)
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
