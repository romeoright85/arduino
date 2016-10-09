#pragma once
#include "stdio.h"
#include <iostream>
using namespace std;

class TestObjects
{
public:
	TestObjects(int);
	~TestObjects();
	void print();
private:
	static int _counter;
	int _id;
};



