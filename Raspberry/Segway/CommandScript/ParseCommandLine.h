#ifndef PARSECOMMANDLINE_H
#define	PARSECOMMANDLINE_H

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
    std::string Name;
    std::string SettingName;
    int SettingValue;
    vector<int> Data;  
    bool QuitScript;
    bool CallScript;
    std::string CallScriptFilename;
};

class ParseCommandLine {
public:
    ParseCommandLine(std::map<std::string, int> commands);
    ParseCommandLine(const ParseCommandLine& orig);
    virtual ~ParseCommandLine();
    CommandData* ParseLine(std::string line);    
    std::vector<int> ConvertStringListToIntList(std::vector<std::string>);
    
private:
    CommandData::CommandType GetCommandType(std::string& line);
    int GetNumberInt(std::string stringNumber);
    void RemoveComment(std::string& line);
    void RemoveCommentStartBlock(std::string& line);
    void RemoveCommentStopBlock(std::string& line);    
    string GetCommandName(std::string& line);
    void ClearLine(std::string& line, int delimiterPosition);
    void ToUpperCase(std::string& line);
    std::vector<int> GetData(std::string& line);
    string GetSettingName(std::string& line);
    std::map<string, int> Commands;
    bool _CommentBlock;
};

#endif	/* PARSECOMMANDLINE_H */

