#ifndef EXPODATA_H
#define EXPODATA_H

#define DATASIZE (300)
#define STEPSIZE (-0.025)
#define START (0.0)

class ExpoData {
public:
    ExpoData();
	void Initialize(double speed);
	double GetData(double input);

private:
	double _DataArray[DATASIZE];
	double _StepsizeInverse;
};

#endif