#pragma once
#include "TestObjects.h"
#include "stdio.h"
#include <iostream>
using namespace std;
class ArrayTester
{
public:
	ArrayTester(TestObjects * [], int);
	~ArrayTester();
private:
	//TestObjects ** _ptrToTestObjectPtrArray;//have to create an array ptr because if you create the array, you have to know the size at the time of declaration
//	TestObjects * _testObjectPtrArray;
	
};

