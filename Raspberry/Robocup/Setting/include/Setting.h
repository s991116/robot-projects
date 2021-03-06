#ifndef SETTING_H
#define	SETTING_H
#include <string>
#include <map>

class Setting {
public:
    Setting();
    void Set(std::string name, int value);
	virtual void   UpdatedSetting(std::string name);

    std::map<std::string, float*> SettingsFloat;
    std::map<std::string, int*> SettingsInt;
    std::map<std::string, bool*> SettingsBool;
    
private:
    void SetFloatValue(std::string name, int value);
    void SetIntValue(std::string name, int value);
    void SetBoolValue(std::string name, int value);    

};

#endif	/* SETTING_H */

