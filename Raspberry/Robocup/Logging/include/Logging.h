#ifndef LOGGING_H
#define	LOGGING_H

#include <string>

class Logging {
public:
    virtual void Log(std::string message) = 0;
    virtual void Log(int value) = 0;
    virtual void Log(std::string message, int value) = 0;
    virtual void Log(std::string message, float value) = 0;
	virtual void Error(std::string message) = 0;
};

#endif	/* LOGGING_H */

