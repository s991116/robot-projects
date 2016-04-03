#include "ScriptRunnerState.h"
#include <ncurses.h>

ScriptRunnerState::ScriptRunnerState(CommandScript* commandScript) {
    _ScriptPath = "TestScript.txt";
    _CommandScript = commandScript;
}

ScriptRunnerState::~ScriptRunnerState() {
}

State* ScriptRunnerState::View() {
    clear();
    printw("*** Script runner ***\n");
    printw("R         - Run script\n");
    printw("C         - Change script\n");
    printw("Q         - Return\n");
    printw("\n");
    printw("Script path:");
    printw(_ScriptPath.c_str());
    printw("\n");
    noecho();

    keypad(stdscr, 1);
    switch (getch()) {
        case 'q':
            return this->ReturnState;
            break;

        case 'r':
            _CommandScript->RunFileScript(_ScriptPath);
            WriteMessage("Script finished.");
            break;

        case 'c':
            _ScriptPath = this->ReadString("Set scriptname incl. path:");
            break;
    }
    return this;
}