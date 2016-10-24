

const int debounceTime = 50;
int oldButtonState = 0;
unsigned long buttonSwitchTime;
int buttonState = 0;         // variable for reading the pushbutton status

void InitalizeButton()
{
  pinMode(SWITCH_BUTTON_PIN, INPUT);  
}

void HandleButtonSwitch() {
  int state = digitalReadDirect(SWITCH_BUTTON_PIN);

  if(state != oldButtonState)
  {
    unsigned long t = millis();
    if((t - buttonSwitchTime) > debounceTime)
    {
      buttonSwitchTime = t;
      buttonState = 1 - buttonState;
      oldButtonState = state;

      if(buttonState == 0)
      {
        HandleButtonPress();
      }
    }
  }
}

void HandleButtonPress()
{
  Serial.println("Button pressed.");
  bool s = GetSegwayEnabled();
  SetSegwayEnabled(!s);
}

