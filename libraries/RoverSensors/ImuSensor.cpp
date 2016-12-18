#include <ImuSensor.h>

/*
References:
http://www.pololu.com/
http://code.google.com/p/sf9domahrs/
http://code.google.com/p/ardu-imu/

*/

//==Start Of Intergrated Code From Others


ImuSensor::ImuSensor()
{
	
	//initialize variables
	this->reset();
	
}
ImuSensor::~ImuSensor()
{
	//do nothing
}		
void ImuSensor::reset() //This function just reinitializes all the variables (and not the hardware)
{
				
		//(Re)initialize variables
		
		this->_heading=0;
		
		//==Start Of Intergrated Code From Others			
		

		// Uncomment the below line to use this axis definition:
		// X axis pointing forward
		// Y axis pointing to the right
		// and Z axis pointing down.
		// Positive pitch : nose up
		// Positive roll : right wing down
		// Positive yaw : clockwise
		this->_SENSOR_SIGN[0] = 1;
		this->_SENSOR_SIGN[1] = 1;
		this->_SENSOR_SIGN[2] = 1;
		this->_SENSOR_SIGN[3] = -1;
		this->_SENSOR_SIGN[4] = -1;
		this->_SENSOR_SIGN[5] = -1;
		this->_SENSOR_SIGN[6] = 1;
		this->_SENSOR_SIGN[7] = 1;
		this->_SENSOR_SIGN[8] = 1;

		//==Start Of Intergrated Code From Others


		// Uncomment the below line to use this axis definition:
		// X axis pointing forward
		// Y axis pointing to the left
		// and Z axis pointing up.
		// Positive pitch : nose down
		// Positive roll : right wing down
		// Positive yaw : counterclockwise	
		this->_SENSOR_SIGN[0] = 1;
		this->_SENSOR_SIGN[1] = -1;
		this->_SENSOR_SIGN[2] = -1;
		this->_SENSOR_SIGN[3] = -1;
		this->_SENSOR_SIGN[4] = 1;
		this->_SENSOR_SIGN[5] = 1;
		this->_SENSOR_SIGN[6] = 1;
		this->_SENSOR_SIGN[7] = -1;
		this->_SENSOR_SIGN[8] = -1;


		this->_G_Dt=0.02;
		this->_timer=0;		

		this->_AN_OFFSET[0] = 0;
		this->_AN_OFFSET[1] = 0;
		this->_AN_OFFSET[2] = 0;
		this->_AN_OFFSET[3] = 0;
		this->_AN_OFFSET[4] = 0;
		this->_AN_OFFSET[5] = 0;
		this->_AN_OFFSET[6] = 0;	

		this->_Accel_Vector[0] = 0;
		this->_Gyro_Vector[1]= 0;
		this->_Omega_Vector[2]= 0;
		this->_Omega_P[0]= 0;
		this->_Omega_I[1]= 0;
		this->_Omega[2]= 0;			

		this->_errorRollPitch[0]= 0;
		this->_errorRollPitch[1] = 0;
		this->_errorRollPitch[2] = 0;

		this->_errorYaw[0] = 0;
		this->_errorYaw[1] = 0;
		this->_errorYaw[2] = 0;

		//this->_counter=0;		

		this->_DCM_Matrix[0][0] = 1;
		this->_DCM_Matrix[0][1] = 0;
		this->_DCM_Matrix[0][2] = 0;
		this->_DCM_Matrix[1][1] = 0;
		this->_DCM_Matrix[1][2] = 1;
		this->_DCM_Matrix[1][3] = 0;
		this->_DCM_Matrix[2][0] = 0;
		this->_DCM_Matrix[2][1] = 0;
		this->_DCM_Matrix[2][2] = 1;			

		//Gyros here
		this->_Update_Matrix[0][0] = 0;
		this->_Update_Matrix[0][1] = 1;
		this->_Update_Matrix[0][2] = 2;
		this->_Update_Matrix[1][0] = 3;
		this->_Update_Matrix[1][1] = 4;
		this->_Update_Matrix[1][2] = 5;
		this->_Update_Matrix[2][0] = 6;
		this->_Update_Matrix[2][1] = 7;
		this->_Update_Matrix[2][2] = 8;

		this->_Temporary_Matrix[0][0] = 0;
		this->_Temporary_Matrix[0][1] = 0;
		this->_Temporary_Matrix[0][2] = 0;
		this->_Temporary_Matrix[1][0] = 0;
		this->_Temporary_Matrix[1][1] = 0;
		this->_Temporary_Matrix[1][2] = 0;
		this->_Temporary_Matrix[2][0] = 0;
		this->_Temporary_Matrix[2][1] = 0;
		this->_Temporary_Matrix[2][2] = 0;		
					
		//==End Of Intergrated Code From Others
		
}
void ImuSensor::init()
{
	
	this->I2C_Init();
//DEBUG ME: FOR SOME REASON Accel_Init(); DOESN'T WORK	
	this->Accel_Init();
	this->Compass_Init();
	this->Gyro_Init();

	
	
	delay(1500);//DEBUG
	
	
Serial.println("0DEBUG");//DEBUG


//DEBUG ME: FOR SOME REASON THE CODE BELOW DOESN'T WORK

	/*
	
	// We take some readings...
	for(int i=0;i<32;i++)
    {
		this->Read_Gyro();
		this->Read_Accel();
		//Accumulate values		
		for(int y=0; y<6; y++) 
		{
			this->_AN_OFFSET[y] += this->_AN[y];
		}//end for
		delay(20);
    }//end for
	
	for(int y=0; y<6; y++)
	{
		this->_AN_OFFSET[y] = this->_AN_OFFSET[y]/32;
	}//end for
	
	this->_AN_OFFSET[5]-=IMU_GRAVITY*this->_SENSOR_SIGN[5];

  delay(2000);  

  this->_timer=millis();
  delay(20);
  //this->_counter=0;	
 
 */

	
}
void ImuSensor::printOffsets()
{
	Serial.println("Offset:");
	for(int y=0; y<6; y++)
	{
		Serial.println(this->_AN_OFFSET[y]);
	}    
}
void ImuSensor::readSensor()
{
//START OF 50 HZ BLOCK

//FINISH WRITING 50HZ BLOCK LATER
  
    //this->_counter++;
    this->_timer_old = this->_timer;
    this->_timer=millis();
    if (this->_timer>this->_timer_old)
    {
      this->_G_Dt = (this->_timer-this->_timer_old)/1000.0;    // Real time of loop run. We use this on the DCM algorithm (gyro integration time)
      if (this->_G_Dt > 0.2)
        this->_G_Dt = 0; // ignore integration times over 200 ms
    }
    else
      this->_G_Dt = 0;



    // *** DCM algorithm
    // Data adquisition
    this->Read_Gyro();   // This read gyro data
    this->Read_Accel();     // Read I2C accelerometer

    
	   
	   // Read compass data at 10Hz... (5 loop runs)
//WRITE CODE TO DO THIS AT 10 HZ for 5 times
//START OF 10 HZ BLOCK
      this->Read_Compass();    // Read I2C magnetometer
      this->Compass_Heading(); // Calculate magnetic heading
//END OF 10 HZ BLOCK




	  
    // Calculations...
    this->Matrix_update();
    this->Normalize();
    this->Drift_correction();
    this->Euler_angles();
    
  
  
//END OF 50 HZ BLOCK
  
}
float ImuSensor::getRoll()
{
	return ToDeg(this->_roll);
}
float ImuSensor::getPitch()
{
	return ToDeg(this->_pitch);
}
float ImuSensor::getYaw()
{
	return ToDeg(this->_yaw);
}
float ImuSensor::getHeading()
{
//WRITE ME
	return 0.0;//DEBUG
}
void ImuSensor::printForAHRS()
{
	  Serial.print("!");

      #if IMU_PRINT_EULER == 1
      Serial.print("ANG:");
      Serial.print(ToDeg(this->_roll));
      Serial.print(",");
      Serial.print(ToDeg(this->_pitch));
      Serial.print(",");
      Serial.print(ToDeg(this->_yaw));
      #endif      
      #if IMU_PRINT_ANALOGS==1
      Serial.print(",AN:");
      Serial.print(this->_AN[0]);  //(int)read_adc(0)
      Serial.print(",");
      Serial.print(this->_AN[1]);
      Serial.print(",");
      Serial.print(this->_AN[2]);  
      Serial.print(",");
      Serial.print(this->_AN[3]);
      Serial.print (",");
      Serial.print(this->_AN[4]);
      Serial.print (",");
      Serial.print(this->_AN[5]);
      Serial.print(",");
      Serial.print(this->_c_magnetom_x);
      Serial.print (",");
      Serial.print(this->_c_magnetom_y);
      Serial.print (",");
      Serial.print(this->_c_magnetom_z);
      #endif
      #if IMU_PRINT_DCM == 1
      Serial.print (",DCM:");
      Serial.print(this->_DCM_Matrix[0][0]);
      Serial.print (",");
      Serial.print(this->_DCM_Matrix[0][1]);
      Serial.print (",");
      Serial.print(this->_DCM_Matrix[0][2]);
      Serial.print (",");
      Serial.print(this->_DCM_Matrix[1][0]);
      Serial.print (",");
      Serial.print(this->_DCM_Matrix[1][1]);
      Serial.print (",");
      Serial.print(this->_DCM_Matrix[1][2]);
      Serial.print (",");
      Serial.print(this->_DCM_Matrix[2][0]);
      Serial.print (",");
      Serial.print(this->_DCM_Matrix[2][1]);
      Serial.print (",");
      Serial.print(this->_DCM_Matrix[2][2]);
      #endif
      Serial.println();
}
void ImuSensor::Compass_Heading()
{
  float MAG_X;
  float MAG_Y;
  float cos_roll;
  float sin_roll;
  float cos_pitch;
  float sin_pitch;
  
  cos_roll = cos(this->_roll);
  sin_roll = sin(this->_roll);
  cos_pitch = cos(this->_pitch);
  sin_pitch = sin(this->_pitch);
  
  // adjust for LSM303 compass axis offsets/sensitivity differences by scaling to +/-0.5 range
  this->_c_magnetom_x = (float)(this->_magnetom_x - this->_SENSOR_SIGN[6]*IMU_M_X_MIN) / (IMU_M_X_MAX - IMU_M_X_MIN) - this->_SENSOR_SIGN[6]*0.5;
  this->_c_magnetom_y = (float)(this->_magnetom_y - this->_SENSOR_SIGN[7]*IMU_M_Y_MIN) / (IMU_M_Y_MAX - IMU_M_Y_MIN) - this->_SENSOR_SIGN[7]*0.5;
  this->_c_magnetom_z = (float)(this->_magnetom_z - this->_SENSOR_SIGN[8]*IMU_M_Z_MIN) / (IMU_M_Z_MAX - IMU_M_Z_MIN) - this->_SENSOR_SIGN[8]*0.5;
  
  // Tilt compensated Magnetic filed X:
  MAG_X = this->_c_magnetom_x*cos_pitch+this->_c_magnetom_y*sin_roll*sin_pitch+this->_c_magnetom_z*cos_roll*sin_pitch;
  // Tilt compensated Magnetic filed Y:
  MAG_Y = this->_c_magnetom_y*cos_roll-this->_c_magnetom_z*sin_roll;
  // Magnetic Heading
  this->_MAG_Heading = atan2(-MAG_Y,MAG_X);
}

