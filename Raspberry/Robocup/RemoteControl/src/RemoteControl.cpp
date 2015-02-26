#include <cstdlib>
#include <stdio.h>
#include <Controller.h>
#include <View.h>
#include <ConsolLog.h>
#include <SensorFactory.h>
#include <ScriptCommands.h>
#include <ParseCommandLine.h>
#include <CommandScript.h>
#include <SensorFactory.h>

using namespace std;

int main(int argc, char** argv) {

  View* view;
  Controller* controller;
  view = new View();
  Logging* logger = new ConsolLog();
  SensorFactory* sensorFactory = new SensorFactory(logger, ScriptCommands::CreateCommands());
  ParseCommandLine* parseCommandLine = new ParseCommandLine(ScriptCommands::CreateCommands());
  CommandScript* commandScript = new CommandScript(parseCommandLine, sensorFactory->GetCommands(), sensorFactory->GetSettings(), sensorFactory->GetSensors());

  controller = new Controller(view, commandScript, sensorFactory->GetCommands(), sensorFactory->GetSensors(), sensorFactory->GetSettings());

  controller->Start();

  return 0;
}
