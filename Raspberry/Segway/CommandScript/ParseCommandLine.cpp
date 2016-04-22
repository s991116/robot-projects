#include "ParseCommandLine.h"
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>

ParseCommandLine::ParseCommandLine(std::map<std::string, int> commands) {
  Commands = commands;
  _CommentBlock = false;
}

ParseCommandLine::ParseCommandLine(const ParseCommandLine& orig) {
}

ParseCommandLine::~ParseCommandLine() {
}

CommandData* ParseCommandLine::ParseLine(std::string line) {
  CommandData* command = new CommandData();

  boost::trim(line);
  RemoveComment(line);
  RemoveCommentStopBlock(line);
  if (_CommentBlock) {
    command->Type = CommandData::EMPTY;
    return command;
  }

  RemoveCommentStartBlock(line);
  command->Type = GetCommandType(line);
  command->QuitScript = false;

  if (command->Type == CommandData::COMMAND || command->Type == CommandData::SENSORINFO) {
    command->Name = GetCommandName(line);
    this->ToUpperCase(command->Name);
    command->Data = GetData(line);
    if (command->Name.compare("QUIT") == 0)
      command->QuitScript = true;
  }

  if (command->Type == CommandData::SETTING) {
    command->Name = GetCommandName(line);
    this->ToUpperCase(command->Name);
    command->SettingName = GetSettingName(line);
    command->SettingValue = GetNumberInt(line);
  }

  if (command->Type == CommandData::CALLSCRIPT) {
    command->CallScript = true;
    command->CallScriptFilename = GetCommandName(line);
  }

  return command;
}

CommandData::CommandType ParseCommandLine::GetCommandType(std::string& line) {
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

void ParseCommandLine::RemoveComment(std::string& line) {
  std::string delimiter = "//";
  int delimiterPosition = line.find(delimiter);
  line = line.substr(0, delimiterPosition);
}

void ParseCommandLine::RemoveCommentStartBlock(std::string& line) {
  std::string delimiter = "/*";
  int delimiterPosition = line.find(delimiter);
  if (delimiterPosition >= 0)
    this->_CommentBlock = true;
  line = line.substr(0, delimiterPosition);
}

void ParseCommandLine::RemoveCommentStopBlock(std::string& line) {
  std::string delimiter = "*/";
  int delimiterPosition = line.find(delimiter);
  if (delimiterPosition >= 0) {
    this->_CommentBlock = false;
    int startPosition = delimiterPosition + 2;
    if (startPosition > 2) {
      int length = line.length() - startPosition;
      line = line.substr(startPosition, length);
      boost::trim(line);
    }
  }
}

std::string ParseCommandLine::GetCommandName(std::string& line) {
  std::string delimiter = " ";
  int delimiterPosition = line.find(delimiter);
  std::string command = line;

  if (delimiterPosition > 0)
    command = line.substr(0, delimiterPosition);

  ClearLine(line, delimiterPosition);
  return command;
}

void ParseCommandLine::ToUpperCase(std::string& line) {
  boost::to_upper(line);
  boost::trim(line);
}

void ParseCommandLine::ClearLine(std::string& line, int delimiterPosition) {
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

std::vector<int> ParseCommandLine::GetData(std::string& line) {
  std::vector<std::string> dataString;

  if (line.length() > 0) {
    boost::split(dataString, line, boost::is_any_of(","));
    return ConvertStringListToIntList(dataString);
  }

  std::vector<int> result;
  return result;
}

std::string ParseCommandLine::GetSettingName(std::string& line) {
  if (line[0] != '-') {
    std::string error = "Error: Expected '-' in Setting line.";
    throw error;
  }

  line = line.substr(1, line.length() - 1);
  return GetCommandName(line);
}

std::vector<int> ParseCommandLine::ConvertStringListToIntList(std::vector<std::string> dataString) {
  std::vector<int> data;
  for (std::vector<std::string>::iterator it = dataString.begin(); it != dataString.end(); ++it) {
    std::string numberString = *it;
    boost::trim(numberString);
    int numberInt = GetNumberInt(numberString);
    data.push_back(numberInt);
  }
  return data;
}

int ParseCommandLine::GetNumberInt(std::string numberString) {
  int numberInt;
  std::map<std::string, int>::iterator exists = Commands.find(numberString);
  if (exists == Commands.end()) {
    try {
      numberInt = boost::lexical_cast<int>(numberString);
    } catch (boost::bad_lexical_cast const& e) {
      std::string error = "Error: input '" + numberString + "' was not a valid interger.";
      throw error;
    }
  } else {
    numberInt = Commands[numberString];
  }
  return numberInt;
}