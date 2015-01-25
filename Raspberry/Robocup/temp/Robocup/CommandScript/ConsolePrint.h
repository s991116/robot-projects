#ifndef CONSOLEPRINT_H
#define	CONSOLEPRINT_H

#include <string>
#include <vector>

using namespace std;

class ConsolePrint {
public:
    static void PrintStandard(string line);
    static void PrintCommand(string line);
    static void PrintError(string line);
    static void PrintSetting(string line);
    static void PrintCall(string line);
    static void PrintLog(string line);
    static void PrintEmpty(string line);
    static void PrintResult(string result);

private:
    enum ConsoleColor
    {
      BLACK=30,
      RED=31,
      GREEN=32,
      YELLOW=33,
      BLUE=34,
      PURPLE=35,
      CYAN=36,
      WHITE=37,
    };

    static void PrintColor(string line, ConsoleColor color);
    static void Print(string line);    
};

#endif	/* CONSOLEPRINT_H */

