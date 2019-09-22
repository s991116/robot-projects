#ifndef HCSR04_H
#define HCSR04_H

#include <Arduino.h>

class HCSR04 {
  public:
    HCSR04(int trigger, int echo);
    
    void Initialize();
    void SetMeasureMode(bool enabled);
    bool IsEnabled();
    byte GetDistance();
    void UpdateDistanceMeasure();

    static HCSR04* instance(){ return _instance; }
    
  private:
    static void _echo_isr();
    
    int _trigger, _echo, _int;
    volatile unsigned long _start, _end;
    volatile bool _finished;
    static HCSR04* _instance;
    bool _distanceSensorEnabled;
    unsigned int _distanceMeasured;

    void start();
    bool isFinished(){ return _finished; }
    unsigned int getRange();
};

#endif