void ImuSensor::Normalize(void)
{
  float error=0;
  float temporary[3][3];
  float renorm=0;
  
  error= -this->Vector_Dot_Product(&this->_DCM_Matrix[0][0],&this->_DCM_Matrix[1][0])*.5; //eq.19

  this->Vector_Scale(&temporary[0][0], &this->_DCM_Matrix[1][0], error); //eq.19
  this->Vector_Scale(&temporary[1][0], &this->_DCM_Matrix[0][0], error); //eq.19
  
  this->Vector_Add(&temporary[0][0], &temporary[0][0], &this->_DCM_Matrix[0][0]);//eq.19
  this->Vector_Add(&temporary[1][0], &temporary[1][0], &this->_DCM_Matrix[1][0]);//eq.19
  
  this->Vector_Cross_Product(&temporary[2][0],&temporary[0][0],&temporary[1][0]); // c= a x b //eq.20
  
  renorm= .5 *(3 - this->Vector_Dot_Product(&temporary[0][0],&temporary[0][0])); //eq.21
  this->Vector_Scale(&this->_DCM_Matrix[0][0], &temporary[0][0], renorm);
  
  renorm= .5 *(3 - this->Vector_Dot_Product(&temporary[1][0],&temporary[1][0])); //eq.21
  this->Vector_Scale(&this->_DCM_Matrix[1][0], &temporary[1][0], renorm);
  
  renorm= .5 *(3 - this->Vector_Dot_Product(&temporary[2][0],&temporary[2][0])); //eq.21
  this->Vector_Scale(&this->_DCM_Matrix[2][0], &temporary[2][0], renorm);
}

