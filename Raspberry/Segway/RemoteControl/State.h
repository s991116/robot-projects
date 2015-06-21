#ifndef STATE_H
#define	STATE_H

class State {
public:
    State();
    virtual State* View() = 0;
    bool Quit;
    State* ReturnState;
};

#endif	/* STATE_H */

