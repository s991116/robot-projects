#ifndef CHECKWITHBREAK_H
#define	CHECKWITHBREAK_H

#include "Check.h"
#include "ComController.h"

class CheckWithBreak : public Check{
public:
    CheckWithBreak(Check* check, ComController* comController);
    void ChangeCheck(Check* check);
    void Prepare();
    bool Test();
    
private:
    Check* _Check;
    ComController* _ComController;
};

#endif	/* CHECKWITHBREAK_H */