void ImuSensor::Drift_correction(void)
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
  Accel_magnitude = sqrt(this->_Accel_Vector[0]*this->_Accel_Vector[0] + this->_Accel_Vector[1]*this->_Accel_Vector[1] + this->_Accel_Vector[2]*this->_Accel_Vector[2]);
  Accel_magnitude = Accel_magnitude / IMU_GRAVITY; // Scale to gravity.
  // Dynamic weighting of accelerometer info (reliability filter)
  // Weight for accelerometer info (<0.5G = 0.0, 1G = 1.0 , >1.5G = 0.0)
  Accel_weight = constrain(1 - 2*abs(1 - Accel_magnitude),0,1);  //  

  this->Vector_Cross_Product(&this->_errorRollPitch[0],&this->_Accel_Vector[0],&this->_DCM_Matrix[2][0]); //adjust the ground of reference
  this->Vector_Scale(&this->_Omega_P[0],&this->_errorRollPitch[0],IMU_Kp_ROLLPITCH*Accel_weight);
  
  this->Vector_Scale(&Scaled_Omega_I[0],&this->_errorRollPitch[0],IMU_Ki_ROLLPITCH*Accel_weight);
  this->Vector_Add(this->_Omega_I,this->_Omega_I,Scaled_Omega_I);     
  
  //*****YAW***************
  // We make the gyro YAW drift correction based on compass magnetic heading
 
  mag_heading_x = cos(this->_MAG_Heading);
  mag_heading_y = sin(this->_MAG_Heading);
  errorCourse=(this->_DCM_Matrix[0][0]*mag_heading_y) - (this->_DCM_Matrix[1][0]*mag_heading_x);  //Calculating YAW error
  this->Vector_Scale(this->_errorYaw,&this->_DCM_Matrix[2][0],errorCourse); //Applys the yaw correction to the XYZ rotation of the aircraft, depeding the position.
  
  this->Vector_Scale(&Scaled_Omega_P[0],&this->_errorYaw[0],IMU_Kp_YAW);//.01proportional of YAW.
  this->Vector_Add(this->_Omega_P,this->_Omega_P,Scaled_Omega_P);//Adding  Proportional.
  
  this->Vector_Scale(&Scaled_Omega_I[0],&this->_errorYaw[0],IMU_Ki_YAW);//.00001Integrator
  this->Vector_Add(this->_Omega_I,this->_Omega_I,Scaled_Omega_I);//adding integrator to the this->_Omega_I
}

