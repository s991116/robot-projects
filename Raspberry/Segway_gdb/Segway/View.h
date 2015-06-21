#pragma once

class Controller;

class View
{
public:
	View();
	void Initialize();
	void UpdateView();
	void GetCommand();

	~View();

	Controller* _Controller;

private:
};

