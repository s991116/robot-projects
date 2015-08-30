#ifndef STATE_H
#define	STATE_H
#include <string>

class State {
public:
    State();
    virtual State* View() = 0;
    bool Quit;
    State* ReturnState;
    
    void WriteMessage(std::string message);
    std::string ReadString();
    std::string ReadString(std::string text);
    int ReadInteger(std::string text);
    int ReadInteger();

};

#endif	/* STATE_H */

