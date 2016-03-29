#ifndef NAVIGATESTATE_H
#define	NAVIGATESTATE_H

#include "State.h"
#include "DirectionEnum.h"
#include <string>
#include "Navigate.h"

class NavigateState : public State {
public:
    NavigateState(Navigate* navigate);
    State* View();
    virtual ~NavigateState();
private:
    Navigate* _Navigate;
    std::string PrintDirection(DirectionEnum dir);
    short _Speed;
    short _TurnSpeed;
};

#endif	/* NAVIGATESTATE_H */

