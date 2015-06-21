#pragma once
#include "HardwareController.h"

class MeasurementController
{
public:
	MeasurementController(HardwareController* controller);
	~MeasurementController();

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

