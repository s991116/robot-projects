#include <cstdlib>
#include <stdio.h>
#include <Controller.h>
#include <View.h>
#include <SensorFactory.h>
#include <ScriptCommands.h>
#include <ParseCommandLine.h>
#include <CommandScript.h>
#include <SensorFactory.h>

using namespace std;

int main(int argc, char** argv) {
  std::string scriptPath = "../Scripts/";
  View* view;
  Controller* controller;
  view = new View();
  map<string, int> commands = ScriptCommands::CreateCommands();
  SensorFactory* sensorFactory = new SensorFactory(commands, scriptPath);
  ParseCommandLine* parseCommandLine = new ParseCommandLine(ScriptCommands::CreateCommands());
  CommandScript* commandScript = new CommandScript(parseCommandLine, sensorFactory->GetCommands(), sensorFactory->GetSettings(), sensorFactory->GetSensors(), scriptPath);

  controller = new Controller(view, commandScript, sensorFactory->GetCommands(), sensorFactory->GetSensors(), sensorFactory->GetSettings());

  controller->Start();

  return 0;
}
