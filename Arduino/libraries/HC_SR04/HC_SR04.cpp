#include "HC_SR04.h"

HC_SR04 *HC_SR04::_instance(NULL);

HC_SR04::HC_SR04(int trigger, int echo, int max_dist) : _trigger(trigger), _echo(echo), _maxDistance(max_dist), _finished(false)
{
  if(_instance==0) _instance=this;
  initialize();
}

void HC_SR04::initialize(){
  pinMode(_trigger, OUTPUT);
  digitalWrite(_trigger, LOW);
  pinMode(_echo, INPUT);  
  attachInterrupt(digitalPinToInterrupt(_echo), _echo_isr, CHANGE);
  _maxDuration = calcDuration(_maxDistance);  
  _state = MESUARE_DISABLED_STATE;
}

void HC_SR04::enable(bool enable)
{
  if(enable) {
    _finished = false;
    setNextMeasureTime();
	_distance = -2;
    _state = START_MEASURE_STATE;	  
  }
  else
  {
	_state = MESUARE_DISABLED_STATE;
  }
}

bool HC_SR04::enabled() {
	return _state != MESUARE_DISABLED_STATE;
}

void HC_SR04::waitToFinished() {
  if(_finished)
  {
    _duration = _end-_start;
    _distance = calcDistance(_duration);
	setNextMeasureTime();
	_state = START_MEASURE_STATE;
  }
  else{
	  unsigned long t = micros();
	  if(_maxDurationNext < t && _minDurationNext < t)
	  {
		  _distance = -1;
		  setNextMeasureTime();
		  _state = START_MEASURE_STATE;
	  }
  }
}

void HC_SR04::setNextMeasureTime() {
  if(_finished)
  {
	_measureTimeNext = millis() + PING_DELAY -(_duration>>10);
  }
  else
  {
    _measureTimeNext = millis() + PING_DELAY;
  }
  	
}

void HC_SR04::start(){
  if(_measureTimeNext < millis())
  {
    _finished=false;
    digitalWrite(_trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigger, LOW);
    _minDurationNext = micros()+1000;
	_state = READING_MEASURE_STATE;
  }
}

void HC_SR04::update() {
	switch(_state)
	{
		case START_MEASURE_STATE:
		  start();
		  break;
		  
		case READING_MEASURE_STATE:
		  waitToFinished();
		  break;
		  
		case MESUARE_DISABLED_STATE:
		  break;  
	}
}

int HC_SR04::getRange() {
  return _distance;
}

unsigned int HC_SR04::calcDistance(unsigned long duration)
{
  return (duration)/DURATION_TO_MM;
}

unsigned int HC_SR04::calcDuration(unsigned int distance)
{
  return distance*DURATION_TO_MM;  
}

void HC_SR04::_echo_isr(){
  HC_SR04* _this=HC_SR04::instance();
  
  switch(digitalRead(_this->_echo)){
    case HIGH:
      _this->_start=micros();
	  _this->_maxDurationNext = _this->_start + _this->_maxDuration;
      break;
    case LOW:
      _this->_end=micros();
      _this->_finished=true;
      break;
  }   
}
