//RoverSandbox.h
#ifndef _ROVERSANDBOX_H
#define _ROVERSANDBOX_H

	#include <Arduino.h>
	#include <RoverDebug.h>
	#include <RoverReset.h>
	
	/*******************************************************************
	Configure (define) flags before calling #include <RoverConfig.h>
	/********************************************************************/
	//define Arduino 1: NAVI in order to use it's config pins
	#ifndef _ARD_1_NAVI_H
		#define _ARD_1_NAVI_H
	#endif

	//define Arduino 2: AUXI in order to use it's config pins
	#ifndef _ARD_2_AUXI_H
		#define _ARD_2_AUXI_H
	#endif

	//define Arduino 3: MAIN in order to use it's config pins
	#ifndef _ARD_3_MAIN_H
		#define _ARD_3_MAIN_H
	#endif
	
	//define Arduino 4: COMM in order to use it's config pins
	#ifndef _ARD_4_COMM_H
		#define _ARD_4_COMM_H		
	#endif
	
	/********************************************************************/

	#include <RoverConfig.h>
	
	class RoverSandbox : public virtual RoverReset {
	public:
		RoverSandbox();//constructor
		~RoverSandbox();//destructor
		static void printNumofObjects();//prints the number of objects
		static void resetObjectInstances();//reset the number of objects
		virtual void reset();//software reset, virtual (but not pure virtual, so it has an implementation of it's own but can be overridden)
		
	private:
		static int _objectInstances;
	};

	#endif 