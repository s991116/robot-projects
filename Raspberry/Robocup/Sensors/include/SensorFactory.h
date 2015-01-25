#ifndef SENSORFACTORY_H
#define	SENSORFACTORY_H
#include <Logging.h>
#include <Command.h>
#include <Setting.h>
#include <SensorInfo.h>
#include <string>
#include <map>

class SensorFactory {
public:
    SensorFactory(Logging* logging, map<string, int> commands);
    map<string, Command*> GetCommands();
    map<string, Setting*> GetSettings();
    map<string, SensorInfo*> GetSensors();
    
private:
    map<string, Command*> _commands;
    map<string, Setting*> _settings;
    map<string, SensorInfo*> _sensors;
};

#endif	/* SENSORFACTORY_H */

