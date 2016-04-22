#include "ConsolePrint.h"
#include "Convert.h"
#include <iostream>

void ConsolePrint::PrintStandard(string line) {
  Print(line);
}

void ConsolePrint::PrintCommand(string line) {
  Print(line);
}

void ConsolePrint::PrintError(string line) {
  PrintColor(line, ConsolePrint::RED);
}

void ConsolePrint::PrintSetting(string line) {
  PrintColor(line, ConsolePrint::YELLOW);
}

void ConsolePrint::PrintCall(string line) {
  PrintColor(line, ConsolePrint::GREEN);
}

void ConsolePrint::PrintLog(string line) {
  PrintColor(line, ConsolePrint::CYAN);  
}

void ConsolePrint::PrintEmpty(string line) {
  PrintColor(line, ConsolePrint::CYAN);
}

void ConsolePrint::PrintResult(string result) {
  string resultString = "-> " + result;
  PrintColor(resultString, ConsolePrint::PURPLE);
}

void ConsolePrint::Print(string line) {
  cout << line << std::endl;
}

void ConsolePrint::PrintColor(string line, ConsoleColor color) {
  string default_console = "\033[0m";
  string numberString = Convert::IntToString(color);

  string colorCode = "\033[" + numberString + "m";
  cout << colorCode;
  Print(line);
  cout << default_console;
}