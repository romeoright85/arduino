#include <UpTime.h>


UpTime::UpTime()
{
	//initialize variables
	this->forcedReset();
}
UpTime::~UpTime()
{
	//do nothing
}
void UpTime::reset()
{
	//do nothing for SW resets as you want the uptime to keep counting as the rover is still up the whole time
	//it will only reset with hardware resets or with forcedReset()
}
void UpTime::forcedReset()
{
	this->_upTimeInSeconds = 0;	
	this->_numberOfRollOvers = 0;
	this->rolloverOccuringSoon = false;
}
unsigned long UpTime::getDays()
{
		
	//Part 1:
	//this->_numberOfRollOvers * 50 means: convert the number of rollovers into days. Each rollover is about 50 days, since 4,294,967,295 milliseconds is 49.71026961805556 days.
	//Part 2:
	//this->_upTimeInSeconds / 86400 means: convert seconds into days. As there are 60 seconds in a minute, 60 minutes in an hour, and 24 hours in a day = 60 x 60 x 24 = 86400
	
	return (this->_numberOfRollOvers * 50) + (this->_upTimeInSeconds / 86400);

	
}
byte UpTime::getHours()
{
	

	//Part 1:
	//this->_upTimeInSeconds / 3600 means: seconds into hours. As there are 60 seconds in a minute and 60 minutes in an hour = 60 x 60 = 3600
	//Part 2:
	//(value from above) % 24 means: take the value of hours calculated earlier, then get the remainder (%) of hours after dividing by 24. As anything in multiples of 24 hours will be captured by days
	return (this->_upTimeInSeconds / 3600) % 24;
	
}
byte UpTime::getMinutes()
{		
	//Part 1:
	//this->_upTimeInSeconds / 60 means: convert minutes to seconds by dividing uptime seconds by 60
	//Part 2:
	//(value from above) % 60 means: take the value of minutes calculated earlier, then get the remainder (%) of minutes after dividing by 60. As anything in multiples of 60 minutes will be captured by hours (or days)
	return (this->_upTimeInSeconds / 60) % 60;	
}
byte UpTime::getSeconds()
{		
	//this->_upTimeInSeconds % 60 means: get the remainder (%) of seconds after dividing by 60. As anything in multiples of 60 seconds will be captured by minutes (or hours, or days)
	return this->_upTimeInSeconds % 60;
}
void UpTime::run()
{
	
	//Detect when the millis() function is near it's upper unsigned long range threshold
	if (millis() >= UPTIME_ROLLOVER_UPPER_THRESHOLD) {
		rolloverOccuringSoon = 1;
	}
	
	//Check for rollover occurence.
	//Check that after the upper threshold was reached, if the millis() function has started over and is now a lower number (as a roll over has occurred since normally the value should always be increasing)
	//Note: this stage might not happen right after the rolloverOccuringSoon has gone to 1, but go ahead and check it all the time.
	if (millis() <= UPTIME_ROLLOVER_LOWER_THRESHOLD && rolloverOccuringSoon == 1) {
		this->_numberOfRollOvers++;//increment the number of rollovers counter
		rolloverOccuringSoon = 0;//reset the rollover upper threshold detector flag
	}

	
	//convert the uptime number of milliseconds to seconds
	this->_upTimeInSeconds = millis() / 1000;	
	
}
void UpTime::printUptime()
{
	char charBuffer[50];
	//sprintf(charBuffer, "Rover Uptime: %d days, %2d:%2d:%2d", getDays(), getHours(), getMinutes(), getSeconds() );
	sprintf(charBuffer, "Rover Uptime: %lu days, %02d:%02d:%02d", getDays(), getHours(), getMinutes(), getSeconds() );
	//Serial.println(getDays());
	//Serial.println(getHours());
	//Serial.println(getMinutes());
	//Serial.println(getSeconds());
	Serial.println(charBuffer);	
}