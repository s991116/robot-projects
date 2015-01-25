#ifndef COMMAND_H

#define	COMMAND_H

#include <vector>
#include <string>

using namespace std;

class Command {
public:
    virtual std::string Execute(vector<int> input) = 0;
    virtual ~Command() = 0;
    
private:
};

class DelayCommand : public Command {
public:
    DelayCommand();
    std::string Execute(vector<int> input);
    
private:
    int _delay;
};

class KeyPressCommand : public Command {
public:
    KeyPressCommand();
    std::string Execute(vector<int> input);    
};

#endif	/* COMMAND_H */