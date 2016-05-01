#ifndef HC_SR04_H
#define HC_SR04_H

#include <Arduino.h>

#define DURATION_TO_MM (57)
#define PING_DELAY (30)

#define START_MEASURE_STATE   (0)
#define READING_MEASURE_STATE (1)
#define MESUARE_DISABLED_STATE (2)


class HC_SR04 {
  public:
    HC_SR04(int trigger, int echo, int max_dist=20000);
    
	void enable(bool enable);
	bool enabled();
	void update();
    int getRange();
	
  private:
    static HC_SR04* instance(){ return _instance; }
    static void _echo_isr();
	void initialize();
	void start();
    void waitToFinished();
	void setNextMeasureTime();

	unsigned int calcDistance(unsigned long duration);
	unsigned int calcDuration(unsigned int distance);
	volatile int _distance;
	unsigned long _duration;
	unsigned long _maxDurationNext;
	unsigned long _minDurationNext;
	unsigned long _measureTimeNext;
	unsigned int _maxDuration;
	unsigned int _maxDistance;
    int _trigger, _echo;
    volatile unsigned long _start, _end;
    volatile bool _finished;
    static HC_SR04* _instance;
	int _state;
};

#endif
