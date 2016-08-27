//IrDistanceSensor.h
#ifndef _IRDISTANCESENSOR_H
#define _IRDISTANCESENSOR_H

#include <Arduino.h>
#include <DistanceSensor.h>
#include <RoverReset.h>

/*******************************************************************
Configure (define) flags before calling #include <RoverConfig.h>
/********************************************************************/

//define Arduino 1: NAVI in order to use it's config pins
#ifndef _ARD_1_NAVI_H
#define _ARD_1_NAVI_H
#endif

/********************************************************************/
#include <RoverConfig.h>





class IrDistanceSensor : public DistanceSensor, public virtual RoverReset {
public:
	IrDistanceSensor(byte);//constructor. (IR distance sensor output pin)
	~IrDistanceSensor();//destructor
	int getDistance(byte);//returns distance (mode: UNIT_CM, UNIT_M, UNIT_FT, UNIT_IN). Also see RoverConfig.h
	virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
private:
	byte IrSensorPin;
};




#endif 