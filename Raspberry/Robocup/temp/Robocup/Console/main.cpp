#include "SensorFactory.h"
#include "ConsolePrint.h"
#include "FileLogger.h"
#include "ScriptCommands.h"
#include "CommandScript.h"
using namespace std;

string GetScriptFilename(int argc, char* argv[]);


int main(int argc, char* argv[])
{             
    try{
      string scriptFilename = GetScriptFilename(argc, argv);    
      Logging* logger = new FileLogger("LineDetectLog.txt");
      SensorFactory* sensorFactory = new SensorFactory(logger, ScriptCommands::CreateCommands());
      ParseCommandLine* parseCommandLine = new ParseCommandLine(ScriptCommands::CreateCommands());
      CommandScript* commandScript = new CommandScript(parseCommandLine, sensorFactory->GetCommands(), sensorFactory->GetSettings());
      
      commandScript->RunFileScript(scriptFilename);
    }
    catch(string error)
    {
        string exception = "Exception: " + error;
        ConsolePrint::PrintError(exception);
    }
    return 0;
}

string GetScriptFilename(int argc, char* argv[]) {    

    switch(argc)
    {                   
        case 2:
            return argv[1];
            break;
            
        default:
            return "TestScript.txt";
            break;
    }
}