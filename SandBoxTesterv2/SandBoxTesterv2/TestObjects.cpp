#include "stdafx.h"
#include "TestObjects.h"



TestObjects::TestObjects(int id)
{
	this->_id = id;
	
}


TestObjects::~TestObjects()
{
}

void TestObjects::print()
{
	cout << "TestObject: " << this->_id << "\n";
}