void ImuSensor::Matrix_update(void)
{
  this->_Gyro_Vector[0]=Gyro_Scaled_X(this->_gyro_x); //gyro x roll
  this->_Gyro_Vector[1]=Gyro_Scaled_Y(this->_gyro_y); //gyro y pitch
  this->_Gyro_Vector[2]=Gyro_Scaled_Z(this->_gyro_z); //gyro Z yaw
  
  this->_Accel_Vector[0]=this->_accel_x;
  this->_Accel_Vector[1]=this->_accel_y;
  this->_Accel_Vector[2]=this->_accel_z;
    
  this->Vector_Add(&this->_Omega[0], &this->_Gyro_Vector[0], &this->_Omega_I[0]);  //adding proportional term
  this->Vector_Add(&this->_Omega_Vector[0], &this->_Omega[0], &this->_Omega_P[0]); //adding Integrator term
  
 #if IMU_OUTPUTMODE==1         
  this->_Update_Matrix[0][0]=0;
  this->_Update_Matrix[0][1]=-this->_G_Dt*this->_Omega_Vector[2];//-z
  this->_Update_Matrix[0][2]=this->_G_Dt*this->_Omega_Vector[1];//y
  this->_Update_Matrix[1][0]=this->_G_Dt*this->_Omega_Vector[2];//z
  this->_Update_Matrix[1][1]=0;
  this->_Update_Matrix[1][2]=-this->_G_Dt*this->_Omega_Vector[0];//-x
  this->_Update_Matrix[2][0]=-this->_G_Dt*this->_Omega_Vector[1];//-y
  this->_Update_Matrix[2][1]=this->_G_Dt*this->_Omega_Vector[0];//x
  this->_Update_Matrix[2][2]=0;
 #else                    // Uncorrected data (no drift correction)
  this->_Update_Matrix[0][0]=0;
  this->_Update_Matrix[0][1]=-this->_G_Dt*this->_Gyro_Vector[2];//-z
  this->_Update_Matrix[0][2]=this->_G_Dt*this->_Gyro_Vector[1];//y
  this->_Update_Matrix[1][0]=this->_G_Dt*this->_Gyro_Vector[2];//z
  this->_Update_Matrix[1][1]=0;
  this->_Update_Matrix[1][2]=-this->_G_Dt*this->_Gyro_Vector[0];
  this->_Update_Matrix[2][0]=-this->_G_Dt*this->_Gyro_Vector[1];
  this->_Update_Matrix[2][1]=this->_G_Dt*this->_Gyro_Vector[0];
  this->_Update_Matrix[2][2]=0;
 #endif

  this->Matrix_Multiply(this->_DCM_Matrix,this->_Update_Matrix,this->_Temporary_Matrix); //a*b=c

  for(int x=0; x<3; x++) //Matrix Addition (update)
  {
    for(int y=0; y<3; y++)
    {
      this->_DCM_Matrix[x][y]+=this->_Temporary_Matrix[x][y];
    } 
  }
}

