#include <DoSomething.h>

byte DoSomething::objectCount = 0;

DoSomething::DoSomething()
{	
	objectCount++;
	this->objectID = objectCount;
}
DoSomething::~DoSomething()
{
	objectCount--;
}
void DoSomething::reset()
{
	Serial.print(F("Reset Object: "));
	Serial.println(this->objectID);
}
void DoSomething::helloWorld()
{
	Serial.println(F("HELLO"));
}
void DoSomething::goodbyeWorld()
{
	Serial.println(F("GOOD BYE"));
}