#include "arduino.h"
#include "StepperMotor.h"

byte StepperMotor::M_28BYJ_48[][PHASE_NUMBER] = 
{
	{ 0, 0, 0, 1 },
	{ 0, 0, 1, 1 },
	{ 0, 0, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 1, 1, 0, 0 },
	{ 1, 0, 0, 0 },
	{ 1, 0, 0, 1 }
};

StepperMotor::StepperMotor(byte motorPin1, byte motorPin2, byte motorPin3, byte motorPin4)
	: period(DEFAULT_PERIOD), stepIdx(0), interrupt(false)
{
	motorPins[0] = motorPin1;
	motorPins[1] = motorPin2;
	motorPins[2] = motorPin3;
	motorPins[3] = motorPin4;

	assignMotorPins();
	
	// Initialize the stepSequence matrix
	for (int n = 0; n < NUMBER_OF_STEPS; ++n)
	{
		for (int p = 0; p < PHASE_NUMBER; ++p)
		{
			stepSequence[n][p] = M_28BYJ_48[n][p];
		}
	}
}

void StepperMotor::setPeriod(int period)
{
	this->period = period;
}

bool StepperMotor::move(int numberOfSteps)
{
	if (numberOfSteps > 0)
	{
		return moveStepsForward(numberOfSteps);
	}
	else
	{
		return moveStepsBackward(abs(numberOfSteps));
	}
}

void StepperMotor::stop(bool stop)
{
	if (stop)
	{
		interrupt = true;
	}
	for (byte idx = 0; idx < PHASE_NUMBER; ++idx)
	{
		digitalWrite(motorPins[idx], LOW);
	}
}

void StepperMotor::reset()
{
	interrupt = false;
}

void StepperMotor::moveOneStep(byte seqIdx)
{
	for (byte idx = 0; idx < PHASE_NUMBER; ++idx)
	{
		digitalWrite(motorPins[idx], stepSequence[seqIdx][idx]);
	}
 
	delay(period);
}

bool StepperMotor::moveOneStepForward()
{
	if (!interrupt)
	{
		stepIdx = incrementStep(stepIdx);
		moveOneStep(stepIdx);
	}
	
	return interrupt;
}

bool StepperMotor::moveOneStepBackward()
{
	if (!interrupt)
	{
		stepIdx = incrementStep(stepIdx);
		moveOneStep(NUMBER_OF_STEPS - stepIdx - 1);
	}
	
	return interrupt; 
}

bool StepperMotor::moveStepsForward(int steps)
{
	for(int n = 0; n < steps; n++)
	{
		if (moveOneStepForward())
		{
			break;
		}
	}

	return interrupt;
}

bool StepperMotor::moveStepsBackward(int steps)
{
	for(int n = 0; n < steps; n++)
	{
		if (moveOneStepBackward())
		{
			break;
		}
	}

	return interrupt;
}





