#pragma once
#include <iostream>
#include "ConsoleColor.h"

class Console
{
public:
	Console();

	void PrintStandard(std::string line);
	
	void PrintCommand(std::string line);

	void PrintError(std::string line);

	void PrintSetting(std::string line);
	
	void Print(std::string line);

	void PrintColor(std::string line, ConsoleColor color);

	~Console();
};

