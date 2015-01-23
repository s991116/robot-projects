#ifndef EMPTYLOG_H
#define	EMPTYLOG_H

#include <Logging.h>

class EmptyLog : public Logging {
public:
    EmptyLog();

    void Log(std::string message);
    void Log(int value);
    void Log(std::string message, int value);

private:
};


#endif	/* EMPTYLOG_H */

