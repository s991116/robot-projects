#ifndef LEDCOMMAND_H
#define	LEDCOMMAND_H

#include <Command.h>
#include <ComController.h>

class LEDCommand : public Command
{
public:
    LEDCommand(ComController* comController);
    std::string Execute(vector<int> data);    
private:
    ComController* _ComController;
};

#endif	/* LEDCOMMAND_H */

