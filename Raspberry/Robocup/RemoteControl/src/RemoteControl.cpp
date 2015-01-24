#include <View.h>
#include <ConsolLog.h>
#include <Controller.h>

using namespace std;

int main(int argc, char** argv) {

  View* view;
  Controller* Controller;
  
  view = new View();
  ConsolLog* logger = new ConsolLog();
  logger->Log("Test Message");
  return 0;
}