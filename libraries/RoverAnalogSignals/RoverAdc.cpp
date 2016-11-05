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
}
long RoverAdc::readVcc()
{
	long result;
	// Read 1.1V reference against AVcc
	ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
	delay(2); // Wait for Vref to settle
	ADCSRA |= _BV(ADSC); // Convert
	while (bit_is_set(ADCSRA, ADSC));
	result = ADCL;
	result |= ADCH << 8;
	result = 1126400L / result; // Back-calculate AVcc in mV
	return result;
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