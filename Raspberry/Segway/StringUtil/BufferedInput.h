#ifndef BUFFEREDINPUT_H
#define	BUFFEREDINPUT_H

#include <termios.h>
#include "iostream"

class BufferedInput {
public:
    void off(void);
    void on(void);
    int ReadKey(void);
    int WaitAndReadKey(void);
    std::string ReadLine(void);
    
private:
    struct termios t;
};

#endif	/* BUFFEREDINPUT_H */

