#ifndef PORTCHECK_H
#define	PORTCHECK_H

#include "Check.h"
#include "Setting.h"
#include "ComController.h"

class PortCheck : public Check, public Setting {
public:
    PortCheck(ComController* comController, int portCount);
    PortCheck(const PortCheck& orig);
    void Prepare();
    bool Test();

private:
    ComController* _ComController;
    int _TargetCount;
    int _DeltaCount;
};

#endif	/* PORTCHECK_H */

