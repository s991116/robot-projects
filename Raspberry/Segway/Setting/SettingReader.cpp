#include "SettingReader.h"

#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

SettingReader::SettingReader() {
}

SettingReader::~SettingReader() {
}

void SettingReader::Read(std::string line, Setting* settings) {
    boost::trim(line);
    RemoveComment(line);
    CommandData* command = new CommandData();
    command->Type = GetCommandType(line);
    if (command->Type == CommandData::SETTING) {
      command->Name = GetCommandName(line);
      command->SettingName = GetSettingName(line);
      ToUpperCase(command->SettingName);
      command->SettingValue = GetNumberDouble(line);
      settings->Set(command->SettingName, command->SettingValue);
    }
}

void SettingReader::RemoveComment(std::string& line)
{
  std::string delimiter = "//";
  int delimiterPosition = line.find(delimiter);
  line = line.substr(0, delimiterPosition);
}

CommandData::CommandType SettingReader::GetCommandType(std::string& line) {
  if (line[0] == '#') {
    line = line.substr(1, line.length() - 1);
    return CommandData::COMMAND;
  }
  if (line[0] == '!') {
    line = line.substr(1, line.length() - 1);
    return CommandData::SETTING;
  }
  if (line[0] == '>') {
    line = line.substr(1, line.length() - 1);
    return CommandData::CALLSCRIPT;
  }
  if (line[0] == '?') {
    line = line.substr(1, line.length() - 1);
    return CommandData::SENSORINFO;
  }

  return CommandData::EMPTY;
}

std::string SettingReader::GetCommandName(std::string& line) {
  std::string delimiter = " ";
  int delimiterPosition = line.find(delimiter);
  std::string command = line;

  if (delimiterPosition > 0)
    command = line.substr(0, delimiterPosition);

  ClearLine(line, delimiterPosition);
  
  return command;
}

void SettingReader::ClearLine(std::string& line, int delimiterPosition) {
  if (delimiterPosition < 0) {
    line = "";
  } else {
    int startPosition = delimiterPosition + 1;

    if (startPosition > 1) {
      int length = line.length() - startPosition;
      line = line.substr(startPosition, length);
    }
    boost::trim(line);
  }
}

void SettingReader::ToUpperCase(std::string& line) {
  boost::to_upper(line);
  boost::trim(line);
}

std::string SettingReader::GetSettingName(std::string& line) {
  if (line[0] != '-') {
    std::string error = "Error: Expected '-' in Setting line.";
    throw error;
  }
  line = line.substr(1, line.length() - 1);
  return GetCommandName(line);
}

double SettingReader::GetNumberDouble(std::string& line) {
  double number;
    try {
      number = boost::lexical_cast<double>(line);
    } catch (boost::bad_lexical_cast const& e) {
      std::string error = "Error: input '" + line + "' was not a valid interger.";
      throw error;
    }
  return number;
}