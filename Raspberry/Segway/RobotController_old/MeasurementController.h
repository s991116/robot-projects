#pragma once
#include "HardwareController.h"

class MeasurementController
{
public:
	MeasurementController(HardwareController* controller);
	~MeasurementController();

	void StartMeasuring();
	void StopMeasuring();
	short GetNextMeasure();
	int GetNrOfMeasurement();

private:
	HardwareController* _Controller;
	int _NrOfMeasurement;
};

