//ImuSensor.cpp


//uncomment to print debugging information
//Note: Since ImuSensor.cpp isn't calling ImuSensor.h (since global variables define it in and can't have duplication since ImuSensor.h is called by the main .ino file already), then put this debug verbose flag here
//#define _DEBUG_VERBOSE

//Uncomment to debug
//#define _DEBUG_COMM_BROADCAST //Debugging with COMM Broadcast




#include <Arduino.h>
#include <Wire.h>
//Note: Since ImuSensor.cpp isn't calling ImuSensor.h, then some of the headers and definitions have to be called here (again)
#define _IMU_DEFINITIONS
#define _IMU_CALIBRATIONS
#include <RoverCalibration.h>
#include <RoverConfig.h>


//IMU Variable Externally (Already) Defined Variables
extern int SENSOR_SIGN[9];
extern float G_Dt;
extern int AN[6];
extern int AN_OFFSET[6];
extern int gyro_x;
extern int gyro_y;
extern int gyro_z;
extern int accel_x;
extern int accel_y;
extern int accel_z;
extern int magnetom_x;
extern int magnetom_y;
extern int magnetom_z;
extern float c_magnetom_x;
extern float c_magnetom_y;
extern float c_magnetom_z;
extern float MAG_Heading;
extern float Accel_Vector[3];
extern float Gyro_Vector[3];
extern float Omega_Vector[3];
extern float Omega_P[3];
extern float Omega_I[3];
extern float Omega[3];
extern float roll;
extern float pitch;
extern float yaw;
extern float errorRollPitch[3];
extern float errorYaw[3];
extern byte gyro_sat;
extern float DCM_Matrix[3][3];
extern float Update_Matrix[3][3];
extern float Temporary_Matrix[3][3];




//IMU Function Definitions


void Compass_Heading()
{
	float MAG_X;
	float MAG_Y;
	float cos_roll;
	float sin_roll;
	float cos_pitch;
	float sin_pitch;

	cos_roll = cos(roll);
	sin_roll = sin(roll);
	cos_pitch = cos(pitch);
	sin_pitch = sin(pitch);

	// adjust for LSM303 compass axis offsets/sensitivity differences by scaling to +/-0.5 range
	c_magnetom_x = (float)(magnetom_x - SENSOR_SIGN[6] * M_X_MIN) / (M_X_MAX - M_X_MIN) - SENSOR_SIGN[6] * 0.5;
	c_magnetom_y = (float)(magnetom_y - SENSOR_SIGN[7] * M_Y_MIN) / (M_Y_MAX - M_Y_MIN) - SENSOR_SIGN[7] * 0.5;
	c_magnetom_z = (float)(magnetom_z - SENSOR_SIGN[8] * M_Z_MIN) / (M_Z_MAX - M_Z_MIN) - SENSOR_SIGN[8] * 0.5;

	// Tilt compensated Magnetic filed X:
	MAG_X = c_magnetom_x*cos_pitch + c_magnetom_y*sin_roll*sin_pitch + c_magnetom_z*cos_roll*sin_pitch;
	// Tilt compensated Magnetic filed Y:
	MAG_Y = c_magnetom_y*cos_roll - c_magnetom_z*sin_roll;
	// Magnetic Heading
	MAG_Heading = atan2(-MAG_Y, MAG_X);
}


//Computes the dot product of two vectors
float Vector_Dot_Product(float vector1[3], float vector2[3])
{
	float op = 0;

	for (int c = 0; c<3; c++)
	{
		op += vector1[c] * vector2[c];
	}

	return op;
}

