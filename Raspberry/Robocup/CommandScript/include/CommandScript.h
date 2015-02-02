#ifndef COMMANDSCRIPT_H
#define	COMMANDSCRIPT_H

#include <Command.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <ParseCommandLine.h>
#include <Setting.h>
#include <SensorInfo.h>
using namespace std;

class CommandScript {
public:
    CommandScript(ParseCommandLine* parseCommandLine, map<string, Command*> commands, map<string, Setting*> settings, map<string, SensorInfo*> sensors);
    void RunFileScript(string scriptFilename);

private:
    map<string, Command*> _Commands;
    map<string, Setting*> _Settings;
    map<string, SensorInfo*> _Sensors;
    ParseCommandLine* _ParseCommandLine;
    std::string ExecuteCommand(CommandData* commandData);
    void PrintToConsole(CommandData* commandData, string line);
};
#endif	/* COMMANDSCRIPT_H */