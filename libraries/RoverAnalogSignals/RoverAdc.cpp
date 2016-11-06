#include <RoverAdc.h>


RoverAdc::RoverAdc()
{
}
RoverAdc::~RoverAdc()
{
	//do nothing
}
void RoverAdc::reset()
{
	//do nothing
}
unsigned int RoverAdc::rawADCRead(byte analogPin)
{
	return analogRead(analogPin);
}
double RoverAdc::voltageRead(byte analogPin)
{
	unsigned int adcValue;
	double measuredVcc;
	measuredVcc = this->readVcc()/1000.0;
	adcValue = this->rawADCRead(analogPin);
	return (adcValue/1024.0)*measuredVcc;	
}