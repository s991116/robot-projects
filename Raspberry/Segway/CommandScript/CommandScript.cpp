#include "CommandScript.h"
#include "ParseCommandLine.h"
#include <stdlib.h>
#include "ConsolePrint.h"

using namespace std;

CommandScript::CommandScript(ParseCommandLine* parseCommandLine, map<string, Command*> commands, map<string, Setting*> settings, map<string, SensorInfo*> sensors) {
  this->_ParseCommandLine = parseCommandLine;
  this->_Commands = commands;
  this->_Settings = settings;
  this->_Sensors = sensors;
}

void CommandScript::RunFileScript(string scriptFileName) {
  string line;
  ifstream scriptFile(scriptFileName.c_str());
  if (scriptFile.is_open()) {
    while (getline(scriptFile, line)) {

      CommandData* commandData = _ParseCommandLine->ParseLine(line);

      PrintToConsole(commandData, line);

      if (commandData->QuitScript)
        return;

      if (commandData->CallScript) {
        RunFileScript(commandData->CallScriptFilename);
      } else {
        std::string result = this->ExecuteCommand(commandData);

        if (result.length() > 0)
          ConsolePrint::PrintResult(result);
      }
    }
    scriptFile.close();
  } else {
    std::string error = "Cannot open script file '" + scriptFileName + "'.";
    ConsolePrint::PrintError(error);
  }
}

std::string CommandScript::ExecuteCommand(CommandData* commandData) {

  if (commandData->Type == CommandData::COMMAND) {
    Command* command = _Commands[commandData->Name];
    if(command == NULL)
    {
      std::string error = "Cannot find command '" + commandData->Name + "'.";
      throw error;
    }
      
    return command->Execute(commandData->Data);
  }
  if (commandData->Type == CommandData::SETTING) {
    Setting* setting = _Settings[commandData->Name];
    if(setting == NULL)
    {
      std::string error = "Cannot find setting '" + commandData->Name + "'.";
      throw error;
    }
    setting->Set(commandData->SettingName, commandData->SettingValue);
  }
  if (commandData->Type == CommandData::SENSORINFO) {
    SensorInfo* sensorInfo = _Sensors[commandData->Name];
    if(sensorInfo == NULL)
    {
      std::string error = "Cannot find sensorinfo '" + commandData->Name + "'.";
      throw error;
    }
    return sensorInfo->GetStatus();
  }
  return "";
}

void CommandScript::PrintToConsole(CommandData* commandData, string line) {
  switch (commandData->Type) {
    case CommandData::COMMAND:
      ConsolePrint::PrintCommand(line);
      break;

    case CommandData::CALLSCRIPT:
      ConsolePrint::PrintCall(line);
      break;

    case CommandData::SETTING:
      ConsolePrint::PrintSetting(line);
      break;

    case CommandData::EMPTY:
      ConsolePrint::PrintEmpty(line);
      break;
      
    default:
      ConsolePrint::PrintStandard(line);
      break;
  }
}