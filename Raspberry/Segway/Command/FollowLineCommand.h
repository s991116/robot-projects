#ifndef FOLLOWLINECOMMAND_H
#define	FOLLOWLINECOMMAND_H

#include "Command.h"

class FollowLineCommand : public Command {
public:
    FollowLineCommand();
    std::string Execute(vector<int> input);
    virtual ~FollowLineCommand();
private:

};

#endif	/* FOLLOWLINECOMMAND_H */

