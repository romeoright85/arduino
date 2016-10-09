// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include <iostream>
using namespace std;
#include "TestObjects.h"
#include "ArrayTester.h"


int main()
{


	TestObjects * testObject1 = new TestObjects(1);
	cout << "testObject1 Created with Address: " << &testObject1 << "\n";
	TestObjects * testObject2 = new TestObjects(2);
	cout << "testObject2 Created with Address: " << &testObject2 << "\n";
	TestObjects * testObject3 = new TestObjects(3);
	cout << "testObject3 Created with Address: " << &testObject3 << "\n";
	TestObjects * testObject4 = new TestObjects(4);
	cout << "testObject4 Created with Address: " << &testObject4 << "\n";

	TestObjects * testObjectPtrArray[] = { testObject1 , testObject2, testObject3, testObject4 };



	ArrayTester * arrayOfObjects = new ArrayTester(testObjectPtrArray, sizeof(testObjectPtrArray) / sizeof(testObjectPtrArray[0]));





	//cout << "Hello World\n";
	//testObject1->print();
	//testObject2->print();
	system("pause");
	return 0;
}

