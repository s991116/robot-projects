#ifndef IMOTORTUNING_H
#define	IMOTORTUNING_H

class IMotorTuning {
public:
    virtual void StartMeasuring() = 0;
    virtual void StopMeasuring() = 0;
    
    virtual short GetError() = 0;
    virtual short GetTarget() = 0;
    virtual void NextMeasure() = 0;
    virtual int GetNrOfMeasurement() = 0;
};

#endif	/* IMOTORTUNING_H */

