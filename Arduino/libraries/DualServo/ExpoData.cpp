#include "ExpoData.h"
#include "Math.h"

float ExpoData::_StepsizeInverse = 0;
float ExpoData::_DataArray[DATASIZE];

void ExpoData::Initialize(double speed) {
	float input = START;
	for(int i=0; i <DATASIZE; i++)
	{
		ExpoData::_DataArray[i] = 1.0 - exp(input);
		input += STEPSIZE;
	}
	ExpoData::_StepsizeInverse = 1.0/(STEPSIZE*speed);
}

float ExpoData::GetData(double input) {

   int inputIndex = input * ExpoData::_StepsizeInverse;
   if(inputIndex < 0.0)
	   return ExpoData::_DataArray[0];
   if(inputIndex >= DATASIZE)
	   return ExpoData::_DataArray[DATASIZE-1];

   return ExpoData::_DataArray[inputIndex];
}