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





double RoverNavigation::getDistance( byte unitType)
{
	return this->calculateDistance(  this->_actualLatitudeRad, this->_actualLongitudeRad, this->_desiredLatitudeRad, this->_desiredLongitudeRad, unitType);
}


double RoverNavigation::calculateDistance( float actualLatitudeRad, float actualLongitudeRad, float desiredLatitudeRad, float desiredLongitudeRad, byte unitType)
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
     
  deltaLatitudeRad =desiredLatitudeRad - actualLatitudeRad;  
  deltaLongitudeRad = desiredLongitudeRad - actualLongitudeRad;  
  varA = sin(deltaLatitudeRad/2) * sin(deltaLatitudeRad/2) + cos(actualLatitudeRad) * cos(desiredLatitudeRad) * sin(deltaLongitudeRad/2) * sin(deltaLongitudeRad/2);
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
	
	return this->calculateTrueBearing(this->_actualLatitudeRad, this->_actualLongitudeRad, this->_desiredLatitudeRad, this->_desiredLongitudeRad);
	
}
  

float RoverNavigation::calculateTrueBearing(float actualLatitudeRad, float actualLongitudeRad, float desiredLatitudeRad, float desiredLongitudeRad)
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

	y = sin(desiredLongitudeRad - actualLongitudeRad) * cos(desiredLatitudeRad);
	x = cos(actualLatitudeRad)*sin(desiredLatitudeRad) - sin(actualLatitudeRad)*cos(desiredLatitudeRad)*cos(desiredLongitudeRad - actualLongitudeRad);
	bearingRad = atan2(y,x);
	bearingDegrees = fmod((this->radToDeg(bearingRad) + 360), 360);
	
	return bearingDegrees;
	
}
float RoverNavigation::normalizeAngleDeg(float angleDeg)
{
	if( angleDeg >= 0 && angleDeg < 360 )
	{
		return angleDeg;
	}
	else if(angleDeg < 0)
	{
		angleDeg = angleDeg + 360;
	}
	else //angleDeg >= 360
	{		
		return fmod(angleDeg,360);
	}
}


float RoverNavigation::calculateRelativeBearing(float heading, float trueBearing)
{

/*
	Sample test for calculateRelativeBearing()
	
	value = roverNavigation->calculateRelativeBearing(10, 20);
	Serial.println(value, 4);//print with 4 decimals
	value = roverNavigation->calculateRelativeBearing(20, 10);
	Serial.println(value, 4);//print with 4 decimals
	value = roverNavigation->calculateRelativeBearing(0, 180);
	Serial.println(value, 4);//print with 4 decimals	
	value = roverNavigation->calculateRelativeBearing(180, 0);
	Serial.println(value, 4);//print with 4 decimals
	value = roverNavigation->calculateRelativeBearing(45, 270);
	Serial.println(value, 4);//print with 4 decimals
	value = roverNavigation->calculateRelativeBearing(270, 45);
	Serial.println(value, 4);//print with 4 decimals
	value = roverNavigation->calculateRelativeBearing(10, 350);
	Serial.println(value, 4);//print with 4 decimals	
	value = roverNavigation->calculateRelativeBearing(350, 10);
	Serial.println(value, 4);//print with 4 decimals
	value = roverNavigation->calculateRelativeBearing(0, 355);
	Serial.println(value, 4);//print with 4 decimals
	value = roverNavigation->calculateRelativeBearing(355, 0);
	Serial.println(value, 4);//print with 4 decimals
	value = roverNavigation->calculateRelativeBearing(90, 270);
	Serial.println(value, 4);//print with 4 decimals
	value = roverNavigation->calculateRelativeBearing(270, 90);
	Serial.println(value, 4);//print with 4 decimals
	value = roverNavigation->calculateRelativeBearing(135, 225);
	Serial.println(value, 4);//print with 4 decimals
	value = roverNavigation->calculateRelativeBearing(225, 135);
	Serial.println(value, 4);//print with 4 decimals
	value = roverNavigation->calculateRelativeBearing(0, 135);
	Serial.println(value, 4);//print with 4 decimals
	value = roverNavigation->calculateRelativeBearing(135, 0);
	Serial.println(value, 4);//print with 4 decimals
	value = roverNavigation->calculateRelativeBearing(135, 270);
	Serial.println(value, 4);//print with 4 decimals
	value = roverNavigation->calculateRelativeBearing(270, 135);
	Serial.println(value, 4);//print with 4 decimals
	value = roverNavigation->calculateRelativeBearing(1, 190);
	Serial.println(value, 4);//print with 4 decimals
	value = roverNavigation->calculateRelativeBearing(190, 1);
	Serial.println(value, 4);//print with 4 decimals
*/

	float relativeBearing = 0.0;
	
	
	//Normalize the angle in degrees to meet the range of 0 to 360 degrees
	trueBearing = normalizeAngleDeg(trueBearing);
	heading = normalizeAngleDeg(heading);
	
	
	//Calculate the delta between the trueBearing (destination) and heading (origin)
	relativeBearing = trueBearing - heading;
	
	if(abs(relativeBearing) > 180)
	{
		if(trueBearing>heading)
		{
			relativeBearing = -1*(heading + 360 - trueBearing);
		}
		else //trueBearing < heading, since if trueBearing == heading then this cannot be true: abs(relativeBearing) > 180 
		{
			relativeBearing = trueBearing + 360 - heading;
		}
	}
	else if(abs(relativeBearing) == 180)
	{
		relativeBearing = 180.0;//for -180 and +180, just make it 180
	}
		
	return relativeBearing;//returns the relative bearing of the rover to the destination
}

void RoverNavigation::setHeadingDeg(float heading)
{
	this->_measuredIMUHeading = heading;
}
float RoverNavigation::getRelativeBearing()
{
	//this->_measuredIMUHeading;
	//float RoverNavigation::calculateRelativeBearing(float heading, float trueBearing)
	return 0.0;//debug
	
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

//when negative angle turn left, when positive angle turn right
//range is between 0 to 180

	int steering = MC_CENTER_POSITION_IDEAL;
	
	//ideal center is 90
	return steering;//TEMP DEBUG VALUE
}
