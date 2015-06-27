#ifndef DATALOGGER_H
#define DATALOGGER_H

#include "Arduino.h"

#define NR_OF_MEASUREMENTS (250)

class DataLogger {
public:
  DataLogger(void);
  void AddMeasure(short data1, short data2);
  int GetNrOfMeasures();
  short GetMeasure1();
  short GetMeasure2();
  short NextMeasure();
  bool LogFull();
  void Reset();
  
private:
  int _nr_of_measures;
  int _read_measure_index;
  int _size;
  short _measurements[NR_OF_MEASUREMENTS][2];
};

#endif //DATALOGGER_H
