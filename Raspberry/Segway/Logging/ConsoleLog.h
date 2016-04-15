#ifndef CONSOLELOG_H
#define	CONSOLELOG_H

#include "Logging.h"

class ConsoleLog : public Logging {
public:
    ConsoleLog();
    void Log(std::string message);
    void Log(int value);
    void Log(std::string message, int value);
    void Log(std::string message, float value);
    void Error(std::string message);
    ~ConsoleLog();
private:

};

#endif	/* CONSOLELOG_H */

