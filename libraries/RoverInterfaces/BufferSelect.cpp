#include <BufferSelect.h>


BufferSelect::BufferSelect(byte bufferSelectPin)
{
	//Assign pins
	this->_bufferSelectPin = bufferSelectPin;
	
	//Setup pins
	pinMode(this->_bufferSelectPin, OUTPUT);

	//Initialize
	this->reset();
}
BufferSelect::~BufferSelect()
{
	//do nothing
}
void BufferSelect::reset()
{
	this->driverMode(AUTO_DRIVE);
}
boolean BufferSelect::inAutoMode()
{
	return this->_isInAutoMode;
}

void BufferSelect::driverMode(byte selection)
{
	if(selection==AUTO_DRIVE)
	{
		digitalWrite(this->_bufferSelectPin, HIGH);
		this->_isInAutoMode = true;
	}
	else//selection==MANUAL_DRIVE
	{
		digitalWrite(this->_bufferSelectPin, LOW);
		this->_isInAutoMode = false;
	}
}

