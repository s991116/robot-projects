#ifndef DIRECTCOMCOMMAND_H
#define	DIRECTCOMCOMMAND_H
#include <Command.h>
#include <ComController.h>

class DirectComCommand : public Command {
public:
    DirectComCommand(ComController* comController);
    std::string Execute(vector<int>);
    
private:
    int _command;
    int _data;
    ComController* _ComController;
};

#endif	/* DIRECTCOMCOMMAND_H */

