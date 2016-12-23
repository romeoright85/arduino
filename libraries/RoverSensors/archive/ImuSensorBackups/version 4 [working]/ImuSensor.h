//ImuSensor.h

/*
Bug Alert:
This code didn't work with pointer objects. It was flakey and the code/serial seemed to lock up.

	#ifdef IMU_V5
			LSM6 * _gyro_acc;
			LIS3MDL * _mag;
		#else // older IMUs through v4
			L3G * _gyro;
			LSM303 * _compass;
		#endif
So use absolute objects instead.
	#ifdef IMU_V5
			LSM6 _gyro_acc;
			LIS3MDL _mag;
		#else // older IMUs through v4
			L3G _gyro;
			LSM303 _compass;
		#endif
*/	
		

#ifndef _IMUSENSOR_H
#define _IMUSENSOR_H

	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>	
	#include <Wire.h>
	
	
	#define _IMU_DEFINITIONS
	#define _IMU_CALIBRATIONS
	

	// Uncomment the following line to use a MinIMU-9 v5 or AltIMU-10 v5. Leave commented for older IMUs (up through v4).
	//#define IMU_V5
	#ifdef IMU_V5
		#include <LSM6.h>
		#include <LIS3MDL.h>
	#else // older IMUs through v4
		#include <L3G.h>
		#include <LSM303.h>
	#endif
	
	
	//MinIMU-9 v2
	//Reference: https://www.pololu.com/product/1268/resources
	
	/*******************************************************************
	Configure (define) flags before calling #include <RoverConfig.h>
	/********************************************************************/

	//define Arduino 2: AUXI in order to use it's config pins
	#ifndef _ARD_2_AUXI_H
		#define _ARD_2_AUXI_H
	#endif

	/********************************************************************/

	#include <RoverCalibration.h>
	#include <RoverConfig.h>
	
	class ImuSensor : public virtual RoverReset {
	public:
		ImuSensor();//constructor
		~ImuSensor();//destructor
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)		
		void init();//initialize the IMU Sensor, must not be done in the global, but either in the setup() or the loop().
		void printOffsets();//serially prints the offsets of the sensors of the array _AN_OFFSET[]
		void readSensor();//reads the IMU Sensor Data. You will still need to get the data.
		float getRoll();	
		float getPitch();
		float getYaw();
		float getHeading();	
		void printForAHRS();//serially prints the output in the format for the AHRS (i.e. "!ANG:0.00,0.00,0.00")
		
		
		
	private:		
	
		//==Start Of Intergrated Code From Others						
		void Accel_Init();
		void Compass_Init();
		void Gyro_Init();
		void I2C_Init();
		void Read_Gyro();
		void Read_Accel();
		
		void Read_Compass();
		void Compass_Heading();
		void Matrix_update();
		void Normalize();
		
		
		
		void Drift_correction();
		void Euler_angles();
		void Matrix_Multiply(float [3][3], float [3][3], float [3][3]);//Multiply two 3x3 matrixs. This function developed by Jordi can be easily adapted to multiple n*n matrix's. (Pero me da flojera!). 
		float Vector_Dot_Product(float [3],float [3]);//Computes the dot product of two vectors
		void Vector_Cross_Product(float [3], float [3],float [3]);//Computes the cross product of two vectors
		void Vector_Scale(float [3],float [3], float );//Multiply the vector by a scalar. 
		void Vector_Add(float [3],float [3], float [3]);//Adds Vectors
		//==End Of Intergrated Code From Others						
		
		
		//SW Resetable		
		float _heading;//compass heading in degrees
						
		//==Start Of Intergrated Code From Others				
			
		int _SENSOR_SIGN[9];//Correct directions x,y,z - gyro, accelerometer, magnetometer			
		float _G_Dt;    // Integration time (DCM algorithm)  We will run the integration loop at 50Hz if possible
		long _timer;   //general purpuse timer
		long _timer_old;		
		int _AN[6]; //array that stores the gyro and accelerometer data
		int _AN_OFFSET[6]; //Array that stores the Offset of the sensors
		int _gyro_x;
		int _gyro_y;
		int _gyro_z;
		int _accel_x;
		int _accel_y;
		int _accel_z;
		int _magnetom_x;
		int _magnetom_y;
		int _magnetom_z;
		float _c_magnetom_x;
		float _c_magnetom_y;
		float _c_magnetom_z;
		float _MAG_Heading;
		float _Accel_Vector[3]; //Store the acceleration in a vector
		float _Gyro_Vector[3];//Store the gyros turn rate in a vector
		float _Omega_Vector[3]; //Corrected Gyro_Vector data
		float _Omega_P[3];//Omega Proportional correction
		float _Omega_I[3];//Omega Integrator
		float _Omega[3];
		// Euler angles
		float _roll;
		float _pitch;
		float _yaw;
		float _errorRollPitch[3];
		float _errorYaw[3];
		unsigned int _counter;
		
		float _DCM_Matrix[3][3];
		float _Update_Matrix[3][3];
		float _Temporary_Matrix[3][3];

		
		#ifdef IMU_V5
			LSM6 _gyro_acc;
			LIS3MDL _mag;
		#else // older IMUs through v4
			L3G _gyro;
			LSM303 _compass;
		#endif
		
		
		//==End Of Intergrated Code From Others						
			
			
	};
	
#endif 














