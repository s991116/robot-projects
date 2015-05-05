#pragma once

class View;

class Controller
{
public:
	Controller(View* view);
	void Start();

	~Controller();

private:
	View* _View;
	bool _QuitProgram;
};

