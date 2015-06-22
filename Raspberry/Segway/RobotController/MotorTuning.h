#pragma once
#include "HardwareController.h"
#include "IMotorTuning.h"

class MotorTuning : public IMotorTuning
{
public:
	MotorTuning(HardwareController* controller);
	~MotorTuning();

	void StartMeasuring();
	void StopMeasuring();
	short GetError();
      	short GetTarget();
        void NextMeasure();
	int GetNrOfMeasurement();

private:
	HardwareController* _Controller;
	int _NrOfMeasurement;
};

