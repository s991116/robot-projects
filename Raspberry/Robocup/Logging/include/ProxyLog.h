#ifndef PROXYLOG_H
#define	PROXYLOG_H

#include <Logging.h>

class ProxyLog  : public Logging {
public:
    ProxyLog(Logging* logging);
 
    void Log(std::string message);
    void Log(int value);
    void Log(std::string message, int value);
    void ChangeLog(Logging* logging);
    
private:
    Logging* _Logging;
};

#endif	/* PROXYLOG_H */

