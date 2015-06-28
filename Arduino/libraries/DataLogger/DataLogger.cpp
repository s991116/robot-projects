#include "DataLogger.h"

DataLogger::DataLogger(void)
{
  _size = NR_OF_MEASUREMENTS;
  Reset();
}

void DataLogger::AddMeasure(short data1, short data2)
{
  if(_nr_of_measures < _size)
  {
    _measurements[_nr_of_measures][0] = data1;
    _measurements[_nr_of_measures][1] = data2;
    _nr_of_measures++;
  }
}

bool DataLogger::LogFull()
{
	return (_nr_of_measures >= _size);
}

int DataLogger::GetNrOfMeasures()
{
  return _nr_of_measures;
}

short DataLogger::GetMeasure1()
{
  return _measurements[_read_measure_index][0];
}

short DataLogger::GetMeasure2()
{
  return _measurements[_read_measure_index][1];
}

short DataLogger::NextMeasure()
{
  if(_read_measure_index >= _nr_of_measures)
    return 0;
  _read_measure_index++;
  return 1;
}

void DataLogger::Reset()
{
  _nr_of_measures = 0;
  _read_measure_index = 0;
}