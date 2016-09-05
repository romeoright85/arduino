//this class is used to test ideas and concepts
#include <RoverSandbox.h>

int	 RoverSandbox::_objectInstances = 0;
	
RoverSandbox::RoverSandbox()
{
	Serial.println("object created");
	RoverSandbox::_objectInstances++;
	RoverSandbox::printNumofObjects();
}
RoverSandbox::~RoverSandbox()
{
	Serial.println("object destroyed");
	RoverSandbox::_objectInstances--;
	RoverSandbox::printNumofObjects();
}
void RoverSandbox::reset()
{
	Serial.println("object resetted");
}

void RoverSandbox::printNumofObjects()
{
	Serial.print("Num Of Objects: ");
	Serial.println(_objectInstances);
}
void RoverSandbox::resetObjectInstances()
{
	RoverSandbox::_objectInstances = 0;
	Serial.print("Reset Count: ");
	Serial.println(RoverSandbox::_objectInstances);
}