void ImuSensor::Euler_angles(void)
{
  this->_pitch = -asin(this->_DCM_Matrix[2][0]);
  this->_roll = atan2(this->_DCM_Matrix[2][1],this->_DCM_Matrix[2][2]);
  this->_yaw = atan2(this->_DCM_Matrix[1][0],this->_DCM_Matrix[0][0]);
}

void ImuSensor::Accel_Init()
{
	
#ifdef IMU_V5

  this->_gyro_acc->init();
  this->_gyro_acc->enableDefault();
  this->_gyro_acc->writeReg(LSM6::CTRL1_XL, 0x3C); // 52 Hz, 8 g full scale
#else

  //this->_compass->init();  

  this->_compass->enableDefault();
   
  switch (this->_compass->getDeviceType())
  {
    case LSM303::device_D:
      this->_compass->writeReg(LSM303::CTRL2, 0x18); // 8 g full scale: AFS = 011
      break;
    case LSM303::device_DLHC:
      this->_compass->writeReg(LSM303::CTRL_REG4_A, 0x28); // 8 g full scale: FS = 10; high resolution output mode
      break;
    default: // DLM, DLH
      this->_compass->writeReg(LSM303::CTRL_REG4_A, 0x30); // 8 g full scale: FS = 11
  }

#endif
}

void ImuSensor::Compass_Init()
{
#ifdef IMU_V5
  this->_mag->init();
  this->_mag->enableDefault();
#else
  // LSM303: doesn't need to do anything because this->Accel_Init() should have already called this->_compass->enableDefault()
#endif
}

void ImuSensor::Gyro_Init()
{
#ifdef IMU_V5
  // this->Accel_Init() should have already called this->_gyro_acc->init() and enableDefault()
  this->_gyro_acc->writeReg(LSM6::CTRL2_G, 0x4C); // 104 Hz, 2000 dps full scale
#else
  this->_gyro->init();
  this->_gyro->enableDefault();
  this->_gyro->writeReg(L3G::CTRL_REG4, 0x20); // 2000 dps full scale
  this->_gyro->writeReg(L3G::CTRL_REG1, 0x0F); // normal power mode, all axes enabled, 100 Hz
#endif
}

void ImuSensor::I2C_Init()
{
  Wire.begin();
}

