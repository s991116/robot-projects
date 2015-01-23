#ifndef FILELOGGER_H
#define	FILELOGGER_H
#include <Logging.h>
#include <iostream>
#include <fstream>

class FileLogger : public Logging {
public:
    FileLogger(std::string filename);

    void Log(std::string message);
    void Log(int value);
    void Log(std::string message, int value);

private:
    std::ofstream _filestream;
    std::string _filename;
};

#endif	/* FILELOGGER_H */

