#ifndef SETTINGFILEREADER_H
#define	SETTINGFILEREADER_H
#include "Setting.h"
#include "SettingReader.h"

#include <string>

class SettingFileReader {
public:
    SettingFileReader(SettingReader* settingReader);
    virtual ~SettingFileReader();
    
    void UpdateSettings(std::string settingFilename, Setting* settings);
private:
    SettingReader* _SettingReader;

};

#endif	/* SETTINGFILEREADER_H */

