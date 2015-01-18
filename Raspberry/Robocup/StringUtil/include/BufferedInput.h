#ifndef BUFFEREDINPUT_H
#define	BUFFEREDINPUT_H
#include <termios.h>

class BufferedInput {
public:
    void off(void);
    void on(void);
    int getch(void);
private:
    struct termios t;
};

#endif	/* BUFFEREDINPUT_H */

