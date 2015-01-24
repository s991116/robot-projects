#include "CheckWithBreak.h"
#include "KeyCodes.h"
#include <stdio.h>
#include "BufferedInput.h"
#include "Direction.h"

CheckWithBreak::CheckWithBreak(Check* check, ComController* comController) {
  _Check = check;
  _ComController = comController;
}

void CheckWithBreak::Prepare() {
  _Check->Prepare();
}

void CheckWithBreak::ChangeCheck(Check* check)
{
  _Check = check;
}

bool CheckWithBreak::Test() {
  BufferedInput bufInput;
  int keyCode = bufInput.getch();  
  if(keyCode == KEYCODE_x)
    return false;

  if(keyCode == KEYCODE_SPACE)
  {
    Direction* direction = _ComController->GetDirection();
    Direction* stop = new Direction(0, 0, 0);
    _ComController->SetDirection(stop);
    do{
      keyCode = bufInput.getch();      
    }while(keyCode != KEYCODE_r);
    _ComController->SetDirection(direction);
  }
  else
  {
    return _Check->Test();
  }
}