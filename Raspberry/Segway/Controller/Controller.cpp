#include "Controller.h"

/*
	To test the library, include "Controller.h" from an application project
	and call ControllerTest().
	
	Do not forget to add the library to Project Dependencies in Visual Studio.
*/

static int s_Test = 0;

extern "C" int ControllerTest();

int ControllerTest()
{
	return ++s_Test;
}

Controller::Controller()
{
}


Controller::~Controller()
{
}
