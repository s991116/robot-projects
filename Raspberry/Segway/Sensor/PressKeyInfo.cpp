#include "PressKeyInfo.h"
#include <ncurses.h>

PressKeyInfo::PressKeyInfo() {
}

void PressKeyInfo::Prepare() {
    
}

bool PressKeyInfo::Test() {
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return true;
    } else {
        return false;
    }
}

PressKeyInfo::~PressKeyInfo() {
}

