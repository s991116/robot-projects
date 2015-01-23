#include <View.h>
#include <ConsolLog.h>

using namespace std;

int main(int argc, char** argv) {

  View* view;
  view = new View();
  ConsolLog* logger = new ConsolLog();
  logger->Log("Test Message");
  return 0;
}