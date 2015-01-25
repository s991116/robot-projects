#ifndef VIEW_H
#define	VIEW_H

#include <string>

class Controller;

class View {    
public:   
    void AddListener(Controller* conttroller);
    void InitializeView(void);
    void UpdateView(void);

    void GetMoveCommand(int keyCode);
    void GetCommand(void);
    
private:
    Controller* _controller;
    std::string _currentScript;
    std::string GetScript(void);
    void PrintHelp(void);
};

#endif	/* VIEW_H */

