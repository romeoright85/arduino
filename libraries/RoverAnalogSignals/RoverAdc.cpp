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
	measuredVcc = this->readVcc()/1000.0;//converted measured Vcc from millivolts to Volts
	adcValue = this->rawADCRead(analogPin);
	return (adcValue/1024.0)*measuredVcc;	//10-bit ADC, so 2^10- 1024
}