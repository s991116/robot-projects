#ifndef SETTINGREADER_H
#define	SETTINGREADER_H
#include "Setting.h"
#include "ParseCommandLine.h"
#include <string>

class SettingReader {
public:
    SettingReader();
    virtual ~SettingReader();
    
    void Read(std::string line, Setting* settings);
private:
    void RemoveComment(std::string& line);
    CommandData::CommandType GetCommandType(std::string& line);
    std::string GetCommandName(std::string& line);
    void ClearLine(std::string& line, int delimiterPosition);
    void ToUpperCase(std::string& line);
    std::string GetSettingName(std::string& line);
    double GetNumberDouble(std::string& line);
};

#endif	/* SETTINGREADER_H */