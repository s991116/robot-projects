#ifndef SENSORINFO_H
#define	SENSORINFO_H

#include <string>

class SensorInfo {
public:
    virtual std::string GetStatus() = 0;
    std::string PrintStatus(std::string, int value);
};

#endif	/* SENSORINFO_H */
