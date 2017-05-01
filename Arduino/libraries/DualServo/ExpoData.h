#ifndef EXPODATA_H
#define EXPODATA_H

#define DATASIZE (50)
#define STEPSIZE (-0.15)
#define START (0.0)

class ExpoData {
public:
	static void Initialize(double speed);
	static float GetData(double input);

private:
	static float _DataArray[DATASIZE];
	static float _StepsizeInverse;
};

#endif