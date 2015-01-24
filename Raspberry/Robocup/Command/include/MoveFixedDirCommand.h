#ifndef MOVEFIXEDDIRCOMMAND_H
#define	MOVEFIXEDDIRCOMMAND_H

#include <ComController.h>
#include "Command.h"
#include "Check.h"

class MoveFixedDirCommand : public Command {
public:
    MoveFixedDirCommand(ComController* comController, Check* check);
    std::string Execute(vector<int> data);

private:
    ComController* _ComController;
    Check* _Check;
};

#endif	/* MOVEFIXEDDIRCOMMAND_H */