//Computes the cross product of two vectors
void Vector_Cross_Product(float vectorOut[3], float v1[3], float v2[3])
{
	vectorOut[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
	vectorOut[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
	vectorOut[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
}

//Multiply the vector by a scalar. 
void Vector_Scale(float vectorOut[3], float vectorIn[3], float scale2)
{
	for (int c = 0; c<3; c++)
	{
		vectorOut[c] = vectorIn[c] * scale2;
	}
}

void Vector_Add(float vectorOut[3], float vectorIn1[3], float vectorIn2[3])
{
	for (int c = 0; c<3; c++)
	{
		vectorOut[c] = vectorIn1[c] + vectorIn2[c];
	}
}


void Matrix_Multiply(float a[3][3], float b[3][3], float mat[3][3])
{
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			mat[x][y] = 0;

			for (int w = 0; w < 3; w++)
			{
				mat[x][y] += a[x][w] * b[w][y];
			}
		}
	}
}




#ifdef IMU_V5

#include <LSM6.h>
#include <LIS3MDL.h>

LSM6 gyro_acc;
LIS3MDL mag;

#else // older IMUs through v4

#include <L3G.h>
#include <LSM303.h>

L3G gyro;
LSM303 compass;

#endif


void I2C_Init()
{
	Wire.begin();
}

void Gyro_Init()
{
#ifdef IMU_V5
	// Accel_Init() should have already called gyro_acc.init() and enableDefault()
	gyro_acc.writeReg(LSM6::CTRL2_G, 0x4C); // 104 Hz, 2000 dps full scale
#else
	gyro.init();
	gyro.enableDefault();
	gyro.writeReg(L3G::CTRL_REG4, 0x20); // 2000 dps full scale
	gyro.writeReg(L3G::CTRL_REG1, 0x0F); // normal power mode, all axes enabled, 100 Hz
#endif
}

void Read_Gyro()
{
#ifdef IMU_V5
	gyro_acc.readGyro();

	AN[0] = gyro_acc.g.x;
	AN[1] = gyro_acc.g.y;
	AN[2] = gyro_acc.g.z;
#else
	gyro.read();

	AN[0] = gyro.g.x;
	AN[1] = gyro.g.y;
	AN[2] = gyro.g.z;
#endif

	gyro_x = SENSOR_SIGN[0] * (AN[0] - AN_OFFSET[0]);
	gyro_y = SENSOR_SIGN[1] * (AN[1] - AN_OFFSET[1]);
	gyro_z = SENSOR_SIGN[2] * (AN[2] - AN_OFFSET[2]);
}

void Accel_Init()
{
#ifdef IMU_V5
	gyro_acc.init();
	gyro_acc.enableDefault();
	gyro_acc.writeReg(LSM6::CTRL1_XL, 0x3C); // 52 Hz, 8 g full scale
#else
	compass.init();
	compass.enableDefault();
	switch (compass.getDeviceType())
	{
	case LSM303::device_D:
		compass.writeReg(LSM303::CTRL2, 0x18); // 8 g full scale: AFS = 011
		break;
	case LSM303::device_DLHC:
		compass.writeReg(LSM303::CTRL_REG4_A, 0x28); // 8 g full scale: FS = 10; high resolution output mode
		break;
	default: // DLM, DLH
		compass.writeReg(LSM303::CTRL_REG4_A, 0x30); // 8 g full scale: FS = 11
	}
#endif
}

// Reads x,y and z accelerometer registers
void Read_Accel()
{
#ifdef IMU_V5
	gyro_acc.readAcc();

	AN[3] = gyro_acc.a.x >> 4; // shift left 4 bits to use 12-bit representation (1 g = 256)
	AN[4] = gyro_acc.a.y >> 4;
	AN[5] = gyro_acc.a.z >> 4;
#else
	compass.readAcc();

	AN[3] = compass.a.x >> 4; // shift left 4 bits to use 12-bit representation (1 g = 256)
	AN[4] = compass.a.y >> 4;
	AN[5] = compass.a.z >> 4;
#endif
	accel_x = SENSOR_SIGN[3] * (AN[3] - AN_OFFSET[3]);
	accel_y = SENSOR_SIGN[4] * (AN[4] - AN_OFFSET[4]);
	accel_z = SENSOR_SIGN[5] * (AN[5] - AN_OFFSET[5]);
}

void Compass_Init()
{
#ifdef IMU_V5
	mag.init();
	mag.enableDefault();
#else
	// LSM303: doesn't need to do anything because Accel_Init() should have already called compass.enableDefault()
#endif
}

void Read_Compass()
{
#ifdef IMU_V5
	mag.read();

	magnetom_x = SENSOR_SIGN[6] * mag.m.x;
	magnetom_y = SENSOR_SIGN[7] * mag.m.y;
	magnetom_z = SENSOR_SIGN[8] * mag.m.z;
#else
	compass.readMag();

	magnetom_x = SENSOR_SIGN[6] * compass.m.x;
	magnetom_y = SENSOR_SIGN[7] * compass.m.y;
	magnetom_z = SENSOR_SIGN[8] * compass.m.z;
#endif
}

void Normalize(void)
{
	float error = 0;
	float temporary[3][3];
	float renorm = 0;

	error = -Vector_Dot_Product(&DCM_Matrix[0][0], &DCM_Matrix[1][0])*.5; //eq.19

	Vector_Scale(&temporary[0][0], &DCM_Matrix[1][0], error); //eq.19
	Vector_Scale(&temporary[1][0], &DCM_Matrix[0][0], error); //eq.19

	Vector_Add(&temporary[0][0], &temporary[0][0], &DCM_Matrix[0][0]);//eq.19
	Vector_Add(&temporary[1][0], &temporary[1][0], &DCM_Matrix[1][0]);//eq.19

	Vector_Cross_Product(&temporary[2][0], &temporary[0][0], &temporary[1][0]); // c= a x b //eq.20

	renorm = .5 *(3 - Vector_Dot_Product(&temporary[0][0], &temporary[0][0])); //eq.21
	Vector_Scale(&DCM_Matrix[0][0], &temporary[0][0], renorm);

	renorm = .5 *(3 - Vector_Dot_Product(&temporary[1][0], &temporary[1][0])); //eq.21
	Vector_Scale(&DCM_Matrix[1][0], &temporary[1][0], renorm);

	renorm = .5 *(3 - Vector_Dot_Product(&temporary[2][0], &temporary[2][0])); //eq.21
	Vector_Scale(&DCM_Matrix[2][0], &temporary[2][0], renorm);
}

/**************************************************/
void Drift_correction(void)
{
	float mag_heading_x;
	float mag_heading_y;
	float errorCourse;
	//Compensation the Roll, Pitch and Yaw drift. 
	static float Scaled_Omega_P[3];
	static float Scaled_Omega_I[3];
	float Accel_magnitude;
	float Accel_weight;


	//*****Roll and Pitch***************

	// Calculate the magnitude of the accelerometer vector
	Accel_magnitude = sqrt(Accel_Vector[0] * Accel_Vector[0] + Accel_Vector[1] * Accel_Vector[1] + Accel_Vector[2] * Accel_Vector[2]);
	Accel_magnitude = Accel_magnitude / GRAVITY; // Scale to gravity.
												 // Dynamic weighting of accelerometer info (reliability filter)
												 // Weight for accelerometer info (<0.5G = 0.0, 1G = 1.0 , >1.5G = 0.0)
	Accel_weight = constrain(1 - 2 * abs(1 - Accel_magnitude), 0, 1);  //  

	Vector_Cross_Product(&errorRollPitch[0], &Accel_Vector[0], &DCM_Matrix[2][0]); //adjust the ground of reference
	Vector_Scale(&Omega_P[0], &errorRollPitch[0], Kp_ROLLPITCH*Accel_weight);

	Vector_Scale(&Scaled_Omega_I[0], &errorRollPitch[0], Ki_ROLLPITCH*Accel_weight);
	Vector_Add(Omega_I, Omega_I, Scaled_Omega_I);

	//*****YAW***************
	// We make the gyro YAW drift correction based on compass magnetic heading

	mag_heading_x = cos(MAG_Heading);
	mag_heading_y = sin(MAG_Heading);
	errorCourse = (DCM_Matrix[0][0] * mag_heading_y) - (DCM_Matrix[1][0] * mag_heading_x);  //Calculating YAW error
	Vector_Scale(errorYaw, &DCM_Matrix[2][0], errorCourse); //Applys the yaw correction to the XYZ rotation of the aircraft, depeding the position.

	Vector_Scale(&Scaled_Omega_P[0], &errorYaw[0], Kp_YAW);//.01proportional of YAW.
	Vector_Add(Omega_P, Omega_P, Scaled_Omega_P);//Adding  Proportional.

	Vector_Scale(&Scaled_Omega_I[0], &errorYaw[0], Ki_YAW);//.00001Integrator
	Vector_Add(Omega_I, Omega_I, Scaled_Omega_I);//adding integrator to the Omega_I
}

void Matrix_update(void)
{
	Gyro_Vector[0] = Gyro_Scaled_X(gyro_x); //gyro x roll
	Gyro_Vector[1] = Gyro_Scaled_Y(gyro_y); //gyro y pitch
	Gyro_Vector[2] = Gyro_Scaled_Z(gyro_z); //gyro Z yaw

	Accel_Vector[0] = accel_x;
	Accel_Vector[1] = accel_y;
	Accel_Vector[2] = accel_z;

	Vector_Add(&Omega[0], &Gyro_Vector[0], &Omega_I[0]);  //adding proportional term
	Vector_Add(&Omega_Vector[0], &Omega[0], &Omega_P[0]); //adding Integrator term

														  //Accel_adjust();    //Remove centrifugal acceleration.   We are not using this function in this version - we have no speed measurement

#if OUTPUTMODE==1         
	Update_Matrix[0][0] = 0;
	Update_Matrix[0][1] = -G_Dt*Omega_Vector[2];//-z
	Update_Matrix[0][2] = G_Dt*Omega_Vector[1];//y
	Update_Matrix[1][0] = G_Dt*Omega_Vector[2];//z
	Update_Matrix[1][1] = 0;
	Update_Matrix[1][2] = -G_Dt*Omega_Vector[0];//-x
	Update_Matrix[2][0] = -G_Dt*Omega_Vector[1];//-y
	Update_Matrix[2][1] = G_Dt*Omega_Vector[0];//x
	Update_Matrix[2][2] = 0;
#else                    // Uncorrected data (no drift correction)
	Update_Matrix[0][0] = 0;
	Update_Matrix[0][1] = -G_Dt*Gyro_Vector[2];//-z
	Update_Matrix[0][2] = G_Dt*Gyro_Vector[1];//y
	Update_Matrix[1][0] = G_Dt*Gyro_Vector[2];//z
	Update_Matrix[1][1] = 0;
	Update_Matrix[1][2] = -G_Dt*Gyro_Vector[0];
	Update_Matrix[2][0] = -G_Dt*Gyro_Vector[1];
	Update_Matrix[2][1] = G_Dt*Gyro_Vector[0];
	Update_Matrix[2][2] = 0;
#endif

	Matrix_Multiply(DCM_Matrix, Update_Matrix, Temporary_Matrix); //a*b=c

	for (int x = 0; x<3; x++) //Matrix Addition (update)
	{
		for (int y = 0; y<3; y++)
		{
			DCM_Matrix[x][y] += Temporary_Matrix[x][y];
		}
	}
}

void Euler_angles(void)
{
	pitch = -asin(DCM_Matrix[2][0]);
	roll = atan2(DCM_Matrix[2][1], DCM_Matrix[2][2]);
	yaw = atan2(DCM_Matrix[1][0], DCM_Matrix[0][0]);
}


void Imu_Init()
{
	I2C_Init();
	Accel_Init();
	Compass_Init();
	Gyro_Init();
	
	delay(20);

	for (int i = 0; i<32; i++)    // We take some readings...
	{
		Read_Gyro();
		Read_Accel();
		for (int y = 0; y<6; y++)   // Cumulate values
			AN_OFFSET[y] += AN[y];
		delay(20);
	}

	for (int y = 0; y<6; y++)
		AN_OFFSET[y] = AN_OFFSET[y] / 32;

	AN_OFFSET[5] -= GRAVITY*SENSOR_SIGN[5];	
	
	#ifdef _DEBUG_VERBOSE
		Serial.println(F("IMU Offset Values:"));
		for (int y = 0; y<6; y++)
			Serial.println(AN_OFFSET[y]);
	#endif	
}


void Imu_Calculations()
{
	Matrix_update();
	Normalize();
	Drift_correction();
	Euler_angles();
	
	
}


float getCorrectedHeading()
{
	//heading is corrected by 180 degrees due to the mounting of the IMU sensor
	//also a correction calibration (transfer) function has been applied to make the numbers more accurate. It was based on approximated empircal measurements)
	//See: K:\Working Directory\DESIGN_PROJ\Design Projects\Robot\My Notes\My Studies\IMU Calibration
		
	float cumulativeSum = 0.0;
	
	for(byte i = 0; i < HEADING_SAMPLE_SIZE ; i++)
	{
			cumulativeSum += compass.heading();
	}
	
	
	float value = cumulativeSum / HEADING_SAMPLE_SIZE;//take the average value of the raw compass headings
	
	
	value = fmod(value + 180.0, 360.0);//adjust for inverted direction, and for ce to fit in the range of 0 to 360
	
    value = fmod((-0.0021*value*value + 1.7305 * value - 52.033) + 360.0, 360.0);//adjust due to calibration and force to fit in the range of 0 to 360
	return value;
	
}


float getHeading()
{
	return compass.heading();
}

float getRoll()
{
	return ToDeg(roll);
}


float getPitch()
{
	return ToDeg(pitch);
}


float getYaw()
{
	return ToDeg(yaw);
}



void printInAHRSFormat(void)
{
#ifdef _DEBUG_COMM_BROADCAST
		
	Serial2.print("!");

	#if PRINT_EULER == 1
		Serial2.print("ANG:");
		Serial2.print(getRoll());
		Serial2.print(",");
		Serial2.print(getPitch());
		Serial2.print(",");
		Serial2.print(getYaw());
			
	#endif      
	#if PRINT_ANALOGS==1
		Serial2.print(",AN:");
		Serial2.print(AN[0]);  //(int)read_adc(0)
		Serial2.print(",");
		Serial2.print(AN[1]);
		Serial2.print(",");
		Serial2.print(AN[2]);
		Serial2.print(",");
		Serial2.print(AN[3]);
		Serial2.print(",");
		Serial2.print(AN[4]);
		Serial2.print(",");
		Serial2.print(AN[5]);
		Serial2.print(",");
		Serial2.print(c_magnetom_x);
		Serial2.print(",");
		Serial2.print(c_magnetom_y);
		Serial2.print(",");
		Serial2.print(c_magnetom_z);
	#endif
	#if PRINT_DCM == 1
		Serial2.print(",DCM:");
		Serial2.print(DCM_Matrix[0][0]);
		Serial2.print(",");
		Serial2.print(DCM_Matrix[0][1]);
		Serial2.print(",");
		Serial2.print(DCM_Matrix[0][2]);
		Serial2.print(",");
		Serial2.print(DCM_Matrix[1][0]);
		Serial2.print(",");
		Serial2.print(DCM_Matrix[1][1]);
		Serial2.print(",");
		Serial2.print(DCM_Matrix[1][2]);
		Serial2.print(",");
		Serial2.print(DCM_Matrix[2][0]);
		Serial2.print(",");
		Serial2.print(DCM_Matrix[2][1]);
		Serial2.print(",");
		Serial2.print(DCM_Matrix[2][2]);
	#endif
	Serial2.println();	
#else
		
	Serial.print("!");

	#if PRINT_EULER == 1
		Serial.print("ANG:");
		Serial.print(getRoll());
		Serial.print(",");
		Serial.print(getPitch());
		Serial.print(",");
		Serial.print(getYaw());
			
	#endif      
	#if PRINT_ANALOGS==1
		Serial.print(",AN:");
		Serial.print(AN[0]);  //(int)read_adc(0)
		Serial.print(",");
		Serial.print(AN[1]);
		Serial.print(",");
		Serial.print(AN[2]);
		Serial.print(",");
		Serial.print(AN[3]);
		Serial.print(",");
		Serial.print(AN[4]);
		Serial.print(",");
		Serial.print(AN[5]);
		Serial.print(",");
		Serial.print(c_magnetom_x);
		Serial.print(",");
		Serial.print(c_magnetom_y);
		Serial.print(",");
		Serial.print(c_magnetom_z);
	#endif
	#if PRINT_DCM == 1
		Serial.print(",DCM:");
		Serial.print(DCM_Matrix[0][0]);
		Serial.print(",");
		Serial.print(DCM_Matrix[0][1]);
		Serial.print(",");
		Serial.print(DCM_Matrix[0][2]);
		Serial.print(",");
		Serial.print(DCM_Matrix[1][0]);
		Serial.print(",");
		Serial.print(DCM_Matrix[1][1]);
		Serial.print(",");
		Serial.print(DCM_Matrix[1][2]);
		Serial.print(",");
		Serial.print(DCM_Matrix[2][0]);
		Serial.print(",");
		Serial.print(DCM_Matrix[2][1]);
		Serial.print(",");
		Serial.print(DCM_Matrix[2][2]);
	#endif
	Serial.println();		
#endif


}