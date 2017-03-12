//TemplateClassPractice.h
#ifndef _TEMPLATECLASSPRACTICE_H
#define _TEMPLATECLASSPRACTICE_H

#include <Arduino.h>
#include <RoverDebug.h>
#include <RoverConfig.h>

template<class T>
class TemplateClassPractice {
public:
	TemplateClassPractice(T, T);//constructor (value 1, value 2)
	~TemplateClassPractice();//destructor	
	T getMax();
private:
	T _values[2];
	
};

template <class T>
TemplateClassPractice<T>::TemplateClassPractice(T value1, T value2)
{
	this->_values[0] = value1;
	this->_values[1] = value2;
}
template <class T>
TemplateClassPractice<T>::~TemplateClassPractice()
{
	Serial.println(F("Object Destroyed"));
}
template <class T>
T TemplateClassPractice<T>::getMax()
{
	return this->_values[0] > this->_values[1] ? this->_values[0] : this->_values[1];
}




#endif 