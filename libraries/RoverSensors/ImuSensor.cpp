#include <ImuSensor.h>


ImuSensor::ImuSensor()
{
	//Required by the Gyro and Compass
	Wire.begin();
	
	//create the ImuGyro, ImuAccelerometer, and ImuCompass objects
	this->_imuGyro = new ImuGyro();
	this->_imuAccelerometer = new ImuAccelerometer();
	this->_imuCompass = new ImuCompass();
	
	this->_resetArray[0] = this->_imuGyro;
	this->_resetArray[1] = this->_imuAccelerometer;
	this->_resetArray[2] = this->_imuCompass;	
	
	
	//initialize the arrays
	this->_compassHeading = 0;
	
	this->_gyroXYZData[X_DATA] = 0;
	this->_gyroXYZData[Y_DATA] = 0;
	this->_gyroXYZData[Z_DATA] = 0;
		
	this->_accelerometerXYZData[X_DATA] = 0;
	this->_accelerometerXYZData[Y_DATA] = 0;
	this->_accelerometerXYZData[Z_DATA] = 0;
	
}
ImuSensor::~ImuSensor()
{
	//do nothing
}
bool ImuSensor::init()
{
	if(!this->_imuGyro->init())
	{
		return false;//when gyro fails to initialize
	}
	if(!this->_imuAccelerometer->init())
	{
		return false;//when accelerometer fails to initialize
	}	
	if(!this->_imuCompass->init())
	{
		return false;//when compass fails to initialize
	}
	return true;//when all are successful
	
}
void ImuSensor::reset()
{
	//Resetting all muxes
	for (byte i = 0; i < sizeof(this->_resetArray) / sizeof(this->_resetArray[0]); i++)
	{
		this->_resetArray[i]->reset();
	}
	
	
	//Reset the Compass heading
	this->_compassHeading = 0;
	
		
	//Reset the Gyro data array
	this->_gyroXYZData[X_DATA] = 0;
	this->_gyroXYZData[Y_DATA] = 0;
	this->_gyroXYZData[Z_DATA] = 0;
				
	//Reset the Accelerometer data array
	this->_accelerometerXYZData[X_DATA] = 0;
	this->_accelerometerXYZData[Y_DATA] = 0;
	this->_accelerometerXYZData[Z_DATA] = 0;

	
}
void ImuSensor::readSensor()
{

	//Read the sensor data
	this->_imuGyro->readSensor();
	this->_imuAccelerometer->readSensor();
	this->_imuCompass->readSensor();

	//Store the Compass Converted Data
	this->_compassHeading = _imuCompass->getCompassHeading();
		
	//Store the Gyro Converted Data
	this->_gyroXYZData[X_DATA] = _imuGyro->getXValue();
	this->_gyroXYZData[Y_DATA] = _imuGyro->getYValue();
	this->_gyroXYZData[Z_DATA] = _imuGyro->getZValue();
				
	//Store the Accelerometer Converted Data		
	this->_accelerometerXYZData[X_DATA] = _imuAccelerometer->getXValue();
	this->_accelerometerXYZData[Y_DATA] = _imuAccelerometer->getYValue();
	this->_accelerometerXYZData[Z_DATA] = _imuAccelerometer->getZValue();
				
	return;
}



void ImuSensor::getGyroXYZData(int gyroXYZData[])
{
	//copy the array values over	
	gyroXYZData[X_DATA] = this->_gyroXYZData[X_DATA];
	gyroXYZData[Y_DATA] = this->_gyroXYZData[Y_DATA];
	gyroXYZData[Z_DATA] = this->_gyroXYZData[Z_DATA];	
	return;
}
//void ImuSensor::getAccelerometerData(int accelerometerData[])
void ImuSensor::getAccelerometerXYZData(int accelerometerXYZData[])
{	
	//copy the array values over
	accelerometerXYZData[X_DATA] = this->_accelerometerXYZData[X_DATA];
	accelerometerXYZData[Y_DATA] = this->_accelerometerXYZData[Y_DATA];
	accelerometerXYZData[Z_DATA] = this->_accelerometerXYZData[Z_DATA];	
	return;
}

float ImuSensor::getCompassHeading()// returns the angular difference in the horizontal plane between a default vector and north, in degrees.
{
	return this->_compassHeading;
}

