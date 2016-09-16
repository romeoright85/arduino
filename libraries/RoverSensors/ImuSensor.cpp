#include <ImuSensor.h>


ImuSensor::ImuSensor()
{
	//create the ImuGyro, ImuAccelerometer, and ImuCompass objects
	this->_imuGyro = new ImuGyro();
	this->_imuAccelerometer = new ImuAccelerometer();
	this->_imuCompass = new ImuCompass();
	
	this->_resetArray[0] = this->_imuGyro;
	this->_resetArray[1] = this->_imuAccelerometer;
	this->_resetArray[2] = this->_imuCompass;	
	
	
	//initialize the arrays
	this->_compassData[X_DATA] = 0;
	this->_compassData[Y_DATA] = 0;
	this->_compassData[Z_DATA] = 0;
	
	this->_gyroData[X_DATA] = 0;
	this->_gyroData[Y_DATA] = 0;
	this->_gyroData[Z_DATA] = 0;
		
	this->_accelerometerData[X_DATA] = 0;
	this->_accelerometerData[Y_DATA] = 0;
	this->_accelerometerData[Z_DATA] = 0;
	
}
ImuSensor::~ImuSensor()
{
	//do nothing
}
void ImuSensor::reset()
{
	//resetting all muxes
	for (byte i = 0; i < sizeof(this->_resetArray) / sizeof(this->_resetArray[0]); i++)
	{
		this->_resetArray[i]->reset();
	}
}
void ImuSensor::readIMUSensor()
{

	//Get the Compass Data
	this->_compassData[X_DATA] = _imuCompass->getXValue();
	this->_compassData[Y_DATA] = _imuCompass->getYValue();
	this->_compassData[Z_DATA] = _imuCompass->getZValue();
	
	//Get the Gyro Data
	this->_gyroData[X_DATA] = _imuGyro->getXValue();
	this->_gyroData[Y_DATA] = _imuGyro->getYValue();
	this->_gyroData[Z_DATA] = _imuGyro->getZValue();
				
	//Get the Accelerometer Data		
	this->_accelerometerData[X_DATA] = _imuAccelerometer->getXValue();
	this->_accelerometerData[Y_DATA] = _imuAccelerometer->getYValue();
	this->_accelerometerData[Z_DATA] = _imuAccelerometer->getZValue();
				
	return;
}



void ImuSensor::getGyroData(int gyroData[])
{
	//copy the array values over	
	gyroData[X_DATA] = this->_gyroData[X_DATA];
	gyroData[Y_DATA] = this->_gyroData[Y_DATA];
	gyroData[Z_DATA] = this->_gyroData[Z_DATA];	
	return;
}
//void ImuSensor::getAccelerometerData(int accelerometerData[])
void ImuSensor::getAccelerometerData(int accelerometerData[])
{	
	//copy the array values over
	accelerometerData[X_DATA] = this->_accelerometerData[X_DATA];
	accelerometerData[Y_DATA] = this->_accelerometerData[Y_DATA];
	accelerometerData[Z_DATA] = this->_accelerometerData[Z_DATA];	
	return;
}
void ImuSensor::getCompassData(int compassData[])
{
	compassData[X_DATA] = this->_compassData[X_DATA];
	compassData[Y_DATA] = this->_compassData[Y_DATA];
	compassData[Z_DATA] = this->_compassData[Z_DATA];	
	return;
}
