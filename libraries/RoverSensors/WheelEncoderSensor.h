//WheelEncoderSensor.h
#ifndef _WHEELENCODERSENSOR_H
#define _WHEELENCODERSENSOR_H

	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>
	
	
	#define _WHEEL_ENCODER_DEFINITIONS
	/*******************************************************************
	Configure (define) flags before calling #include <RoverConfig.h>
	/********************************************************************/
	//define Arduino 1: NAVI in order to use it's config pins
	#ifndef _ARD_1_NAVI_H
		#define _ARD_1_NAVI_H
	#endif

	//define Arduino 3: MAIN in order to use it's config pins
	#ifndef _ARD_3_MAIN_H
		#define _ARD_3_MAIN_H
	#endif
	
/*
Motor
https://www.pololu.com/product/2275
Wheel (120mm diameter)
https://www.pololu.com/product/1555
The circumference of the wheel is 2*pi*r=2*pi*(d/2) = 2*pi*60mm = 376.991118431 = 14.84217001696851 inches = about 15 inches
So let INCHES_PER_REVOLUTION  = 15


The quadrature encoder provides a resolution of 48 counts per revolution of the motor shaft when counting both edges of both channels.
To compute the counts per revolution of the gearbox output, multiply the gear ratio by 48.
Since the motor is 74.83:1, 48 x 74.83 = 3591.84.
But for this design we will be counting only one edge of one channel. And we don't care about the gearbox output, but the motor output instead as the wheel is connected to the motor not the gear box.
So 48 counts for two edges for two channels / 2 channels / 2 edges = 12 counts per rising edge of one channel.
So let SINGLE_SIDED_EDGES_PER_REVOLUTION = 12



A Quadrature Encoder has two channels. For this design, they will be called channel A and channel B.

//DEBUG, MAY NEED TO UPDATE THIS CONVENTION AFTER TESTING IT ON THE ROVER. JUST RENAME THE DEFINITIONS OR CHANNEL A and CHANNEL B

	Due to the limited number of interrupts in the Arduinos, each motor will have Channel A connected to an interrupt and Channel B connected to a regular Digital Input.

	Let's define the convention as such:
		when the motor is mounted on the right side of the assembly
			and channel A's signal goes high (rising edge) before channel B, the motor is going forward.
				This can be detected by sensing the rising edge of Channel A, and measuring a low logic level on Channel B.
			and channel B's signal goes high (rising edge) before channel A, the motor is going in reverse.
				This can be detected by sensing the rising edge of Channel A, and measuring a high logic level on Channel B.
		when the motor is mounted on the left side of the assembly
			and channel A's signal goes high (rising edge) before channel B, the motor is going in reverse.
				This can be detected by sensing the rising edge of Channel A, and measuring a low logic level on Channel B.
			and channel B's signal goes high (rising edge) before channel A, the motor is going forward.
				This can be detected by sensing the rising edge of Channel A, and measuring a high logic level on Channel B.
*/
	
	/********************************************************************/

	#include <RoverConfig.h>
	
	typedef void (*voidFuncPtr)(void);//defining the type voidFuncPtr that is a function pointer that takes no arguments and returns void. It is used later on for the interrupt service routine.
	
	class WheelEncoderSensor : public virtual RoverReset {
	public:
		WheelEncoderSensor(byte, byte, byte, voidFuncPtr);//constructor. (pin of encoder channel A, pin of encoder channel B, side the motor is on, the interrupt service routine for the edge detection). The side the motor is on the robot will determine if the motor is going in reverse or forward relativate to encoder channel A and B.
		~WheelEncoderSensor();//destructor
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		byte getDirection();//returns the direction of the motor in
		int getSpeed();//returns the speed of the motor in inches per second, value is rounded off/truncated
		int getFootage();//returns the distance traveled in feet, value is rounded off/truncated
		void isrUpdate();//updates the _chAIsLeadingChB and _encoderAEdgeCount variables when the interrupt service routine (ISR) is called
	private:
		
		//Not SW Resettable
		byte _pinEncoderA;
		byte _pinEncoderB;
		byte _motorSide;
		void calculateMotorParameters();//DEBUG, called by a timer function??
		
		
		//SW Resettable
		byte _motorDirection;
		byte _inchesTraveled;
		int _mtrSpeed;
		byte _encoderAEdgeCount;//holds the current edge count
		byte _prevEncoderAEdgeCount;//holds the past edge count
		byte _encoderBLevel;
		bool _chAIsLeadingChB;//if encoder channel A is leading channel B
	};

	#endif 