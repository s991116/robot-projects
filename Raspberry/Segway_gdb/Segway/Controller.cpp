#include "Controller.h"
#include "View.h"


Controller::Controller(View* view)
{
	_View = view;
}

void Controller::Start()
{
	_View->Initialize();
	_QuitProgram = false;
	while (!_QuitProgram) {
		_View->UpdateView();
		_View->GetCommand();
	}
}

Controller::~Controller()
{
}
