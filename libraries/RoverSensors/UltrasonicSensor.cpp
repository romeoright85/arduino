#include <UltrasonicSensor.h>




UltrasonicSensor::UltrasonicSensor(byte triggerPin, byte echoPin)
{
	
	//Trigger setup
	this->_triggerPin = triggerPin;
	pinMode(this->_triggerPin, OUTPUT);

	//Echo setup
	this->_echoPin = echoPin;
	pinMode(this->_echoPin, INPUT);
}
UltrasonicSensor::~UltrasonicSensor()
{
	//do nothing
}

int UltrasonicSensor::getDistance(byte mode)
{
		/*
	//initialize variables
	unsigned long prevMicros5uS;//used to read the 1st timestamp to detect timeout
	unsigned long postMicros5uS;//used to read the 2nd timestamp to detect timeout
	this->_distance = 0;//Inherited from DistanceSensor.h
	int pulseWidth = 0;

	//start with the trigger pin low
	digitalWrite(this->_triggerPin, LOW);

	//wait 50mS between sensor enables  
	delay(50);
	
	//pulse trigger pin high
	digitalWrite(this->_triggerPin, HIGH);
	
	//wait 10uS
	delayMicroseconds(10);

	//pulse trigger pin low, this will yield a negative edge. This is where the timing starts.
	digitalWrite(this->_triggerPin, LOW);
	

	//get the 1st reading of the current timestamp
	prevMicros5uS = micros();

	//distance is actually in two-way uS (measured the two way speed of sound)
	pulseWidth = pulseIn(this->_echoPin, HIGH, ULTRASONIC_SENSOR_TIMEOUT);

	//get the 2nd reading of the current timestamp
	postMicros5uS = micros();

	//if the time that has past is greater than the timeout, no echo was returned, so no oject was detected
	if (postMicros5uS - prevMicros5uS >= ULTRASONIC_SENSOR_TIMEOUT)
	{
		this->_distance = -1;//no object detected
	}//end if
	else
	{
		//select mode for returning the distance value
		switch (mode)
		{
			
			//Range of ultrasonic sensor:
				//~2cm - ~450cm			
				//0.02 m to 4.5 m
				//~0.8 in to ~177 in
				//~0.07 ft to ~14.8 ft
			
			case UNIT_CM:
					this->_distance = pulseWidth / 58;//see conversion notes below. The resulting one way distance in "cm".
					this->_distance = constrain(this->_distance, 0, 450);//Output constrained to prevent irregular numbers. Max based on the range of the ultrasonic sensor. See above.
				break;
			case UNIT_M:
					this->_distance = pulseWidth / 5831;//see conversion notes below. The resulting one way distance in "m".
					this->_distance = constrain(this->_distance, 0, 5);//Output constrained to prevent irregular numbers. Max based on the range of the ultrasonic sensor. See above.
				break;
			case UNIT_IN:
					this->_distance = pulseWidth / 148;//see conversion notes below. The resulting one way distance in "in".
					this->_distance = constrain(this->_distance, 0, 178);//Output constrained to prevent irregular numbers. Max based on the range of the ultrasonic sensor. See above.
				break;
			case UNIT_FT:
					this->_distance = pulseWidth / 1778;//see conversion notes below. The resulting one way distance in "ft".
					this->_distance = constrain(this->_distance, 0, 15);//Output constrained to prevent irregular numbers. Max based on the range of the ultrasonic sensor. See above.
				break;
		}//end switch
		
	}//end else

	return this->_distance;

*/

	//initialize variables
	this->_distance = 0;//Inherited from DistanceSensor.h
	int pulseWidth = 0;
	unsigned long avgPulseWidth = 0;
	byte noObjectDetected = 0;//keeps track of the number of times no object is detected
	
	
	#ifdef _DEBUG_TEST_CASE_2 //test with a mix of object detected and non detected pulse width values, but no objects below the threshold
		int pulseWidthArray[ULTRASONIC_SENSOR_SAMPLE_TIMES];
		
		for(byte i = 0 ; i <ULTRASONIC_SENSOR_SAMPLE_TIMES; i++)
		{
				if( i < ULTRASONIC_SENSOR_NO_OBJECT_SAMPLES - 1 )//subtract 1 to keep it below the threshold
				{
					pulseWidthArray[i] = -1;
				}
				else
				{								
					pulseWidthArray[i] = random(20000,22000);//DEBUG
				}
		}		
	#endif			
	#ifdef _DEBUG_TEST_CASE_3 //test with a mix of object detected and non detected pulse width values, but no objects above the threshold
		int pulseWidthArray[ULTRASONIC_SENSOR_SAMPLE_TIMES];
		
		for(byte i = 0 ; i <ULTRASONIC_SENSOR_SAMPLE_TIMES; i++)
		{
				if( i < ULTRASONIC_SENSOR_NO_OBJECT_SAMPLES )
				{
					pulseWidthArray[i] = -1;
				}
				else
				{								
					pulseWidthArray[i] = random(20000,22000);//DEBUG
				}
		}		
	#endif		
		
	
	
	for(byte i = 0; i < ULTRASONIC_SENSOR_SAMPLE_TIMES; i++)
	{
	
		pulseWidth = this->readSensor();
		
		//overwrite actual data with test case data if in debugging
		#ifdef _DEBUG_TEST_CASE_1 //tests with random but object detected pulse width numbers
			/*
				The calculations vary between distance types, pick an artibitrary average value
				for CM 450*58 = 26100 max
				for CM 5*5831 = 29155 max
				//etc
			*/			
			pulseWidth = random(20000,22000);//DEBUG
			Serial.print(F("Pulse Width: "));//DEBUG
			Serial.println(pulseWidth);			
		#endif
		#ifdef _DEBUG_TEST_CASE_2 //test with a mix of object detected and non detected pulse width values, but no objects below the threshold
			pulseWidth = pulseWidthArray[i];
			Serial.print(F("Pulse Width: "));//DEBUG
			Serial.println(pulseWidth);					
		#endif		
		#ifdef _DEBUG_TEST_CASE_3 //test with a mix of object detected and non detected pulse width values, but no objects above the threshold
			pulseWidth = pulseWidthArray[i];
			Serial.print(F("Pulse Width: "));//DEBUG
			Serial.println(pulseWidth);					
		#endif				
		#ifdef _DEBUG_TEST_CASE_4 //test non detected pulse width values
			pulseWidth = -1;//DEBUG	
			Serial.print(F("Pulse Width: "));//DEBUG
			Serial.println(pulseWidth);					
		#endif		
			
		//count the number of no object data
		if(pulseWidth < 0 )
		{
			noObjectDetected++;			
			//if the number of times no object was detected
			if(noObjectDetected >= ULTRASONIC_SENSOR_NO_OBJECT_SAMPLES)
			{				
				this->_distance = -1;//no object detected
				return this->_distance;
			}//end if
		}//end if
		else
		{
			//accumulate pulse width values when the data has detected an object
			avgPulseWidth += pulseWidth;
		}//end else		
	}//end for

	//take the average of the pulse widths by using the sum above and dividing it by (the number of samples taken minus the samples where no object was detected)
	avgPulseWidth = avgPulseWidth/(ULTRASONIC_SENSOR_SAMPLE_TIMES - noObjectDetected);
	
	#if defined (_DEBUG_TEST_CASE_1) || defined(_DEBUG_TEST_CASE_2) || defined(_DEBUG_TEST_CASE_3) || defined(_DEBUG_TEST_CASE_4)
		Serial.print(F("Avg Pulse Width: "));//DEBUG
		Serial.println(avgPulseWidth);//DEBUG
	#endif

		
	//select mode for returning the distance value
	switch (mode)
	{
		
		//Range of ultrasonic sensor:
			//~2cm - ~450cm			
			//0.02 m to 4.5 m
			//~0.8 in to ~177 in
			//~0.07 ft to ~14.8 ft
		
		case UNIT_CM:
				this->_distance = avgPulseWidth / 58;//see conversion notes below. The resulting one way distance in "cm".
				this->_distance = constrain(this->_distance, 0, 450);//Output constrained to prevent irregular numbers. Max based on the range of the ultrasonic sensor. See above.
			break;
		case UNIT_M:
				this->_distance = avgPulseWidth / 5831;//see conversion notes below. The resulting one way distance in "m".
				this->_distance = constrain(this->_distance, 0, 5);//Output constrained to prevent irregular numbers. Max based on the range of the ultrasonic sensor. See above.
			break;
		case UNIT_IN:
				this->_distance = avgPulseWidth / 148;//see conversion notes below. The resulting one way distance in "in".
				this->_distance = constrain(this->_distance, 0, 178);//Output constrained to prevent irregular numbers. Max based on the range of the ultrasonic sensor. See above.
			break;
		case UNIT_FT:
				this->_distance = avgPulseWidth / 1778;//see conversion notes below. The resulting one way distance in "ft".
				this->_distance = constrain(this->_distance, 0, 15);//Output constrained to prevent irregular numbers. Max based on the range of the ultrasonic sensor. See above.
			break;
	}//end switch
		
		

	return this->_distance;


	

}

