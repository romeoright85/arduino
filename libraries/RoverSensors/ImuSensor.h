//ImuSensor.h
#ifndef _IMUSENSOR_H
#define _IMUSENSOR_H
//ImuSensor.h and ImuSensor.cpp are not class files but function prototypes and functions.
//This is because it requires other libraries that already uses classes. (i.e. LSM6, LIS3MDL, L3G, LSM303)



/*

MinIMU-9-Arduino-AHRS
Pololu MinIMU-9 + Arduino AHRS (Attitude and Heading Reference System)

Copyright (c) 2011-2016 Pololu Corporation.
http://www.pololu.com/

MinIMU-9-Arduino-AHRS is based on sf9domahrs by Doug Weibel and Jose Julio:
http://code.google.com/p/sf9domahrs/

sf9domahrs is based on ArduIMU v1.5 by Jordi Munoz and William Premerlani, Jose
Julio and Doug Weibel:
http://code.google.com/p/ardu-imu/

MinIMU-9-Arduino-AHRS is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your option)
any later version.

MinIMU-9-Arduino-AHRS is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License along
with MinIMU-9-Arduino-AHRS. If not, see <http://www.gnu.org/licenses/>.

*/













//IMU Global Variables



// Uncomment the following line to use a MinIMU-9 v5 or AltIMU-10 v5. Leave commented for older IMUs (up through v4).
//#define IMU_V5

// Uncomment the below line to use this axis definition:
// X axis pointing forward
// Y axis pointing to the right
// and Z axis pointing down.
// Positive pitch : nose up
// Positive roll : right wing down
// Positive yaw : clockwise
int SENSOR_SIGN[9] = { 1,1,1,-1,-1,-1,1,1,1 }; //Correct directions x,y,z - gyro, accelerometer, magnetometer
											   // Uncomment the below line to use this axis definition:
											   // X axis pointing forward
											   // Y axis pointing to the left
											   // and Z axis pointing up.
											   // Positive pitch : nose down
											   // Positive roll : right wing down
											   // Positive yaw : counterclockwise
											   //int SENSOR_SIGN[9] = {1,-1,-1,-1,1,1,1,-1,-1}; //Correct directions x,y,z - gyro, accelerometer, magnetometer

											   // tested with Arduino Uno with ATmega328 and Arduino Duemilanove with ATMega168


								
float G_Dt = 0.02;    // Integration time (DCM algorithm)  We will run the integration loop at 50Hz if possible


int AN[6]; //array that stores the gyro and accelerometer data
int AN_OFFSET[6] = { 0,0,0,0,0,0 }; //Array that stores the Offset of the sensors

int gyro_x;
int gyro_y;
int gyro_z;
int accel_x;
int accel_y;
int accel_z;
int magnetom_x;
int magnetom_y;
int magnetom_z;
float c_magnetom_x;
float c_magnetom_y;
float c_magnetom_z;
float MAG_Heading;

float Accel_Vector[3] = { 0,0,0 }; //Store the acceleration in a vector
float Gyro_Vector[3] = { 0,0,0 };//Store the gyros turn rate in a vector
float Omega_Vector[3] = { 0,0,0 }; //Corrected Gyro_Vector data
float Omega_P[3] = { 0,0,0 };//Omega Proportional correction
float Omega_I[3] = { 0,0,0 };//Omega Integrator
float Omega[3] = { 0,0,0 };

// Euler angles
float roll;
float pitch;
float yaw;



float errorRollPitch[3] = { 0,0,0 };
float errorYaw[3] = { 0,0,0 };
byte gyro_sat = 0;

float DCM_Matrix[3][3] = {
	{
		1,0,0 }
		,{
			0,1,0 }
			,{
				0,0,1 }
};
float Update_Matrix[3][3] = { { 0,1,2 },{ 3,4,5 },{ 6,7,8 } }; //Gyros here


float Temporary_Matrix[3][3] = {
	{
		0,0,0 }
		,{
			0,0,0 }
			,{
				0,0,0 }
};





//IMU Function Prototypes
void Compass_Heading();
float Vector_Dot_Product(float vector1[3], float vector2[3]);
void Vector_Cross_Product(float vectorOut[3], float v1[3], float v2[3]);
void Vector_Scale(float vectorOut[3], float vectorIn[3], float scale2);
void Vector_Add(float vectorOut[3], float vectorIn1[3], float vectorIn2[3]);
void printInAHRSFormat(void);
void Matrix_Multiply(float a[3][3], float b[3][3], float mat[3][3]);
void I2C_Init();
void Gyro_Init();
void Read_Gyro();
void Accel_Init();
void Read_Accel();
void Compass_Init();
void Read_Compass();
void Normalize(void);
void Drift_correction(void);
void Matrix_update(void);
void Euler_angles(void);
void Imu_Init();
void Imu_Calculations();
float getHeading();
float getRoll();
float getPitch();
float getYaw();


#endif