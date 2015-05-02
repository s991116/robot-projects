#include "gtest.h"

/*
	To test the library, include "gtest.h" from an application project
	and call gtestTest().
	
	Do not forget to add the library to Project Dependencies in Visual Studio.
*/

static int s_Test = 0;

extern "C" int gtestTest();

int gtestTest()
{
	return ++s_Test;
}