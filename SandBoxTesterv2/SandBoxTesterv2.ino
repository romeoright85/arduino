void setup()
{
	Serial.begin(9600);
  

}

void loop()
{
	double numValue = 3.141592654;
	char numCharArray[10];
	char charBuffer[20];
	dtostrf(numValue, 4, 4, numCharArray);//(double, min width, precision, char array)
	sprintf(charBuffer, "Pi: %s", numCharArray);//optional step, if you want to add other text too, you have to send it to another buffer though
	Serial.println(charBuffer);

	//Adding a character to the string
	numValue = 35.7;
	char unit = 'F';
	dtostrf(numValue, 2, 1, numCharArray);//(double, min width, precision, char array)	
	sprintf(charBuffer, "Temp: %s %c", numCharArray, unit);//optional step, if you want to add other text too, you have to send it to another buffer though
	Serial.println(charBuffer);

	//byte to char array
	byte byteValue = 4;		
	sprintf(charBuffer, "Byte Value: %u", byteValue);//where %u is unsigned decimal integer (i.e. a byte is unsigned since it's 0-255)
	Serial.println(charBuffer);
	while (1);
}
