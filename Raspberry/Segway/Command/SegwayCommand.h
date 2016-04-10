#ifndef SEGWAYCOMMAND_H
#define	SEGWAYCOMMAND_H

#include "Navigate.h"
#include "Command.h"


class SegwayCommand : public Command {
public:
    SegwayCommand(Navigate* navigate);
    std::string Execute(vector<int> input);
    virtual ~SegwayCommand();
private:
    Navigate* _Navigate;
};

#endif	/* SEGWAYCOMMAND_H */

