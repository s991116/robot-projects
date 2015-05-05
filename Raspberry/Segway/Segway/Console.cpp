#include "Console.h"
#include "Convert.h"

Console::Console()
{
}


void Console::PrintStandard(std::string line) {
	Print(line);
}

void Console::PrintCommand(std::string line) {
	Print(line);
}

void Console::PrintError(std::string line) {
	PrintColor(line, ConsoleColor::RED);
}

void Console::PrintSetting(std::string line) {
	PrintColor(line, ConsoleColor::YELLOW);
}

void Console::Print(std::string line) {
	std::cout << line << std::endl;
}

void Console::PrintColor(std::string line, ConsoleColor color) {
	std::string default_console = "\033[0m";
	std::string numberString = Convert::IntToString(static_cast<int>(color));

	std::string colorCode = "\033[" + numberString + "m";
	std::cout << colorCode;
	Print(line);
	std::cout << default_console;
}

Console::~Console()
{
}
