#include "PressKeyInfo.h"
#include <ncurses.h>

PressKeyInfo::PressKeyInfo() {
}

void PressKeyInfo::Prepare() {
    
}

bool PressKeyInfo::Test() {
    nodelay(stdscr, TRUE);
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        nodelay(stdscr, FALSE);
        return true;
    } else {
        return false;
        nodelay(stdscr, FALSE);        
    }
}

PressKeyInfo::~PressKeyInfo() {
}

