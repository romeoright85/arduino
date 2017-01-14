

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);

}

// the loop function runs over and over again until power down or reset
void loop() {
			
	char gpsData[] = "GPGGA,142103.400,3916.2242,N,07636.6542,W,1,3,3.90,183.6,M,-33.6,M,,*6B";

	char * output;

	


	Serial.println(gpsData);
	
	byte startIndex;
	byte endIndex;

	//1
	endIndex = indexOf(gpsData, ',', sizeof(gpsData) / sizeof(gpsData[0]));//array, start index, array size
	output = subCharArray(gpsData, startIndex, endIndex + 1);
	Serial.println(output);
	//2
	startIndex = endIndex + 1;
	endIndex = indexOf(gpsData, startIndex, ',', sizeof(gpsData) / sizeof(gpsData[0]));//array, start index, array size
	output = subCharArray(gpsData, startIndex, endIndex);
	Serial.println(output);
	//3
	startIndex = endIndex + 1;
	endIndex = indexOf(gpsData, startIndex, ',', sizeof(gpsData) / sizeof(gpsData[0]));//array, start index, array size
	output = subCharArray(gpsData, startIndex, endIndex);
	Serial.println(output);
	//4	
	startIndex = endIndex + 1;
	endIndex = indexOf(gpsData, startIndex, ',', sizeof(gpsData) / sizeof(gpsData[0]));//array, start index, array size
	output = subCharArray(gpsData, startIndex, endIndex);
	Serial.println(output);
	//5
	startIndex = endIndex + 1;
	endIndex = indexOf(gpsData, startIndex, ',', sizeof(gpsData) / sizeof(gpsData[0]));//array, start index, array size	
	output = subCharArray(gpsData, startIndex, endIndex);
	Serial.println(output);
	//6
	startIndex = endIndex + 1;
	endIndex = indexOf(gpsData, startIndex, ',', sizeof(gpsData) / sizeof(gpsData[0]));//array, start index, array size	
	output = subCharArray(gpsData, startIndex, endIndex);
	Serial.println(output);
	//7
	startIndex = endIndex + 1;
	endIndex = indexOf(gpsData, startIndex, ',', sizeof(gpsData) / sizeof(gpsData[0]));//array, start index, array size	
	output = subCharArray(gpsData, startIndex, endIndex);
	Serial.println(output);
	//8
	startIndex = endIndex + 1;
	endIndex = indexOf(gpsData, startIndex, ',', sizeof(gpsData) / sizeof(gpsData[0]));//array, start index, array size	
	output = subCharArray(gpsData, startIndex, endIndex);
	Serial.println(output);
	//9
	startIndex = endIndex + 1;
	endIndex = indexOf(gpsData, startIndex, ',', sizeof(gpsData) / sizeof(gpsData[0]));//array, start index, array size	
	output = subCharArray(gpsData, startIndex, endIndex);
	Serial.println(output);
	//10
	startIndex = endIndex + 1;
	endIndex = indexOf(gpsData, startIndex, ',', sizeof(gpsData) / sizeof(gpsData[0]));//array, start index, array size	
	output = subCharArray(gpsData, startIndex, endIndex);
	Serial.println(output);
	//11
	startIndex = endIndex + 1;
	endIndex = indexOf(gpsData, startIndex, ',', sizeof(gpsData) / sizeof(gpsData[0]));//array, start index, array size	
	output = subCharArray(gpsData, startIndex, endIndex);
	Serial.println(output);
	//12
	startIndex = endIndex + 1;
	endIndex = indexOf(gpsData, startIndex, ',', sizeof(gpsData) / sizeof(gpsData[0]));//array, start index, array size	
	output = subCharArray(gpsData, startIndex, endIndex);
	Serial.println(output);
	//13
	startIndex = endIndex + 1;
	endIndex = indexOf(gpsData, startIndex, ',', sizeof(gpsData) / sizeof(gpsData[0]));//array, start index, array size	
	output = subCharArray(gpsData, startIndex, endIndex);
	Serial.println(output);
	//14
	startIndex = endIndex + 1;
	endIndex = indexOf(gpsData, startIndex, ',', sizeof(gpsData) / sizeof(gpsData[0]));//array, start index, array size	
	output = subCharArray(gpsData, startIndex, endIndex);
	Serial.println(output);
	//15
	startIndex = endIndex + 1;
	endIndex = indexOf(gpsData, startIndex, ',', sizeof(gpsData) / sizeof(gpsData[0]));//array, start index, array size	
	output = subCharArray(gpsData, startIndex, endIndex);
	Serial.println(output);





	Serial.println("bye");
	free(output);
	while (1);//end the program
}

//With no start index provided
byte indexOf(char * array, char charToFind, byte arraySize)
{
	//add delay else the function delegation doesn't work properly
	delay(1);
	return indexOf(array, 0, charToFind, arraySize);
}

//With start index provided
byte indexOf(char * array, byte startIndex, char charToFind, byte arraySize)
{


	for (byte i = startIndex; i <= arraySize; i++)
	{

		if (array[i] == charToFind)
		{

			return i;

		}
	}
	return -1;
}




char * subCharArray(char * array, byte startIndex, byte endIndex)
{
	byte size = endIndex - startIndex;
	char * temp;
	temp = (char*)malloc(size * sizeof(char));
	strncpy(temp, array + startIndex, size * sizeof(char));
	temp[size * sizeof(char)] = 0;
	return temp;

}


char * subCharArray(char * array, byte endIndex)
{
	byte size = endIndex;
	char * temp;
	temp = (char*)malloc(size * sizeof(char));
	strncpy(temp, array, size * sizeof(char));
	temp[size * sizeof(char)] = 0;
	return temp;

}