void UltrasonicSensor::reset()
{
	//software reset
	
	//Trigger setup
	pinMode(this->_triggerPin, OUTPUT);

	//Echo setup
	pinMode(this->_echoPin, INPUT);
	
	this->_distance = 0;//Inherited from DistanceSensor.h
}

int UltrasonicSensor::readSensor()
{
	//initialize variables
	unsigned long prevMicros5uS;//used to read the 1st timestamp to detect timeout
	unsigned long postMicros5uS;//used to read the 2nd timestamp to detect timeout	
	int pulseWidth = 0;

	//start with the trigger pin low
	digitalWrite(this->_triggerPin, LOW);

	//wait 50mS between sensor enables  
	delay(50);
	
	//pulse trigger pin high
	digitalWrite(this->_triggerPin, HIGH);
	
	//wait 10uS
	delayMicroseconds(10);

	//pulse trigger pin low, this will yield a negative edge. This is where the timing starts.
	digitalWrite(this->_triggerPin, LOW);
	

	//get the 1st reading of the current timestamp
	prevMicros5uS = micros();

	//distance is actually in two-way uS (measured the two way speed of sound)
	pulseWidth = pulseIn(this->_echoPin, HIGH, ULTRASONIC_SENSOR_TIMEOUT);

	//get the 2nd reading of the current timestamp
	postMicros5uS = micros();

	//if the time that has past is greater than the timeout, no echo was returned, so no oject was detected
	if (postMicros5uS - prevMicros5uS >= ULTRASONIC_SENSOR_TIMEOUT)
	{
		return -1;//no object detected
	}//end if
	else
	{
		return pulseWidth;		
	}//end else
}






