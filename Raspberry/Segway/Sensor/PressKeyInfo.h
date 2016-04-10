#ifndef PRESSKEYINFO_H
#define	PRESSKEYINFO_H

#include "Check.h"
#include <ncurses.h>
class PressKeyInfo : public Check{
public:
    PressKeyInfo();
    virtual ~PressKeyInfo();
    void Prepare();
    bool Test();
    
private:

};

#endif	/* PRESSKEYINFO_H */

