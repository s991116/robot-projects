#ifndef COMMANDSCRIPT_H
#define	COMMANDSCRIPT_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "ParseCommandLine.h"
#include "Command.h"
#include "Setting.h"
#include "SensorInfo.h"

class CommandScript {
public:
    CommandScript(ParseCommandLine* parseCommandLine, map<string, Command*> commands, map<string, Setting*> settings, map<string, SensorInfo*> sensors);
    void RunFileScript(string scriptFilename);

private:
    map<std::string, Command*> _Commands;
    map<std::string, Setting*> _Settings;
    map<std::string, SensorInfo*> _Sensors;
    ParseCommandLine* _ParseCommandLine;
    std::string ExecuteCommand(CommandData* commandData);
    void PrintToConsole(CommandData* commandData, std::string line);
};

#endif	/* COMMANDSCRIPT_H */

