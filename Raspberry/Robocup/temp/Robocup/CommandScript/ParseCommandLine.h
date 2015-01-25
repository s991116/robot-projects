#ifndef PARSECOMMANDLINE_H
#define	PARSECOMMANDLINE_H

#include "Command.h"
#include <string>
#include <vector>
#include <map>

using namespace std;
    
struct CommandData {
  public:
    enum CommandType
    {
      EMPTY,
      COMMAND,
      SETTING,
      CALLSCRIPT,
      SENSORINFO,
    };
   
    CommandType Type;
    string Name;
    string SettingName;
    int SettingValue;
    vector<int> Data;  
    bool QuitScript;
    bool CallScript;
    string CallScriptFilename;
};

class ParseCommandLine {
public:
    ParseCommandLine(std::map<string, int> commands);
    ParseCommandLine(const ParseCommandLine& orig);
    virtual ~ParseCommandLine();
    CommandData* ParseLine(string line);    
    std::vector<int> ConvertStringListToIntList(std::vector<std::string>);
    
private:
    CommandData::CommandType GetCommandType(string& line);
    int GetNumberInt(std::string stringNumber);
    void RemoveComment(string& line);
    void RemoveCommentStartBlock(string& line);
    void RemoveCommentStopBlock(string& line);    
    string GetCommandName(string& line);
    void ClearLine(string& line, int delimiterPosition);
    void ToUpperCase(string& line);
    vector<int> GetData(string& line);
    string GetSettingName(string& line);
    std::map<string, int> Commands;
    bool _CommentBlock;
};
#endif	/* PARSECOMMANDLINE_H */