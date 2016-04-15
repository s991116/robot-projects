#include "ConsoleLog.h"
#include "ConsolePrint.h"
#include "Convert.h"

ConsoleLog::ConsoleLog() {
}
void ConsoleLog::Log(std::string message) {
    ConsolePrint::PrintResult(message);
}

void ConsoleLog::Log(int value) {
    ConsolePrint::PrintResult(Convert::IntToString(value));
}

void ConsoleLog::Log(std::string message, int value) {
    ConsolePrint::PrintResult(message+": "+Convert::IntToString(value));
}

void ConsoleLog::Log(std::string message, float value) {
    ConsolePrint::PrintResult(message+": "+Convert::FloatToString(value));
}

void ConsoleLog::Error(std::string message) {
    ConsolePrint::PrintError(message);
}

ConsoleLog::~ConsoleLog() {
}

