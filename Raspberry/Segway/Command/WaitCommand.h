#ifndef WAITCOMMAND_H
#define	WAITCOMMAND_H

#include "Command.h"
#include "Check.h"

class WaitCommand : public Command {
public:
    WaitCommand(Check* check);
    std::string Execute(vector<int> input);
    virtual ~WaitCommand();
private:
    Check* _Check;
};

#endif	/* WAITCOMMAND_H */

