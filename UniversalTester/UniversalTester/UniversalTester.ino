//STILL NEED TO TEST THE UART reroute
//the digital pins work



#define PC_BAUD 9600
#define UUT_ARDUINO_BAUD 9600

//global variables
char incomingByte;

//input states
boolean pin2Active = false;
boolean pin3Active = false;
boolean pin4Active = false;

//previous states
boolean pin2Prev = false;
boolean pin3Prev = false;
boolean pin4Prev = false;

boolean pinActiveArray[] = { pin2Active, pin3Active, pin4Active };
boolean pinPrevStatus[] = { pin2Prev, pin3Prev, pin4Prev };
byte inputArray[] = { 2,3,4 };

//output states
boolean pin5Active = false;
boolean pin6Active = false;
boolean pin7Active = false;


//function prototypes
void getPinStatus(byte, byte);//pin, index of pinActiveArray
void printStatus(byte, boolean);//pin, activeState

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(PC_BAUD);//MEGA to PC

	Serial1.begin(UUT_ARDUINO_BAUD);//MEGA to UUT Arduino, 19 (RX) and 18 (TX)

	//declare inputs
	pinMode(2,INPUT);
	pinMode(3, INPUT);
	pinMode(4, INPUT);

	//declare outputs
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);


	//initialize output states
	digitalWrite(5, HIGH);
	digitalWrite(6, LOW);
	digitalWrite(7, LOW);
}

// the loop function runs over and over again until power down or reset
void loop() {
	
	//Take any serial data received from UUT Arduino and re-route it to the PC
	if (Serial1.available() > 0)
	{
		Serial.print("UART: ");

		while(Serial1.available() > 0)
		{
			incomingByte = Serial1.read();
			Serial.print(incomingByte);
		}
	}
	

	//get status of each input and print it out
	for (byte i = 0; i < sizeof(inputArray) / sizeof(inputArray[0]); i++)
	{
		getPinStatus(inputArray[i], i);
	}
		
	delay(1000);

	

	



}

void getPinStatus(byte pin, byte index)
{
	int val;

	val = digitalRead(pin);
	
	if (val == HIGH)
	{	
		pinActiveArray[index] = true;
	}
	else
	{
		pinActiveArray[index] = false;	
	}

	//if the state of the pin has change from last time
	if (pinActiveArray[index] != pinPrevStatus[index])
	{
		printStatus(pin, pinActiveArray[index]);
	}
	pinPrevStatus[index] = pinActiveArray[index];//set the previous state

}

void printStatus(byte pin, boolean activeState)
{
	Serial.print("Pin: ");
	Serial.print(pin);

	if (activeState)
	{
		Serial.println(" is high.");
	}
	else
	{
		Serial.println(" is low.");
	}
}