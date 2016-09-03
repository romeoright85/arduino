// HelloWorld.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Test.h>
#include <iostream>

using namespace std;

int main()
{
	char pause;
	Test tester = Test();
	cout << tester.getValue();
	cin >> pause;
	return 0;
}

