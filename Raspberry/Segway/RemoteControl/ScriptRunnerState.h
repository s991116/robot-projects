#ifndef SCRIPTRUNNERSTATE_H
#define	SCRIPTRUNNERSTATE_H

#include "State.h"
#include "CommandScript.h"
#include <string>

class ScriptRunnerState : public State{
public:
    ScriptRunnerState(CommandScript* commandScript);
    State* View();
    virtual ~ScriptRunnerState();
private:
    std::string _ScriptPath;
    CommandScript* _CommandScript;
};

#endif	/* SCRIPTRUNNERSTATE_H */

