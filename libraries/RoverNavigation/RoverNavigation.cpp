#include <RoverNavigation.h>


RoverNavigation::RoverNavigation()
{
	this->_desiredCoordinates = new Coordinates();
	this->_actualCoordinates = new Coordinates();
}
RoverNavigation::~RoverNavigation()
{
	//do nothing
}
void RoverNavigation::reset()
{
	
	this->_desiredCoordinates->reset();
	this->_actualCoordinates->reset();
	
}
void RoverNavigation::setLatitudeDeg(double degreesLatitude, byte type)
{
	if( type == TYPE_ACTUAL)
	{
		//stores the actual latitude in degrees
		this->_actualCoordinates->setLatitudeDeg(degreesLatitude);
	}
	else if (type == TYPE_DESIRED)
	{
		//stores the desired latitude in degrees
		this->_desiredCoordinates->setLatitudeDeg(degreesLatitude);	
	}
	else
	{
		//do nothing since error, invalid type
	}
	
}
void RoverNavigation::setLongitudeDeg(double degreesLongitude, byte type)
{	
	if( type == TYPE_ACTUAL)
	{		
		//stores the desired longitude in degrees
		this->_actualCoordinates->setLongitudeDeg(degreesLongitude);
	}
	else if (type == TYPE_DESIRED)
	{
		//stores the desired longitude in degrees
		this->_desiredCoordinates->setLongitudeDeg(degreesLongitude);		
	}
	else
	{
		//do nothing since error, invalid type
	}
}
void RoverNavigation::setPositionDeg(double degreesLatitude, double degreesLongitude, byte type)
{
	if( type == TYPE_ACTUAL || type == TYPE_DESIRED)
	{		
		this->setLatitudeDeg(degreesLatitude, type);
		this->setLongitudeDeg(degreesLongitude, type);
	}
	else
	{
		//do nothing since error, invalid type
	}
}
void RoverNavigation::setHeadingDeg(float heading)
{
	this->_measuredIMUHeading = heading;
}
double RoverNavigation::getLatitude(byte type, byte unit)
{
	if( unit == UNIT_DEGREES)
	{
		if( type == TYPE_ACTUAL)
		{		
			return this->_actualCoordinates->getLatitudeDeg();
		}
		else if (type == TYPE_DESIRED)
		{
			return this->_desiredCoordinates->getLatitudeDeg();		
		}
		else
		{
			//do nothing since error, invalid type
		}
	}
	else if( unit == UNIT_RADIANS)
	{
		if( type == TYPE_ACTUAL)
		{		
			return this->_actualCoordinates->getLatitudeRad();
		}
		else if (type == TYPE_DESIRED)
		{
			return this->_desiredCoordinates->getLatitudeRad();		
		}
		else
		{
			//do nothing since error, invalid type
		}
	}
	else
	{
		//do nothing since error, invalid type
	}
}
double RoverNavigation::getLongitude(byte type, byte unit)
{
	if( unit == UNIT_DEGREES)
	{
		if( type == TYPE_ACTUAL)
		{		
			return this->_actualCoordinates->getLongitudeDeg();
		}
		else if (type == TYPE_DESIRED)
		{
			return this->_desiredCoordinates->getLongitudeDeg();		
		}
		else
		{
			//do nothing since error, invalid type
		}
	}
	else if( unit == UNIT_RADIANS)
	{
		if( type == TYPE_ACTUAL)
		{		
			return this->_actualCoordinates->getLongitudeRad();
		}
		else if (type == TYPE_DESIRED)
		{
			return this->_desiredCoordinates->getLongitudeRad();		
		}
		else
		{
			//do nothing since error, invalid type
		}
	}
	else
	{
		//do nothing since error, invalid type
	}
}
double RoverNavigation::calculateDistance(Coordinates * actualCoordinates, Coordinates * desiredCoordinates, byte unitType)
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
     
  //deltaLatitudeRad = desiredLatitudeRad - actualLatitudeRad;  
  deltaLatitudeRad = desiredCoordinates->getLatitudeRad() - actualCoordinates->getLatitudeRad();  
  //deltaLongitudeRad = desiredLongitudeRad - actualLongitudeRad;  
  deltaLongitudeRad = desiredCoordinates->getLongitudeRad() - actualCoordinates->getLongitudeRad();  
  //varA = sin(deltaLatitudeRad/2) * sin(deltaLatitudeRad/2) + cos(actualLatitudeRad) * cos(desiredLatitudeRad) * sin(deltaLongitudeRad/2) * sin(deltaLongitudeRad/2);
  varA = sin(deltaLatitudeRad/2) * sin(deltaLatitudeRad/2) + cos(actualCoordinates->getLatitudeRad()) * cos(desiredCoordinates->getLatitudeRad()) * sin(deltaLongitudeRad/2) * sin(deltaLongitudeRad/2);
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
float RoverNavigation::calculateTrueBearing(Coordinates * actualCoordinates, Coordinates * desiredCoordinates)
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

	//y = sin(desiredLongitudeRad - actualLongitudeRad) * cos(desiredLatitudeRad);
	y = sin(desiredCoordinates->getLongitudeRad() - actualCoordinates->getLongitudeRad()) * cos(desiredCoordinates->getLatitudeRad());
	//x = cos(actualLatitudeRad)*sin(desiredLatitudeRad) - sin(actualLatitudeRad)*cos(desiredLatitudeRad)*cos(desiredLongitudeRad - actualLongitudeRad);
	x = cos(actualCoordinates->getLatitudeRad())*sin(desiredCoordinates->getLatitudeRad()) - sin(actualCoordinates->getLatitudeRad())*cos(desiredCoordinates->getLatitudeRad())*cos(desiredCoordinates->getLongitudeRad() - actualCoordinates->getLongitudeRad());
	
	bearingRad = atan2(y,x);
	bearingDegrees = fmod((Angles::radToDeg(bearingRad) + 360), 360);
	
	return bearingDegrees;
	
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
	trueBearing = Angles::normalizeAngleDeg(trueBearing);
	heading = Angles::normalizeAngleDeg(heading);
	
	
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
double RoverNavigation::getDistance( byte unitType)
{
	return this->calculateDistance(this->_actualCoordinates, this->_desiredCoordinates, unitType);
}
float RoverNavigation::getTrueBearing()
{
	
	return this->calculateTrueBearing(this->_actualCoordinates, this->_desiredCoordinates);
	
}
float RoverNavigation::getRelativeBearing()
{
	//FINISH WRITING ME!!	
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


  
  
  


  













