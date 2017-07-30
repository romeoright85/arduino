#include <Angles.h>


Angles::Angles()
{
	//do nothing
}
Angles::~Angles()
{
	//do nothing
}
double Angles::normalizeAngleDeg(double angleDeg)
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
double Angles::degToRad(double degrees)
{
	return (degrees * M_PI) / 180;//returns radians
}
double Angles::radToDeg(double radians)
{
	return (radians * 180) / M_PI;//returns degrees
}
void Angles::reset()
{
	//do nothing
}
  



  