void ImuSensor::Read_Gyro()
{
#ifdef IMU_V5
  this->_gyro_acc->readGyro();

  this->_AN[0] = this->_gyro_acc->g.x;
  this->_AN[1] = this->_gyro_acc->g.y;
  this->_AN[2] = this->_gyro_acc->g.z;
#else
  this->_gyro->read();

  this->_AN[0] = this->_gyro->g.x;
  this->_AN[1] = this->_gyro->g.y;
  this->_AN[2] = this->_gyro->g.z;
#endif

  this->_gyro_x = this->_SENSOR_SIGN[0] * (this->_AN[0] - this->_AN_OFFSET[0]);
  this->_gyro_y = this->_SENSOR_SIGN[1] * (this->_AN[1] - this->_AN_OFFSET[1]);
  this->_gyro_z = this->_SENSOR_SIGN[2] * (this->_AN[2] - this->_AN_OFFSET[2]);
}

// Reads x,y and z accelerometer registers
void ImuSensor::Read_Accel()
{
#ifdef IMU_V5
  this->_gyro_acc->readAcc();

  this->_AN[3] = this->_gyro_acc->a.x >> 4; // shift left 4 bits to use 12-bit representation (1 g = 256)
  this->_AN[4] = this->_gyro_acc->a.y >> 4;
  this->_AN[5] = this->_gyro_acc->a.z >> 4;
#else
  this->_compass->readAcc();

  this->_AN[3] = this->_compass->a.x >> 4; // shift left 4 bits to use 12-bit representation (1 g = 256)
  this->_AN[4] = this->_compass->a.y >> 4;
  this->_AN[5] = this->_compass->a.z >> 4;
#endif
  this->_accel_x = this->_SENSOR_SIGN[3] * (this->_AN[3] - this->_AN_OFFSET[3]);
  this->_accel_y = this->_SENSOR_SIGN[4] * (this->_AN[4] - this->_AN_OFFSET[4]);
  this->_accel_z = this->_SENSOR_SIGN[5] * (this->_AN[5] - this->_AN_OFFSET[5]);
}

void ImuSensor::Read_Compass()
{
#ifdef IMU_V5
  this->_mag->read();

  this->_magnetom_x = this->_SENSOR_SIGN[6] * this->_mag->m.x;
  this->_magnetom_y = this->_SENSOR_SIGN[7] * this->_mag->m.y;
  this->_magnetom_z = this->_SENSOR_SIGN[8] * this->_mag->m.z;
#else
  this->_compass->readMag();

  this->_magnetom_x = this->_SENSOR_SIGN[6] * this->_compass->m.x;
  this->_magnetom_y = this->_SENSOR_SIGN[7] * this->_compass->m.y;
  this->_magnetom_z = this->_SENSOR_SIGN[8] * this->_compass->m.z;
#endif
}
//Multiply two 3x3 matrixs. This function developed by Jordi can be easily adapted to multiple n*n matrix's. (Pero me da flojera!). 
void ImuSensor::Matrix_Multiply(float a[3][3], float b[3][3], float mat[3][3])
{
  for(int x = 0; x < 3; x++)
  {
    for(int y = 0; y < 3; y++)
    {
      mat[x][y] = 0;
      
      for(int w = 0; w < 3; w++)
      {
        mat[x][y] += a[x][w] * b[w][y];
      } 
    }
  }
}
//Computes the dot product of two vectors
float ImuSensor::Vector_Dot_Product(float vector1[3],float vector2[3])
{
  float op=0;
  
  for(int c=0; c<3; c++)
  {
	op+=vector1[c]*vector2[c];
  }  
  return op; 
}
//Computes the cross product of two vectors
void ImuSensor::Vector_Cross_Product(float vectorOut[3], float v1[3],float v2[3])
{
  vectorOut[0]= (v1[1]*v2[2]) - (v1[2]*v2[1]);
  vectorOut[1]= (v1[2]*v2[0]) - (v1[0]*v2[2]);
  vectorOut[2]= (v1[0]*v2[1]) - (v1[1]*v2[0]);
}
//Multiply the vector by a scalar
void ImuSensor::Vector_Scale(float vectorOut[3],float vectorIn[3], float scale2)
{
  for(int c=0; c<3; c++)
  {
   vectorOut[c]=vectorIn[c]*scale2; 
  }
}
//Adds Vectors
void ImuSensor::Vector_Add(float vectorOut[3],float vectorIn1[3], float vectorIn2[3])
{
  for(int c=0; c<3; c++)
  {
     vectorOut[c]=vectorIn1[c]+vectorIn2[c];
  }
}
//==End Of Intergrated Code From Others