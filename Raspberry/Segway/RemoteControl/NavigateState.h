#ifndef NAVIGATESTATE_H
#define	NAVIGATESTATE_H

#include "State.h"
#include "DirectionEnum.h"
#include <string>
#include "Navigate.h"
#include "Distance.h"

class NavigateState : public State {
public:
    NavigateState(Navigate* navigate, Distance* distance);
    State* View();
    virtual ~NavigateState();
private:
    Navigate* _Navigate;
    Distance* _Distance;
    std::string PrintDirection(DirectionEnum dir);
    short _Speed;
    short _TurnSpeed;
};

#endif	/* NAVIGATESTATE_H */

