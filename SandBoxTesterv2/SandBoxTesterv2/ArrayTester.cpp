#include "stdafx.h"
#include "ArrayTester.h"


ArrayTester::ArrayTester(TestObjects * testObjectPtrArray[], int testObjectPtrArraySize)
{
	cout << "Num Of TestObjects in testObjectPtrArray: " << testObjectPtrArraySize << "\n";
	//TestObjects *_testObjectPtrArray;
	TestObjects * _testObjectPtrArray[1000];
	for (int i = 0; i < testObjectPtrArraySize; i++)
	{
		//testObjectPtrArray[i]->print();
		_testObjectPtrArray[i] = testObjectPtrArray[i];
		//_testObjectPtrArray[i]->print();
	}



	//_testObjectPtrArray = new TestObjects * [testObjectPtrArraySize];
	
	TestObjects ** tempArray;
	tempArray = new TestObjects * [testObjectPtrArraySize];
	
	memcpy(tempArray, _testObjectPtrArray, testObjectPtrArraySize); //memcpy(pointer to dest array, pointer to src array, size)

	for (int i = 0; i < testObjectPtrArraySize; i++)
	{
		(*tempArray)[i].print();
	}
//	cout << "debug\n";
	//cout << testObjectPtrArray[0] << "\n";
	//cout << &_testObjectPtrArray[0] << "\n";
	
	


//	cout << *_testObjectPtrArray[0] << "\n";

	//cout << "Num Of TestObjects in _testObjectPtrArray: " << sizeof(&_testObjectPtrArray)/sizeof(&_testObjectPtrArray[0]) << "\n";



	

	
}


ArrayTester::~ArrayTester()
{
}
