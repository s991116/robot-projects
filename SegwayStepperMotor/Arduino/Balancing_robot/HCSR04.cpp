#include "HCSR04.h"

//HCSR04 *HCSR04::_instance=NULL;
HCSR04 *HCSR04::_instance(NULL);

HCSR04::HCSR04(int trigger, int echo) : _trigger(trigger), _echo(echo), _finished(false) {
  if(_instance==0) _instance=this;    
}

void HCSR04::Initialize() {
  pinMode(_trigger, OUTPUT);
  digitalWrite(_trigger, LOW);
  pinMode(_echo, INPUT);  
  attachInterrupt(digitalPinToInterrupt(_echo), _echo_isr, CHANGE);
  _distanceSensorEnabled = false;
}

void HCSR04::SetMeasureMode(bool enabled) {
  if(enabled) {
    start();
  }
  _distanceSensorEnabled = enabled;
}

bool HCSR04::IsEnabled() {
    return _distanceSensorEnabled;
}

byte HCSR04::GetDistance() {
    if(_distanceSensorEnabled) {
        if(_distanceMeasured > 255)
            return 255;
        else
            return _distanceMeasured;    
    }
    else {
        return 0; 
    }
}

void HCSR04::UpdateDistanceMeasure() {
    if(_distanceSensorEnabled && isFinished()) {
        _distanceMeasured = getRange();    
        start();
    }
}

void HCSR04::start(){
  _finished=false;
  digitalWrite(_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigger, LOW);  
}

unsigned int HCSR04::getRange(){
  return (_end-_start)/(148);
}

void HCSR04::_echo_isr(){
  HCSR04* _this=HCSR04::instance();
  
  switch(digitalRead(_this->_echo)){
    case HIGH:
      _this->_start=micros();
      break;
    case LOW:
      _this->_end=micros();
      _this->_finished=true;
      break;
  }   
}