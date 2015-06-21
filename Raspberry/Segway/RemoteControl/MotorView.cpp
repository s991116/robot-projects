#include "MotorView.h"
#include "iostream"
#include "Convert.h"
#include "BufferedInput.h"
#include "KeyCodes.h"

MotorView::MotorView(Motor* motor) {
    _Motor = motor;
}

void MotorView::View() {
    BufferedInput buf = BufferedInput();

    std::cout << "*** Motor view ***" << std::endl;
    
    while(true)
    {
        PrintHelp();
    
    
        int keyCode = buf.WaitAndReadKey();    
        if(keyCode == KeyCodes::KeyCode_x)
            break;
        
        std::cout << "Set motorspeed:";        
        std::string input = buf.ReadLine();
        int speed = Convert::StringToInt(input);
        _Motor->SetMotorLeftSpeed(speed);
        _Motor->SetMotorRightSpeed(speed);        
    }
}

void MotorView::PrintHelp() {
    std::cout << "S: Setspeed for both motors" << std::endl;    
}

MotorView::~MotorView() {
}

