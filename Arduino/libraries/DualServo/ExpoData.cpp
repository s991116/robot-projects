#include "ExpoData.h"
#include "Math.h"

ExpoData::ExpoData() {}

void ExpoData::Initialize(double speed) {
	double input = START;
	for(int i=0; i <DATASIZE; i++)
	{
		_DataArray[i] = 1.0 - exp(input);
		input += STEPSIZE;
	}
	_StepsizeInverse = 1.0/(STEPSIZE*speed);
}

double ExpoData::GetData(double input) {

   int inputIndex = input * _StepsizeInverse;
   if(inputIndex < 0.0)
	   return _DataArray[0];
   if(inputIndex >= DATASIZE)
	   return _DataArray[DATASIZE-1];

   return _DataArray[inputIndex];
}