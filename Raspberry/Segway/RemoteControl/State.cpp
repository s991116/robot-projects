#include "State.h"
#include <ncurses.h>
#include "Convert.h"
#include "ContinuousPresentation.h"

State::State() {
    this->Quit = false;
}

int State::ReadInteger() {
    return ReadInteger("");
}

int State::ReadInteger(std::string text) {
    printw(text.c_str());
    std::string result = this->ReadString();
    noecho();
    return Convert::StringToInt(result);
}

std::string State::ReadString() {
    return ReadString("");
}

void State::WriteMessage(std::string message) {
    cbreak();
    printw(message.c_str());
    getch();
}

std::string State::ReadString(std::string text) {
    printw(text.c_str());
    std::string input;

    // let the terminal do the line editing
    nocbreak();
    echo();

    // this reads from buffer after <ENTER>, not "raw" 
    // so any backspacing etc. has already been taken care of
    int ch = getch();

    while (ch != '\n') {
        input.push_back(ch);
        ch = getch();
    }
    noecho();
    cbreak();

    return input;
}

void State::LoopDisplayFunction(ContinuousPresentation* continuousPresentation)
{
            cbreak();
            clear();
            noecho();
            nodelay(stdscr, TRUE);
            scrollok(stdscr, TRUE);
            mvprintw(0,0, "Q         - Return\n");
            while (!kbhit()) {
                std::string result = continuousPresentation->Presentation();
                move(1, 0);
                clrtoeol(); 
                mvprintw(1,1,"%s", result.c_str());
            }
            echo();
            nodelay(stdscr, FALSE);
            scrollok(stdscr, FALSE);    
}

int State::kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}