/*


	References:
	http://www.robot-electronics.co.uk/htm/arduino_examples.htm#SRF04 Ultrasonic Ranger     
	http://www.robot-electronics.co.uk/files/arduino_srf04.ino
	http://www.unitconversion.org/time/microseconds-to-milliseconds-conversion.html

	Note:
	"The timing of this function has been determined empirically and will probably show errors in longer pulses. Works on pulses from 10 microseconds to 3 minutes in length."
	http ://arduino.cc/en/Reference/pulseIn

	Hardware:
		Ultrasonic sensor I bought on Ebay.
		Range : 2cm - 450cm(~0.8 in to ~177 in) or (~0.07 ft to ~14.8 ft) or (0.02 m to 4.5 m)


	Block Diagram:

	_________________
	|   ___   ___    |
	|  /   \ /   \   |
	|  \___/ \___/   |
	|________________|
		  oooo
		  1234 (left to right from front view)

	Pin Diagram :

	oooo
	1234 (left to right from front view)

	1 : Vcc = 5V
	2 : Input to Ultrasonic Sensor : Trigger = Normally low and disabled, when pulse high for at least 10uS device is enabled.One negative edge of this pulse is T1. (wait 50mS between enables)
	3 : Output from Ultrasonic Sensor : Echo = Normally low.Then it pulses high after it is enabled by the trigger.When it goes back to low, the negative edge is T2.
	4 : Ground = 0V

	Distance : Let x = delta(T) = T2 - T1


	In Centimeters:

		34300 cm / s = the speed of sound

		x uS * (s / 1000000 uS) * (34300 cm / s) = x * 34300 / 1000000 cm = x * 0.034300 cm = x / 29.15451895043732 cm (two way distance)

		is the time from the sensor out to the object and back

		so

		the one way distance is :

		( x / 29.15451895043732 ) / 2 cm = x / (29.15451895043732 * 2) cm = x / 58.30903790087464 ~= x / 58 cm
	
	In Meters:

		343 m / s = the speed of sound

		x uS * (s / 1000000 uS) * (343 m / s) = x * 343 / 1000000 m = x * 0.000343 m = x / 2915.451895043732 m (two way distance)

		is the time from the sensor out to the object and back

		so

		the one way distance is :

		(( x / 2915.451895043732 ) / 2) m = x / (2915.451895043732 * 2) cm = x / 5830.903790087464 ~= x / 5831 m

	In Inches:


		13504 in / s = the speed of sound

		x uS * (s / 1000000 uS) * (13504 in / s) = x * 13504 / 1000000 in = x * 0.013504 in = x / 74.0521327014218 in (two way distance)

		is the time from the sensor out to the object and back

		so

		the one way distance is :

		(( x / 74.0521327014218 ) / 2 ) in = x / (74.0521327014218 * 2) in = x / 148.1042654028436 ~= x / 148 in




	In Feet:


		1125 ft / s = the speed of sound

		x uS * (s / 1000000 uS) * (1125 ft / s) = x * 1125 / 1000000 ft = x * 0.001125 ft = x / 888.8888888888889 ft (two way distance)

		is the time from the sensor out to the object and back

		so

		the one way distance is :

		(( x / 888.8888888888889 ) / 2 ) in = x / ( 888.8888888888889 * 2) in = x / 1777.777777777778 ~= x / 1778 in


*/


